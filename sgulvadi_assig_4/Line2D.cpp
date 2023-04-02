// 24-780 Engineering Computation Assignment 4 
// Date:09/30/2022
#include <math.h>
#include <cmath>
#define PI 3.141592654
#include "Line2D.h"

using namespace std;

double Line2D::getLength(Point2D startPoint, Point2D endPoint)
{
	// just call other version of function
	return getLength(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
}

double Line2D::getLength(float startX, float startY, float endX, float endY)
{
	// using square root of the sum of the squares (SRSS)

	return sqrt((endX - startX) * (endX-startX) + (endY-startY) * (endY-startY));
}

bool Line2D::isBetween(Point2D startPoint, Point2D endPoint, Point2D checkPoint)
{
	float distA = getLength(startPoint, checkPoint);
	float distB = getLength(checkPoint, endPoint);
	float distC = getLength(startPoint, endPoint);

	// If A + B = C, checkPoint is indeed between
	return fabs( distC - distA - distB) < (distA * 1e-5f); // tolerance based on length
}

Point2D Line2D::getIntersection(Point2D pnt1, Point2D pnt2, Point2D pnt3, Point2D pnt4)
{
	// note that I changed names of parameters in .cpp so that I could use formulas from 
	// Piazza post directly. Names in .h file make sense for whoever uses the function

	float denominator = (pnt1.x - pnt2.x) * (pnt3.y - pnt4.y) - (pnt1.y - pnt2.y) * (pnt3.x - pnt4.x);
	if (fabs(denominator) < 1e-8) // lines are parallel (not sure what to use for tolerance)
		return { -INFINITY, -INFINITY };
	else {
		float topX = (pnt1.x * pnt2.y - pnt1.y * pnt2.x) * (pnt3.x - pnt4.x)
			- (pnt1.x - pnt2.x) * (pnt3.x * pnt4.y - pnt3.y * pnt4.x);

		float topY = (pnt1.x * pnt2.y - pnt1.y * pnt2.x) * (pnt3.y - pnt4.y)
			- (pnt1.y - pnt2.y) * (pnt3.x * pnt4.y - pnt3.y * pnt4.x);

		return { topX / denominator, topY / denominator };
	}
}

Point2D Line2D::getTrueIntersection(Point2D lineAstart, Point2D lineAend, Point2D lineBstart, Point2D lineBend)
{
	Point2D intersectionPnt = getIntersection(lineAstart, lineAend, lineBstart, lineBend);
	if (intersectionPnt.x == -INFINITY || intersectionPnt.y == -INFINITY)
	{
		return { -INFINITY,-INFINITY };
	}
	else if (isBetween(lineAstart,lineAend,intersectionPnt)&&isBetween(lineBstart,lineBend,intersectionPnt))
	{
		return intersectionPnt;

	}
	else
	{
		return { -INFINITY,-INFINITY };
	}

}

float Line2D::getAngle(Point2D startPnt, Point2D endPnt)
{
	return  atan2((endPnt.y - startPnt.y), (endPnt.x - startPnt.x)) * (180 / PI);

}
