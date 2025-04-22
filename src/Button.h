#ifndef BUTTON_H
#define BUTTON_H

#include "TextureManager.h"


class Button
{
public:
    ButtonSprite currentSprite;

    Button();

    Button(int x, int y);

    void SetPosition(int x, int y);

    bool IsInside(SDL_Event *e, int size);

    void Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, TextureManager gButtonTextureManager);

private:
    SDL_Point position;
};

#endif // BUTTON_H
