#include "Logic_In_Game.h"

std::string GetHighScore(std::string path) {
    std::fstream ScoreFile;
    std::string highscore;

    ScoreFile.open(path, std::ios::in);
    ScoreFile >> highscore;

    return highscore;

}

void UpdateHighScore(std::string path, const int& score, const std::string& prev_high_score) {
    int prevHighScore = 0;
    std::fstream ScoreFile;
    std::string newHighScore;
    std::stringstream ConvertToInt(prev_high_score);

    ScoreFile.open(path, std::ios::out);

    ConvertToInt >> prevHighScore;
    if (score > prevHighScore)
    {
        prevHighScore = score;
    }
    newHighScore = std::to_string(prevHighScore);

    ScoreFile << newHighScore;
}

int UpdateGameTimeAndScore(int& time, int& speed, int& score) {
    int TIME_MAXX = 1000;
    if (time == TIME_MAXX)
    {
        speed += SPEED_INCREASEMENT;
        TIME_MAXX += 1000;
    }

    if (time % 5 == 0)
    {
        score += SCORE_INCREASEMENT;
    }

    time += TIME_INCREASEMENT;

    return time;
}

void RenderScrollingBackground(std::vector <double>& offsetSpeed, TextureManager(&gBackgroundTextureManager)[BACKGROUND_LAYER], SDL_Renderer* gRenderer) {
    std::vector <double> layer_speed;
    layer_speed.push_back(LAYER_1_SPEED);
    layer_speed.push_back(LAYER_2_SPEED);
    layer_speed.push_back(LAYER_3_SPEED);
    layer_speed.push_back(LAYER_4_SPEED);
    layer_speed.push_back(LAYER_5_SPEED);

    for (int i = 0; i < BACKGROUND_LAYER; ++i)
    {
        offsetSpeed[i] -= layer_speed[i];
        if (offsetSpeed[i] < -gBackgroundTextureManager[i].GetWidth())
        {
            offsetSpeed[i] = 0;
        }
        gBackgroundTextureManager[i].Render(offsetSpeed[i], 0, gRenderer);
        gBackgroundTextureManager[i].Render(offsetSpeed[i] + gBackgroundTextureManager[i].GetWidth(), 0, gRenderer);
    }
}

void RenderScrollingGround(int& speed, const int acceleration, TextureManager gGroundTextureManager, SDL_Renderer* gRenderer) {
    speed -= GROUND_SPEED + acceleration;
    if (speed < -gGroundTextureManager.GetWidth())
    {
        speed = 0;
    }
    gGroundTextureManager.Render(speed, 0, gRenderer);
    gGroundTextureManager.Render(speed + gGroundTextureManager.GetWidth(), 0, gRenderer);
}

void HandlePlayButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu, bool& Play, Mix_Chunk* gClick) {
    if (e->type == SDL_QUIT) {
        QuitMenu = true;
    }

    if (PlayButton.IsInside(e, COMMON_BUTTON)) {
        switch (e->type) {
        case SDL_MOUSEMOTION:
            PlayButton.currentSprite = BUTTON_MOUSE_OVER;
            break;
        case SDL_MOUSEBUTTONDOWN:
            Play = true;
            QuitMenu = true;
            Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
            PlayButton.currentSprite = BUTTON_MOUSE_OVER;
            break;
        }
    }
    else {
        PlayButton.currentSprite = BUTTON_MOUSE_OUT;
    }
}

void HandleHelpButton(SDL_Event* e, SDL_Rect(&gBackButton)[BUTTON_TOTAL], Button& HelpButton, Button& BackButton, TextureManager gInstructionTextureManager, TextureManager gBackButtonTextureManager, SDL_Renderer *gRenderer, bool &Quit_game, Mix_Chunk *gClick) {
    if (HelpButton.IsInside(e, COMMON_BUTTON)) {
        switch (e->type)
        {
        case SDL_MOUSEMOTION:
            HelpButton.currentSprite = BUTTON_MOUSE_OVER;
            break;
        case SDL_MOUSEBUTTONDOWN:
            HelpButton.currentSprite = BUTTON_MOUSE_OVER;
            Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);

            bool ReadDone = false;
            while (!ReadDone)
            {
                do
                {
                    if (e->type == SDL_QUIT)
                    {
                        ReadDone = true;
                        Quit_game = true;
                        Close();
                    }

                    else if (BackButton.IsInside(e, COMMON_BUTTON))
                    {
                        switch (e->type)
                        {
                        case SDL_MOUSEMOTION:
                            BackButton.currentSprite = BUTTON_MOUSE_OVER;
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            BackButton.currentSprite = BUTTON_MOUSE_OVER;
                            Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
                            ReadDone = true;
                            break;
                        }
                    }
                    else
                    {
                        BackButton.currentSprite = BUTTON_MOUSE_OUT;
                    }

                    gInstructionTextureManager.Render(0, 0, gRenderer);

                    SDL_Rect* currentClip_Back = &gBackButton[BackButton.currentSprite];
                    BackButton.Render(currentClip_Back, gRenderer, gBackButtonTextureManager);

                    SDL_RenderPresent(gRenderer);
                }
                while ((SDL_PollEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN) || e->type == SDL_MOUSEMOTION);
            }
            break;
        }
    }
    else
    {
        HelpButton.currentSprite = BUTTON_MOUSE_OUT;
    }
}

