from statistics import median


def _partition(lst, pivot_index):
    next_below_pivot_index = 0
    for i, value in enumerate(lst):
        if value > lst[pivot_index] or i == pivot_index:
            continue
        lst[i], lst[next_below_pivot_index] = lst[next_below_pivot_index], lst[i]
        next_below_pivot_index += 1
    lst[next_below_pivot_index], lst[pivot_index] = lst[pivot_index], lst[next_below_pivot_index]
    return next_below_pivot_index


def _get_pivot_index(lst):
    candidate_indices = [0, len(lst) // 2, -1]
    m = median(map(lst.__getitem__, candidate_indices))
    return next(i for i in candidate_indices if lst[i] == m)


def quicksort(lst):
    if len(lst) == 0:
        return []

    pivot_index = _get_pivot_index(lst)
    pivot_index = _partition(lst, pivot_index)
    left = lst[:pivot_index]
    right = lst[pivot_index + 1:]

    return quicksort(left) + [lst[pivot_index]] + quicksort(right)
