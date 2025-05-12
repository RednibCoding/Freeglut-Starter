#include <stdio.h>
#include <string.h>
#include <GL/freeglut.h>

static int key_state[256] = { 0 };
static int mouse_buttons[3] = { 0 };
static int mouse_x = 0, mouse_y = 0;
static int mouse_wheel = 0;

static double lastTime = 0.0;
static int frameCount = 0;
static int currentFPS = 0;

int is_key_down(unsigned char key) {
    return key_state[key];
}

int is_mouse_button_down(int button) {
    return (button >= 0 && button < 3) ? mouse_buttons[button] : 0;
}

void createLights() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);  // Ensure normals are scaled properly
    glShadeModel(GL_SMOOTH);

    GLfloat light_pos[] = { 2.0f, 2.0f, 2.0f, 1.0f };
    GLfloat light_amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_dif[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat light_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_spe);

    GLfloat mat_spec[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, aspect, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text++);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Setup camera
    gluLookAt(
        0.0, 0.0, 5.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    // Draw spinning cube
    static float angle = 0.0f;
    angle += 1.0f;

    glRotatef(angle, 1.0f, 1.0f, 0.0f);
    glColor3f(0.2f, 0.8f, 1.0f);
    glutSolidCube(1.5f);

    // Draw FPS
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 600, 0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    char fpsText[32];
    sprintf(fpsText, "FPS: %d", currentFPS);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(10, 20, fpsText);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
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
    double currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double delta = currentTime - lastTime;

    if (delta >= 1.0 / 60.0) {
        lastTime = currentTime;
        glutPostRedisplay();

        frameCount++;
        static double fpsTimer = 0.0;
        fpsTimer += delta;
        if (fpsTimer >= 1.0) {
            currentFPS = frameCount;
            frameCount = 0;
            fpsTimer = 0.0;
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("FreeGLUT C99 Starter");

    glEnable(GL_DEPTH_TEST);
    createLights();

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
