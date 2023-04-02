#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "fssimplewindow.h"
#include "Maze.h"
#include <chrono>
#include <algorithm>
#include "yssimplesound.h"


using namespace std;

class Entity
{

	public:
		
	int entity_row, entity_col;

	void move(Maze& aMaze, int direction);
	void paint(Maze& aMaze, int direction,int r, int g, int b);
	bool reset(Maze& aMaze); // places entity at maze start 
	bool reachedGoal(Maze& aMaze);
	bool isNavigable(Maze& aMaze,int row, int col);
	void celebrate();
	void drawEntity(int vert_x, int vert_y,int inflation, int r, int g, int b);
	void killEntity(Maze aMaze);
	

	void erase(Maze& aMaze);


};
