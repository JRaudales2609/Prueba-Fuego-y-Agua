#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;
    int selectedButton;
    
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    
public:
    Menu();
    void handleInput(sf::Event& event);
    void update(const sf::Vector2i& mousePos);
    void render(sf::RenderWindow& window);
    int getSelectedOption() const; // 0 = Comenzar, 1 = Salir, -1 = ninguno
    void resetSelection(); // Para resetear la selección
};

#endif
