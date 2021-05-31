#include "stdafx.h"
#include "CBase4618.h"
#include <chrono>
#include <thread>


CBase4618::CBase4618() 
{
}


CBase4618::~CBase4618()
{
}

void CBase4618::update()
{
}

void CBase4618::draw()
{
}

void CBase4618::run()
{
	// call update and draw in a loop while waiting for user to press 'q' to quit
	do
	{
		update();
		draw();

	} while (cv::waitKey(1) != 'q');
}