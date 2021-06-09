#include "../include/GL/glut.h"
#include "../include/GL/freeglut.h"

#include "../include/quantities.hpp"
#include "../include/spheres.hpp"
#include "../include/axis.hpp"

#ifndef OBJECTS_HPP
#define OBJECTS_HPP

namespace objects {
	const int amount = 96;

	axis::Axis guide;
	spheres::Sphere bodys[amount];

	quantities::Vector base;

	int element;
}

#endif