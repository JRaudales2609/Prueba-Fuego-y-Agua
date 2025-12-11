#include <SFML/Graphics.hpp>
#include "../include/Game.hpp"
#include <iostream>

int main()
{
    Game game;
    game.run();

    return 0;
}

Game::Game() :
    window(sf::VideoMode(1200, 800), "Fuego y Agua - 2 Jugadores"),
    currentLevel(1),
    speed(5.0f),
    player1Diamonds(0),
    player2Diamonds(0),
    diamond1Visible(true),
    diamond2Visible(true),
    currentFrame1(0),
    currentFrame2(0),
    frameTime(0.1f),
    baseScale1(0.0f),
    baseScale2(0.0f)
{
    window.setFramerateLimit(60);

    // Cargar el nivel
    currentLevel.loadLevel();

    // Cargar fuente para texto de coordenadas (usa fuente del sistema)
    // Si no funciona, descarga una fuente .ttf y ponla en assets/fonts/
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Advertencia: No se pudo cargar la fuente" << std::endl;
    }
    mouseCoordText.setFont(font);
    mouseCoordText.setCharacterSize(20);
    mouseCoordText.setFillColor(sf::Color::White);
    mouseCoordText.setPosition(10.0f, 10.0f);

    // Cargar texturas de diamantes
    if (!fireDiamondTexture.loadFromFile("assets/imagenes/diamantes/fire_diamond.png")) {
        std::cerr << "Error: No se pudo cargar fire_diamond.png" << std::endl;
    } else {
        std::cout << "fire_diamond.png cargado correctamente" << std::endl;
    }
    if (!waterDiamondTexture.loadFromFile("assets/imagenes/diamantes/water_diamond.png")) {
        std::cerr << "Error: No se pudo cargar water_diamond.png" << std::endl;
    } else {
        std::cout << "water_diamond.png cargado correctamente" << std::endl;
    }

    // Cargar texturas de puertas
    if (!fireDoorTexture.loadFromFile("assets/imagenes/puertas/fire_door.png")) {
        std::cerr << "Error: No se pudo cargar fire_door.png" << std::endl;
    } else {
        std::cout << "fire_door.png cargado correctamente" << std::endl;
    }
    if (!waterDoorTexture.loadFromFile("assets/imagenes/puertas/water_door.png")) {
        std::cerr << "Error: No se pudo cargar water_door.png" << std::endl;
    } else {
        std::cout << "water_door.png cargado correctamente" << std::endl;
    }

    // Cargar texturas de personajes (sprite sheets)
    if (!fireboyTexture.loadFromFile("assets/imagenes/personajes/fireboy_spritesheet.png")) {
        std::cerr << "Error: No se pudo cargar fireboy_spritesheet.png" << std::endl;
    } else {
        std::cout << "fireboy_spritesheet.png cargado correctamente" << std::endl;
    }
    if (!watergirlTexture.loadFromFile("assets/imagenes/personajes/watergirl_spritesheet.png")) {
        std::cerr << "Error: No se pudo cargar watergirl_spritesheet.png" << std::endl;
    } else {
        std::cout << "watergirl_spritesheet.png cargado correctamente" << std::endl;
    }

    // Cargar texturas de obstáculos
    if (!lavaTexture.loadFromFile("assets/imagenes/obstaculos/lava.png")) {
        std::cerr << "Error: No se pudo cargar lava.png" << std::endl;
    } else {
        std::cout << "lava.png cargado correctamente" << std::endl;
    }
    if (!waterTexture.loadFromFile("assets/imagenes/obstaculos/water.png")) {
        std::cerr << "Error: No se pudo cargar water.png" << std::endl;
    } else {
        std::cout << "water.png cargado correctamente" << std::endl;
    }
    if (!mudTexture.loadFromFile("assets/imagenes/obstaculos/mud.png")) {
        std::cerr << "Error: No se pudo cargar mud.png" << std::endl;
    } else {
        std::cout << "mud.png cargado correctamente" << std::endl;
    }

    // Configurar Jugador 1 - Fireboy (WASD)
    player1.setTexture(fireboyTexture);
    // Asumiendo 4 frames horizontales, cada frame es width/4
    int frameWidth1 = fireboyTexture.getSize().x / 4;
    int frameHeight1 = fireboyTexture.getSize().y;
    player1.setTextureRect(sf::IntRect(0, 0, frameWidth1, frameHeight1));
    player1.setOrigin(frameWidth1 / 2.0f, frameHeight1 / 2.0f); // Centrar el origen
    player1.setPosition(150.0f, 375.0f);
    float player1Scale = 50.0f / frameWidth1; // Ajustar tamaño del jugador
    player1.setScale(player1Scale, player1Scale);
    baseScale1 = player1Scale; // Guardar escala base

    // Configurar Jugador 2 - Watergirl (Flechas)
    player2.setTexture(watergirlTexture);
    int frameWidth2 = watergirlTexture.getSize().x / 4;
    int frameHeight2 = watergirlTexture.getSize().y;
    player2.setTextureRect(sf::IntRect(0, 0, frameWidth2, frameHeight2));
    player2.setOrigin(frameWidth2 / 2.0f, frameHeight2 / 2.0f); // Centrar el origen
    player2.setPosition(1000.0f, 375.0f);
    float player2Scale = 50.0f / frameWidth2; // Ajustar tamaño del jugador
    player2.setScale(player2Scale, player2Scale);
    baseScale2 = player2Scale; // Guardar escala base

    // Diamante 1 - Fuego (usar sprite con textura)
    diamond1.setTexture(fireDiamondTexture);
    diamond1.setPosition(300.0f, 400.0f);
    // Calcular escala basada en el tamaño de la textura para que tenga 50 píxeles
    float scale1 = 50.0f / fireDiamondTexture.getSize().x;
    diamond1.setScale(scale1, scale1);

    // Diamante 2 - Agua (usar sprite con textura)
    diamond2.setTexture(waterDiamondTexture);
    diamond2.setPosition(900.0f, 400.0f);
    // Calcular escala basada en el tamaño de la textura para que tenga 50 píxeles
    float scale2 = 50.0f / waterDiamondTexture.getSize().x;
    diamond2.setScale(scale2, scale2);

    // Configurar Lava (usar sprite con textura)
    lava.setTexture(lavaTexture);
    lava.setPosition(500.0f, 600.0f);
    float lavaScale = 150.0f / lavaTexture.getSize().x;
    lava.setScale(lavaScale, lavaScale);
    // Hitbox simple: rectángulo directo (X, Y, Ancho, Alto)
    lavaHitbox = sf::FloatRect(510.0f, 700.0f, 130.0f, 15.0f);

    // Configurar Agua (usar sprite con textura)
    water.setTexture(waterTexture);
    water.setPosition(300.0f, 500.0f);
    float waterScale = 150.0f / waterTexture.getSize().x;
    water.setScale(waterScale, waterScale);
    // Hitbox simple: rectángulo directo
    waterHitbox = sf::FloatRect(310.0f, 600.0f, 130.0f, 15.0f);

    // Configurar Lodo (usar sprite con textura)
    mud.setTexture(mudTexture);
    mud.setPosition(700.0f, 500.0f);
    float mudScale = 150.0f / mudTexture.getSize().x;
    mud.setScale(mudScale, mudScale);
    // Hitbox simple: rectángulo directo
    mudHitbox = sf::FloatRect(710.0f, 600.0f, 130.0f, 15.0f);

    // Puerta 1 - Fuego (usar sprite con textura)
    door1.setTexture(fireDoorTexture);
    door1.setPosition(50.0f, 650.0f);
    float doorScale1 = 80.0f / fireDoorTexture.getSize().x; // Reducido a 80px
    door1.setScale(doorScale1, doorScale1);
    // Hitbox un poco más grande que el personaje (~60x60)
    door1Hitbox = sf::FloatRect(50.0f + 10.0f, 650.0f + 10.0f, 60.0f, 70.0f);

    // Puerta 2 - Agua (usar sprite con textura)
    door2.setTexture(waterDoorTexture);
    door2.setPosition(1070.0f, 650.0f);
    float doorScale2 = 80.0f / waterDoorTexture.getSize().x; // Reducido a 80px
    door2.setScale(doorScale2, doorScale2);
    // Hitbox un poco más grande que el personaje
    door2Hitbox = sf::FloatRect(1070.0f + 10.0f, 650.0f + 10.0f, 60.0f, 70.0f);
}

