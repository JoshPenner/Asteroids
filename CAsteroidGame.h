/**
*
* @brief Creates game of asteroids
*
* This class inherits from the CBase 4618 class. It creates game of Asteroids on 1000 x 800
* canvas. Initiates communication over desired com port to a microcontroller.
*
* @author Josh Penner
*
*/

#pragma once
#include "CBase4618.h"
#include "opencv.hpp"
#include <chrono>
#include <thread>
#include <vector>

#include "CGameObject.h"
#include "CShip.h"
#include "CAsteroid.h"
#include "CMissile.h"

class CAsteroidGame : public CBase4618
{
private:
	enum colours { RED, GREEN, BLUE };			///< Colours enumeration
		
	int jstick_pct;								///< Joystick % value in 
	bool _reset = false;						///< Reset canvas flag
	double jstick_sens = 1.3;					///< Sensitivity of joystick (scales range)
	cv::Point2d joystick_pos;

	double fps;									///< Frames per second

	CShip myShip;

	int asteroid_delay = 2000;					///< delay between asteroid creation in milliseconds

	std::vector<CAsteroid> _asteroid_list;		///< asteroid vector

	std::vector<CMissile> _missile_list;		///< missile vector

	int score = 0;								///< total player score (asteroids destroyed * 10)
	int lives = 10;								///< lives remaining

public:

	/** @brief Constructor.
	*
	* @return nothing to return
	*/
	CAsteroidGame();

	/** @brief Constructor. Accepts com port
	*
	* @param com_port Com port
	* @return nothing to return
	*/
	CAsteroidGame(int com_port);

	/** @brief Destructor
	*	
	* @return nothing to return
	*/
	~CAsteroidGame();

	/** @brief Updates data received from microcontroller
	*	@return nothing to return
	*/
	void update();

	/** @brief Draws on Canvas image based on values from update method
	*	@return nothing to return
	*/
	void draw();

	/** @brief Runs update and draw in a loop while waiting for 'q' to quit.
	*	@return nothing to return
	*/
	void run();
};

