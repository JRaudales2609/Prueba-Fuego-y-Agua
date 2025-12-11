#include "../include/Level.hpp"
#include <iostream>

Level::Level(int levelNumber) : levelNumber(levelNumber) {
    loadLevel();
}

void Level::loadLevel() {
    // Cargar imagen de fondo decorativa
    std::string backgroundPath = "assets/imagenes/niveles/background.png";
    
    if (!backgroundTexture.loadFromFile(backgroundPath)) {
        std::cerr << "Advertencia: No se pudo cargar fondo decorativo, usando color sólido" << std::endl;
    } else {
        backgroundSprite.setTexture(backgroundTexture);
        
        // Escalar la imagen para que cubra toda la ventana (1200x800)
        sf::Vector2u textureSize = backgroundTexture.getSize();
        float scaleX = 1200.0f / textureSize.x;
        float scaleY = 800.0f / textureSize.y;
        backgroundSprite.setScale(scaleX, scaleY);
    }
    
    // Cargar texturas de bloques
    if (!borderBlockTexture.loadFromFile("assets/imagenes/bloques/border_block.png")) {
        std::cerr << "Error: No se pudo cargar border_block.png" << std::endl;
    } else {
        std::cout << "Textura de bloque de borde cargada" << std::endl;
    }
    
    if (!platformBlockTexture.loadFromFile("assets/imagenes/bloques/platform_block.png")) {
        std::cerr << "Error: No se pudo cargar platform_block.png" << std::endl;
    } else {
        std::cout << "Textura de bloque de plataforma cargada" << std::endl;
    }
    
    // Configurar datos específicos del nivel
    switch(levelNumber) {
        case 1:
            setupLevel1();
            break;
        case 2:
            setupLevel2();
            break;
        case 3:
            setupLevel3();
            break;
        default:
            setupLevel1();
            break;
    }
}

void Level::setupLevel1() {
    // Limpiar bloques anteriores
    blocks.clear();
    
    // Crear bordes del nivel (paredes y suelo)
    // Suelo (24 bloques de 50px = 1200px de ancho)
    for(int x = 0; x < 24; x++) {
        addBlock("border", x * blockSize, 750);
    }
    
    // Pared izquierda (16 bloques de 50px = 800px de alto) - rotados 90°
    for(int y = 0; y < 15; y++) {
        addBlock("border", 0, y * blockSize, 90.0f);
    }
    
    // Pared derecha - rotados 90°
    for(int y = 0; y < 15; y++) {
        addBlock("border", 1150, y * blockSize, 90.0f);
    }
    
    // Plataformas internas (ejemplo: plataforma horizontal)
    for(int x = 4; x < 8; x++) {
        addBlock("platform", x * blockSize, 600);
    }
    
    // Otra plataforma
    for(int x = 14; x < 18; x++) {
        addBlock("platform", x * blockSize, 500);
    }
    
    // Plataforma vertical (escalera/torre)
    for(int y = 10; y < 14; y++) {
        addBlock("platform", 600, y * blockSize);
    }
    
    // Posiciones iniciales de jugadores
    player1Start = sf::Vector2f(100.0f, 650.0f);
    player2Start = sf::Vector2f(1050.0f, 650.0f);
    
    // Posiciones de diamantes
    diamond1Pos = sf::Vector2f(250.0f, 550.0f);
    diamond2Pos = sf::Vector2f(850.0f, 450.0f);
    
    // Posiciones de puertas
    door1Pos = sf::Vector2f(100.0f, 650.0f);
    door2Pos = sf::Vector2f(1000.0f, 650.0f);
    
    // Obstáculos (ejemplo)
    lavaPositions.push_back(sf::Vector2f(400.0f, 700.0f));
    waterPositions.push_back(sf::Vector2f(700.0f, 700.0f));
    mudPositions.push_back(sf::Vector2f(550.0f, 700.0f));
}

