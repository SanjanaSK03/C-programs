#include <stdio.h>

void selectionSort(int arr[], int size) 
{
    int i, j, min;
    for (i = 0; i < size-1; i++) 
    {
        min = i;
        for (j = i+1; j < size; j++)
        {
            if (arr[j] < arr[min])
                min = j;
        }
        int temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

int main() 
{
    FILE *input, *output;
    int arr[100], size;
    input = fopen("input.txt", "r");
    if (input == NULL) 
    {
        perror("Error in opening input file");
        return 1;
    }
    size = 0;
    while (fscanf(input, "%d", &arr[size]) != EOF && size < 100)
        {
            size++;
        }

    selectionSort(arr, size);


    output = fopen("output.txt", "w");
    for (int i = 0; i < size; i++)
    {
        fprintf(output, "%d ", arr[i]);
    }
    fclose(output);
    return 0;
}
