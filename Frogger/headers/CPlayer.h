#ifndef PLAYER_HEADER
#define PLAYER_HEADER


#include "CSpriteSheet.h"


class CPlayer : public CSpriteSheet
{
    public:
        CPlayer();
        virtual ~CPlayer();
        enum STATES{
            WAITING,
            WALKING,
            JUMPING_UP,
            JUMPING_DOWN
        };

        animationData waiting;
        animationData walking;
        animationData jumpingUp;
        animationData jumpingDown;

        STATES currentState;
        float maxSpeed = 2;
        float currentSpeedX = 0;
        float currentSpeedY = 0;
        float acceletration = 0.5;
        bool isJumping;
        bool isOnGround ;
        bool canJump;
        float gravity = 0.5;
        bool isColliding;
        float jumpingSpeed = 8.5;
        void hitTheGround();
        void configStates(STATES st, animationData ad);
        void selectState (STATES st);
        bool isFalling();
        void checkIdleAnimation();
        void reset();
        void move();
    protected:
    private:
};

#endif // PLAYER_HEADER
