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

    // Texturas
    sf::Texture fireDiamondTexture;
    sf::Texture waterDiamondTexture;
    sf::Texture fireDoorTexture;
    sf::Texture waterDoorTexture;
    sf::Texture fireboyTexture;
    sf::Texture watergirlTexture;
    sf::Texture lavaTexture;
    sf::Texture waterTexture;
    sf::Texture mudTexture;

    // Jugadores (ahora usando sprites)
    sf::Sprite player1;
    sf::Sprite player2;

    // Variables para animación
    int currentFrame1;
    int currentFrame2;
    sf::Clock animationClock;
    float frameTime;
    float baseScale1; // Escala base del jugador 1
    float baseScale2; // Escala base del jugador 2

    // Diamantes (ahora usando sprites)
    sf::Sprite diamond1;
    sf::Sprite diamond2;

    // Obstáculos (ahora usando sprites)
    sf::Sprite lava;
    sf::Sprite water;
    sf::Sprite mud;

    // Hitboxes ajustadas (solo el área del líquido)
    sf::FloatRect lavaHitbox;
    sf::FloatRect waterHitbox;
    sf::FloatRect mudHitbox;

    // Puertas (ahora usando sprites)
    sf::Sprite door1; // Puerta de Fireboy
    sf::Sprite door2; // Puerta de Watergirl

    // Velocidad de movimiento
    float speed;

    // Contadores de diamantes recolectados
    int player1Diamonds;
    int player2Diamonds;

    // Estado de visibilidad de diamantes
    bool diamond1Visible;
    bool diamond2Visible;

    // Funciones auxiliares
    void updateAnimation();
    sf::FloatRect getPlayer1Bounds();
    sf::FloatRect getPlayer2Bounds();
};

#endif // GAME_HPP