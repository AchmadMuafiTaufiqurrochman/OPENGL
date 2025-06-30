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

void drawPolygon(Point2D_t pnt[], int n,Color_t warna, float size)
{
    setColor(warna);
    glLineWidth(size);
    glBegin(GL_LINE_LOOP);
    for (int i = 0;i < n;i++) {
        glVertex2f(pnt[i].x, pnt[i].y);
    }
    glEnd();
}

void fillPolygon(Point2D_t pnt[], int n,Color_t warna)
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

void Translasi(Point2D_t t_objek[], Point2D_t objek[], int n, float dx, float dy, float tick)
{
    static float transX = 0., transY = 0.;
    float ddx, ddy, batasX, batasY, gerakX, gerakY;
    int aba, kika;
    for (int i = 0; i < n; i++)
    {
        t_objek[i].x = objek[i].x + transX;
        t_objek[i].y = objek[i].y + transY;
    }
    if (dx == 0.)
    {
        ddx = 0.;
        ddy = tick;
    }
    else if (dy == 0.)
    {
        ddx = tick;
        ddy = 0.;
    }

    else if ((abs(dx) < abs(dy)) && (dx != 0.))
    {
        ddx = tick;
        ddy = (abs(dy) / abs(dx)) * tick;
    }
    else if ((abs(dy) < abs(dx)) && (dy != 0.))
    {
        ddy = tick;
        ddx = (abs(dx) / abs(dy)) * tick;
    }
    if (dx < 0.)
    {
        ddx = -ddx;
        kika = -1;
    }
    else if
        (dx > 0.) kika = 1;
    else kika = 0;
    if (dy < 0.)
    {
        ddy = -ddy;
        aba = -1;
    }
    else if (dy > 0.) aba = 1;
    else aba = 0;
    batasX = objek[0].x + dx;
    batasY = objek[0].y + dy;
    gerakX = objek[0].x + transX;
    gerakY = objek[0].y + transY;

    if (tick == 0.)
    {
        transX = dx;
        transY = dy;
    }
    else
    {
        if ((gerakX > batasX) && (gerakY > batasY) && (kika == -1) && (aba == -1)) // kiri-bawah
        {
            transX += ddx;
            transY += ddy;
        }
        else if ((gerakX > batasX) && (gerakY < batasY) && (kika == -1) && (aba == 1)) // kiri-atas
        {
            transX += ddx;
            transY += ddy;
        }
        else if ((gerakX < batasX) && (gerakY < batasY) && (kika == 1) && (aba == 1)) // kanan-atas
        {
            transX += ddx;
            transY += ddy;
        }
        else if ((gerakX < batasX) && (gerakY > batasY) && (kika == 1) && (aba == -1)) // kanan-bawah
        {
            transX += ddx;
            transY += ddy;
        }
        else if ((gerakX == batasX) && (gerakY > batasY) && (kika == 0) && (aba == -1)) // bawah
        {
            transX = 0.;
            transY += ddy;
        }
        else if ((gerakX == batasX) && (gerakY < batasY) && (kika == 0) && (aba == 1)) // atas
        {
            transX = 0.;
            transY += ddy;
        }
        else if ((gerakX > batasX) && (gerakY == batasY) && (kika == -1) && (aba == 0)) // kiri
        {
            transX += ddx;
            transY = 0.;
        }
        else if ((gerakX < batasX) && (gerakY == batasY) && (kika == 1) && (aba == 0)) // kanan
        {
            transX += ddx;
            transY = 0.;
        }
        else
        {
            transX = 0.;
            transY = 0.;
        }
    }
}

