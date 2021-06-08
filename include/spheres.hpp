#include <iostream>

#include <cstdlib>
#include <ctime>
#include <cmath>

#include "../include/GL/glut.h"
#include "../include/GL/freeglut.h"

#include "../include/screen.hpp"
#include "../include/settings.hpp"
#include "../include/quantities.hpp"

#ifndef SPHERES_HPP
#define SPHERES_HPP

int random(float lim) {
	return std::rand() % (int)lim;
}

namespace spheres {
	class Sphere {
	public:
		quantities::Scalar mass;

		quantities::Vector position;
		quantities::Vector velocity;
		quantities::Vector aceleration;

		bool abscissa = false;
		bool ordered = false;
		bool quota = false;

		bool climb = false;

		int color;

		int axe;

		double radius;

		bool start = true;
		bool init = true;
		bool creation = false;
		bool plot = false;

		double displace = settings::mul * 0.02;

		Sphere() {}

		Sphere(double x, double y, double z, double _radius) {
			position = quantities::Vector(x, y, z);

			velocity = quantities::Vector(0, 0, 0);
			aceleration = quantities::Vector(0, 0, 0);

			radius = _radius;
		}

		void vel() {
			velocity = quantities::Vector(1.5, 0, 0);
		}

		void choice() {
			initialize();
			
			init = false;

			color = random(7);
			radius = ((float) random(100)) / (100.0 * screen::lengh[0]);

			fill();

			for (int j = 0; j < 3; j++) {
				if (random((int) (settings::mul / screen::lengh[0])) % 2 == 0) {
					position.coord[j] = random((int) (settings::mul / screen::lengh[0]));
				}
				else {
					position.coord[j] = -random((int) (settings::mul / screen::lengh[0]));
				}
			}
		}

		void initialize() {
			mass = quantities::Scalar(0);

			position = quantities::Vector(0, 0, 0);
			velocity = quantities::Vector(0, 0, 0);
			aceleration = quantities::Vector(0, 0, 0);

			radius = 0;
			color = random(7);

			abscissa = false;
			ordered = false;
			quota = false;

			start = true;
			init = true;
			creation = false;
			plot = false;
		}

		void col() {
			color = random(7);
		}

		void getacel(Sphere other, quantities::Vector soft) {
			aceleration += ((other.position - position + soft) / ((!(other.position - position + soft))^3)) * other.mass;
		}

		void update(quantities::Scalar moment) {
			velocity += aceleration * moment;
			position += velocity * moment;
		}

		void fill() {
			mass = quantities::Scalar(radius / settings::mul);
		}

		void colision(Sphere &other) {
			quantities::Vector transfer;
			quantities::Vector receive;

			if (!(other.position - position) <= other.radius + radius) {
				if (other.mass >= mass) {
					transfer = other.position - position;
					transfer *= ((velocity || transfer) / (transfer || transfer));
					velocity -= transfer;

					receive = position - other.position;
					receive *= ((other.velocity || receive) / (receive || receive));
					velocity += receive;
				}
				else {
					transfer = position - other.position;
					transfer *= ((other.velocity || transfer) / (transfer || transfer));
					other.velocity -= transfer;

					receive = position - other.position;
					receive *= ((velocity || receive) / (receive || receive));
					other.velocity += receive;
				}
			}
		}

		void draw() {
			glPushMatrix();

        	glTranslatef(position.coord[0], position.coord[1], position.coord[2]);

			glColor3f(settings::colors[color][0], 
					  settings::colors[color][1], 
					  settings::colors[color][2]);

			glutSolidSphere(radius, 64, 64);

			glPopMatrix();
		}

		void axis() {
			if (plot) {
				switch (axe) {
					case 0:
						glColor3f(0.26, 0.90, 0.87);        //x
						glLineWidth(2.0);
						glBegin(GL_LINES);
							glVertex3f(position.coord[0] - 2 * radius, position.coord[1], position.coord[2]);
							glVertex3f(position.coord[0] + 2 * radius, position.coord[1], position.coord[2]);
						glEnd();
						break;

					case 1:
						glColor3f(0.90, 0.83, 0.26);        //y
						glLineWidth(2.0);
						glBegin(GL_LINES);
							glVertex3f(position.coord[0], position.coord[1] - 2 * radius, position.coord[2]);
							glVertex3f(position.coord[0], position.coord[1] + 2 * radius, position.coord[2]);
						glEnd();
						break;

					case 2:
						glColor3f(0.90, 0.26, 0.43);        //z
						glLineWidth(2.0);
						glBegin(GL_LINES);
							glVertex3f(position.coord[0], position.coord[1], position.coord[2] - 2 * radius);
							glVertex3f(position.coord[0], position.coord[1], position.coord[2] + 2 * radius);
						glEnd();
						break;
				}
			}
		}

		void redim(bool val) {
			if (val) {
				if (radius + 0.01 * settings::mul <= 0.5 * settings::mul) {
					radius += 0.01 * settings::mul;
				}
				
			}
			else {
				if (radius - 0.01 * settings::mul >= 0.01 * settings::mul) {
					radius -= 0.01 * settings::mul;
				}
			}
		}

		void repos(int axi, bool val, double lengh) {
			switch (axi) {
				case 0:
					if (val) {
						if (position.coord[0] + displace < settings::mul / lengh) {
							position.coord[0] += displace;
						}
					}
					else {
						if (position.coord[0] - displace > -settings::mul / lengh) {
							position.coord[0] -= displace;
						}
					}
					break;

				case 1:
					if (val) {
						if (position.coord[1] + displace < settings::mul / lengh) {
							position.coord[1] += displace;
						}
					}
					else {
						if (position.coord[1] - displace > -settings::mul / lengh) {
							position.coord[1] -= displace;
						}
					}
					break;

				case 2:
					if (val) {
						if (position.coord[2] + displace < settings::mul / lengh) {
							position.coord[2] += displace;
						}
					}
					else {
						if (position.coord[2] - displace > -settings::mul / lengh) {
							position.coord[2] -= displace;
						}
					}
					break;
			}
		}
	};
}

#endif
