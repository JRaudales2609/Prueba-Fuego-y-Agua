#ifndef PAUSEMENU_HPP
#define PAUSEMENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class PauseMenu {
private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;
    int selectedOption;
    
    sf::RectangleShape overlay;
    
    sf::Texture exitButtonTexture;  // NUEVO
    sf::Sprite exitButtonSprite;    // NUEVO
    
public:
    PauseMenu();
    void updatePositions(const sf::Vector2u& windowSize); // NUEVO
    void handleInput(sf::Event& event);
    void update(const sf::Vector2i& mousePos);
    void render(sf::RenderWindow& window);
    int getSelectedOption() const; // 0 = Reanudar, 1 = Reiniciar, 2 = Salir, -1 = ninguno
    void resetSelection();
};

#endif
