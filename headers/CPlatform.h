#ifndef PLATFORM_HEADER
#define PLATFORM_HEADER


#include "CSpriteSheet.h"


class Platform : public CSpriteSheet
{
    public:

        int speed = 1;
        Platform();
        virtual ~Platform();
        void move();
        void reposition();
    protected:
    private:
};

#endif // PLATFORM_HEADER
