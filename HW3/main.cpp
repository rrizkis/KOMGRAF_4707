#include <GL/glut.h>
#include <cmath>
#include <algorithm>
#include <iostream>

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 15, 0, 15);
}

void drawLineDDA(int x1, int y1, int x2, int y2, const char* soal) {
    glColor3f(0.0, 0.5, 0.0);
    glPointSize(8.0);
    glBegin(GL_POINTS);

    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = std::max(std::abs(dx), std::abs(dy));

    float xInc = static_cast<float>(dx) / steps;
    float yInc = static_cast<float>(dy) / steps;
    float x = x1;
    float y = y1;

    std::cout << soal << std::endl;

    for(int i = 0; i <= steps; ++i) {
        glVertex2i(round(x), round(y));
        std::cout << "(" << round(x) << ", " << round(y) << ")" << std::endl;
        x += xInc;
        y += yInc;
    }

    glEnd();
    glFlush();
}

void display1() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawLineDDA(10, 1, 2, 10, "Soal 1 : A(10, 1); B(2, 10)");
    glFlush();
}

void display2() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawLineDDA(4, 1, 8, 12, "Soal 2 : A(4, 1); B(8, 12)");
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Output Soal 1
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Algorithm (Soal 1)");
    init();
    glutDisplayFunc(display1);

    // Output Soal 2
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(600, 100);
    glutCreateWindow("DDA Algorithm (Soal 2)");
    init();
    glutDisplayFunc(display2);

    glutMainLoop();
    return 0;
}
