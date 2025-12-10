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
    player1(sf::Vector2f(50.0f, 50.0f)),
    player2(sf::Vector2f(50.0f, 50.0f)),
    diamond1(15.0f),
    diamond2(15.0f),
    lava(sf::Vector2f(200.0f, 50.0f)),
    water(sf::Vector2f(200.0f, 50.0f)),
    mud(sf::Vector2f(200.0f, 50.0f)),
    door1(sf::Vector2f(50.0f, 100.0f)),
    door2(sf::Vector2f(50.0f, 100.0f)),
    speed(5.0f),
    player1Diamonds(0),
    player2Diamonds(0)
{
    window.setFramerateLimit(60);

    // Jugador 1 - Rojo (WASD)
    player1.setFillColor(sf::Color::Red);
    player1.setPosition(150.0f, 375.0f);

    // Jugador 2 - Azul (Flechas)
    player2.setFillColor(sf::Color::Blue);
    player2.setPosition(1000.0f, 375.0f);

    // Diamante 1 - Rojo
    diamond1.setFillColor(sf::Color::Red);
    diamond1.setPosition(300.0f, 400.0f);

    // Diamante 2 - Azul
    diamond2.setFillColor(sf::Color::Blue);
    diamond2.setPosition(900.0f, 400.0f);

    // Lava
    lava.setFillColor(sf::Color(255, 69, 0)); // Naranja
    lava.setPosition(500.0f, 600.0f);

    // Agua
    water.setFillColor(sf::Color::Blue);
    water.setPosition(300.0f, 500.0f);

    // Lodo verde
    mud.setFillColor(sf::Color(0, 128, 0)); // Verde oscuro
    mud.setPosition(700.0f, 500.0f);

    // Puerta 1 - Rojo (Fireboy)
    door1.setFillColor(sf::Color::Red);
    door1.setPosition(100.0f, 100.0f);

    // Puerta 2 - Azul (Watergirl)
    door2.setFillColor(sf::Color::Blue);
    door2.setPosition(1050.0f, 100.0f);
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
    if (player1.getGlobalBounds().intersects(diamond1.getGlobalBounds())) {
        diamond1.setPosition(-50.0f, -50.0f); // Mover fuera de la pantalla
        player1Diamonds++;
    }
    if (player2.getGlobalBounds().intersects(diamond2.getGlobalBounds())) {
        diamond2.setPosition(-50.0f, -50.0f); // Mover fuera de la pantalla
        player2Diamonds++;
    }

    // Detectar colisiones con las puertas
    if (player1.getGlobalBounds().intersects(door1.getGlobalBounds()) && player1Diamonds >= 1) {
        std::cout << "Fireboy ha ganado!" << std::endl;
        window.close(); // Fireboy gana
    }
    if (player2.getGlobalBounds().intersects(door2.getGlobalBounds()) && player2Diamonds >= 1) {
        std::cout << "Watergirl ha ganado!" << std::endl;
        window.close(); // Watergirl gana
    }

    // Detectar colisiones con la lava
    if (player1.getGlobalBounds().intersects(lava.getGlobalBounds())) {
        // Fireboy puede pasar por la lava
    } else if (player2.getGlobalBounds().intersects(lava.getGlobalBounds())) {
        player2.setPosition(1000.0f, 375.0f); // Reiniciar posición de Watergirl
    }

    // Detectar colisiones con el agua
    if (player2.getGlobalBounds().intersects(water.getGlobalBounds())) {
        // Watergirl puede pasar por el agua
    } else if (player1.getGlobalBounds().intersects(water.getGlobalBounds())) {
        player1.setPosition(150.0f, 375.0f); // Reiniciar posición de Fireboy
    }

    // Detectar colisiones con el lodo verde
    if (player1.getGlobalBounds().intersects(mud.getGlobalBounds())) {
        player1.setPosition(150.0f, 375.0f); // Reiniciar posición de Fireboy
    }
    if (player2.getGlobalBounds().intersects(mud.getGlobalBounds())) {
        player2.setPosition(1000.0f, 375.0f); // Reiniciar posición de Watergirl
    }
}

void Game::render()
{
    window.clear(sf::Color::Black);
    window.draw(player1);
    window.draw(player2);
    window.draw(diamond1); // Dibujar diamantes
    window.draw(diamond2);
    window.draw(lava); // Dibujar obstáculos
    window.draw(water); // Dibujar agua
    window.draw(mud); // Dibujar lodo verde
    window.draw(door1); // Dibujar puerta de Fireboy
    window.draw(door2); // Dibujar puerta de Watergirl
    window.display();
}
