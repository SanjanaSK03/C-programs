#include <stdio.h>
#define MAX_SIZE 10
int main() 
{

    FILE *input,*output;
    int array[MAX_SIZE];
    int size, largest, smallest, sum;
    float average;

    input = fopen("input.txt", "r");
    if (input == NULL) {
        printf("Error opening input file\n");
        return 1;
    }
    size = 0;
    while (fscanf(input, "%d", &array[size]) != EOF) 
    {
        size++;
    }
    largest = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > largest) {
            largest = array[i];
        }
    }

    smallest = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] < smallest) {
            smallest = array[i];
        }
    }

    sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }

    average = (float) sum / size;

    output = fopen("output.txt", "w");
    fprintf(output, "Largest Element: %d\n", largest);
    fprintf(output, "Smallest Element: %d\n", smallest);
    fprintf(output, "Sum: %d\n", sum);
    fprintf(output, "Average: %.2f\n", average);
    fclose(output);
    return 0;
}
