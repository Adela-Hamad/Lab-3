//iterative Algorithm5

#include <stdio.h>

void iterative_shuffle(int arr[], int n) {
    int odd[n], even[n];
    int odd_count = 0, even_count = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 != 0) {
            odd[odd_count] = arr[i];
            odd_count++;
        } else {
            even[even_count] = arr[i];
            even_count++;
        }
    }

    for (int i = 0; i < n; i++) {
        if (i < odd_count) {
            arr[i] = odd[i];
        } else {
            arr[i] = even[i - odd_count];
        }
    }
}

int main() {
    int arr[] = {5, 8, 3, 1, 6, 9, 7, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    iterative_shuffle(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}