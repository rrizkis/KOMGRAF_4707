#include <gl/glut.h>
#include <stdio.h>

int x1, y1, x2, y2;

void myInit() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 10, 0, 10);
}

void draw_pixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void draw_line(int x1, int x2, int y1, int y2) {
    int dx, dy, i, p;
    int incx, incy, inc1, inc2;
    int x, y;

    dx = x2 - x1;
    dy = y2 - y1;

    incx = 1;
    if (dx < 0) {
        incx = -1;
        dx = -dx;
    }
    incy = 1;
    if (dy < 0) {
        incy = -1;
        dy = -dy;
    }

    x = x1;
    y = y1;
    printf("(%d, %d)\n", x, y); // Cetak titik pertama

    if (dx > dy) {
        p = 2 * dy - dx;
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;

        for (i = 0; i < dx; i++) {
            x += incx;
            if (p >= 0) {
                y += incy;
                p += inc1;
            } else {
                p += inc2;
            }
            printf("(%d, %d)\n", x, y); // Cetak titik yang dilalui
        }
    } else {
        p = 2 * dx - dy;
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;

        for (i = 0; i < dy; i++) {
            y += incy;
            if (p >= 0) {
                x += incx;
                p += inc1;
            } else {
                p += inc2;
            }
            printf("(%d, %d)\n", x, y); // Cetak titik yang dilalui
        }
    }
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Warna garis (putih)
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
	printf("NIM : 13783\n");
    printf("Titik-titik yang dilalui:\n");
    draw_line(x1, x2, y1, y2);
    glFlush();
}



int main(int argc, char **argv) {
    x1 = 3;
    y1 = 7;
    x2 = 8;
    y2 = 3;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham Algorithm");
    myInit();

    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}

