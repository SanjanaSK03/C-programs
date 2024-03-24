#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Function to concatenate two strings
void concatenate_strings(char *str1, char *str2, char *result) {
    strcpy(result, str1);
    strcat(result, str2);
}

// Function to copy one string to another
void copy_string(char *src, char *dst) {
    strcpy(dst, src);
}

// Function to compare two strings
int compare_strings(char *str1, char *str2) {
    return strcmp(str1, str2);
}

int main() {
    FILE *input, *output;
    char str1[MAX], str2[MAX];
    char result[MAX * 2]; 
    input = fopen("input.txt", "r");
    if (input == NULL) {
        perror("Error in opening input file");
        return 1;
    }

    fscanf(input, "%s", str1);
    fscanf(input, "%s", str2);

    concatenate_strings(str1, str2, result);
    int comparison_result = compare_strings(str1, str2);
    char copied_string[MAX];
    copy_string(str1, copied_string);

    output = fopen("output.txt", "w");
    
    fprintf(output, "Concatenated string: %s\n", result);
    fprintf(output, "Comparison result: %d\n", comparison_result);
    fprintf(output, "Copied string: %s\n", copied_string);
    fclose(output);
    return 0;
}
