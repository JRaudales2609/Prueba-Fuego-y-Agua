#include "../include/LevelSelector.hpp"
#include <iostream>

LevelSelector::LevelSelector() : selectedLevel(-1) {
    // Cargar fuente
    if (!font.loadFromFile("assets/fonts/ThaleahFat.ttf")) {
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            std::cerr << "Error: No se pudo cargar ninguna fuente" << std::endl;
        }
    }
    
    // Cargar fondo
    if (backgroundTexture.loadFromFile("assets/imagenes/niveles/background.png")) {
        backgroundSprite.setTexture(backgroundTexture);
        sf::Vector2u textureSize = backgroundTexture.getSize();
        float scaleX = 1200.0f / textureSize.x;
        float scaleY = 800.0f / textureSize.y;
        backgroundSprite.setScale(scaleX, scaleY);
    }
    
    // Título
    title.setFont(font);
    title.setString("SELECCIONA UN NIVEL");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color(255, 140, 0));
    title.setOutlineThickness(3);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    title.setPosition(600, 100);
    
    // Crear botones de niveles
    float buttonWidth = 350;
    float buttonHeight = 400;
    float startX = 200;
    float spacing = 500;
    float yPos = 250;
    
    for (int i = 0; i < 2; i++) {
        // Botón del nivel
        sf::RectangleShape button(sf::Vector2f(buttonWidth, buttonHeight));
        button.setPosition(startX + i * spacing, yPos);
        button.setFillColor(sf::Color(50, 50, 50, 200));
        button.setOutlineColor(sf::Color::White);
        button.setOutlineThickness(3);
        levelButtons.push_back(button);
        
        // Texto del nivel
        sf::Text text;
        text.setFont(font);
        text.setString("NIVEL " + std::to_string(i + 1));
        text.setCharacterSize(40);
        text.setFillColor(sf::Color::White);
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.width / 2, textBounds.height / 2);
        text.setPosition(startX + i * spacing + buttonWidth / 2, yPos + buttonHeight - 50);
        levelTexts.push_back(text);
        
        // Cargar preview del nivel (usa el fondo por ahora)
        sf::Texture previewTex;
        if (previewTex.loadFromFile("assets/imagenes/niveles/background.png")) {
            previewTextures.push_back(previewTex);
            
            sf::Sprite preview;
            preview.setTexture(previewTextures[i]);
            
            // Escalar preview para que quepa en el botón
            sf::Vector2u texSize = previewTex.getSize();
            float scale = std::min((buttonWidth - 20) / texSize.x, (buttonHeight - 100) / texSize.y);
            preview.setScale(scale, scale);
            
            // Centrar preview en el botón
            sf::FloatRect previewBounds = preview.getLocalBounds();
            preview.setOrigin(previewBounds.width / 2, previewBounds.height / 2);
            preview.setPosition(
                startX + i * spacing + buttonWidth / 2,
                yPos + (buttonHeight - 100) / 2
            );
            
            levelPreviews.push_back(preview);
        }
    }
    
    std::cout << "LevelSelector inicializado correctamente" << std::endl;
}

void LevelSelector::handleInput(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            for (size_t i = 0; i < levelButtons.size(); i++) {
                if (levelButtons[i].getGlobalBounds().contains(
                    static_cast<float>(event.mouseButton.x),
                    static_cast<float>(event.mouseButton.y))) {
                    selectedLevel = i + 1; // Nivel 1 o Nivel 2
                    std::cout << "Nivel " << selectedLevel << " seleccionado" << std::endl;
                    return;
                }
            }
        }
    }
}

void LevelSelector::update(const sf::Vector2i& mousePos) {
    // Resaltar botón cuando el mouse está encima
    for (size_t i = 0; i < levelButtons.size(); i++) {
        if (levelButtons[i].getGlobalBounds().contains(
            static_cast<float>(mousePos.x),
            static_cast<float>(mousePos.y))) {
            levelButtons[i].setFillColor(sf::Color(100, 100, 100, 220));
            levelButtons[i].setOutlineColor(sf::Color(255, 140, 0));
            levelButtons[i].setOutlineThickness(5);
            levelTexts[i].setFillColor(sf::Color(255, 140, 0));
        } else {
            levelButtons[i].setFillColor(sf::Color(50, 50, 50, 200));
            levelButtons[i].setOutlineColor(sf::Color::White);
            levelButtons[i].setOutlineThickness(3);
            levelTexts[i].setFillColor(sf::Color::White);
        }
    }
}

void LevelSelector::render(sf::RenderWindow& window) {
    // Dibujar fondo
    window.draw(backgroundSprite);
    
    // Overlay oscuro
    sf::RectangleShape overlay(sf::Vector2f(1200, 800));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlay);
    
    // Dibujar título
    window.draw(title);
    
    // Dibujar botones de niveles
    for (size_t i = 0; i < levelButtons.size(); i++) {
        window.draw(levelButtons[i]);
        if (i < levelPreviews.size()) {
            window.draw(levelPreviews[i]);
        }
        window.draw(levelTexts[i]);
    }
}

int LevelSelector::getSelectedLevel() const {
    return selectedLevel;
}

void LevelSelector::resetSelection() {
    selectedLevel = -1;
}
