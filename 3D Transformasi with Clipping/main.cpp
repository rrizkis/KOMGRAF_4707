#include <GL/glut.h>
#include <iostream>
#include <cmath>

float vertices[8][3] = {
    {-1, -1, -1}, {-1, -1, 1},
    {-1, 1, -1},  {-1, 1, 1},
    {1, -1, -1},  {1, -1, 1},
    {1, 1, -1},   {1, 1, 1}
};

float translation[3] = {0, 0, 0};
float rotation[3] = {0, 0, 0};
float scaling[3] = {1, 1, 1};
float color[6][3] = {
    {1.0, 0.0, 0.0}, // Merah
    {0.0, 1.0, 0.0}, // Hijau
    {0.0, 0.0, 1.0}, // Biru
    {1.0, 1.0, 0.0}, // Kuning
    {1.0, 0.0, 1.0}, // Ungu
    {0.0, 1.0, 1.0}  // Cyan
};

void drawCube() {
    // Gambar kubus dengan GL_QUADS
    glBegin(GL_QUADS);

    // Sisi depan
    glColor3fv(color[0]);
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[1]);
    glVertex3fv(vertices[3]);
    glVertex3fv(vertices[2]);

    // Sisi belakang
    glColor3fv(color[1]);
    glVertex3fv(vertices[4]);
    glVertex3fv(vertices[5]);
    glVertex3fv(vertices[7]);
    glVertex3fv(vertices[6]);

    // Sisi kiri
    glColor3fv(color[2]);
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[2]);
    glVertex3fv(vertices[6]);
    glVertex3fv(vertices[4]);

    // Sisi kanan
    glColor3fv(color[3]);
    glVertex3fv(vertices[1]);
    glVertex3fv(vertices[3]);
    glVertex3fv(vertices[7]);
    glVertex3fv(vertices[5]);

    // Sisi atas
    glColor3fv(color[4]);
    glVertex3fv(vertices[2]);
    glVertex3fv(vertices[3]);
    glVertex3fv(vertices[7]);
    glVertex3fv(vertices[6]);

    // Sisi bawah
    glColor3fv(color[5]);
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[1]);
    glVertex3fv(vertices[5]);
    glVertex3fv(vertices[4]);

    glEnd();
}

void mirrorY() {
    for (int i = 0; i < 8; ++i) {
        vertices[i][0] = -vertices[i][0];
    }
}

void mirrorX() {
    for (int i = 0; i < 8; ++i) {
        vertices[i][1] = -vertices[i][1];
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Lihat dari sudut 45 derajat

    // Terapkan transformasi
    glTranslatef(translation[0], translation[1], translation[2]);
    glRotatef(rotation[0], 1, 0, 0);
    glRotatef(rotation[1], 0, 1, 0);
    glRotatef(rotation[2], 0, 0, 1);
    glScalef(scaling[0], scaling[1], scaling[2]);

    // Gambar kubus dengan warna
    drawCube();

    // Simpan matriks modelview untuk digunakan dalam clipping
    float modelviewMatrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);

    // Cek apakah setiap titik kubus berada di dalam frustum (clipping)
    for (int i = 0; i < 8; ++i) {
        float transformedVertex[4];
        for (int j = 0; j < 4; ++j) {
            transformedVertex[j] = 0;
            for (int k = 0; k < 4; ++k) {
                transformedVertex[j] += modelviewMatrix[k * 4 + j] * vertices[i][k];
            }
        }

        if (transformedVertex[2] < -transformedVertex[3] || transformedVertex[2] > transformedVertex[3]) {
            // Titik berada di luar frustum, lewati penggambarannya
            continue;
        }

        // Normalisasi koordinat proyeksi dan lakukan perspektif divide
        float w_inv = 1.0 / transformedVertex[3];
        transformedVertex[0] *= w_inv;
        transformedVertex[1] *= w_inv;
        transformedVertex[2] *= w_inv;

        // Gambar titik yang masih berada di dalam frustum
        glBegin(GL_POINTS);
        glVertex3fv(transformedVertex);
        glEnd();
    }

    glutSwapBuffers();
}

void menu(int value) {
    switch (value) {
        case 1:
            std::cout << "Masukkan nilai translasi (tx ty tz): ";
            std::cin >> translation[0] >> translation[1] >> translation[2];
            break;
        case 2:
            std::cout << "Masukkan nilai rotasi (rx ry rz): ";
            std::cin >> rotation[0] >> rotation[1] >> rotation[2];
            break;
        case 3:
            std::cout << "Masukkan nilai scaling (sx sy sz): ";
            std::cin >> scaling[0] >> scaling[1] >> scaling[2];
            break;
        case 4:
            mirrorX();
            break;
        case 5:
            mirrorY();
            break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Transformasi dan Pencerminan Kubus");

    glEnable(GL_DEPTH_TEST);

    // Tambahkan inisialisasi perspektif
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 1.0, 100.0); // Fovy, Aspect, Znear, Zfar
    glMatrixMode(GL_MODELVIEW);

    int menuId = glutCreateMenu(menu);
    glutAddMenuEntry("Translasi", 1);
    glutAddMenuEntry("Rotasi", 2);
    glutAddMenuEntry("Scaling", 3);
    glutAddMenuEntry("MirrorX", 4);
    glutAddMenuEntry("MirrorY", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

