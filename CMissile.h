/**
*
* @brief Class for missile object
*
* Missile object.
*
* @author Josh Penner
*
*/

#pragma once

#include "CGameObject.h"

class CMissile : public CGameObject
{
public:

	/** @brief Constructor
	*
	* @return nothing to return
	*/
	CMissile();

	/** @brief Constructor
	*
	* @param cv::Size board Size of the image
	* @return nothing to return
	*/
	CMissile(cv::Size board);

	/** @brief Destructor
	*
	* @return nothing to return
	*/
	~CMissile();
};

