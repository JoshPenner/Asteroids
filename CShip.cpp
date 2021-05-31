#include "stdafx.h"
#include "CShip.h"


CShip::CShip()
{
	_radius = 20;
	_lives = 10;
	_color = cv::Scalar(
		255,	// blue
		0,		// green
		255);	// red
	_line_type = CV_FILLED;
	//std::cout << "\n" <<_radius;
}

CShip::CShip(int radius)
{
	_radius = radius;
	_lives = 10;
	_color = cv::Scalar(
		255,	// blue
		0,		// green
		255);	// red
	_line_type = CV_FILLED;

	//std::cout << "\n" <<_radius;
}


CShip::~CShip()
{
}
