#include "TextureManager.h"

TextureManager::TextureManager()
{
    texture = nullptr;
    width = 0;
    height = 0;
}

TextureManager::~TextureManager()
{
    Destroy();
}

void TextureManager::Destroy() {
    if (texture != nullptr) {
        texture = nullptr;
        width = 0;
        height = 0;
    }
}

bool TextureManager::LoadRenderText (std::string textureText, TTF_Font* font, SDL_Color textColor, SDL_Renderer* renderer) {
    Destroy();
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    if (textSurface == NULL) {
        std::cout << "Unable to render text surface! SDL_ttf Error: %s\n" << TTF_GetError() << std::endl;
    } else {
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (texture == NULL) {
            std::cout << "Unable to create texture from rendered text! SDL Error: %s\n" << SDL_GetError() << std::endl;
        } else {
            width = textSurface->w;
            height = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }

    return texture != NULL;
}

bool TextureManager::LoadFile(std::string path, SDL_Renderer *renderer) {
    Destroy();
    SDL_Texture* tmp_texture = nullptr;
    SDL_Surface* tmp_surface = IMG_Load(path.c_str());
    if (tmp_surface == nullptr)
    {
        LogError("Can not load image.", IMG_ERROR);
    }
    else
    {
        SDL_SetColorKey(tmp_surface, SDL_TRUE, SDL_MapRGB(tmp_surface->format, 0, 255, 255));

        tmp_texture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
        if (tmp_texture == nullptr)
        {
            std::cout << "IMG_Load failed for file: " << path << "\n";
            LogError("Can not create texture from surface.", SDL_ERROR);
            std::cout << "IMG_Load failed: " << IMG_GetError() << std::endl;
        }
        else
        {
            width = tmp_surface->w;
            height = tmp_surface->h;
        }

        SDL_FreeSurface(tmp_surface);
    }

    texture = tmp_texture;

    return texture != nullptr;
}

 void TextureManager::Render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip){
    SDL_Rect renderSpace = { x, y, width, height };

    if (clip != nullptr)
    {
        renderSpace.w = clip->w;
        renderSpace.h = clip->h;
    }

    SDL_RenderCopy(renderer, texture, clip, &renderSpace);
}

int TextureManager::GetWidth() {
    return width;
}
int TextureManager::GetHeight() {
    return height;
}

