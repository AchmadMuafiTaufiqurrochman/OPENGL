#include<stdlib.h>
#include <GL/glut.h>
#include <math.h>
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

void gradatePolygon(Point2D_t pnt[], int n,
    Color_t warna1,
    Color_t warna2, int b)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        if (i <= b) setColor(warna1);
        else setColor(warna2);
        glVertex2f(pnt[i].x, pnt[i].y);
    }
    glEnd();
}

void drawPolyline(Point2D_t pnt[], int n,
    Color_t warna, float size)
{
    setColor(warna);
    glLineWidth(size);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < n; i++) {
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
    for (int i = 0; i < n; i++) {
        glVertex2f(pnt[i].x, pnt[i].y);
    }
    glEnd();
}

void fillPolygon(Point2D_t pnt[], int n,
    Color_t warna)
{
    setColor(warna);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(pnt[i].x, pnt[i].y);
    }
    glEnd();
}

void drawCircle(Point2D_t pusat, float jari2, int sudut, float size, Point2D_t pntCircle[])
{
    int sdt, i;
    sdt = 0;
    for (i = 0; i <= abs(sudut); i++)
    {
        float srad = sdt * 3.14 / 180;
        pntCircle[i].x = (float)((jari2 * cos(srad)) + pusat.x);
        pntCircle[i].y = (float)((jari2 * sin(srad)) + pusat.y);
        if (sudut > 0) sdt++;
        else sdt--;
    }
}

void drawEllipse(Point2D_t pusat, float jariH, float jariV, int sudut, float size,
    Point2D_t pntEllipse[])
{
    int sdt, i;
    sdt = 0;
    for (i = 0; i <= abs(sudut); i++)
    {
        float srad = sdt * 3.14 / 180;
        pntEllipse[i].x = (float)((jariH * cos(srad)) + pusat.x);
        pntEllipse[i].y = (float)((jariV * sin(srad)) + pusat.y);
        if (sudut > 0) sdt++;
        else sdt--;
    }
}

void drawPolar(Point2D_t pusat, float jari2, float daun, int sudut, float size, Point2D_t pntPolar[])
{
    int sdt, i;
    float r;
    sdt = 0;
    for (i = 0; i <= abs(sudut); i++)
    {
        float srad = sdt * 3.14 / 180;
        r = sin(daun * srad);
        pntPolar[i].x = (float)((r * cos(srad) * jari2) + pusat.x);
        pntPolar[i].y = (float)((r * sin(srad) * jari2) + pusat.y);
        if (sudut > 0) sdt++;
        else sdt--;
    }
}

void drawSharpStar(Point2D_t pusat, float radiusLuar, float radiusDalam, int jumlahSudut, Point2D_t pntStar[])
{
    int totalTitik = jumlahSudut * 2;
    float sudutStep = 360.0f / totalTitik;
    float sudutSekarang = 90.0f;

    for (int i = 0; i < totalTitik; i++) {
        float rad = sudutSekarang * 3.14159f / 180.0f;
        float r = (i % 2 == 0) ? radiusLuar : radiusDalam;

        pntStar[i].x = pusat.x + r * cos(rad);
        pntStar[i].y = pusat.y + r * sin(rad);

        sudutSekarang -= sudutStep;
    }
}

