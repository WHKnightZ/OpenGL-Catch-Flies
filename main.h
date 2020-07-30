#ifndef MAIN_H
#define MAIN_H

#include "../Library/loadpng.h"
#include "../Library/process_image.h"

#include <GL/glut.h>

#include <math.h>
#include <time.h>

#include <vector>

#include "../Library/gl_texture.h"

#define WIDTH 880
#define HEIGHT 464

#define START_X 80
#define START_Y 80
#define CELL_SIZE 24
#define MAX_X 30
#define MAX_Y 24

#define CLOUD_COUNT 3
#define PLATFORMER_COUNT 6

#define SCALE 3

#define INTERVAL 15

#define PI 3.141592
#define RAD 57.295780

int POS_X, POS_Y;

float BOUNDARY_LEFT = START_X + 30.0f, BOUNDARY_RIGHT = START_X + 690.0f;

int Game_State;

enum GAME_STATE { GAME_PLAY };

float Color_Left_Right[][3] = {{0.600f, 0.819f, 0.945f},
                               {0.345f, 0.561f, 0.698f}},
      Color_Bottom[] = {0.267f, 0.267f, 0.267f};

Rect Rct_Left = {0, START_X - 6.0f, START_Y, HEIGHT},
     Rct_White_Left = {START_X - 6.0f, START_X, START_Y, HEIGHT},
     Rct_Right = {WIDTH - START_X + 6.0f, WIDTH, START_Y, HEIGHT},
     Rct_White_Right = {WIDTH - START_X, WIDTH - START_X + 6.0f, START_Y,
                        HEIGHT},
     Rct_Bottom = {0, WIDTH, 0, START_Y - 6.0f},
     Rct_White_Bottom = {0, WIDTH, START_Y - 6.0f, START_Y};

Image Img_Numbers[10];

Image Img_Background, Img_Ground;

Rect Rct_Background = {START_X, 720 + START_X, 48 + START_Y, 384 + START_Y},
     Rct_Ground = {START_X, 720 + START_X, START_Y, 48 + START_Y};

float Color_White[] = {1.0f, 1.0f, 1.0f};

float Gravity = -1.2f;

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
        Load_Texture(&Img, "Images/Lines.png");
        Crop_Image(&Img, &Img_Save[0], 0, 0, 8, 4);
        Crop_Image(&Img, &Img_Save[1], 0, 4, 8, 4);
        Zoom_Image(&Img_Save[0], SCALE);
        Zoom_Image(&Img_Save[1], SCALE);
        Delete_Image(&Img);

        Rct.Left = -12.0f;
        Rct.Right = 12.0f;
        Rct.Bottom = -8.0f;
        Rct.Top = 8.0f;
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
        x = _x + START_X;
        y = _y + START_Y;
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
        x -= 0.3f;
        if (x < -120.0f)
            x += 1080.0f;
        Update_Rect();
    }

    static void Load_Image() {
        Load_Texture_Swap(&Img_Save, "Images/Cloud.png");
        Zoom_Image(&Img_Save, SCALE);
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
        Zoom_Image(&Img_Save, SCALE);
    }
};

Image c_Platformer::Img_Save;

c_Platformer Platformers[PLATFORMER_COUNT];

class c_Particle {
  public:
    static Image Img_Save;

    Rect Rct;
    Image *Img;

    float x, y, vx, vy, Opacity;

    c_Particle(float _x, float _y, float Angle) {
        x = _x;
        y = _y;
        Angle /= RAD;
        vx = cos(Angle) * 1.0f;
        vy = sin(Angle) * 1.0f;
        Opacity = 1.0f;
        Img = &Img_Save;
        Update_Rect();
    }

    void Update_Rect() {
        Rct.Left = x - Img->w / 2;
        Rct.Right = Rct.Left + Img->w;
        Rct.Bottom = y;
        Rct.Top = Rct.Bottom + Img->h;
    }

    void Draw() {
        glColor4f(1.0f, 1.0f, 1.0f, Opacity);
        Map_Texture(Img);
        Draw_Rect(&Rct);
        glColor3fv(Color_White);
    }

    bool Update() {
        Opacity -= 0.015f;
        if (Opacity < 0.0f)
            return false;

        x += vx;
        y += vy;
        Update_Rect();
        return true;
    }
};

Image c_Particle::Img_Save;

std::vector<c_Particle> Particles;

class c_Fly {
  public:
    static Image Img_Save[2];
    static float ax_Base, ay_Base;
    static float vx_Max, vy_Max;

    Rect Rct;
    Image *Img;

    float x, y, vx, vy, ax, ay, Scale;
    int Timer, Anim, Region;
    bool Is_Alive;

