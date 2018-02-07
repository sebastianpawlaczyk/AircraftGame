#include "Game.h"
#include <iostream>

const float Game::playerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game():statisticsNumFrames(0) {

    window = new sf::RenderWindow(sf::VideoMode(640,480),"Tick", sf::Style::Close);
    player = new sf::Sprite();
    texture = new sf::Texture();
    font = new sf::Font();
    statisticsText = new sf::Text();
    statisticsUpdateTime = new sf::Time();

    mIsMovingUp = false;
    mIsMovingDown = false;
    mIsMovingRight = false;
    mIsMovingLeft = false;

    if(!texture->loadFromFile("/home/seba/CLionProjects/tick/Media/Textures/Eagle.png")){
        //error
    }

    player->setTexture(*texture);
    player->setPosition(100.f,100.f);
    font->loadFromFile("/home/seba/CLionProjects/tick/Media/Sansation.ttf");
    statisticsText->setFont(*font);
    statisticsText->setPosition(5.f,5.f);
    statisticsText->setCharacterSize(10);
}

Game::~Game() {

    std::cout<<"Destructor of Game class"<<std::endl;
    delete window;
    delete player;
}

void Game::run() {

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(window->isOpen()){

        processEvents();
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while(timeSinceLastUpdate > TimePerFrame) {

            timeSinceLastUpdate -= TimePerFrame;

            processEvents();
            update(TimePerFrame);
        }
        updateStatistics(elapsedTime);
        render();
    }
}

void Game::processEvents() {

    sf::Event event;
    while(window->pollEvent(event)){

        switch (event.type){

            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code,true); // when I push the key, the object moves
                break;

            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false); // when I take my finger from the key, the object stops
                break;
            case sf::Event::Closed:
                window->close();
                break;

        }
    }
}

void Game::render() {

    window->clear();
    window->draw(*player);
    window->draw(*statisticsText);
    window->display();
}

void Game::update(sf::Time deltaTime) {

    sf::Vector2f movement(0.f, 0.f);
    if(mIsMovingUp){
        movement.y -= playerSpeed;
    }
    if(mIsMovingDown){
        movement.y += playerSpeed;
    }
    if(mIsMovingLeft){
        movement.x -= playerSpeed;
    }
    if(mIsMovingRight){
        movement.x += playerSpeed;
    }

    player->move(movement * deltaTime.asSeconds());
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {

    if(key == sf::Keyboard::Key::W){
        mIsMovingUp = isPressed;
    }
    else if(key == sf::Keyboard::Key::S){
        mIsMovingDown = isPressed;
    }
    else if(key == sf::Keyboard::Key::A){
        mIsMovingLeft = isPressed;
    }
    else if(key == sf::Keyboard::Key::D){
        mIsMovingRight = isPressed;
    }

}

void Game::updateStatistics(sf::Time elapsedTime) {

    *statisticsUpdateTime += elapsedTime;
    statisticsNumFrames += 1;

    if(*statisticsUpdateTime >= sf::seconds(1.0f)){

        statisticsText->setString(
                "Frames / Second = " + std::to_string(statisticsNumFrames) + "\n"
                        "Time / Update = " + std::to_string(statisticsUpdateTime->asMicroseconds() / statisticsNumFrames) + "us");
        *statisticsUpdateTime -= sf::seconds(1.0f);
        statisticsNumFrames = 0;
    }
}


