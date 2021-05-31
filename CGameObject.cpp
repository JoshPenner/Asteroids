#include "stdafx.h"
#include "CGameObject.h"
#include <chrono>
#include <thread>

void CGameObject::move() 
{ 
	freq = cv::getTickFrequency(); // Get tick frequency

	elapsed_time = (cv::getTickCount() - start_tic) / freq;

	if (start_tic != 0)
	{
	_position = _position + (_velocity * elapsed_time);
	}

	start_tic = cv::getTickCount(); 
}

bool CGameObject::collide(CGameObject &obj)
{ 
	int radiiSum = _radius + obj._radius;
	double dist = cv::norm(obj._position - _position);
	if (dist <= radiiSum)
		return true;
	else
		return false;
}

bool CGameObject::collide_wall(cv::Size board) 
{ 
	// collision with right edge
	if ((_position.x + _radius) > board.width)
		return true;
	// collision with left edge
	if ((_position.x - _radius) < 0)
		return true;
	// collision with top edge
	if ((_position.y + _radius) > board.height)
		return true;
	// collision with bottom edge
	if ((_position.y - _radius) < 0)
		return true;
	// if no conditions met, no collisions
	return false;
}

void CGameObject::hit() { ; }

void CGameObject::draw(cv::Mat &im) 
{ 
	cv::circle(im,
		_position,				// location
		_radius,				// radius
		_color,					// color
		_line_type);			// filled
}