def _get_pivot(lst):
    return lst[0]


def quicksort(lst):
    if len(lst) == 0:
        return []

    pivot = _get_pivot(lst)
    left = [e for e in lst if e <= pivot]
    left.remove(pivot)
    right = [e for e in lst if e > pivot]

    return quicksort(left) + [pivot] + quicksort(right)
