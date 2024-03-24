#include <stdio.h>

int binarySearch(int [], int , int);

int main()
{
    int arr[10];
    int key;
    FILE *input, *output;
    input = fopen("input.txt", "r");
    if (input == NULL)
    {
        perror("\nError in opening input file\n");
        return 1;
    }

    int i = 0;
    while (fscanf(input, "%d", &arr[i]) != EOF)
    {
        i++;
        if (i >= 10)
        {
            printf("Overflow\n");
            break;
        }
    }
    fclose(input);

    int size = i;

    printf("Enter key to search: ");
    scanf("%d", &key);

    

    output = fopen("output.txt", "w");
    fprintf(output,"Elements are:\n");
    for (int j = 0; j < size; j++)
    {
        fprintf(output,"%d ", arr[j]);
    }
    fprintf(output,"\n");
    int index = binarySearch(arr, size, key);
    if (index != 1)
    {
        fprintf(output, "Key element %d is found at index %d\n", key,index);
    }
    else
    {
        fprintf(output, "Key %d is not found\n", key);
    }

    fclose(output);
    return 0;
}

int binarySearch(int arr[], int size, int key)
{
    int low = 0;
    int high = size - 1;
    int mid;

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}