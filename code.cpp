sai vị trí scale, cop thư viện trước, sau đó tạo project, cài đặt, code 1 file, về sau tách ra, cuối cùng tham khảo code mình up trên github

#include <math.h>
#include <GL/glut.h>
#include <vector>
#include "../Library/loadpng.h"
#include "../Library/process_image.h"
#include "../Library/gl_texture.h"
#define WIDTH 880
#define HEIGHT 464
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	int POS_X = (glutGet(GLUT_SCREEN_WIDTH) - WIDTH) >> 1;
	int POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) >> 1;
	glutInitWindowPosition(POS_X, POS_Y);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Catch Flies");
	glutMainLoop();
	return 0;
}
void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glutSwapBuffers();
}
	glutDisplayFunc(Display);
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
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glEnable(GL_TEXTURE_2D);
}
	Init_GL();
#define INTERVAL 15
void Timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(INTERVAL, Timer, 0);
}
	glutTimerFunc(0, Timer, 0);
	printf("Hello");
float Color_Left_Right[][3] = {{0.600f, 0.819f, 0.945f}, {0.345f, 0.561f, 0.698f}},
	  Color_Bottom[] = {0.267f, 0.267f, 0.267f};
#define START_X 80
#define START_Y 80
Rect Rct_Left = {0, START_X - 6.0f, START_Y, HEIGHT},
	 Rct_White_Left = {START_X - 6.0f, START_X, START_Y, HEIGHT},
	 Rct_Right = {WIDTH - START_X + 6.0f, WIDTH, START_Y, HEIGHT},
	 Rct_White_Right = {WIDTH - START_X, WIDTH - START_X + 6.0f, START_Y, HEIGHT},
	 Rct_Bottom = {0, WIDTH, 0, START_Y - 6.0f},
	 Rct_White_Bottom = {0, WIDTH, START_Y - 6.0f, START_Y};
Rect Rct_Background = {START_X, 720 + START_X, 48 + START_Y, 384 + START_Y},
	 Rct_Ground = {START_X, 720 + START_X, START_Y, 48 + START_Y};
Image Img_Background, Img_Ground;
void Init_Game() {
	Load_Texture_Swap(&Img_Background, "Images/Background.png");
	Zoom_Image(&Img_Background, SCALE);
	Load_Texture_Swap(&Img_Ground, "Images/Ground.png");
	Zoom_Image(&Img_Ground, SCALE);
}
	Init_Game();
	Map_Texture(&Img_Background);
	Draw_Rect(&Rct_Background);
	Map_Texture(&Img_Ground);
	Draw_Rect(&Rct_Ground);
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
	Draw_Frame();
#define CELL_SIZE 24
#define MAX_X 30
#define MAX_Y 24
int Map[MAX_Y][MAX_X];
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < MAX_X; j++)
			Map[i][j] = 1;
	for (int i = 2; i < MAX_Y; i++)
		for (int j = 0; j < MAX_X; j++)
			Map[i][j] = 0;
class c_Platformer {
  public:
	static Image Img_Save;
	static void Load_Image() {
		Load_Texture_Swap(&Img_Save, "Images/Platformer.png");
	}
};
Image c_Platformer::Img_Save;
	c_Platformer::Load_Image();
#define SCALE 3
		Zoom_Image(&Img_Save, SCALE);
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
#define PLATFORMER_COUNT 6
c_Platformer Platformers[PLATFORMER_COUNT];
	Platformers[0].Init(7, 5);
	Platformers[1].Init(19, 5);
	Platformers[2].Init(4, 9);
	Platformers[3].Init(22, 9);
	Platformers[4].Init(9, 13);
	Platformers[5].Init(17, 13);
	for (int i = 0; i < PLATFORMER_COUNT; i++)
		Platformers[i].Draw();
class c_Cloud {
  public:
	static Image Img_Save;
	static void Load_Image() {
		Load_Texture_Swap(&Img_Save, "Images/Cloud.png");
		Zoom_Image(&Img_Save, SCALE);
	}
};
Image c_Cloud::Img_Save;
	c_Cloud::Load_Image();
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
#define CLOUD_COUNT 3
c_Cloud Clouds[CLOUD_COUNT];
	Clouds[0].Init(570.0f, 210.0f);
	Clouds[1].Init(930.0f, 300.0f);
	Clouds[2].Init(240.0f, 255.0f);
	for (int i = 0; i < CLOUD_COUNT; i++)
		Clouds[i].Draw();
	for (int i = 0; i < CLOUD_COUNT; i++)
		Clouds[i].Update();
