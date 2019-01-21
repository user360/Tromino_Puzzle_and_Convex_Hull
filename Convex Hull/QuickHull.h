#pragma once

#define SELECTED	'R'

#include <stdio.h>
#include <vector>

struct Point
{
	float x;
	float y;
	char color;

	bool operator == (const Point rhs) const
	{
		if ((x == rhs.x) && (y == rhs.y))
			return true;
	}

	bool operator < (const Point rhs) const
	{
		return x < rhs.x;
	}

	bool operator > (const Point rhs) const
	{
		return x > rhs.x;
	}
};

class QuickHull
{
private:
	std::vector<Point> _inputSet;
	std::vector<Point> _Hull;

	float calcDet(Point q1, Point q2, Point q3);
	std::vector<Point> getLeftSet(std::vector<Point> set, Point P1, Point Pn, bool left);
	bool leftPoint(Point start, Point end, Point p);
	Point getPmax(std::vector<Point> leftSet);
	void QH(std::vector<Point> set);
	// void print();
public:
	QuickHull(std::vector<Point> inputSet);
	~QuickHull();
	void run();
};

