#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 2048
#define MAX_SONGS 10000

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

int es_artista_unico(char artista[50], char lista[][50], int total) {
    for (int i = 0; i < total; i++) {
        if (strcmp(artista, lista[i]) == 0) return 0;
    }
    return 1;
}

int es_album_unico(char album[50], char lista[][50], int total) {
    for (int i = 0; i < total; i++) {
        if (strcmp(album, lista[i]) == 0) return 0;
    }
    return 1;
}

int es_genero_unico(char genre[50], char lista[][50], int total) {
    for (int i = 0; i < total; i++) {
        if (strcmp(genre, lista[i]) == 0) return 0;
    }
    return 1;
}

int es_idioma_unico(char lenguage[50], char lista[][50], int total) {
    for (int i = 0; i < total; i++) {
        if (strcmp(lenguage, lista[i]) == 0) return 0;
    }
    return 1;
}


void mostrar_artistas_unicos(cancion *canciones, int total_canciones) {
    char artistas[100][50];
    int total_unicos = 0;

    for (int i = 0; i < total_canciones && total_unicos < 100; i++) {
        if (es_artista_unico(canciones[i].artist, artistas, total_unicos)) {
            strncpy(artistas[total_unicos], canciones[i].artist, 49);
            total_unicos++;
        }
    }

    printf("\nMostrando hasta 100 artistas únicos:\n\n");
    for (int i = 0; i < total_unicos; i++) {
        printf("%s\n", artistas[i]);
    }
    printf("\n");
}

void mostrar_albums_unicos(cancion *canciones, int total_canciones) {
    char album[100][50];
    int total_unicos = 0;

    for (int i = 0; i < total_canciones && total_unicos < 100; i++) {
        if (es_genero_unico(canciones[i].album, album, total_unicos)) {
            strncpy(album[total_unicos], canciones[i].album, 49);
            total_unicos++;
        }
    }

    printf("\nMostrando hasta 100 album únicos:\n\n");
    for (int i = 0; i < total_unicos; i++) {
        printf("%s\n", album[i]);
    }
    printf("\n");
}

void mostrar_generos_unicos(cancion *canciones, int total_canciones) {
    char genre[100][50];
    int total_unicos = 0;

    for (int i = 0; i < total_canciones && total_unicos < 100; i++) {
        if (es_genero_unico(canciones[i].genre, genre, total_unicos)) {
            strncpy(genre[total_unicos], canciones[i].genre, 49);
            total_unicos++;
        }
    }

    printf("\nMostrando generos:\n\n");
    for (int i = 0; i < total_unicos; i++) {
        printf("%s\n", genre[i]);
    }
    printf("\n");
}

