def quick_sort(arr):
    def quicksort(low, high):
        if high <= low:
            return

        mid = partition(low, high)
        quicksort(low, mid - 1)
        quicksort(mid, high)

    # return the index of a split point
    def partition(low, high):

        # Specify the value in the middle of the list as the pivot value
        pivot = arr[(low + high) // 2]
        while low <= high:
            while arr[low] < pivot:
                low += 1

            while arr[high] > pivot:
                high -= 1

            if low <= high:
                arr[low], arr[high] = arr[high], arr[low]
                low, high = low + 1, high - 1
        return low

    return quicksort(0, len(arr) - 1)


def display(arr):
    for i in range(len(arr)):
        print(arr[i], end=" ")


if __name__ == '__main__':
    arr = [8, 7, 6, 5, 4, 3, 2, 1]
    print("Original array: ")
    display(arr)
    print()
    print("Sorted array: ")
    quick_sort(arr)
    display(arr)
