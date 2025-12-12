#include "../include/PauseMenu.hpp"
#include <iostream>

PauseMenu::PauseMenu() : selectedOption(-1) {
    // Cargar fuente
    if (!font.loadFromFile("assets/fonts/ThaleahFat.ttf")) {
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            std::cerr << "Error: No se pudo cargar ninguna fuente" << std::endl;
        }
    }
    
    // Overlay oscuro semi-transparente
    overlay.setSize(sf::Vector2f(1200, 800));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    
    // Título
    title.setFont(font);
    title.setString("PAUSA");
    title.setCharacterSize(70);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color(255, 140, 0));
    title.setOutlineThickness(4);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    title.setPosition(600, 200);
    
    // Cargar textura del botón de salir
    if (exitButtonTexture.loadFromFile("assets/imagenes/ui/exit_button.png")) {
        std::cout << "✓ Textura del botón de salir cargada (PauseMenu)" << std::endl;
        exitButtonSprite.setTexture(exitButtonTexture);
    }
    
    // Crear botones
    std::vector<std::string> buttonLabels = {"REANUDAR", "REINICIAR", "SALIR"};
    float buttonWidth = 300;
    float buttonHeight = 70;
    float startY = 350;
    float spacing = 100;
    
    for (size_t i = 0; i < buttonLabels.size(); i++) {
        // Botón
        sf::RectangleShape button(sf::Vector2f(buttonWidth, buttonHeight));
        button.setPosition(450, startY + i * spacing);
        button.setFillColor(sf::Color(50, 50, 50, 220));
        button.setOutlineColor(sf::Color::White);
        button.setOutlineThickness(3);
        buttons.push_back(button);
        
        // Texto
        sf::Text text;
        text.setFont(font);
        text.setString(buttonLabels[i]);
        text.setCharacterSize(35);
        text.setFillColor(sf::Color::White);
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.width / 2, textBounds.height / 2);
        text.setPosition(600, startY + i * spacing + buttonHeight / 2);
        buttonTexts.push_back(text);
    }
}

void PauseMenu::handleInput(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            for (size_t i = 0; i < buttons.size(); i++) {
                if (buttons[i].getGlobalBounds().contains(
                    static_cast<float>(event.mouseButton.x),
                    static_cast<float>(event.mouseButton.y))) {
                    selectedOption = static_cast<int>(i);
                    std::cout << "Opción de pausa seleccionada: " << i << std::endl;
                    return;
                }
            }
        }
    }
}

void PauseMenu::update(const sf::Vector2i& mousePos) {
    for (size_t i = 0; i < buttons.size(); i++) {
        if (buttons[i].getGlobalBounds().contains(
            static_cast<float>(mousePos.x),
            static_cast<float>(mousePos.y))) {
            buttons[i].setFillColor(sf::Color(100, 100, 100, 240));
            buttonTexts[i].setFillColor(sf::Color(255, 140, 0));
        } else {
            buttons[i].setFillColor(sf::Color(50, 50, 50, 220));
            buttonTexts[i].setFillColor(sf::Color::White);
        }
    }
}

void PauseMenu::updatePositions(const sf::Vector2u& windowSize) {
    float centerX = windowSize.x / 2.0f;
    float buttonWidth = 300;
    float buttonHeight = 70;
    float startY = windowSize.y * 0.45f;
    float spacing = 100;
    
    // Actualizar overlay
    overlay.setSize(sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));
    
    // Actualizar título
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    title.setPosition(centerX, windowSize.y * 0.3f);
    
    // Actualizar botones
    for (size_t i = 0; i < buttons.size(); i++) {
        buttons[i].setPosition(centerX - buttonWidth / 2, startY + i * spacing);
        
        sf::FloatRect textBounds = buttonTexts[i].getLocalBounds();
        buttonTexts[i].setOrigin(textBounds.width / 2, textBounds.height / 2);
        buttonTexts[i].setPosition(centerX, startY + i * spacing + buttonHeight / 2);
    }
    
    // Actualizar sprite del botón de salir (botón 2 = SALIR)
    if (exitButtonTexture.getSize().x > 0) {
        // Escalar para que quepa en el botón
        float scale = std::min(buttonWidth / exitButtonTexture.getSize().x, 
                               buttonHeight / exitButtonTexture.getSize().y);
        exitButtonSprite.setScale(scale, scale);
        
        // Centrar en el botón de SALIR
        sf::FloatRect spriteBounds = exitButtonSprite.getGlobalBounds();
        float centerX = windowSize.x / 2.0f;
        exitButtonSprite.setPosition(
            centerX - spriteBounds.width / 2,
            startY + 2 * spacing + (buttonHeight - spriteBounds.height) / 2
        );
    }
}

void PauseMenu::render(sf::RenderWindow& window) {
    window.draw(overlay);
    window.draw(title);
    
    for (size_t i = 0; i < buttons.size(); i++) {
        window.draw(buttons[i]);
        
        // Si es el botón de SALIR y hay textura, dibujarla
        if (i == 2 && exitButtonTexture.getSize().x > 0) {
            window.draw(exitButtonSprite);
        }
        
        window.draw(buttonTexts[i]);
    }
}

int PauseMenu::getSelectedOption() const {
    return selectedOption;
}

void PauseMenu::resetSelection() {
    selectedOption = -1;
}
