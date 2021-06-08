#include "../include/GL/glut.h"
#include "../include/GL/freeglut.h"

#include "../include/functions.hpp"
#include "../include/settings.hpp"
#include "../include/screen.hpp"

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition((GetSystemMetrics(SM_CXSCREEN) - screen::width)/2,
                           (GetSystemMetrics(SM_CYSCREEN) - screen::height)/2);
    glutInitWindowSize(screen::width, screen::height);
    glutCreateWindow("Orbits");

    glEnable(GL_DEPTH_TEST);

    functions::init();

    glutDisplayFunc(functions::display);
    glutTimerFunc(settings::per, functions::timer, 0.0);
    glutReshapeFunc(functions::reshape);
    glutKeyboardFunc(functions::keyboard);
    glutKeyboardUpFunc(functions::keyboardUp);
    glutSpecialFunc(functions::special);
    glutMotionFunc(functions::motion);
    glutMouseWheelFunc(functions::mouseWheel);
    glutMouseFunc(functions::mousef);

    glFlush();

    glutMainLoop();

    return 0;
}