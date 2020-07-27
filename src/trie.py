from typing import List


class _Node(object):
    def __init__(self):
        self._child_by_char = {}
        self._is_end_of_word = False

    @property
    def is_end_of_word(self):
        return self._is_end_of_word

    @is_end_of_word.setter
    def is_end_of_word(self, is_end_of_word: bool):
        self._is_end_of_word = is_end_of_word

    @property
    def has_children(self):
        return len(self._child_by_char)

    def __getitem__(self, char: str):
        return self._child_by_char.get(char)

    def __setitem__(self, char: str, node):
        self._child_by_char[char] = node

    def _words(self) -> List[List[str]]:
        words: List[List[str]] = []
        if self.is_end_of_word:
            words.append([''])
        for char, node in self._child_by_char.items():
            if node is None:
                continue
            word: List[str]
            node: _Node
            words.extend([char] + word for word in node._words())
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
