#ifndef CSCROLL_PLAYER_H
#define CSCROLL_PLAYER_H

#include "CSpriteSheet.h"


class CMap : public CSpriteSheet
{
    public:
        CMap();
        virtual ~CMap();
        int initMap(bool isTopImage,SDL_Renderer *prenderer);
        float speed = 1;
        void move();
        void restartSpeed();
        void changeSpeed(float newSpeed);
    protected:
    private:

};

#endif // CSCROLL_PLAYER_H
