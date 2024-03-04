CC=gcc
CFLAGS=-O3 -g

# Les cibles à construire
TARGET=test mandel

all: $(TARGET)

# Création de la bibliothèque partagée libppm.so à partir du fichier ppm.c
libppm.so : ppm.c
	$(CC) $(CFLAGS) -fpic -shared $^ -o $@

# Construction du programme test à partir de main.c et de la bibliothèque libppm.so
test: main.c libppm.so
	$(CC) $(CFLAGS) $(LDFLAGS) main.c -lppm -L. -o $@

# Construction du programme mandel à partir de mandel.c et de la bibliothèque libppm.so
mandel: mandel.c libppm.so
	$(CC) $(CFLAGS) $(LDFLAGS) $< -lppm -lm -L. -o $@

# Nettoyage des fichiers générés lors de la compilation
clean:
	rm -fr $(TARGET) *.so
