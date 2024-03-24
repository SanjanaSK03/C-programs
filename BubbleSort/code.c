#include <stdio.h>

void bubbleSort(int arr[], int size) {
    int i, j;
    for (i = 0; i < size-1; i++) 
    {
        for (j = 0; j < size-i-1; j++) 
        {
            if (arr[j] > arr[j+1]) 
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
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
 
    bubbleSort(arr, size);

    output = fopen("output.txt", "w");

    for (int i = 0; i < size; i++)
        {
            fprintf(output, "%d ", arr[i]);
        }
    fclose(output);
    return 0;
}
