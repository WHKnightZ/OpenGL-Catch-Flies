#include "main.h"

// Display

void Game_Display_Play() {
    glLoadIdentity();

    Map_Texture(&Img_Background);
    Draw_Rect(&Rct_Background);

    for (int i = 0; i < CLOUD_COUNT; i++)
        Clouds[i].Draw();

    for (c_Line Line : Lines)
        Line.Draw();

    for (int i = 0; i < PLATFORMER_COUNT; i++)
        Platformers[i].Draw();

    Frogs[0].Draw();
    Frogs[1].Draw();
}

// Process

void Game_Process_Play() {
    for (int i = 0; i < CLOUD_COUNT; i++)
        Clouds[i].Update();

    Lines.clear();
    Frogs[0].Update();
    Frogs[1].Update();

    glutPostRedisplay();
}

// Keyboard

void Game_Keyboard_None(GLubyte &key) {
}

void Game_Keyboard_Play(GLubyte &key) {
    Frogs[0].Jump(4, 7);
}

// Special

void Game_Special_None(int &key) {
}

void Game_Special_Play(int &key) {
}
