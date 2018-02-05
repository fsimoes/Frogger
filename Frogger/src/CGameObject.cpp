#include "../headers/CGameObject.h"

int CGameObject::load(SDL_Renderer *renderer)
{
    SDL_Surface *temp;

    /* Load the sprite image */
    temp = SDL_LoadBMP(imagename);
    if (temp == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s", imagename, SDL_GetError());
        return (-1);
    }
    rect.w = temp->w;
    rect.h = temp->h;
    colisionRect.w = temp->w;
    colisionRect.h = temp->h;

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
    texture = SDL_CreateTextureFromSurface(renderer, temp);
    if (!texture)
    {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return (-1);
    }
    SDL_FreeSurface(temp);

    /* We're ready to roll. :) */
    return (0);
}

void CGameObject::display(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void CGameObject::setDirection(DIRECTION direction)
{
    currentDirection = direction;

}
void CGameObject::setPosition(int x, int y)
{
    rect.x = x;
    rect.y = y;
    colisionRect.x = x;
    colisionRect.y = y;
}

void CGameObject::setColisionRect(int x, int y, int w, int h)
{
    colisionRect.x = x;
    colisionRect.y = y;
    colisionRect.h = h;
    colisionRect.w = w;
}

bool CGameObject::collisionTest(CGameObject &go){
        colisionRect.x = rect.x;
        colisionRect.y = rect.y;
        // check if there is any collision between two objects
        bool colistionState = false;
        // check if the x of the item 1 is inside the range of item 2 x;
        if(colisionRect.x + colisionRect.w> go.colisionRect.x && colisionRect.x < go.colisionRect.x + go.colisionRect.w ){
         // check if the y of the item 1 is inside the range of item 2 y;
            if(colisionRect.y + colisionRect.h > go.colisionRect.y && colisionRect.y < go.colisionRect.y + go.colisionRect.h ){
                //check if the collision is happening on the center or on the sides
                colistionState = true;
            }
        }
        //Return Collision State
       // isColliding = colistionState;
        return colistionState;
    };

