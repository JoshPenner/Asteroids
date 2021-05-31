/**
*
* @brief Class for game objects
*
* Game objects. Circles with radius, position, velocity, lives, color.
*
* @author Josh Penner
*
*/

#pragma once

#include "stdafx.h"
#include "opencv.hpp"

class CGameObject
{
protected:
	cv::Point2f _position;			///< position variable
	cv::Point2f _velocity;			///< velocity variable
	int _radius;					///< radius
	int _lives;						///< lives remaining
	cv::Scalar _color;				///< color
	int _line_type;					///< line type

	double start_tic = 0;			///< timer start tick count
	double freq;					///< clock frequency
	double elapsed_time;			///< time from start to end

public:

	/** @brief updates location of asteroid or missile
	*
	* @return nothing to return
	*/
	void move();

	/** @brief Detects collision between two circular objects (ship, missile, asteroid)
	*
	* @param CGameObject &obj Object to detect collision with.
	* @return Return true if collision detected.
	*/
	bool collide(CGameObject &obj);

	/** @brief Detects collision object and wall
	*
	* @param cv::Size board Size of canvas
	* @return Return true if collision detected.
	*/
	bool collide_wall(cv::Size board);

	/** @brief Detects hit
	*
	* @return Nothing to return
	*/
	void hit();

	/** @brief Gets lives remaining
	*
	* @return Return number of lives remaining.
	*/
	int get_lives() { return _lives; }

	/** @brief Sets number of lives remaining
	*
	* @param cv::Size board Size of canvas
	* @return Return true if collision detected.
	*/
	void set_lives(int lives) { _lives = lives;  }

	/** @brief Sets ship position
	*
	* @param cv::Point2f pos Location of ship to set.
	* @return Nothing to return
	*/
	void set_pos(cv::Point2f pos) { _position = pos; }

	/** @brief Gets ship position
	*
	* @return Returns current ship position.
	*/
	cv::Point2f get_pos() { return _position; }

	/** @brief Draws object on the screen
	*
	* @param cv::Mat &im Image to draw on
	* @return Nothing to return
	*/
	void draw(cv::Mat &im);
};

