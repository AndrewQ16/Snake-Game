//
//  main.cpp
//  Snake
//
//  Created by Andrew Quinonez on 1/9/19.
//  Copyright © 2019 Andrew Quinonez. All rights reserved.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <random>
#include "Food.h"
#include "Snake.h"

using namespace sf;
using namespace std;


int main() {
    //size of window
    RenderWindow* window = new RenderWindow(VideoMode(640,480), "Snake");
    window->setFramerateLimit(60);
    Food *food = new Food();
    Snake * snake = new Snake();
    //To create the size of game container in the window, we'll have a container of size:
    RectangleShape gameWindow;
    gameWindow.setSize(Vector2f(403, 403));
    gameWindow.setFillColor(Color(48, 211, 173));
    //hard coded in the coordinates to put the game window in the middle
    gameWindow.setPosition(117, 57);
    //gameWindow.setPosition(117, 50);
    gameWindow.setOutlineColor(Color::Black);
    //Keeps track of the events
    Event event;
    //Keep track of time
    Time time;
    Clock clock;
    
    //Font
    Font font;
    if(!font.loadFromFile("res/Lato-Black.ttf")){
        cout << "Cant load font."<< endl;
    }
    
    Text text;
    text.setFont(font);
    text.setFillColor(Color::Black);
    text.setCharacterSize(30);
    text.setPosition(200, 10);
    
    
    while (window->isOpen()) {
        while(window->pollEvent(event)){
            if(event.type == Event::Closed){
                delete food;
                window->close();
                return 0;
            }
            //Check for direction change
            if (event.type == Event::KeyPressed) {
                snake->setDirection(event.key.code);
            }

            //checks if there's collision with food within while loops
            if(snake->getSnakeHead().getPosition().x == food->getRect().getPosition().x &&
               snake->getSnakeHead().getPosition().y == food->getRect().getPosition().y){
                snake->increaseSnake();
                food->setNewLocation(snake->getSnakeArray(), snake->getCurrentSize());
            }
            snake->collision(gameWindow);
            //Check if it's been more than a second, if so, move all the snake the next block over.
            time = clock.getElapsedTime();
            if(time.asSeconds() > .5){
                snake->moveSnake();
                clock.restart();
            }
            text.setString("Score: " + to_string(snake->getCurrentSize() - 1)) ;
            
            window->clear(Color::White);
            window->draw(gameWindow);
            window->draw(food->getRect());
            snake->drawSnake(*window);
            window->draw(text);
            window->display();
        };
        
        //checks if there's collision with food outside of the event loop check
        if(snake->getSnakeHead().getPosition().x == food->getRect().getPosition().x &&
           snake->getSnakeHead().getPosition().y == food->getRect().getPosition().y){
            snake->increaseSnake();
            food->setNewLocation(snake->getSnakeArray(), snake->getCurrentSize());
        }
        snake->collision(gameWindow);
        //Check if it's been more than a second, if so, move all the snake the next block over.
        time = clock.getElapsedTime();
        if(time.asSeconds() > .5){
            snake->moveSnake();
            clock.restart();
        }
        text.setString("Score: " + to_string(snake->getCurrentSize() - 1)) ;
        window->clear(Color::White);
        window->draw(gameWindow);
        window->draw(food->getRect());
        window->draw(text);
        snake->drawSnake(*window);
        window->display();
    };
    return 0;
}
