#ifndef CAT_H
#define CAT_H

#include "TextureManager.h"

#define JUMP 1
#define FALL 2
#define RUN	0

class Cat
{
public:
	static const int JUMP_SPEED = 7;
	static const int FALL_SPEED = 7;

	Cat();

	bool OnGround();

	void HandleEvent(SDL_Event& gEvent, Mix_Chunk *gJump);

	void Move();

	void Render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, TextureManager gTextureManager);

	int GetX();

	int GetY();

private:
	int X, Y;

	int status;
};

#endif // CAT_H
