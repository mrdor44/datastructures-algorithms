import re


class SharedPtr(object):
    def __init__(self, obj):
        self.obj = obj

    def get(self):
        return self.obj['_M_ptr']

    def deref(self):
        return self.get().dereference()

    def __getitem__(self, item):
        return self.deref()[item]


class TypePrinter(object):
    TYPE_PATTERN = None

    def __init__(self, obj):
        self.obj = obj

    def to_string(self):
        raise NotImplementedError()


class ListPrinter(TypePrinter):
    TYPE_PATTERN = re.compile('^List<.*>$')

    def to_string(self):
        first_dummy = SharedPtr(self.obj['m_first_dummy'])
        last_dummy = SharedPtr(self.obj['m_last_dummy'])
        current_node = SharedPtr(first_dummy['next'])
        values = []
        while current_node.get() != last_dummy.get():
            values.append(current_node['value'])
            current_node = SharedPtr(current_node['next'])
        return ', '.join(map(str, values))


class ListNodePtrPrinter(TypePrinter):
    TYPE_PATTERN = re.compile('element_type')

    def to_string(self):
        return str(self.obj['value'])


class StackPrinter(TypePrinter):
    TYPE_PATTERN = re.compile('^Stack<.*>$')

    def to_string(self):
        if self.obj['m_list']['m_length'] == 0:
            return 'Stack: Empty ||'
        return f'Stack: top = {self.obj["m_list"]} ||'


TYPE_PRINTERS = (StackPrinter, ListPrinter, ListNodePtrPrinter)


def lookup_type(val):
    lookup_tag = val.type
    if lookup_tag is None:
        return None
    lookup_tag = str(lookup_tag)
    for printer in TYPE_PRINTERS:
        if printer.TYPE_PATTERN.search(lookup_tag):
            return printer(val)
    return None


gdb.pretty_printers.append(lookup_type)
