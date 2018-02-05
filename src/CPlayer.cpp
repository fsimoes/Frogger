#include "../headers/CPlayer.h"


CPlayer::CPlayer()
{
    //ctor
}

CPlayer::~CPlayer()
{
    //dtor
}

void CPlayer::selectState(STATES st){


    if(st == WAITING){
        config_sheet(waiting);
    }
    else if(st == WALKING){

       config_sheet(walking);
    }
    else if(st == JUMPING_UP){

        config_sheet(jumpingUp);
    }
    else if(st == JUMPING_DOWN){
        config_sheet(jumpingDown);
    }
    currentState = st;
}


void CPlayer::configStates(STATES st, animationData ad){

    if(st == WAITING){
        waiting = ad;
    }
    else if(st == WALKING){

        walking = ad;
    }
    else if(st == JUMPING_UP){

        jumpingUp = ad;
    }
    else if(st == JUMPING_DOWN){

        jumpingDown = ad;
    }
}

void CPlayer::checkIdleAnimation(){


}
void CPlayer::hitTheGround(){
    isOnGround = true;
    isJumping = false;
    isColliding = true;
    currentSpeedY = 0;
    selectState(WAITING);


}

bool CPlayer::isFalling(){
    return currentSpeedY >= 0 ;
}

void CPlayer::reset(){
    currentSpeedX = 0;
    currentSpeedY = 0;
    rightKeyDown = false;
    leftKeyDown = false;
    upKeyDown = false;
    isJumping = false;
    isColliding = false;
}

void CPlayer::move()
{
    colisionRect.x = rect.x;
    colisionRect.y = rect.y;

    //move the player based on the keys that are pressed
    if(rightKeyDown && (rect.x + rect.w < window_w)){
       if(currentSpeedX < maxSpeed){
            currentSpeedX += acceletration;
       }
       if(currentState == WAITING){
            selectState(WALKING);
       }

    }
   else if (leftKeyDown && (rect.x > 0)){
       if(currentSpeedX > -maxSpeed){
            currentSpeedX -= acceletration;

       }
        if(currentState == WAITING){
            selectState(WALKING);
       }
    }else {
        currentSpeedX = 0;
       if(currentState == WALKING){
            selectState(WAITING);
       }
    }



    if(isFalling() || !isColliding || isJumping){
        currentSpeedY += gravity;
    }

    if(upKeyDown && !isJumping && isColliding){
       isJumping = true;
       currentSpeedY -= jumpingSpeed;
       selectState(JUMPING_UP);
       Mix_PlayChannel(-1,sfx,0);
    }

    if(isFalling() && !isColliding){
        if(currentState != JUMPING_DOWN){
            selectState(JUMPING_DOWN);
        }
    }
    rect.y += currentSpeedY;
    rect.x += currentSpeedX;
}


