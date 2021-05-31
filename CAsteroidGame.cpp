#include "stdafx.h"
#include "CAsteroidGame.h"

CAsteroidGame::CAsteroidGame()
{
}

CAsteroidGame::CAsteroidGame(int com_port)
{
	uCtlr.init_com(com_port);
	// add check for com function

	// initialize canvas image to desired width and height
	_Canvas = cv::Mat::zeros(cv::Size(1000, 800), CV_8UC3); // image type is CV_8UC3 : means 8 bit unsigned pixels with 3 channels(color)

}


CAsteroidGame::~CAsteroidGame()
{
}

void CAsteroidGame::update() // update internal variables of CSketch
{
	// use get_analog to get x position value as %
	uCtlr.get_analog(JOYSTICK_X, JOYSTICK_X_MAX, jstick_pct);

	// calculate x position based on joystick input
	// x = width of canvas * [ (sensitivity * input) - (1/2 scaled width offset) + (1/2 width offset) ]
	joystick_pos.x = _Canvas.cols * ( (jstick_sens * jstick_pct / 100) - (jstick_sens / 2) + 0.5 );
	//std::cout << "X position: " << joystick_pos.x << "\t";

	// limit x-coordinate to edges
	if (joystick_pos.x > _Canvas.cols) {
		joystick_pos.x = _Canvas.cols;
	}
	if (joystick_pos.x <= 0) {
		joystick_pos.x = 0;
	}

	// use get_analog to get y position value as %
	uCtlr.get_analog(JOYSTICK_Y, JOYSTICK_Y_MAX, jstick_pct);

	// calculate y position based on joystick input
	joystick_pos.y = _Canvas.rows *(1 - ((jstick_sens * jstick_pct / 100) - (jstick_sens / 2) + 0.5 ));
	//std::cout << "Y position: " << joystick_pos.y << "\n";

	// limit y-coordinate to edges
	if (joystick_pos.y > _Canvas.rows) {
		joystick_pos.y = _Canvas.rows;
	}
	if (joystick_pos.y <= 0) {
		joystick_pos.y = 0;
	}

	// Update ship position
	myShip.set_pos(joystick_pos);

	// Update asteroid positions:
	if (_asteroid_list.size() != 0)
	{
		for (int i = 0; i < _asteroid_list.size(); i++)
		{
			_asteroid_list[i].move();

			// check for asteroid - ship collisions
			if (_asteroid_list[i].collide(myShip))
			{
				_asteroid_list[i].set_lives(0);
				myShip.set_lives(myShip.get_lives() - 1);
			}

			// check for asteroid - missile collisions
			for (int j = 0; j < _missile_list.size(); j++)
			{
				if (_asteroid_list[i].collide(_missile_list[j]))
				{
					_asteroid_list[i].set_lives(0);
					_missile_list[j].set_lives(0);

					// add 10 to score
					score = score + 10;
				}
				
			}

			// check for asteroid - wall collisions
			if (_asteroid_list[i].collide_wall(_Canvas.size()))
				_asteroid_list[i].set_lives(0);
		}
	}

	// Update missile positions:
	if (_missile_list.size() != 0)
	{
		for (int i = 0; i < _missile_list.size(); i++)
		{
			_missile_list[i].move();

			// check for missile - wall collisions
			if (_missile_list[i].collide_wall(_Canvas.size()))
				_missile_list[i].set_lives(0);
		}
	}

	// Check remaining lives on asteroids:
	if (_asteroid_list.size() != 0)
	{
		for (int i = 0; i < _asteroid_list.size(); i++)
		{
			if (_asteroid_list[i].get_lives() <= 0)
			{
			_asteroid_list.erase(_asteroid_list.begin() + i);
			}
		}
	}

	// Check remaining lives on missiles:
	if (_missile_list.size() != 0)
	{
		for (int i = 0; i < _missile_list.size(); i++)
		{
			if (_missile_list[i].get_lives() <= 0)
				_missile_list.erase(_missile_list.begin() + i);
		}
	}
	

	// read a debounced pushbutton and create a missile if pressed
	if (uCtlr.pushbutton_db(PB1))
	{
		// create missile
		CMissile missile(_Canvas.size());
		missile.set_pos(myShip.get_pos());
		_missile_list.push_back(missile);
		
		// print the event to the screen with cout
		std::cout << "PB1 PRESSED: FIRE MISSILE\n";
	}

	// read a debounced pushbutton and set a _reset flag to true if pressed
	if (uCtlr.pushbutton_db(PB2))
	{
		//set _reset flag
		_reset = true;

		// print the event to the screen with cout
		std::cout << "PB2 PRESSED: SET RESET FLAG\n";
	}
}


