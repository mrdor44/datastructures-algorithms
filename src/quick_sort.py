from statistics import median


def _partition(lst):
    """
    Partition a list in place using it's last element as the pivot
    :param lst: The list to partition
    :return: The new position of the pivot element
    """
    next_below_pivot_index = 0
    for i in range(len(lst) - 1):  # Don't consider the pivot element
        if lst[i] > lst[-1]:
            continue
        lst[i], lst[next_below_pivot_index] = lst[next_below_pivot_index], lst[i]
        next_below_pivot_index += 1
    lst[next_below_pivot_index], lst[-1] = lst[-1], lst[next_below_pivot_index]
    return next_below_pivot_index


def _get_pivot_index(lst, begin, end):
    candidate_indices = [begin, (begin + end) // 2, end - 1]
    m = median(map(lst.__getitem__, candidate_indices))
    return next(i for i in candidate_indices if lst[i] == m)


def quicksort(lst, begin=None, end=None):
    if len(lst) == 0:
        return []

    begin = begin or 0
    end = end or len(lst)

    pivot_index = _get_pivot_index(lst, begin, end)
    lst[pivot_index], lst[end - 1] = lst[end - 1], lst[pivot_index]
    lst = lst[begin:end]
    pivot_index = _partition(lst)
    left = lst[:pivot_index]
    right = lst[pivot_index + 1:]

    return quicksort(left) + [lst[pivot_index]] + quicksort(right)
