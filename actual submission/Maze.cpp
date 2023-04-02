#include "Maze.h"

void Maze::readFile(std::ifstream& input)
{
	string wholeLineString; // used to read file one whole line at a time 
	stringstream lineStream; // used to easily get numbers from part of line
	stringstream checkStream;
	int colonLocation; // used to store location of colon in line 
	currRow = 0;
	
	
	while (!input.eof()) {
		lineStream.clear();// just in case 
		int col = 0;
		getline(input, wholeLineString); // read the whole line into a string
		// if there is a colon, set up lineStream to start just after colon 
		// also, remember colonLocation, just in case 
		if ((colonLocation = wholeLineString.find(":")) != string::npos)
		{
			lineStream.str(wholeLineString.substr(colonLocation + 1));
			//std::cout << lineStream.str();
			if (wholeLineString.find("Start:") != string::npos) // find() returns npos when not found 
				lineStream >> startRow >> startCol;

			else if (wholeLineString.find("End:") != string::npos) // find() returns npos when not found 
				lineStream >> goalRow >> goalCol;
			else if (wholeLineString.find("Begin:") != string::npos)
			{
				lineStream >> totalCols;

			}

		}
		

		else 
		{
			string temp;
			checkStream.str(wholeLineString);
			//if we have garbage value in the maze file ignore it
			checkStream >> temp;
			if (temp[0] != '1' && temp[0] != '0')// anything not 1 and 0 is garbage
			{
				continue;
			}
			
			else
			{
				colonLocation = -1;
				lineStream.str(wholeLineString);

				
				while (lineStream >> temp)
				{
					map[currRow][col] = temp;
					col += 1;
				}
				currRow += 1;
			}
			
		}
	}
	max_row = currRow;// save max row
}

void Maze::printMaze()
{// print stored data
	cout << "Start: " << startRow <<" "<< startCol << endl;
	cout << "End: " << goalRow << " " << goalCol << endl;
	cout << "Map Begin: " << totalCols << endl;
	
	for (int i = 0; i < currRow; ++i)// loop through rows and columns and print maze
	{
		for (int j = 0; j < stoi(totalCols); ++j)
		{
			std::cout << map[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	cout << "Map End:"<<endl;

}

void Maze::makeQuad(int vert_x,int vert_y,int r,int g,int b)
{// make a 20x20 quad
	glColor3d(r,g,b);
	glBegin(GL_QUADS); 
		glVertex2f(vert_x, vert_y); 
		glVertex2f(vert_x+20.0, vert_y); 
		glVertex2f(vert_x + 20.0, vert_y+20.0);
		glVertex2f(vert_x, vert_y+20.0); 
	glEnd();

}


void Maze::printMessage()
{// print "Kill Bug" for context
	glColor3ub(0, 120,0); 
	glBegin(GL_QUADS);
	glVertex2i(300, 500);
	glVertex2i(300, 800);
	glVertex2i(800, 800);
	glVertex2i(800, 500);
	glEnd();
	glColor3ub(0, 0, 255);
	glRasterPos2i(400, 600);  
	YsGlDrawFontBitmap20x32("Kill the Bug !!");
	glRasterPos2i(400, 700);
	YsGlDrawFontBitmap20x32("Press 'R' to reset");

	
}



void Maze::paint()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	int vert_x = 0, vert_y = 0;
	
	
	
	for (int i = 0; i < 40; ++i)
	{
		for (int j = 0; j < 40;++j)
		{
			if (map[i][j] =="1")
			{// if we have '1' in maze it is an obstacle
				makeQuad(vert_x, vert_y,0,0,0);
				
			}
			else 
			{
				if (i>=max_row || j>=stoi(totalCols))
				{//beyond the maze size make blue quads (I am color blind, 
				// blue is easier to identify)
					makeQuad(vert_x, vert_y, 255,255,255);
					makeQuad(vert_x, vert_y, 0, 140, 140);

				}
			}

			vert_x += 20;
			
		}
		vert_y += 20;
		vert_x = 0;

		
	}
	//print start and goal
	makeQuad(20 * (stoi(startCol)-1), 20 * (stoi(startRow)-1), 0, 255,0);
	makeQuad(20 * (stoi(goalCol)-1), 20 * (stoi(goalRow)-1), 255, 0, 0);
	printMessage();


}


