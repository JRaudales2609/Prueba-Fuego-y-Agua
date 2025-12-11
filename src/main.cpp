#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Game.hpp"
#include "../include/Menu.hpp"
#include "../include/LevelSelector.hpp"
#include "../include/GameState.hpp"

int main() {
    std::cout << "=== Iniciando Fuego y Agua ===" << std::endl;
    
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Fuego y Agua");
    window.setFramerateLimit(60);

    // Estado del juego
    GameState currentState = GameState::MENU_PRINCIPAL;
    Menu menu;
    LevelSelector levelSelector;
    Game* game = nullptr;
    int selectedLevel = 1;

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (currentState == GameState::MENU_PRINCIPAL) {
                menu.handleInput(event);
            } else if (currentState == GameState::SELECTOR_NIVEL) {
                levelSelector.handleInput(event);
            }
        }

        // UPDATE
        if (currentState == GameState::MENU_PRINCIPAL) {
            menu.update(sf::Mouse::getPosition(window));
            
            int selectedOption = menu.getSelectedOption();
            if (selectedOption == 0) { // COMENZAR
                std::cout << ">>> COMENZAR presionado <<<" << std::endl;
                std::cout << ">>> Mostrando selector de niveles... <<<" << std::endl;
                currentState = GameState::SELECTOR_NIVEL;
                menu.resetSelection();
                
            } else if (selectedOption == 1) { // SALIR
                std::cout << ">>> SALIR presionado <<<" << std::endl;
                window.close();
            }
        } 
        else if (currentState == GameState::SELECTOR_NIVEL) {
            levelSelector.update(sf::Mouse::getPosition(window));
            
            selectedLevel = levelSelector.getSelectedLevel();
            if (selectedLevel > 0) { // Si se seleccionó un nivel
                std::cout << ">>> Iniciando nivel " << selectedLevel << " <<<" << std::endl;
                window.close(); // Cerrar ventana del menú
                
                // Crear y ejecutar el juego con el nivel seleccionado
                game = new Game(selectedLevel);
                game->run();
                
                // Cuando el juego termina, volver al menú principal
                delete game;
                game = nullptr;
                
                // Reabrir ventana para el menú
                window.create(sf::VideoMode(1200, 800), "Fuego y Agua");
                window.setFramerateLimit(60);
                currentState = GameState::MENU_PRINCIPAL;
                levelSelector.resetSelection();
            }
        }

        // RENDER
        if (window.isOpen()) {
            window.clear(sf::Color::Black);
            
            if (currentState == GameState::MENU_PRINCIPAL) {
                menu.render(window);
            } else if (currentState == GameState::SELECTOR_NIVEL) {
                levelSelector.render(window);
            }
            
            window.display();
        }
    }

    if (game != nullptr) {
        delete game;
    }

    std::cout << "Juego cerrado correctamente" << std::endl;
    return 0;
}
