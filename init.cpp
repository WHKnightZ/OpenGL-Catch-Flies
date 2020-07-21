#include "main.h"

void Reload_Game() {
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < MAX_X; j++)
            Map[i][j] = 1;
    for (int i = 2; i < MAX_Y; i++)
        for (int j = 0; j < MAX_X; j++)
            Map[i][j] = 0;

    Clouds[0].Init(190.0f, 70.0f);
    Clouds[1].Init(310.0f, 100.0f);
    Clouds[2].Init(80.0f, 85.0f);

    Platformers[0].Init(7, 5);
    Platformers[1].Init(19, 5);
    Platformers[2].Init(5, 9);
    Platformers[3].Init(21, 9);
    Platformers[4].Init(9, 13);
    Platformers[5].Init(17, 13);

    Frogs[0].Init(0);
    Frogs[1].Init(1);

//    float Angle=70.0f*3.141592653/180;
//    float vx=cos(Angle)*7.0f;
//    float vy=sin(Angle)*7.0f;
//    float x=10.0f,y=10.0f;
//    float oldx=x,oldy=y;
//    Gravity=-0.5f;
//    for (int i=0;i<20;i++){
//    	x+=vx;
//    	y+=vy;
//    	if ((x-oldx)*(x-oldx)+(y-oldy)*(y-oldy)>=90.0f){
//    		oldx=x;
//    		oldy=y;
//    		Angle=atan2(vy,vx)*180/3.141592653f;
//    		Lines.push_back(c_Line(0,x,y,Angle));
//		}
//    	vy+=Gravity;
//	}
}

void Init_Game() {
    Load_Texture_Swap(&Img_Background, "Images/Background.png");
    c_Line::Load_Image();
    c_Cloud::Load_Image();
    c_Platformer::Load_Image();
    c_Frog::Load_Image();

    Reload_Game();
}

void Init_GL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, WIDTH, HEIGHT);
    gluOrtho2D(0, WIDTH / SCALE, 0, HEIGHT / SCALE);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glutIgnoreKeyRepeat(GL_TRUE);
    glEnable(GL_TEXTURE_2D);

    Game_State = GAME_PLAY;
}
