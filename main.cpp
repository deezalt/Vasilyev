
// No warnings
#define _CRT_SECURE_NO_WARNINGS

// OpenGL
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")

// Includes
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <time.h>

#include <string>
//#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glext.h>
using namespace std;

// Engine
#include "files/defines.cpp"
#include "other.cpp"
#include "keyboard.cpp"
#include "mouse.cpp"
#include "view.cpp"
#include "display.cpp"
#include "texture.cpp"
#include "files/textures.cpp"
#include "window.cpp"
#include "object.cpp"
#include "files/functions.h"
#include "files/objects.cpp"
#include "room.cpp"
#include "files/rooms.cpp"
#include "files/functions.cpp"

// Main function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Creating window
	if (!window.create(GM_TITLE, GM_FULL,
		(display.width - GM_WIDTH) / 2,
		(display.height - GM_HEIGHT) / 2,
		GM_WIDTH, GM_HEIGHT)) return 0;

	GM_loadTextures();
	room.set(r_start);

	// Variables
	float timeStep = 1000.0 / fps;
	int timeNow = clock(), timeSleep, timeStart = timeNow, timeEnd = timeStart + 1000, frame = 0;
	MSG msg;
	//genmap("map2.bmp");
	//genmap("map2x2.bmp");
	//genmap("map10x10.bmp",10,10);
	// Main cycle
	while (GM_game)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		GM_step();
		
		if (!GM_transition())
			GM_draw();

		if ((timeSleep = timeStart + timeStep * ++frame - (timeNow = clock())) > 0)
		{
			timeNow += timeSleep;
			Sleep(timeSleep);
		}

		if (timeEnd <= timeNow)
		{
			fps = frame;
			frame = 0;
			timeStart = timeNow;
			timeEnd = timeNow + 1000;
			//window.setTitle(str(fps));
		}
	}

	// App end
	GM_deleteObjects();
	GM_unloadTextures();
	window.destroy();
	return 0;
}
