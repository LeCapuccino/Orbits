#include "../include/GL/glut.h"
#include "../include/GL/freeglut.h"

#ifndef AXIS_HPP
#define AXIS_HPP

namespace axis {
	class Axis {
	public:
		float color = 0.9;

		bool view = true;

		void col(bool cond) {
			if (cond) {color += 0.08;}
			else {color -= 0.08;}
		}

		void draw() {
			if (view) {
				glColor3f(0.26, 0.90, 0.87);        //x
				glLineWidth(2.0);
				glBegin(GL_LINES);
					glVertex3f(0, 0, 0);
					glVertex3f(0.2 * settings::mul, 0, 0);
				glEnd();

				glColor3f(0.90, 0.83, 0.26);        //y
				glLineWidth(2.0);
				glBegin(GL_LINES);
					glVertex3f(0, 0, 0);
					glVertex3f(0, 0.2 * settings::mul, 0);
				glEnd();

				glColor3f(0.90, 0.26, 0.43);        //z
				glLineWidth(2.0);
				glBegin(GL_LINES);
					glVertex3f(0, 0, 0);
					glVertex3f(0, 0, 0.2 * settings::mul);
				glEnd();

				glColor3f(color, color, color);      //-x
				glLineWidth(2.0);
				glBegin(GL_LINES);
					glVertex3f(0, 0, 0);
					glVertex3f(-0.2 * settings::mul, 0, 0);
				glEnd();

				glColor3f(color, color, color);      //-y
				glLineWidth(2.0);
				glBegin(GL_LINES);
					glVertex3f(0, 0, 0);
					glVertex3f(0, -0.2 * settings::mul, 0);
				glEnd();

				glColor3f(color, color, color);     //-z
				glLineWidth(2.0);
				glBegin(GL_LINES);
					glVertex3f(0, 0, 0);
					glVertex3f(0, 0, -0.2 * settings::mul);
				glEnd();
			}
		}
	};
}

#endif