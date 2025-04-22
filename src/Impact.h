#ifndef IMPACT_H
#define IMPACT_H

#include "BasicPart.h"
#include "Cat.h"
#include "Button.h"
#include "Obstacle.h"
#include "Logic_In_Game.h"

class Impact
{
    public:
        Impact();
        ~Impact();

    bool res;

    bool CheckImpact(Cat cat,
    SDL_Rect* cat_clip,
    Obstacle obstacle,
    SDL_Rect* obstacle_clip = nullptr);

    bool CheckObstacleImpact(Cat cat,
    Obstacle obstacle1,
    Obstacle obstacle2,
    Obstacle obstacle3,
    SDL_Rect* cat_clip,
    SDL_Rect* obstacle_clip = nullptr);
};

#endif // IMPACT_H
