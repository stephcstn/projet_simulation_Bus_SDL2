# Chemins
CC = gcc
SRC_DIR = src
OBJ_DIR = obj/Debug
BIN_DIR = bin/Debug
INC_DIR = include
SDL_DIR = SDL2/x86_64-w64-mingw32

# Options de compilation
CFLAGS = -I$(INC_DIR) -I$(SDL_DIR)/include/SDL2 -Wno-incompatible-pointer-types -fpermissive
LDFLAGS = -L$(SDL_DIR)/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lm -mconsole

# Fichiers
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
EXEC = $(BIN_DIR)/projetBus.exe

# Règle principale
all: $(OBJ_DIR) $(BIN_DIR) $(EXEC)

# Création des dossiers (Compatible Windows)
$(OBJ_DIR):
	@if not exist "obj" mkdir "obj"
	@if not exist "obj\Debug" mkdir "obj\Debug"

$(BIN_DIR):
	@if not exist "bin" mkdir "bin"
	@if not exist "bin\Debug" mkdir "bin\Debug"

# Création de l'exécutable dans bin/Debug
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Compilation des fichiers .o dans obj/Debug
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Nettoyage complet
clean:
	@if exist obj rmdir /s /q obj
	@if exist bin rmdir /s /q bin

.PHONY: all clean