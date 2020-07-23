#include "main.h"

void Reload_Game() {
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < MAX_X; j++)
            Map[i][j] = 1;
    for (int i = 2; i < MAX_Y; i++)
        for (int j = 0; j < MAX_X; j++)
            Map[i][j] = 0;

    Clouds[0].Init(570.0f, 210.0f);
    Clouds[1].Init(930.0f, 300.0f);
    Clouds[2].Init(240.0f, 255.0f);

    Platformers[0].Init(7, 5);
    Platformers[1].Init(19, 5);
    Platformers[2].Init(5, 9);
    Platformers[3].Init(21, 9);
    Platformers[4].Init(9, 13);
    Platformers[5].Init(17, 13);

    Frogs[0].Init(0);
    Frogs[1].Init(1);
}

void Init_Game() {
    Load_Texture_Swap(&Img_Background, "Images/Background.png");
    Zoom_Image(&Img_Background, SCALE);
    Load_Texture_Swap(&Img_Ground, "Images/Ground.png");
    Zoom_Image(&Img_Ground, SCALE);
    
    c_Line::Load_Image();
    c_Cloud::Load_Image();
    c_Platformer::Load_Image();
    c_Frog::Load_Image();
    c_Fly::Load_Image();

    Reload_Game();
}

void Init_GL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, WIDTH, HEIGHT);
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glutIgnoreKeyRepeat(GL_TRUE);
    glEnable(GL_TEXTURE_2D);

    Game_State = GAME_PLAY;
}
