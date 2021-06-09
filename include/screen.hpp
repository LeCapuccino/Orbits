#ifndef SCREEN_HPP
#define SCREEN_HPP

namespace screen {
	double width = 600;
	double height = 600;

	double angles[3] = {0, 0, 1};

	double origin[2] = {0, 0};
	double relative[2][2] = {{0, 0}, {0, 0}};

	float color = 1.0;//0.94;

	double lengh[3] = {1, 0.005, 0.005};

	void initialize() {
		angles[0] = 0;
		angles[1] = 0;
		angles[2] = 1;

		origin[0] = 0;
		origin[1] = 0;

		relative[0][0] = 0; relative[0][1] = 0;
		relative[1][0] = 0; relative[1][1] = 0;

		lengh[0] = 1;
		lengh[1] = 0.005;
		lengh[2] = 0.005;
	}
}

#endif