    c_Fly(float _x, float _y, int _Region) {
        x = _x + rand() % 41 - 20 + START_X;
        y = _y + rand() % 41 - 20 + START_Y;
        vx = vx_Max;
        vy = 0.0f;
        ax = ax_Base;
        ay = ay_Base;

        Region = _Region;
        Timer = 0;
        Anim = 0;
        Scale = 0.0f;
        Is_Alive = false;
        Img = &Img_Save[0];

        for (int i = 0; i < 8; i++)
            Particles.push_back(c_Particle(x, y, 45.0f * i));
    }

    void Update_Rect() {
        Rct.Left = x - Img->w / 2 * Scale;
        Rct.Right = Rct.Left + Img->w * Scale;
        Rct.Bottom = y - Img->h / 2 * Scale;
        Rct.Top = Rct.Bottom + Img->h * Scale;
    }

    void Draw() {
        Map_Texture(Img);
        Draw_Rect(&Rct);
    }

    void Update() {
        if (!Is_Alive) {
            Scale += 0.05f;
            if (Scale >= 1.0f) {
                Scale = 1.0f;
                Is_Alive = true;
            }
        }

        x += vx;
        y += vy;
        vx += ax;
        vy += ay;

        if (vx >= vx_Max || vx <= -vx_Max)
            ax = vx < 0 ? ax_Base : -ax_Base;
        if (vy >= vy_Max || vy <= -vy_Max)
            ay = vy < 0 ? ay_Base : -ay_Base;

        Timer++;
        if (Timer == 6) {
            Timer = 0;
            Anim = 1 - Anim;
            Img = &Img_Save[Anim];
        }

        Update_Rect();
    }

    bool Is_Caught(float _x, float _y) {
        if (_x - 20.0f < x && _x + 20.0f > x && _y - 6.0f < y && _y + 34.0f > y)
            return true;
        return false;
    }

    static void Load_Image() {
        Image Img;
        Load_Texture(&Img, "Images/Fly.png");
        Crop_Image(&Img, &Img_Save[0], 0, 0, 10, 6);
        Crop_Image(&Img, &Img_Save[1], 0, 6, 10, 6);
        Crop_Image(&Img, &c_Particle::Img_Save, 0, 12, 2, 2);
        Swap_Image(Img_Save[0].img, 10, 6);
        Swap_Image(Img_Save[1].img, 10, 6);
        Zoom_Image(&Img_Save[0], SCALE);
        Zoom_Image(&Img_Save[1], SCALE);
        Zoom_Image(&c_Particle::Img_Save, SCALE);
    }
};

Image c_Fly::Img_Save[2];
float c_Fly::ax_Base = 0.015f, c_Fly::ay_Base = 0.02f;
float c_Fly::vx_Max = 0.3f, c_Fly::vy_Max = 0.8f;

std::vector<c_Fly> Flies;

class c_Point {
  public:
    float x, y;

    c_Point(float _x, float _y) {
        x = _x;
        y = _y;
    }
};

class c_Spawn_Flies {
  public:
    c_Point Spawn_Points[6] = {
        c_Point(100.0f, 300.0f), c_Point(620.0f, 300.0f),
        c_Point(360.0f, 280.0f), c_Point(360.0f, 130.0f),
        c_Point(100.0f, 120.0f), c_Point(620.0f, 120.0f)};

    int Max_Flies, Count_Spawn_Points, Timer;

    c_Spawn_Flies(int _Max_Flies) {
        Max_Flies = _Max_Flies;
        Timer = 60;
        Count_Spawn_Points = sizeof(Spawn_Points) / sizeof(c_Point);
    }

    void Update() {
        Timer++;
        if (Timer == 90) {
            Timer = 0;
            if (Flies.size() < Max_Flies) {
                bool Check;
                int Region;
                do {
                    Check = false;
                    Region = rand() % Count_Spawn_Points;
                    for (c_Fly Fly : Flies)
                        if (Fly.Region == Region) {
                            Check = true;
                            break;
                        }
                } while (Check);
                Flies.push_back(c_Fly(Spawn_Points[Region].x,
                                      Spawn_Points[Region].y, Region));
            }
        }
    }
};

c_Spawn_Flies Spawn_Flies(2);

class c_Frog {
  public:
    static Image Img_Save[2][2][2]; // Player color, Direction, Animation
    static Image Img_Button_Save[2], Img_Button_Shadow;
    static float Map_Offset[2];
    static float Map_Base_Angle[2];

    Rect Rct, Rct_Button, Rct_Button_Shadow, Rct_Score;
    Image *Img, *Img_Button, *Img_Score;

    float x, y, vx, vy;
    int Player;
    int Drt, Anim;
    int Prepare_Stt;
    bool Is_Jumping;
    bool Is_Jump_Pressed;
    float Angle;
    int Angle_Drt;

    int Score;

    static bool (*Check_Boundary[2])(float x);
    static bool (*Check_Angle[2][2])(float Angle);

