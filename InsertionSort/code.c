#include <stdio.h>

void insertionSort(int arr[], int size)
 {
    int i, key, j;
    for (i = 1; i < size; i++) 
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
         {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main()
 {
    FILE *input, *output;
    int arr[100], size;
    input = fopen("input.txt", "r");
    if (input == NULL) {
        perror("Error in opening input file");
        return 1;
    }
    size = 0;
    while (fscanf(input, "%d", &arr[size]) != EOF && size < 100)
        {
            size++;
        }
    insertionSort(arr, size);
    output = fopen("output.txt", "w");
    
    for (int i = 0; i < size; i++)
        {
            fprintf(output, "%d ", arr[i]);
        }
    fclose(output);
    return 0;
}
