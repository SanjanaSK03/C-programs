#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct song
{
    char title[100];
    char artist[100];
    struct song *next;
};

void addSong(struct song **head, char songTitle[], char artist[]);
void displayPlaylist(struct song *head, FILE *output);
void removeSong(struct song **head, char songTitle[], FILE *output);
int countSongs(struct song *head);
void clearPlaylist(struct song **head);

void addSong(struct song **head, char songTitle[], char artist[])
{
    struct song *newSong = (struct song *)malloc(sizeof(struct song));
    if (newSong == NULL)
    {
        perror("Error");
        exit(1);
    }
    strcpy(newSong->title, songTitle);
    strcpy(newSong->artist, artist);
    newSong->next = NULL;

    if (*head == NULL)
    {
        *head = newSong;
    }
    else
    {
        struct song *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newSong;
    }
}

void displayPlaylist(struct song *head, FILE *output)
{
    struct song *current = head;
    while (current != NULL)
    {
        fprintf(output, "Title: %s\n", current->title);
        fprintf(output, "Artist: %s\n", current->artist);
        fprintf(output, "\n");
        current = current->next;
    }
}

void removeSong(struct song **head, char songTitle[], FILE *output)
{
    if (*head == NULL)
    {
        fprintf(output, "Playlist is empty.\n");
        return;
    }

    struct song *current = *head;
    struct song *prev = NULL;

    while (current != NULL && strcmp(current->title, songTitle) != 0)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        fprintf(output, "Song not found.\n");
        return;
    }

    if (prev == NULL)
    {
        *head = current->next;
    }
    else
    {
        prev->next = current->next;
    }

    fprintf(output, "Song removed:\n");
    fprintf(output, "Title: %s\n", current->title);
    fprintf(output, "Artist: %s\n", current->artist);
    free(current);
}

int countSongs(struct song *head)
{
    int count = 0;
    struct song *current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

void clearPlaylist(struct song **head)
{
    struct song *current = *head;
    struct song *next;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

int main()
{
    struct song *playlist = NULL;
    FILE *input, *output;
    input = fopen("input.txt", "r");
    if (input == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    output = fopen("output.txt", "w");
    if (output == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    char songTitle[100], artist[100], x[20];
    while (fscanf(input, "%s", x) != EOF)
    {
        if (!strcmp(x, "delete"))
        {
            
            fscanf(input, "%[^\n]",songTitle);
            printf("Deleting song: %s\n", songTitle);
            removeSong(&playlist, songTitle, output);
        }

        else if (!strcmp(x, "display"))
        {
            fprintf(output, "Playlist:\n");
            displayPlaylist(playlist, output);
        }
        else if (!strcmp(x, "add"))
        {
            fscanf(input, "%[^,],", songTitle);  
            fscanf(input, " %[^\n]", artist);  
            addSong(&playlist, songTitle, artist);
        }
        else if (!strcmp(x, "count"))
        {
            int count = countSongs(playlist);
            fprintf(output, "Total songs in playlist: %d\n", count);
        }
        else if (!strcmp(x, "clear"))
        {
            clearPlaylist(&playlist);
            fprintf(output, "Playlist cleared.\n");
        }
    }
    fclose(output);
    return 0;
}
