#include "main.h"

// Display

void Draw_Frame() {
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glColor3fv(Color_Left_Right[0]);
    glVertex2f(Rct_Left.Left, Rct_Left.Bottom);
    glVertex2f(Rct_Left.Right, Rct_Left.Bottom);
    glColor3fv(Color_Left_Right[1]);
    glVertex2f(Rct_Left.Right, Rct_Left.Top);
    glVertex2f(Rct_Left.Left, Rct_Left.Top);

    glColor3fv(Color_Left_Right[0]);
    glVertex2f(Rct_Right.Left, Rct_Right.Bottom);
    glVertex2f(Rct_Right.Right, Rct_Right.Bottom);
    glColor3fv(Color_Left_Right[1]);
    glVertex2f(Rct_Right.Right, Rct_Right.Top);
    glVertex2f(Rct_Right.Left, Rct_Right.Top);

    glColor3fv(Color_Bottom);
    glVertex2f(Rct_Bottom.Left, Rct_Bottom.Bottom);
    glVertex2f(Rct_Bottom.Right, Rct_Bottom.Bottom);
    glVertex2f(Rct_Bottom.Right, Rct_Bottom.Top);
    glVertex2f(Rct_Bottom.Left, Rct_Bottom.Top);

    glColor3fv(Color_White);
    glVertex2f(Rct_White_Left.Left, Rct_White_Left.Bottom);
    glVertex2f(Rct_White_Left.Right, Rct_White_Left.Bottom);
    glVertex2f(Rct_White_Left.Right, Rct_White_Left.Top);
    glVertex2f(Rct_White_Left.Left, Rct_White_Left.Top);

    glVertex2f(Rct_White_Right.Left, Rct_White_Right.Bottom);
    glVertex2f(Rct_White_Right.Right, Rct_White_Right.Bottom);
    glVertex2f(Rct_White_Right.Right, Rct_White_Right.Top);
    glVertex2f(Rct_White_Right.Left, Rct_White_Right.Top);

    glVertex2f(Rct_White_Bottom.Left, Rct_White_Bottom.Bottom);
    glVertex2f(Rct_White_Bottom.Right, Rct_White_Bottom.Bottom);
    glVertex2f(Rct_White_Bottom.Right, Rct_White_Bottom.Top);
    glVertex2f(Rct_White_Bottom.Left, Rct_White_Bottom.Top);
    glEnd();
    glEnable(GL_TEXTURE_2D);
}

void Game_Display_Play() {
    glLoadIdentity();

    Map_Texture(&Img_Background);
    Draw_Rect(&Rct_Background);

    for (int i = 0; i < CLOUD_COUNT; i++)
        Clouds[i].Draw();

    for (c_Line Line : Lines)
        Line.Draw();

    Map_Texture(&Img_Ground);
    Draw_Rect(&Rct_Ground);

    for (int i = 0; i < PLATFORMER_COUNT; i++)
        Platformers[i].Draw();

    int Size = Flies.size();
    for (int i = 0; i < Size; i++)
        Flies[i].Draw();

    Size = Particles.size();
    for (int i = 0; i < Size; i++)
        Particles[i].Draw();

    Frogs[0].Draw();
    Frogs[1].Draw();

    Draw_Frame();

    Frogs[0].Draw_Button();
    Frogs[1].Draw_Button();

    Frogs[0].Draw_Score();
    Frogs[1].Draw_Score();
}

// Process

void Game_Process_Play() {
    for (int i = 0; i < CLOUD_COUNT; i++)
        Clouds[i].Update();

    int Size = Flies.size();
    for (int i = 0; i < Size; i++)
        Flies[i].Update();

    std::vector<c_Particle>::iterator it = Particles.begin();
    while (it != Particles.end()) {
        if (!it->Update())
            it = Particles.erase(it);
        else
            it++;
    }

    Lines.clear();
    Frogs[0].Update();
    Frogs[1].Update();

    Spawn_Flies.Update();

    glutPostRedisplay();
}

// Keyboard

void Game_Keyboard_Down_Play(GLubyte &key) {
    switch (key) {
    case 32:
        Frogs[0].Key_Down();
        break;
    case 13:
        Frogs[1].Key_Down();
        break;
    }
}

void Game_Keyboard_Up_Play(GLubyte &key) {
    switch (key) {
    case 32:
        Frogs[0].Key_Up();
        break;
    case 13:
        Frogs[1].Key_Up();
        break;
    }
}
