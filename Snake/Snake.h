//
//  Snake.h
//  Snake
//
//  Created by Andrew Quinonez on 1/9/19.
//  Copyright © 2019 Andrew Quinonez. All rights reserved.
//

#ifndef Snake_h
#define Snake_h


#include <SFML/Graphics.hpp>
#include <stdlib.h>

using namespace sf;
using namespace std;

/*
 *  The Snake object will have the necessary methods to grow and return the result if the game is lost.
 */
class Snake{
    RectangleShape head; //head of the snake, if it collides the game ends, since all pieces after follow its path
    int _size = 2; //keeps track of the array's size
    int _index = 0; //keeps track of the current _index
    RectangleShape* snake; //the pointer of the array for the rectangle objects (snake)
    Vector2f* movement; //coordinates of the next tile for the
    Vector2f* lastLocation; //Holds the previous location of the snake's last piece

public:
    Snake(){
        //movement will initially be to the right
        movement = new Vector2f(20,0);
        
        lastLocation = new Vector2f();
        
        head.setFillColor(Color::Red);
        head.setOutlineColor(Color::Black);
        head.setSize(Vector2f(16,16));
        head.setOutlineThickness(2);
        head.setPosition(260, 260);
        snake = new RectangleShape[_size]; //allocates array space in the heap
        
        snake[_index] = head;
        _index++;
    };
    
    //set collision detection for the walls and the snake itself
    void collision(RectangleShape & gameWindow){
        if(snakeCollision()){
            _index = 1;
            cout << "Snake collided" << endl;
        } else if(wallCollision(gameWindow)){
            _index = 1;
            snake[0].setPosition(250, 250);
        }
    };
    
    bool wallCollision(RectangleShape & gameWindow){
        if(snake[0].getPosition().x < 120 || snake[0].getPosition().x > 510 ||
           snake[0].getPosition().y > 440 || snake[0].getPosition().y < 50){
            return true;
        }
        
        return false;
    };
    
    
    
    /*
        Return true if there is a collision found, false otherwise
     */
    bool snakeCollision(){
        if(_index > 1){
            for(int i = 1; i < _index ; i++){
                if(snake[0].getPosition().x == snake[i].getPosition().x &&
                   snake[0].getPosition().y == snake[i].getPosition().y){
                    return true;
                }
            }
        }
        return false;
    };
    
    
    
    /*
        Checks if the location of the head is = to the location of the food
     */
    bool foodCollision(Vector2f food){
        if(food.x == snake[0].getPosition().x && food.y == snake[0].getPosition().y){
            return true;
        } else{
            return false;
        }
    }
    
    //set the increase of the snake
    void increaseSnake(){
        
        
            RectangleShape body; //The following piece of the snake
            body.setSize(Vector2f(16,16));
            body.setOutlineThickness(2);
            body.setFillColor(Color::Red);
            body.setOutlineColor(Color::Black);
            if(_index < _size){//assuming the size of our array is enough
                snake[_index] = body;
                snake[_index].setPosition(lastLocation->x, lastLocation->y);
                _index++;
            } else { //the size needs to be increased
                RectangleShape*temp = new RectangleShape[_size * 2];
                
                for(int i = 0; i < _index; i++){
                    temp[i] = snake[i];
                }
                delete[] snake;
                _size*=2;
                snake = temp;
                snake[_index] = body;
                snake[_index].setPosition(lastLocation->x, lastLocation->y);
                _index++;
            }
       
    };
    
    /*
        Does the drawing of the game.
     */
    void drawSnake(RenderWindow& window){
        for(int i = 0; i < _index; i++){
            window.draw(snake[i]);
        }
    }
    
    /*
        Sets the direction of the head. Get's called after every 1 second
     */
    void setDirection(Keyboard::Key code){
        if(code == Keyboard::Key::A){           //Left
            movement->x = -20;
            movement->y = 0;
        } else if(code == Keyboard::Key::D){     //Right
            movement->x = 20;
            movement->y = 0;
        } else if(code == Keyboard::Key::W){    //Up
            movement->x = 0;
            movement->y = -20;
        } else if(code == Keyboard::Key::S){    //Down
            movement->x = 0;
            movement->y = 20;
        }
    };
    /*
        Will set the next position coordinates to follow the previous snake piece
     */
    void moveSnake(){
        for(int i = 0; i < _index; i++){
            
  
            if(i > 0){
                Vector2f tempPos = snake[i].getPosition();
                snake[i].setPosition(lastLocation->x, lastLocation->y);
                *lastLocation = tempPos;
                
            } else {
                *lastLocation = snake[0].getPosition();
                snake[0].move(movement->x, movement->y);
                
               
            }
            
            

        };
    };
    
    RectangleShape& getSnakeHead(){
        return snake[0];
    }
    
    RectangleShape *getSnakeArray(){
        return snake;
    }
    
    int & getCurrentSize(){
        return _index;
    }
    
    
};


#endif /* Snake_h */
