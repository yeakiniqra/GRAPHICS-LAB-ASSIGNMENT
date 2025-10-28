#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int line_x1 = 50, line_y1 = 50, line_x2 = 450, line_y2 = 400;
int lineThickness = 5;

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

void draw_line(int x1, int y1, int x2, int y2) {
    int dx, dy, i, e;
    int incx, incy, inc1, inc2;
    int x, y;

    dx = x2 - x1;
    dy = y2 - y1;

    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    incx = 1;
    if (x2 < x1) incx = -1;
    incy = 1;
    if (y2 < y1) incy = -1;
    x = x1;
    y = y1;

    if (dx > dy) {
        draw_pixel(x, y);
        e = 2 * dy - dx;
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;
        for (i = 0; i < dx; i++) {
            if (e >= 0) {
                y += incy;
                e += inc1;
            } else {
                e += inc2;
            }
            x += incx;
            draw_pixel(x, y);
        }
    } else {
        draw_pixel(x, y);
        e = 2 * dx - dy;
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;
        for (i = 0; i < dy; i++) {
            if (e >= 0) {
                x += incx;
                e += inc1;
            } else {
                e += inc2;
            }
            y += incy;
            draw_pixel(x, y);
        }
    }
}

void draw_thick_line(int x1, int y1, int x2, int y2, int thickness) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    double length = sqrt((double)(dx * dx + dy * dy));

    if (length == 0) {
        for (int i = -thickness/2; i <= thickness/2; i++) {
            for (int j = -thickness/2; j <= thickness/2; j++) {
                draw_pixel(x1 + i, y1 + j);
            }
        }
        return;
    }

 
    double perpX = -dy / length;
    double perpY = dx / length;


    for (int t = -thickness/2; t <= thickness/2; t++) {
        int offsetX = (int)(perpX * t);
        int offsetY = (int)(perpY * t);
        draw_line(x1 + offsetX, y1 + offsetY, x2 + offsetX, y2 + offsetY);
    }
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 0.0f);
    draw_thick_line(line_x1, line_y1, line_x2, line_y2, lineThickness);
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case '+':
            lineThickness++;
            printf("Line thickness: %d\n", lineThickness);
            glutPostRedisplay();
            break;
        case '-':
            if (lineThickness > 1) {
                lineThickness--;
                printf("Line thickness: %d\n", lineThickness);
                glutPostRedisplay();
            }
            break;
        case 'q':
        case 'Q':
            exit(0);
            break;
    }
}

int main(int argc, char **argv) {
    printf("Task 1b: Thick Line Drawing (8-way symmetry)\n");
    printf("Drawing line from (%d, %d) to (%d, %d)\n", line_x1, line_y1, line_x2, line_y2);
    printf("Initial thickness: %d\n", lineThickness);
    printf("Controls:\n");
    printf("  + : Increase line thickness\n");
    printf("  - : Decrease line thickness\n");
    printf("  Q : Quit\n\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Task 1b - Thick Line Drawing");

    myInit();
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
