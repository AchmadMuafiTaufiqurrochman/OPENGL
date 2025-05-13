#include <GL/glut.h>
#include <cmath>

// === Struktur Data Sesuai PDF ===
typedef struct {
    float x;
    float y;
} Point2D_t;

typedef struct {
    float r;
    float g;
    float b;
} Color_t;

// === Deklarasi Fungsi ===
void setColor(Color_t col);
void fillPolygon(Point2D_t pnt[], int n, Color_t warna);
void drawPolygon(Point2D_t pnt[], int n, Color_t warna, float size);
void drawCircle(Point2D_t pusat, float jari2, int sudut, float size, Point2D_t pntCircle[]);

// === Fungsi Display ===
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Bersihkan layar

    // === Lingkaran merah (tanpa outline) ===
    const int JUMLAH_TITIK_LINGKARAN = 360;
    Point2D_t lingkaran[JUMLAH_TITIK_LINGKARAN];
    Point2D_t pusatLingkaran = {460.0, 360.0}; // Pusat layar
    float radius = 100.0;

    drawCircle(pusatLingkaran, radius, 360, 1.0, lingkaran);
    Color_t merah = {1.0, 0.0, 0.0};
    fillPolygon(lingkaran, JUMLAH_TITIK_LINGKARAN, merah);

    // === Kotak dengan outline hitam dan isi biru ===
    Point2D_t kotak[4] = {
        {100.0, 100.0},
        {300.0, 100.0},
        {300.0, 200.0},
        {100.0, 200.0}
    };

    Color_t biru = {0.0, 0.0, 1.0};     // Warna biru untuk isi
    Color_t hitam = {0.0, 0.0, 0.0};    // Warna hitam untuk outline

    // Gambar isi kotak dulu, baru outline agar tetap terlihat
    fillPolygon(kotak, 4, biru);
    drawPolygon(kotak, 4, hitam, 2.0f);  // Garis tepi tebal 2.0

    glutSwapBuffers(); // Tampilkan hasil
}

// === Implementasi Fungsi ===

// Set warna
void setColor(Color_t col) {
    glColor3f(col.r, col.g, col.b);
}

// Isi polygon (warna bagian dalam)
void fillPolygon(Point2D_t pnt[], int n, Color_t warna) {
    setColor(warna);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(pnt[i].x, pnt[i].y);
    }
    glEnd();
}

// Gambar outline polygon
void drawPolygon(Point2D_t pnt[], int n, Color_t warna, float size) {
    setColor(warna);
    glLineWidth(size);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++) {
        glVertex2f(pnt[i].x, pnt[i].y);
    }
    glEnd();
}

// Gambar titik-titik lingkaran
void drawCircle(Point2D_t pusat, float jari2, int sudut, float size, Point2D_t pntCircle[]) {
    int sdt = 0;
    for (int i = 0; i <= abs(sudut); i++) {
        float srad = sdt * 3.14159f / 180.0f;
        pntCircle[i].x = (float)((jari2 * cos(srad)) + pusat.x);
        pntCircle[i].y = (float)((jari2 * sin(srad)) + pusat.y);
        if (sudut > 0) sdt++;
        else sdt--;
    }
}

// === Main Function ===
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(920, 720);
    glutCreateWindow("Lingkaran Merah & Kotak Biru Hitam Outline");

    glClearColor(1.0, 1.0, 1.0, 0.0); // Background putih
    gluOrtho2D(0.0, 920.0, 0.0, 720.0); // Sistem koordinat (0,0) di kiri bawah

    glutDisplayFunc(display);
    glutIdleFunc(display); // Agar tetap update

    glutMainLoop();
    return 0;
}