#include <GL/glut.h>

// Struktur titik 2D
typedef struct {
    float x;
    float y;
} Point2D_t;

// Struktur warna RGB
typedef struct {
    float r;
    float g;
    float b;
} Color_t;

// Fungsi set warna
void setColor(Color_t col) {
    glColor3f(col.r, col.g, col.b);
}

// Fungsi menggambar polyline
void drawPolyline(Point2D_t pnt[], int n, Color_t warna, float size) {
    setColor(warna);
    glLineWidth(size);
    glBegin(GL_LINE_LOOP); // Menggunakan GL_LINE_LOOP untuk menutup poligon
    for (int i = 0; i < n; i++) {
        glVertex2f(pnt[i].x, pnt[i].y);
    }
    glEnd();
}

// Fungsi display untuk menggambar
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Definisi titik-titik kotak
    Point2D_t kotak[4] = {
        {100.0, 100.0},   // Titik 0
        {300.0, 100.0},   // Titik 1
        {300.0, 300.0},   // Titik 2
        {100.0, 300.0}    // Titik 3
    };

    // Definisi warna
    Color_t merah = {1.0, 0.0, 0.0};

    // Gambar kotak sebagai polyline
    drawPolyline(kotak, 4, merah, 3.0);  // 4 titik, warna merah, tebal garis 3

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 75);
    glutInitWindowSize(920, 720);
    glutCreateWindow("UTS Achmad Muafi Taufiqurrochman");

    glClearColor(1.0, 1.0, 1.0, 0.0); // Background putih
    gluOrtho2D(0, 920, 0, 720); // Sistem koordinat (0,0) di kiri bawah

    glutIdleFunc(display);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}