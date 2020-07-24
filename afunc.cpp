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

    Map_Texture(&Img_Ground);
    Draw_Rect(&Rct_Ground);

	for (c_Particle Particle: Particles)
		Particle.Draw();
		
    for (int i = 0; i < PLATFORMER_COUNT; i++)
        Platformers[i].Draw();

    Frogs[0].Draw();
    Frogs[1].Draw();
}

// Process

void Game_Process_Play() {
    for (int i = 0; i < CLOUD_COUNT; i++)
        Clouds[i].Update();

	for (c_Particle Particle: Particles)
		Particle.Update();
	
    Lines.clear();
    Frogs[0].Update();
    Frogs[1].Update();

    glutPostRedisplay();
}

// Keyboard

void Game_Keyboard_None(GLubyte &key) {

}

void Game_Keyboard_Down_Play(GLubyte &key) {
    switch(key) {
    case 32:
//    	for (int i=0;i<10;i++)
    		Particles.push_back(c_Particle(100,100,0));
        Frogs[0].Key_Down();
        break;
    case 13:
        Frogs[1].Key_Down();
        break;
    }
}

void Game_Keyboard_Up_Play(GLubyte &key) {
    switch(key) {
    case 32:
        Frogs[0].Key_Up();
        break;
    case 13:
        Frogs[1].Key_Up();
        break;
    }
}

// Special

void Game_Special_None(int &key) {
}

void Game_Special_Play(int &key) {
}
