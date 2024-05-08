#include <stdio.h>
#include <stdlib.h>
struct tree
{
    int data;
    struct tree *left;
    struct tree *right;
};

void insert(struct tree **root, int d) {
    struct tree *newnode;
    newnode = (struct tree*)malloc(sizeof(struct tree));
    if (newnode == NULL) {
        perror("Error in creating a node");
        exit(0);
    }
    newnode->data = d;
    newnode->left = NULL;
    newnode->right = NULL;

    if ((*root) == NULL) {
        *root = newnode;
        printf("Insertion Successful\n");
        return;
    }

    struct tree *cur, *parent;
    cur = *root;
    parent = NULL;
    while (cur != NULL) 
    {
        parent = cur;
        if ((newnode->data)> (cur->data)) 
        {
            cur = cur->right;
        }
        else 
        {
            cur = cur->left;
        }
    }
    if ((newnode->data) < (parent->data)) 
    {
        parent->left = newnode;
    }
    else
     {
        parent->right = newnode;
    }
    printf("Insertion Successful\n");
}

void inOrder(struct tree *root)
{
    if(root!=NULL)
    {
        inOrder(root->left);
        printf("%d  ",root->data);
        inOrder(root->right);
    }
}
void preOrder(struct tree *root)
{
    if(root!=NULL)
    {
        printf("%d  ",root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}
void postOrder(struct tree *root)
{
    if(root!=NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d  ",root->data);
    }
}
struct tree* search(struct tree *root,int d)
{
    if(root==NULL)
    return root;
    if(root->data==d)
    return root;
    else if((root->data)>d)
    return search(root->left,d);
    else if((root->data)<d)
    return search(root->right,d);
}
int main()
{
    struct tree *root=NULL;
    int key;
    insert(&root, 50);
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 40);
    insert(&root, 70);
    insert(&root, 60);
    printf("Inorder=\n");
    inOrder(root);
    printf("\nPreorder=\n");
    preOrder(root);
    printf("\nPostorder=\n");
    postOrder(root);
    printf("\nEnter key:");
    scanf("%d",&key);
    if((search(root,key))==NULL)
    printf("Key not found");
    else
    printf("Key found");

}