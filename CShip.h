/**
*
* @brief Class for ship object
*
* Ship object
*
* @author Josh Penner
*
*/

#include "CGameObject.h"

#pragma once
class CShip : public CGameObject
{
public:

	/** @brief Constructor
	*
	* @return nothing to return
	*/
	CShip();

	/** @brief Constructor
	*
	* @param int radius Radius of ship
	* @return nothing to return
	*/
	CShip(int radius);

	/** @brief Destructor
	*
	* @return nothing to return
	*/
	~CShip();
};

