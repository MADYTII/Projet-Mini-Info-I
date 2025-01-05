
all: perceptron run clean

perceptron: main_perceptron.o perceptron_utilitaires.o normalisation.o echantillonnage.o extraction_donnees.o lecture_fichier.o 
	gcc main_perceptron.o perceptron_utilitaires.o normalisation.o echantillonnage.o extraction_donnees.o lecture_fichier.o -o perceptron

main_perceptron.o: perceptron_src/main_perceptron.c perceptron_include/perceptron_utilitaires.h perceptron_include/normalisation.h perceptron_include/echantillonnage.h perceptron_include/extraction_donnees.h perceptron_include/lecture_fichier.h perceptron_include/types_struct.h
	gcc  -c perceptron_src/main_perceptron.c -o main_perceptron.o -Iperceptron_include

lecture_fichier.o: perceptron_src/lecture_fichier.c perceptron_include/lecture_fichier.h
	gcc -Wall -c perceptron_src/lecture_fichier.c -o lecture_fichier.o -Iperceptron_include

extraction_donnees.o: perceptron_src/extraction_donnees.c perceptron_include/extraction_donnees.h
	gcc -Wall -c perceptron_src/extraction_donnees.c -o extraction_donnees.o -Iperceptron_include

echantillonnage.o: perceptron_src/echantillonnage.c perceptron_include/echantillonnage.h
	gcc -Wall -c  perceptron_src/echantillonnage.c -o echantillonnage.o -Iperceptron_include

normalisation.o: perceptron_src/normalisation.c perceptron_include/normalisation.h perceptron_include/extraction_donnees.h
	gcc -Wall -c perceptron_src/normalisation.c -o normalisation.o -Iperceptron_include

perceptron_utilitaires.o: perceptron_src/perceptron_utilitaires.c perceptron_include/perceptron_utilitaires.h perceptron_include/extraction_donnees.h
	gcc -Wall -c perceptron_src/perceptron_utilitaires.c -o perceptron_utilitaires.o -Iperceptron_include



run:
	./perceptron

clean:
	rm -f *.o perceptron

