#include "BasicPart.h"
#include "Cat.h"
#include "Heart.h"
#include "Impact.h"
#include "Obstacle.h"
#include "Button.h"
#include "TextureManager.h"
#include "Donut.h"
#include "Logic_In_Game.h"

const std::string BACKGROUND[BACKGROUND_LAYER] = {
    "image/Background/result_Layer2.png",
    "image/Background/result_Layer2.png",
    "image/Background/result_Layer2.png",
    "image/Background/result_Layer2.png",
    "image/Background/result_Layer2.png"
};

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Color textColor = { 255, 255, 255 };
SDL_Color textColor2 = { 170, 0, 0 };
TTF_Font* gFont = nullptr;
TTF_Font* gFont2 = nullptr;
Mix_Music* gMusic = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClick = nullptr;
Mix_Chunk* gJump = nullptr;
Mix_Chunk* gLose = nullptr;

SDL_Rect gPlayButton[BUTTON_TOTAL];
SDL_Rect gHelpButton[BUTTON_TOTAL];
SDL_Rect gExitButton[BUTTON_TOTAL];
SDL_Rect gBackButton[BUTTON_TOTAL];
SDL_Rect gPauseButton[BUTTON_TOTAL];
SDL_Rect gContinueButton[BUTTON_TOTAL];
SDL_Rect gPlayAgainButton[BUTTON_TOTAL];
SDL_Rect gCatClips[RUNNING_FRAMES];
SDL_Rect gObstacleClips[FLYING_FRAMES];
SDL_Rect gDonutClips[DONUT_FRAMES];

TextureManager gMenuTextureManager;
TextureManager gInstructionTextureManager;
TextureManager gBackgroundTextureManager[BACKGROUND_LAYER];
TextureManager gCatTextureManager;
TextureManager gHeartTextureManager;
TextureManager gGroundTextureManager;
TextureManager gPlayButtonTextureManager;
TextureManager gHelpButtonTextureManager;
TextureManager gExitButtonTextureManager;
TextureManager gBackButtonTextureManager;
TextureManager gPauseButtonTextureManager;
TextureManager gContinueButtonTextureManager;
TextureManager gLoseTextureManager;
TextureManager gText1TextureManager;
TextureManager gScoreTextureManager;
TextureManager gText2TextureManager;
TextureManager gHighScoreTextureManager;
TextureManager gText3TextureManager;


