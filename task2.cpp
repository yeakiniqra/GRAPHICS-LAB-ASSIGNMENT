#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>

void myInit() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void draw_pixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void draw_circle_points(int xc, int yc, int x, int y) {
    draw_pixel(xc + x, yc + y);
    draw_pixel(xc - x, yc + y);
    draw_pixel(xc + x, yc - y);
    draw_pixel(xc - x, yc - y);
    draw_pixel(xc + y, yc + x);
    draw_pixel(xc - y, yc + x);
    draw_pixel(xc + y, yc - x);
    draw_pixel(xc - y, yc - x);
}

void draw_circle(int xc, int yc, int radius) {
    int x = 0;
    int y = radius;
    int p = 1 - radius;

    draw_circle_points(xc, yc, x, y);

    while (x < y) {
        x++;
        if (p < 0) {
            p = p + 2 * x + 1;
        } else {
            y--;
            p = p + 2 * (x - y) + 1;
        }
        draw_circle_points(xc, yc, x, y);
    }
}

void draw_thick_circle(int xc, int yc, int radius, int thickness) {
    for (int t = 0; t < thickness; t++) {
        draw_circle(xc, yc, radius + t - thickness/2);
    }
}

void draw_concentric_circles() {
    int centerX = 250;
    int centerY = 250;
    int numCircles = 10;
    int maxRadius = 200;

    for (int i = 0; i < numCircles; i++) {
        int radius = (i + 1) * maxRadius / numCircles;
        int thickness = 2 + i / 2;

        float t = (float)i / (numCircles - 1);
        glColor3f(1.0f - t, 0.2f, t);

        draw_thick_circle(centerX, centerY, radius, thickness);
    }
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    draw_concentric_circles();
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'q' || key == 'Q') {
        exit(0);
    }
}

int main(int argc, char **argv) {
    printf("Task 2: Concentric Circles with Color Gradient\n");
    printf("Drawing 10 concentric circles with:\n");
    printf("  - Increasing radius and thickness\n");
    printf("  - Color gradient from red to blue\n");
    printf("Press Q to quit\n\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Task 2 - Concentric Circles");

    myInit();
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
