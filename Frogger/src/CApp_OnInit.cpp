//==============================================================================
#include "../headers/CApp.h"
#include <stdlib.h>
#include <time.h>
//==============================================================================
bool CApp::OnInit()
{

    int i;

    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_AUDIO)<0)
    {
        return false;
    }
    window = SDL_CreateWindow("Basic SDL 2.0 Scrolling",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);


    TTF_Init( );		//starts up SDL_ttf
    font = TTF_OpenFont("sprites/zeldadxt.ttf", 30); //load zelda font
    color = { 0, 0, 0};

    //starts audio
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        return false;
    }

    music = Mix_LoadMUS( "sounds/background.wav" );

    if( music == NULL ) {
         printf( "Sound Error" );
        return false;
    }
    Mix_PlayMusic(music,-1);

    if (!window)
        return false;
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
        return false;


    strncpy_s(gameTitle.imagename,"sprites/title.bmp",255);
    gameTitle.load(renderer);
    gameTitle.sfx = Mix_LoadWAV("sounds/level.wav");

    strncpy_s(gameOver.imagename,"sprites/gameover.bmp",255);
    gameOver.load(renderer);
    gameOver.sfx = Mix_LoadWAV("sounds/gameOver.wav");

    strncpy_s(win.imagename,"sprites/win.bmp",255);
    win.sfx = Mix_LoadWAV("sounds/win.wav");
    win.load(renderer);

    srand(time(NULL));
    initialDraw();
    return true;
}

void CApp::initialDraw(){

    strncpy_s(backgroundRight.imagename,"sprites/background.bmp",255);
    backgroundRight.load(renderer);
    backgroundRight.setPosition(320,0);

    strncpy_s(backgroundLeft.imagename,"sprites/background.bmp",255);
    backgroundLeft.load(renderer);
    backgroundLeft.setPosition(0,0);

    strncpy_s(layerBack.imagename,"sprites/baseLayer.bmp",255);
    layerBack.load(renderer);

    strncpy_s(layerCosmetic.imagename,"sprites/cosmeticLayer.bmp",255);
    layerCosmetic.load(renderer);

    strncpy_s(basePlatform.imagename,"sprites/basePlatfomr.bmp",255);
    basePlatform.load(renderer);
    basePlatform.setPosition(0,432);

    strncpy_s(lowerPlatform.imagename,"sprites/platform.bmp",255);
    lowerPlatform.load(renderer);
    lowerPlatform.setPosition(0,360);

    strncpy_s(higherPlatform.imagename,"sprites/platform.bmp",255);
    higherPlatform.load(renderer);
    higherPlatform.sfx = Mix_LoadWAV("sounds/hurt.wav");
    higherPlatform.setPosition(0,289);

    strncpy_s(bridge.imagename,"sprites/bridge.bmp",255);
    bridge.load(renderer);
    bridge.setPosition(3,210);

    caveSpaceDiference = (window_w/(numCaves+1));
    platformSpaceDiference = (window_w/(numPlatform));
    arrowSpaceDiference = (window_w/(arrowPerRow));
    for (int i = 0; i < (numPlatform*2)+ numCaves; i++){
        movingPlatforms[i] = {};
    }

    for (int i = 0; i < numPlatform; ++i) {
        //select the sprite
        strncpy_s(movingPlatforms[i].imagename,"sprites/movingPlatform.bmp",255);
        //load the sprite
        movingPlatforms[i].load(renderer);
        //change position to out of screen
        movingPlatforms[i].setPosition(platformSpaceDiference*i,105);
        movingPlatforms[i].setDirection( movingPlatforms[i].LEFT);
    }


    //create platform
    for (int i = numPlatform; i < numPlatform*2; ++i) {
        //select the sprite
        strncpy_s(movingPlatforms[i].imagename,"sprites/movingPlatform.bmp",255);
        //load the sprite
        movingPlatforms[i].load(renderer);
        //change position to out of screen
        movingPlatforms[i].setPosition(movingPlatforms[i].rect.w +(platformSpaceDiference*(i-numPlatform)),155);
        movingPlatforms[i].setDirection( movingPlatforms[i].RIGHT);
    }


    int pi;
    //create platform
    for (int i = 0; i < numCaves; ++i) {
        //select the sprite
        strncpy_s(caves[i].imagename,"sprites/cave.bmp",255);
        //load the sprite
        caves[i].load(renderer);
        //change position to out of screen

        caves[i].setPosition((caveSpaceDiference*(i+1))-caves[i].rect.w/2,5);

        pi = (numPlatform*2) + i;


        strncpy_s(movingPlatforms[pi].imagename,"sprites/movingPlatform.bmp",255);
        movingPlatforms[pi].load(renderer);
        movingPlatforms[pi].setPosition((caves[i].rect.x + caves[i].rect.w/2 - movingPlatforms[pi].rect.w/2),(caves[i].rect.y + caves[i].rect.h));
        if(currentLevel > 3){
            movingPlatforms[pi].setDirection( movingPlatforms[pi].RIGHT);
        }
    }

    for (int i = 0; i < arrowPerRow; ++i) {
        //select the sprite
        strncpy_s(arrows[i].imagename,"sprites/arrow.bmp",255);
        //load the sprite
        arrows[i].load(renderer);
        arrows[i].sfx = Mix_LoadWAV("sounds/hurt.wav");
        //change position to out of screen
        arrows[i].setPosition(arrowSpaceDiference*i,255);
        arrows[i].setDirection( arrows[i].LEFT);
    }

    for (int i = arrowPerRow; i < arrowPerRow*2; ++i) {
        //select the sprite
        strncpy_s(arrows[i].imagename,"sprites/arrow.bmp",255);
        //load the sprite
        arrows[i].load(renderer);
        arrows[i].sfx = Mix_LoadWAV("sounds/hurt.wav");
        //change position to out of screen
        arrows[i].setPosition(arrowSpaceDiference*(i - arrowPerRow),325);
        arrows[i].setDirection(arrows[i].RIGHT);
    }

    strncpy_s(player.imagename,"sprites/player.bmp",255);
    player.load(renderer);

    strncpy_s(heart.imagename,"sprites/heart.bmp",255);
    heart.load(renderer);



    player.configStates(player.WAITING,{6,6,4,60,70,6,1,0,15});
    player.configStates(player.WALKING,{7,71,85,66,68,7,1,0,10});
    player.configStates(player.JUMPING_UP,{1,63,1406,58,71,1,1,0,10});
    player.configStates(player.JUMPING_DOWN,{2,514,1401,62,78,2,1,0,30});
    player.selectState(player.WAITING);
    player.setPosition(WINDOW_WIDTH/2,350);
    player.sfx = Mix_LoadWAV("sounds/jump.wav");
    player.reset();

}




//==============================================================================
