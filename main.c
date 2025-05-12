#include <stdio.h>
#include <string.h>
#include <GL/freeglut.h>

static int key_state[256] = { 0 };
static int mouse_buttons[3] = { 0 };
static int mouse_x = 0, mouse_y = 0;
static int mouse_wheel = 0;

int is_key_down(unsigned char key) {
    return key_state[key];
}

int is_mouse_button_down(int button) {
    return (button >= 0 && button < 3) ? mouse_buttons[button] : 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Example: draw a red background
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);  // Top-left origin
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
    key_state[key] = 1;
    if (key == 27) exit(0);  // ESC to quit
}

void keyboardUp(unsigned char key, int x, int y) {
    key_state[key] = 0;
}

void mouse(int button, int state, int x, int y) {
    if (button >= 0 && button < 3) {
        mouse_buttons[button] = (state == GLUT_DOWN);
    }
    mouse_x = x;
    mouse_y = y;
}

void motion(int x, int y) {
    mouse_x = x;
    mouse_y = y;
}

void passiveMotion(int x, int y) {
    mouse_x = x;
    mouse_y = y;
}

void mouseWheel(int wheel, int direction, int x, int y) {
    mouse_wheel += direction;
}

void idle() {
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("FreeGLUT C99 Starter");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(passiveMotion);
    glutMouseWheelFunc(mouseWheel);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