Button PlayButton(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
Button HelpButton(HELP_BUTTON_POSX, HELP_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button BackButton(BACK_BUTTON_POSX, BACK_BUTTON_POSY);
Button PauseButton(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
Button ContinueButton(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY);


Cat cat;


int main(int argc, char* args[]) {
    if (!Init()) {
        std::cout << "Failed to initialize!" << std::endl;
    } else {
        std::cout << "success to initiallize!" << std::endl;
        if(!LoadMedia()) {
            std::cout << "Failed to load media" << std::endl;
        } else {
            std::cout << "success to load media!" << std::endl;
            bool Quit_Menu = false;
            bool Play_Again = false;

            Mix_PlayMusic(gMenuMusic, IS_REPEATITIVE);
            while (!Quit_Menu) {
                SDL_Event e_mouse;
                bool Quit_Game = false;
                while (SDL_PollEvent(&e_mouse) != 0) {
                    if (e_mouse.type == SDL_QUIT) {
                        Quit_Menu = true;
                    }

                    HandlePlayButton(&e_mouse, PlayButton, Quit_Menu, Play_Again, gClick);
                    HandleHelpButton(&e_mouse, gBackButton, HelpButton, BackButton, gInstructionTextureManager, gBackButtonTextureManager, gRenderer, Quit_Game, gClick);
                    HandleExitButton(&e_mouse, ExitButton, Quit_Menu, gClick);
                    if (Quit_Game == true) {
                        return 0;
                    }
                }

                gMenuTextureManager.Render(0, 0, gRenderer);
                SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
                PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTextureManager);

                SDL_Rect* currentClip_Help = &gHelpButton[HelpButton.currentSprite];
                HelpButton.Render(currentClip_Help, gRenderer, gHelpButtonTextureManager);

                SDL_Rect* currentClip_Exit = &gExitButton[ExitButton.currentSprite];
                ExitButton.Render(currentClip_Exit, gRenderer, gExitButtonTextureManager);

                SDL_RenderPresent(gRenderer);


            }
            bool isMuted = false;

            while (Play_Again) {
                srand(time(NULL));
                int time = 0;
                int score = 0;
                int acceleration = 0;
                int frame_Cat = 0;
                int frame_Obstacle = 0;
                int frame_Donut = 0;
                std::string highscore = GetHighScore("high_score.txt");

                SDL_Event e;
                Obstacle obstacle1(ON_GROUND_OBSTACLE);
                Obstacle obstacle2(ON_GROUND_OBSTACLE);
                Obstacle obstacle3(IN_AIR_OBSTACLE);

                Donut donut;

                Mix_PlayMusic(gMusic, IS_REPEATITIVE);
                GenerateObstacle(obstacle1, obstacle2, obstacle3, gObstacleClips, gRenderer);
                GenerateDonut(donut, gDonutClips, gRenderer);

                int OffsetSpeed_Ground = BASE_SPEED;
                std::vector<double> OffsetSpeed_BackGround(BACKGROUND_LAYER, BASE_SPEED);

                bool Quit = false;
                bool Game_State = true;

                int HP = 1;
                int frame_count = 0;
                while (!Quit) {
                    if (Game_State) {
                        UpdateGameTimeAndScore(time, acceleration, score);
                        while (SDL_PollEvent(&e) != 0) {
                            if (e.type == SDL_QUIT) {
                                Quit = true;
                                Play_Again = false;

                            }

                            if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
                                if (e.key.keysym.sym == SDLK_m) {
                                    if (isMuted) {
                                        Mix_ResumeMusic();
                                        isMuted = false;
                                        std::cout << "Music resumed.\n";
                                    } else {
                                        Mix_PauseMusic();
                                        isMuted = true;
                                        std::cout << "Music paused.\n";
                                    }
                                }
                            }

                            HandlePauseButton(e, gRenderer, gContinueButton, PauseButton, ContinueButton, gContinueButtonTextureManager, Game_State, gClick);
                            cat.HandleEvent(e, gJump);

                        }
                        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                        SDL_RenderClear(gRenderer);

                        RenderScrollingBackground(OffsetSpeed_BackGround, gBackgroundTextureManager, gRenderer);
                        RenderScrollingGround(OffsetSpeed_Ground, acceleration, gGroundTextureManager, gRenderer);

                        cat.Move();
                        SDL_Rect* currentClip_Cat = nullptr;
                        if (cat.OnGround()) {
                            currentClip_Cat = &gCatClips[frame_Cat / SLOW_FRAME_CAT];
                            cat.Render(currentClip_Cat, gRenderer, gCatTextureManager);
                        } else {
                            currentClip_Cat = &gCatClips[0];
                            cat.Render(currentClip_Cat, gRenderer, gCatTextureManager);
                        }



                        obstacle1.Move(acceleration);
                        obstacle1.Render(gRenderer);

                        obstacle2.Move(acceleration);
                        obstacle2.Render(gRenderer);
                        SDL_Rect* currentClip_Obstacle = &gObstacleClips[frame_Obstacle / SLOW_FRAME_OBSTACLE];
                        obstacle3.Move(acceleration);
                        int frame = (frame_count / SLOW_FRAME_OBSTACLE) % FLYING_FRAMES;
                        obstacle3.Render(gRenderer, &gObstacleClips[frame]);

                        SDL_Rect*currentClip_Donut = &gDonutClips[frame_Donut];
                        donut.Move(acceleration);
                        donut.Render(gRenderer, currentClip_Donut);

                        SDL_Rect*currentClip_Pause = &gPauseButton[PauseButton.currentSprite];
                        PauseButton.Render(currentClip_Pause, gRenderer, gPauseButtonTextureManager);

                        DrawPlayerScore(gText1TextureManager, gScoreTextureManager, textColor, gRenderer, gFont, score);
                        DrawPlayerHighScore(gText2TextureManager, gHighScoreTextureManager, textColor, gRenderer, gFont, highscore);


                        if (CheckObstacleImpact(cat, obstacle1, obstacle2, obstacle3, currentClip_Cat, currentClip_Obstacle)) {
                            HP -= 1;
                            std::cout << HP << std::endl;
                            Mix_PlayChannel(MIX_CHANNEL, gLose, NOT_REPEATITIVE);
                        } else if (CheckDonutImpact(cat, donut, currentClip_Cat, currentClip_Donut) && !donut.IsCollected()) {
                            score += 100;
                            donut.SetCollected(true);
                            Mix_PlayChannel(MIX_CHANNEL, gLose, NOT_REPEATITIVE);
                        }

                        if (HP <= -1) {
                            Mix_PauseMusic();
                            UpdateHighScore("high_score.txt", score, highscore);
                            Quit = true;
                        }
                        SDL_RenderPresent(gRenderer);
                        frame_count++;

                        ControlCatFrame(frame_Cat);
                        ControlObstacleFrame(frame_Obstacle);
                        ControlDonutFrame(frame_Donut, CheckDonutImpact(cat, donut, currentClip_Cat, currentClip_Donut), donut.GetX());



                    }
                }
                DrawEndGameSelection(gLoseTextureManager, &e, gRenderer, Play_Again);
                if (!Play_Again) {
                    obstacle1.~Obstacle();
                    obstacle2.~Obstacle();
                    obstacle3.~Obstacle();
                    donut.~Donut();
                }
            }
        }
    }
    Close();
    return 0;



}

bool Init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) < 0) {
        LogError("Can not initialize SDL.", SDL_ERROR);
        success = false;
    } else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            std::cout << "Warning: Linear texture filtering not enable!" << std::endl;
        }
        gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            LogError("Can not create window", SDL_ERROR);
            success = false;
        } else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL) {
                LogError("Can not create renderer!", SDL_ERROR);
                success = false;
            } else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlag = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlag) & imgFlag)) {
                    LogError("Can not initialize SDL image", IMG_ERROR);
                    success = false;
                }

                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                    std::cout << "SDL mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
                    success = false;
                }

                if (TTF_Init() == -1) {
                    std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
                    success = false;
                }
            }
        }
    }
    return success;
}

