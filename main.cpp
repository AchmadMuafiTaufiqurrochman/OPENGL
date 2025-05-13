#include <GL/glut.h>
#include <cmath>
typedef struct {
    float x;
    float y;
} Point2D_t;

typedef struct {
    float r;
    float g;
    float b;
} Color_t;

void setColor(Color_t col)
{
    glColor3f(col.r, col.g, col.b);
}

void drawPolyline(Point2D_t pnt[], int n,
    Color_t warna, float size)
{
    setColor(warna);
    glLineWidth(size);
    glBegin(GL_LINE_STRIP);
    for (int i = 0;i < n;i++) {
        glVertex2f(pnt[i].x, pnt[i].y);
    }
    glEnd();
}

void drawPolygon(Point2D_t pnt[], int n,
    Color_t warna, float size)
{
    setColor(warna);
    glLineWidth(size);
    glBegin(GL_LINE_LOOP);
    for (int i = 0;i < n;i++) {
        glVertex2f(pnt[i].x, pnt[i].y);
    }
    glEnd();
}

void fillPolygon(Point2D_t pnt[], int n,
    Color_t warna)
{
    setColor(warna);
    glBegin(GL_POLYGON);
    for (int i = 0;i < n;i++) {
        glVertex2f(pnt[i].x, pnt[i].y);
    }
    glEnd();
}

void gradatePolygon(Point2D_t pnt[], int n,
    Color_t warna1,
    Color_t warna2, int b)
{
    glBegin(GL_POLYGON);
    for (int i = 0;i < n;i++) {
        if (i <= b) setColor(warna1);
        else setColor(warna2);
        glVertex2f(pnt[i].x, pnt[i].y);
    }
    glEnd();
}

void drawCircle(Point2D_t pusat, float jari2, int sudut,
 float size, Point2D_t pntCircle[])
{
int sdt,i;
sdt=0;
for(i=0;i<=abs(sudut);i++)
{
float srad = sdt * 3.14/180;
pntCircle[i].x=(float)((jari2 * cos(srad)) + pusat.x);
pntCircle[i].y=(float)((jari2 * sin(srad)) + pusat.y);
if(sudut>0) sdt++;
else sdt--;
}
}

void drawEllipse(Point2D_t pusat, float jariH, float jariV, int sudut, float size,
    Point2D_t pntEllipse[])
{
    int sdt, i;
    sdt = 0;
    for (i = 0;i <= abs(sudut);i++)
    {
        float srad = sdt * 3.14 / 180;
        pntEllipse[i].x = (float)((jariH * cos(srad)) + pusat.x);
        pntEllipse[i].y = (float)((jariV * sin(srad)) + pusat.y);
        if (sudut > 0) sdt++;
        else sdt--;
    }
}

void userdraw()
{
//isinya warna
Color_t putih_tulang = {0.9,0.9,0.8};
Color_t hitam = {0,0,0};
Color_t coklat_cerah = {0.8,0.5,0};
Color_t coklat_gelap_bgt = {0.30000000000000004,0.30000000000000004,0};
Color_t api_cerah = {1,1,0.7000000000000001};
Color_t api_menyala = {1,0.8,0.2};

// pintu
Point2D_t  ktk_pintu [4] = {{40.,0.},{180.,0.},{180.,320.},{40.,320.}};
drawPolygon(ktk_pintu, 4, hitam, 10);
fillPolygon(ktk_pintu, 4, coklat_cerah);

//gaggang pintu
Point2D_t  lngkrn_ggng_pintu [1] = {{150.,140.}};
Point2D_t lingkaran_penuh[360];
drawCircle(lngkrn_ggng_pintu[0], 10,360,1.0,lingkaran_penuh);
drawPolygon(lingkaran_penuh,360,hitam,2.0);
fillPolygon(lingkaran_penuh, 360,putih_tulang);

//ganggang obor
Point2D_t  ktk_ggng_obor1 [4] = {{240.,220.},{260.,220.},{260.,280.},{240.,280.}};
drawPolygon(ktk_ggng_obor1,4,hitam,10);
fillPolygon(ktk_ggng_obor1,4,coklat_gelap_bgt);

//kotak api cerah obor 1
Point2D_t  ktk_api1_obor1 [4] = {{240.,280.},{260.,280.},{260.,292.},{240.,292.}};
drawPolygon(ktk_api1_obor1,4,hitam,10);
fillPolygon(ktk_api1_obor1,4,api_cerah);

//kotak api menyala obor 1
Point2D_t  ktk_api2_obor1 [4] = {{240.,292.},{260.,292.},{260.,300.},{240.,300.}};
drawPolygon(ktk_api2_obor1,4,hitam,10);
fillPolygon(ktk_api2_obor1,4,api_menyala);

//kotak api ganggang obor 2
Point2D_t  ktk_ggng_obor2 [4] = {{300.,220.},{320.,220.},{320.,280.},{300.,280.}};
drawPolygon(ktk_ggng_obor2,4,hitam,10);
fillPolygon(ktk_ggng_obor2,4,coklat_gelap_bgt);

Point2D_t  ktk_api1_obor2 [4] = {{300.,280.},{320.,280.},{320.,292.},{300.,292.}};
drawPolygon(ktk_api1_obor2,4,hitam,10);
fillPolygon(ktk_api1_obor2,4,api_cerah);

Point2D_t  ktk_api2_obor2 [4] = {{300.,292.},{320.,292.},{320.,300.},{300.,300.}};
drawPolygon(ktk_api2_obor2,4,hitam,10);
fillPolygon(ktk_api2_obor2,4,api_menyala);

Point2D_t  ktk_crfting_tble [4] = {{240.,0.},{340.,0.},{340.,100.},{240.,100.}};
drawPolygon(ktk_crfting_tble,4,hitam,10);
fillPolygon(ktk_crfting_tble,4,coklat_cerah);

Point2D_t  sgt_crfiting_tble [3] = {{280.,100.},{300.,100.},{290.,80.}};
drawPolygon(sgt_crfiting_tble,3,hitam,10);
fillPolygon(sgt_crfiting_tble,3,hitam);

Point2D_t  line_crfting_tble [2] = {{290.,80.},{290.,0.}};
drawPolyline(line_crfting_tble,2,hitam,6);

Point2D_t  ktk_ggng_palu [4] = {{256.,40.},{264.,40.},{264.,80.},{256.,80.}};
drawPolygon(ktk_ggng_palu, 4, hitam,5);
fillPolygon(ktk_ggng_palu,4,coklat_gelap_bgt);

Point2D_t  ktk_palu [4] = {{248.,30.},{272.,30.},{272.,40.},{248.,40.}};
drawPolygon(ktk_palu, 4, hitam,5);
fillPolygon(ktk_palu,4,putih_tulang);



}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    userdraw();
    glutSwapBuffers();
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