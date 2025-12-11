#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Level.hpp"
#include "Menu.hpp"
#include "GameState.hpp"

class Game {
public:
    Game(int startingLevel = 1); // Aceptar nivel inicial
    void run();

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;

    // Estados del juego
    GameState currentState;
    Menu menu;
    bool gameInitialized;

    // Sistema de niveles
    Level currentLevel;

    // Texto para mostrar coordenadas del mouse (temporal para desarrollo)
    sf::Font font;
    sf::Text mouseCoordText;

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

    // Puertas (ahora usando sprites)
    sf::Sprite door1; // Puerta de Fireboy
    sf::Sprite door2; // Puerta de Watergirl
    
    // Hitboxes ajustadas para las puertas
    sf::FloatRect door1Hitbox;
    sf::FloatRect door2Hitbox;

    // Velocidad de movimiento
    float speed;

    // Variables de física
    float gravity;           // Fuerza de gravedad
    float jumpForce;         // Fuerza del salto
    float player1VelocityY;  // Velocidad vertical jugador 1
    float player2VelocityY;  // Velocidad vertical jugador 2
    bool player1OnGround;    // ¿Jugador 1 está en el suelo?
    bool player2OnGround;    // ¿Jugador 2 está en el suelo?
    bool player1DoubleJumpAvailable;  // ¿Jugador 1 puede hacer doble salto?
    bool player2DoubleJumpAvailable;  // ¿Jugador 2 puede hacer doble salto?

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
    void resetGame(); // Reiniciar posiciones al cambiar de nivel
    void initializeGame(); // Nueva función para inicializar el juego
};

#endif // GAME_HPP