#include <SFML/Graphics.hpp>
#include "../include/Game.hpp"
#include <iostream>

Game::Game(int startingLevel) :
    window(sf::VideoMode(1200, 800), "Fuego y Agua - 2 Jugadores"),
    currentLevel(startingLevel), // Usar el nivel seleccionado
    speed(7.0f),
    gravity(0.5f),
    jumpForce(-9.5f),
    player1VelocityY(0.0f),
    player2VelocityY(0.0f),
    player1OnGround(false),
    player2OnGround(false),
    player1DoubleJumpAvailable(false),
    player2DoubleJumpAvailable(false),
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
    std::cout << "Iniciando juego en nivel " << startingLevel << std::endl;
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

    // Los obstáculos (lava, agua, lodo) NO se configuran aquí
    // Se crearán dinámicamente desde las posiciones del nivel
    // Solo preparar las texturas y escalas
    lava.setTexture(lavaTexture);
    float lavaScale = 150.0f / lavaTexture.getSize().x;
    lava.setScale(lavaScale, lavaScale);
    lava.setOrigin(lavaTexture.getSize().x / 2.0f, lavaTexture.getSize().y / 2.0f);
    
    water.setTexture(waterTexture);
    float waterScale = 150.0f / waterTexture.getSize().x;
    water.setScale(waterScale, waterScale);
    water.setOrigin(waterTexture.getSize().x / 2.0f, waterTexture.getSize().y / 2.0f);
    
    mud.setTexture(mudTexture);
    float mudScale = 150.0f / mudTexture.getSize().x;
    mud.setScale(mudScale, mudScale);
    mud.setOrigin(mudTexture.getSize().x / 2.0f, mudTexture.getSize().y / 2.0f);

    // Puerta 1 - Fuego (usar sprite con textura)
    door1.setTexture(fireDoorTexture);
    door1.setPosition(50.0f, 650.0f);
    float doorScale1 = 80.0f / fireDoorTexture.getSize().x; // Reducido a 80px
    door1.setScale(doorScale1, doorScale1);
    // Hitbox pequeña en el centro del portal (~30x40)
    door1Hitbox = sf::FloatRect(50.0f + 25.0f, 650.0f + 20.0f, 30.0f, 40.0f);

    // Puerta 2 - Agua (usar sprite con textura)
    door2.setTexture(waterDoorTexture);
    door2.setPosition(1070.0f, 650.0f);
    float doorScale2 = 80.0f / waterDoorTexture.getSize().x; // Reducido a 80px
    door2.setScale(doorScale2, doorScale2);
    // Hitbox pequeña en el centro del portal
    door2Hitbox = sf::FloatRect(1070.0f + 25.0f, 650.0f + 20.0f, 30.0f, 40.0f);
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
        
        // Cambiar de nivel con teclas numéricas
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Num1) {
                currentLevel.changeLevel(1);
                resetGame();
            }
            else if (event.key.code == sf::Keyboard::Num2) {
                currentLevel.changeLevel(2);
                resetGame();
            }
            // Salto Jugador 1 (W)
            else if (event.key.code == sf::Keyboard::W) {
                if (player1OnGround) {
                    player1VelocityY = jumpForce;
                    player1OnGround = false;
                    player1DoubleJumpAvailable = true;
                } else if (player1DoubleJumpAvailable) {
                    player1VelocityY = jumpForce;
                    player1DoubleJumpAvailable = false;
                }
            }
            // Salto Jugador 2 (Up)
            else if (event.key.code == sf::Keyboard::Up) {
                if (player2OnGround) {
                    player2VelocityY = jumpForce;
                    player2OnGround = false;
                    player2DoubleJumpAvailable = true;
                } else if (player2DoubleJumpAvailable) {
                    player2VelocityY = jumpForce;
                    player2DoubleJumpAvailable = false;
                }
            }
        }
    }
}

