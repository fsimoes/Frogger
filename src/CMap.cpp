#include "../headers/CMap.h"

CMap::CMap()
{
    //ctor
}

CMap::~CMap()
{
    //dtor
}

//position the map on the screen
int CMap::initMap(bool isTopImage,SDL_Renderer *prenderer)
{
    int retval;
    retval = CGameObject::load(prenderer);
    rect.x = 0;
    rect.y = isTopImage? -rect.h:0;
    velocity.x = 0;
    velocity.y = speed;
    return (retval);
}

void CMap::changeSpeed(float newSpeed)
{
    speed  += newSpeed;
    velocity.y = speed;
    if(rect.y > 0){
        rect.y -= speed;
    }else{
        rect.y += speed;
    }
}

void CMap::restartSpeed()
{
    speed = 1;
     velocity.y = speed;
}
//make it move
void CMap::move()
{
    rect.y += velocity.y;

    if (rect.y >= window_h)
    {
        rect.y = -rect.h;
    }
}




