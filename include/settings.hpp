#include "../include/quantities.hpp"

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

namespace settings {
	bool start;

	bool gravitational = true;

	double frames = 60.0;

	double per = 1000.0 / frames;

	double mul = 10;

	float colors[7][4] = {
		{0.96, 0.24, 0.30, 1.0},  //red
		{0.00, 0.81, 0.90, 1.0},  //blue
		{0.92, 0.81, 0.16, 1.0},  //yellow
		{0.18, 0.85, 0.56, 1.0},  //green
		{0.49, 0.08, 0.67, 1.0},  //purple
		{0.96, 0.50, 0.20, 1.0},  //orange
		{1.00, 0.38, 0.48, 1.0}   //pink
	};

	bool perspective = false;

	double distance = 0;

	double variation = 100;

	double nearval = variation - 5 * mul;
	double farval = variation + 100 * mul;

	quantities::Scalar instant;
	quantities::Scalar moment;
}

#endif