void userdraw()
{
//isinya pallet warna
Color_t abu_muda = {0.5,0.5,0.5};
Color_t abu_tua = {0.30000000000000004,0.30000000000000004,0.30000000000000004};
Color_t oranye_menyala = {1,0.1,0};
Color_t putih = {0.9,0.9,0.9};
Color_t biru_muda = {0.30000000000000004,0.6000000000000001,0.8};
Color_t putih_tulang = {0.9,0.9,0.8};
Color_t hitam = {0,0,0};
Color_t coklat_cerah = {0.8,0.5,0};
Color_t coklat_gelap = {0.7000000000000001,0.4,0};
Color_t coklat_gelap_bgt = {0.30000000000000004,0.30000000000000004,0};
Color_t api_cerah = {1,1,0.7000000000000001};
Color_t api_menyala = {1,0.8,0.2};
Color_t merah_menyala = {1,0,0};
Color_t background_COOKLAAT = {1,0.7,0};
Color_t warna_grid_kayu = {0.7,0.4,0};

Point2D_t  garis_1 [2] = {{0.,600.},{920.,600.}};
Point2D_t  garis_2 [2] = {{0.,480.},{920.,480.}};
Point2D_t  garis_3 [2] = {{0.,360.},{920.,360.}};
Point2D_t  garis_4 [2] = {{0.,240.},{920.,240.}};
Point2D_t  garis_5 [2] = {{0.,120.},{920.,120.}};
Point2D_t  garis_6 [2] = {{0.,0.},{0.,920.}};
Point2D_t  garis_7 [2] = {{120.,0.},{120.,720.}};
Point2D_t  garis_8 [2] = {{240.,0.},{240.,720.}};
Point2D_t  garis_9 [2] = {{360.,0.},{360.,720.}};
Point2D_t  garis_10 [2] = {{480.,0.},{480.,720.}};
Point2D_t  garis_11 [2] = {{600.,0.},{600.,720.}};
Point2D_t  garis_12 [2] = {{720.,0.},{720.,720.}};
Point2D_t  garis_13 [2] = {{840.,0.},{840.,720.}};
drawPolyline(garis_1,2,warna_grid_kayu,3);
drawPolyline(garis_2,2,warna_grid_kayu,3);
drawPolyline(garis_3,2,warna_grid_kayu,3);
drawPolyline(garis_4,2,warna_grid_kayu,3);
drawPolyline(garis_5,2,warna_grid_kayu,3);
drawPolyline(garis_6,2,warna_grid_kayu,3);
drawPolyline(garis_7,2,warna_grid_kayu,3);
drawPolyline(garis_8,2,warna_grid_kayu,3);
drawPolyline(garis_9,2,warna_grid_kayu,3);
drawPolyline(garis_10,2,warna_grid_kayu,3);
drawPolyline(garis_11,2,warna_grid_kayu,3);
drawPolyline(garis_12,2,warna_grid_kayu,3);
drawPolyline(garis_13,2,warna_grid_kayu,3);


// Objek pintu
Point2D_t  ktk_pintu [4] = {{40.,0.},{180.,0.},{180.,320.},{40.,320.}};
drawPolygon(ktk_pintu, 4, hitam, 10);
fillPolygon(ktk_pintu, 4, coklat_cerah);

Point2D_t  lngkrn_ggng_pintu [1] = {{150.,140.}};
Point2D_t lingkaran_penuh[360];
drawCircle(lngkrn_ggng_pintu[0], 10,360,1.0,lingkaran_penuh);
drawPolygon(lingkaran_penuh,360,hitam,2.0);
fillPolygon(lingkaran_penuh, 360,putih_tulang);



//Objek obor 1
Point2D_t  ktk_ggng_obor1 [4] = {{240.,220.},{260.,220.},{260.,280.},{240.,280.}};
drawPolygon(ktk_ggng_obor1,4,hitam,10);
fillPolygon(ktk_ggng_obor1,4,coklat_gelap_bgt);

Point2D_t  ktk_api1_obor1 [4] = {{240.,280.},{260.,280.},{260.,292.},{240.,292.}};
drawPolygon(ktk_api1_obor1,4,hitam,10);
fillPolygon(ktk_api1_obor1,4,api_cerah);

Point2D_t  ktk_api2_obor1 [4] = {{240.,292.},{260.,292.},{260.,300.},{240.,300.}};
drawPolygon(ktk_api2_obor1,4,hitam,10);
fillPolygon(ktk_api2_obor1,4,api_menyala);



//Objek obor 2
Point2D_t  ktk_ggng_obor2 [4] = {{300.,220.},{320.,220.},{320.,280.},{300.,280.}};
drawPolygon(ktk_ggng_obor2,4,hitam,10);
fillPolygon(ktk_ggng_obor2,4,coklat_gelap_bgt);

Point2D_t  ktk_api1_obor2 [4] = {{300.,280.},{320.,280.},{320.,292.},{300.,292.}};
drawPolygon(ktk_api1_obor2,4,hitam,10);
fillPolygon(ktk_api1_obor2,4,api_cerah);

Point2D_t  ktk_api2_obor2 [4] = {{300.,292.},{320.,292.},{320.,300.},{300.,300.}};
drawPolygon(ktk_api2_obor2,4,hitam,10);
fillPolygon(ktk_api2_obor2,4,api_menyala);



//Objek Crafting Table
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

Point2D_t  ktk_ggng_gergaji [4] = {{310.,60.},{330.,60.},{330.,80.},{310.,80.}};
drawPolygon(ktk_ggng_gergaji,4,hitam,5);
fillPolygon(ktk_ggng_gergaji,4,coklat_gelap_bgt);

Point2D_t  ktk_lbng_gergaji [4] = {{316.,64.},{328.,64.},{328.,76.},{316.,76.}};
drawPolygon(ktk_lbng_gergaji,4,hitam,2);
fillPolygon(ktk_lbng_gergaji,4,coklat_cerah);

Point2D_t  sgt_gergaji [3] = {{310.,60.},{330.,60.},{330.,20.}};
drawPolygon(sgt_gergaji,3,hitam,5);
fillPolygon(sgt_gergaji,3,putih_tulang);



//Objek Chest 1
Point2D_t  ktk_bwh_chest [4] = {{500.,0.},{660.,0.},{660.,40.},{500.,40.}};
drawPolygon(ktk_bwh_chest,4,hitam,10);
fillPolygon(ktk_bwh_chest,4,coklat_cerah);

Point2D_t  ktk_atas_chest [4] = {{500.,40.},{660.,40.},{660.,60.},{500.,60.}};
drawPolygon(ktk_atas_chest,4,hitam,10);
fillPolygon(ktk_atas_chest,4,coklat_gelap);

Point2D_t  ktk_kunci_chest [4] = {{570.,22.},{586.,22.},{586.,60.},{570.,60.}};
drawPolygon(ktk_kunci_chest,4,hitam,10);
fillPolygon(ktk_kunci_chest,4,putih_tulang);



//Objek Chest 2
Point2D_t  ktk_bwh_chest2 [] = {{500.,80.},{660.,80.},{660.,120.},{500.,120.}};
drawPolygon(ktk_bwh_chest2,4,hitam,10);
fillPolygon(ktk_bwh_chest2,4,coklat_cerah);

Point2D_t  ktk_atas_chest2 [] = {{500.,120.},{660.,120.},{660.,140.},{500.,140.}};
drawPolygon(ktk_atas_chest2,4,hitam,10);
fillPolygon(ktk_atas_chest2,4,coklat_gelap);

Point2D_t  ktk_kunci_chest2 [] = {{570.,102.},{586.,102.},{586.,140.},{570.,140.}};
drawPolygon(ktk_kunci_chest2,4,hitam,10);
fillPolygon(ktk_kunci_chest2,4,putih_tulang);



//Objek Jendela
Point2D_t  ktk_jendela [4] = {{660.,280.},{780.,280.},{780.,400.},{660.,400.}};
drawPolygon(ktk_jendela,4,hitam,10);
fillPolygon(ktk_jendela,4,putih_tulang);

Point2D_t  gris_jendela1 [2] = {{700.,380.},{680.,360.}};
Point2D_t  gris_jendela2 [2] = {{760.,380.},{740.,360.}};
Point2D_t  gris_jendela3 [2] = {{700.,340.},{680.,320.}};
Point2D_t  gris_jendela4 [2] = {{760.,340.},{740.,320.}};
drawPolyline(gris_jendela1,2,biru_muda,5);
drawPolyline(gris_jendela2,2,biru_muda,5);
drawPolyline(gris_jendela3,2,biru_muda,5);
drawPolyline(gris_jendela4,2,biru_muda,5);



//Objek Kasur
Point2D_t  ktk_kki_kasur2 [4] = {{688.,0.},{704.,0.},{704.,100.},{688.,100.}};
drawPolygon(ktk_kki_kasur2,4,hitam,10);
fillPolygon(ktk_kki_kasur2,4,coklat_gelap);

Point2D_t  ktk_kki_kasur1 [4] = {{680.,0.},{692.,0.},{692.,100.},{680.,100.}};
drawPolygon(ktk_kki_kasur1,4,hitam,10);
fillPolygon(ktk_kki_kasur1,4,coklat_cerah);

Point2D_t  ktk_kki_kasur3 [] = {{900.,0.},{912.,0.},{912.,100.},{900.,100.}};
drawPolygon(ktk_kki_kasur3,4,hitam,10);
fillPolygon(ktk_kki_kasur3,4,coklat_gelap);

Point2D_t  ktk_kki_kasur4 [] = {{908.,0.},{916.,0.},{916.,100.},{908.,100.}};
drawPolygon(ktk_kki_kasur4,4,hitam,10);
fillPolygon(ktk_kki_kasur4,4,coklat_cerah);

Point2D_t  ktk_kasur_mrh [4] = {{680.,100.},{840.,100.},{840.,130.},{680.,130.}};
drawPolygon(ktk_kasur_mrh,4,hitam,10);
fillPolygon(ktk_kasur_mrh,4,merah_menyala);

Point2D_t  ktk_bntl_putih [4] = {{860.,130.},{920.,130.},{920.,160.},{860.,160.}};
drawPolygon(ktk_bntl_putih,4,hitam,10);
fillPolygon(ktk_bntl_putih,4,putih);

Point2D_t  ktk_kasur_putih [4] = {{840.,100.},{920.,100.},{920.,130.},{840.,130.}};
drawPolygon(ktk_kasur_putih,4,hitam,10);
fillPolygon(ktk_kasur_putih,4,putih);



//Object Furnace
Point2D_t  ktk_ats_furnace [4] = {{360.,50.},{460.,50.},{460.,100.},{360.,100.}};
drawPolygon(ktk_ats_furnace,4,hitam,10);
fillPolygon(ktk_ats_furnace,4,abu_muda);

Point2D_t  ktk_bwh_furnace [4] = {{360.,0.},{460.,0.},{460.,50.},{360.,50.}};
drawPolygon(ktk_bwh_furnace,4,hitam,10);
fillPolygon(ktk_bwh_furnace,4,abu_tua);

Point2D_t  stglkr1_furnace [1] = {{410.,52.}};
Point2D_t st_lkr[180];
drawCircle(stglkr1_furnace[0],20,180,5,st_lkr);
drawPolygon(st_lkr,180,hitam,5);
fillPolygon(st_lkr,180,hitam);

Point2D_t  stglkr2_furnace [1] = {{410.,2.}};
drawCircle(stglkr2_furnace[0],20,180,5,st_lkr);
drawPolygon(st_lkr,180,hitam,5);
fillPolygon(st_lkr,180,merah_menyala);
}

//fungsi untuk menampilkan
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    userdraw();
    glutSwapBuffers();
}

//Fungsi Utama
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(920, 720);
    glutCreateWindow("Lingkaran Merah & Kotak Biru Hitam Outline");
    glClearColor(1.0, 0.7, 0.0, 0.0);
    gluOrtho2D(0.0, 920.0, 0.0, 720.0); 
    glutDisplayFunc(display);
    glutIdleFunc(display); 
    glutMainLoop();
    return 0;
}