/*-----------------------------------------------------------------
Fungsi Translasi ini bisa digunakan untuk Polyline, Polygon,
Circle, Ellipse, dan Polar.
-------------------------------------------------------------------
t_objek[] - objek hasil translasi
 objek[] - objek yang akan ditranslasi
 n - banyaknya titik yang akan ditranslasi
 dx - jarak translasi searah sumbu x (- kekiri, + ke kanan)
 dy - jarak translasi searah sumbu y (- ke bawah, + ke atas )
 tick - kecepatan animasi (tanpa animasi nilainya 0.)
-------------------------------------------------------------------*/
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
    /*--- Warna yg di Pakai ---*/
    Color_t Outline = { 0,0,0 };
    Color_t WarnaAwan = { 1,1,1 };
    Color_t WarnaDinding = { 0.9,0.8,0.4 };
    Color_t WarnaPintu = { 0,0.4,0.8 };
    Color_t WarnaJendela = { 0.3,0.6,0.9 };
    Color_t WarnaTanah = { 0.6,0.8,0.3 };
    Color_t WarnaInterior1 = { 0.3,0.3,0.3 };
    Color_t WarnaInterior2 = { 1,0.9,0.4 };
    Color_t WarnaInterior3 = { 1,0.8,0.6 };
    Color_t WarnaTangga = { 0.7,0.7,0.7 };
    Color_t WarnaBangunan = { 1,0.8,0.6 };
    Color_t WarnaMatahari = { 1,1,0 };
    Color_t WarnaAtap = { 0.7,0.2,0 };
    Color_t WarnaDaun = { 0.5,0.7,0.2 };
    Color_t WarnaMobil = { 1,0.7,0.1 };
    Color_t WarnaRoda1 = { 0.3,0.4,0.4 };
    Color_t WarnaRoda2 = { 0.5,0.7,0.7 };
    Color_t WarnaKursi = { 0.6,0.3,0 };
    Color_t WarnaKaca = { 0.6,0.7,0.9 };
    Color_t WarnaJalan = { 0.1,0.1,0.1 };
    Color_t WarnaBingkai = { 0.3,0.3,0.3 };
    Color_t WarnaBulan = { 1,1,0.7 };
    Color_t WarnaLampu = { 1,1,0.7 };
    Color_t WarnaMalam = { 0.1,0.1,0.2 };
    Color_t WarnaPagi = { 0.5,0.8,1 };


    /*--- Langit ---*/
    static float time = 0.0f; // Variabel untuk mengatur waktu (0-60 siklus)
    Point2D_t Langit[4] = { {0.,100.},{920.,100.},{920.,720.},{0.,720.} };

    // Increment time untuk animasi
    time += 0.01f;
    if (time > 60.0f) time = 0.0f; // Reset setelah 60 detik

    if (time < 30.0f) {
        // Siang hari (0-30 detik)
        drawPolygon(Langit, 4, WarnaPagi, 0);
        fillPolygon(Langit, 4, WarnaPagi);
    }
    else {
        // Malam hari (30-60 detik)
        drawPolygon(Langit, 4, WarnaMalam, 0);
        fillPolygon(Langit, 4, WarnaMalam);
    }

    /*--- Matahari/Bulan ---*/
    Point2D_t Matahari[361];
    Point2D_t Bulan[361];
    Point2D_t pusatMatahari = { 828,628 };
    Point2D_t pusatBulan = { 828,628 };
    
    if (time < 30.0f) {
        // Siang hari - tampilkan matahari
        drawCircle(pusatMatahari, 40, 360, 2, Matahari);
        fillPolygon(Matahari, 361, WarnaMatahari);

    }
    else {
        // Malam hari - tampilkan bulan
        drawCircle(pusatBulan, 40, 360, 2, Bulan);
        fillPolygon(Bulan, 361, WarnaBulan);
    }

    /*--- Awan Kiri ---*/
    Point2D_t AwanKiri1[361];
    Point2D_t AwanKiri2[361];
    Point2D_t AwanKiri3[361];
    drawCircle({ 60.,640. }, 18, 360, 2, AwanKiri1);
    drawCircle({ 92.,652. }, 25, 360, 2, AwanKiri2);
    drawCircle({ 120.,640. }, 18, 360, 2, AwanKiri3);
    drawPolygon(AwanKiri1, 361, WarnaAwan, 0);
    drawPolygon(AwanKiri2, 361, WarnaAwan, 0);
    drawPolygon(AwanKiri3, 361, WarnaAwan, 0);
    fillPolygon(AwanKiri1, 361, WarnaAwan);
    fillPolygon(AwanKiri2, 361, WarnaAwan);
    fillPolygon(AwanKiri3, 361, WarnaAwan);


    /*--- Awan Kanan ---*/
    Point2D_t  Awankanan1[1] = { {540.,640.} };
    Point2D_t  Awankanan2[1] = { {572.,652.} };
    Point2D_t  Awankanan3[1] = { {600.,640.} };
    Point2D_t AwanKanan1[361];
    Point2D_t AwanKanan2[361];
    Point2D_t AwanKanan3[361];
    drawCircle({ 540.,640. }, 18, 360, 2, AwanKanan1);
    drawCircle({ 572.,652. }, 25, 360, 2, AwanKanan2);
    drawCircle({ 600.,640. }, 18, 360, 2, AwanKanan3);
    drawPolygon(AwanKanan1, 361, WarnaAwan, 0);
    drawPolygon(AwanKanan2, 361, WarnaAwan, 0);
    drawPolygon(AwanKanan3, 361, WarnaAwan, 0);
    fillPolygon(AwanKanan1, 361, WarnaAwan);
    fillPolygon(AwanKanan2, 361, WarnaAwan);
    fillPolygon(AwanKanan3, 361, WarnaAwan);

    /*--- Bangunan Urut 3 ---*/
    Point2D_t  BangunanKiri2[4] = { {20.,100.},{160.,100.},{160.,400.},{20.,400.} };
    Point2D_t  BangunanKanan2[4] = { {760.,100.},{900.,100.},{900.,400.},{760.,400.} };
    drawPolygon(BangunanKiri2, 4, Outline, 2);
    drawPolygon(BangunanKanan2, 4, Outline, 2);
    fillPolygon(BangunanKiri2, 4, WarnaBangunan);
    fillPolygon(BangunanKanan2, 4, WarnaBangunan);

    /*--- Bangunan Urut 2 ---*/
    Point2D_t  BangunanKiri1[4] = { {160.,100.},{320.,100.},{320.,540.},{160.,540.} };
    Point2D_t  BangunanKanan1[4] = { {600.,100.},{760.,100.},{760.,540.},{600.,540.} };
    drawPolygon(BangunanKanan1, 4, Outline, 2);
    drawPolygon(BangunanKiri1, 4, Outline, 2);
    fillPolygon(BangunanKanan1, 4, WarnaBangunan);
    fillPolygon(BangunanKiri1, 4, WarnaBangunan);

    /*--- Bangunan Tengah ---*/
    Point2D_t  BangunanTengah1[4] = { {320.,100.},{600.,100.},{600.,620.},{320.,620.} };
    Point2D_t  BangunanAtap1[4] = { {380.,620.},{540.,620.},{536.,660.},{380.,660.} };
    Point2D_t  BangunanAtap2[4] = { {420.,620.},{500.,620.},{500.,660.},{420.,660.} };
    drawPolygon(BangunanAtap1, 4, WarnaBangunan, 2);
    drawPolygon(BangunanAtap2, 4, WarnaBangunan, 2);
    drawPolygon(BangunanTengah1, 4, Outline, 2);
    fillPolygon(BangunanTengah1, 4, WarnaBangunan);
    fillPolygon(BangunanAtap1, 4, WarnaBangunan);
    fillPolygon(BangunanAtap2, 4, WarnaBangunan);

    /*--- Atap Kiri & Kanan ---*/
    Point2D_t  AtapKanan1[4] = { {760.,400.},{920.,400.},{920.,420.},{760.,420.} };
    Point2D_t  AtapKanan2[5] = { {600.,480.},{780.,480.},{800.,492.},{800.,500.},{600.,500.} };
    Point2D_t  AtapKanan3[4] = { {600.,540.},{780.,540.},{780.,560.},{600.,560.} };
    Point2D_t  AtapKiri1[4] = { {0.,400.},{160.,400.},{160.,420.},{0.,420.} };
    Point2D_t  AtapKiri2[4] = { {140.,540.},{320.,540.},{320.,560.},{140.,560.} };
    Point2D_t  AtapKiri4[5] = { {140.,480.},{320.,480.},{320.,500.},{120.,500.},{120.,492.} };
    drawPolygon(AtapKanan1, 4, Outline, 2);
    drawPolygon(AtapKanan2, 5, Outline, 2);
    drawPolygon(AtapKanan3, 4, Outline, 2);
    drawPolygon(AtapKiri1, 4, Outline, 2);
    drawPolygon(AtapKiri2, 4, Outline, 2);
    drawPolygon(AtapKiri4, 5, Outline, 2);
    fillPolygon(AtapKanan1, 4, WarnaAtap);
    fillPolygon(AtapKanan2, 5, WarnaAtap);
    fillPolygon(AtapKanan3, 4, WarnaAtap);
    fillPolygon(AtapKiri1, 4, WarnaAtap);
    fillPolygon(AtapKiri2, 4, WarnaAtap);
    fillPolygon(AtapKiri4, 5, WarnaAtap);

    /*--- Atap Tengah ---*/
    Point2D_t  AtapTengah1[4] = { {300.,620.},{380.,620.},{380.,640.},{300.,640.} };
    Point2D_t  AtapTengah2[4] = { {340.,640.},{420.,640.},{420.,660.},{340.,660.} };
    Point2D_t  AtapTengah3[4] = { {400.,660.},{520.,660.},{520.,680.},{400.,680.} };
    Point2D_t  AtapTengah4[4] = { {500.,640.},{580.,640.},{580.,660.},{500.,660.} };
    Point2D_t  AtapTengah5[4] = { {540.,620.},{620.,620.},{620.,640.},{540.,640.} };
    Point2D_t  AtapTengah6[4] = { {320.,480.},{600.,480.},{600.,500.},{320.,500.} };
    Point2D_t  AtapTengah7[4] = { {320.,480.},{340.,480.},{340.,620.},{320.,620.} };
    Point2D_t  AtapTengah8[4] = { {580.,480.},{600.,480.},{600.,620.},{580.,620.} };
    drawPolygon(AtapTengah1, 4, Outline, 2);
    drawPolygon(AtapTengah2, 4, Outline, 2);
    drawPolygon(AtapTengah3, 4, Outline, 2);
    drawPolygon(AtapTengah4, 4, Outline, 2);
    drawPolygon(AtapTengah5, 4, Outline, 2);
    drawPolygon(AtapTengah6, 4, Outline, 2);
    drawPolygon(AtapTengah7, 4, Outline, 2);
    drawPolygon(AtapTengah8, 4, Outline, 2);
    fillPolygon(AtapTengah1, 4, WarnaAtap);
    fillPolygon(AtapTengah2, 4, WarnaAtap);
    fillPolygon(AtapTengah3, 4, WarnaAtap);
    fillPolygon(AtapTengah4, 4, WarnaAtap);
    fillPolygon(AtapTengah5, 4, WarnaAtap);
    fillPolygon(AtapTengah6, 4, WarnaAtap);
    fillPolygon(AtapTengah7, 4, WarnaAtap);
    fillPolygon(AtapTengah8, 4, WarnaAtap);

    /*--- Tembok ---*/
    Point2D_t  DindingKiri1[4] = { {160.,320.},{320.,320.},{320.,340.},{160.,340.} };
    Point2D_t  DindingKiri2[4] = { {20.,180.},{320.,180.},{320.,200.},{20.,200.} };
    Point2D_t  DindingKanan1[4] = { {600.,320.},{760.,320.},{760.,340.},{600.,340.} };
    Point2D_t  DindingKanan2[4] = { {600.,180.},{900.,180.},{900.,200.},{600.,200.} };
    Point2D_t  Banner[4] = { {320.,340.},{600.,340.},{600.,400.},{320.,400.} };
    drawPolygon(DindingKanan1, 4, Outline, 2);
    drawPolygon(DindingKanan2, 4, Outline, 2);
    drawPolygon(DindingKiri1, 4, Outline, 2);
    drawPolygon(DindingKiri2, 4, Outline, 2);
    drawPolygon(Banner, 4, Outline, 2);
    fillPolygon(DindingKiri1, 4, WarnaDinding);
    fillPolygon(DindingKiri2, 4, WarnaDinding);
    fillPolygon(DindingKanan1, 4, WarnaDinding);
    fillPolygon(DindingKanan2, 4, WarnaDinding);
    fillPolygon(Banner, 4, WarnaDinding);

    /*--- Pintu---*/
    Point2D_t  Ventilasi[4] = { {380.,300.},{540.,300.},{540.,320.},{380.,320.} };
    drawPolygon(Ventilasi, 4, Outline, 2);
    fillPolygon(Ventilasi, 4, WarnaInterior2);
    Point2D_t  Pintu[4] = { {380.,160.},{540.,160.},{540.,300.},{380.,300.} };
    drawPolygon(Pintu, 4, Outline, 2);
    fillPolygon(Pintu, 4, WarnaPintu);
    Point2D_t  PintuJendela1[4] = { {400.,240.},{432.,240.},{432.,280.},{400.,280.} };
    Point2D_t  PintuJendela2[4] = { {488.,240.},{520.,240.},{520.,280.},{488.,280.} };
    drawPolygon(PintuJendela1, 4, Outline, 2);
    drawPolygon(PintuJendela2, 4, Outline, 2);
    fillPolygon(PintuJendela1, 4, WarnaJendela);
    fillPolygon(PintuJendela2, 4, WarnaJendela);

    /*--- Gagang Pintu---*/
    Point2D_t  GarisPintu[2] = { {460.,160.},{460.,300.} };
    drawPolyline(GarisPintu, 2, Outline, 2);
    Point2D_t  GagangPintu1[361];
    drawCircle({ 448.,228. }, 5, 360, 2, GagangPintu1);
    drawPolygon(GagangPintu1, 361, Outline, 2);
    fillPolygon(GagangPintu1, 361, WarnaAwan);
    Point2D_t  GagangPintu2[361];
    drawCircle({ 472.,228. }, 5, 360, 2, GagangPintu2);
    drawPolygon(GagangPintu2, 361, Outline, 2);
    fillPolygon(GagangPintu2, 361, WarnaAwan);

    /*--- Pilar ---*/
    Point2D_t  PilarKiri1[4] = { {328.,320.},{372.,320.},{372.,340.},{328.,340.} };
    Point2D_t  PilarKiri2[4] = { {340.,180.},{360.,180.},{360.,320.},{340.,320.} };
    Point2D_t  SanggahKiri1[4] = { {320.,100.},{380.,100.},{380.,180.},{320.,180.} };
    Point2D_t  SanggahKiri2[4] = { {320.,120.},{380.,120.},{380.,168.},{320.,168.} };
    drawPolygon(PilarKiri1, 4, Outline, 2);
    drawPolygon(PilarKiri2, 4, Outline, 2);
    drawPolygon(SanggahKiri1, 4, Outline, 2);
    drawPolygon(SanggahKiri2, 4, Outline, 2);
    fillPolygon(PilarKiri1, 4, WarnaInterior2);
    fillPolygon(PilarKiri2, 4, WarnaInterior2);
    fillPolygon(SanggahKiri1, 4, WarnaInterior1);
    fillPolygon(SanggahKiri2, 4, WarnaInterior2);

    Point2D_t  PilarKanan1[4] = { {548.,320.},{592.,320.},{592.,340.},{548.,340.} };
    Point2D_t  PilarKanan2[4] = { {560.,180.},{580.,180.},{580.,340.},{560.,340.} };
    Point2D_t  SanggahKanan1[4] = { {540.,100.},{600.,100.},{600.,180.},{540.,180.} };
    Point2D_t  SanggahKanan2[4] = { {540.,120.},{600.,120.},{600.,168.},{540.,168.} };
    drawPolygon(PilarKanan1, 4, Outline, 2);
    drawPolygon(PilarKanan2, 4, Outline, 2);
    drawPolygon(SanggahKanan1, 4, Outline, 2);
    drawPolygon(SanggahKanan2, 4, Outline, 2);
    fillPolygon(PilarKanan1, 4, WarnaInterior2);
    fillPolygon(PilarKanan2, 4, WarnaInterior2);
    fillPolygon(SanggahKanan1, 4, WarnaInterior1);
    fillPolygon(SanggahKanan2, 4, WarnaInterior2);

    /*--- Interior Jendela ---*/
    Point2D_t  BingkaiJendela1[4] = { {40.,220.},{140.,220.},{140.,380.},{40.,380.} };
    Point2D_t  BingkaiJendela2[4] = { {780.,220.},{880.,220.},{880.,380.},{780.,380.} };
    drawPolygon(BingkaiJendela1, 4, Outline, 2);
    drawPolygon(BingkaiJendela2, 4, Outline, 2);
    fillPolygon(BingkaiJendela1, 4, WarnaBingkai);
    fillPolygon(BingkaiJendela2, 4, WarnaBingkai);


    /*--- Jendela ---*/
    Point2D_t  JendelaKiri1[4] = { {60.,240.},{120.,240.},{120.,360.},{60.,360.} };
    Point2D_t  JendelaKiri2[4] = { {200.,360.},{280.,360.},{280.,440.},{200.,440.} };
    Point2D_t  JendelaKiri3[4] = { {212.,220.},{268.,220.},{268.,300.},{212.,300.} };
    Point2D_t  JendelaKanan1[4] = { {800.,240.},{860.,240.},{860.,360.},{800.,360.} };
    Point2D_t  JendelaKanan2[4] = { {640.,360.},{720.,360.},{720.,440.},{640.,440.} };
    Point2D_t  JendelaKanan3[4] = { {652.,220.},{708.,220.},{708.,300.},{652.,300.} };
    drawPolygon(JendelaKiri1, 4, Outline, 2);
    drawPolygon(JendelaKiri2, 4, Outline, 2);
    drawPolygon(JendelaKiri3, 4, Outline, 2);
    drawPolygon(JendelaKanan1, 4, Outline, 2);
    drawPolygon(JendelaKanan2, 4, Outline, 2);
    drawPolygon(JendelaKanan3, 4, Outline, 2);
    fillPolygon(JendelaKiri2, 4, WarnaAtap);
    fillPolygon(JendelaKanan2, 4, WarnaAtap);

    // Animasi lampu berdasarkan waktu
    if (time < 30.) { // Malam hari - lampu menyala
        fillPolygon(JendelaKiri1, 4, WarnaJendela);
        fillPolygon(JendelaKiri3, 4, WarnaJendela);
        fillPolygon(JendelaKanan1, 4, WarnaJendela);
        fillPolygon(JendelaKanan3, 4, WarnaJendela);
    }
    else { // Pagi hari - warna asli
        fillPolygon(JendelaKiri1, 4, WarnaLampu);
        fillPolygon(JendelaKiri3, 4, WarnaLampu);
        fillPolygon(JendelaKanan1, 4, WarnaLampu);
        fillPolygon(JendelaKanan3, 4, WarnaLampu);
    }

    /*--- Garis Jendela ---*/
    Point2D_t  GarisJendela1[2] = { {240.,360.},{240.,440.} };
    Point2D_t  GarisJendela2[2] = { {680.,360.},{680.,440.} };
    Point2D_t  GarisJendela3[2] = { {240.,220.},{240.,300.} };
    Point2D_t  GarisJendela4[2] = { {212.,260.},{268.,260.} };
    Point2D_t  GarisJendela5[2] = { {680.,220.},{680.,300.} };
    Point2D_t  GarisJendela6[2] = { {652.,260.},{708.,260.} };
    drawPolyline(GarisJendela1, 2, Outline, 2);
    drawPolyline(GarisJendela2, 2, Outline, 2);
    drawPolyline(GarisJendela3, 2, Outline, 2);
    drawPolyline(GarisJendela4, 2, Outline, 2);
    drawPolyline(GarisJendela5, 2, Outline, 2);
    drawPolyline(GarisJendela6, 2, Outline, 2);

    /*--- Tangga ---*/
    Point2D_t  Tangga1[4] = { {380.,140.},{540.,140.},{540.,160.},{380.,160.} };
    drawPolygon(Tangga1, 4, Outline, 2);
    fillPolygon(Tangga1, 4, WarnaTangga);
    Point2D_t  Tangga2[4] = { {380.,120.},{540.,120.},{540.,140.},{380.,140.} };
    drawPolygon(Tangga2, 4, Outline, 2);
    fillPolygon(Tangga2, 4, WarnaTangga);
    Point2D_t  Tangga3[4] = { {380.,100.},{540.,100.},{540.,120.},{380.,120.} };
    drawPolygon(Tangga3, 4, Outline, 2);
    fillPolygon(Tangga3, 4, WarnaTangga);

    /*--- Tanah ---*/
    Point2D_t  Tanah[4] = { {0.,0.},{920.,0.},{920.,100.},{0.,100.} };
    Point2D_t  AlasKiri[4] = { {20.,100.},{320.,100.},{320.,180.},{20.,180.} };
    Point2D_t  AlasKanan[4] = { {600.,100.},{900.,100.},{900.,180.},{600.,180.} };
    drawPolygon(Tanah, 4, Outline, 2);
    drawPolygon(AlasKiri, 4, Outline, 2);
    drawPolygon(AlasKanan, 4, Outline, 2);
    fillPolygon(AlasKiri, 4, WarnaAtap);
    fillPolygon(AlasKanan, 4, WarnaAtap);
    fillPolygon(Tanah, 4, WarnaTanah);

    /*--- Jam ---*/
    Point2D_t  Jam[361];
    drawCircle({ 460.,580. }, 50, 360, 2, Jam);
    drawPolygon(Jam, 361, Outline, 10);
    fillPolygon(Jam, 361, WarnaAwan);
    Point2D_t  JarumJam[3] = { {440.,560.},{460.,580.},{460.,620.} };
    drawPolyline(JarumJam, 3, Outline, 4);
    Point2D_t  TitikJarum[361];
    drawCircle({ 460.,580. }, 4, 360, 2, TitikJarum);
    fillPolygon(TitikJarum, 361, Outline);

    /*--- Kursi ---*/
    Point2D_t  GarisKursi1[2] = { {240.,100.},{240.,140.} };
    Point2D_t  GarisKursi2[2] = { {300.,100.},{300.,140.} };
    Point2D_t  GarisKursi3[2] = { {228.,112.},{312.,112.} };
    Point2D_t  GarisKursi4[2] = { {820.,100.},{820.,140.} };
    Point2D_t  GarisKursi5[2] = { {880.,100.},{880.,140.} };
    Point2D_t  GarisKursi6[2] = { {812.,112.},{888.,112.} };
    drawPolyline(GarisKursi1, 2, Outline, 2);
    drawPolyline(GarisKursi2, 2, Outline, 2);
    drawPolyline(GarisKursi3, 2, Outline, 2);
    drawPolyline(GarisKursi4, 2, Outline, 2);
    drawPolyline(GarisKursi5, 2, Outline, 2);
    drawPolyline(GarisKursi6, 2, Outline, 2);
    Point2D_t  KursiKanan[4] = { {816.,124.},{884.,124.},{884.,136.},{816.,136.} };
    Point2D_t  KursiKiri[4] = { {236.,124.},{304.,124.},{304.,136.},{236.,136.} };
    drawPolygon(KursiKanan, 4, Outline, 2);
    drawPolygon(KursiKiri, 4, Outline, 2);
    fillPolygon(KursiKanan, 4, WarnaKursi);
    fillPolygon(KursiKiri, 4, WarnaKursi);

    /*--- Taman ---*/
    Point2D_t Taman1[361];
    drawCircle({ 712.,108. }, 15, 360, 2, Taman1);
    drawPolygon(Taman1, 361, WarnaDaun, 0);
    fillPolygon(Taman1, 361, WarnaDaun);

    Point2D_t Taman2[361];
    drawCircle({ 728.,108. }, 15, 360, 2, Taman2);
    drawPolygon(Taman2, 361, WarnaDaun, 0);
    fillPolygon(Taman2, 361, WarnaDaun);

    Point2D_t Taman3[361];
    drawCircle({ 744.,108. }, 15, 360, 2, Taman3);
    drawPolygon(Taman3, 361, WarnaDaun, 0);
    fillPolygon(Taman3, 361, WarnaDaun);

    Point2D_t Taman4[361];
    drawCircle({ 728.,132. }, 15, 360, 2, Taman4);
    drawPolygon(Taman4, 361, WarnaDaun, 0);
    fillPolygon(Taman4, 361, WarnaDaun);

     /*--- Jalan ---*/
    Point2D_t  Jalan[4] = { {352.,0.},{568.,0.},{540.,100.},{380.,100.} };
    drawPolygon(Jalan, 4, Outline, 2);
    fillPolygon(Jalan, 4, WarnaJalan);


    // Mobil 
    static Point2D_t  MobilStatic[6] = { {20.,100.},{220.,100.},{220.,140.},{188.,140.},{188.,200.},{20.,200.} };
    static Point2D_t  JendelaMobil1Static[4] = { {40.,140.},{120.,140.},{120.,180.},{40.,180.} };
    static Point2D_t  JendelaMobil2Static[4] = { {140.,120.},{168.,120.},{168.,180.},{140.,180.} };
    static Point2D_t  RodaKiriStatic = { 56.,100. };
    static Point2D_t  RodaKananStatic = { 188.,100. };

    // Titik mobil untuk animasi
    Point2D_t  Mobil[6];
    Point2D_t  JendelaMobil1[4];
    Point2D_t  JendelaMobil2[4];
    Point2D_t  RodaKiriPos[1];
    Point2D_t  RodaKananPos[1];

    // Animasi mobil dengan berhenti sejenak di depan pintu
    float carDx = 0.0f;
    const float stopPosition = 280.0f; 
    const float moveTime = 20.0f;      
    const float stopTime = 10.0f;       

    if (time < 30.0f) {
            if (time < moveTime) {
            float moveProgress = time / moveTime; 
            carDx = 0.0f + (moveProgress * (stopPosition - 0.0f)); 
        }
        else {
            carDx = stopPosition; 
        }
    }
    else {
        // Waktu malam (30-60 detik)
        float nightTime = time - 30.0f;
        float nightProgress = nightTime / 30.0f; 

        // Mobil mulai dari posisi berhenti dan bergerak ke luar layar kanan
        carDx = stopPosition + (nightProgress * (920.0f + 220.0f - stopPosition)); 
    }

    // Terapkan translasi ke badan mobil
    Translasi(Mobil, MobilStatic, 6, carDx, 0.0f, 0.0f);
    Translasi(JendelaMobil1, JendelaMobil1Static, 4, carDx, 0.0f, 0.0f);
    Translasi(JendelaMobil2, JendelaMobil2Static, 4, carDx, 0.0f, 0.0f);

    // Terapkan translasi ke posisi roda
    RodaKiriPos[0].x = RodaKiriStatic.x + carDx;
    RodaKiriPos[0].y = RodaKiriStatic.y;
    RodaKananPos[0].x = RodaKananStatic.x + carDx;
    RodaKananPos[0].y = RodaKananStatic.y;

    if (carDx > -250.0f && carDx < 970.0f) {

        /*--- Body & Jendela Mobil ---*/
        drawPolygon(Mobil, 6, Outline, 2);
        fillPolygon(Mobil, 6, WarnaMobil);
        drawPolygon(JendelaMobil1, 4, Outline, 2);
        drawPolygon(JendelaMobil2, 4, Outline, 2);
        fillPolygon(JendelaMobil1, 4, WarnaKaca);
        fillPolygon(JendelaMobil2, 4, WarnaKaca);

        /*--- Roda ---*/
        Point2D_t  RodaKiri1[361];
        drawCircle(RodaKiriPos[0], 15, 360, 2, RodaKiri1);
        drawPolygon(RodaKiri1, 361, Outline, 3);
        fillPolygon(RodaKiri1, 361, WarnaRoda1);
        Point2D_t  RodaKiri2[361];
        drawCircle(RodaKiriPos[0], 5, 360, 2, RodaKiri2);
        drawPolygon(RodaKiri2, 361, Outline, 3);
        fillPolygon(RodaKiri2, 361, WarnaRoda2);

        // Roda kanan (lingkaran luar dan dalam)
        Point2D_t  RodaKanan1[361];
        drawCircle(RodaKananPos[0], 15, 360, 2, RodaKanan1);
        drawPolygon(RodaKanan1, 361, Outline, 3);
        fillPolygon(RodaKanan1, 361, WarnaRoda1);
        Point2D_t  RodaKanan2[361];
        drawCircle(RodaKananPos[0], 5, 360, 2, RodaKanan2);
        drawPolygon(RodaKanan2, 361, Outline, 3);
        fillPolygon(RodaKanan2, 361, WarnaRoda2);
    }
   
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    userdraw();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 75);
    glutInitWindowSize(920, 720);
    glutCreateWindow("UAS GRAFIKA KOMPUTER");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    gluOrtho2D(0., 920., 0., 720.);
    glutIdleFunc(display);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}