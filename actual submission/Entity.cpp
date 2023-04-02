#include "Entity.h"

void Entity::move(Maze& aMaze, int direction)
{
	// first check if the chosen direction is navigable 
	// if so erase present cell and draw a new one
	if (direction == FSKEY_UP)
	{
		if (isNavigable(aMaze,entity_row-1,entity_col))
		{
			//cout << "move up";
			erase(aMaze);
			entity_row = entity_row - 1;
			paint(aMaze, direction, 0, 255, 0);
		}
		
		
		

	}
	else if (direction == FSKEY_DOWN)
	{
		if (isNavigable(aMaze, entity_row+1,entity_col))
		{
			//cout << "move down";
			erase(aMaze);
			entity_row = entity_row + 1;
			paint(aMaze, direction, 0, 255, 0);
		}

	}
	else if (direction == FSKEY_LEFT)
	{
		if (isNavigable(aMaze,entity_row,entity_col-1))
		{
			//cout << "move Left";
			erase(aMaze);
			entity_col = entity_col - 1;
			paint(aMaze, direction, 0, 255, 0);
		}
		

	}
	else if (direction == FSKEY_RIGHT)
	{
		if (isNavigable(aMaze, entity_row,entity_col+1))
		{
			//cout << "move right";
			erase(aMaze);
			entity_col = entity_col + 1;
			paint(aMaze, direction, 0, 255, 0);
		}

	}

	else if(direction == FSKEY_R)
		{// if user has pressed R-reset
		erase(aMaze);
		reset(aMaze);
		}

}

void Entity::erase(Maze& aMaze)
{//erase by painting a white quad
	aMaze.makeQuad(20 * (entity_col - 1), 20 * (entity_row - 1), 255,255,255);
	
}

void Entity::paint(Maze& aMaze, int direction,int r,int g, int b)
{// Paint is same as draw
	
	drawEntity(20 * (entity_col - 1), 20 * (entity_row - 1),1,0,0,125);


}

bool Entity::reset(Maze& aMaze) // places entity at maze start
{// move the entity back to start
	entity_row = stoi(aMaze.startRow);
	entity_col = stoi(aMaze.startCol);
	drawEntity(20 * (entity_col - 1), 20 * (entity_row - 1), 1, 0, 0, 125);
	
	return true;

}
bool Entity::reachedGoal(Maze& aMaze)
{// check if goal has been reached return true only if we have reached
	if (stoi(aMaze.goalRow) == entity_row && stoi(aMaze.goalCol) == entity_col)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Entity::isNavigable(Maze& aMaze,int row, int col)
{// check is tyhe requested direction is an obstacle return false if it is
	if (aMaze.map[row - 1][col - 1] == "0")
	{
		return true;
	}
	else 
	{
		return false;

	}
}

void Entity::celebrate()
{
	// celebrate with music
	
	YsSoundPlayer player1; //sound card
	YsSoundPlayer::SoundData myWav1;
	

	
	if (YSOK == myWav1.LoadWav("smb_world_clear.wav"))
	{

		// start the player after opening window
		player1.Start();

		
		player1.PlayOneShot(myWav1);
		

		// need something to keep program running until sound is done
		while (YSTRUE == player1.IsPlaying(myWav1)) {
			//player1.KeepPlaying();  // only really needed when using Linux
			

			// just something to keep track of passing time
			auto nowTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			//cout << std::ctime(&nowTime);
			
			//
			FsSleep(30);
		}

		// common courtesy to close player, although destructor of player 
		// will end player when variable passes "out of scope" at end of main()
		player1.End();
		
	}

}

void Entity::killEntity(Maze aMaze)
{
	// kill entity by drawing blood spatter patterns
	erase(aMaze);
	drawEntity(20 * (entity_col - 1), 20 * (entity_row - 1), 2,255,0,0);

}

void Entity::drawEntity(int vert_x,int vert_y,int inflation, int r, int g, int b)
{ //draw a spider by making diagonal and horizontal quads of specific size
 //inflation of two makes blood spatter like patterns
	glColor3d(r,g,b);
	for (int i = 0; i < 20; i += 2)
	{
		for (int j = 0; j < 20; j += 2)
		{
			//cout << "i=" << i << " " << "j=" << j;
			if (i  == j || i == 20-j || i==10 || j ==10)
			{
				glBegin(GL_QUADS);
				glVertex2f(vert_x+i, vert_y+j);
				glVertex2f(vert_x+i + 2.0* inflation, vert_y+j* inflation);
				glVertex2f(vert_x+i + 2.0* inflation, vert_y+j + 2.0* inflation);
				glVertex2f(vert_x+i, vert_y+j + 2.0* inflation);
				glEnd();
			}
			if (i == 10 && j == 10)
			{
				glBegin(GL_QUADS);
				glVertex2f(vert_x + i-4* inflation, vert_y + j-4* inflation);
				glVertex2f(vert_x + i + 4.0* inflation, vert_y + j-4* inflation);
				glVertex2f(vert_x + i + 4.0* inflation, vert_y + j + 4.0* inflation);
				glVertex2f(vert_x + i-4* inflation, vert_y + j + 4.0* inflation);
				glEnd();

			}

		}

	}
	
}
