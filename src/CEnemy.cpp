#include "../headers/CEnemy.h"

Enemy::Enemy()
{
    //ctor
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::reposition(){
    //change the position to an random place out of screen
   if(currentDirection == LEFT){
        rect.x = window_w ;
   }else if(currentDirection == RIGHT){
       rect.x = -rect.w;
   }
}
void Enemy::display(SDL_Renderer *renderer)
{
    if(currentDirection == RIGHT){
        SDL_RenderCopyEx(renderer, texture, NULL, &rect, NULL, NULL, SDL_FLIP_HORIZONTAL);
    }else{
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
}


void Enemy::move()
{
    if(currentDirection == LEFT){
        rect.x -= speed ;
   }else if(currentDirection == RIGHT){
       rect.x += speed;
   }

    if (rect.x > window_w && currentDirection == RIGHT)
    {
       reposition();
    }else if (rect.x + rect.w < 0 && currentDirection == LEFT)
    {
       reposition();
    }
}
