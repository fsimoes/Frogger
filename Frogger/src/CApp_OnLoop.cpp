//==============================================================================
#include "../headers/CApp.h"


void
CApp::MoveSprites()
{
    //move the enemy sprites
   /* for (int i = 0; i < NUM_SPRITES; ++i)
    {
        enemies[i].move();
        enemies[i].display(renderer);
    }
*/

}


void CApp::Draw(){

    backgroundRight.display(renderer);
    backgroundLeft.display(renderer);
    layerBack.display(renderer);
    basePlatform.display(renderer);
    lowerPlatform.display(renderer);
    higherPlatform.display(renderer);
    layerCosmetic.display(renderer);

    for (int i =0; i < numCaves; i++){
        caves[i].display(renderer);
    }

    for (int i = 0; i < arrowPerRow*2; i++){
        arrows[i].display(renderer);
    }

    for (int i = 0; i < (numPlatform*2)+ numCaves; i++){
       movingPlatforms[i].display(renderer);
    }

      for (int q = 0; q < lives; q++){
        //position and display hearts
        heart.rect.x = q * heart.rect.w;
        heart.display(renderer);
    }
	  char UI[] = " % 3d ";
    displayGameStats(window_w,0, UI, (currentLevel));
    bridge.display(renderer);
    player.play(renderer);

}
void CApp::Move(){
    player.move();
    for (int i = 0; i < arrowPerRow*2; i++){
        arrows[i].move();
    }
     for (int i = 0; i < (numPlatform*2)+ numCaves; i++){
          movingPlatforms[i].move();
     }
}
void CApp::CollisionDetect(){
   // player.isColliding = false;
    if(player.isFalling() && player.collisionTest(bridge) && player.rect.y + player.rect.h  <= bridge.rect.y + bridge.rect.h /2){
        player.hitTheGround();
        player.setPosition(player.rect.x,bridge.rect.y - player.rect.h + 3);
    }
     if(player.isFalling() && player.collisionTest(basePlatform)){
        player.hitTheGround();
        player.setPosition(player.rect.x,basePlatform.rect.y - player.rect.h + 3);
    }
     if(player.isFalling() &&player.collisionTest(lowerPlatform)&&  player.rect.y + player.rect.h  <= lowerPlatform.rect.y + lowerPlatform.rect.h/2  ){
        player.hitTheGround();
        player.setPosition(player.rect.x,lowerPlatform.rect.y - player.rect.h + 3);
    }
     if(player.isFalling() &&player.collisionTest(higherPlatform)&& player.rect.y + player.rect.h  <= higherPlatform.rect.y + higherPlatform.rect.h/2  ){
        player.hitTheGround();
        player.setPosition(player.rect.x,higherPlatform.rect.y - player.rect.h + 3);
        if(touchedBridge){
           //gameOver
           //currentStatus = GAME_OVER;
           Mix_PlayChannel(-1,higherPlatform.sfx,0);
           loseLife();
        }
    }

    for (int i = 0; i < (numPlatform*2)+ numCaves; i++){
        if( movingPlatforms[i].collisionTest(player) && player.rect.y + player.rect.h  <= movingPlatforms[i].rect.y + movingPlatforms[i].rect.h/2 ){
            if(player.isFalling()){
                player.hitTheGround();
                player.setPosition(player.rect.x,movingPlatforms[i].rect.y - player.rect.h + 3 );
                touchedBridge = true;

            }
            if(movingPlatforms[i].currentDirection == movingPlatforms[i].LEFT){
               if(player.rect.x > 0){
                 player.rect.x -= movingPlatforms[i].speed;
               }
            }else if(movingPlatforms[i].currentDirection == movingPlatforms[i].RIGHT){
                 if( player.rect.x + player.rect.w < window_w){
                    player.rect.x += movingPlatforms[i].speed;
                 }
            }

             for (int i = 0; i < numCaves; i++){
                if(player.collisionTest(caves[i]) && player.rect.y + player.rect.h  <= caves[i].rect.y + caves[i].rect.h){
                    nextLevel();
                }
            }
        }
    }

    for (int i = 0; i < arrowPerRow*2; i++){
        if(arrows[i].collisionTest(player)){
            Mix_PlayChannel(-1,arrows[i].sfx,0);
            loseLife();
        }
    }
}

//==============================================================================
void CApp::OnLoop()
{
    static Uint32 cnt = 0;

    SDL_SetRenderDrawColor(renderer, 234, 251, 248, 0xFF);
    SDL_RenderClear(renderer);

    switch (currentStatus){
    case START:
        gameTitle.display(renderer);
    break;
    case GAME:
            CollisionDetect();
            Move();
            Draw();

        if(touchedBridge && !bridgeIsMoved){
            bridgeIsMoved = true;
            bridge.setPosition(1000,000);
        }
        break;
        case GAME_OVER:
            gameOver.display(renderer);
        break;
        case WIN:
            win.display(renderer);
        break;
    }
/*
    if(hasStarted && !isGameOver){
        //move and display map
        mapTop.move();
        mapTop.display(renderer);
        mapBotton.move();
        mapBotton.display(renderer);
        //move and display player
        player.move();
        player.play(renderer);

        //check collision with the player
        for (int i = 0; i < NUM_SPRITES; i++){
            if(enemies[i].collisionTest(player) && !isImortal){
                //play hurt sound
                Mix_PlayChannel(-1,player.sfx,0);
                //change the arrow position
                enemies[i].reposition();
                //remove one live
                lives--;
                // set the player to Imortal mode
                isImortal = true;
                imortalTime = 1;
                // if lives are over the game is over
                if(lives <= 0){
                    // set status as game over
                    isGameOver = true;
                    //play game over sound
                    Mix_PlayChannel(-1,gameOver.sfx,0);
                }
            }
        }

        for (int q = 0; q < lives; q++){
            //position and display hearts
            heart.rect.x = q * heart.rect.w;
            heart.display(renderer);
        }

        //control the imortal time
        if(imortalTime%100 == 0){
            isImortal = false;
        }

        //control the meter update
        if(currentTick%45 == 0){
            meters++;
        }

        //move enemy sprites
        MoveSprites();

        //display meter text
        displayGameStats(window_w/2,0, "Meters:%3d ", (meters));

        //add to 1 tickers
        cnt++;
        currentTick++;
        imortalTime++;
    }
    else if(!isGameOver){
            //show intro
            intro.display(renderer);
            displayGameStats(window_w/2,window_h - 80, "Press SPACE to start",0);
    }else {
        //show gameover
        gameOver.display(renderer);
        displayGameStats(window_w/2,window_h - 80, "Press SPACE to restart",0);
        displayGameStats(window_w/2,0, "Meters:%3d ", (meters));
    }*/

}

//==============================================================================
