all: kmeans run clean

kmeans: main_kmeans.o file_handling.o extraction_donnees.o normalisation.o kmeans_utilitaires.o analyse_cluster.o
	gcc main_kmeans.o file_handling.o extraction_donnees.o normalisation.o kmeans_utilitaires.o analyse_cluster.o -o kmeans -lm

main_kmeans.o : kmeans_src/main_kmeans.c kmeans_include/types_struct.h kmeans_include/file_handling.h kmeans_include/normalisation.h kmeans_include/kmeans_utilitaires.h kmeans_include/analyse_cluster.h
	gcc -c kmeans_src/main_kmeans.c -o main_kmeans.o -Ikmeans_include

file_handling.o : kmeans_src/file_handling.c kmeans_include/file_handling.h
	gcc -Wall -c kmeans_src/file_handling.c -o file_handling.o -Ikmeans_include

extraction_donnees.o : kmeans_src/extraction_donnees.c kmeans_include/extraction_donnees.h
	gcc -Wall -c kmeans_src/extraction_donnees.c -o extraction_donnees.o -Ikmeans_include

normalisation.o : kmeans_src/normalisation.c kmeans_include/normalisation.h kmeans_include/extraction_donnees.h
	gcc -Wall -c kmeans_src/normalisation.c -o normalisation.o -Ikmeans_include

kmeans_utilitaires.o : kmeans_src/kmeans_utilitaires.c kmeans_include/kmeans_utilitaires.h
	gcc -Wall -c kmeans_src/kmeans_utilitaires.c -o kmeans_utilitaires.o -Ikmeans_include

analyse_cluster.o: kmeans_src/analyse_cluster.c kmeans_include/analyse_cluster.h kmeans_include/extraction_donnees.h
	gcc -Wall -c kmeans_src/analyse_cluster.c -o analyse_cluster.o -Ikmeans_include

run:
	./kmeans

clean:
	rm -f *.o kmeans
