#include "Cat.h"

Cat::Cat()
{
	X = 300;
	Y = GROUND;

	status = 0;
}

bool Cat::OnGround()
{
	return Y == GROUND;
}

void Cat::HandleEvent(SDL_Event& gEvent, Mix_Chunk *gJump)
{
	if (gEvent.type == SDL_KEYDOWN && gEvent.key.repeat == 0)
	{
		switch (gEvent.key.keysym.sym)
		{
			case SDLK_UP:
			{
				if (OnGround())
				{
					Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
					status = JUMP;
				}
			}
		}
	}

    if (gEvent.type == SDL_MOUSEBUTTONDOWN && gEvent.button.button == SDL_BUTTON_LEFT)
    {
        if (OnGround())
        {
            Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
            status = JUMP;
        }
    }
}

void Cat::Move()
{
	if (status == JUMP && Y >= MAX_HEIGHT)
	{
		Y += -JUMP_SPEED;
	}
	if (Y <= MAX_HEIGHT)
	{
		status = FALL;
	}
	if (status == FALL && Y < GROUND)
	{
		Y += FALL_SPEED;
	}
}

void Cat::Render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, TextureManager gTextureManager)
{
	gTextureManager.Render(X, Y, gRenderer, currentClip);
}

int Cat::GetX()
{
	return X;
}

int Cat::GetY()
{
	return Y;
}
