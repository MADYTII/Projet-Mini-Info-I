all: kmeans run clean

kmeans: main_kmeans.o file_handling.o extraction_donnees.o normalisation.o kmeans_utilitaires.o analyse_cluster.o
	gcc main_kmeans.o file_handling.o extraction_donnees.o normalisation.o kmeans_utilitaires.o analyse_cluster.o -o kmeans -lm

main_kmeans.o : main_kmeans.c types_struct.h file_handling.h normalisation.h kmeans_utilitaires.h analyse_cluster.h
	gcc -c main_kmeans.c -o main_kmeans.o

file_handling.o : file_handling.c file_handling.h
	gcc -Wall -c file_handling.c -o file_handling.o

extraction_donnees.o : extraction_donnees.c extraction_donnees.h
	gcc -Wall -c extraction_donnees.c -o extraction_donnees.o

normalisation.o : normalisation.c normalisation.h extraction_donnees.h
	gcc -Wall -c normalisation.c -o normalisation.o

kmeans_utilitaires.o : kmeans_utilitaires.c kmeans_utilitaires.h
	gcc -Wall -c kmeans_utilitaires.c -o kmeans_utilitaires.o

analyse_cluster.o: analyse_cluster.c analyse_cluster.h extraction_donnees.h
	gcc -Wall -c analyse_cluster.c -o analyse_cluster.o

run:
	./kmeans

clean:
	rm -f *.o kmeans
