class _Node(object):
    def __init__(self):
        # TODO: Dynamic children allocation
        self._children = [None] * (ord('z') - ord('a') + 1)
        self._is_end_of_word = False

    @property
    def is_end_of_word(self):
        return self._is_end_of_word

    @is_end_of_word.setter
    def is_end_of_word(self, is_end_of_word: bool):
        self._is_end_of_word = is_end_of_word

    def __getitem__(self, char: str):
        assert len(char) == 1
        return self._children[ord(char) - ord('a')]

    def __setitem__(self, char: str, node):
        assert len(char) == 1
        self._children[ord(char) - ord('a')] = node

    def words(self):
        words = []
        if self.is_end_of_word:
            words.append('')
        for i, node in enumerate(self._children):
            if node is None:
                continue
            words.extend(f"{chr(i + ord('a'))}{word}" for word in node.words())
        return words


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
