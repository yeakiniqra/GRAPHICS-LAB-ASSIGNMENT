#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



#define MAX_LINES 10

typedef struct {
    int x1, y1, x2, y2;
} Line;

Line lines[MAX_LINES];
int numLines = 0;
int xmin = 100, ymin = 100, xmax = 400, ymax = 400;

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

int clipTest(float p, float q, float *t1, float *t2) {
    float r;
    int result = 1;

    if (p < 0.0f) {
        r = q / p;
        if (r > *t2) {
            result = 0;
        } else if (r > *t1) {
            *t1 = r;
        }
    } else if (p > 0.0f) {
        r = q / p;
        if (r < *t1) {
            result = 0;
        } else if (r < *t2) {
            *t2 = r;
        }
    } else {
        if (q < 0.0f) {
            result = 0;
        }
    }
    return result;
}

int liangBarsky(float x1, float y1, float x2, float y2,
                float *cx1, float *cy1, float *cx2, float *cy2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float t1 = 0.0f;
    float t2 = 1.0f;

    if (clipTest(-dx, x1 - xmin, &t1, &t2)) {
        if (clipTest(dx, xmax - x1, &t1, &t2)) {
            if (clipTest(-dy, y1 - ymin, &t1, &t2)) {
                if (clipTest(dy, ymax - y1, &t1, &t2)) {
                    if (t2 < 1.0f) {
                        *cx2 = x1 + t2 * dx;
                        *cy2 = y1 + t2 * dy;
                    } else {
                        *cx2 = x2;
                        *cy2 = y2;
                    }

                    if (t1 > 0.0f) {
                        *cx1 = x1 + t1 * dx;
                        *cy1 = y1 + t1 * dy;
                    } else {
                        *cx1 = x1;
                        *cy1 = y1;
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

void draw_clipping_window() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmax, ymin);
    glVertex2i(xmax, ymax);
    glVertex2i(xmin, ymax);
    glEnd();
}

void draw_clipped_lines() {
    draw_clipping_window();

    for (int i = 0; i < numLines; i++) {
        float cx1, cy1, cx2, cy2;


        glColor3f(1.0f, 0.0f, 0.0f);
        draw_line(lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2);

    
        if (liangBarsky((float)lines[i].x1, (float)lines[i].y1,
                       (float)lines[i].x2, (float)lines[i].y2,
                       &cx1, &cy1, &cx2, &cy2)) {
            glColor3f(0.0f, 1.0f, 0.0f);
            draw_thick_line((int)cx1, (int)cy1, (int)cx2, (int)cy2, 3);
        }
    }
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    draw_clipped_lines();
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'q' || key == 'Q') {
        exit(0);
    }
}

void initializeData() {

    numLines = 5;
    lines[0].x1 = 50; lines[0].y1 = 150; lines[0].x2 = 450; lines[0].y2 = 350;
    lines[1].x1 = 150; lines[1].y1 = 50; lines[1].x2 = 350; lines[1].y2 = 450;
    lines[2].x1 = 200; lines[2].y1 = 200; lines[2].x2 = 300; lines[2].y2 = 300;
    lines[3].x1 = 50; lines[3].y1 = 450; lines[3].x2 = 450; lines[3].y2 = 50;
    lines[4].x1 = 10; lines[4].y1 = 10; lines[4].x2 = 80; lines[4].y2 = 80;
}

int main(int argc, char **argv) {
    printf("Task 3: Liang-Barsky Line Clipping Algorithm\n");
    printf("Clipping window: (%d, %d) to (%d, %d)\n", xmin, ymin, xmax, ymax);
    printf("Number of lines: %d\n", 5);
    printf("Color coding:\n");
    printf("  White  - Clipping window\n");
    printf("  Red    - Original lines\n");
    printf("  Green  - Clipped portions\n");
    printf("Press Q to quit\n\n");

    initializeData();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Task 3 - Liang-Barsky Clipping");

    myInit();
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
