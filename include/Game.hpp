#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;

    // Jugadores
    sf::RectangleShape player1;
    sf::RectangleShape player2;

    // Diamantes
    sf::CircleShape diamond1;
    sf::CircleShape diamond2;

    // Obstáculos
    sf::RectangleShape lava;
    sf::RectangleShape water;
    sf::RectangleShape mud;

    // Puertas
    sf::RectangleShape door1; // Puerta de Fireboy
    sf::RectangleShape door2; // Puerta de Watergirl

    // Velocidad de movimiento
    float speed;

    // Contadores de diamantes recolectados
    int player1Diamonds;
    int player2Diamonds;
};

#endif // GAME_HPP