void CAsteroidGame::draw() // performs all the drawing on the Mat image and displays image on the screen
{
	// start timer
	auto calc_start = std::chrono::steady_clock::now();

	// check if _reset flag is set and if so, clear image and _reset flag
	if ((_reset) || (myShip.get_lives() <= 0))
	{
		_reset = false; // clear flag

		// reset score
		score = 0;

		// reset lives
		myShip.set_lives(10);

		// reset asteroids
		_asteroid_list.clear();

		// reset missiles
		_missile_list.clear();
	}

	// clear previous image
	_Canvas = cv::Mat::zeros(_Canvas.size(), CV_8UC3);

	// draw ship
	/*
	cv::circle(_Canvas,
		myShip.get_pos(),					// location
		10,									// radius
		cv::Scalar(255, 255, 255),			// color
		CV_FILLED);							// filled
	*/
	myShip.draw(_Canvas);

	// draw asteroids
	if (_asteroid_list.size() != 0)
	{
		for (int i = 0; i < _asteroid_list.size(); i++)
		{
			_asteroid_list[i].draw(_Canvas);
		}
	}

	// draw missiles
	if (_missile_list.size() != 0)
	{
		for (int i = 0; i < _missile_list.size(); i++)
		{
			_missile_list[i].draw(_Canvas);
		}
	}

	// draw player score
	cv::putText(_Canvas,
		"Score: ",
		cv::Point(50, 50),
		CV_FONT_HERSHEY_PLAIN,
		2,
		cv::Scalar(255, 255, 255));

	cv::putText(_Canvas,
		std::to_string(score),
		cv::Point(200, 50),
		CV_FONT_HERSHEY_PLAIN,
		2,
		cv::Scalar(255, 255, 255));


	// draw number of lives
	cv::putText(_Canvas,
		"Lives: ",
		cv::Point(400, 50),
		CV_FONT_HERSHEY_PLAIN,
		2,
		cv::Scalar(255, 255, 255));

	cv::putText(_Canvas,
		std::to_string(myShip.get_lives()),
		cv::Point(550, 50),
		CV_FONT_HERSHEY_PLAIN,
		2,
		cv::Scalar(255, 255, 255));

	// draw fps
	cv::putText(_Canvas,
		std::to_string(fps),
		cv::Point(800, 50),
		CV_FONT_HERSHEY_PLAIN,
		2,
		cv::Scalar(255, 255, 255));

	// display canvas image
	cv::imshow("Canvas", _Canvas);

	// set update rate: 45ms per loop for 22fps
	// Sleep if time remaining
	std::this_thread::sleep_until(calc_start + std::chrono::milliseconds(45));

	// calculate fps
	auto calc_end = std::chrono::steady_clock::now();
	auto calc_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(calc_end - calc_start);
	//elapsed = calc_elapsed.count();
	fps = 1000 / calc_elapsed.count();
}

void CAsteroidGame::run()
{
	/*
	// initialize ship object
	CShip myShip(10);
	*/

	auto start_time = std::chrono::steady_clock::now();

	// call update and draw in a loop while waiting for user to press 'q' to quit
	do
	{
		update();
		draw();

		//create asteroid every few seconds
		auto end_time = std::chrono::steady_clock::now();
		auto calc_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
			if (calc_elapsed.count() > asteroid_delay) {

				CAsteroid astro(_Canvas.size());
				_asteroid_list.push_back(astro);
				//std::cout << "\nCreate asteroid " << _asteroid_list.size();

				//reset timer
				start_time = std::chrono::steady_clock::now();

				//std::cout << "\n Asteroid 1 pos: " << _asteroid_list[0].get_pos();
			}
		

	} while (cv::waitKey(1) != 'q');
}