void mostrar_idioma_unicos(cancion *canciones, int total_canciones) {
    char language[100][50];
    int total_unicos = 0;

    for (int i = 0; i < total_canciones && total_unicos < 100; i++) {
        if (es_idioma_unico(canciones[i].language, language, total_unicos)) {
            strncpy(language[total_unicos], canciones[i].language, 49);
            total_unicos++;
        }
    }

    printf("\nMostrando idiomas:\n\n");
    for (int i = 0; i < total_unicos; i++) {
        printf("%s\n", language[i]);
    }
    printf("\n");
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

void FilterMenu(cancion *canciones, int total_canciones){
	int FilterType = 1;
	
	while (FilterType != 0) {
		printf("1) filtrar por artista\n");
		printf("2) filtrar por álbum\n");
		printf("3) filtrar por género\n");
		printf("4) filtrar por idioma\n");
		printf("5) filtrar por año de lanzamiento\n");
		printf("6) filtrar por duracion\n");
		printf("0) terminar de filtrar\n");
		
		printf("Ingrese numero de filtro deseado: ");
		scanf("%d", &FilterType);
		printf("\n-----------------------------------\n");

		
		while (FilterType > 7 || FilterType < 0){
			printf("seleccione un numero valido: ");
			scanf("%d",&FilterType);
			printf("\n-----------------------------------\n");
		};
		
		if (FilterType == 1){
		mostrar_artistas_unicos(canciones, total_canciones);
		printf("Ingrese nombre de artista: ");
		scanf("\n");
		scanf("%[^\n]", FilterArtist);
		printf("\n"); 
		};
		
		if (FilterType == 2){
		mostrar_albums_unicos(canciones, total_canciones);
		printf("Ingrese nombre de álbum: ");
		scanf("\n");
		scanf("%[^\n]",FilterAlbum);
		printf("\n"); 
		};
		
		if (FilterType == 3){
		mostrar_generos_unicos(canciones, total_canciones);
		printf("Ingrese género musical: ");
		scanf("\n");
		scanf("%[^\n]",FilterGender);
		printf("\n"); 
		};
		
		if (FilterType == 4){
		mostrar_idioma_unicos(canciones, total_canciones);
		printf("Ingrese idioma: ");
		scanf("\n");
		scanf("%[^\n]",FilterLenguage);
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
		printf("-----------------------------------\n");
		
	};
};
	
void ver_primeras_canciones(cancion *lista, int cantidad) {
    int limite = (cantidad < 100) ? cantidad : 100;
    printf("\nMostrando primeras %d canciones:\n\n", limite);
    for (int i = 0; i < limite; i++) {
        printf("%s: %s - %s (%d) -- %s\n",
               lista[i].song_id,
               lista[i].artist,
               lista[i].song_title,
               lista[i].release_date,
               lista[i].genre);
    }
}
	
int main(void) 
{
	char nombre_archivo[100];
	printf("¿Qué archivo desea usar? (1 = small, 2 = big): ");
	int opcion_archivo = 0;
	scanf("%d", &opcion_archivo);
	if(opcion_archivo == 1){
	strcpy(nombre_archivo, "songs_bd_small.csv");
    	} else {
        strcpy(nombre_archivo, "songs_bd_big.csv");
        }
	FILE *file = fopen(nombre_archivo, "r");
	if (file == NULL) {
	perror("Error opening file");
	return 1;
	}

	char line[MAX_LINE_LENGTH];


	cancion *canciones = malloc(sizeof(cancion) * MAX_SONGS);
	cancion *canciones_filtradas = malloc(sizeof(cancion) * MAX_SONGS);


	if (!canciones || !canciones_filtradas) {
	fprintf(stderr, "Error: No se pudo asignar memoria.\n");
	fclose(file);
	return 1;}

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


	fclose(file);

	FilterMenu(canciones, entries);	




	int cantidad_filtradas = 0;

	for (int i = 0; i < entries; i++) {
	if (verificar_filtros(canciones[i])) {
	    canciones_filtradas[cantidad_filtradas++] = canciones[i];
	}}
	

	printf("\n=== %d canciones encontradas ===.\n", cantidad_filtradas);



	int OutputType = 1;

	while (OutputType!=3) {
		printf("1) Visualizar primeras canciones\n");
		printf("2) Exportar la lista a un archivo de texto\n");
		printf("3) Terminar programa\n");
		
		printf("Ingrese numero de accion deseada: ");
		scanf("%d",&OutputType);
		printf("\n-----------------------------------\n");
		
		while (OutputType > 3 || OutputType < 1){
				printf("seleccione un numero valido: ");
				scanf("%d",&OutputType);
				printf("\n-----------------------------------\n");
		};
		
		if (OutputType == 1){
		printf("mostrando canciones");
		ver_primeras_canciones(canciones_filtradas, cantidad_filtradas);

		};
		
		if (OutputType == 2){
		printf("Exportando archivo...\n");
		exportar_lista(canciones_filtradas, cantidad_filtradas);
		};
		printf("\n-----------------------------------\n");
		
		if (OutputType == 3){
		printf("El programa ha finalizado... Muchas gracias por usar el programa c:\n");
		
		};
	};


	free(canciones);
	free(canciones_filtradas);

	return 0;
	};
