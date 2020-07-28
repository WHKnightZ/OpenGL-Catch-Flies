#include <math.h>
#include <time.h>
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
		Zoom_Image(&Img_Save, SCALE);
	}
};
Image c_Platformer::Img_Save;
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