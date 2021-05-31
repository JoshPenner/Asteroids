#pragma once
#include "Serial.h"
#include <string>

#define RED_LED 39
#define GRN_LED 38
#define BLU_LED 37

#define PB1 33
#define PB2 32

#define JOYSTICK_Y 9
#define JOYSTICK_X 15

#define JOYSTICK_Y_MAX 1021
#define JOYSTICK_X_MAX 1005

enum data_type { DIGITAL, ANALOG, SERVO };

/**
*
* @brief Initializes serial com port, gets data, sets data
*
* This class contains functions for initiating serial
* communications, retrieving data from the controller,
* and sending data to the controller.
*
* @author Josh Penner
*
*/

class CControl
{
private:
	Serial _com;								///< Com serial object

	// TX and RX strings
	std::string tx_str;							///< Tx string sent over com port
	std::string rx_str;							///< Rx string received over com port

	int counter = 0;
	int data;
	unsigned int elapsed;
	bool button_pressed = false;
	double start_time = 0;

public:
	
	/** @brief Constructor
	*	@return nothing to return
	*/
	CControl();

	/** @brief Destructor
	*	@return nothing to return
	*/
	~CControl();

	/** @brief Initiates communication with specified com port
	*
	* @param comport Com port
	* @return nothing to return
	*/
	void init_com(int comport);

	/** @brief Gets data from uController via active com port
	*
	* @param type Data type (digital, analog, or servo)
	* @param channel Channel/pin #
	* @param result Data received from uController
	* @return Data received
	*/
	bool get_data(int type, int channel, int &result);

	/** @brief Gets analog data as % from uController via active com port
	*
	* @param channel Channel/pin #
	* @param range Full range value
	* @param result_pct Data received in % of full range
	* @return Data received
	*/
	bool get_analog(int channel, int range, int &result_pct);

	/** @brief Sends command to uController via active com port
	*
	* @param type Data type (digital, analog, or servo)
	* @param channel Channel/pin #
	* @param val Desired value to set
	* @return Data sent
	*/
	bool set_data(int type, int channel, int val);

	/** @brief Debounced pushbutton reading
	*
	* @param channel Channel/pin #
	* @return Button pressed (debounced)
	*/
	bool pushbutton_db(int channel);
};

