#include "../headers/CSpriteSheet.h"
#include <stdio.h>
CSpriteSheet::CSpriteSheet()
{
    //ctor
    cur_image = 0;
}

CSpriteSheet::~CSpriteSheet()
{
    //dtor
}

/*
    int num_of_images    How many images to extract from texture
     int sx,             Start image x loc in texture
      int sy,            Start image y loc in texture
       int sw,           Width of ONE image in texture
        int sh,          Height of ONE image in texture
         int wx,         How many images on ONE row
          int hy,        How many rows of images on texture
           int border    How many pixels between images

    Note: Images are not really extracted... locations are saved to allow quick display...

*/

void CSpriteSheet::config_sheet(animationData ad)
{
    SDL_Rect *pr;
    int curx,cury;
    int working_rec = 0;
    int working_row = 1;
    int working_col = 1;

    curx = ad.sx;
    cury = ad.sy;
    while (working_rec<ad.num_of_images && working_row <= ad.hy)
    {
        pr = &images[working_rec];
        pr->x = curx;
        pr->y = cury;
        pr->w = ad.sw;
        pr->h = ad.sh;
        working_col++;
        working_rec++;
        curx += ad.sw + ad.border;
        if (working_col>ad.wx)
        {
            working_row++;
            working_col = 1;
            cury += ad.sh + ad.border;
            curx = ad.sx;
        }

    }
    max_images = ad.num_of_images;
    rect.h = pr->h;
    rect.w = pr->w;
    frameRate = ad.frameRate;
    setColisionRect(rect.x,rect.y,ad.sw,ad.sh);
}

void CSpriteSheet::setCurrentAnimation(int num_of_images, int sx, int sy, int sw, int sh, int wx, int hy, int border, int frameRate){
    animationData ad = {num_of_images, sx, sy, sw, sh, wx, hy, border, frameRate};

    config_sheet(ad);
}
/*
    Display the Sprite (current position) to the screen
    and optionally move to next image....

*/
void CSpriteSheet::play(SDL_Renderer *r)
{
    if(currentDirection == LEFT){
        SDL_RenderCopyEx(r, texture, &images[cur_image], &rect, NULL, NULL, SDL_FLIP_HORIZONTAL);
    }else{
        SDL_RenderCopy(r,texture,&images[cur_image],&rect);
    }



    if(frameCounter%frameRate == 0){
        cur_image++;
        if (cur_image>=max_images)
            cur_image = 0;
    }
    frameCounter++;
}
