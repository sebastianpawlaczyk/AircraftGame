#ifndef TICK_GAME_H
#define TICK_GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Game {

private:
    static const float playerSpeed;
    static const sf::Time TimePerFrame;

    sf::RenderWindow *window;
    sf::Sprite *player;
    sf::Texture *texture;

    sf::Font *font;
    sf::Text *statisticsText;
    sf::Time *statisticsUpdateTime;

    unsigned int statisticsNumFrames;

    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;

public:

    Game();
    ~Game();
    void run();

    void processEvents();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void update(sf::Time deltaTime);
    void render();

    void updateStatistics(sf::Time elapsedTime);

};


#endif //TICK_GAME_H
