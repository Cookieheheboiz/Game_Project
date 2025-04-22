#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "BasicPart.h"

class TextureManager
{
    public:
        TextureManager();
        ~TextureManager();
        void Destroy();

       bool LoadFile (std::string path, SDL_Renderer* renderer);
       void Render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = nullptr);
       bool LoadRenderText (std::string textureText, TTF_Font* font, SDL_Color textColor, SDL_Renderer* renderer);
       int GetWidth();
       int GetHeight();

    private:
        SDL_Texture* texture;
        int width;
        int height;
};

#endif // TEXTUREMANAGER_H