void HandleExitButton(SDL_Event* e, Button& ExitButton, bool& Quit, Mix_Chunk* gClick) {
    if (ExitButton.IsInside(e, COMMON_BUTTON)) {
        switch (e->type) {
        case SDL_MOUSEMOTION:
            ExitButton.currentSprite = BUTTON_MOUSE_OVER;
            break;
        case SDL_MOUSEBUTTONDOWN:
            Quit = true;
            ExitButton.currentSprite = BUTTON_MOUSE_OVER;
            Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
            break;
        }
    } else {
        ExitButton.currentSprite = BUTTON_MOUSE_OUT;
    }
}

void HandleContinueButton(Button ContinueButton, TextureManager gContinueButtonTextureManager, SDL_Event& e, SDL_Renderer* gRenderer, SDL_Rect(&gContinueButton)[BUTTON_TOTAL], bool& Game_State, Mix_Chunk* gClick)
{
    bool Back_To_Game = false;
    while (!Back_To_Game)
    {
        do
        {
            if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && Game_State == false)
            {
                switch (e.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                    {
                        Game_State = true;
                        Back_To_Game = true;
                        ContinueButton.currentSprite = BUTTON_MOUSE_OVER;
                        Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
                        Mix_ResumeMusic();
                    }
                    case SDLK_c:
                    {
                        Game_State = true;
                        Back_To_Game = true;
                        ContinueButton.currentSprite = BUTTON_MOUSE_OVER;
                        Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
                        Mix_ResumeMusic();
                    }
                }
            }

            SDL_Rect* currentClip_Continue = &gContinueButton[ContinueButton.currentSprite];
            ContinueButton.Render(currentClip_Continue, gRenderer, gContinueButtonTextureManager);

            SDL_RenderPresent(gRenderer);
        }
        while (SDL_WaitEvent(&e) != 0 && e.type == SDL_KEYDOWN);
    }
}

void HandlePauseButton(SDL_Event& e, SDL_Renderer* gRenderer, SDL_Rect (&gContinueButton)[BUTTON_TOTAL], Button& PauseButton, Button ContinueButton, TextureManager gContinueButtonTextureManager, bool &Game_State, Mix_Chunk *gClick)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && Game_State == true )
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            {
            PauseButton.currentSprite = BUTTON_MOUSE_OVER;
            Game_State = false;
            HandleContinueButton(ContinueButton, gContinueButtonTextureManager, e, gRenderer, gContinueButton, Game_State, gClick);
            Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
            Mix_PauseMusic();
            break;
            }
        case SDLK_p:
            {
            PauseButton.currentSprite = BUTTON_MOUSE_OVER;
            Game_State = false;
            HandleContinueButton(ContinueButton, gContinueButtonTextureManager, e, gRenderer, gContinueButton, Game_State, gClick);
            Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
            Mix_PauseMusic();
            break;
            }
        }
    }
    PauseButton.currentSprite = BUTTON_MOUSE_OUT;
}

void GenerateObstacle(Obstacle& obstacle1, Obstacle& obstacle2, Obstacle& obstacle3, SDL_Rect(&gObstacleClips)[FLYING_FRAMES], SDL_Renderer * gRenderer)
{
    obstacle1.LoadFile("image/enemy/Rock.png", gRenderer);
    obstacle2.LoadFile("image/enemy/Rock.png", gRenderer);
    obstacle3.LoadFile("image/enemy/Bird.png", gRenderer);
    {

        for (int i = 0; i < 5; i++) {
            gObstacleClips[i].x = 76.6 * i;
            gObstacleClips[i].y = 0;
            gObstacleClips[i].w = 76.6;
            gObstacleClips[i].h = 64;
        }

    }
}

