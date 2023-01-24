//
// Created by caigou on 2023-01-23.
//
#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>

class Button {
private:
    int scene;
    int mX;
    int mY;
    int mWidth;
    int mHeight;
public:
    Button(){}
    Button(int x,int y,int w, int h){
        setRect(x,y,w,h);
    }
    ~Button(){}

    bool checkClicked(SDL_Event *event);

    void setMx(int mX) {
        Button::mX = mX;
    }

    void setMy(int mY) {
        Button::mY = mY;
    }

    void setMWidth(int mWidth) {
        Button::mWidth = mWidth;
    }

    void setMHeight(int mHeight) {
        Button::mHeight = mHeight;
    }

    int getMx() const {
        return mX;
    }

    int getMy() const {
        return mY;
    }

    int getMWidth() const {
        return mWidth;
    }

    int getMHeight() const {
        return mHeight;
    }

    void setRect(int x, int y, int w, int h) {
        Button::mX = x;
        Button::mY = y;
        Button::mWidth = w;
        Button::mHeight = h;
    }


};

bool Button::checkClicked(SDL_Event *event) {
    if (event->button.x >= Button::mX && event->button.x <= (Button::mX + Button::mWidth) &&
        event->button.y >= Button::mY && event->button.y <= (Button::mY + Button::mHeight)) {
        return true;
    }
    return false;
}

#endif BUTTON_H



