#include <iostream>
#include "SDL.h"
#include<SDL_mixer.h>
#include<map>
#include<ctime>
#include<random>
// 解决中文乱码问题
#pragma once
#pragma execution_character_set("utf-8")
//#define FRAMERATE 60
#define FILE_NAME "START.BMP"
const int WIDTH =800;
const int  HIGHTH= 600;
using namespace std;
map <char, int> object;//判断物体是否存在
int zm[5] = { 0,0,0,0,0 }, zm_Pos_x[5] = {0,0,0,0,0};int zm_Pos_y = 0;//zm代表5个物体的编号
int Music = 1,SoundEffect=1,Difficulty=0,cnt=0;//cnt代表场景内物体个数
int a=1,dontouch=0,status=0,wangwang=0;//status=0 START界面，1游戏中，2设置,3退出界面,4代表Over//wangwang代表叫声
int SCORE = 0,TIME=60000;
///////////////////////////////////////////////////////////////////////////////
SDL_Window *windows;
//SDL_Surface* screen=NULL;
SDL_Texture *imageStart;
SDL_Texture *imageSetup;
SDL_Texture *imageExit;
SDL_Texture *imageDoge;
SDL_Texture *imageDonnotTouch;
SDL_Texture *imageName;
SDL_Texture *imageLeave;
SDL_Texture *imageGame;
SDL_Texture* imageMain;
SDL_Texture* imageSet;
SDL_Texture* imageYes;
SDL_Texture* imageOver;
SDL_Texture* aa;SDL_Texture* b;SDL_Texture* c;SDL_Texture* d;SDL_Texture* e;SDL_Texture* f;SDL_Texture* g;SDL_Texture* h;SDL_Texture* ii;SDL_Texture* j;SDL_Texture* k;SDL_Texture* l;SDL_Texture* m;SDL_Texture* n;SDL_Texture* o;SDL_Texture* p;SDL_Texture* q;SDL_Texture* r;SDL_Texture* s;SDL_Texture* t;SDL_Texture* u;SDL_Texture* v;SDL_Texture* w;SDL_Texture* x;SDL_Texture* y;SDL_Texture* z;
SDL_Texture* a1;SDL_Texture* a2;SDL_Texture* a3;SDL_Texture* a4;SDL_Texture* a5;SDL_Texture* a6;SDL_Texture* a7;SDL_Texture* a8;SDL_Texture* a9;SDL_Texture* a0;
SDL_Renderer *render;
//音效
Mix_Chunk* doge = NULL;
Mix_Music* sound = NULL;
Mix_Chunk* Over = NULL;