void Game::run()
{
    // Bucle principal
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update()
{
    // Obtener posición del mouse y mostrarla en pantalla
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    mouseCoordText.setString("Mouse: X=" + std::to_string(mousePos.x) + " Y=" + std::to_string(mousePos.y));

    // Movimiento Jugador 1 (WASD)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        player1.move(0.0f, -speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        player1.move(0.0f, speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        player1.move(-speed, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        player1.move(speed, 0.0f);

    // Movimiento Jugador 2 (Flechas)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        player2.move(0.0f, -speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        player2.move(0.0f, speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        player2.move(-speed, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        player2.move(speed, 0.0f);

    // Limitar los jugadores dentro de la pantalla
    // Jugador 1
    if (player1.getPosition().x < 0)
        player1.setPosition(0, player1.getPosition().y);
    if (player1.getPosition().x + 50 > 1200)
        player1.setPosition(1150, player1.getPosition().y);
    if (player1.getPosition().y < 0)
        player1.setPosition(player1.getPosition().x, 0);
    if (player1.getPosition().y + 50 > 800)
        player1.setPosition(player1.getPosition().x, 750);

    // Jugador 2
    if (player2.getPosition().x < 0)
        player2.setPosition(0, player2.getPosition().y);
    if (player2.getPosition().x + 50 > 1200)
        player2.setPosition(1150, player2.getPosition().y);
    if (player2.getPosition().y < 0)
        player2.setPosition(player2.getPosition().x, 0);
    if (player2.getPosition().y + 50 > 800)
        player2.setPosition(player2.getPosition().x, 750);

    // Detectar colisiones con los diamantes
    if (diamond1Visible && player1.getGlobalBounds().intersects(diamond1.getGlobalBounds())) {
        diamond1Visible = false; // Ocultar el diamante
        player1Diamonds++;
    }
    if (diamond2Visible && player2.getGlobalBounds().intersects(diamond2.getGlobalBounds())) {
        diamond2Visible = false; // Ocultar el diamante
        player2Diamonds++;
    }

    // Detectar colisiones con las puertas (usando hitboxes ajustadas)
    if (player1.getGlobalBounds().intersects(door1Hitbox) && player1Diamonds >= 1) {
        std::cout << "Fireboy ha ganado!" << std::endl;
        window.close(); // Fireboy gana
    }
    if (player2.getGlobalBounds().intersects(door2Hitbox) && player2Diamonds >= 1) {
        std::cout << "Watergirl ha ganado!" << std::endl;
        window.close(); // Watergirl gana
    }

    // Detectar colisiones con la lava (usando hitbox ajustada)
    if (player1.getGlobalBounds().intersects(lavaHitbox)) {
        // Fireboy puede pasar por la lava
    } else if (player2.getGlobalBounds().intersects(lavaHitbox)) {
        player2.setPosition(1000.0f, 375.0f); // Reiniciar posición de Watergirl
    }

    // Detectar colisiones con el agua (usando hitbox ajustada)
    if (player2.getGlobalBounds().intersects(waterHitbox)) {
        // Watergirl puede pasar por el agua
    } else if (player1.getGlobalBounds().intersects(waterHitbox)) {
        player1.setPosition(150.0f, 375.0f); // Reiniciar posición de Fireboy
    }

    // Detectar colisiones con el lodo verde (usando hitbox ajustada)
    if (player1.getGlobalBounds().intersects(mudHitbox)) {
        player1.setPosition(150.0f, 375.0f); // Reiniciar posición de Fireboy
    }
    if (player2.getGlobalBounds().intersects(mudHitbox)) {
        player2.setPosition(1000.0f, 375.0f); // Reiniciar posición de Watergirl
    }

    // Actualizar animación
    updateAnimation();
}

void Game::updateAnimation()
{
    // Actualizar animación si ha pasado suficiente tiempo
    if (animationClock.getElapsedTime().asSeconds() > frameTime) {
        // Determinar si los jugadores están en movimiento y dirección
        bool player1Moving = sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
                            sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
                            sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
                            sf::Keyboard::isKeyPressed(sf::Keyboard::D);

        bool player2Moving = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
                            sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
                            sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
                            sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

        // Dimensiones de frames para cada jugador
        int frameWidth1 = fireboyTexture.getSize().x / 4;
        int frameHeight1 = fireboyTexture.getSize().y;
        int frameWidth2 = watergirlTexture.getSize().x / 4;
        int frameHeight2 = watergirlTexture.getSize().y;

        // Animar jugador 1 si se está moviendo
        if (player1Moving) {
            currentFrame1 = (currentFrame1 + 1) % 4; // Ciclar entre 0-3
            player1.setTextureRect(sf::IntRect(currentFrame1 * frameWidth1, 0, frameWidth1, frameHeight1));
            
            // Voltear sprite según la dirección horizontal
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                // Moviendo a la izquierda - voltear sprite
                player1.setScale(-baseScale1, baseScale1);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                // Moviendo a la derecha - orientación normal
                player1.setScale(baseScale1, baseScale1);
            }
        } else {
            currentFrame1 = 0; // Volver al primer frame cuando está quieto
            player1.setTextureRect(sf::IntRect(0, 0, frameWidth1, frameHeight1));
        }

        // Animar jugador 2 si se está moviendo
        if (player2Moving) {
            currentFrame2 = (currentFrame2 + 1) % 4; // Ciclar entre 0-3
            player2.setTextureRect(sf::IntRect(currentFrame2 * frameWidth2, 0, frameWidth2, frameHeight2));
            
            // Voltear sprite según la dirección horizontal
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                // Moviendo a la izquierda - voltear sprite
                player2.setScale(-baseScale2, baseScale2);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                // Moviendo a la derecha - orientación normal
                player2.setScale(baseScale2, baseScale2);
            }
        } else {
            currentFrame2 = 0; // Volver al primer frame cuando está quieto
            player2.setTextureRect(sf::IntRect(0, 0, frameWidth2, frameHeight2));
        }

        animationClock.restart();
    }
}

sf::FloatRect Game::getPlayer1Bounds()
{
    return player1.getGlobalBounds();
}

sf::FloatRect Game::getPlayer2Bounds()
{
    return player2.getGlobalBounds();
}

void Game::render()
{
    window.clear(sf::Color::Black);
    
    // Dibujar fondo del nivel
    currentLevel.render(window);
    
    window.draw(player1);
    window.draw(player2);
    if (diamond1Visible) window.draw(diamond1); // Dibujar diamante solo si es visible
    if (diamond2Visible) window.draw(diamond2);
    window.draw(lava); // Dibujar obstáculos
    window.draw(water); // Dibujar agua
    window.draw(mud); // Dibujar lodo verde
    window.draw(door1); // Dibujar puerta de Fireboy
    window.draw(door2); // Dibujar puerta de Watergirl
    
    // Dibujar coordenadas del mouse (para desarrollo)
    window.draw(mouseCoordText);
    
    window.display();
}
