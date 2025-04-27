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
		printf("1) filtrar artista\n");
		printf("2) filtrar álbum\n");
		printf("3) filtrar género\n");
		printf("4) filtrar idioma\n");
		printf("5) filtrar año de lanzamiento\n");
		printf("6) filtrar por duracion\n");
		printf("0) buscar musica filtrada\n");
		
		printf("Ingrese numero de filto deseado: ");
		scanf("%d", &FilterType);
		printf("\n");
		
		
		//Si seleccionan un numero no planeado
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
    
    
    
	// Saving the
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
	menu();	
 	
    fclose(file);
    // Mostrar los filtros seleccionados
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
    
    
    return 0;
};