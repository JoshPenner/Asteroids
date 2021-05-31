#include "stdafx.h"
#include "CControl.h"
#include "opencv.hpp"


CControl::CControl()
{
}

CControl::~CControl()
{
}

void CControl::init_com(int comport)
{
	std::string comportstring = "COM";
	comportstring += std::to_string(comport);
	_com.open(comportstring);

}

bool CControl::get_data(int type, int channel, int &result)
{
	std::string result_str;
	
	tx_str = "G ";
	tx_str += std::to_string(type);
	tx_str += " ";
	tx_str += std::to_string(channel);
	tx_str += "\n";

	// temporary storage
	char buff[2];

		// Send TX string
		_com.write(tx_str.c_str(), tx_str.length());
		//Sleep(10); // wait for ADC conversion, etc. May not be needed?

		rx_str = "";
		// start timeout count
		double start_time = cv::getTickCount();

		buff[0] = 0;
		// Read 1 byte and if an End Of Line then exit loop
	// Timeout after 1 second, if debugging step by step this will cause you to exit the loop
		while (buff[0] != '\n' && (cv::getTickCount() - start_time) / cv::getTickFrequency() < 1.0)
		{
			if (_com.read(buff, 1) > 0)
			{
				rx_str = rx_str + buff[0];
			}
		}

		int index = 6;
		do
		{
			result_str = result_str + rx_str[index];
			index++;
		} while (rx_str[index] != '\n'); // while not \n
			
		result = std::stoi(result_str);

	return 0;
}

bool CControl::get_analog(int channel, int range, int &result_pct) {
	int result_analog;
	get_data(ANALOG, channel, result_analog);
	result_pct = (100 * result_analog) / range; // convert pos to %
	return 0;
}

bool CControl::set_data(int type, int channel, const int val)
{
	tx_str = "S ";
	tx_str += std::to_string(type);
	tx_str += " ";
	tx_str += std::to_string(channel);
	tx_str += " ";
	tx_str += std::to_string(val);
	tx_str += "\n";

	// Send TX string
	_com.write(tx_str.c_str(), tx_str.length());

	// temporary storage
	char buff[2];

	rx_str = "";
	// start timeout count
	double start_time = cv::getTickCount();

	// Read 1 byte and if an End Of Line then exit loop
// Timeout after 1 second, if debugging step by step this will cause you to exit the loop
	while (buff[0] != '\n' && (cv::getTickCount() - start_time) / cv::getTickFrequency() < 1.0)
	{
		if (_com.read(buff, 1) > 0)
		{
			rx_str = rx_str + buff[0];
		}
	}

	rx_str = "";

	return 0;
}

bool CControl::pushbutton_db(int channel) {

	get_data(DIGITAL, channel, data);
	button_pressed = !data;

	if (button_pressed) {

		elapsed = ((cv::getTickCount() - start_time) * 1000 / cv::getTickFrequency());

		if ((elapsed > 50) && (start_time != 0))
		{
			start_time = 0; // reset timer
			get_data(DIGITAL, channel, data);
			button_pressed = !data;
		
			if (button_pressed == true) 
			{
			return true;
			}
		}

		start_time = cv::getTickCount();
	}

	return 0;
}