    void Init(int _Player) {
        Player = _Player;
        Drt = 1 - Player;
        Anim = 0;

        float Offset = 11.0f * CELL_SIZE * (Player == 0 ? -1 : 1);
        x = WIDTH / 2 + Offset;
        y = CELL_SIZE * 2.0f + START_Y;
        Prepare_Stt = 0;
        Is_Jumping = false;
        Is_Jump_Pressed = false;

        Update_Image();
        Update_Rect();

        Offset *= 1.2f;
        Img_Button = &Img_Button_Save[Player];
        Rct_Button.Left = WIDTH / 2 + Offset - Img_Button->w / 2;
        Rct_Button.Right = Rct_Button.Left + Img_Button->w;
        Rct_Button.Bottom = 24.0f;
        Rct_Button.Top = Rct_Button.Bottom + Img_Button->h;

        Rct_Button_Shadow.Left = Rct_Button.Left + 12.0f;
        Rct_Button_Shadow.Right = Rct_Button.Right + 12.0f;
        Rct_Button_Shadow.Bottom = Rct_Button.Bottom - 12.0f;
        Rct_Button_Shadow.Top = Rct_Button.Top - 12.0f;

        Score = 0;

        Offset *= 0.4f;
        Img_Score = &Img_Numbers[Score];
        Rct_Score.Left = WIDTH / 2 + Offset - Img_Score->w / 2;
        Rct_Score.Right = Rct_Score.Left + Img_Score->w;
        Rct_Score.Bottom = 18.0f;
        Rct_Score.Top = Rct_Score.Bottom + Img_Score->h;
    }

    void Update_Image() { Img = &Img_Save[Player][Drt][Anim]; }

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

    void Draw_Button() {
        Map_Texture(&Img_Button_Shadow);
        Draw_Rect(&Rct_Button_Shadow);
        Map_Texture(Img_Button);
        Draw_Rect(&Rct_Button);
    }

    void Draw_Score() {
        Map_Texture(Img_Score);
        Draw_Rect(&Rct_Score);
    }

    void Key_Down() {
        Is_Jump_Pressed = true;
        Rct_Button.Left += 4.0f;
        Rct_Button.Right += 4.0f;
        Rct_Button.Bottom -= 4.0f;
        Rct_Button.Top -= 4.0f;
    }

    void Key_Up() {
        Is_Jump_Pressed = false;
        Rct_Button.Left -= 4.0f;
        Rct_Button.Right -= 4.0f;
        Rct_Button.Bottom += 4.0f;
        Rct_Button.Top += 4.0f;
    }

    void Prepare_Start() {
        if (Prepare_Stt == 0) {
            Prepare_Stt = 1;
            Angle_Drt = Drt;
            Angle = Map_Base_Angle[Drt];
        }
    }

    void Prepare_End() {
        if (Prepare_Stt == 1)
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
            if (Is_Jump_Pressed)
                Prepare_Start();
            else
                Prepare_End();
        }

