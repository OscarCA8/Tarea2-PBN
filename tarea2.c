#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_SONGS 100

typedef struct cancion {
    char song_id[50];
    char song_title[50];
    char artist[50];
    char album[50];
    char genre[50];
    int release_date;
    int duration;
    int popularity;
    int stream;
    char language[50];
    char explicit_content[50];
    char label[50];
    char composer[50];
    char producer[50];
    char collaboration[50];
} cancion;

int main(void)
{
    FILE *file = fopen("songs_bd_small.csv", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    cancion canciones[MAX_SONGS];
    int entries = 0;

    // Skip the header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) && entries < MAX_SONGS) {
        char *token;
        int field = 0;

        token = strtok(line, ",");
        while (token != NULL && field < 15) {
            // Remove newline and carriage return at end
            token[strcspn(token, "\r\n")] = 0;

            switch (field) {
                case 0: strncpy(canciones[entries].song_id, token, 49); break;
                case 1: strncpy(canciones[entries].song_title, token, 49); break;
                case 2: strncpy(canciones[entries].artist, token, 49); break;
                case 3: strncpy(canciones[entries].album, token, 49); break;
                case 4: strncpy(canciones[entries].genre, token, 49); break;
                case 5: canciones[entries].release_date = atoi(token); break;
                case 6: canciones[entries].duration = atoi(token); break;
                case 7: canciones[entries].popularity = atoi(token); break;
                case 8: canciones[entries].stream = atoi(token); break;
                case 9: strncpy(canciones[entries].language, token, 49); break;
                case 10: strncpy(canciones[entries].explicit_content, token, 49); break;
                case 11: strncpy(canciones[entries].label, token, 49); break;
                case 12: strncpy(canciones[entries].composer, token, 49); break;
                case 13: strncpy(canciones[entries].producer, token, 49); break;
                case 14: strncpy(canciones[entries].collaboration, token, 49); break;
            }

            token = strtok(NULL, ",");
            field++;
        }

        if (field == 15) {
            entries++;
        }
    }

    // Print the songs
    for (int i = 0; i < entries; i++) {
        printf("%s | %s | %s | %s | %s | %d | %d | %d | %d | %s | %s | %s | %s | %s | %s\n",
               canciones[i].song_id,
               canciones[i].song_title,
               canciones[i].artist,
               canciones[i].album,
               canciones[i].genre,
               canciones[i].release_date,
               canciones[i].duration,
               canciones[i].popularity,
               canciones[i].stream,
               canciones[i].language,
               canciones[i].explicit_content,
               canciones[i].label,
               canciones[i].composer,
               canciones[i].producer,
               canciones[i].collaboration);
    }

    fclose(file);
    return 0;
}

