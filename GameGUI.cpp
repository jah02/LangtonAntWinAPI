#include "GameGUI.h"

extern const int WINDOW_X;
extern const int WINDOW_Y;

GameGUI::GameGUI(HWND& hwndWnd, HDC& hdcWnd) : Engine() {
    handleWindow = hwndWnd;
    handleDC = hdcWnd;
    cellSize = 10;
    generateStatus = true;
    playStatus = true;
    isRunning = false;
    antOldX = 0;
    antOldY = 0;
    gameSpeed = 0.03;

    handleBrushAntColor = CreateSolidBrush(RGB(255, 0, 0)); //RED
    handlePenAntColor = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    handleBrushFieldColor = CreateSolidBrush(RGB(0, 255, 0)); //GREEN
    handlePenFieldColor = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    handleBrushBackgroundColor = CreateSolidBrush(RGB(200, 200, 200)); //GREY
    handlePenBackgroundColor = CreatePen(PS_SOLID, 1, RGB(200, 200, 200));
}



void GameGUI::play() {
    if(!isRunning && !generateStatus) {
        playThread = new std::thread(&GameGUI::displayGame, this);
        isRunning = true;
    } else
        playStatus = true;
}

void GameGUI::displayGame() {
    while(true) {
        if(playStatus) {
            Engine::play();

            if(!getMapCellStatus(antOldX, antOldY))
                drawRectangle(antOldX, antOldY, handleBrushBackgroundColor, handlePenBackgroundColor);
            else
                drawRectangle(antOldX, antOldY, handleBrushFieldColor, handlePenFieldColor);

            antOldX = getAntPosX();
            antOldY = getAntPosY();

            drawAnt(getAntPosX(), getAntPosY());
            UpdateWindow(handleWindow);
        }
        Sleep(gameSpeed*1000);
    }
}

void GameGUI::generateMap() {
    if(generateStatus) {
        POINT oldPoint;

        //vertical
        for(int i=0; i<=WINDOW_X; i+=cellSize) {
            MoveToEx(handleDC, i, 100, &oldPoint);
            LineTo(handleDC, i, WINDOW_Y);
        }

        //horizontal
        for(int i=100; i<=WINDOW_Y; i+=cellSize) {
            MoveToEx(handleDC, 0, i, &oldPoint);
            LineTo(handleDC, WINDOW_X-9, i); //-9 draw correction
        }

        handleBrushObject = (HBRUSH) SelectObject(handleDC, handleBrushAntColor);
        handlePenObject = (HPEN) SelectObject(handleDC, handlePenAntColor);
        Ellipse(handleDC, (getAntPosX()*10)+10, (getAntPosY()*10)+102, (getAntPosX()*10)+2, (getAntPosY()*10)+110);

        generateStatus = false;
    }
}

void GameGUI::drawAnt(int cx, int cy) {
    int xStart = 0;
    int yStart = 0;
    int xStop = 0;
    int yStop = 0;

    if(cx == 0) {
        xStart = 2;
        xStop = 10;
    } else {
        xStart = (cx*10)+10;
        xStop = cx*10+2;
    }

    if(cy == 0) {
        yStart = 102;
        yStop = 110;
    } else {
        yStart = (cy*10)+102;
        yStop = (cy*10)+110;
    }

    handleBrushObject = (HBRUSH) SelectObject(handleDC, handleBrushAntColor);
    handlePenObject = (HPEN) SelectObject(handleDC, handlePenAntColor);
    Ellipse(handleDC, xStart, yStart, xStop, yStop);
}

void GameGUI::drawRectangle(int cx, int cy, HBRUSH colorFill, HPEN colorPen) {
    int xStart = 0;
    int yStart = 0;
    int xStop = 0;
    int yStop = 0;

    if(cx == 0) {
        xStart = 2;
        xStop = 10;
    } else {
        xStart = (cx*10)+10;
        xStop = cx*10+2;
    }

    if(cy == 0) {
        yStart = 102;
        yStop = 110;
    } else {
        yStart = (cy*10)+102;
        yStop = (cy*10)+110;
    }

    handleBrushObject = (HBRUSH) SelectObject(handleDC, colorFill);
    handlePenObject = (HPEN) SelectObject(handleDC, colorPen);
    Rectangle(handleDC, xStart, yStart, xStop, yStop);
}

void GameGUI::drawNewAntPosition(int mx, int my) {
    if(!generateStatus) {
        int mapX = 0;
        int mapY = 0;
        int oldAntX = getAntPosX();
        int oldAntY = getAntPosY();

        if(mx < 10)
            mapX = 0;
        else
            mapX = (mx/10);

        if((my < 110) && (my >= 100))
            mapY = 0;
        else
            mapY = (my/10)-10;

        if(setAntPos(mapX, mapY)) {
            drawRectangle(oldAntX, oldAntY, handleBrushBackgroundColor, handlePenBackgroundColor);
            drawAnt(mapX, mapY);

            antOldX = mapX;
            antOldY = mapY;
        }
    }
}


