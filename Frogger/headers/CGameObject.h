#ifndef CGAMEOBJECT
#define CGAMEOBJECT
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include "mywindow.h"
#include <stdlib.h>
#include <time.h>

/* Implement a sprite as a player.... */

class CGameObject
{
    public:
			CGameObject() {}
            CGameObject(char image[],int x=0, int y=0, int vx=0, int vy=0)
            {
                strncpy_s(imagename,image,255);
                rect.x = x;
                rect.y = y;
                velocity.x = vx;
                velocity.y = vy;
                loaded = false;
                srand(time(NULL));
            }
            enum DIRECTION{
                NONE,
                LEFT,
                RIGHT
            };
            DIRECTION currentDirection = NONE;

            bool loaded;
            SDL_Rect rect;
            SDL_Rect colisionRect;
            SDL_Rect velocity;

            char imagename[255];
            bool leftKeyDown = false;
            bool rightKeyDown = false;
            bool upKeyDown = false;
            Mix_Chunk *sfx = NULL;
            int load(SDL_Renderer *prenderer);

            void setDirection( DIRECTION direction);
            void display(SDL_Renderer *prenderer);
            void move();
            void setImage();
            void update();
            void setPosition(int x, int y);
            void setColisionRect(int x, int y ,int w, int h);
            bool collisionTest(CGameObject &go);
    protected:
            SDL_Texture *texture;


};


#endif
