#include <iostream>
#include <fstream>
#include <cstdio>
#include <windows.h>
#include <conio.h>
using namespace std;

HANDLE id = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cursorPos;

///////// PAINT WINDOW SIZE /////////

const int width = 20;
const int height = 10;

//////// [MIN: 4 | MAX: 100] ////////


///// FUNCTIONS /////

// log the paint window
void drawMap();

// stops you at the border
void colision();

// prints color at cursor position and next to 'fill' icon
void color(const int set);

//makes you move around [W-S-A-D] && [arrow keys]
void movement(string direction);

// sets cursor position
void posXY(int x, int y);

// changes square color next to 'fill' icon
void changeFillStatus();

// hides/shows this thing that blinks next to cursor
void cursorVisibility(bool visible);

// saves the project to a *.ppm file, which can be opened with photoshop,
// gimp or by converting it to a more common file extension
void saveImgToFile();

void fillAll();
void attributeMenu();
void setColor(const int colorNumber);


///// GLOBAL VARRIABLES /////

int currentColor = 112;

// arrays needed to save the project to a *.ppm file
int Red[100][100] = { 0 };
int Green[100][100] = { 0 };
int Blue[100][100] = { 0 };
int R, G, B;

// representation of your color position
char hero = ' ';

// initial cursor position
int posX = width;
int posY = height;
int RGB_posX = posX / 2 - 2;
int RGB_posY = posY - 4;
int extraX = 0;


int main()
{
	// The x-axis is displayed as 2 times longer due to console formatting.
	// For this reason, at even width, half an uncolored field is left at the right wall.
	// This condition is to prevent this
	if (posX % 2 == 0)
	{
		extraX = 1;
	}

	if (height < 4 || height > 100)
	{
		posXY(20, 10);
		cerr << "The height of the arena should be in the range of [4-100]";
		cin.get();
		return 1;
	}
	if (width < 4 || width > 100)
	{
		posXY(20, 10);
		cerr << "The width of the arena should be in the range of [4-100]";
		cin.get();
		return 1;
	}

	setColor(7);
	cursorVisibility(false);

	drawMap();
	attributeMenu();
	changeFillStatus();

	R = 255; G = 255; B = 255;

	cout << hero << hero;

	while (1)
	{
		Red[RGB_posY][RGB_posX] = R;
		Green[RGB_posY][RGB_posX] = G;
		Blue[RGB_posY][RGB_posX] = B;

		char choose = _getch();

		switch (choose)
		{
			// a-w-s-d //
		case 'a': movement("left");  break;
		case 'w': movement("up");    break;
		case 's': movement("down");  break;
		case 'd': movement("right"); break;
			// a-w-s-d Caps //
		case 'A': movement("left");  break;
		case 'W': movement("up");    break;
		case 'S': movement("down");  break;
		case 'D': movement("right"); break;
			// arrrow keys //
		case 75: movement("left");  break;
		case 72: movement("up");    break;
		case 80: movement("down");  break;
		case 77: movement("right"); break;
			// colors //
		case '1': color(0);    R = 0; G = 0; B = 0; break; //   0 - (black)
		case '2': color(112);  R = 255; G = 255; B = 255; break; //   7 - (grey)
		case '3': color(64);   R = 255; G = 0; B = 0; break; //   4 - (red)
		case '4': color(32);   R = 0; G = 128; B = 0; break; //   2 - (green)
		case '5': color(48);   R = 0; G = 255; B = 255; break; //   3 - (blue)
		case '6': color(80);   R = 255; G = 0; B = 255; break; //   5 - (violet)
		case '7': color(192);  R = 255; G = 127; B = 127; break; //  12 - (pink)
		case '8': color(96);   R = 255; G = 255; B = 0; break; //   6 - (yellow)
		case '9': color(160);  R = 0; G = 255; B = 0; break; //  10 - (light green)
			// attributes //
		case 'n': fillAll();       break;
		case 'N': fillAll();       break;
		case 'v': saveImgToFile(); break;
		case 'V': saveImgToFile(); break;
		}
	}
}


void movement(string direction)
{
	if (direction == "up") { posY--;  RGB_posY--; }
	if (direction == "down") { posY++;  RGB_posY++; }
	if (direction == "left") { posX -= 2; RGB_posX--; }
	if (direction == "right") { posX += 2; RGB_posX++; }

	colision();
	posXY(posX, posY);

	cout << hero << hero;
}


