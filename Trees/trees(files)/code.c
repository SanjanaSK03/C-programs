/* I-insert
S-search
A-preorder
B-inorder
C-postorder*/
#include <stdio.h>
#include <stdlib.h>

struct tree {
    int data;
    struct tree *left;
    struct tree *right;
};

void insert(struct tree **root, int d) 
{
    struct tree *newNode = (struct tree*)malloc(sizeof(struct tree));
    if(newNode == NULL) 
    {
        perror("Error in creating the node");
        exit(0);
    }
    newNode->data = d;
    newNode->right = NULL;
    newNode->left = NULL;
    if(*root == NULL) 
    {
        *root = newNode;
        return;
    }
    struct tree *cur = *root;
    struct tree *parent = NULL;
    while(cur != NULL) 
    {
        parent = cur;
        if(d > (cur->data))
        {
            cur = cur->right;
        }
        else 
        {
            cur = cur->left;
        }
    }
    if(d > (parent->data)) 
    {
        parent->right = newNode;
    }
    else 
    {
        parent->left = newNode;
    }
}

void preorder(struct tree *root, FILE *output) 
{
    if(root == NULL)
        return;
    fprintf(output, "%d ", root->data);
    preorder(root->left, output);
    preorder(root->right, output);
}

void inorder(struct tree *root, FILE *output) 
{
    if(root == NULL)
        return;
    inorder(root->left, output);
    fprintf(output, "%d ", root->data);
    inorder(root->right, output);
}

void postorder(struct tree *root, FILE *output) 
{
    if(root == NULL)
        return;
    postorder(root->left, output);
    postorder(root->right, output);
    fprintf(output, "%d ", root->data);
}

struct tree* search(struct tree *root, int val) 
{
    if(root == NULL || root->data == val)
        return root;
    if(val < root->data)
        return search(root->left, val);
    return search(root->right, val);
}

int main() 
{
    struct tree *root = NULL;
    FILE *input, *output;
    input = fopen("input.txt", "r");
    if(input == NULL) 
    {
        perror("Error in opening the file");
        exit(0);
    }
    output = fopen("output.txt", "w");
    if(output == NULL) 
    {
        perror("Error in opening the file");
        exit(0);
    }
    char ch;
    int val;
    while(fscanf(input, "%c", &ch) == 1) {
        switch(ch) 
        {
            case 'I':
                fscanf(input, "%d", &val);
                insert(&root, val);
                break;
            case 'A':
                fprintf(output, "Preorder traversal: ");
                preorder(root, output);
                fprintf(output, "\n");
                break;
            case 'B':
                fprintf(output, "Inorder traversal: ");
                inorder(root, output);
                fprintf(output, "\n");
                break;
            case 'C':
                fprintf(output, "Postorder traversal: ");
                postorder(root, output);
                fprintf(output, "\n");
                break;
            case 'S':
                fscanf(input, "%d", &val);
                if(search(root, val) == NULL) 
                {
                    fprintf(output, "Key value %d not found", val);
                    fprintf(output, "\n");
                }
                else 
                {
                    fprintf(output, "Key value %d found", val);
                    fprintf(output, "\n");
                }
                break;
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}