bool LoadMedia() {
    bool success = true;
    gMusic = Mix_LoadMUS("sound/lofi-streets.wav");
    if(gMusic == nullptr) {
        LogError("Failed to load Background music", MIX_ERROR);
        success = false;
    }

    gMenuMusic = Mix_LoadMUS("sound/lofi-streets.wav");
    if (gMenuMusic == nullptr) {
        LogError("Failed to load Menu music", MIX_ERROR);
        success = false;
    }
    gClick = Mix_LoadWAV("sound/mouse_click.wav");
    if (gClick == nullptr) {
        LogError("Failed to load click music", MIX_ERROR);
        success = false;
    }
    gJump = Mix_LoadWAV("sound/jump_sound.wav");
    if (gJump == nullptr) {
        LogError("Failed to load jump music", MIX_ERROR);
        success = false;
    }
    gLose = Mix_LoadWAV("sound/cat_meow.wav");
    if (gLose == nullptr) {
        LogError("Failed to load meo music", MIX_ERROR);
        success = false;
    } else {
        gFont = TTF_OpenFont("font/pixel_font.ttf", 28);
        gFont2 = TTF_OpenFont("font/pixel_font.ttf", 40);
        if (gFont == NULL) {
            LogError("Failed to load font", MIX_ERROR);
            success = false;
        } else {
            if (!gText1TextureManager.LoadRenderText("Your score: ", gFont, textColor, gRenderer)) {
                std::cout << "Failed to render text1 Texture" << std::endl;
                success = false;
            }

            if (!gText2TextureManager.LoadRenderText("High score: ", gFont, textColor, gRenderer)) {
                std::cout << "Failed to render text2 Texture" << std::endl;
                success = false;
            }



            if (!gMenuTextureManager.LoadFile("image/Background/result_Menu_cat.png", gRenderer)) {
                std::cout << "Failed to load menu image" <<std::endl;
            }

            if (!gInstructionTextureManager.LoadFile("image/background/Guide.png", gRenderer))
			{
				std::cout << "Failed to load instruction image" << std::endl;
				success = false;
			}

            if (!gPlayButtonTextureManager.LoadFile("image/button/big_button/Play.png", gRenderer)) {
                std::cout << "Failed to load play button image" <<std::endl;
                success = false;
            } else {
                for (int i = 0; i < BUTTON_TOTAL; i++) {
                    gPlayButton[i].x = 139 * i;
                    gPlayButton[i].y = 0;
                    gPlayButton[i].w = 139;
                    gPlayButton[i].h = 98;
                }
            }

            if (!gHelpButtonTextureManager.LoadFile("image/button/big_button/Help.png", gRenderer)) {
                std::cout << "Failed to load  help button" << std::endl;
                success = false;
            } else {
                for (int i = 0; i < BUTTON_TOTAL; i++) {
                    gHelpButton[i].x = 139 * i;
                    gHelpButton[i].y = 0;
                    gHelpButton[i].w = 139;
                    gHelpButton[i].h = 98;
                }
            }
            if (!gBackButtonTextureManager.LoadFile("image/button/big_button/Back.png", gRenderer)) {
                std::cout << "Failed to load back_button image" << std::endl;
                success = false;
            } else  {
                for (int i = 0; i < BUTTON_TOTAL; i++) {
                    gBackButton[i].x = 139 * i;
                    gBackButton[i].y = 0;
                    gBackButton[i].w = 139;
                    gBackButton[i].h = 49;
                }
            }
            if (!gExitButtonTextureManager.LoadFile("image/button/big_button/exit.png", gRenderer)) {
                std::cout << "Failed to load exit_button image" << std::endl;
                success = false;
            } else {
                for (int i = 0; i < BUTTON_TOTAL; ++i) {
                    gExitButton[i].x = 150 * i;
                    gExitButton[i].y = 0;
                    gExitButton[i].w = 150;
                    gExitButton[i].h = 98;
                }
            }

            if (!gPauseButtonTextureManager.LoadFile("image/button/big_button/pause_button.png", gRenderer)) {
                std::cout << "Failed to load pause_button image" << std::endl;
                success = false;
            } else {
                for (int i = 0; i < BUTTON_TOTAL; ++i) {
                    gPauseButton[i].x = 22 * i;
                    gPauseButton[i].y = 0;
                    gPauseButton[i].w = 22;
                    gPauseButton[i].h = 34;
                }
            }

            if (!gContinueButtonTextureManager.LoadFile("image/button/big_button/continue_button.png", gRenderer)) {
                std::cout << "Failed to load continue_button image " << std::endl;
                success = false;
            } else  {
                for (int i = 0; i < BUTTON_TOTAL; ++i) {
                    gContinueButton[i].x = 22 * i;
                    gContinueButton[i].y = 0;
                    gContinueButton[i].w = 22;
                    gContinueButton[i].h = 34;
                }
            }

            for (int i = 0; i < BACKGROUND_LAYER; i++) {
                if (!gBackgroundTextureManager[i].LoadFile(BACKGROUND[i].c_str(), gRenderer)) {
                    std::cout << "Failed to load background image" << std::endl;
                    success = false;
                }
            }

            if (!gGroundTextureManager.LoadFile("image/Background/result_road.png", gRenderer)) {
                std::cout << "Failed to load ground image" << std::endl;
                success = false;
            }
            if (!gCatTextureManager.LoadFile("image/character/CatRunn.png", gRenderer)) {
                std::cout << "Failed to load character_run image." << std::endl;
                success = false;
            } else {
                for (int i = 0; i < 7; ++i) {
                    gCatClips[i].x = 150 * i;
                    gCatClips[i].y = 0;
                    gCatClips[i].w = 150;
                    gCatClips[i].h = 120;
                }
            }


            if (!gLoseTextureManager.LoadFile("image/Background/result_cry2.png", gRenderer)) {
                std::cout << "Failed to load lose image." << std::endl;
                success = false;
            }

        }

    }

    return success;


}

void Close() {
    gMenuTextureManager.Destroy();
    gInstructionTextureManager.Destroy();
    gCatTextureManager.Destroy();
    gPlayButtonTextureManager.Destroy();
    gGroundTextureManager.Destroy();
    gHelpButtonTextureManager.Destroy();
    gExitButtonTextureManager.Destroy();
    gBackButtonTextureManager.Destroy();
    gPauseButtonTextureManager.Destroy();
    gContinueButtonTextureManager.Destroy();
    gLoseTextureManager.Destroy();
    gText1TextureManager.Destroy();
    gScoreTextureManager.Destroy();
    gText2TextureManager.Destroy();
    gHighScoreTextureManager.Destroy();
    gText3TextureManager.Destroy();


    for (int i = 0; i < BACKGROUND_LAYER; i++) {
        gBackgroundTextureManager[i].Destroy();

    }

    Mix_FreeMusic(gMusic);
    Mix_FreeMusic(gMenuMusic);
    Mix_FreeChunk(gClick);
    Mix_FreeChunk(gLose);
    Mix_FreeChunk(gJump);
    gMusic = nullptr;
    gMenuMusic = nullptr;
    gClick = nullptr;
    gLose = nullptr;
    gJump = nullptr;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}
