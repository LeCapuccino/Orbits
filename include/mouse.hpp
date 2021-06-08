#ifndef MOUSE_HPP
#define MOUSE_HPP

namespace mouse {
	struct button {
		bool press = false;
	};

	button left;
	button middle;
	button right;

	int scroll[2] = {0, 0};

	void initialize() {
		left.press = false;
		middle.press = false;
		right.press = false;

		scroll[0] = 0;
		scroll[1] = 0;
	}
}

#endif