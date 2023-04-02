#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
using namespace std;
class Maze
{
private:
	
	int currRow=0,max_row;
	
	
	


public:
	string startRow, startCol, goalRow, goalCol, totalCols;
	
	
	
	string map[40][40];

	void readFile(std::ifstream& input);
	void printMaze();
	void paint();
	void makeQuad(int vert_x, int vert_y,int r,int g,int b);
	void printMessage();
	

};