void GenerateDonut(Donut& donut, SDL_Rect(&gDonutClips)[DONUT_FRAMES], SDL_Renderer* gRenderer)
{
    donut.LoadFile("image/enemy/result_fish.png", gRenderer);
    {
        gDonutClips[0].x = 72 * 0;
        gDonutClips[0].y = 0;
        gDonutClips[0].w = 72;
        gDonutClips[0].h = 41;

        gDonutClips[1].x = 72 * 1;
        gDonutClips[1].y = 0;
        gDonutClips[1].w = 72;
        gDonutClips[1].h = 41;
    }
}

bool CheckImpact(Cat cat, SDL_Rect* cat_clip, Obstacle obstacle, SDL_Rect* obstacle_clip)
{
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
    else if (obstacle.GetType() == IN_AIR_OBSTACLE)
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

bool CheckImpact2(Cat cat_, SDL_Rect* cat_clip_,
                  Donut donut_,
                  SDL_Rect* donut_clip_ )
{
    int left_a = cat_.GetX();
    int right_a = left_a + cat_clip_->w;
    int top_a = cat_.GetY();
    int bottom_a = top_a + cat_clip_->h;

    int left_b = donut_.GetX();
    int right_b = left_b + donut_clip_->w;
    int top_b = donut_.GetY();
    int bottom_b = top_b + donut_clip_->h;

    // Rect A intersects Rect B
    if (right_a > left_b &&
        left_a < right_b &&
        bottom_a > top_b &&
        top_a < bottom_b)
    {
        return true;
    }

    return false;
}


bool CheckDonutImpact(Cat cat, Donut donut, SDL_Rect* cat_clip_, SDL_Rect* donut_clip_)
{
    if (CheckImpact2(cat, cat_clip_, donut, donut_clip_))
    {
        return true;
    }
    return false;
}

bool CheckObstacleImpact(Cat cat, Obstacle obstacle1, Obstacle obstacle2, Obstacle obstacle3, SDL_Rect* cat_clip, SDL_Rect* obstacle_clip)
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

void ControlCatFrame(int &frame)
{
    frame += FRAME_INCREASEMENT;
    if (frame / SLOW_FRAME_CAT >= RUNNING_FRAMES)
    {
        frame = 0;
    }
}

void ControlObstacleFrame(int &frame)
{
    frame += FRAME_INCREASEMENT;
    if (frame / SLOW_FRAME_OBSTACLE >= FLYING_FRAMES)
    {
        frame = 0;
    }
}

void ControlDonutFrame(int& frame, bool check, int location)
{
    if (check == true)
    {
        frame = 1;
    }
    if (location < -50)
    {
        frame = 0;
    }

}


void DrawPlayerScore(TextureManager gTextTextureManager, TextureManager gScoreTextureManager, SDL_Color textColor, SDL_Renderer *gRenderer, TTF_Font *gFont, const int& score)
{
    gTextTextureManager.Render(TEXT_1_POSX, TEXT_1_POSY, gRenderer);
    if (gScoreTextureManager.LoadRenderText(std::to_string(score), gFont, textColor, gRenderer))
    {
        gScoreTextureManager.Render(SCORE_POSX, SCORE_POSY, gRenderer);
    }
}

void DrawPlayerHighScore(TextureManager gTextTextureManager, TextureManager gHighScoreTextureManager, SDL_Color textColor, SDL_Renderer* gRenderer, TTF_Font* gFont, const std::string& HighScore)
{
    gTextTextureManager.Render(TEXT_2_POSX, TEXT_2_POSY, gRenderer);
    if (gHighScoreTextureManager.LoadRenderText(HighScore, gFont, textColor, gRenderer))
    {
        gHighScoreTextureManager.Render(HIGH_SCORE_POSX, HIGH_SCORE_POSY, gRenderer);
    }
}

void DrawEndGameSelection(TextureManager gLoseTextureManager, SDL_Event *e, SDL_Renderer *gRenderer, bool &Play_Again)
{
    if (Play_Again)
    {
        bool End_Game = false;
        while (!End_Game)
        {
            while (SDL_PollEvent(e) != 0)
            {
                if (e->type == SDL_QUIT)
                {
                    Play_Again = false;
                }

                if (e->type == SDL_KEYDOWN)
                {
                    switch (e->key.keysym.sym)
                    {
                    case SDLK_SPACE:
                        End_Game = true;
                        break;
                    case SDLK_ESCAPE:
                        End_Game = true;
                        Play_Again = false;
                        break;
                    }
                }
            }

            gLoseTextureManager.Render(0, 0, gRenderer);

            SDL_RenderPresent(gRenderer);
        }
    }
}







