#ifndef LOGIC_IN_GAME_H
#define LOGIC_IN_GAME_H

#include "windows.h"
#include "BasicPart.h"
#include "Obstacle.h"
#include "Donut.h"
#include "Cat.h"
#include "Button.h"

bool Init();
bool LoadMedia();
void Close();

std::string GetHighScore(std::string path);

void UpdateHighScore(std::string path, const int& score, const std::string& old_high_score);

int UpdateGameTimeAndScore(int& time, int& speed, int& score);

void RenderScrollingBackground(std::vector <double>& offsetSpeed, TextureManager(&gBackgroundTextureManager)[BACKGROUND_LAYER], SDL_Renderer* gRenderer);

void RenderScrollingGround(int& speed, const int acceleration, TextureManager gGroundTextureManager, SDL_Renderer* gRenderer);

void HandlePlayButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu, bool& Play, Mix_Chunk* gClick);

void HandleHelpButton(SDL_Event* e, SDL_Rect(&gBackButton)[BUTTON_TOTAL], Button& HelpButton, Button& BackButton, TextureManager gInstructionTextureManager, TextureManager gBackButtonTextureManager, SDL_Renderer* gRenderer, bool& Quit_game, Mix_Chunk* gClick);

void HandleExitButton(SDL_Event* e, Button& ExitButton, bool& Quit, Mix_Chunk* gClick);

void HandleContinueButton(Button ContinueButton, TextureManager gContinueButtonTextureManager, SDL_Event& e, SDL_Renderer* gRenderer, SDL_Rect(&gContinueButton)[BUTTON_TOTAL], bool& Game_State, Mix_Chunk* gClick);

void HandlePauseButton(SDL_Event& e, SDL_Renderer* gRenderer, SDL_Rect(&gContinueButton)[BUTTON_TOTAL], Button& PauseButton, Button ContinueButton, TextureManager gContinueButtonTextureManager, bool& game_state, Mix_Chunk* gClick);

void GenerateObstacle(Obstacle& obstacle1, Obstacle& obstacle2, Obstacle& obstacle3, SDL_Rect(&gObstacleClips)[FLYING_FRAMES], SDL_Renderer* gRenderer);

void GenerateDonut(Donut& donut, SDL_Rect(&gDonutClips)[DONUT_FRAMES], SDL_Renderer* gRenderer);


bool CheckImpact(Cat cat, SDL_Rect* cat_clip, Obstacle Obstacle, SDL_Rect* obstacle_clip = nullptr);

bool CheckImpact2(Cat cat, SDL_Rect* cat_clip, Donut donut, SDL_Rect* donut_clip = nullptr);

bool CheckObstacleImpact(Cat cat, Obstacle obstacle1, Obstacle obstacle2, Obstacle obstacle3, SDL_Rect* cat_clip, SDL_Rect* obstacle_clip = nullptr);

bool CheckDonutImpact(Cat cat, Donut donut, SDL_Rect* cat_clip, SDL_Rect* donut_clip = nullptr);

/// void ControlHeartFrame(int& frame, int hp);

void ControlCatFrame(int& frame);

void ControlObstacleFrame(int& frame);

void ControlDonutFrame(int& frame, bool check, int location);

/// void DrawHPScore(TextureManager gTextTextureManager, TextureManager gHPTextureManager, SDL_Color textColor, SDL_Renderer* gRenderer, TTF_Font* gFont, const int& HP);

void DrawPlayerScore(TextureManager gTextTextureManager, TextureManager gScoreTextureManager, SDL_Color textColor, SDL_Renderer* gRenderer, TTF_Font* gFont, const int& score);

void DrawPlayerHighScore(TextureManager gTextTextureManager, TextureManager gHighScoreTextureManager, SDL_Color textColor, SDL_Renderer* gRenderer, TTF_Font* gFont, const std::string& HighScore);

void DrawEndGameSelection(TextureManager gLoseTextureManager, SDL_Event* e, SDL_Renderer* gRenderer, bool& Play_Again);

#endif // LOGIC_IN_GAME_H