void colision()
{
	if (posX <= 2) { posX += 2; RGB_posX++; }
	if (posX >= width * 2 + 3) { posX -= 2; RGB_posX--; }
	if (posY == 3) { posY++;  RGB_posY++; }
	if (posY == height + 4) { posY--;  RGB_posY--; }
}


void attributeMenu()
{
	posXY(5, 1);

	setColor(7);
	cout << "[1] black  ";

	setColor(7);
	cout << "[2]  ";

	setColor(4);
	cout << "[3]  ";

	setColor(2);
	cout << "[4]  ";

	setColor(3);
	cout << "[5]  ";

	setColor(5);
	cout << "[6]  ";

	setColor(12);
	cout << "[7]  ";

	setColor(6);
	cout << "[8]  ";

	setColor(10);
	cout << "[9]";

	posXY(5, height + 6);
	setColor(7);

	cout << "[n] fill:";

	posXY(5, height + 8);

	cout << "[v] Save to file";
}


void fillAll()
{
	// changes color to the current one in the whole area
	for (int i = 3 + extraX; i < width * 2 + 3 + extraX; i++)
	{
		for (int j = 4; j < height + 4; j++)
		{
			posXY(i, j);
			cout << ' ';
		}
	}

	// choosing current color to set RGB values (needed to *.ppm file)
	switch (currentColor)
	{
	case 0:    R = 0; G = 0; B = 0; break;
	case 112:  R = 255; G = 255; B = 255; break;
	case 64:   R = 255; G = 0; B = 0; break;
	case 32:   R = 0; G = 128; B = 0; break;
	case 48:   R = 0; G = 255; B = 255; break;
	case 80:   R = 255; G = 0; B = 255; break;
	case 192:  R = 255; G = 127; B = 127; break;
	case 96:   R = 255; G = 255; B = 0; break;
	case 160:  R = 0; G = 255; B = 0; break;
	}

	// putting color RGB data into array that represents drawing space
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			Red[i][j] = R;
			Green[i][j] = G;
			Blue[i][j] = B;
		}
	}

	posXY(posX, posY);
	setColor(112);
	if (currentColor == 112) setColor(0);
	cout << hero << hero;
}


void saveImgToFile()
{
	fstream file("image.ppm", ios::out);

	// file head
	file << "P3" << endl
		<< width << ' ' << height << endl
		<< "255" << endl;

	// file body
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			file << Red[j][i] << ' ' << Green[j][i] << ' ' << Blue[j][i] << endl;
		}
	}

	file.close();
	attributeMenu();

	changeFillStatus();

	// something like animation changing 'save' to 'saved'
	posXY(13, height + 8);
	setColor(7);

	cout << "d to file";
	Sleep(1000);
	posXY(13, height + 8);

	cout << " to file ";

	posXY(posX, posY);
	setColor(currentColor);
}


void drawMap()
{
	// top wall
	posXY(2 + extraX, 3);

	for (int i = 3; i < width * 2 + 5; i++)
	{
		cout << "-";
	}

	// bottom wall
	posXY(2 + extraX, height + 4);

	for (int i = 3; i < width * 2 + 5; i++)
	{
		cout << "-";
	}

	// left wall
	for (int i = 4; i < height + 4; i++)
	{
		posXY(2 + extraX, i);

		cout << "|" << endl;
	}

	// right wall
	for (int i = 4; i < height + 4; i++)
	{
		posXY(width * 2 + 3 + extraX, i);

		cout << "|" << endl;
	}
}


void cursorVisibility(bool visible)
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = visible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}


void posXY(int x, int y)
{
	cursorPos.X = x;
	cursorPos.Y = y;
	SetConsoleCursorPosition(id, cursorPos);
}


void color(const int set)
{
	setColor(set);

	posXY(16, height + 6);

	cout << hero << hero;

	posXY(posX, posY);
	cout << hero << hero;

	currentColor = set;
}


void setColor(const int colorNumber)
{
	SetConsoleTextAttribute(id, colorNumber);
}


void changeFillStatus()
{
	setColor(currentColor);

	posXY(16, height + 6);

	cout << hero << hero;

	posXY(posX, posY);
}

//  MADE BY:
//   _______       ___   ____    ____  _______        ______              
//  |       \     /   \  \   \  /   / |   ____|      /      |   _     _   
//  |  .--.  |   /  ^  \  \   \/   /  |  |__        |  ,----' _| |_ _| |_ 
//  |  |  |  |  /  /_\  \  \      /   |   __|       |  |     |_   _|_   _|
//  |  '--'  | /  _____  \  \    /    |  |____      |  `----.  |_|   |_|  
//  |_______/ /__/     \__\  \__/     |_______|      \______|             
//