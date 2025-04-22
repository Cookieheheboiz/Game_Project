#ifndef DONUT_H
#define DONUT_H
#include "TextureManager.h"
#define DONUT_POSITION_RANGE 250
class Donut
{
    public:
        Donut();
        ~Donut();

        void LoadFile(std::string path, SDL_Renderer* renderer);
        void Move(const int& acceleration);
        void Render(SDL_Renderer* renderer, SDL_Rect* currentClip = nullptr);
        void Reset();
        int GetSpeed(const int& speed);
        int GetX();
        int GetY();
        int GetWidth();
        int GetHeight();
        bool IsCollected() const;
        void SetCollected(bool collected);


    private:
        int X, Y;
        int food_width, food_height;
        SDL_Texture *FoodTexture;
        bool isActive; // Quả táo đang được hiện diện trên màn hình hay không
        int distanceTraveled; // Khoảng cách đã đi được (pixel)
        bool isCollected;

};

#endif // DONUT_H
