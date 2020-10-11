#ifndef GAMEGUI_H
#define GAMEGUI_H

#include <windows.h>
#include <thread> //c++11 std
#include <tchar.h>
#include "Engine.h"
#include <iostream> //debug

class GameGUI: public Engine {

private:
    HWND handleWindow;
    HDC handleDC;
    HBRUSH handleBrushObject, handleBrushFieldColor, handleBrushAntColor, handleBrushBackgroundColor;
    HPEN handlePenObject, handlePenFieldColor, handlePenAntColor, handlePenBackgroundColor;
    std::thread* playThread;
    int cellSize;
    bool generateStatus, playStatus, isRunning;
    int antOldX, antOldY;
    double gameSpeed;

    void drawAnt(int cx, int cy);
    void drawRectangle(int cx, int cy, HBRUSH colorFill, HPEN colorPen);
    void displayGame();

public:
    GameGUI(HWND& handleWnd, HDC& hdcWnd);
    virtual ~GameGUI() {};
    GameGUI(const GameGUI& cg) {}
    GameGUI& operator=(const GameGUI& cg) {return *this;}

    virtual void play();
    void generateMap();
    void drawNewAntPosition(int mx, int my);
    void stopGame() {playStatus = false;}
    void startGame() {playStatus = true;}
};

#endif // GAMEGUI_H
