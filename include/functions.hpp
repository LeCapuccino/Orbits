#include <iostream>
#include <ctime>
#include <cmath>

#include "../include/GL/glut.h"
#include "../include/GL/freeglut.h"

#include "../include/quantities.hpp"
#include "../include/settings.hpp"
#include "../include/objects.hpp"
#include "../include/screen.hpp"
#include "../include/mouse.hpp"

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

namespace functions {
	void seed() {
		std::srand((unsigned)std::time(0));
	}

	void init() {
		glClearColor(screen::color, screen::color, screen::color, 1);
		glShadeModel(GL_FLAT);

		settings::start = false;

		settings::instant = quantities::Scalar(1.0 / (100 * settings::frames));
		settings::moment = quantities::Scalar(0);

		screen::initialize();
		mouse::initialize();

		for (int i = 0; i <= objects::amount; i++) {
			objects::bodys[i].initialize();
		}

		objects::element = 0;
	}

	void generate(bool gravitational) {
		seed();

		settings::moment = quantities::Scalar(0);

		objects::element = random(objects::amount);

		for (int i = 0; i < objects::element; i++) {
			objects::bodys[i].choice(gravitational);
		}
	}

	void create() {
		if (objects::bodys[objects::element].init) {
			objects::bodys[objects::element] = spheres::Sphere(0, 0, 0, settings::mul * 0.1);
			objects::bodys[objects::element].creation = true;
			objects::bodys[objects::element].init = false;
		}
	}

	void projection() {
		glViewport(0, 0, screen::width, screen::height);

		double aspect = (float)screen::width / (float)screen::height;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		if (screen::width >= screen::height) {
			if (!settings::perspective) {
				glOrtho(-settings::mul * aspect,
						 settings::mul * aspect,
						-settings::mul,
						 settings::mul,
						-5 * settings::mul,
						 5 * settings::mul);
			}
			else {
				glFrustum(-settings::mul * aspect,
						   settings::mul * aspect,
						  -settings::mul,
						   settings::mul,
						   settings::nearval,
						   settings::farval);
			}
		}
		else {
			if (!settings::perspective) {
				glOrtho(-settings::mul,
						 settings::mul,
						-settings::mul / aspect,
						 settings::mul / aspect,
						-5 * settings::mul,
						 5 * settings::mul);
			}
			else {
				glFrustum(-settings::mul,
						   settings::mul,
						  -settings::mul / aspect,
						   settings::mul / aspect,
					  	   settings::nearval,
						   settings::farval);
			}
		}

		glMatrixMode(GL_MODELVIEW);

		glutPostRedisplay();
	}
	
	void reshape(int width, int height) {
		screen::width = width;
		screen::height = height;
	}

	void rotate() {
		if (settings::farval > settings::nearval) {
			glRotatef(screen::angles[0], 1.0, 0.0, 0.0);
			glRotatef(screen::angles[1], 0.0, 1.0, 0.0);
		}
		else {
			glRotatef(-screen::angles[0], 1.0, 0.0, 0.0);
			glRotatef(-screen::angles[1], 0.0, 1.0, 0.0);
		}
	}

	void scale() {
		if (settings::perspective) {
			float adjus = settings::variation / settings::nearval;
			glScaled(adjus * screen::lengh[0], adjus * screen::lengh[0], adjus * screen::lengh[0]);
		}
		else {
			glScaled(screen::lengh[0], screen::lengh[0], screen::lengh[0]);
		}
	}

	void draw() {
		objects::guide.draw();

		objects::bodys[objects::element].axis();

		for (int i = 0; i <= objects::element; i++) {
			objects::bodys[i].draw();
		}

    	glFlush();
		glutSwapBuffers();
	}

	void update() {
		if (settings::start) {
			for (int i = 0; i < objects::element; i++) {
				if (objects::bodys[i].start) {
					for (int j = 0; j < objects::element; j++) {
						if (j != i) {
							objects::bodys[i].collision(objects::bodys[j]);

							if (settings::gravitational) {
								objects::bodys[i].getacel(objects::bodys[j]);
							}
						}
					}
				}

				objects::bodys[i].update(settings::moment);
			}

			settings::moment += settings::instant;
		}
	}

	void timer(int) {
		projection();
		update();
		draw();

		glutPostRedisplay();
		glutTimerFunc(settings::per, timer, 0.0);
	}

	void display() {
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	glClearColor(screen::color, screen::color, screen::color, 1);

    	glLoadIdentity();

    	if (!settings::perspective) {
    		glTranslatef(0, 0, -settings::distance);

    		settings::distance = 0;

	    	rotate();
	    	scale();
	    }
	    else {
	    	glTranslatef(0, 0, -settings::variation);

	    	settings::distance = -settings::variation;

	    	rotate();
	    	scale();
	    }

    	glFlush();
	}

