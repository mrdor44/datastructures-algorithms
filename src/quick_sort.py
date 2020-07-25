from statistics import median


def _get_pivot_index(lst):
    candidate_indices = [0, len(lst) // 2, -1]
    m = median(map(lst.__getitem__, candidate_indices))
    return next(i for i in candidate_indices if lst[i] == m)


def quicksort(lst):
    if len(lst) == 0:
        return []

    pivot_index = _get_pivot_index(lst)
    left = [e for e in lst if e <= lst[pivot_index]]
    left.remove(lst[pivot_index])
    right = [e for e in lst if e > lst[pivot_index]]

    return quicksort(left) + [lst[pivot_index]] + quicksort(right)
