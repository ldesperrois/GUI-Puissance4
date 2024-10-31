# Makefile pour compiler un programme utilisant SFML et CSFML

# Compilateur C
CC = gcc

# Drapeaux de compilation
CFLAGS = -I/usr/local/include

# Drapeaux de liaison
LDFLAGS = -L/usr/local/lib -lcsfml-graphics -lcsfml-window -lcsfml-system

# Nom de l'exécutable
TARGET = sfml_window

ARCH = arch -x86_64

# Fichiers sources
SRCS = ./src/main.c \
       ./src/game/game_view.c

# Règle par défaut
all: $(TARGET)

# Règle pour compiler l'exécutable
$(TARGET): $(SRCS)
	$(ARCH) $(CC) -o $(TARGET) $(SRCS) $(CFLAGS) $(LDFLAGS)

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(TARGET)

# Règle pour afficher les cibles disponibles
help:
	@echo "Makefile pour compiler un programme utilisant SFML et CSFML"
	@echo "Cibles disponibles:"
	@echo "  all     - Compile le programme"
	@echo "  clean   - Nettoie les fichiers générés"
	@echo "  help    - Affiche cet
