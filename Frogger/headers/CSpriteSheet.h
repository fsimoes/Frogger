#ifndef CSPRITESHEET_H
#define CSPRITESHEET_H

#include <SDL.h>
#include <string.h>

#define MAX_SPRITE_IMAGES 100
#include "CGameObject.h"

class CSpriteSheet : public CGameObject
{
    public:
         struct animationData{
                int num_of_images;
                int sx;
                int sy;
                int sw;
                int sh;
                int wx;
                int hy;
                int border;
                int frameRate;
            };
        animationData currentAnimation;
        char fname[255];
        int max_images;
        int cur_image;
        int frameRate;
        int frameCounter;
        SDL_Rect images[MAX_SPRITE_IMAGES];
        CSpriteSheet();

        virtual ~CSpriteSheet();

        void set_sheet( char n[]) { strncpy_s(fname,n,255); }

        void config_sheet(animationData aniData);
        void setCurrentAnimation(int num_of_images, int sx, int sy, int sw, int sh, int wx, int hy, int border, int frameRate);
        void play(SDL_Renderer *r);
        void rewind() {  cur_image = 0; }
    protected:
    private:
        SDL_Surface *ps;
};

#endif // CSPRITESHEET_H
