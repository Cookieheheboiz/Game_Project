#include "Obstacle.h"

Obstacle::Obstacle(int _type)
{
    X = 0;
    Y = 0;

    Width = 0;
    Height = 0;

    type = _type;
    if (type == IN_AIR_OBSTACLE)
    {
        X = rand() % (SCREEN_WIDTH + OBSTACLE_POSITION_RANGE) + SCREEN_WIDTH;
        Y = 330;
    }
    else if (type == ON_GROUND_OBSTACLE)
    {
        X = rand() % (SCREEN_WIDTH + OBSTACLE_POSITION_RANGE) + SCREEN_WIDTH;
        Y = GROUND - 8;
    }

    ObstacleTexture = nullptr;
}

Obstacle::~Obstacle()
{
    X = 0;
    Y = 0;

    Width = 0;
    Height = 0;

    type = 0;
    if (ObstacleTexture != nullptr)
    {
        ObstacleTexture = nullptr;
    }
}

void Obstacle::LoadFile(std::string path, SDL_Renderer* gRenderer)
{
    SDL_Texture* tmpTexture = nullptr;

    SDL_Surface* tmpSurface = IMG_Load(path.c_str());
    if (tmpSurface == nullptr)
    {
        LogError("Can not load image.", IMG_ERROR);
    }
    else
    {
        SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));

        tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
        if (tmpTexture == nullptr)
        {
            LogError("Can not create texture from surface.", SDL_ERROR);
        }
        else
        {
            Width = tmpSurface->w;
            Height = tmpSurface->h;
        }

        SDL_FreeSurface(tmpSurface);
    }

    ObstacleTexture = tmpTexture;
}

void Obstacle::Move(const int &speed)
{
    X += -(OBSTACLE_SPEED + speed);
    if (X + MAX_OBSTACLE_WIDTH < 0)
    {
        X = rand() % (SCREEN_WIDTH + OBSTACLE_POSITION_RANGE) + SCREEN_WIDTH;

        if (type == IN_AIR_OBSTACLE)
        {
            Y = 330;
        }
    }
}

void Obstacle::Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip)
{
    SDL_Rect renderSpace = {X, Y, Width, Height};
    if (currentClip != nullptr)
    {
        renderSpace.w = currentClip->w;
        renderSpace.h = currentClip->h;
    }
    SDL_RenderCopy(gRenderer, ObstacleTexture, currentClip, &renderSpace);
}

int Obstacle::GetType()
{
    if (type == IN_AIR_OBSTACLE)
    {
        return IN_AIR_OBSTACLE;
    }
        return ON_GROUND_OBSTACLE;

}

int Obstacle::GetSpeed(const int &speed)
{
    return OBSTACLE_SPEED + speed;
}

int Obstacle::GetX()
{
    return X;
}

int Obstacle::GetY()
{
    return Y;
}

int Obstacle::GetWidth()
{
    return Width;
}

int Obstacle::GetHeight()
{
    return Height;
}
