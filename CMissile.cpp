#include "stdafx.h"
#include "CMissile.h"


CMissile::CMissile()
{
}

CMissile::CMissile(cv::Size board)
{
	_radius = 2;
	_velocity.x = 0;
	_velocity.y = -150;
	_color = cv::Scalar(
		0,	// blue
		0,	// green
		255);	// red
	_line_type = CV_FILLED;
	_lives = 1;
}


CMissile::~CMissile()
{
}
