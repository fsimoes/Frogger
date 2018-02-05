#include "../headers/CPlatform.h"

Platform::Platform()
{
    //ctor
}

Platform::~Platform()
{
    //dtor
}


void Platform::reposition(){

    if(currentDirection == LEFT){
        rect.x = window_w ;
   }else if(currentDirection == RIGHT){
       rect.x = -rect.w;
   }
}

void Platform::move()
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
