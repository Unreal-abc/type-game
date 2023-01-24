//
// Created by caigou on 2023-01-23.
//
#pragma once
#ifndef LTEXTURE_H
#define LTEXTURE_H

#include "SDL.h"
#include "iostream"
#include "button.hpp"

class LTexture : public Button {
private:
    //The actual hardware texture
    SDL_Renderer *renderer;
    SDL_Texture *mTexture;
public:
    LTexture():Button(){

    }

    LTexture(SDL_Renderer *renderer):Button(){
        LTexture::renderer = renderer;
        mTexture = NULL;
        Button::setMWidth(0);
        Button::setMHeight(0);
        Button::setMx(0);
        Button::setMy(0);
    }

    ~LTexture(){

    }

    bool loadFromFile(std::string path);

    void free();

    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    void setBlendMode(SDL_BlendMode blending);

    void setAlpha(Uint8 alpha);

    void render(int x = -1, int y = -1, int w = -1, int h = -1);
    void render(SDL_Rect srcrect,SDL_Rect dstrect){
        SDL_RenderCopy(LTexture::renderer, mTexture, &srcrect, &dstrect);
    }

    bool changeTheXAndY = false;


};

bool LTexture::loadFromFile(std::string path) {
    free();
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(LTexture::renderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        } else {
            //Get image dimensions
            Button::setMWidth(loadedSurface->w);
            Button::setMHeight(loadedSurface->h);
        }
        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free() {
    //Free texture if it exists
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        Button::setMWidth(0);
        Button::setMHeight(0);
    }
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    //Modulate texture rgb
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending) {
    //Set blending function
    SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha) {
    //Modulate texture alpha
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, int w, int h) {
    SDL_Rect renderQuad = {x, y, w, h};
    if (x == -1)renderQuad.x = Button::getMx();
    if (y == -1)renderQuad.y = Button::getMy();
    if (w == -1)renderQuad.w = Button::getMWidth();
    if (h == -1)renderQuad.h = Button::getMHeight();
    Button::setRect(x,y,w,h);
    SDL_RenderCopy(LTexture::renderer, mTexture, NULL, &renderQuad);
}


#endif LTEXTURE_H

