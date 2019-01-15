//
//  Food.h
//  Snake
//
//
//  Created by Andrew Quinonez on 1/9/19.
//  Copyright © 2019 Andrew Quinonez. All rights reserved.
//

#ifndef Food_h
#define Food_h

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <random>


using namespace sf;
using namespace std;
/*
 *   Creates the 'food' , the squares the snake 'eats'.
 */
class Food {
    RectangleShape* rect;
    Vector2f size;
    
public:
    //Default constructor that creates the food graphic.
    
    Food(){
        rect = new RectangleShape();
        
        
        rect->setSize(Vector2f(16,16));
        rect->setFillColor(Color::White);
        rect->setOutlineThickness(2);
        rect->setOutlineColor(Color::Red);
        rect->setPosition(260, 180);
    }
    
    RectangleShape& getRect(){
        return *rect;
    }
    
    ~Food(){
        delete rect;
    }

    /*
        Creates the new location for the 'food' once it's been eaten.
     
     Note: Add check if the new location is on top of the new snake pieces
     */
    void setNewLocation(RectangleShape * array, int& currentSize){
        int x =10 * 2 * (rand() % 6);
        int y = 10 * 2 * (rand() % 6);
        if(x > 0){
            x += 100 * (rand() % 4);
            
        } else{
            x+= 100 * (rand() % 4);
            
        }
        
        if(y>0){
            y += 100 * (rand() % 4);
        } else{
            y += 100 * (rand() % 4);
        }
        
        x+=120;
        y+=40;
        
        for(int i = 0; i < currentSize ;i++){
            while(x == array->getPosition().x && y == array->getPosition().y){
                x =10 * 2 * (rand() % 6);
                y = 10 * 2 * (rand() % 6);
                if(x > 0){
                    x += 100 * (rand() % 4);
                    
                } else{
                    x+= 100 * (rand() % 4);
                    
                }
                
                if(y>0){
                    y += 100 * (rand() % 4);
                } else{
                    y += 100 * (rand() % 4);
                }
                
                x+=120;
                y+=40;
                
                array++;
            }
        }
        cout << "Food coords: " << x << " , " << y << endl;
        rect->setPosition(x, y);
    }
};

#endif /* Food_h */
