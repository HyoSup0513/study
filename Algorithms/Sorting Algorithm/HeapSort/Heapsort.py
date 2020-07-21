# To heapify subtree rooted at index 'idx'.
def heapify(array, idx, heap_size):
    largest = idx  # Initialize largest as root
    left = 2*idx + 1  # left child
    right = 2*idx + 2  # right child

    # CHeck left child of root exists and is greater than root
    if left < heap_size and arr[left] > arr[largest]:
        largest = left

    # Check if right child of root exists and is greater than root
    if right < heap_size and arr[right] > arr[largest]:
        largest = right

    # Change root, if needed
    if largest != idx:
        arr[largest], arr[idx] = arr[idx], arr[largest]  # Swap

        # Heapify the root.
        heapify(arr, largest, heap_size)


def heap_sort(arr):
    n = len(arr)

    # First, build a maxheap.
    for i in range((n // 2) - 1, -1, -1):
        heapify(arr, i, n)

    for i in range(n-1, 0, -1):
        # Swap first and last element of array.
        arr[0], arr[i] = arr[i], arr[0]
        # Then, heapify.
        heapify(arr, 0, i)
    return arr


def display(arr):
    for i in range(len(arr)):
        print(arr[i], end=" ")


if __name__ == '__main__':
    arr = [8, 7, 6, 5, 4, 3, 2, 1]
    print("Original array: ")
    display(arr)
    print()
    print("Sorted array: ")
    heap_sort(arr)
    display(arr)