void Level::setupLevel2() {
    // Configurar nivel 2 (por ahora similar al 1)
    player1Start = sf::Vector2f(100.0f, 350.0f);
    player2Start = sf::Vector2f(1050.0f, 350.0f);
    
    diamond1Pos = sf::Vector2f(400.0f, 300.0f);
    diamond2Pos = sf::Vector2f(800.0f, 300.0f);
    
    door1Pos = sf::Vector2f(50.0f, 100.0f);
    door2Pos = sf::Vector2f(1070.0f, 100.0f);
    
    platforms.push_back(sf::FloatRect(0.0f, 750.0f, 1200.0f, 50.0f));
    
    lavaPositions.push_back(sf::Vector2f(400.0f, 650.0f));
    waterPositions.push_back(sf::Vector2f(600.0f, 650.0f));
}

void Level::setupLevel3() {
    // Configurar nivel 3
    player1Start = sf::Vector2f(50.0f, 300.0f);
    player2Start = sf::Vector2f(1100.0f, 300.0f);
    
    diamond1Pos = sf::Vector2f(600.0f, 200.0f);
    diamond2Pos = sf::Vector2f(650.0f, 200.0f);
    
    door1Pos = sf::Vector2f(100.0f, 700.0f);
    door2Pos = sf::Vector2f(1000.0f, 700.0f);
    
    platforms.push_back(sf::FloatRect(0.0f, 750.0f, 1200.0f, 50.0f));
}

void Level::addBlock(const std::string& type, float x, float y, float rotation) {
    Block block;
    block.type = type;
    
    // Asignar textura según el tipo
    if (type == "border") {
        block.sprite.setTexture(borderBlockTexture);
    } else if (type == "platform") {
        block.sprite.setTexture(platformBlockTexture);
    }
    
    block.sprite.setPosition(x, y);
    
    // Escalar sprite al tamaño del bloque (50x50)
    sf::Vector2u texSize = block.sprite.getTexture()->getSize();
    float scaleX = blockSize / texSize.x;
    float scaleY = blockSize / texSize.y;
    block.sprite.setScale(scaleX, scaleY);
    
    // Aplicar rotación si se especifica
    if (rotation != 0.0f) {
        block.sprite.setOrigin(blockSize / 2.0f, blockSize / 2.0f);
        block.sprite.setPosition(x + blockSize / 2.0f, y + blockSize / 2.0f);
        block.sprite.setRotation(rotation);
    }
    
    // Crear hitbox del bloque
    block.hitbox = sf::FloatRect(x, y, blockSize, blockSize);
    
    // Añadir a la lista de bloques
    blocks.push_back(block);
    
    // También agregar a platforms para compatibilidad con colisiones existentes
    platforms.push_back(block.hitbox);
}

void Level::render(sf::RenderWindow& window) {
    // Dibujar fondo decorativo
    window.draw(backgroundSprite);
    
    // Dibujar todos los bloques
    for (const auto& block : blocks) {
        window.draw(block.sprite);
    }
}

// Getters
sf::Vector2f Level::getPlayer1StartPos() const { return player1Start; }
sf::Vector2f Level::getPlayer2StartPos() const { return player2Start; }
sf::Vector2f Level::getDiamond1Pos() const { return diamond1Pos; }
sf::Vector2f Level::getDiamond2Pos() const { return diamond2Pos; }
sf::Vector2f Level::getDoor1Pos() const { return door1Pos; }
sf::Vector2f Level::getDoor2Pos() const { return door2Pos; }

std::vector<sf::FloatRect> Level::getPlatforms() const { return platforms; }
std::vector<sf::ConvexShape> Level::getTriangles() const { return triangles; }
std::vector<sf::Vector2f> Level::getLavaPositions() const { return lavaPositions; }
std::vector<sf::Vector2f> Level::getWaterPositions() const { return waterPositions; }
std::vector<sf::Vector2f> Level::getMudPositions() const { return mudPositions; }