        if (!Is_Jumping) {
            if (Prepare_Stt > 0) {
                if (Prepare_Stt == 2) {
                    Prepare_Stt = 0;
                    Jump();
                } else {
                    Angle += Map_Offset[Angle_Drt];
                    if (Check_Angle[Drt][Angle_Drt](Angle))
                        Angle_Drt = 1 - Angle_Drt;

                    float Angle2 = Angle / RAD;
                    float x2 = x, y2 = y + 4.0f, vx2, vy2;
                    vx2 =
                        cos(Angle2) * 4 + (Drt == 0 ? Angle2 - PI : Angle2) * 9;
                    vy2 = sin(Angle2) * 21;
                    vx = vx2;
                    vy = vy2;
                    for (int i = 0; i < 18; i++) {
                        x2 += vx2;
                        y2 += vy2;
                        if (i % 3 == 2) {
                            Angle2 = atan2(vy2, vx2) * RAD;
                            Lines.push_back(c_Line(Player, x2, y2, Angle2));
                        }
                        vy2 += Gravity;
                    }
                }
            }
        } else {
            float y_old = y;
            x += vx;
            y += vy;
            vy += Gravity;

            if (vy < -24.0f)
                vy = -24.0f;

            if (vy <= 0.0f) {
                int col1 = (x - START_X - 9.0f) / CELL_SIZE;
                int col2 = (x - START_X + 9.0f) / CELL_SIZE;
                int row_old = (y_old - START_Y) / CELL_SIZE;
                int row = (y - START_Y) / CELL_SIZE;
                if ((!Map[row_old][col1] && !Map[row_old][col2]) &&
                    (Map[row][col1] || Map[row][col2])) {
                    Is_Jumping = false;
                    y = (row + 1) * CELL_SIZE + START_Y;
                    vx = 0.0f;
                    vy = 0.0f;
                    Anim = 0;
                    Update_Image();
                }
            }

            if (Check_Boundary[Drt](x)) {
                Drt = 1 - Drt;
                vx = -vx;
                Update_Image();
            }

            std::vector<c_Fly>::iterator it = Flies.begin();
            while (it != Flies.end()) {
                if (it->Is_Caught(x, y)) {
                    it = Flies.erase(it);
                    Score++;
                    Img_Score = &Img_Numbers[Score];
                } else
                    it++;
            }

            Update_Rect();
        }
    }

    static bool Check_Boundary_Left(float x) { return x < BOUNDARY_LEFT; }

    static bool Check_Boundary_Right(float x) { return x > BOUNDARY_RIGHT; }

    static bool Check_Angle_Left_Decrease(float Angle) {
        return Angle <= 110.0f;
    }

    static bool Check_Angle_Left_Increase(float Angle) {
        return Angle >= 160.0f;
    }

    static bool Check_Angle_Right_Decrease(float Angle) {
        return Angle <= 20.0f;
    }

    static bool Check_Angle_Right_Increase(float Angle) {
        return Angle >= 70.0f;
    }

    static void Load_Image() {
        Image Img;
        Load_Texture(&Img, "Images/Frogs.png");
        Crop_Image(&Img, &Img_Save[0][1][0], 0, 0, 18, 16);
        Crop_Image(&Img, &Img_Save[0][1][1], 0, 16, 18, 16);
        Crop_Image(&Img, &Img_Save[1][1][0], 18, 0, 18, 16);
        Crop_Image(&Img, &Img_Save[1][1][1], 18, 16, 18, 16);
        Swap_Image(Img_Save[0][1][0].img, 18, 16);
        Swap_Image(Img_Save[0][1][1].img, 18, 16);
        Swap_Image(Img_Save[1][1][0].img, 18, 16);
        Swap_Image(Img_Save[1][1][1].img, 18, 16);
        Zoom_Image(&Img_Save[0][1][0], SCALE);
        Zoom_Image(&Img_Save[0][1][1], SCALE);
        Zoom_Image(&Img_Save[1][1][0], SCALE);
        Zoom_Image(&Img_Save[1][1][1], SCALE);
        Flip_Horizontal(&Img_Save[0][1][0], &Img_Save[0][0][0]);
        Flip_Horizontal(&Img_Save[0][1][1], &Img_Save[0][0][1]);
        Flip_Horizontal(&Img_Save[1][1][0], &Img_Save[1][0][0]);
        Flip_Horizontal(&Img_Save[1][1][1], &Img_Save[1][0][1]);
        Delete_Image(&Img);

        Load_Texture(&Img, "Images/Buttons.png");
        Crop_Image(&Img, &Img_Button_Save[0], 0, 0, 44, 24);
        Crop_Image(&Img, &Img_Button_Save[1], 0, 24, 44, 24);
        Swap_Image(Img_Button_Save[0].img, 44, 24);
        Swap_Image(Img_Button_Save[1].img, 44, 24);
        Zoom_Image(&Img_Button_Save[0], SCALE);
        Zoom_Image(&Img_Button_Save[1], SCALE);

        unsigned char Color_Shadow[] = {0, 0, 0, 50};
        Clone_Image_Shadow(&Img_Button_Save[0], &Img_Button_Shadow,
                           Color_Shadow);
        Delete_Image(&Img);
    }
};

Image c_Frog::Img_Save[2][2][2], c_Frog::Img_Button_Save[2],
    c_Frog::Img_Button_Shadow;
float c_Frog::Map_Offset[2] = {-1.0f, 1.0f};
float c_Frog::Map_Base_Angle[2] = {160.0f, 20.0f};
bool (*c_Frog::Check_Boundary[2])(float x) = {c_Frog::Check_Boundary_Left,
                                              c_Frog::Check_Boundary_Right};
bool (*c_Frog::Check_Angle[2][2])(float Angle) = {
    {Check_Angle_Left_Decrease, Check_Angle_Left_Increase},
    {Check_Angle_Right_Decrease, Check_Angle_Right_Increase}};

c_Frog Frogs[2];

// Prototype

// Function_Pointer
void Game_Display_Play();
void Game_Process_Play();
void Game_Keyboard_Down_Play(GLubyte &key);
void Game_Keyboard_Up_Play(GLubyte &key);

// Variable

void (*Game_Display_Func[])() = {Game_Display_Play};
void (*Game_Process_Func[])() = {Game_Process_Play};
void (*Game_Keyboard_Down_Func[])(GLubyte &key) = {Game_Keyboard_Down_Play};
void (*Game_Keyboard_Up_Func[])(GLubyte &key) = {Game_Keyboard_Up_Play};

// including all referenced .cpp files, you don't need to compile all of them
#include "afunc.cpp"
#include "init.cpp"

#endif
