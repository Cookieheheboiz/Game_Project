#include "Donut.h"



Donut::Donut()
{
    X = 0;
    Y = 0;

    food_width = 0;
    food_height = 0;

        X = rand() % (SCREEN_WIDTH + DONUT_POSITION_RANGE) + SCREEN_WIDTH;
        Y = 520;

    FoodTexture = nullptr;
    distanceTraveled = 0;
    isActive = true;
    isCollected = false;
}

Donut::~Donut()
{
    X = 0;
    Y = 0;

    food_width = 0;
    food_height = 0;

    if (FoodTexture != nullptr)
    {
        FoodTexture = nullptr;
    }
}

void Donut::LoadFile(std::string path, SDL_Renderer* renderer)
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

        tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
        if (tmpTexture == nullptr)
        {
            LogError("Can not create texture from surface.", SDL_ERROR);
        }
        else
        {
            food_width = tmpSurface->w;
            food_height = tmpSurface->h;
        }

        SDL_FreeSurface(tmpSurface);
    }

    FoodTexture = tmpTexture;
}

void Donut::Move(const int& acceleration)
{
    X += -(OBSTACLE_SPEED + acceleration);
    if (X + MAX_OBSTACLE_WIDTH < 0) {
        X = rand() % (SCREEN_WIDTH + DONUT_POSITION_RANGE) + SCREEN_WIDTH;
        Y = 520;
        isCollected = false;
    }
}

void Donut::Reset() {
    X = rand() % (SCREEN_WIDTH + DONUT_POSITION_RANGE) + SCREEN_WIDTH;
    Y = 520;
}

void Donut::Render(SDL_Renderer* renderer, SDL_Rect* currentClip)
{
    SDL_Rect renderSpace = { X, Y, food_width, food_height };
    if (currentClip != nullptr)
    {
        renderSpace.w = currentClip->w;
        renderSpace.h = currentClip->h;
    }
    SDL_RenderCopy(renderer, FoodTexture, currentClip, &renderSpace);
}

int Donut::GetSpeed(const int &acceleration)
{
    return OBSTACLE_SPEED + acceleration;
}



int Donut::GetX()
{
    return X;
}

int Donut::GetY()
{
    return Y;
}

int Donut::GetWidth()
{
    return food_width;
}

int Donut::GetHeight()
{
    return food_height;
}
bool Donut::IsCollected() const {
    return isCollected;
}

void Donut::SetCollected(bool collected) {
    isCollected = collected;
}
