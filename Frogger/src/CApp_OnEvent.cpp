//==============================================================================
#include "../headers/CApp.h"

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {
    if(Event->type == SDL_QUIT) {
        Running = false;
    }

    if(Event->key.keysym.sym == SDLK_SPACE){
      //start the game when press space
       if(currentStatus == START || currentStatus == GAME_OVER || currentStatus == WIN){
           restartGame();
           currentStatus = GAME;
       }

    }
//read the user input and stores it
    if(Event->key.keysym.sym == SDLK_LEFT){
        //left arrow input
        if(Event->type == SDL_KEYDOWN){
            player.leftKeyDown = true;
            player.setDirection(player.LEFT);
        }else {
            player.leftKeyDown = false;
        }
    }
    //right arrow input
    else if(Event->key.keysym.sym == SDLK_RIGHT){
        if(Event->type == SDL_KEYDOWN){
            player.rightKeyDown = true;
            player.setDirection(player.RIGHT);
        }else {
            player.rightKeyDown = false;
        }
    } else if(Event->key.keysym.sym == SDLK_UP){
        if(Event->type == SDL_KEYDOWN){
            player.upKeyDown = true;

        }else {
            player.upKeyDown = false;

        }
    }
}

//==============================================================================
