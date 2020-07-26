from statistics import median


def _partition(lst, begin, end):
    """
    Partition a list in place using it's last element as the pivot
    :param lst: The list to partition
    :param begin: The beginning of the list
    :param end: The end of the list
    :return: The new position of the pivot element
    """
    next_below_pivot_index = begin
    pivot_index = end - 1
    for i in range(begin, pivot_index):
        if lst[i] > lst[pivot_index]:
            continue
        lst[i], lst[next_below_pivot_index] = lst[next_below_pivot_index], lst[i]
        next_below_pivot_index += 1
    lst[next_below_pivot_index], lst[pivot_index] = lst[pivot_index], lst[next_below_pivot_index]
    return next_below_pivot_index


def _get_pivot_index(lst, begin, end):
    candidate_indices = [begin, (begin + end) // 2, end - 1]
    m = median(map(lst.__getitem__, candidate_indices))
    return next(i for i in candidate_indices if lst[i] == m)


def quicksort(lst):
    spans = [(0, len(lst))]

    while len(spans) != 0:
        begin, end = spans.pop()
        if end - begin <= 1:
            continue

        pivot_index = _get_pivot_index(lst, begin, end)
        lst[pivot_index], lst[end - 1] = lst[end - 1], lst[pivot_index]
        pivot_index = _partition(lst, begin, end)

        spans.append((begin, pivot_index))
        spans.append((pivot_index + 1, end))


def quicksorted(lst):
    new_lst = lst[:]
    quicksort(new_lst)
    return new_lst
