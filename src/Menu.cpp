#include "../include/Menu.hpp"
#include <iostream>

Menu::Menu() : selectedButton(-1) {
    std::cout << "=== Inicializando Menu ===" << std::endl;
    
    // Cargar fuente - intentar múltiples ubicaciones
    bool fontLoaded = false;
    
    // Intento 1: Fuente del proyecto
    if (font.loadFromFile("assets/fonts/ThaleahFat.ttf")) {
        std::cout << "✓ Fuente cargada: assets/fonts/ThaleahFat.ttf" << std::endl;
        fontLoaded = true;
    }
    // Intento 2: Arial del sistema
    else if (font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cout << "✓ Fuente cargada: C:/Windows/Fonts/arial.ttf" << std::endl;
        fontLoaded = true;
    }
    // Intento 3: Cualquier fuente común
    else if (font.loadFromFile("C:/Windows/Fonts/calibri.ttf")) {
        std::cout << "✓ Fuente cargada: calibri.ttf" << std::endl;
        fontLoaded = true;
    }
    else {
        std::cerr << "✗ ERROR CRÍTICO: No se pudo cargar ninguna fuente" << std::endl;
        std::cerr << "  Verifica que existe: assets/fonts/ThaleahFat.ttf" << std::endl;
    }
    
    // Cargar fondo
    if (backgroundTexture.loadFromFile("assets/imagenes/niveles/background.png")) {
        std::cout << "✓ Fondo cargado" << std::endl;
        backgroundSprite.setTexture(backgroundTexture);
        sf::Vector2u textureSize = backgroundTexture.getSize();
        float scaleX = 1200.0f / textureSize.x;
        float scaleY = 800.0f / textureSize.y;
        backgroundSprite.setScale(scaleX, scaleY);
    } else {
        std::cerr << "✗ No se pudo cargar el fondo (no crítico)" << std::endl;
    }
    
    if (fontLoaded) {
        // Título del juego
        title.setFont(font);
        title.setString("FUEGO Y AGUA");
        title.setCharacterSize(80);
        title.setFillColor(sf::Color::White);
        title.setOutlineColor(sf::Color(255, 140, 0));
        title.setOutlineThickness(4);
        sf::FloatRect titleBounds = title.getLocalBounds();
        title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
        title.setPosition(600, 200);
        
        // Crear botones
        std::vector<std::string> buttonLabels = {"COMENZAR", "SALIR"};
        float buttonWidth = 300;
        float buttonHeight = 80;
        float startY = 400;
        float spacing = 120;
        
        for (size_t i = 0; i < buttonLabels.size(); i++) {
            // Crear rectángulo del botón
            sf::RectangleShape button(sf::Vector2f(buttonWidth, buttonHeight));
            button.setPosition(450, startY + i * spacing);
            button.setFillColor(sf::Color(50, 50, 50, 200));
            button.setOutlineColor(sf::Color::White);
            button.setOutlineThickness(3);
            buttons.push_back(button);
            
            // Crear texto del botón
            sf::Text text;
            text.setFont(font);
            text.setString(buttonLabels[i]);
            text.setCharacterSize(40);
            text.setFillColor(sf::Color::White);
            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin(textBounds.width / 2, textBounds.height / 2);
            text.setPosition(600, startY + i * spacing + buttonHeight / 2);
            buttonTexts.push_back(text);
        }
        
        std::cout << "✓ Menu inicializado correctamente" << std::endl;
    } else {
        std::cerr << "✗ Menu NO pudo inicializarse correctamente" << std::endl;
    }
}

void Menu::handleInput(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            for (size_t i = 0; i < buttons.size(); i++) {
                if (buttons[i].getGlobalBounds().contains(
                    static_cast<float>(event.mouseButton.x),
                    static_cast<float>(event.mouseButton.y))) {
                    selectedButton = static_cast<int>(i);
                    std::cout << "Botón seleccionado: " << i << std::endl;
                    return;
                }
            }
        }
    }
}

void Menu::update(const sf::Vector2i& mousePos) {
    for (size_t i = 0; i < buttons.size(); i++) {
        if (buttons[i].getGlobalBounds().contains(
            static_cast<float>(mousePos.x),
            static_cast<float>(mousePos.y))) {
            buttons[i].setFillColor(sf::Color(100, 100, 100, 220));
            buttonTexts[i].setFillColor(sf::Color(255, 140, 0));
        } else {
            buttons[i].setFillColor(sf::Color(50, 50, 50, 200));
            buttonTexts[i].setFillColor(sf::Color::White);
        }
    }
}

void Menu::render(sf::RenderWindow& window) {
    // Dibujar fondo
    if (backgroundTexture.getSize().x > 0) {
        window.draw(backgroundSprite);
    } else {
        // Fondo negro si no hay textura
        sf::RectangleShape bg(sf::Vector2f(1200, 800));
        bg.setFillColor(sf::Color(20, 20, 40));
        window.draw(bg);
    }
    
    // Overlay oscuro
    sf::RectangleShape overlay(sf::Vector2f(1200, 800));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlay);
    
    // Dibujar título
    if (title.getFont() != nullptr) {
        window.draw(title);
    }
    
    // Dibujar botones
    for (size_t i = 0; i < buttons.size(); i++) {
        window.draw(buttons[i]);
        if (buttonTexts[i].getFont() != nullptr) {
            window.draw(buttonTexts[i]);
        }
    }
}

int Menu::getSelectedOption() const {
    return selectedButton;
}

void Menu::resetSelection() {
    selectedButton = -1;
}
