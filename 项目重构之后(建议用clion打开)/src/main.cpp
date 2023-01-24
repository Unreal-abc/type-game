#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include<SDL_mixer.h>
#include<map>
#include<ctime>
#include<random>
#include <list>
#include "button.hpp"
#include "ltexture.hpp"
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
// 解决中文乱码问题
#pragma once
#pragma execution_character_set("utf-8")
using namespace std;
std::list<char> zm;
map<std::string, LTexture> textureManagement;
map<std::string, SDL_Rect> rectManagement;
Mix_Music *BGM = NULL;
Mix_Chunk *DOGE = NULL;
Mix_Chunk *OVER = NULL;
map<std::string, Button> buttonManagement;
int zm_Pos_y = 0;//zm代表5个物体的编号
int a = 1;
enum class scene {
    mainInterfaceScene = 0, inGameScenes = 1, setUpInterfaceScene = 2, exitScreenScene = 3, gameOverScene = 4
};
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
typedef struct {
    scene scene;
    bool doge_state = false;
    bool Music = true;
    bool SoundEffect = true;
    bool Difficulty = false;//false是简单 true是难
    int SCORE = 0;
    int TIME = 60000;
} GameState;
GameState gameState;

void clean() {
    //清除变量
    zm.clear();
    zm_Pos_y = 0;
}
void Game() {
    textureManagement["主界面"].render(0, 0, 800, 600);
    //创建文字
    int font_x = 660, num[4] = {0, 0, 0, 0};
    //分离数字
    num[0] = gameState.SCORE / 1000 % 10;
    num[1] = gameState.SCORE / 100 % 10;
    num[2] = gameState.SCORE / 10 % 10;
    num[3] = gameState.SCORE % 10;
    //分数
    for (int i = 0; i < 4; i++) {
        textureManagement["数字贴图"].render(rectManagement["数字" + to_string(num[i])], {font_x, 60, 30, 30});
        font_x += 30;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////
    int time_x = 700, time_num = gameState.TIME / 1000, time_nums[2] = {0, 0};
    time_nums[0] = time_num / 10 % 10;
    time_nums[1] = time_num % 10;
    //绘制时间
    if (gameState.Difficulty) {
        for (int i = 0; i < 2; i++) {
            textureManagement["数字贴图"].render(rectManagement["数字9"], {time_x, 200, 30, 30});
            time_x += 30;
        }
    } else {
        for (int i = 0; i < 2; i++) {
            textureManagement["数字贴图"].render(rectManagement["数字" + to_string(time_nums[i])],
                                                 {time_x, 200, 30, 30});
            time_x += 30;
        }
    }
    ///////////////////////////////////////////////////////////////////////////////////////
    int zm_Pos_x = 200;
    zm_Pos_y += 5;//向下移动
    if (zm.empty()) {
        clean();
        for (int i = 0; i < 5; i++) {//创建5个字母物体
            int size = rand() % (26);//取随机数1-26，分别代表A-Z
            /////实例化物体
            std::string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            zm.push_back(s[size]);
        }
    } else {
        for (char ele: zm) {
            if (zm_Pos_y >= 520 && gameState.Difficulty == false) zm_Pos_y = 0;//如果字母物体越界，放在开头；
            if (zm_Pos_y >= 520 && gameState.Difficulty == true) {
                gameState.scene = scene::gameOverScene;
                Mix_HaltMusic();
                if (gameState.SoundEffect) Mix_PlayChannel(-1, OVER, 0);
            }
            std::string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            textureManagement["字母贴图"].render(rectManagement["字母" + to_string(ele)], {zm_Pos_x, zm_Pos_y, 40, 40});
            zm_Pos_x += 50;
        }
    }
    if (gameState.Difficulty == false) {
        SDL_Delay(40);//延迟
        gameState.TIME -= 60;
        if (gameState.TIME <= 0) {
            gameState.scene = scene::gameOverScene;
            Mix_HaltMusic();
            if (gameState.SoundEffect) Mix_PlayChannel(-1, OVER, 0);
        }
    } else SDL_Delay(10);
}

void draw() {//绘图函数
    SDL_SetRenderDrawColor(gRenderer, 95, 158, 160, 255);
    SDL_RenderClear(gRenderer);
    switch (gameState.scene) {
        case scene::mainInterfaceScene : {//开始界面
            //实现Start图片缩放
            static float x = 2.0;
            x += 0.02 * a;
            if (x >= 2.5) {
                a = -a;
            }
            if (x <= 2.0) {
                a = -a;
            }
            SDL_RenderSetScale(gRenderer, 1, 1);
            textureManagement["设置按钮"].render(180, 350, 200, 50);
            textureManagement["开始按钮"].render(180 - int(x * 10), 250 - int(x * 10), 200 + int(x * 20),
                                                 50 + int(x * 20));
            textureManagement["退出按钮"].render(180, 450, 200, 50);
            textureManagement["狗"].render(650 - int(x * 10), 440 - int(x * 10), 111 + int(x * 20), 102 + int(x * 20));
            textureManagement["名称"].render(50, 0, 700, 200);
            if (gameState.doge_state == true) {
                textureManagement["不要碰我"].render(650, 370, 150, 50);
            }
            break;
        }
        case scene::inGameScenes: {//进入游戏中
            Game();
            break;
        }
        case scene::setUpInterfaceScene: {//设置界面
            textureManagement["设置界面"].render(0, 0, 800, 600);
            if (gameState.Music) {
                textureManagement["勾按钮"].render(500, 210, 20, 20);
            }
            if (gameState.SoundEffect) {
                textureManagement["勾按钮"].render(500, 290, 20, 20);
            }
            if (gameState.Difficulty == false) {
                textureManagement["勾按钮"].render(428, 375, 20, 20);
            } else {
                textureManagement["勾按钮"].render(590, 375, 20, 20);
            }
            break;
        }
        case scene::exitScreenScene: {//退出界面
            textureManagement["离开界面"].render(0, 0, 800, 600);
            break;
        }
        case scene::gameOverScene: {
            textureManagement["游戏结束界面"].render(0, 0, 800, 600);
            //创建文字
            int font_x = 360, num[4] = {0, 0, 0, 0};
            //分离数字
            num[0] = gameState.SCORE / 1000 % 10;
            num[1] = gameState.SCORE / 100 % 10;
            num[2] = gameState.SCORE / 10 % 10;
            num[3] = gameState.SCORE % 10;
            for (int i = 0; i < 4; i++) {
                textureManagement["数字贴图"].render(rectManagement["数字" + to_string(num[i])], {font_x, 290, 30, 30});
                font_x += 30;
            }
            break;
        }
    }
    SDL_RenderPresent(gRenderer);
    SDL_Delay(20);//延迟
}

void close() {
    for (auto it: textureManagement) {
        it.second.free();
    }
    Mix_FreeMusic(BGM);
    Mix_FreeChunk(DOGE);
    Mix_FreeChunk(OVER);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void check_clicked(SDL_Event &event) {
    switch (gameState.scene) {
        case scene::mainInterfaceScene :
            if (textureManagement["开始按钮"].checkClicked(&event)) {
                gameState.scene = scene::mainInterfaceScene;
                clean();
                gameState.SCORE = 0;
                gameState.TIME = 60000;
                if (gameState.Music) {
                    if (Mix_PausedMusic() == 1) {
                        Mix_ResumeMusic();
                    } else {
                        Mix_PlayMusic(BGM, -1);
                    }
                } else {
                    Mix_PausedMusic();
                }
                gameState.scene = scene::inGameScenes;
            }

            if (textureManagement["设置按钮"].checkClicked(&event)) {
                gameState.scene = scene::setUpInterfaceScene;
            }

            if (textureManagement["退出按钮"].checkClicked(&event)) {
                gameState.scene = scene::exitScreenScene;
            }

            if (textureManagement["狗"].checkClicked(&event)) {
                gameState.doge_state = true;
                Mix_PlayChannel(-1, DOGE, 0);
            }
            break;
        case scene::inGameScenes:
            buttonManagement["游戏中菜单"] = Button(677, 259, 105, 55);
            if (buttonManagement["游戏中菜单"].checkClicked(&event)) {
                gameState.scene = scene::mainInterfaceScene;
                if (Mix_PlayingMusic() != 0) {
                    Mix_HaltMusic();
                }
            }
            break;
        case scene::setUpInterfaceScene:

            if (buttonManagement["音乐"].checkClicked(&event)) {
                gameState.Music = !gameState.Music;
            }
            if (buttonManagement["音效"].checkClicked(&event)) {
                gameState.SoundEffect = !gameState.SoundEffect;
            }
            if (buttonManagement["游戏难度简单"].checkClicked(&event)) {
                gameState.Difficulty = false;
            }
            if (buttonManagement["游戏难度困难"].checkClicked(&event)) {
                gameState.Difficulty = true;
            }
            if (buttonManagement["应用设置"].checkClicked(&event)) {
                gameState.scene = scene::mainInterfaceScene;
            }
            break;
        case scene::exitScreenScene:
            buttonManagement["是"] = Button(540, 360, 190, 85);
            buttonManagement["否"] = Button(130, 360, 190, 85);
            if (buttonManagement["是"].checkClicked(&event)) {
                close();
                exit(0);
            }
            if (buttonManagement["否"].checkClicked(&event)) {
                gameState.scene = scene::mainInterfaceScene;
//                gameState.SCORE = 0;
//                gameState.TIME = 60000;
                if (Mix_PlayingMusic() != 0) Mix_HaltMusic();
            }
            break;
        case scene::gameOverScene:
            buttonManagement["游戏结束菜单"] = Button(252, 433, 315, 60);
            if (buttonManagement["游戏结束菜单"].checkClicked(&event)) gameState.scene = scene::mainInterfaceScene;
            break;
    }
}

void loop_event() {///事件循环函数
    while (1) {
        draw();
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    gameState.scene = scene::exitScreenScene;
                    break;
                }
                case SDL_MOUSEBUTTONUP:
                    check_clicked(event);
                    SDL_Log("鼠标点击位置(%d %d)", event.button.x, event.button.y);
                case SDL_KEYDOWN:
                    char key = 'A';
                    int flag = 0;
                    if (event.key.keysym.sym >= 97 && event.key.keysym.sym <= 122) {
                        key = char(event.key.keysym.sym - 32);
                        for (auto it = zm.begin(); it != zm.end();) {
                            if (*it == key) {
                                it = zm.erase(it);
                                if (gameState.Difficulty == 0) {
                                    gameState.SCORE += 10;
                                    SDL_Log("+10");
                                } else {
                                    gameState.SCORE += 30;
                                    SDL_Log("+30");
                                }
                                flag = 1;
                                break;
                            } else {
                                it++;
                            }
                        }
                        if (flag != 1) {
                            gameState.Difficulty == false ? gameState.SCORE -= 30 : gameState.SCORE -= 20;
                        }
                    }
            }
        }
    }
}
bool init() {
    //Initialization flag
    bool success = true;
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }
        //Create window
        gWindow = SDL_CreateWindow("《是女人就拿到1000分》", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
                //Initialize SDL_mixer
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia() {//加载图片与声音资源
    //加载成功标志
    bool success = true;
    map<std::string, string> res;
    res["狗"] = "data/pic/DOGE.png";
    res["不要碰我"] = "data/pic/DONNOT TOUCH ME.png";
    res["退出按钮"] = "data/pic/EXIT.png";
    res["离开界面"] = "data/pic/LEAVE.png";
    res["主界面"] = "data/pic/Main.png";
    res["名称"] = "data/pic/NAME.png";
    res["游戏结束界面"] = "data/pic/OVER.png";
    res["设置界面"] = "data/pic/Set.png";
    res["设置按钮"] = "data/pic/SETUP.png";
    res["开始按钮"] = "data/pic/START.png";
    res["勾按钮"] = "data/pic/YES.png";
    for (auto it: res) {
        textureManagement[it.first] = LTexture(gRenderer);
        if (!textureManagement[it.first].loadFromFile(it.second)) {
            printf("加载失败!\n");
            success = false;
        }
    }

    textureManagement["数字贴图"] = LTexture(gRenderer);
    if (!textureManagement["数字贴图"].loadFromFile("data/pic/a.png")) {
        printf("加载失败!\n");
        success = false;
    } else {
        //Set sprite clips
        for (int i = 0; i < 10; i++) {
            SDL_Rect rect;
            rect.x = 40 * i;
            rect.y = 0;
            rect.w = 40;
            rect.h = 40;
            rectManagement["数字" + to_string(i)] = rect;
        }
    }
    textureManagement["字母贴图"] = LTexture(gRenderer);
    if (!textureManagement["字母贴图"].loadFromFile("data/pic/b.png")) {
        printf("加载失败!\n");
        success = false;
    } else {
        //Set sprite clips
        std::string s = "ABCDEFGHIJ";
        for (size_t i = 0; i < s.size(); i++) {
            SDL_Rect rect;
            rect.x = 200 * i;
            rect.y = 0;
            rect.w = 200;
            rect.h = 200;
            rectManagement["字母" + to_string(s[i])] = rect;
        }

        s = "KLMNOPQRST";
        for (size_t i = 0; i < s.size(); i++) {
            SDL_Rect rect;
            rect.x = 200 * i;
            rect.y = 200;
            rect.w = 200;
            rect.h = 200;
            rectManagement["字母" + to_string(s[i])] = rect;
        }
        s = "UVWXYZ";
        for (size_t i = 0; i < s.size(); i++) {
            SDL_Rect rect;
            rect.x = 200 * i;
            rect.y = 400;
            rect.w = 200;
            rect.h = 200;
            rectManagement["字母" + to_string(s[i])] = rect;
        }
    }
    BGM = Mix_LoadMUS("data/audio/BGM.wav");
    if (BGM == NULL) {
        printf("加载失败!\n");
        success = false;
    }
    DOGE = Mix_LoadWAV("data/audio/DOGE.wav");
    if (DOGE == NULL) {
        printf("加载失败!\n");
        success = false;
    }
    OVER = Mix_LoadWAV("data/audio/OVER.wav");
    if (OVER == NULL) {
        printf("加载失败!\n");
        success = false;
    }
    //注册按钮
    buttonManagement["音乐"] = Button(500, 210, 35, 35);
    buttonManagement["音效"] = Button(500, 280, 35, 35);
    buttonManagement["游戏难度简单"] = Button(430, 370, 35, 35);
    buttonManagement["游戏难度困难"] = Button(595, 380, 35, 35);
    buttonManagement["应用设置"] = Button(365, 445, 290, 75);
    buttonManagement["是"] = Button(540, 360, 190, 85);
    buttonManagement["否"] = Button(130, 360, 190, 85);
    buttonManagement["游戏中菜单"] = Button(677, 259, 105, 55);
    buttonManagement["游戏结束菜单"] = Button(252, 433, 315, 60);
    return success;
}
int WinMain(int argc, char **args) {
    srand((unsigned) time(NULL));
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        // Load media
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            loop_event();
        }
    }
    close();
    return 0;
}