def mergesort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        left = arr[:mid]
        right = arr[mid:]

        # sort first half
        mergesort(left)
        # sort second half
        mergesort(right)

        i = j = k = 0

        while i < len(left) and j < len(right):
            if left[i] < right[j]:
                arr[k] = left[i]
                i += 1
            else:
                arr[k] = right[j]
                j += 1
            k += 1

        while i < len(left):
            arr[k] = left[i]
            i += 1
            k += 1

        while j < len(right):
            arr[k] = right[j]
            j += 1
            k += 1


def display(arr):
    for i in range(len(arr)):
        print(arr[i], end=" ")


if __name__ == '__main__':
    arr = [8, 7, 6, 5, 4, 3, 2, 1]
    print("Original array: ")
    display(arr)
    print()
    print("Sorted array: ")
    mergesort(arr)
    display(arr)
