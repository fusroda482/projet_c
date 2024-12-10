# Makefile

# Compilateur C
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -pedantic

# Fichiers source
SRCS = main.c gestion_clavier.c gamemode.c save.c affichage.c game.c material.c 

# Fichiers d'en-tête
INCLUDES = main.h gestion_clavier.h gamemode.h save.h affichage.h game.h material.h

# Règle pour compiler le projet
all: $(SRCS)
	$(CC) $(CFLAGS) -o le_Jeu $(SRCS)

# Règle pour nettoyer les fichiers générés
clean:
	rm -f le_Jeu
