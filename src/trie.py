from typing import List, Optional


class _INode(object):
    @property
    def is_end_of_word(self):
        raise NotImplementedError()

    @property
    def has_children(self):
        raise NotImplementedError()


class _Node(_INode):
    _children: List[Optional[_INode]]

    def __init__(self):
        # TODO: Dynamic children allocation
        self._children: List[Optional[_Node]]
        self._children = [None] * (ord('z') - ord('a') + 1)
        self._num_children = 0
        self._is_end_of_word = False

    @property
    def is_end_of_word(self):
        return self._is_end_of_word

    @is_end_of_word.setter
    def is_end_of_word(self, is_end_of_word: bool):
        self._is_end_of_word = is_end_of_word

    @property
    def has_children(self):
        return self._num_children > 0

    def __getitem__(self, char: str):
        assert len(char) == 1
        return self._children[ord(char) - ord('a')]

    def __setitem__(self, char: str, node):
        assert len(char) == 1
        index = ord(char) - ord('a')
        if self._children[index] is None and node is not None:
            self._num_children += 1
        if self._children[index] is not None and node is None:
            self._num_children -= 1
        self._children[index] = node

    def _words(self) -> List[List[str]]:
        words: List[List[str]] = []
        if self.is_end_of_word:
            words.append([''])
        for i, node in enumerate(self._children):
            if node is None:
                continue
            word: List[str]
            node: _Node
            words.extend([chr(i + ord('a'))] + word for word in node._words())
        return words

    def words(self):
        return map(''.join, self._words())


class Trie(object):
    def __init__(self):
        self._root = _Node()

    def insert(self, word):
        current = self._root
        for c in word:
            current[c] = current[c] or _Node()
            current = current[c]
        current.is_end_of_word = True

    def words(self):
        return self._root.words()

    def hasword(self, word):
        current = self._root
        for c in word:
            current = current[c]
            if current is None:
                return False
        return current.is_end_of_word

    def delete(self, word):
        nodes_stack = []
        current = self._root
        for char in word:
            nodes_stack.insert(0, (current, char))
            current = current[char]
            if current is None:
                return
        current.is_end_of_word = False
        for node, char in nodes_stack:
            if not node[char].has_children and node[char].is_end_of_word:
                node[char] = None
