import unittest
from src import trie


class TrieTests(unittest.TestCase):
    def test_trie(self):
        _WORDS = ('great', 'greece', 'green', 'greenwich', 'grumble', 'balloon', 'ball',
                  'babka')
        t = trie.Trie()
        for w in _WORDS:
            t.insert(w)
        self.assertSetEqual(set(_WORDS), set(t.words()))
        for w in _WORDS:
            self.assertTrue(t.hasword(w))
            self.assertFalse(t.hasword(w + 'z'))
        for w in _WORDS:
            t.delete(w)
            self.assertFalse(t.hasword(w))


if __name__ == '__main__':
    unittest.main()