	void keyboard(unsigned char key, int x, int y) {
		switch(key) {
			case 27:     //esc
				glutLeaveMainLoop();
				break;

			case 32:
				if (objects::element != 0){
					if (!objects::bodys[objects::element - 1].creation) {
						settings::start = !settings::start;
					}
				}
				break;

			case 99:     //c
				objects::bodys[objects::element].col();
				break;

			case 103:     //g
				generate(settings::gravitational);
				break;

			case 114:     //r
				init();
				break;

			case 13:     //enter
				if (objects::bodys[objects::element].creation) {
					objects::bodys[objects::element].fill();
					objects::bodys[objects::element].creation = false;
					objects::element++;
				}
				break;

			case 112:    //p
				settings::perspective = !settings::perspective;
				break;

			case 109:    //m
				settings::gravitational = !settings::gravitational;

				if (settings::gravitational) {screen::color += 0.08;}
				else {screen::color -= 0.08;}

				objects::guide.col(settings::gravitational);

				break;

			case 115:     //s
				objects::bodys[objects::element].start = !objects::bodys[objects::element].start;
				break;

			case 120:     //x
				if (objects::bodys[objects::element].creation) {
					objects::bodys[objects::element].abscissa = true;
					objects::bodys[objects::element].ordered = false;
					objects::bodys[objects::element].quota = false;

					objects::bodys[objects::element].axe = 0;
					objects::bodys[objects::element].plot = true;
				}
				break;

			case 121:     //y
				if (objects::bodys[objects::element].creation) {
					objects::bodys[objects::element].abscissa = false;
					objects::bodys[objects::element].ordered = true;
					objects::bodys[objects::element].quota = false;

					objects::bodys[objects::element].axe = 1;
					objects::bodys[objects::element].plot = true;
				}
				break;

			case 122:     //z
				if (objects::bodys[objects::element].creation) {
					objects::bodys[objects::element].abscissa = false;
					objects::bodys[objects::element].ordered = false;
					objects::bodys[objects::element].quota = true;

					objects::bodys[objects::element].axe = 2;
					objects::bodys[objects::element].plot = true;
				}
				break;

			case 118:     //v
				objects::guide.view = !objects::guide.view;
				break;
		}

		glutPostRedisplay();
	}

	void keyboardUp(unsigned char key, int x, int y) {
		switch(key) {
			case 120:     //x
				if (objects::bodys[objects::element].creation) {
					objects::bodys[objects::element].abscissa = false;
					objects::bodys[objects::element].ordered = false;
					objects::bodys[objects::element].quota = false;

					objects::bodys[objects::element].plot = false;
				}
				break;

			case 121:     //y
				if (objects::bodys[objects::element].creation) {
					objects::bodys[objects::element].abscissa = false;
					objects::bodys[objects::element].ordered = false;
					objects::bodys[objects::element].quota = false;

					objects::bodys[objects::element].plot = false;
				}
				break;

			case 122:     //z
				if (objects::bodys[objects::element].creation) {
					objects::bodys[objects::element].abscissa = false;
					objects::bodys[objects::element].ordered = false;
					objects::bodys[objects::element].quota = false;

					objects::bodys[objects::element].plot = false;
				}
				break;
		}

		glutPostRedisplay();
	}

	void special(int key, int x, int y) {
		switch(key) {
			case GLUT_KEY_LEFT:            //left
				if (settings::perspective) {
					if (settings::nearval - 1 > 0) {
						settings::variation--;
					}
				}
				else {
					screen::angles[1] -= screen::angles[2];
				}
				break;

			case GLUT_KEY_RIGHT:           //right
				if (settings::perspective) {
					settings::variation++;
				}
				else {
					screen::angles[1] += screen::angles[2];
				}
				break;

			case GLUT_KEY_UP:              //up
				if (settings::perspective) {
					settings::variation++;
				}
				else{
					if (screen::angles[0] - screen::angles[2] >= -90) {
						screen::angles[0] -= screen::angles[2];
					}
				}
				break;

			case GLUT_KEY_DOWN:            //down
				if (settings::perspective) {
					if (settings::nearval - 1 > 0) {
						settings::variation--;
					}
				}
				else {
					if (screen::angles[0] + screen::angles[2] <= 90) {
						screen::angles[0] += screen::angles[2];
					}
				}
				break;
		}

		settings::nearval = settings::variation - 5 * settings::mul;
		settings::farval = settings::variation + 100 * settings::mul;

		glutPostRedisplay();
	}

