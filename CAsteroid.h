/**
*
* @brief Class asteroid object
*
* Description
*
* @author Josh Penner
*
*/

#pragma once

#include "CGameObject.h"

class CAsteroid : public CGameObject
{
private:
	int asteroid_min_vel = -150;					///< min x and y velocity of asteroid
	int asteroid_max_vel = 150;					///< max x and y velocity of asteroid
	int asteroid_min_radius = 5;				///< min radius of asteroid
	int asteroid_max_radius = 20;				///< max radius of asteroid
public:
	CAsteroid();
	CAsteroid(cv::Size board);
	//CAsteroid(int radius, cv::Point2d position, cv::Point2d velocity);
	~CAsteroid();
};