class c_Frog {
  public:
	static Image Img_Save[2][2][2];
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
		Clone_Image_Shadow(&Img_Button_Save[0], &Img_Button_Shadow, Color_Shadow);
		Delete_Image(&Img);
	}
};
Image c_Frog::Img_Save[2][2][2], c_Frog::Img_Button_Save[2], c_Frog::Img_Button_Shadow;
float c_Frog::Map_Offset[2] = {-1.0f, 1.0f};
float c_Frog::Map_Base_Angle[2] = {160.0f, 20.0f};
c_Frog Frogs[2];
	c_Frog::Load_Image();
	Frogs[0].Init(0);
	Frogs[1].Init(1);
	Frogs[0].Draw();
	Frogs[1].Draw();
float Gravity = -1.2f;
void Keyboard_Down(GLubyte key, int x, int y) {
	switch (key) {
	case 32:
		break;
	case 13:
		break;
	}
}
void Keyboard_Up(GLubyte key, int x, int y) {
	switch (key) {
	case 32:
		break;
	case 13:
		break;
	}
}
	glutKeyboardFunc(Keyboard_Down);
	glutKeyboardUpFunc(Keyboard_Up);
printf("Down");
printf("Up");
	void Jump() {
		if (!Is_Jumping) {
			Is_Jumping = true;
			Anim = 1;
			Update_Image();
		}
	}
	void Update() {
		if (Is_Jumping) {
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
		}
	}
	Frogs[0].Update();
	Frogs[1].Update();
	void Key_Down() {
		Is_Jump_Pressed = true;
	}
	void Key_Up() {
		Is_Jump_Pressed = false;
	}
		Frogs[0].Key_Down();
		Frogs[1].Key_Down();
		Frogs[0].Key_Up();
		Frogs[1].Key_Up();
		vx = 7.0f;
		vy = 7.0f;
		Jump();
float BOUNDARY_LEFT = START_X + 30.0f, BOUNDARY_RIGHT = START_X + 690.0f;
	static bool Check_Boundary_Left(float x) { return x < BOUNDARY_LEFT; }
	static bool Check_Boundary_Right(float x) { return x > BOUNDARY_RIGHT; }
	static bool (*Check_Boundary[2])(float x);
bool (*c_Frog::Check_Boundary[2])(float x) = {c_Frog::Check_Boundary_Left, c_Frog::Check_Boundary_Right};
			if (Check_Boundary[Drt](x)) {
				Drt = 1 - Drt;
				vx = -vx;
				Update_Image();
			}
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
c_Line Line(100.0f, 100.0f, 45.0f);
	c_Line::Load_Image();
	Line.Draw();
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
	static bool (*Check_Angle[2][2])(float Angle);
bool (*c_Frog::Check_Angle[2][2])(float Angle) = {
	{Check_Angle_Left_Decrease, Check_Angle_Left_Increase},
	{Check_Angle_Right_Decrease, Check_Angle_Right_Increase}};
#define PI 3.141592
#define RAD 57.295780
		if (!Is_Jumping) {
			if (Is_Jump_Pressed)
				Prepare_Start();
			else
				Prepare_End();
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
					vx2 = cos(Angle2) * 4 + (Drt == 0 ? Angle2 - PI : Angle2) * 9;
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
		}
	Lines.clear();
class c_Fly {
  public:
	static Image Img_Save[2];
	static float ax_Base, ay_Base;
	static float vx_Max, vy_Max;
	static void Load_Image() {
		Image Img;
		Load_Texture(&Img, "Images/Fly.png");
		Crop_Image(&Img, &Img_Save[0], 0, 0, 10, 6);
		Crop_Image(&Img, &Img_Save[1], 0, 6, 10, 6);
		Swap_Image(Img_Save[0].img, 10, 6);
		Swap_Image(Img_Save[1].img, 10, 6);
		Zoom_Image(&Img_Save[0], SCALE);
		Zoom_Image(&Img_Save[1], SCALE);
	}
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
	bool Is_Catched(float _x, float _y) {
		if (_x - 20.0f < x && _x + 20.0f > x && _y - 6.0f < y && _y + 34.0f > y)
			return true;
		return false;
	}
};
Image c_Fly::Img_Save[2];
float c_Fly::ax_Base = 0.015f, c_Fly::ay_Base = 0.02f;
float c_Fly::vx_Max = 0.3f, c_Fly::vy_Max = 0.8f;
std::vector<c_Fly> Flies;
	c_Fly::Load_Image();
	int Size = Flies.size();
	for (int i = 0; i < Size; i++)
		Flies[i].Draw();
	int Size = Flies.size();
	for (int i = 0; i < Size; i++)
		Flies[i].Update();
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
				Flies.push_back(c_Fly(Spawn_Points[Region].x, Spawn_Points[Region].y, Region));
			}
		}
	}
};
c_Spawn_Flies Spawn_Flies(2);
	Spawn_Flies.Update();
			std::vector<c_Fly>::iterator it = Flies.begin();
			while (it != Flies.end()) {
				if (it->Is_Catched(x, y)) {
					it = Flies.erase(it);
					Score++;
				} else
					it++;
			}
