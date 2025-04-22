#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "TextureManager.h"

#define OBSTACLE_GROUND_HEIGHT 300
#define OBSTACLE_SKY_HEIGHT 350

#define OBSTACLE_POSITION_RANGE 250

class Obstacle
{
    public:
        Obstacle(int _type = 0);

        ~Obstacle();
        void LoadFile(std::string path, SDL_Renderer* gRenderer);
        void Move(const int& speed);
        void Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip = nullptr);
        int GetType();
        int GetSpeed(const int& speed);
        int GetX();
        int GetY();
        int GetWidth();
        int GetHeight();
    private:
        int X, Y;

        int Width, Height;

        int type;

        SDL_Texture *ObstacleTexture;
};

#endif // OBSTACLE_H
