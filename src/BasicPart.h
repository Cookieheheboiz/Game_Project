#ifndef BASICPART_H
#define BASICPART_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include <fstream>
#include <sstream>

#define TIME_MAX 1000
#define GROUND 724
#define MAX_HEIGHT 330 ///chieu cao toi da co the nhay

#define SDL_ERROR 1
#define IMG_ERROR 2
#define MIX_ERROR 3
#define TTF_ERROR 4

#define MIX_CHANNEL -1

#define BASE_SPEED 0
#define SPEED_INCREASEMENT 0.5
#define SCORE_INCREASEMENT 1
#define TIME_INCREASEMENT 1
#define FRAME_INCREASEMENT 1

#define GROUND_SPEED 5
#define OBSTACLE_SPEED 5
#define MAX_OBSTACLE_WIDTH 100

#define IN_AIR_OBSTACLE 1
#define ON_GROUND_OBSTACLE 0

#define SLOW_FRAME_CAT 4
#define SLOW_FRAME_OBSTACLE 4
#define SLOW_FRAME_DONUT 7


#define IS_REPEATITIVE -1 ///chi hanh dong lap vo han
#define NOT_REPEATITIVE 0  ///chi hanh dong khong lap
#define SMALL_BUTTON 1  /// dinh danh cac loai nut
#define COMMON_BUTTON 2 /// dinh danh nut

const std::string WINDOW_TITLE = "CAT GO GO";


const int SCREEN_HEIGHT = 844;
const int SCREEN_WIDTH = 1500;


const int COMMON_BUTTON_WIDTH = 150;
const int COMMON_BUTTON_HEIGHT = 98;
const int SMALL_BUTTON_WIDTH = 22;
const int SMALL_BUTTON_HEIGHT = 34;

const int PLAY_BUTON_POSX = 650;
const int PLAY_BUTTON_POSY= 250;
const int HELP_BUTTON_POSX = 650;
const int HELP_BUTTON_POSY = 357;
const int EXIT_BUTTON_POSX = 650;
const int EXIT_BUTTON_POSY = 466;
const int BACK_BUTTON_POSX = 31;
const int BACK_BUTTON_POSY = 29;
const int PAUSE_BUTTON_POSX = 31;
const int PAUSE_BUTTON_POSY = 29;
const int CONTINUE_BUTTON_POSX = 31;
const int CONTINUE_BUTTON_POSY = 29;
const int TEXT_1_POSX = 1150;
const int TEXT_1_POSY = 20;
const int TEXT_2_POSX = 1150;
const int TEXT_2_POSY = 80;
const int TEXT_3_POSX = 600;
const int TEXT_3_POSY = 30;
const int SCORE_POSX = 1270;
const int SCORE_POSY = 20;
const int HIGH_SCORE_POSX = 1270;
const int HIGH_SCORE_POSY = 80;


const double LAYER_1_SPEED = 0.0;
const double LAYER_2_SPEED = 0.25;
const double LAYER_3_SPEED = 0.5;
const double LAYER_4_SPEED = 0.75;
const double LAYER_5_SPEED = 1.0;

const int RUNNING_FRAMES = 6;
const int FLYING_FRAMES = 5;
const int DONUT_FRAMES = 1;
const int BACKGROUND_LAYER = 5;

enum ButtonSprite {
    BUTTON_MOUSE_OUT = 0,
    BUTTON_MOUSE_OVER = 1,
    BUTTON_TOTAL = 2
};


void LogError(std::string msg, int error_code = SDL_ERROR);

#endif // BASICPART_H
