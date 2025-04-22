#include "Impact.h"

Impact::Impact()
{

}

bool Impact::CheckImpact(Cat cat, SDL_Rect* cat_clip, Obstacle obstacle, SDL_Rect* obstacle_clip) {
    bool collide = false;

	int left_a = cat.GetX();
	int right_a = cat.GetX() + cat_clip->w;
	int top_a = cat.GetY();
	int bottom_a = cat.GetY() + cat_clip->h;

	if (obstacle.GetType() == ON_GROUND_OBSTACLE)
	{
		const int TRASH_PIXEL_1 = 25;
		const int TRASH_PIXEL_2 = 30;

		int left_b = obstacle.GetX();
		int right_b = obstacle.GetX() + obstacle.GetWidth();
		int top_b = obstacle.GetY();


		if (right_a - TRASH_PIXEL_1 >= left_b && left_a + TRASH_PIXEL_1 <= right_b)
		{
			if (bottom_a - TRASH_PIXEL_2 >= top_b)
			{
				collide = true;
			}
		}
	}
	else
	{
		const int TRASH_PIXEL_1 = 22;
		const int TRASH_PIXEL_2 = 18;

		int left_b = obstacle.GetX() + TRASH_PIXEL_1;
		int right_b = obstacle.GetX() + obstacle_clip->w - TRASH_PIXEL_1;
		int top_b = obstacle.GetY();
		int bottom_b = obstacle.GetY() + obstacle_clip->h - TRASH_PIXEL_2;

		if (right_a >= left_b && left_a <= right_b)
		{
			if (top_a <= bottom_b && top_a >= top_b)
			{
				collide = true;
			}

			if (bottom_a >= bottom_b && bottom_a <= top_b)
			{
				collide = true;
			}
		}
	}

	return collide;
}

bool Impact::CheckObstacleImpact(Cat cat, Obstacle obstacle1, Obstacle obstacle2, Obstacle obstacle3, SDL_Rect* cat_clip, SDL_Rect* obstacle_clip)
{

	if (CheckImpact(cat, cat_clip, obstacle1))
	{
		return true;
	}
	if (CheckImpact(cat, cat_clip, obstacle2))
	{
		return true;
	}
	if (CheckImpact(cat, cat_clip, obstacle3, obstacle_clip))
	{
		return true;
	}
	return false;
}
