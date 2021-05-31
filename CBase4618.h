/**
*
* @brief Contains methods used in various ELEX4618 programs
*
* This class contains various functions and variables used
* in ELEX4618
*
* @author Josh Penner
*
*/

#pragma once

#include "opencv.hpp"
#include "CControl.h"

class CBase4618	
{
private:

public:
	cv::Mat _Canvas;						///< Canvas image object
	CControl uCtlr;							///< CControl object for microcontroller

	/** @brief Constructor
	*	@return nothing to return
	*/
	CBase4618();

	/** @brief Destructor
	*	@return nothing to return
	*/
	~CBase4618();

	/** @brief Updates data received from microcontroller
	*	@return nothing to return
	*/
	virtual void update();

	/** @brief Draws Canvas image based on values from update method
	*	@return nothing to return
	*/
	virtual void draw();

	/** @brief Runs update() and draw() methods in a loop while waiting for 'q' to quit
	*	@return nothing to return
	*/
	virtual void run();
};

