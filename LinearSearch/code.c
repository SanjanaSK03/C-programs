#include <stdio.h>

int linearSearch(int [], int , int);

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

    printf("Enter key: ");
    scanf("%d", &key);

    int s = linearSearch(arr, size, key);

    output = fopen("output.txt", "w"); // Corrected here
    fprintf(output,"Elements are:\n");
    for (int j = 0; j < size; j++)
    {
        fprintf(output,"%d ", arr[j]);
    }
    fprintf(output,"\n");
    if (s == 1)
    {
        fprintf(output, "Key %d is found\n", key);
    }
    else if (s == -1)
    {
        fprintf(output, "Key %d is not found\n", key);
    }

    fclose(output);
    return 0;
}

int linearSearch(int arr[], int size, int key)
{
    for (int j = 0; j < size; j++)
    {
        if (arr[j] == key)
            return 1;
    }
    return -1;
}

