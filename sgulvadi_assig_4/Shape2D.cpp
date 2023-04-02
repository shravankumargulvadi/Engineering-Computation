// 24-780 Engineering Computation Assignment 4 
// Date:09/30/2022
#include <iostream>
#include <math.h>
#include "fssimplewindow.h"
#include "Line2D.h"
#include "Shape2D.h"
#include "DrawingUtilNG.h"

using namespace std;

Shape2D::Shape2D()
{
	// nothing here yet
}

Shape2D::Shape2D(std::ifstream& input)
{
	// these will temporarily hold the values read from the file
	float newX, newY;

	// these are used to avoid duplicate points, initialized to values that
	// essentially mean "no point at all" (the negative of largest possible float number)
	float oldX = -INFINITY, oldY = -INFINITY;

	while (!input.eof()) {  // continue reading until the whole file has been read

		// the ifstream variable "input" can be used just like "cin".
		// it is like magic in that it does all the "translating" and advancing
		// down the line and down the file, using tabs, spaces, and newline
		// characters as separators.
		input >> newX >> newY;

		// we want to avoid the consecutive points being exactly the same
		if (newX != oldX || newY != oldY)
			thePoints.push_back({ newX, newY }); // define Point2D on the fly & add to vector

		// reset old coords in preparation for reading next coords
		oldX = newX; oldY = newY;
	}
	recalcShape();
}

bool Shape2D::addPoint(Point2D newPoint, int index)
{
	if (index < 1)
		return false;
	else {
		if (index > thePoints.size())
			thePoints.push_back(newPoint);
		else
			thePoints.insert(thePoints.begin() + index - 1, newPoint);

		recalcShape();
		return true;
	}
}

bool Shape2D::addPoint(int index, float ratio)
{
	if (0. <= ratio || ratio >= 1.0 || index < 2 || index >= thePoints.size())
		return false;
	else {
		// insert a point between index-2 and index-1
		// the coords of new point are based on similar triangles
		// coords = prevPoint + ratio * (difference from nextPoint to newPoint)
		float newX = thePoints[index - 2].x
			+ ratio * (thePoints[index - 1].x - thePoints[index - 2].x);
		float newY = thePoints[index - 2].y
			+ ratio * (thePoints[index - 1].y - thePoints[index - 2].y);
		thePoints.insert(thePoints.begin() + index - 1, { newX, newY });

		//recalcShape(); not required 
		return true;
	}
}

bool Shape2D::removePoint(int index)
{
	if (index < 1 || index > thePoints.size())
		return false;
	else {
		thePoints.erase(thePoints.begin() + index - 1);
		recalcShape();
		return true;
	}
}



void Shape2D::paint(bool closed, bool filled, bool showPoints, float colorOverride)
{
	if (thePoints.size() >= 2)
	{
		double r, g, b; 
		if (colorOverride > -1.f) //if coloroverride is requested
			DrawingUtilNG::hsv2rgb(colorOverride, 1.f, 1.f, r, g, b); //convert the requested color to RGB
		else
			DrawingUtilNG::hsv2rgb(10, 1.f, 0.f, r, g, b); 
		glColor3d(r, g, b);
		

		glBegin(GL_LINES);

		glVertex2f(thePoints.front().x, thePoints.front().y);
		for (auto currPnt : thePoints) {
			glVertex2f(currPnt.x, currPnt.y);
			glVertex2f(currPnt.x, currPnt.y);
		}
		if (closed)
			glVertex2f(thePoints.front().x, thePoints.front().y);
		glEnd();

		if (showPoints) {
			float pntSize;
			if (thePoints.size() <= 1)
				pntSize = 4.f;
			else
				
				pntSize = 0.1 * perimeter() / thePoints.size();

			for (auto currPnt : thePoints) {
				glTranslatef(currPnt.x, currPnt.y, 0.f);

				glBegin(GL_QUADS);
				glVertex2f(pntSize, 0);
				glVertex2f(0, pntSize);
				glVertex2f(-pntSize, 0);
				glVertex2f(0, -pntSize);
				glEnd();

				glTranslatef(-currPnt.x, -currPnt.y, 0.f);
			}
		}

	}
}

Point2D Shape2D::getPoint(int index)
{
	if (index <= 0 || index > thePoints.size())
	{
		 return { -INFINITY, -INFINITY };
	}
	else
	{
		return thePoints[index - 1];
	}
}

bool Shape2D::movePoint(Point2D newCoords, int index)
{
	if (index<=0 || index > thePoints.size())
	{
		return false;
	}
	else
	{
		removePoint(index);
		addPoint(newCoords, index);
		return true;
	}
}

bool Shape2D::movePointDelta(Point2D deltaCoords, int index)
{
	if (index<=0 || index > thePoints.size())
	{
		return false;
	}
	else
	{
		Point2D newPnt = {};
		newPnt.x = thePoints[index - 1].x + deltaCoords.x;
		newPnt.y = thePoints[index - 1].y + deltaCoords.y;
		return movePoint(newPnt, index);
	}
}

int Shape2D::getIndex(Point2D givenCoord, float dist)
{
	if (((abs(givenCoord.x - lowerBound.x) <dist) && ((givenCoord.y - lowerBound.y) < dist)) || (((givenCoord.x - upperBound.x) > dist ) && ((givenCoord.y - upperBound.y) >dist )))
	{
		return -1;
	}
	else
	{
		for (int i=1; i<=thePoints.size();i++)
		{
			if (abs(givenCoord.x - thePoints[i-1].x) < dist && abs(givenCoord.y - thePoints[i-1].y) < dist)
			{
				return i;
			}

		}
	}

	return 0;
}

bool Shape2D::selfIntersects()
{
	if (thePoints.size() <= 2) return false; 
	vector<Point2D> thePointsClosed = thePoints;
	thePointsClosed.push_back(thePoints[0]);

	for (int i = 0; i <= thePointsClosed.size()-3; i++)
	{
		for (int j = i + 2; j <= thePointsClosed.size()-2; j++)
		{
			Point2D intersection = Line2D::getTrueIntersection(thePointsClosed[i], thePointsClosed[i + 1], thePointsClosed[j], thePointsClosed[j + 1]);
			if (intersection.x != -INFINITY)
			{
				return true; 
			}
		}
	}
	return false;
}


void Shape2D::recalcShape()
{

	if (thePoints.size() >= 3)
	{
		perim = 0.f;
		Point2D prevPnt = thePoints.back();
		lowerBound = prevPnt;
		upperBound = prevPnt;
		for (auto currPnt : thePoints)
		{
			perim += Line2D::getLength(prevPnt, currPnt);
			if (currPnt.y < lowerBound.y) lowerBound.y = currPnt.y;
			if (currPnt.y > upperBound.y) upperBound.y = currPnt.y;
			if (currPnt.x < lowerBound.x) lowerBound.x = currPnt.x;
			if (currPnt.x > upperBound.x) upperBound.x = currPnt.x;
			prevPnt = currPnt;
		}
	}
}

void Shape2D::changeHue()
{
	colorHue = colorHue + 10.f;
	colorHue = fmod(colorHue, 360.f); 

}



std::ostream& operator<<(std::ostream& os, const Shape2D& aShape)
{
	for (auto currPnt : aShape.thePoints) {
		os << currPnt.x << "\t" << currPnt.y << endl;
	}
	return os;
}
