# Directorios de origen y destino
SRC_DIR := src
BIN_DIR := bin

SFML := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d

# Archivos fuente
SOURCES := $(SRC_DIR)/game.cpp $(SRC_DIR)/Level.cpp

# Regla principal para compilar el juego
$(BIN_DIR)/game.exe: $(SOURCES)
	@mkdir -p $(BIN_DIR)
	g++ $(SOURCES) -o $@ $(SFML) -Iinclude

# Regla por defecto
all: $(BIN_DIR)/game.exe

# Regla para ejecutar el juego
run: $(BIN_DIR)/game.exe
	./$(BIN_DIR)/game.exe

# Regla para limpiar los archivos generados
clean:
	rm -f $(BIN_DIR)/game.exe

.PHONY: all clean run
