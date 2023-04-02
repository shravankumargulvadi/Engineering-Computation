#include "Maze.h"
#include "Entity.h"



int chooseLevel(void)
{//ask user to choose level and return it
	int level;
	cout << "Choose level to play: " << endl << "Press '1' for level-1" << endl;
	cout << "Press '2' for level-2" << endl << "Press '3' for level-3" << endl << "Level:";
	cin >> level;
	return level;
}


int main()
{
	int level = chooseLevel();
	FsOpenWindow(5, 5, 800, 800, 0, "Maze Game");
	while (level != 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		int key;
		Maze aMaze;
		Entity entity;

		//read the maps as per the level variable
		if (level == 1)
		{
			std::ifstream inFile1("mazeA_10x10.map");
			aMaze.readFile(inFile1);
		}
		else if (level == 2)
		{
			std::ifstream inFile2("mazeB_25x25.map");
			aMaze.readFile(inFile2);
		}
		else
		{
			std::ifstream inFile3("mazeC_40x20.map");
			aMaze.readFile(inFile3);
		}
		
		entity.entity_row = stoi(aMaze.startRow);
		entity.entity_col = stoi(aMaze.startCol);

		while (FSKEY_NULL == FsInkey())
		{
			//paint maze and entity
			aMaze.paint();
			entity.drawEntity(20 * (entity.entity_col - 1), 20 * (entity.entity_row - 1), 1, 0, 0, 125);
			glFlush();
			FsPollDevice();
			key = FsInkey();
			if (entity.reachedGoal(aMaze))
			{//if goal is reached kill the bug and celebrate
				entity.killEntity(aMaze);
				glFlush();
				entity.celebrate();
				if (level <= 2)
				{
					level += 1;
					break;
				}
				else
				{
					cout << "You Win!!!!";
					break;
				}
			}
			// take keyboard input and call move function
			if (key == FSKEY_ESC)
			{
				return 0;
			
			}
			else
			{
				entity.move(aMaze, key);
			}
			
		}
	}
}