#pragma once

#include "common.hpp"

namespace engine {
	void initialize(string window_name, int res_x, int res_y, bool resizable, int gl_major, int gl_minor);
	uint32_t getMs();
	
	void getWindowSize(int &w, int &h);
	void getScreenSize(int &w, int &h);
	void setViewport(int x, int y, int w, int h);
	void swapBuffer();
	void clearScreen(float r, float g, float b);
	void quit();
}