	void motion(int x, int y) {
		screen::relative[1][0] = screen::relative[0][0];
		screen::relative[1][1] = screen::relative[0][1];

		screen::relative[0][0] = x;
		screen::relative[0][1] = y;

		if (objects::bodys[objects::element].abscissa ||
			objects::bodys[objects::element].ordered  ||
			objects::bodys[objects::element].quota) {
			
			if (objects::bodys[objects::element].abscissa) {
				if (screen::relative[0][0] > screen::relative[1][0]) {
					objects::bodys[objects::element].repos(0, true, screen::lengh[0]);
				}
				if (screen::relative[0][0] < screen::relative[1][0]) {
					objects::bodys[objects::element].repos(0, false, screen::lengh[0]);
				}
				if (screen::relative[0][1] > screen::relative[1][1]) {
					objects::bodys[objects::element].repos(0, false, screen::lengh[0]);
				}
				if (screen::relative[0][1] < screen::relative[1][1]) {
					objects::bodys[objects::element].repos(0, true, screen::lengh[0]);
				}
			}

			if (objects::bodys[objects::element].ordered) {
				if (screen::relative[0][0] > screen::relative[1][0]) {
					objects::bodys[objects::element].repos(1, true, screen::lengh[0]);
				}
				if (screen::relative[0][0] < screen::relative[1][0]) {
					objects::bodys[objects::element].repos(1, false, screen::lengh[0]);
				}
				if (screen::relative[0][1] > screen::relative[1][1]) {
					objects::bodys[objects::element].repos(1, false, screen::lengh[0]);
				}
				if (screen::relative[0][1] < screen::relative[1][1]) {
					objects::bodys[objects::element].repos(1, true, screen::lengh[0]);
				}
			}

			if (objects::bodys[objects::element].quota) {
				if (screen::relative[0][0] > screen::relative[1][0]) {
					objects::bodys[objects::element].repos(2, true, screen::lengh[0]);
				}
				if (screen::relative[0][0] < screen::relative[1][0]) {
					objects::bodys[objects::element].repos(2, false, screen::lengh[0]);
				}
				if (screen::relative[0][1] > screen::relative[1][1]) {
					objects::bodys[objects::element].repos(2, false, screen::lengh[0]);
				}
				if (screen::relative[0][1] < screen::relative[1][1]) {
					objects::bodys[objects::element].repos(2, true, screen::lengh[0]);
				}
			}
		}
		else{
			if (mouse::left.press) {
				if (screen::relative[0][0] > screen::relative[1][0]) {
					screen::angles[1] += screen::angles[2];
				}
				if (screen::relative[0][0] < screen::relative[1][0]) {
					screen::angles[1] -= screen::angles[2];
				}

				if (screen::relative[0][1] > screen::relative[1][1]) {
					if (screen::angles[0] + screen::angles[2] <= 90) {
						screen::angles[0] += screen::angles[2];
					}
				}
				if (screen::relative[0][1] < screen::relative[1][1]) {
					if (screen::angles[0] - screen::angles[2] >= -90) {
						screen::angles[0] -= screen::angles[2];
					}
				}
			}
		}

		glutPostRedisplay();
	}

	void mousef(int button, int state, int x, int y) {
		if (button == GLUT_LEFT_BUTTON) {
			if (state == GLUT_DOWN) {
				screen::origin[0] = x;
				screen::origin[1] = y;

				screen::relative[0][0] = x;
				screen::relative[0][1] = y;

				mouse::left.press = true;
			}

			if (state == GLUT_UP) {
				mouse::left.press = false;
			}
		}

		if (button == GLUT_MIDDLE_BUTTON) {
			if (state == GLUT_DOWN) {
				mouse::middle.press = true;
				screen::lengh[0] = 1;
			}
			if (state == GLUT_UP) {
				mouse::middle.press = false;
			}
		}

		if (button == GLUT_RIGHT_BUTTON) {

			if (state == GLUT_DOWN) {
				mouse::right.press = true;

				create();
			}
			if (state == GLUT_UP) {
				mouse::right.press = false;
			}

		}

		glutPostRedisplay();
	}

	void mouseWheel(int button, int dir, int x, int y) {
		if (mouse::right.press) {
			if (dir > 0) {
				objects::bodys[objects::element].redim(true);
			}
			if (dir < 0) {
				objects::bodys[objects::element].redim(false);
			}
		}
		else if (objects::bodys[objects::element].abscissa) {
			if (dir > 0) {
				objects::bodys[objects::element].repos(0, true, screen::lengh[0]);
			}
			if (dir < 0) {
				objects::bodys[objects::element].repos(0, false, screen::lengh[0]);
			}
		}
		else if (objects::bodys[objects::element].ordered) {
			if (dir > 0) {
				objects::bodys[objects::element].repos(1, true, screen::lengh[0]);
			}
			if (dir < 0) {
				objects::bodys[objects::element].repos(1, false, screen::lengh[0]);
			}
		}
		else if (objects::bodys[objects::element].quota) {
			if (dir > 0) {
				objects::bodys[objects::element].repos(2, true, screen::lengh[0]);
			}
			if (dir < 0) {
				objects::bodys[objects::element].repos(2, false, screen::lengh[0]);
			}
		}
		else {
			mouse::scroll[0] = mouse::scroll[1];

			if (dir > 0) {
				mouse::scroll[1] = 1;

				if (mouse::scroll[0] != mouse::scroll[1]) {
					screen::lengh[1] = 0.005;
				}

				if (screen::lengh[0] + screen::lengh[1] <= 5) {
					screen::lengh[0] += screen::lengh[1];
				}
			}
			if (dir < 0) {
				mouse::scroll[1] = -1;

				if (mouse::scroll[0] != mouse::scroll[1]) {
					screen::lengh[1] = 0.005;
				}

				if (screen::lengh[0] - screen::lengh[1] > 0) {
					screen::lengh[0] -= screen::lengh[1];
				}
			}

			screen::lengh[1] += screen::lengh[2];
		}

		glutPostRedisplay();
	}
}

#endif