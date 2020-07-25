import unittest
from src.quick_sort import quicksort


class MyTestCase(unittest.TestCase):
    def test_quicksort(self):
        lst = [6, 8, 4, 9, 2, 0, 1, 3]
        self.assertEqual(sorted(lst), quicksort(lst))


if __name__ == '__main__':
    unittest.main()
