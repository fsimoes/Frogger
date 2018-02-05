//==============================================================================
#include "../headers/CApp.h"

#define QMAKE_CXXFLAGS_RELEASE -= -Zc : strictStrings
#define QMAKE_CFLAGS_RELEASE -= -Zc : strictStrings
#define QMAKE_CFLAGS -= -Zc : strictStrings
#define QMAKE_CXXFLAGS -= -Zc : strictStrings

//==============================================================================
CApp::CApp()
{
    //Surf_Display = NULL;

    Running = true;
}


Uint32 CApp::time_left(void)
{
    Uint32 now;

    now = SDL_GetTicks();
    if(next_time <= now)
        return 0;
    else
        return next_time - now;
}

void CApp::restartGame(){
    arrowPerRow = 2;
    numPlatform = 4;
    numCaves = 4;
    currentLevel = 1;
    lives = 5;
    currentStatus = GAME;
    touchedBridge = false;
    bridgeIsMoved = false;
    initialDraw();
}

void CApp::loseLife(){
    lives--;
    if(lives == 0){
        Mix_PlayChannel(-1,gameOver.sfx,0);
        currentStatus = GAME_OVER;
    }
    touchedBridge = false;
    bridgeIsMoved = false;
    initialDraw();
}




void CApp::nextLevel()
{
    bridgeIsMoved = false;
    touchedBridge = false;
    currentLevel++;
    if(currentLevel == 1){
        arrowPerRow = 2;
        numPlatform = 4;
        numCaves = 4;
        Mix_PlayChannel(-1,gameTitle.sfx,0);
    }else if(currentLevel == 2){
        arrowPerRow = 2;
        numPlatform = 3;
        numCaves = 3;
        Mix_PlayChannel(-1,gameTitle.sfx,0);
    }else if(currentLevel == 3){
        arrowPerRow = 3;
        numPlatform = 3;
        numCaves = 3;
        Mix_PlayChannel(-1,gameTitle.sfx,0);
    }else if(currentLevel == 4){
        arrowPerRow = 3;
        numPlatform = 2;
        numCaves = 2;
        Mix_PlayChannel(-1,gameTitle.sfx,0);
    }else if(currentLevel == 5){
        arrowPerRow = 3;
        numPlatform = 1;
        numCaves = 1;
        Mix_PlayChannel(-1,gameTitle.sfx,0);
    }else{
        currentStatus = WIN;
        Mix_PlayChannel(-1,win.sfx,0);
    }
    initialDraw();
}



int
CApp::LoadSprite(char *file, SDL_Texture **psprite, SDL_Rect *prect)
{
    SDL_Surface *temp;

    /* Load the sprite image */
    temp = SDL_LoadBMP(file);
    if (temp == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s", file, SDL_GetError());
        return (-1);
    }
    prect->w = temp->w;
    prect->h = temp->h;

    /* Set transparent pixel as the pixel at (0,0) */
    if (temp->format->palette)
    {
        SDL_SetColorKey(temp, SDL_TRUE, *(Uint8 *) temp->pixels);
    }
    else
    {
        switch (temp->format->BitsPerPixel)
        {
        case 15:
            SDL_SetColorKey(temp, SDL_TRUE,
                            (*(Uint16 *) temp->pixels) & 0x00007FFF);
            break;
        case 16:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint16 *) temp->pixels);
            break;
        case 24:
            SDL_SetColorKey(temp, SDL_TRUE,
                            (*(Uint32 *) temp->pixels) & 0x00FFFFFF);
            break;
        case 32:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint32 *) temp->pixels);
            break;
        }
    }

    /* Create textures from the image */
    *psprite = SDL_CreateTextureFromSurface(renderer, temp);
    if (!*psprite)
    {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return (-1);
    }
    SDL_FreeSurface(temp);

    /* We're ready to roll. :) */
    return (0);
}



//------------------------------------------------------------------------------
int CApp::OnExecute()
{
    if(OnInit() == false)
    {
        return -1;
    }

    SDL_Event Event;
    next_time = SDL_GetTicks() + TICK_INTERVAL;
    while(Running)
    {
        while(SDL_PollEvent(&Event))
        {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}

//==============================================================================
int main(int argc, char* argv[])
{
    CApp theApp;

    return theApp.OnExecute();
}

//==============================================================================
void CApp::displayGameStats(int x, int y, char* formattedString, int number){

    sprintf_s(message, formattedString, number);	 	//convert number to string, insert into formatted string
    messageSurface = TTF_RenderText_Solid(font,message, color);	//make text an image (an SDL_Surface)
    messageTexture = SDL_CreateTextureFromSurface(renderer,messageSurface);	//convert SDL_Surface to SDL_Texture

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(messageTexture, NULL, NULL, &texW, &texH);	//get width & height of texture
    messageRect = { x-texW, y, texW, texH };				//create a SDL_Rect for the message

    SDL_RenderCopy(renderer, messageTexture, NULL, &messageRect);	//copy it to screen
}


