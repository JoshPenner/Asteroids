#include "stdafx.h"
#include "CAsteroid.h"

CAsteroid::CAsteroid()
{
}

CAsteroid::CAsteroid(cv::Size board)
{
	// randomize radius
	_radius = ((asteroid_max_radius - asteroid_min_radius) * ((float)rand() / (float)RAND_MAX) + asteroid_min_radius);

	// randomize x position
	_position.x = (board.width * ((float)rand() / (float)RAND_MAX));
	// y position = top of screen
	_position.y = _radius;

	// randomize x velocity
	_velocity.x = ((asteroid_max_vel - asteroid_min_vel) * ((float)rand() / (float)RAND_MAX) + asteroid_min_vel);
	// randomize y velocity
	_velocity.y = abs((asteroid_max_vel - asteroid_min_vel) * ((float)rand() / (float)RAND_MAX) + asteroid_min_vel);

	_color = cv::Scalar(200, 200, 200);
	_line_type = 2;
	_lives = 1;
}

/*
CAsteroid::CAsteroid(int radius, cv::Point2d position, cv::Point2d velocity)
{
	_radius = radius;
	_position = position;
	_velocity = velocity;
	_color = cv::Scalar(200, 200, 200);
	_line_type = 2;
}
*/

CAsteroid::~CAsteroid()
{
}
