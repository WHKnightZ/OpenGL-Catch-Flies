#ifndef MAIN_H
#define MAIN_H

#include "../Library/loadpng.h"
#include "../Library/process_image.h"

#include <GL/glut.h>

#include <math.h>

#include <vector>

#include "../Library/gl_texture.h"

/*
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
*/

#define WIDTH 720
#define HEIGHT 384

#define START_X 0
#define START_Y 0
#define CELL_SIZE 8
#define MAX_X 30
#define MAX_Y 24

#define CLOUD_COUNT 3
#define PLATFORMER_COUNT 6

#define SCALE 3.0f

#define INTERVAL 15

#define PI 3.141592
#define RAD 57.295780

int POS_X, POS_Y;
float BOUNDARY_LEFT = 10.0f, BOUNDARY_RIGHT = 230.0f;

int Game_State;

enum GAME_STATE {
    GAME_PLAY
};

Image Img_Background, Img_Ground;
Rect Rct_Background = {0, 240, 16, 128}, Rct_Ground={0,240,0,16};

float Gravity = -0.4f;

int Map[MAX_Y][MAX_X];

class c_Line {
public:
    static Image Img_Save[2];
    static Rect Rct;

    Image *Img;
    float x, y, Angle;
    int Player;

    c_Line(int _Player, float _x, float _y, float _Angle) {
        Player = _Player;
        x = _x;
        y = _y;
        Angle = _Angle;
        Img = &Img_Save[Player];
    }

    void Draw() {
        glTranslatef(x, y, 0.0f);
        glRotatef(Angle, 0.0f, 0.0f, 1.0f);
        Map_Texture(Img);
        Draw_Rect(&Rct);
        glLoadIdentity();
    }

    static void Load_Image() {
        Image Img;
        Load_Texture(&Img, "Images/Line.png");
        Crop_Image(&Img, &Img_Save[0], 0, 0, 8, 4);
        Crop_Image(&Img, &Img_Save[1], 0, 4, 8, 4);
        Swap_Image(Img_Save[0].img, 8, 4);
        Swap_Image(Img_Save[0].img, 8, 4);
        Delete_Image(&Img);

        Rct.Left = -4.0f;
        Rct.Right = 4.0f;
        Rct.Bottom = -2.0f;
        Rct.Top = 2.0f;
    }
};

Image c_Line::Img_Save[2];
Rect c_Line::Rct;

std::vector<c_Line> Lines;

class c_Cloud {
public:
    static Image Img_Save;

    Rect Rct;
    Image *Img;

    float x, y;

    void Init(float _x, float _y) {
        Img = &Img_Save;
        x = _x;
        y = _y;
        Update_Rect();
        Rct.Bottom = y;
        Rct.Top = Rct.Bottom + Img->h;
    }

    void Draw() {
        Map_Texture(Img);
        Draw_Rect(&Rct);
    }

    void Update_Rect() {
        Rct.Left = x - Img->w / 2;
        Rct.Right = Rct.Left + Img->w;
    }

    void Update() {
        x -= 0.1f;
        if (x < -40.0f)
            x += 360.0f;
        Update_Rect();
    }

    static void Load_Image() {
        Load_Texture_Swap(&Img_Save, "Images/Cloud.png");
    }
};

Image c_Cloud::Img_Save;

c_Cloud Clouds[CLOUD_COUNT];

class c_Platformer {
public:
    static Image Img_Save;

    Rect Rct;
    Image *Img;

    void Init(int _x, int _y) {
        Map[_y][_x] = Map[_y][_x + 1] = Map[_y][_x + 2] = Map[_y][_x + 3] = 1;
        Img = &Img_Save;
        float x = START_X + (_x + 2) * CELL_SIZE;
        float y = START_Y + _y * CELL_SIZE;
        Rct.Left = x - Img->w / 2;
        Rct.Right = Rct.Left + Img->w;
        Rct.Bottom = y;
        Rct.Top = Rct.Bottom + Img->h;
    }

    void Draw() {
        Map_Texture(Img);
        Draw_Rect(&Rct);
    }

    static void Load_Image() {
        Load_Texture_Swap(&Img_Save, "Images/Platformer.png");
    }
};

Image c_Platformer::Img_Save;

c_Platformer Platformers[PLATFORMER_COUNT];

class c_Frog {
public:
    static Image Img_Save[2][2][2]; // Player color, Direction, Animation
    static float Map_Offset[2];
    static float Map_Base_Angle[2];

    float x, y, vx, vy;
    Rect Rct;
    Image *Img;
    int Player;
    int Drt, Anim;
    int Prepare_Stt;
    bool Is_Jumping;
    float Angle;
    int Angle_Drt;

    void Init(int _Player) {
        Player = _Player;
        Drt = 1 - Player;
        Anim = 0;
        float Offset = 11.0f * CELL_SIZE * (Player == 0 ? -1 : 1);
        x = WIDTH / SCALE / 2 + Offset;
        y = CELL_SIZE * 2.0f;
        Prepare_Stt = 0;
        Is_Jumping = false;
        Update_Image();
        Update_Rect();
    }

    void Update_Image() {
        Img = &Img_Save[Player][Drt][Anim];
    }

    void Update_Rect() {
        Rct.Left = x - Img->w / 2;
        Rct.Right = Rct.Left + Img->w;
        Rct.Bottom = y;
        Rct.Top = Rct.Bottom + Img->h;
    }