void Game::update()
{
    // Obtener posición del mouse y mostrarla en pantalla
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    mouseCoordText.setString("Mouse: X=" + std::to_string(mousePos.x) + " Y=" + std::to_string(mousePos.y));

    // === FÍSICA: Aplicar gravedad ===
    player1VelocityY += gravity;
    player2VelocityY += gravity;

    std::vector<sf::FloatRect> platforms = currentLevel.getPlatforms();

    // === MOVIMIENTO HORIZONTAL Jugador 1 (A/D) ===
    sf::Vector2f player1OldPos = player1.getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        player1.move(-speed, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        player1.move(speed, 0.0f);

    // Colisión horizontal Jugador 1
    bool player1HorizontalCollision = false;
    for(const auto& platform : platforms) {
        sf::FloatRect p1Bounds = player1.getGlobalBounds();
        if (p1Bounds.intersects(platform)) {
            // Calcular superposiciones
            float overlapLeft = (p1Bounds.left + p1Bounds.width) - platform.left;
            float overlapRight = (platform.left + platform.width) - p1Bounds.left;
            float overlapTop = (p1Bounds.top + p1Bounds.height) - platform.top;
            float overlapBottom = (platform.top + platform.height) - p1Bounds.top;
            
            // Determinar cual superposición es menor para saber desde dónde viene la colisión
            float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});
            
            // Solo bloquear si la menor superposición es lateral (left o right)
            if (minOverlap == overlapLeft || minOverlap == overlapRight) {
                player1.setPosition(player1OldPos);
                player1HorizontalCollision = true;
                break;
            }
        }
    }

    // === MOVIMIENTO VERTICAL Jugador 1 ===
    player1OldPos = player1.getPosition();
    player1.move(0.0f, player1VelocityY);

    // Colisión vertical Jugador 1
    player1OnGround = false;
    for(const auto& platform : platforms) {
        sf::FloatRect p1Bounds = player1.getGlobalBounds();
        if (p1Bounds.intersects(platform)) {
            if (player1VelocityY > 0) {
                // Cayendo
                player1.setPosition(player1OldPos);
                player1VelocityY = 0.0f;
                player1OnGround = true;
                player1DoubleJumpAvailable = false;
            } else if (player1VelocityY < 0) {
                // Subiendo
                player1.setPosition(player1OldPos);
                player1VelocityY = 0.0f;
            }
            break;
        }
    }

    // === MOVIMIENTO HORIZONTAL Jugador 2 (Left/Right) ===
    sf::Vector2f player2OldPos = player2.getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        player2.move(-speed, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        player2.move(speed, 0.0f);

    // Colisión horizontal Jugador 2
    bool player2HorizontalCollision = false;
    for(const auto& platform : platforms) {
        sf::FloatRect p2Bounds = player2.getGlobalBounds();
        if (p2Bounds.intersects(platform)) {
            // Calcular superposiciones
            float overlapLeft = (p2Bounds.left + p2Bounds.width) - platform.left;
            float overlapRight = (platform.left + platform.width) - p2Bounds.left;
            float overlapTop = (p2Bounds.top + p2Bounds.height) - platform.top;
            float overlapBottom = (platform.top + platform.height) - p2Bounds.top;
            
            // Determinar cual superposición es menor para saber desde dónde viene la colisión
            float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});
            
            // Solo bloquear si la menor superposición es lateral (left o right)
            if (minOverlap == overlapLeft || minOverlap == overlapRight) {
                player2.setPosition(player2OldPos);
                player2HorizontalCollision = true;
                break;
            }
        }
    }

    // === MOVIMIENTO VERTICAL Jugador 2 ===
    player2OldPos = player2.getPosition();
    player2.move(0.0f, player2VelocityY);

    // Colisión vertical Jugador 2
    player2OnGround = false;
    for(const auto& platform : platforms) {
        sf::FloatRect p2Bounds = player2.getGlobalBounds();
        if (p2Bounds.intersects(platform)) {
            if (player2VelocityY > 0) {
                // Cayendo
                player2.setPosition(player2OldPos);
                player2VelocityY = 0.0f;
                player2OnGround = true;
                player2DoubleJumpAvailable = false;
            } else if (player2VelocityY < 0) {
                // Subiendo
                player2.setPosition(player2OldPos);
                player2VelocityY = 0.0f;
            }
            break;
        }
    }


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

    // Detectar colisiones con obstáculos del nivel
    std::vector<sf::Vector2f> lavaPos = currentLevel.getLavaPositions();
    std::vector<sf::Vector2f> waterPos = currentLevel.getWaterPositions();
    std::vector<sf::Vector2f> mudPos = currentLevel.getMudPositions();
    
    // Colisiones con lava
    for(const auto& pos : lavaPos) {
        float hitWidth = 130.0f;
        float hitHeight = 30.0f;
        sf::FloatRect hitbox(pos.x - hitWidth/2.0f, pos.y - hitHeight/2.0f, hitWidth, hitHeight);
        
        if (player2.getGlobalBounds().intersects(hitbox)) {
            player2.setPosition(currentLevel.getPlayer2StartPos());
        }
        // Fireboy puede pasar por la lava
    }
    
    // Colisiones con agua
    for(const auto& pos : waterPos) {
        float hitWidth = 130.0f;
        float hitHeight = 30.0f;
        sf::FloatRect hitbox(pos.x - hitWidth/2.0f, pos.y - hitHeight/2.0f, hitWidth, hitHeight);
        
        if (player1.getGlobalBounds().intersects(hitbox)) {
            player1.setPosition(currentLevel.getPlayer1StartPos());
        }
        // Watergirl puede pasar por el agua
    }
    
    // Colisiones con lodo
    for(const auto& pos : mudPos) {
        float hitWidth = 130.0f;
        float hitHeight = 30.0f;
        sf::FloatRect hitbox(pos.x - hitWidth/2.0f, pos.y - hitHeight/2.0f, hitWidth, hitHeight);
        
        if (player1.getGlobalBounds().intersects(hitbox)) {
            player1.setPosition(currentLevel.getPlayer1StartPos());
        }
        if (player2.getGlobalBounds().intersects(hitbox)) {
            player2.setPosition(currentLevel.getPlayer2StartPos());
        }
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

void Game::resetGame()
{
    // Reiniciar posiciones de jugadores según el nivel actual
    player1.setPosition(currentLevel.getPlayer1StartPos());
    player2.setPosition(currentLevel.getPlayer2StartPos());
    
    // Reiniciar diamantes
    diamond1.setPosition(currentLevel.getDiamond1Pos());
    diamond2.setPosition(currentLevel.getDiamond2Pos());
    diamond1Visible = true;
    diamond2Visible = true;
    player1Diamonds = 0;
    player2Diamonds = 0;
    
    // Reiniciar puertas
    door1.setPosition(currentLevel.getDoor1Pos());
    door2.setPosition(currentLevel.getDoor2Pos());
    // Actualizar hitboxes de puertas - pequeñas en el centro
    door1Hitbox = sf::FloatRect(currentLevel.getDoor1Pos().x + 25.0f, currentLevel.getDoor1Pos().y + 20.0f, 30.0f, 40.0f);
    door2Hitbox = sf::FloatRect(currentLevel.getDoor2Pos().x + 25.0f, currentLevel.getDoor2Pos().y + 20.0f, 30.0f, 40.0f);
    
    std::cout << "Nivel cambiado y juego reiniciado" << std::endl;
}

void Game::render()
{
    window.clear(sf::Color::Black);
    
    // Dibujar fondo del nivel
    currentLevel.render(window);
    
    // Dibujar puertas primero (para que estén detrás de los jugadores)
    window.draw(door1);
    window.draw(door2);
    
    // Dibujar jugadores encima de las puertas
    window.draw(player1);
    window.draw(player2);
    if (diamond1Visible) window.draw(diamond1);
    if (diamond2Visible) window.draw(diamond2);
    
    // Dibujar obstáculos solo si hay posiciones definidas en el nivel
    std::vector<sf::Vector2f> lavaPos = currentLevel.getLavaPositions();
    std::vector<sf::Vector2f> waterPos = currentLevel.getWaterPositions();
    std::vector<sf::Vector2f> mudPos = currentLevel.getMudPositions();
    
    for(const auto& pos : lavaPos) {
        lava.setPosition(pos);
        window.draw(lava);
    }
    for(const auto& pos : waterPos) {
        water.setPosition(pos);
        window.draw(water);
    }
    for(const auto& pos : mudPos) {
        mud.setPosition(pos);
        window.draw(mud);
    }
    
    // Dibujar coordenadas del mouse (para desarrollo)
    window.draw(mouseCoordText);
    
    window.display();
}
