#include <stdio.h>

int binarySearch(int arr[], int size, int target, int *comparisons) {
    int low = 0, high = size - 1;
    *comparisons = 0;

    while (low <= high) {
        (*comparisons)++;
        int mid = (low + high) / 2;

        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1; // Element not found
}

int main() {
    int arr[] = {5, 10, 15, 20, 25, 30, 35, 40, 45};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 20, comparisons;

    int index = binarySearch(arr, size, target, &comparisons);

    if (index != -1)
        printf("Element %d found at index %d with %d comparisons.\n", target, index, comparisons);
    else
        printf("Element not found.\n");

    return 0;
}
