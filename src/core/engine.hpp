#pragma once

#include "common.hpp"

namespace engine {
	/* for a simple rendering job we need to initialize, set up shader, texture, mesh and send the (M)VP matrix (from camera) to shader */

	void initialize(string window_name, int res_x, int res_y, bool resizable, bool vsync, int gl_major, int gl_minor);
	uint32_t getMs();
	void sleep(uint32_t ms);
	void getWindowSize(int &w, int &h);
	void getScreenSize(int &w, int &h);
	void setViewport(int x, int y, int w, int h);
	void swapBuffer();
	void clearScreen(float r, float g, float b);
	void quit();
}

