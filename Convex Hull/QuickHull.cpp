#include "QuickHull.h"



QuickHull::QuickHull(std::vector<Point> inputSet)
{
	this->_inputSet = inputSet;
}


QuickHull::~QuickHull()
{
}

float QuickHull::calcDet(Point q1, Point q2, Point q3)
{
	return q1.x * q2.y + q2.x * q3.y + q3.x * q1.y - q3.x * q2.y - q2.x * q1.y - q1.x * q3.y;
}

bool QuickHull::leftPoint(Point start, Point end, Point p)
{
	if (this->calcDet(start, end, p) > 0)
		return true;
	return false;
}

std::vector<Point> QuickHull::getLeftSet(std::vector<Point> set, Point P1, Point Pn, bool left)
{
	std::vector<Point> leftSet;
	leftSet.push_back(P1);
	leftSet.push_back(Pn);

	if (left == true)
	{
		set.erase(set.begin());
		set.erase(set.begin());
	}
	else
	{
		set.erase(set.begin());
		set.erase(set.begin() + set.size() - 1);
	}
	

	for (size_t i = 0; i < set.size(); i++)
		if (leftPoint(P1, Pn, set[i]))
			leftSet.push_back(set[i]);

	return leftSet;
}

Point QuickHull::getPmax(std::vector<Point> leftSet)
{
	Point P1 = leftSet[0];
	Point Pn = leftSet[1];
	Point Pmax;

	float maxArea = 0.0;

	leftSet.erase(leftSet.begin());
	leftSet.erase(leftSet.begin());

	for (size_t i = 0; i < leftSet.size(); i++)
	{
		float area = this->calcDet(P1, Pn, leftSet[i]);
		if (area > maxArea)
		{
			maxArea = area;
			Pmax = leftSet[i];
		}
	}

	return Pmax;
}

void QuickHull::QH(std::vector<Point> set)
{
	std::vector<Point> upHull, lowHull;

	if (set.size() == 2)
		return;
	if (set.size() == 3)
	{
		set[2].color = SELECTED;
		this->_Hull.push_back(set[2]);
		return;
	}

	Point P1 = set[0];
	Point Pn = set[1];
	Point Pmax = this->getPmax(set);
	Pmax.color = SELECTED;
	this->_Hull.push_back(Pmax);

	upHull = this->getLeftSet(set, P1, Pmax, true);
	lowHull = this->getLeftSet(set, Pmax, Pn, true);
	QH(upHull);
	QH(lowHull);
}

void QuickHull::run()
{
	this->_inputSet[0].color = SELECTED;
	this->_Hull.push_back(this->_inputSet[0]);
	this->_inputSet[this->_inputSet.size() - 1].color = SELECTED;
	this->_Hull.push_back(this->_inputSet[this->_inputSet.size() - 1]);

	size_t n = this->_inputSet.size();

	std::vector<Point> upHull = this->getLeftSet(this->_inputSet, 
		this->_inputSet[0], this->_inputSet[n - 1], false);
	std::vector<Point> lowHull = this->getLeftSet(this->_inputSet, 
		this->_inputSet[n - 1], this->_inputSet[0], false);

	QH(upHull);
	QH(lowHull);

	for (size_t i = 0; i < this ->_Hull.size(); i++)
	{
		printf("( %f, %f )\n", this->_Hull[i].x, this->_Hull[i].y);
	}
}