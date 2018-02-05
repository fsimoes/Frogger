#ifndef ENEMY_HEADER
#define ENEMY_HEADER


#include "CSpriteSheet.h"


class Enemy : public CSpriteSheet
{
    public:
        Enemy();
        virtual ~Enemy();
        int speed = 2;
        void move();
        void reposition();
        void display(SDL_Renderer *prenderer);
    protected:
    private:
};

#endif // ENEMY_HEADER