//////////////////////////////////////////////////////////////////////////////////
void clean() {
    //清除变量
    cnt = 0;
    for (int i = 0;i < 5;i++) {
        zm[i] = 0;zm_Pos_x[i] = 0;
    }
    zm_Pos_y = 0;
    object['A'] = 0;object['B'] = 0;object['C'] = 0;object['D'] = 0;object['E'] = 0;object['F'] = 0;object['G'] = 0;object['H'] = 0;object['I'] = 0;object['J'] = 0;object['K'] = 0;object['L'] = 0;object['M'] = 0;object['N'] = 0;object['O'] = 0;object['P'] = 0;object['Q'] = 0;object['R'] = 0;object['S'] = 0;object['T'] = 0;object['U'] = 0;object['V'] = 0;object['W'] = 0;object['X'] = 0;object['Y'] = 0;object['Z'] = 0;
    // // // //
}
void Game() {
    SDL_SetRenderDrawColor(render, 95, 158, 160, 255);
    SDL_RenderClear(render);
    SDL_Rect destRectMain = { 0,0 ,800,600 };
    SDL_RenderCopy(render, imageMain, NULL, &destRectMain);
    //创建文字
    int font_x = 660, num[4] = {0,0,0,0};
    //分离数字
    num[0] = SCORE / 1000 % 10;
    num[1] = SCORE / 100 % 10;
    num[2] = SCORE / 10 % 10;
    num[3] = SCORE % 10;
    for (int i = 0;i < 4;i++) {
        SDL_Rect destRectFont = {font_x ,60 ,30,30 };font_x += 30;
        if(num[i]==0){ SDL_RenderCopy(render, a0, NULL, &destRectFont); }
        if (num[i] == 1) { SDL_RenderCopy(render, a1, NULL, &destRectFont); }
        if (num[i] == 2) { SDL_RenderCopy(render, a2, NULL, &destRectFont); }
        if (num[i] == 3) { SDL_RenderCopy(render, a3, NULL, &destRectFont); }
        if (num[i] == 4) { SDL_RenderCopy(render, a4, NULL, &destRectFont); }
        if (num[i] == 5) { SDL_RenderCopy(render, a5, NULL, &destRectFont); }
        if (num[i] == 6) { SDL_RenderCopy(render, a6, NULL, &destRectFont); }
        if (num[i] == 7) { SDL_RenderCopy(render, a7, NULL, &destRectFont); }
        if (num[i] == 8) { SDL_RenderCopy(render, a8, NULL, &destRectFont); }
        if (num[i] == 9) { SDL_RenderCopy(render, a9, NULL, &destRectFont); }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////
    int time_x = 700, time_num = TIME / 1000, time_nums[2] = {0,0};
    time_nums[0] = time_num / 10 % 10;
    time_nums[1] = time_num  % 10;
    if (Difficulty == 1) {
        for (int i = 0;i < 2;i++) {
            SDL_Rect destRectTime= { time_x ,200 ,30,30 };time_x += 30;
            SDL_RenderCopy(render, a9, NULL, &destRectTime);
        }
    }
    else {
        for (int i = 0;i < 2;i++) {
            SDL_Rect destRectTime = { time_x ,200 ,30,30 };time_x += 30;
            if (time_nums[i] == 0) { SDL_RenderCopy(render, a0, NULL, &destRectTime); }
            if (time_nums[i] == 1) { SDL_RenderCopy(render, a1, NULL, &destRectTime); }
            if (time_nums[i] == 2) { SDL_RenderCopy(render, a2, NULL, &destRectTime); }
            if (time_nums[i] == 3) { SDL_RenderCopy(render, a3, NULL, &destRectTime); }
            if (time_nums[i] == 4) { SDL_RenderCopy(render, a4, NULL, &destRectTime); }
            if (time_nums[i] == 5) { SDL_RenderCopy(render, a5, NULL, &destRectTime); }
            if (time_nums[i] == 6) { SDL_RenderCopy(render, a6, NULL, &destRectTime); }
            if (time_nums[i] == 7) { SDL_RenderCopy(render, a7, NULL, &destRectTime); }
            if (time_nums[i] == 8) { SDL_RenderCopy(render, a8, NULL, &destRectTime); }
            if (time_nums[i] == 9) { SDL_RenderCopy(render, a9, NULL, &destRectTime); }
        }
    }


    ///////////////////////////////////////////////////////////////////////////////////////
    if (cnt <= 0) {
        clean();
        for (int i = 0;i < 5;i++) {//创建5个字母物体
           int size = rand() % (26 - 1 + 1) + 1;//取随机数1-26，分别代表A-Z
           zm[i] = size;
           int Pos_x= rand() % (580 - 30 + 30) + 30;
           zm_Pos_x[i] = Pos_x;
           SDL_Log("%d",zm[i]);
           cnt++;
           /////实例化物体
           SDL_Rect destRectObject = { zm_Pos_x[i],0 ,40,40 };
           if (zm[i] == 1) { object['A'] = 1; SDL_RenderCopy(render, aa, NULL, &destRectObject);}
           if (zm[i] == 2) { object['B'] = 1; SDL_RenderCopy(render, b, NULL, &destRectObject); }
           if (zm[i] == 3) { object['C'] = 1; SDL_RenderCopy(render, c, NULL, &destRectObject); }
           if (zm[i] == 4) { object['D'] = 1; SDL_RenderCopy(render, d, NULL, &destRectObject); }
           if (zm[i] == 5) { object['E'] = 1; SDL_RenderCopy(render, e, NULL, &destRectObject); }
           if (zm[i] == 6) { object['F'] = 1; SDL_RenderCopy(render, f, NULL, &destRectObject); }
           if (zm[i] == 7) { object['G'] = 1; SDL_RenderCopy(render, g, NULL, &destRectObject); }
           if (zm[i] == 8) { object['H'] = 1; SDL_RenderCopy(render, h, NULL, &destRectObject); }
           if (zm[i] == 9) { object['I'] = 1; SDL_RenderCopy(render, ii, NULL, &destRectObject); }
           if (zm[i] == 10) { object['J'] = 1; SDL_RenderCopy(render, j, NULL, &destRectObject); }
           if (zm[i] == 11) { object['K'] = 1; SDL_RenderCopy(render, k, NULL, &destRectObject); }
           if (zm[i] == 12) { object['L'] = 1; SDL_RenderCopy(render, l, NULL, &destRectObject); }
           if (zm[i] == 13) { object['M'] = 1; SDL_RenderCopy(render, m, NULL, &destRectObject); }
           if (zm[i] == 14) { object['N'] = 1; SDL_RenderCopy(render, n, NULL, &destRectObject); }
           if (zm[i] == 15) { object['O'] = 1; SDL_RenderCopy(render, o, NULL, &destRectObject); }
           if (zm[i] == 16) { object['P'] = 1; SDL_RenderCopy(render, p, NULL, &destRectObject); }
           if (zm[i] == 17) { object['Q'] = 1; SDL_RenderCopy(render, q, NULL, &destRectObject); }
           if (zm[i] == 18) { object['R'] = 1; SDL_RenderCopy(render, r, NULL, &destRectObject); }
           if (zm[i] == 19) { object['S'] = 1; SDL_RenderCopy(render, s, NULL, &destRectObject); }
           if (zm[i] == 20) { object['T'] = 1; SDL_RenderCopy(render, t, NULL, &destRectObject); }
           if (zm[i] == 21) { object['U'] = 1; SDL_RenderCopy(render, u, NULL, &destRectObject); }
           if (zm[i] == 22) { object['V'] = 1; SDL_RenderCopy(render, v, NULL, &destRectObject); }
           if (zm[i] == 23) { object['W'] = 1; SDL_RenderCopy(render, w, NULL, &destRectObject); }
           if (zm[i] == 24) { object['X'] = 1; SDL_RenderCopy(render, x, NULL, &destRectObject); }
           if (zm[i] == 25) { object['Y'] = 1; SDL_RenderCopy(render, y, NULL, &destRectObject); }
           if (zm[i] == 26) { object['Z'] = 1; SDL_RenderCopy(render, z, NULL, &destRectObject); }
           SDL_RenderPresent(render);
        }
    }
    else {
        for (int i = 0;i < 5;i++) {
            zm_Pos_y += 1;//向下移动
            if (zm_Pos_y >= 520&&Difficulty == 0) {
                zm_Pos_y = 0;//如果字母物体越界，放在开头；
            }
            if(zm_Pos_y >= 520 && Difficulty == 1)
            {
                status = 4;Mix_HaltMusic();
                if (SoundEffect == 1) {
                    Mix_PlayChannel(-1, Over, 0);
                }

            }

            SDL_Rect destRectObject = { zm_Pos_x[i],zm_Pos_y ,40,40 };
            if (zm[i] == 1) { object['A'] = 1; SDL_RenderCopy(render, aa, NULL, &destRectObject); }
            if (zm[i] == 2) { object['B'] = 1; SDL_RenderCopy(render, b, NULL, &destRectObject); }
            if (zm[i] == 3) { object['C'] = 1; SDL_RenderCopy(render, c, NULL, &destRectObject); }
            if (zm[i] == 4) { object['D'] = 1; SDL_RenderCopy(render, d, NULL, &destRectObject); }
            if (zm[i] == 5) { object['E'] = 1; SDL_RenderCopy(render, e, NULL, &destRectObject); }
            if (zm[i] == 6) { object['F'] = 1; SDL_RenderCopy(render, f, NULL, &destRectObject); }
            if (zm[i] == 7) { object['G'] = 1; SDL_RenderCopy(render, g, NULL, &destRectObject); }
            if (zm[i] == 8) { object['H'] = 1; SDL_RenderCopy(render, h, NULL, &destRectObject); }
            if (zm[i] == 9) { object['I'] = 1; SDL_RenderCopy(render, ii, NULL, &destRectObject); }
            if (zm[i] == 10) { object['J'] = 1; SDL_RenderCopy(render, j, NULL, &destRectObject); }
            if (zm[i] == 11) { object['K'] = 1; SDL_RenderCopy(render, k, NULL, &destRectObject); }
            if (zm[i] == 12) { object['L'] = 1; SDL_RenderCopy(render, l, NULL, &destRectObject); }
            if (zm[i] == 13) { object['M'] = 1; SDL_RenderCopy(render, m, NULL, &destRectObject); }
            if (zm[i] == 14) { object['N'] = 1; SDL_RenderCopy(render, n, NULL, &destRectObject); }
            if (zm[i] == 15) { object['O'] = 1; SDL_RenderCopy(render, o, NULL, &destRectObject); }
            if (zm[i] == 16) { object['P'] = 1; SDL_RenderCopy(render, p, NULL, &destRectObject); }
            if (zm[i] == 17) { object['Q'] = 1; SDL_RenderCopy(render, q, NULL, &destRectObject); }
            if (zm[i] == 18) { object['R'] = 1; SDL_RenderCopy(render, r, NULL, &destRectObject); }
            if (zm[i] == 19) { object['S'] = 1; SDL_RenderCopy(render, s, NULL, &destRectObject); }
            if (zm[i] == 20) { object['T'] = 1; SDL_RenderCopy(render, t, NULL, &destRectObject); }
            if (zm[i] == 21) { object['U'] = 1; SDL_RenderCopy(render, u, NULL, &destRectObject); }
            if (zm[i] == 22) { object['V'] = 1; SDL_RenderCopy(render, v, NULL, &destRectObject); }
            if (zm[i] == 23) { object['W'] = 1; SDL_RenderCopy(render, w, NULL, &destRectObject); }
            if (zm[i] == 24) { object['X'] = 1; SDL_RenderCopy(render, x, NULL, &destRectObject); }
            if (zm[i] == 25) { object['Y'] = 1; SDL_RenderCopy(render, y, NULL, &destRectObject); }
            if (zm[i] == 26) { object['Z'] = 1; SDL_RenderCopy(render, z, NULL, &destRectObject); }
            SDL_RenderPresent(render);
        }

    }
    if (Difficulty == 0) {
        SDL_Delay(40);//延迟
        TIME -= 60;
        if (TIME <= 0) {
            status = 4;Mix_HaltMusic();
            if (SoundEffect == 1) {
                Mix_PlayChannel(-1, Over, 0);
            }
        }
    }
    else {
        SDL_Delay(30);
    }


}
void Load() {
    //加载A
    SDL_Surface* A = SDL_LoadBMP("./data/A.bmp");
    if (A == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    aa = SDL_CreateTextureFromSurface(render, A);
    SDL_FreeSurface(A);//释放加载图片指针
        //加载B
    SDL_Surface* B = SDL_LoadBMP("./data/B.bmp");
    if (B == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    b = SDL_CreateTextureFromSurface(render, B);
    SDL_FreeSurface(B);//释放加载图片指针
        //加载C
    SDL_Surface* C = SDL_LoadBMP("./data/C.bmp");
    if (C == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    c = SDL_CreateTextureFromSurface(render, C);
    SDL_FreeSurface(C);//释放加载图片指针
        //加载D
    SDL_Surface* D = SDL_LoadBMP("./data/D.bmp");
    if (D == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    d= SDL_CreateTextureFromSurface(render, D);
    SDL_FreeSurface(D);//释放加载图片指针
        //加载E
    SDL_Surface* E = SDL_LoadBMP("./data/E.bmp");
    if (E == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    e= SDL_CreateTextureFromSurface(render, E);
    SDL_FreeSurface(E);//释放加载图片指针
        //加载F
    SDL_Surface* F = SDL_LoadBMP("./data/F.bmp");
    if (F == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    f = SDL_CreateTextureFromSurface(render, F);
    SDL_FreeSurface(F);//释放加载图片指针
        //加载G
    SDL_Surface* G = SDL_LoadBMP("./data/G.bmp");
    if (G == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    g = SDL_CreateTextureFromSurface(render, G);
    SDL_FreeSurface(G);//释放加载图片指针
        //加载H
    SDL_Surface* H = SDL_LoadBMP("./data/H.bmp");
    if (H == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    h = SDL_CreateTextureFromSurface(render, H);
    SDL_FreeSurface(H);//释放加载图片指针
        //加载I
    SDL_Surface* I = SDL_LoadBMP("./data/I.bmp");
    if (I == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    ii = SDL_CreateTextureFromSurface(render, I);
    SDL_FreeSurface(I);//释放加载图片指针
        //加载J
    SDL_Surface* J = SDL_LoadBMP("./data/J.bmp");
    if (J == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    j = SDL_CreateTextureFromSurface(render, J);
    SDL_FreeSurface(J);//释放加载图片指针
        //加载K
    SDL_Surface* K = SDL_LoadBMP("./data/K.bmp");
    if (K == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    k = SDL_CreateTextureFromSurface(render, K);
    SDL_FreeSurface(K);//释放加载图片指针
        //加载L
    SDL_Surface* L = SDL_LoadBMP("./data/L.bmp");
    if (L == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    l = SDL_CreateTextureFromSurface(render, L);
    SDL_FreeSurface(L);//释放加载图片指针
        //加载M
    SDL_Surface* M = SDL_LoadBMP("./data/M.bmp");
    if (M == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    m = SDL_CreateTextureFromSurface(render, M);
    SDL_FreeSurface(M);//释放加载图片指针
        //加载N
    SDL_Surface* N = SDL_LoadBMP("./data/N.bmp");
    if (N == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    n = SDL_CreateTextureFromSurface(render, N);
    SDL_FreeSurface(N);//释放加载图片指针
        //加载O
    SDL_Surface* O = SDL_LoadBMP("./data/O.bmp");
    if (O == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    o = SDL_CreateTextureFromSurface(render, O);
    SDL_FreeSurface(O);//释放加载图片指针
        //加载P
    SDL_Surface* P = SDL_LoadBMP("./data/P.bmp");
    if (P == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    p = SDL_CreateTextureFromSurface(render, P);
    SDL_FreeSurface(P);//释放加载图片指针
        //加载Q
    SDL_Surface* Q = SDL_LoadBMP("./data/Q.bmp");
    if (Q == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    q = SDL_CreateTextureFromSurface(render, Q);
    SDL_FreeSurface(Q);//释放加载图片指针
        //加载R
    SDL_Surface* R = SDL_LoadBMP("./data/R.bmp");
    if (R == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    r = SDL_CreateTextureFromSurface(render, R);
    SDL_FreeSurface(R);//释放加载图片指针
        //加载S
    SDL_Surface* S = SDL_LoadBMP("./data/S.bmp");
    if (S == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    s = SDL_CreateTextureFromSurface(render, S);
    SDL_FreeSurface(S);//释放加载图片指针
        //加载T
    SDL_Surface* T = SDL_LoadBMP("./data/T.bmp");
    if (T == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    t = SDL_CreateTextureFromSurface(render, T);
    SDL_FreeSurface(T);//释放加载图片指针
        //加载U
    SDL_Surface* U = SDL_LoadBMP("./data/U.bmp");
    if (U == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    u = SDL_CreateTextureFromSurface(render, U);
    SDL_FreeSurface(U);//释放加载图片指针
        //加载V
    SDL_Surface* V = SDL_LoadBMP("./data/V.bmp");
    if (V == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    v = SDL_CreateTextureFromSurface(render, V);
    SDL_FreeSurface(V);//释放加载图片指针
        //加载W
    SDL_Surface* W = SDL_LoadBMP("./data/W.bmp");
    if (W == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    w = SDL_CreateTextureFromSurface(render, W);
    SDL_FreeSurface(W);//释放加载图片指针
        //加载X
    SDL_Surface* X = SDL_LoadBMP("./data/X.bmp");
    if (X == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    x = SDL_CreateTextureFromSurface(render, X);
    SDL_FreeSurface(X);//释放加载图片指针
        //加载Y
    SDL_Surface* Y = SDL_LoadBMP("./data/Y.bmp");
    if (Y == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    y = SDL_CreateTextureFromSurface(render, Y);
    SDL_FreeSurface(Y);//释放加载图片指针
        //加载Z
    SDL_Surface* Z = SDL_LoadBMP("./data/Z.bmp");
    if (Z == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    z = SDL_CreateTextureFromSurface(render, Z);
    SDL_FreeSurface(Z);//释放加载图片指针
            //加载0
    SDL_Surface* A0 = SDL_LoadBMP("./data/0.bmp");
    if (A0 == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    a0 = SDL_CreateTextureFromSurface(render, A0);
    SDL_FreeSurface(A0);//释放加载图片指针
            //加载1
    SDL_Surface* A1 = SDL_LoadBMP("./data/1.bmp");
    if (A1 == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    a1 = SDL_CreateTextureFromSurface(render, A1);
    SDL_FreeSurface(A1);//释放加载图片指针
            //加载2
    SDL_Surface* A2 = SDL_LoadBMP("./data/2.bmp");
    if (A2 == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    a2 = SDL_CreateTextureFromSurface(render, A2);
    SDL_FreeSurface(A2);//释放加载图片指针
            //加载3
    SDL_Surface* A3 = SDL_LoadBMP("./data/3.bmp");
    if (A3 == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    a3 = SDL_CreateTextureFromSurface(render, A3);
    SDL_FreeSurface(A3);//释放加载图片指针
            //加载4
    SDL_Surface* A4 = SDL_LoadBMP("./data/4.bmp");
    if (A4 == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    a4 = SDL_CreateTextureFromSurface(render, A4);
    SDL_FreeSurface(A4);//释放加载图片指针
            //加载5
    SDL_Surface* A5 = SDL_LoadBMP("./data/5.bmp");
    if (A5 == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    a5 = SDL_CreateTextureFromSurface(render, A5);
    SDL_FreeSurface(A5);//释放加载图片指针
            //加载6
    SDL_Surface* A6 = SDL_LoadBMP("./data/6.bmp");
    if (A6 == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    a6 = SDL_CreateTextureFromSurface(render, A6);
    SDL_FreeSurface(A6);//释放加载图片指针
            //加载7
    SDL_Surface* A7 = SDL_LoadBMP("./data/7.bmp");
    if (A7 == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    a7 = SDL_CreateTextureFromSurface(render, A7);
    SDL_FreeSurface(A7);//释放加载图片指针
            //加载8
    SDL_Surface* A8 = SDL_LoadBMP("./data/8.bmp");
    if (A8 == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    a8 = SDL_CreateTextureFromSurface(render, A8);
    SDL_FreeSurface(A8);//释放加载图片指针
            //加载9
    SDL_Surface* A9 = SDL_LoadBMP("./data/9.bmp");
    if (A9 == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        exit(1);
    }
    a9 = SDL_CreateTextureFromSurface(render, A9);
    SDL_FreeSurface(A9);//释放加载图片指针
}
void draw() {//绘图函数
    switch (status) {
    case 0: {//开始界面
        SDL_SetRenderDrawColor(render, 95, 158, 160, 255);
        SDL_RenderClear(render);
        //实现Start图片缩放
        static float x = 2.0;
        x += 0.02 * a;
        if (x >= 2.5) {
            a = -a;
        }
        if (x <= 2.0) {
            a = -a;
        }
        SDL_Rect destRectStart = { 180 - int(x * 10),250 - int(x * 10),200 + int(x * 20),50 + int(x * 20) };
        SDL_Rect destRectSetup = { 180,350 ,200,50 };
        SDL_Rect destRectExit = { 180,450,200,50 };
        SDL_Rect destRectDoge = { 650 - int(x * 10),440 - int(x * 10),111 + int(x * 20),102 + int(x * 20) };
        SDL_Rect destRectDonnotTouch = { 650,370 ,150,50 };
        SDL_Rect destRectName = { 50,0 ,700,200 };

        SDL_RenderSetScale(render, 1, 1);
        SDL_RenderCopy(render, imageStart, NULL, &destRectStart);
        SDL_RenderCopy(render, imageSetup, NULL, &destRectSetup);
        SDL_RenderCopy(render, imageExit, NULL, &destRectExit);
        SDL_RenderCopy(render, imageDoge, NULL, &destRectDoge);
        SDL_RenderCopy(render, imageName, NULL, &destRectName);
        //如果点击狗狗，设置一个状态
        if (dontouch == 1) {
            SDL_RenderCopy(render, imageDonnotTouch, NULL, &destRectDonnotTouch);

        }
        SDL_RenderPresent(render);
        SDL_Delay(20);//延迟
        break;
        }
    /// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    case 1: {//进入游戏中
        Game();
        break;
    }
    case 2:{//设置界面
        SDL_SetRenderDrawColor(render, 95, 158, 160, 255);
        SDL_RenderClear(render);
        SDL_Rect destRectSet = { 0,0 ,800,600 };
        SDL_Rect destRectMusic = { 500,210 ,20,20 };
        SDL_Rect destRectSoundEffect = { 500,290 ,20,20 };
        SDL_Rect destRectEasy = { 428,375 ,20,20 };
        SDL_Rect destRectHard = { 590,375 ,20,20};
        SDL_RenderCopy(render, imageSet, NULL, &destRectSet);
        if (Music == 1) {
            SDL_RenderCopy(render, imageYes, NULL, &destRectMusic);
        }
        if (SoundEffect == 1) {
            SDL_RenderCopy(render, imageYes, NULL, &destRectSoundEffect);
        }
        if (Difficulty == 0) {
            SDL_RenderCopy(render, imageYes, NULL, &destRectEasy);
        }
        else {
            SDL_RenderCopy(render, imageYes, NULL, &destRectHard);
        }
        SDL_RenderPresent(render);
        SDL_Delay(20);//延迟
        break;
     }
    case 3:{//退出界面
        SDL_SetRenderDrawColor(render, 95, 158, 160, 255);
        SDL_RenderClear(render);
        SDL_Rect destRectLeave = { 0,0 ,800,600 };
        SDL_RenderCopy(render, imageLeave, NULL, &destRectLeave);
        SDL_RenderPresent(render);
        break;
        }
    case 4: {
        SDL_SetRenderDrawColor(render, 95, 158, 160, 255);
        SDL_RenderClear(render);
        SDL_Rect destRectOver = { 0,0 ,800,600 };
        SDL_RenderCopy(render, imageOver, NULL, &destRectOver);
        //创建文字
        int font_x = 360, num[4] = { 0,0,0,0 };
        //分离数字
        num[0] = SCORE / 1000 % 10;
        num[1] = SCORE / 100 % 10;
        num[2] = SCORE / 10 % 10;
        num[3] = SCORE % 10;
        for (int i = 0;i < 4;i++) {
            SDL_Rect destRectFont = { font_x ,290 ,30,30 };font_x += 30;
            if (num[i] == 0) { SDL_RenderCopy(render, a0, NULL, &destRectFont); }
            if (num[i] == 1) { SDL_RenderCopy(render, a1, NULL, &destRectFont); }
            if (num[i] == 2) { SDL_RenderCopy(render, a2, NULL, &destRectFont); }
            if (num[i] == 3) { SDL_RenderCopy(render, a3, NULL, &destRectFont); }
            if (num[i] == 4) { SDL_RenderCopy(render, a4, NULL, &destRectFont); }
            if (num[i] == 5) { SDL_RenderCopy(render, a5, NULL, &destRectFont); }
            if (num[i] == 6) { SDL_RenderCopy(render, a6, NULL, &destRectFont); }
            if (num[i] == 7) { SDL_RenderCopy(render, a7, NULL, &destRectFont); }
            if (num[i] == 8) { SDL_RenderCopy(render, a8, NULL, &destRectFont); }
            if (num[i] == 9) { SDL_RenderCopy(render, a9, NULL, &destRectFont); }
        }
        SDL_RenderPresent(render);
        break;
    }


   }
}
void loop_event() {///事件循环函数
    /////创建事件
    while (1) {
        draw();
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: {status = 3;SDL_Log("关闭按钮被按下");break;}
                case SDL_MOUSEBUTTONUP:
                    if (event.button.x >= 157 && event.button.x <= 400 && event.button.y >= 230 && event.button.y <= 320&& status == 0) {//点击start按钮事件
                        SDL_Log("开始按钮被按下");status = 1;clean();SCORE = 0, TIME = 60000;
                        if (Music == 1) {
                            if (Mix_PausedMusic() == 1) {
                                Mix_ResumeMusic();
                            }
                            else
                            {
                                Mix_PlayMusic(sound, -1);
                            }
                        }
                        else {
                            Mix_PausedMusic();
                        }
                    }
                    if (event.button.x >= 180 && event.button.x <= 380 && event.button.y >= 350 && event.button.y <= 400 && status == 0) {
                        SDL_Log("设置按钮被按下");status = 2;
                    }
                    if (event.button.x >= 180 && event.button.x <= 380 && event.button.y >= 450 && event.button.y <= 500&& status == 0) { SDL_Log("The EXIT button is clicked");
                        status = 3;
                    }
                    if (event.button.x >= 650 && event.button.x <= 756 && event.button.y >= 430 && event.button.y <= 552 && status == 0) {
                        SDL_Log("点了小狗狗一下");dontouch = 1;Mix_PlayChannel(-1, doge, 0);
                    }
                    if (event.button.x >= 127 && event.button.x <= 317 && event.button.y >= 358 && event.button.y <= 444&& status == 3) {
                        SDL_Log("你选择了NO！！！");
                        status = 0;SCORE = 0, TIME = 60000;
                        if (Mix_PlayingMusic() != 0) {
                            Mix_HaltMusic();
                        }
                    }
                    if (event.button.x >= 541 && event.button.x <= 711 && event.button.y >= 363 && event.button.y <= 450 && status == 3) {
                        SDL_Log("你选择了YES！！！");
                        SDL_DestroyTexture(imageStart);//释放贴图
                        SDL_DestroyTexture(imageSetup);
                        SDL_DestroyTexture(imageExit);
                        SDL_DestroyTexture(imageDoge);
                        SDL_DestroyTexture(imageDonnotTouch);
                        SDL_DestroyTexture(imageName);
                        SDL_DestroyRenderer(render);
                        //释放渲染
                        Mix_FreeChunk(doge);
                        Mix_FreeChunk(Over);SDL_DestroyWindow(windows);
                        exit(0);
                    }
                    if (event.button.x >= 677 && event.button.x <= 782 && event.button.y >= 259 && event.button.y <= 313 && status == 1) {
                        SDL_Log("菜单按钮被按下");status = 0;
                        if (Mix_PlayingMusic() != 0) {
                            Mix_HaltMusic();
                        }
                    }
                    if (event.button.x >= 264 && event.button.x <= 551 && event.button.y >= 445 && event.button.y <= 518 && status == 2) {
                        SDL_Log("应用设置按钮被按下");status = 0;
                    }
                    /////////////////////////////////////////////////////////////////////////////////////////////////////音乐控制
                    if (event.button.x >= 498 && event.button.x <= 532 && event.button.y >= 211 && event.button.y <= 236 && status == 2&&Music==1) {
                        SDL_Log("音乐按钮被按下");Music = 0;
                    }
                    else {
                        if (event.button.x >= 498 && event.button.x <= 532 && event.button.y >= 211 && event.button.y <= 236 && status == 2 && Music == 0) {
                            SDL_Log("音乐按钮被按下");Music = 1;
                        }
                    }

                    /// ////////////////////////////////////////////////////////////////////////////////////////////////音效选择
                    if (event.button.x >= 496 && event.button.x <= 530 && event.button.y >= 277 && event.button.y <= 308 && status == 2 && SoundEffect == 1) {
                        SDL_Log("音效按钮被按下");SoundEffect =0;
                    }
                    else {
                        if (event.button.x >= 496 && event.button.x <= 530 && event.button.y >= 277 && event.button.y <= 308 && status == 2 && SoundEffect == 0) {
                            SDL_Log("音效按钮被按下");SoundEffect = 1;
                        }
                    }

                    /////////////////////////////////////////////////////////////////////////////////////////////////////难度模式选择
                    if (event.button.x >= 427 && event.button.x <= 457 && event.button.y >= 373 && event.button.y <= 400 && status == 2 && Difficulty == 1) {
                        SDL_Log("容易模式按钮被按下");Difficulty = 0;
                    }
                    else {
                        if (event.button.x >= 427 && event.button.x <= 457 && event.button.y >= 373 && event.button.y <= 400 && status == 2 && Difficulty == 0) {
                            SDL_Log("容易模式按钮被按下");Difficulty = 1;
                        }
                    }
                    if (event.button.x >= 593 && event.button.x <= 622 && event.button.y >= 377 && event.button.y <= 403 && status == 2 && Difficulty == 1) {
                        SDL_Log("困难模式按钮被按下");Difficulty = 0;
                    }
                    else {
                        if (event.button.x >= 593 && event.button.x <= 622 && event.button.y >= 377 && event.button.y <= 403 && status == 2 && Difficulty == 0) {
                            SDL_Log("困难模式按钮被按下");Difficulty = 1;
                        }
                    }
                    if (event.button.x >= 252 && event.button.x <= 567 && event.button.y >= 433 && event.button.y <= 492 && status == 4) {
                        SDL_Log("返回到菜单按钮被按下");status = 0;
                    }
                    //////////////////////////////////////////////////////////////////////////////////////////////////////
                    SDL_Log("鼠标点击位置(%d %d)", event.button.x, event.button.y);
                case SDL_KEYDOWN: {
                    if (status == 1) {//1为游戏中
                        if(event.key.keysym.sym==SDLK_a){
                            /////逻辑处理函数////////////////////////////////////////////////////////////
                            if(object['A']==0){ SDL_Log("你点错了，扣分！！！");
                                if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;}
                            }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 1) {
                                        zm[i] = 0;cnt--;object['A'] = 0;i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10");}else{ SCORE += 30;SDL_Log("+30");}
                                    }
                                }
                            }
                        ////////////////////////////////////////////////////////////
                        }
                        if (event.key.keysym.sym == SDLK_b) {
                            if (object['B'] == 0) { SDL_Log("你点错了，扣分！！！");
                                if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;}
                            }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 2) {
                                        zm[i] = 0;cnt--;object['B'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10");}else{ SCORE += 30;SDL_Log("+30");}
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_c) {
                            if (object['C'] == 0) { SDL_Log("你点错了，扣分！！！"); if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;} }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 3) {
                                        zm[i] = 0;cnt--;object['C'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_d) {
                            if (object['D'] == 0) { SDL_Log("你点错了，扣分！！！"); if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;} }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 4) {
                                        zm[i] = 0;cnt--;object['D'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_e) {
                            if (object['E'] == 0) { SDL_Log("你点错了，扣分！！！");if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;}  }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 5) {
                                        zm[i] = 0;cnt--;object['E'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_f) {
                            if (object['F'] == 0) { SDL_Log("你点错了，扣分！！！"); if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;} }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 6) {
                                        zm[i] = 0;cnt--;object['F'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_g) {
                            if (object['G'] == 0) { SDL_Log("你点错了，扣分！！！"); if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;} }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 7) {
                                        zm[i] = 0;cnt--;object['G'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_h) {
                            if (object['H'] == 0) { SDL_Log("你点错了，扣分！！！"); if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;} }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 8) {
                                        zm[i] = 0;cnt--;object['H'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_i) {
                            if (object['I'] == 0) { SDL_Log("你点错了，扣分！！！"); if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;} }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 9) {
                                        zm[i] = 0;cnt--;object['I'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_j) {
                            if (object['J'] == 0) { SDL_Log("你点错了，扣分！！！"); if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;} }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 10) {
                                        zm[i] = 0;cnt--;object['J'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_k) {
                            if (object['K'] == 0) { SDL_Log("你点错了，扣分！！！"); if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;} }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 11) {
                                        zm[i] = 0;cnt--;object['K'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_l) {
                            if (object['L'] == 0) { SDL_Log("你点错了，扣分！！！");if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;}  }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 12) {
                                        zm[i] = 0;cnt--;object['L'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_m) {
                            if (object['M'] == 0) { SDL_Log("你点错了，扣分！！！");if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;}  }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 13) {
                                        zm[i] = 0;cnt--;object['M'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_n) {
                            if (object['N'] == 0) { SDL_Log("你点错了，扣分！！！");if (Difficulty == 0) { SCORE -=30; }else{SCORE -= 20;}  }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 14) {
                                        zm[i] = 0;cnt--;object['N'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_o) {
                            if (object['O'] == 0) { SDL_Log("你点错了，扣分！！！");if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;}  }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 15) {
                                        zm[i] = 0;cnt--;object['O'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_p) {
                            if (object['P'] == 0) { SDL_Log("你点错了，扣分！！！"); if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;} }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 16) {
                                        zm[i] = 0;cnt--;object['P'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_q) {
                            if (object['Q'] == 0) { SDL_Log("你点错了，扣分！！！");if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;}  }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 17) {
                                        zm[i] = 0;cnt--;object['Q'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_r) {
                            if (object['R'] == 0) { SDL_Log("你点错了，扣分！！！");if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;}  }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 18) {
                                        zm[i] = 0;cnt--;object['R'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_s) {
                            if (object['S'] == 0) { SDL_Log("你点错了，扣分！！！"); if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;} }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 19) {
                                        zm[i] = 0;cnt--;object['S'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_t) {
                            if (object['T'] == 0) { SDL_Log("你点错了，扣分！！！"); if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;} }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 20) {
                                        zm[i] = 0;cnt--;object['T'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_u) {
                            if (object['U'] == 0) { SDL_Log("你点错了，扣分！！！"); if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;} }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 21) {
                                        zm[i] = 0;cnt--;object['U'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_v) {
                            if (object['V'] == 0) { SDL_Log("你点错了，扣分！！！");if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;}  }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 22) {
                                        zm[i] = 0;cnt--;object['V'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_w) {
                            if (object['W'] == 0) { SDL_Log("你点错了，扣分！！！"); if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;} }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 23) {
                                        zm[i] = 0;cnt--;object['W'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_x) {
                            if (object['X'] == 0) { SDL_Log("你点错了，扣分！！！");if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;}  }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 24) {
                                        zm[i] = 0;cnt--;object['X'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_y) {
                            if (object['Y'] == 0) { SDL_Log("你点错了，扣分！！！");if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;}  }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 25) {
                                        zm[i] = 0;cnt--;object['Y'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        if (event.key.keysym.sym == SDLK_z) {
                            if (object['Z'] == 0) { SDL_Log("你点错了，扣分！！！"); if (Difficulty == 0) { SCORE -= 30; }else{SCORE -= 20;} }
                            else {
                                for (int i = 0;i < 5;i++) {//遍历物体管理器
                                    if (zm[i] == 26) {
                                        zm[i] = 0;cnt--;object['Z'] = 0;SDL_Log("+10");i = 5;
                                        if (Difficulty == 0) { SCORE += 10; SDL_Log("+10"); }
                                        else { SCORE += 30;SDL_Log("+30"); }
                                    }
                                }
                            }
                        }
                        SDL_Log("KEYDOWN %s", SDL_GetKeyName(event.key.keysym.sym));
                    }
                }


            }

        }
    }
}
int WinMain(int argc, char* argv[])///Main函数，程序入口处
{   ////设置视频模式，设置音频模式
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Cannot init Video and audio,%s", SDL_GetError());//如果创建视频与音频模式失败则退出；
        return 1;
    }
    /////创建一个Windows窗口
    windows = SDL_CreateWindow(
        "《是女人就拿到1000分》",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WIDTH, HIGHTH,
        SDL_WINDOW_SHOWN
    );
    if (windows == NULL) {///如果创建窗口失败，则退出；
        SDL_Log("Cannot create Windows,%s", SDL_GetError());
        return 1;
    }
    //screen = SDL_GetWindowSurface(windows);
    ////创建一个渲染
    render = SDL_CreateRenderer(windows, -1, SDL_RENDERER_ACCELERATED);
    ////如果渲染创建失败，则退出；
    if (render == NULL) {
        SDL_Log("Cannot create renderer,%s", SDL_GetError());
        return 1;
    }
    ///创建声音设备
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        SDL_Log("Cannot create Audio1");
        return 1;
    }
    doge = Mix_LoadWAV("./data/doge.wav");
    if (doge == NULL) {
        SDL_Log("Cannot create Audio2");
        return 1;
    }
    sound=Mix_LoadMUS("./data/BGM.wav");
    if (sound == NULL) {
        SDL_Log("Cannot create Audio3");
        return 1;
    }
    Over = Mix_LoadWAV("./data/Over.wav");
    if (Over == NULL) {
        SDL_Log("Cannot create Audio4");
        return 1;
    }

    //////////////////////////////////////////////////////////////////////////////
    //加载图片

    //加载START
    SDL_Surface *imageSTART=SDL_LoadBMP("./data/START.BMP");
    if (imageSTART == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        return 1;
    }
    imageStart=SDL_CreateTextureFromSurface(render, imageSTART);
    SDL_FreeSurface(imageSTART);//释放加载图片指针

    //加载SETUP
    SDL_Surface* imageSETUP = SDL_LoadBMP("./data/SETUP.BMP");
    if (imageSETUP == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        return 1;
    }
    imageSetup = SDL_CreateTextureFromSurface(render, imageSETUP);
    SDL_FreeSurface(imageSETUP);//释放加载图片指针

    //加载EXIT
    SDL_Surface* imageEXIT = SDL_LoadBMP("./data/EXIT.BMP");
    if (imageEXIT == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        return 1;
    }
    imageExit = SDL_CreateTextureFromSurface(render, imageEXIT);
    SDL_FreeSurface(imageEXIT);//释放加载图片指针

    //加载DOGE
    SDL_Surface* imageDOGE = SDL_LoadBMP("./data/DOGE.BMP");
    if (imageDOGE == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        return 1;
    }
    imageDoge = SDL_CreateTextureFromSurface(render, imageDOGE);
    SDL_FreeSurface(imageDOGE);//释放加载图片指针

    //加载Dotnot touch
    SDL_Surface* imageDONNOTTOUCH = SDL_LoadBMP("./data/DONNOT TOUCH ME.BMP");
    if (imageDONNOTTOUCH == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        return 1;
    }
    imageDonnotTouch = SDL_CreateTextureFromSurface(render, imageDONNOTTOUCH);
    SDL_FreeSurface(imageDONNOTTOUCH);//释放加载图片指针
    //加载Name
    SDL_Surface* imageNAME = SDL_LoadBMP("./data/NAME.BMP");
    if (imageNAME == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        return 1;
    }
    imageName = SDL_CreateTextureFromSurface(render, imageNAME);
    SDL_FreeSurface(imageNAME);//释放加载图片指针
        //加载Leave
    SDL_Surface* imageLEAVE = SDL_LoadBMP("./data/LEAVE.BMP");
    if (imageLEAVE == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        return 1;
    }
    imageLeave = SDL_CreateTextureFromSurface(render, imageLEAVE);
    SDL_FreeSurface(imageLEAVE);//释放加载图片指针
    //加载Main
    SDL_Surface* imageMAIN = SDL_LoadBMP("./data/Main.BMP");
    if (imageMAIN == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        return 1;
    }
    imageMain = SDL_CreateTextureFromSurface(render, imageMAIN);
    SDL_FreeSurface(imageMAIN);//释放加载图片指针

        //加载Set
    SDL_Surface* imageSET = SDL_LoadBMP("./data/Set.BMP");
    if (imageSET == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        return 1;
    }
    imageSet = SDL_CreateTextureFromSurface(render, imageSET);
    SDL_FreeSurface(imageSET);//释放加载图片指针

        //加载Yes
    SDL_Surface* imageYES = SDL_LoadBMP("./data/Yes.BMP");
    if (imageYES == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        return 1;
    }
    imageYes = SDL_CreateTextureFromSurface(render, imageYES);
    SDL_FreeSurface(imageYES);//释放加载图片指针
            //加载Over
    SDL_Surface* imageOVER = SDL_LoadBMP("./data/Over.bmp");
    if (imageOVER == NULL) {
        SDL_Log("Cannot load image,%s", SDL_GetError());
        return 1;
    }
    imageOver = SDL_CreateTextureFromSurface(render, imageOVER);
    SDL_FreeSurface(imageOVER);//释放加载图片指针
    /// //////////////////////////////////////////////////////////////////////////////////
    srand((unsigned)time(NULL));
    ////////////////////////////////////////////////////////////////////////////////////////
    Load();
    loop_event(); //事件循环函数

    SDL_DestroyTexture(imageStart);//释放贴图
    SDL_DestroyTexture(imageSetup);
    SDL_DestroyTexture(imageExit);
    SDL_DestroyTexture(imageDoge);
    SDL_DestroyTexture(imageDonnotTouch);
    SDL_DestroyTexture(imageName);
    SDL_DestroyTexture(imageLeave);
    SDL_DestroyRenderer(render);//释放渲染
    //SDL_Delay(30000);
    return 0;
}
