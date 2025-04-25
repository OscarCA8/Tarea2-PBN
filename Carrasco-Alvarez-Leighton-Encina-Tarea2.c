#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct cancion {
    char*song_id;
    char*song_title;
    char*artist;
    char*album;
    char*genre;
    int*release_date;
    int*duration;
    int*popularity;
    int*stream;
    char*language;
    char*explicit_content;
    char*label;
    char*composer;
    char*producer;
    char*collaboration;
} cancion;

void exportar_lista(Cancion *lista, int cantidad) {
    char nombre_archivo[256];
    printf("Nombre del archivo de salida (ej: lista.txt): ");
    scanf("%s", nombre_archivo);

    FILE *archivo = fopen(nombre_archivo, "w");
    if (!archivo) {
        perror("No se pudo crear el archivo");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%s: %s - %s (%d) -- %s",
                lista[i].song_id,
                lista[i].artist,
                lista[i].song_title,
                lista[i].release_year,
                lista[i].genre);
    }

    fclose(archivo);
    printf("Archivo exportado correctamente.");
}