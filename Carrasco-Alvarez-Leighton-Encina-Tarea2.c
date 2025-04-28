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


char FilterArtist[50] = "";
char FilterAlbum[50] = "";
char FilterGender[50] = "";
char FilterLenguage[50] = "";
int FilterMinYear = 0;
int FilterMaxYear = 0;
int FilterMinTime = 0;
int FilterMaxTime = 0;


void menu(){
	int FilterType = 1;
	
	while (FilterType != 0) {
		printf("1) filtrar por artista\n");
		printf("2) filtrar por álbum\n");
		printf("3) filtrar por género\n");
		printf("4) filtrar por idioma\n");
		printf("5) filtrar por año de lanzamiento\n");
		printf("6) filtrar por duracion\n");
		printf("0) buscar musica filtrada\n");
		
		printf("Ingrese numero de filtro deseado: ");
		scanf("%d", &FilterType);
		printf("\n");
		
		while (FilterType > 6 || FilterType < 0){
			printf("seleccione un numero valido: ");
			scanf("%d",&FilterType);
			printf("\n");
		};
		
		if (FilterType == 1){
		printf("Ingrese nombre de artista: ");
		scanf("%s",FilterArtist);
		printf("\n"); 
		};
		
		if (FilterType == 2){
		printf("Ingrese nombre de álbum: ");
		scanf("%s",FilterAlbum);
		printf("\n"); 
		};
		
		if (FilterType == 3){
		printf("Ingrese género musical: ");
		scanf("%s",FilterGender);
		printf("\n"); 
		};
		
		if (FilterType == 4){
		printf("Ingrese idioma: ");
		scanf("%s",FilterLenguage);
		printf("\n"); 
		};
		
		if (FilterType == 5){
		printf("Ingrese año minimo: ");
		scanf("%d",&FilterMinYear);
		printf("\n");
		printf("Ingrese año maximo: ");
		scanf("%d",&FilterMaxYear);
		printf("\n");  
		};
		
		if (FilterType == 6){
		printf("Ingrese duracion minima: ");
		scanf("%d",&FilterMinTime);
		printf("\n");
		printf("Ingrese duracion maxima: ");
		scanf("%d",&FilterMaxTime);
		printf("\n");  
		};
		
		if (FilterType == 0){
		printf("generando archivo txt\n");
		};
	};
};

int verificar_filtros(cancion c) {
    if (strlen(FilterArtist) > 0 && strcmp(c.artist, FilterArtist) != 0) return 0;
    if (strlen(FilterAlbum) > 0 && strcmp(c.album, FilterAlbum) != 0) return 0;
    if (strlen(FilterGender) > 0 && strcmp(c.genre, FilterGender) != 0) return 0;
    if (strlen(FilterLenguage) > 0 && strcmp(c.language, FilterLenguage) != 0) return 0;
    if (FilterMinYear > 0 && c.release_date < FilterMinYear) return 0;
    if (FilterMaxYear > 0 && c.release_date > FilterMaxYear) return 0;
    if (FilterMinTime > 0 && c.duration < FilterMinTime) return 0;
    if (FilterMaxTime > 0 && c.duration > FilterMaxTime) return 0;
    return 1;
}

void exportar_lista(cancion *lista, int cantidad) {
    char nombre_archivo[256];
    printf("Nombre del archivo de salida (nombre.txt): ");
    scanf("%s", nombre_archivo);

    FILE *archivo = fopen(nombre_archivo, "w");
    if (!archivo) {
        perror("No se pudo crear el archivo");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%s: %s - %s (%d) -- %s\n",
                lista[i].song_id,
                lista[i].artist,
                lista[i].song_title,
                lista[i].release_date,
                lista[i].genre);
    }

    fclose(archivo);
    printf("Archivo exportado correctamente. ¡Gracias por usar el programa! c:");
}

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

    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) && entries < MAX_SONGS) {
        char *token;
        int field = 0;

        token = strtok(line, ",");
        while (token != NULL && field < 15) {
            token[strcspn(token, "\r\n")] = 0;

            switch (field) {
                case 0: strncpy(canciones[entries].song_id, token, 49); break;
                case 1: strncpy(canciones[entries].song_title, token, 49); break;
                case 2: strncpy(canciones[entries].artist, token, 49); break;
                case 3: strncpy(canciones[entries].album, token, 49); break;
                case 4: strncpy(canciones[entries].genre, token, 49); break;
                case 5: {
                    char year[5];
                    strncpy(year, token, 4);
                    year[4] = '\0';
                    canciones[entries].release_date = atoi(year);
                    break;
                }
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
	menu();	
 	
    fclose(file);

    printf("\n======= FILTROS APLICADOS =======\n");
    printf("Artista: %s\n", FilterArtist);
    printf("Álbum: %s\n", FilterAlbum);
    printf("Género: %s\n", FilterGender);
    printf("Idioma: %s\n", FilterLenguage);
    printf("Año mínimo: %d\n", FilterMinYear);
    printf("Año máximo: %d\n", FilterMaxYear);
    printf("Duración mínima: %d segundos\n", FilterMinTime);
    printf("Duración máxima: %d segundos\n", FilterMaxTime);
    printf("=================================\n");
    
    cancion canciones_filtradas[MAX_SONGS];
    int cantidad_filtradas = 0;

    for (int i = 0; i < entries; i++) {
        if (verificar_filtros(canciones[i])) {
            canciones_filtradas[cantidad_filtradas++] = canciones[i];
        }
    }

    printf("\n=== %d canciones encontradas ===.\n", cantidad_filtradas);

    exportar_lista(canciones_filtradas, cantidad_filtradas);

    return 0;
};