    void Draw() {
        Map_Texture(Img);
        Draw_Rect(&Rct);
    }

    void Prepare_Start() {
        Prepare_Stt = 1;
        Angle_Drt = Map_Offset[Drt];
    	Angle=Map_Base_Angle[Drt];
    }

    void Prepare_End() {
        Prepare_Stt = 2;
    }

    void Jump() {
        if (!Is_Jumping) {
            Is_Jumping = true;
            Anim = 1;
            Update_Image();
        }
    }

    void Update() {
        if (!Is_Jumping) {
            if (Prepare_Stt > 0) {
            	if (Prepare_Stt==2){
            		Prepare_Stt=0;
            		Jump();
				}else{
					Angle+=Angle_Drt;
					bool Check=false;
					if (Angle_Drt==1){
						if (Drt==0){
							if (Angle>=160.0f)
								Check=true;
						}else if (Angle>=70.0f)
							Check=true;
					}else{
						if (Drt==0){
							if (Angle<=110.0f)
								Check=true;
						}else if (Angle<=20.0f)
							Check=true;
					}
					if (Check) Angle_Drt=-Angle_Drt;
					
	                float Angle2 = Angle/RAD;
	                float x2=x,y2=y,vx2,vy2;
	                vx2 = cos(Angle2) * 3 + (Drt==0?(PI-Angle2)*-2:Angle2*2);
	                vy2 = sin(Angle2) * 7;
	                vx=vx2;
	                vy=vy2;
	                for (int i = 0; i < 17; i++) {
	                    x2 += vx2;
	                    y2 += vy2;
	                    if (i % 3 == 1) {
	                        Angle2 = atan2(vy2, vx2) * RAD;
	                        Lines.push_back(c_Line(Player, x2, y2,Angle2));
	                    }
	                    vy2 += Gravity;
	                }
	            }
            }
        } else {
            x += vx;
            y += vy;
            printf("%f\n",vy);
            vy += Gravity;
            if (vy <= 0.0f) {
                int col1 = (x - START_X - 3.0f) / CELL_SIZE;
                int col2 = (x - START_X + 3.0f) / CELL_SIZE;
                int row = (y - START_Y - 5.0f) / CELL_SIZE;
                if (Map[row][col1] || Map[row][col2]) {
                    Is_Jumping = false;
                    y = (row + 1) * CELL_SIZE + START_Y;
                    vx = 0.0f;
                    vy = 0.0f;
                    Anim = 0;
                    Update_Image();
                }
            }
            if (Drt == 0) {
                if (x < BOUNDARY_LEFT) {
                    Drt = 1;
                    vx = -vx;
                    Update_Image();
                }
            } else {
                if (x > BOUNDARY_RIGHT) {
                    Drt = 0;
                    vx = -vx;
                    Update_Image();
                }
            }
            Update_Rect();
        }
    }

    static void Load_Image() {
        Image Img;
        Load_Texture(&Img, "Images/Frog.png");
        Crop_Image(&Img, &Img_Save[0][1][0], 0, 0, 18, 16);
        Crop_Image(&Img, &Img_Save[0][1][1], 0, 16, 18, 16);
        Crop_Image(&Img, &Img_Save[1][1][0], 18, 0, 18, 16);
        Crop_Image(&Img, &Img_Save[1][1][1], 18, 16, 18, 16);
        Swap_Image(Img_Save[0][1][0].img, 18, 16);
        Swap_Image(Img_Save[0][1][1].img, 18, 16);
        Swap_Image(Img_Save[1][1][0].img, 18, 16);
        Swap_Image(Img_Save[1][1][1].img, 18, 16);
        Flip_Horizontal(&Img_Save[0][1][0], &Img_Save[0][0][0]);
        Flip_Horizontal(&Img_Save[0][1][1], &Img_Save[0][0][1]);
        Flip_Horizontal(&Img_Save[1][1][0], &Img_Save[1][0][0]);
        Flip_Horizontal(&Img_Save[1][1][1], &Img_Save[1][0][1]);
        Delete_Image(&Img);
    }
};

Image c_Frog::Img_Save[2][2][2];
float c_Frog::Map_Offset[2]={-1.0f,1.0f};
float c_Frog::Map_Base_Angle[2]={160.0f,20.0f};

c_Frog Frogs[2];

class c_Fly {
public:
};

// Prototype

// Function_Pointer
void Game_Display_Play();
void Game_Process_Play();
void Game_Keyboard_None(GLubyte &key);
void Game_Keyboard_Down_Play(GLubyte &key);
void Game_Keyboard_Up_Play(GLubyte &key);
void Game_Special_None(int &key);
void Game_Special_Play(int &key);

// Variable

void (*Game_Display_Func[])() = {Game_Display_Play};
void (*Game_Process_Func[])() = {Game_Process_Play};
void (*Game_Keyboard_Down_Func[])(GLubyte &key) = {Game_Keyboard_Down_Play};
void (*Game_Keyboard_Up_Func[])(GLubyte &key) = {Game_Keyboard_Up_Play};
void (*Game_Special_Func[])(int &key) = {Game_Special_Play};

// including all referenced .cpp files, you don't need to compile all of them
#include "afunc.cpp"
#include "init.cpp"

#endif
