#include <GL/glut.h>
#include <iostream>
#include <cmath>

float A[2] = {3, 8};
float B[2] = {7, 3};
int selectedTransformation = 0;

// Fungsi untuk melakukan translasi
void translate(float &x, float &y, float tx, float ty) {
    x += tx;
    y += ty;
    x = std::max(0.0f, std::min(10.0f, x));
    y = std::max(0.0f, std::min(10.0f, y));
}

// Rotasi
void rotate(float &x, float &y, float angle) {
    float angle_radians = angle * M_PI / 180.0;
    float new_x = A[0] + (x - A[0]) * cos(angle_radians) - (y - A[1]) * sin(angle_radians);
    float new_y = A[1] + (x - A[0]) * sin(angle_radians) + (y - A[1]) * cos(angle_radians);
    x = new_x;
    y = new_y;
}

// Scaling
void scale(float &x, float &y, float sx, float sy) {
    x = A[0] + (x - A[0]) * sx;
    y = A[1] + (y - A[1]) * sy;
}

// Display garis
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2f(A[0], A[1]);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2f(B[0], B[1]);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(A[0], A[1]);
    glVertex2f(B[0], B[1]);
    glEnd();

    glRasterPos2f(3.5, 8.2);
    const char* pointAText = "Titik A";
    for (int i = 0; pointAText[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, pointAText[i]);
    }

    glRasterPos2f(7.2, 3.2);
    const char* pointBText = "Titik B";
    for (int i = 0; pointBText[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, pointBText[i]);
    }

    glRasterPos2f(0.5, 0.5);
    const char* menuText = "Klik kanan untuk melihat menu";
    for (int i = 0; menuText[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, menuText[i]);
    }

    glFlush();
}


// Pilihan menu
void menu(int value) {
    selectedTransformation = value;
    if (selectedTransformation == 1) {
        float tx, ty;
        std::cout << "Masukkan nilai tx dan ty (pisahkan dengan spasi): ";
        std::cin >> tx >> ty;
        translate(A[0], A[1], tx, ty);
        translate(B[0], B[1], tx, ty);
    } else if (selectedTransformation == 2) {
        float angle;
        std::cout << "Masukkan sudut rotasi (derajat): ";
        std::cin >> angle;
        rotate(A[0], A[1], angle);
        rotate(B[0], B[1], angle);
    } else if (selectedTransformation == 3) {
        float sx, sy;
        std::cout << "Masukkan faktor scaling sx dan sy (pisahkan dengan spasi): ";
        std::cin >> sx >> sy;
        scale(A[0], A[1], sx, sy);
        scale(B[0], B[1], sx, sy);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Transformasi Titik A dan B");

    // Membuat menu
    int menuId = glutCreateMenu(menu);
    glutAddMenuEntry("Tidak Ada Transformasi", 0);
    glutAddMenuEntry("Translasi", 1);
    glutAddMenuEntry("Rotasi", 2);
    glutAddMenuEntry("Scaling", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 10.0, 0.0, 10.0);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

