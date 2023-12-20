// XZAnlys2012-E.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

#include <fstream>
#include <iomanip>
#include <windows.h>
#define karakter 100
using namespace std;
double acibul(double dx, double dy);
int main(int argc, char* argv[])
{

    // n      : Cubuk Sayýsý
    // x      : Dugum Sayýsý
    // sd     : Serbestlik Sayýsý
    // *R     : Refefans Dugum No Vektoru
    // *K     : Referans Olmayan Dugum No Vektoru
    // sno    : Serbestlik Numarasý
    // yss    : Yuklu Seerbestlik Sayýsý
    // A      : Alan
    // E      : Elastisite Modulu
    // I      : Atalaet Momenti
    // *Dx    : Dugum Noktasýnýn X Koordinat Vektoru
    // *Dy    : Dugum Noktasýnýn Y Koordinat Vektoru
    // *delx  : X Koordinatlarý Arasýndaki Fark Vektoru
    // *dely  : Y Koordinatlar Arasýndaki Fark Vektoru
    // *nj    : Dogrussal Cubuklar Ýcin Eksenal Yayýlý Yuk Vektoru

    int n, i, i1, j, j1, x, * R, * K, sd, * u, * v, * teta, ** Dj, sno, pivotkol, * Xizle, Xyeni, rep, yss;
    double* A, * E, * I, * Dx, * Dy, * Aci, * L, * delx, * dely, ** Sj, ** S, * P, * N, * W, * a, ** Q, * Qj, * Qt, * Pj, * X, pivot, eksiilecarp, rep1, ** qussu, ** qussucizgi, ** qcubuk, ** Djyeni, * nj;

    int k, k1 = 0, s, s1 = 0, l, l1 = 0, m, egricbksys, egriprcsys, * egricbknolar, yenicbksys, yenisd, yenix, ** uy, ** vy, ** tetay, ** Ry, ** Ky;
    double* Xm, * Ym, * delxref, * delyref, * delxrefol, * delyrefol, * aciref, * acirefol, * aciadim, * r, ** Xy, ** Yy, kooraci, ** Ay, ** Ey, ** Iy, ** Wy, ** Py, ** Ny, ** ay, ** Nj;
    double* egridelx, * egridely, * egriAci, * egriAci1;

    int* Rt, * Kt, * ut, * vt, * tetat, sayac, yok, sayac1, l2, l3 = 0, gaussevethayir;
    double* At, * Et, * It, * Xt, * Yt, * Wt, * Pt, * Nt, * at, * njt;

    ofstream yaz;
    ifstream oku;
    char* yazad, * okuad, * uzunlukbrm, * kuvvetbrm;
    yazad = new char[karakter];
    okuad = new char[karakter];
    uzunlukbrm = new char[karakter];
    kuvvetbrm = new char[karakter];
    cout << endl << endl;

    //Acýklama Basla
    for (i = 0; i < 3; i++)   //dikey sayac
    {
        if (i > 0 && i < 2)
        {
            cout << "* Isleme Baslamadan Once                                                    *" << endl;
            cout << "* Program Dosyasinin Bulundugu Yerde Bir Veri Dosyasi Olusturmalisin        *" << endl;
            cout << "* Veri Dosyasinin Yazimi Su Sekilde Olmalidir                               *" << endl;
            cout << "* Ilk Once Cubuk Bilgileri Olan i k A E I Verileri                          *" << endl;
            cout << "* Birinci Cubuk Icin Aralarinda Bosluk Birakilarak Girilmeli,               *" << endl;
            cout << "* Sonra Alt Satira Gecilerek Ayni Islem Diger Cubuklar Icin de Yapilmalidir *" << endl;
            cout << "* Daha Sonra Cubuk Yuk Bilgileri Olan W P N a nj Verileri                   *" << endl;
            cout << "* Birinci Cubuk Icin Aralarinda Bosluk Birakilarak Girilmeli,               *" << endl;
            cout << "* Sonra Alt Satira Gecilerek Ayni Islem Diger Cubuklar Icin de Yapilmalidir *" << endl;
            cout << "* Dugum Bilgileri Olan x y u v teta Verileri                                *" << endl;
            cout << "* Birinci Dugum Icin Aralarinda Bosluk Birakilarak Girilmeli,               *" << endl;
            cout << "* Sonra Alt Satira Gecilerek Ayni Islem Diger Dugumler Icin de Yapilmalidir *";
        }
        else
        {
            for (j = 0; j < 77; j++)  //yatay sayac
                cout << "*";
        }
        cout << endl;
    }
    //Acýklama Son

    cout << endl << endl;
    cout << "Islem Sonuclarinin Saklanacagi Dosyaya Ad Verin (Uzantisiyla Birlikte) = " << endl;
    cin >> yazad;
    cout << endl << "Islem Verilerinin Alinacagi Dosyanin Adini Girin (Uzantisiyla Birlikte) = " << endl;
    cin >> okuad;

    yaz.open(yazad);
    oku.open(okuad);
    if (yaz.fail())
        cout << "Hopp Hay Aksi Dosya Yaratilamiyor" << endl;
    if (oku.fail())
        cout << "Hopp Hay Aksi Dosya Acilamiyor" << endl;
    cout << endl << "Yapacaginiz Islemdeki Uzunluk Birimi Girin = " << endl;
    cin >> uzunlukbrm;
    cout << endl << "Yapacaginiz Islemdeki Kuvvet Birimini Girin = " << endl;
    cin >> kuvvetbrm;

    //Kimlik Basla
    for (i = 0; i < 3; i++)   //dikey sayac
    {
        if (i > 0 && i < 2)
        {
            yaz << "*       Iskender ATALAY         *" << endl;
            yaz << "*      Insaat  Muhendisi        *" << endl;
            yaz << "* Elektrik-Elektronik Muhendisi *" << endl;
            yaz << "* XZ Corporation'da Founder,CEO *" << endl;
            yaz << "*       www.xzcorp.com          *" << endl;
            yaz << "*  www.facebook.com/XZCorp      *" << endl;
            yaz << "*  www.twitter.com/XZCorp       *";
        }
        else
        {
            for (j = 0; j < 33; j++)  //yatay sayac
                yaz << "*";
        }
        yaz << endl;
    }
    //Kimlik Son

    yaz << endl;
    yaz << "Yapýlan Islemdeki Uzunluk Birimi = " << uzunlukbrm << endl;
    yaz << "Yapýlan Islemdeki Kuvvet Birimi = " << kuvvetbrm << endl << endl;
    cout << endl << "Cubuk Sayisini Girin " << endl;
    cin >> n;
    yaz << "Cubuk Sayýsý = " << n << endl;
    cout << endl << "Dugum Sayisi Girin " << endl;
    cin >> x;
    yaz << "Dugum Sayýsý= " << x << endl;
    cout << endl << "Serbestlik Derecesini Girin " << endl;
    cin >> sd;
    yaz << "Serbestlik Derecesi = " << sd << endl;

    R = new int[n];
    K = new int[n];
    A = new double[n];
    E = new double[n];
    I = new double[n];
    W = new double[n];
    P = new double[n];
    N = new double[n];
    a = new double[n];
    nj = new double[n];

    if ((R == NULL) || (K == NULL) || (A == NULL) || (E == NULL) || (I == NULL) || (W == NULL) || (P == NULL) || (N == NULL) || (a == NULL) || (nj == NULL))
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }

    cout << endl << "Cubuk Bilgileri Olusturdugunuz Veri Dosyasindan Alinacak" << endl;
    for (i = 0; i < n; i++)
    {
        oku >> R[i];
        oku >> K[i];
        oku >> A[i];
        oku >> E[i];
        oku >> I[i];
    }
    cout << endl;
    yaz << endl;
    cout << "Cubuk Bilgileri = " << endl << endl;
    yaz << "Cubuk Bilgileri = " << endl << endl;
    cout << setw(16) << "i";
    cout << setw(5) << "k";
    cout << setw(8) << "A(" << uzunlukbrm << "^2)";
    cout << setw(13) << "E(" << kuvvetbrm << "/" << uzunlukbrm << "^2)";
    cout << setw(8) << "I(" << uzunlukbrm << "^4)" << endl;
    yaz << setw(16) << "i";
    yaz << setw(5) << "k";
    yaz << setw(8) << "A(" << uzunlukbrm << "^2)";
    yaz << setw(13) << "E(" << kuvvetbrm << "/" << uzunlukbrm << "^2)";
    yaz << setw(8) << "I(" << uzunlukbrm << "^4)" << endl;
    for (i = 0; i <= 65; i++)
    {
        cout << "-";
        yaz << "-";
    }
    cout << endl;
    yaz << endl;
    for (i = 0; i < n; i++)
    {
        cout << i + 1 << ". Cubuk = ";
        yaz << i + 1 << ". Cubuk = ";
        cout << fixed << setprecision(6) << setw(5) << R[i];
        cout << fixed << setprecision(6) << setw(5) << K[i];
        cout << fixed << setprecision(6) << setw(12) << A[i];
        cout << fixed << setprecision(6) << setw(20) << E[i];
        cout << fixed << setprecision(6) << setw(12) << I[i] << endl;
        yaz << fixed << setprecision(6) << setw(5) << R[i];
        yaz << fixed << setprecision(6) << setw(5) << K[i];
        yaz << fixed << setprecision(6) << setw(12) << A[i];
        yaz << fixed << setprecision(6) << setw(20) << E[i];
        yaz << fixed << setprecision(6) << setw(12) << I[i] << endl;
    }
    for (i = 0; i < n; i++)
    {
        oku >> W[i];
        oku >> P[i];
        oku >> N[i];
        oku >> a[i];
        oku >> nj[i];
    }
    cout << endl;
    yaz << endl;
    cout << "Cubuk Yuk Bilgileri = " << endl << endl;
    yaz << "Cubuk Yuk Bilgileri = " << endl << endl;
    cout << setw(18) << "W(" << kuvvetbrm << "/" << uzunlukbrm << ")";
    cout << setw(9) << "P(" << kuvvetbrm << ")";
    cout << setw(9) << "N(" << kuvvetbrm << ")";
    cout << setw(10) << "a(" << uzunlukbrm << ")";
    cout << setw(10) << "nj(" << kuvvetbrm << "/" << uzunlukbrm << ")" << endl;
    yaz << setw(18) << "W(" << kuvvetbrm << "/" << uzunlukbrm << ")";
    yaz << setw(9) << "P(" << kuvvetbrm << ")";
    yaz << setw(9) << "N(" << kuvvetbrm << ")";
    yaz << setw(10) << "a(" << uzunlukbrm << ")";
    yaz << setw(10) << "nj(" << kuvvetbrm << "/" << uzunlukbrm << ")" << endl;
    for (i = 0; i <= 71; i++)
    {
        cout << "-";
        yaz << "-";
    }
    cout << endl;
    yaz << endl;
    for (i = 0; i < n; i++)
    {
        cout << i + 1 << ". Cubuk = ";
        yaz << i + 1 << ". Cubuk = ";
        cout << fixed << setprecision(6) << setw(12) << W[i];
        cout << fixed << setprecision(6) << setw(12) << P[i];
        cout << fixed << setprecision(6) << setw(12) << N[i];
        cout << fixed << setprecision(6) << setw(12) << a[i];
        cout << fixed << setprecision(6) << setw(12) << nj[i] << endl;
        yaz << fixed << setprecision(6) << setw(12) << W[i];
        yaz << fixed << setprecision(6) << setw(12) << P[i];
        yaz << fixed << setprecision(6) << setw(12) << N[i];
        yaz << fixed << setprecision(6) << setw(12) << a[i];
        yaz << fixed << setprecision(6) << setw(12) << nj[i] << endl;
    }

    u = new int[x];
    v = new int[x];
    teta = new int[x];
    Dx = new double[x];
    Dy = new double[x];

    if ((u == NULL) || (v == NULL) || (teta == NULL) || (Dx == NULL) || (Dy == NULL))
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }

    cout << endl;
    cout << "Dugum Bilgileri Olusturdugunuz Veri Dosyasindan Alinacak" << endl;
    for (i = 0; i < x; i++)
    {
        oku >> Dx[i];
        oku >> Dy[i];
        oku >> u[i];
        oku >> v[i];
        oku >> teta[i];
    }
    cout << endl;
    yaz << endl;
    cout << "Dugum Bilgileri = " << endl << endl;
    yaz << "Dugum Bilgileri = " << endl << endl;
    cout << setw(20) << "X" << "(" << uzunlukbrm << ")";
    cout << setw(9) << "Y" << "(" << uzunlukbrm << ")";
    cout << setw(5) << "U";
    cout << setw(5) << "V";
    cout << setw(7) << "Teta" << endl;
    yaz << setw(20) << "X" << "(" << uzunlukbrm << ")";
    yaz << setw(9) << "Y" << "(" << uzunlukbrm << ")";
    yaz << setw(5) << "U";
    yaz << setw(5) << "V";
    yaz << setw(7) << "Teta" << endl;
    for (i = 0; i <= 52; i++)
    {
        cout << "-";
        yaz << "-";
    }
    cout << endl;
    yaz << endl;
    for (i = 0; i < x; i++)
    {
        cout << i + 1 << ". Dugum = ";
        yaz << i + 1 << ". Dugum = ";
        cout << setw(12) << Dx[i];
        cout << setw(12) << Dy[i];
        cout << setw(5) << u[i];
        cout << setw(5) << v[i];
        cout << setw(7) << teta[i] << endl;
        yaz << fixed << setprecision(6) << setw(12) << Dx[i];
        yaz << fixed << setprecision(6) << setw(12) << Dy[i];
        yaz << setw(5) << u[i];
        yaz << setw(5) << v[i];
        yaz << setw(7) << teta[i] << endl;
    }
    cout << endl;
    yaz << endl;

    cout << "Egri Eksenli Cubuk Sayisini Girin = " << endl;
    cin >> egricbksys;
    yaz << "Egri Eksenli Cubuk Sayýsý = " << egricbksys << endl << endl;

    if (egricbksys == 0)
    {
        cout << endl << "Sistemde Egri Eksenli Cubuk Bulunmamaktadir." << endl << endl;
        yaz << "Sistemde Egri Eksenli Cubuk Bulunmamaktadýr." << endl << endl;

        yenicbksys = n;
        yenix = x;
        yenisd = sd;

        for (i = 0; i < n; i++)
        {
            Rt[i] = R[i];
            Kt[i] = K[i];
            At[i] = A[i];
            It[i] = I[i];
            Wt[i] = W[i];
            Pt[i] = P[i];
            Nt[i] = N[i];
            at[i] = a[i];
            njt[i] = nj[i];
        }
        for (i = 0; i < x; i++)
        {
            Xt[i] = Dx[i];
            Yt[i] = Dy[i];
            ut[i] = u[i];
            vt[i] = v[i];
            tetat[i] = teta[i];
        }
    }
    else
    {
        cout << endl << "Egri Eksenli Cubuk(lar) Kac Parcaya Bolunsun = " << endl;
        cin >> egriprcsys;
        yaz << "Egri Eksenli Cubuk(lar)ýn Bolunecegi Parca Sayýsý = " << egriprcsys << endl << endl;

        yenicbksys = n + ((egriprcsys - 1) * egricbksys);
        yenisd = sd + ((egriprcsys - 1) * 3 * egricbksys);
        yenix = x + ((egriprcsys - 1) * egricbksys);

        cout << endl << "Sistemin Yeni Cubuk Sayisi = " << yenicbksys << endl << endl;
        yaz << "Sistemin Yeni Cubuk Sayýsý = " << yenicbksys << endl << endl;
        cout << "Sistemin Yeni Dugum Sayisi = " << yenix << endl << endl;
        yaz << "Sistemin Yeni Dugum Sayýsý = " << yenix << endl << endl;
        cout << "Sistemin Yeni Serbestlik Derecesi = " << yenisd << endl << endl;
        yaz << "Sistemin Yeni Serbestlik Derecesi = " << yenisd << endl << endl;

        egricbknolar = new int[egricbksys];
        Xm = new double[egricbksys];
        Ym = new double[egricbksys];
        delxref = new double[egricbksys];
        delyref = new double[egricbksys];
        delxrefol = new double[egricbksys];
        delyrefol = new double[egricbksys];
        aciref = new double[egricbksys];
        acirefol = new double[egricbksys];
        aciadim = new double[egricbksys];
        r = new double[egricbksys];
        Rt = new int[yenicbksys];
        Kt = new int[yenicbksys];
        At = new double[yenicbksys];
        Et = new double[yenicbksys];
        It = new double[yenicbksys];
        Wt = new double[yenicbksys];
        Pt = new double[yenicbksys];
        Nt = new double[yenicbksys];
        at = new double[yenicbksys];
        njt = new double[yenicbksys];

        egridelx = new double[egricbksys * egriprcsys];
        egridely = new double[egricbksys * egriprcsys];
        egriAci = new double[egricbksys * egriprcsys];
        egriAci1 = new double[egricbksys * egriprcsys];

        Xy = new double* [egricbksys];
        for (i = 0; i < egricbksys; i++)
        {
            Xy[i] = new double[egriprcsys - 1];
            if (Xy[i] == NULL)
            {
                cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                system("pause");
                return 0;
            }
        }
        Yy = new double* [egricbksys];
        for (i = 0; i < egricbksys; i++)
        {
            Yy[i] = new double[egriprcsys - 1];
            if (Yy[i] == NULL)
            {
                cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                system("pause");
                return 0;
            }
        }
        uy = new int* [egricbksys];
        for (i = 0; i < egricbksys; i++)
        {
            uy[i] = new int[egriprcsys - 1];
            if (uy[i] == NULL)
            {
                cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                system("pause");
                return 0;
            }
        }
        vy = new int* [egricbksys];
        for (i = 0; i < egricbksys; i++)
        {
            vy[i] = new int[egriprcsys - 1];
            if (vy[i] == NULL)
            {
                cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                system("pause");
                return 0;
            }
        }
        tetay = new int* [egricbksys];
        for (i = 0; i < egricbksys; i++)
        {
            tetay[i] = new int[egriprcsys - 1];
            if (tetay[i] == NULL)
            {
                cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                system("pause");
                return 0;
            }
        }
        Ry = new int* [egricbksys];
        for (i = 0; i < egricbksys; i++)
        {
            Ry[i] = new int[egriprcsys];
            if (Ry[i] == NULL)
            {
                cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                system("pause");
                return 0;
            }
        }
        Ky = new int* [egricbksys];
        for (i = 0; i < egricbksys; i++)
        {
            Ky[i] = new int[egriprcsys];
            if (Ky[i] == NULL)
            {
                cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                system("pause");
                return 0;
            }
        }
        Ay = new double* [egricbksys];
        for (i = 0; i < egricbksys; i++)
        {
            Ay[i] = new double[egriprcsys];
            if (Ay[i] == NULL)
            {
                cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                system("pause");
                return 0;
            }
        }
        Ey = new double* [egricbksys];
        for (i = 0; i < egricbksys; i++)
        {
            Ey[i] = new double[egriprcsys];
            if (Ey[i] == NULL)
            {
                cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                system("pause");
                return 0;
            }
        }
        Iy = new double* [egricbksys];
        for (i = 0; i < egricbksys; i++)
        {
            Iy[i] = new double[egricbksys * egriprcsys];
            if (Iy[i] == NULL)
            {
                cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                system("pause");
                return 0;
            }
        }
        Wy = new double* [egricbksys];
        for (i = 0; i < egricbksys; i++)
        {
            Wy[i] = new double[egricbksys * egriprcsys];
            if (Wy[i] == NULL)
            {
                cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                system("pause");
                return 0;
            }
        }
        Py = new double* [egricbksys];
        for (i = 0; i < egricbksys; i++)
        {
            Py[i] = new double[egricbksys * egriprcsys];
            if (Py[i] == NULL)
            {
                cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                system("pause");
                return 0;
            }
        }
        Ny = new double* [egricbksys];
        for (i = 0; i < egricbksys; i++)
        {
            Ny[i] = new double[egricbksys * egriprcsys];
            if (Ny[i] == NULL)
            {
                cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                system("pause");
                return 0;
            }
        }
        ay = new double* [egricbksys];
        for (i = 0; i < egricbksys; i++)
        {
            ay[i] = new double[egricbksys * egriprcsys];
            if (ay[i] == NULL)
            {
                cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                system("pause");
                return 0;
            }
        }
        Nj = new double* [egricbksys];
        for (i = 0; i < egricbksys; i++)
        {
            Nj[i] = new double[egricbksys * egriprcsys];
            if (Nj[i] == NULL)
            {
                cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
                system("pause");
                return 0;
            }
        }

        if ((aciref == NULL) || (acirefol == NULL) || (aciadim == NULL) || (r == NULL) || (delxref == NULL) || (delyref == NULL) || (delxrefol == NULL) || (delyrefol == NULL) || (egricbknolar == NULL))
        {
            cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            system("pause");
            return 0;
        }
        if ((Xm == NULL) || (Ym == NULL) || (Ry == NULL) || (Ky == NULL) || (Ay == NULL) || (Ey == NULL) || (Iy == NULL) || (Wy == NULL) || (Py == NULL) || (Ny == NULL) || (ay == NULL) || (Nj == NULL))
        {
            cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            system("pause");
            return 0;
        }
        if ((At == NULL) || (Et == NULL) || (It == NULL) || (Wt == NULL) || (Pt == NULL) || (Nt == NULL) || (at == NULL) || (egridelx == NULL) || (egridely == NULL) || (egriAci == NULL) || (njt == NULL))
        {
            cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            system("pause");
            return 0;
        }
        m = x + 1;
        for (i = 0; i < egricbksys; i++)
        {
            cout << i + 1 << ". Egri Eksenli Cubugun Cubuk Numarasini Girin = " << endl;
            cin >> egricbknolar[i];
            cout << endl << i + 1 << ". Egri Cubugun Merkez X Koordinatini Girin = " << endl;
            cin >> Xm[i];
            cout << endl << i + 1 << ". Egri Cubugun Merkez Y Koordinatini Girin = " << endl;
            cin >> Ym[i];

            cout << endl << i + 1 << ". Egri Cubugun Cubuk Numarasi = " << egricbknolar[i] << endl << endl;
            yaz << i + 1 << ". Egri Cubugun Cubuk Numarasý = " << egricbknolar[i] << endl << endl;

            cout << i + 1 << ". Egri Cubugun Merkez Koordinatlari= " << Xm[i] << " " << uzunlukbrm << "\t" << Ym[i] << " " << uzunlukbrm << endl << endl;
            yaz << i + 1 << ". Egri Cubugun Merkez Koordinatlarý= " << Xm[i] << " " << uzunlukbrm << "\t" << Ym[i] << " " << uzunlukbrm << endl << endl;

            delxref[i] = Dx[R[egricbknolar[i] - 1] - 1] - Xm[i];
            delyref[i] = Dy[R[egricbknolar[i] - 1] - 1] - Ym[i];
            delxrefol[i] = Dx[K[egricbknolar[i] - 1] - 1] - Xm[i];
            delyrefol[i] = Dy[K[egricbknolar[i] - 1] - 1] - Ym[i];

            cout << i + 1 << ". Egri Eksenli Cubugun Referans Delta X'si = " << delxref[i] << " " << uzunlukbrm << endl << endl;
            cout << i + 1 << ". Egri Eksenli Cubugun Referans Delta Y'si = " << delyref[i] << " " << uzunlukbrm << endl << endl;
            cout << i + 1 << ". Egri Eksenli Cubugun Referans Olmayan Delta X'si = " << delxrefol[i] << " " << uzunlukbrm << endl << endl;
            cout << i + 1 << ". Egri Eksenli Cubugun Referans Olmayan Delta Y'si = " << delyrefol[i] << " " << uzunlukbrm << endl << endl;
            yaz << i + 1 << ". Egri Eksenli Cubugun Referans Delta X'si = " << delxref[i] << " " << uzunlukbrm << endl << endl;
            yaz << i + 1 << ". Egri Eksenli Cubugun Referans Delta Y'si = " << delyref[i] << " " << uzunlukbrm << endl << endl;
            yaz << i + 1 << ". Egri Eksenli Cubugun Referans Olmayan Delta X'si = " << delxrefol[i] << " " << uzunlukbrm << endl << endl;
            yaz << i + 1 << ". Egri Eksenli Cubugun Referans Olmayan Delta Y'si = " << delyrefol[i] << " " << uzunlukbrm << endl << endl;

            aciref[i] = acibul(delxref[i], delyref[i]);
            acirefol[i] = acibul(delxrefol[i], delyrefol[i]);
            if (acirefol[i] < aciref[i])
                acirefol[i] = acirefol[i] + (2 * M_PI);
            aciadim[i] = fabs(acirefol[i] - aciref[i]) / egriprcsys;
            r[i] = sqrt(pow(delxref[i], 2) + pow(delyref[i], 2));

            cout << i + 1 << ". Egri Eksenli Cubugun Referans Acisi = " << aciref[i] << " " << "radyan" << " = " << aciref[i] * 180 / M_PI << " derece" << endl << endl;
            cout << i + 1 << ". Egri Eksenli Cubugun Referans Olmayan Acisi = " << acirefol[i] << " " << "radyan" << " = " << acirefol[i] * 180 / M_PI << " derece" << endl << endl;
            cout << i + 1 << ". Egri Eksenli Cubugun Adim Acisi = " << aciadim[i] << " " << "radyan" << " = " << aciadim[i] * 180 / M_PI << " derece" << endl << endl;
            cout << i + 1 << ". Egri Eksenli Cubugun Yaricapi = " << r[i] << " " << uzunlukbrm << endl << endl;
            yaz << i + 1 << ". Egri Eksenli Cubugun Referans Acýsý = " << aciref[i] << " " << "radyan" << " = " << aciref[i] * 180 / M_PI << " derece" << endl << endl;
            yaz << i + 1 << ". Egri Eksenli Cubugun Referans Olmayan Acýsý = " << acirefol[i] << " " << "radyan" << " = " << acirefol[i] * 180 / M_PI << " derece" << endl << endl;
            yaz << i + 1 << ". Egri Eksenli Cubugun Adým Acýsý = " << aciadim[i] << " " << "radyan" << " = " << aciadim[i] * 180 / M_PI << " derece" << endl << endl;
            yaz << i + 1 << ". Egri Eksenli Cubugun Yarýcapý = " << r[i] << " " << uzunlukbrm << endl << endl;

            kooraci = 0;
            s = sd + 1;
            if (i != 0)
                s = s1;
            for (j = 0; j < egriprcsys - 1; j++)
            {
                kooraci = kooraci + aciadim[i];
                Xy[i][j] = Xm[i] + r[i] * cos(kooraci + aciref[i]);
                Yy[i][j] = Ym[i] + r[i] * sin(kooraci + aciref[i]);

                uy[i][j] = s;
                vy[i][j] = uy[i][j] + 1;
                tetay[i][j] = vy[i][j] + 1;
                s = s + 3;
                s1 = s;
            }

            for (j = 0; j < egriprcsys; j++)
            {
                Ry[i][j] = R[egricbknolar[i] - 1];
                Ky[i][j] = m;

                if (j != 0)
                {
                    Ry[i][j] = Ky[i][j - 1];
                    Ky[i][j] = Ry[i][j] + 1;
                }
                if (j == egriprcsys - 1)
                    Ky[i][j] = K[egricbknolar[i] - 1];
            }
            m = m + egriprcsys - 1;

            for (j = 0; j < egriprcsys; j++)
            {
                Ay[i][j] = A[egricbknolar[i] - 1];
                Ey[i][j] = E[egricbknolar[i] - 1];
                Iy[i][j] = I[egricbknolar[i] - 1];
                Py[i][j] = P[egricbknolar[i] - 1];
                Ny[i][j] = N[egricbknolar[i] - 1];
                ay[i][j] = a[egricbknolar[i] - 1];
            }

        }//egricbksys kadar gonguyu dondurmek icin

        Xt = new double[yenix];
        Yt = new double[yenix];
        ut = new int[yenix];
        vt = new int[yenix];
        tetat = new int[yenix];

        if ((Xt == NULL) || (Yt == NULL) || (ut == NULL) || (vt == NULL) || (tetat == NULL))
        {
            cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            yaz << "Hopp Hay Aksii Bellek Yeter1sizz" << endl;
            system("pause");
            return 0;
        }

        sayac1 = 0;
        for (i = 0; i < x; i++)
        {
            Xt[sayac1] = Dx[i];
            Yt[sayac1] = Dy[i];
            ut[sayac1] = u[i];
            vt[sayac1] = v[i];
            tetat[sayac1] = teta[i];
            sayac1++;
        }
        for (i = 0; i < egricbksys; i++)
        {
            for (j = 0; j < egriprcsys - 1; j++)
            {
                Xt[sayac1] = Xy[i][j];
                Yt[sayac1] = Yy[i][j];
                ut[sayac1] = uy[i][j];
                vt[sayac1] = vy[i][j];
                tetat[sayac1] = tetay[i][j];
                sayac1++;
            }
        }

        for (i = 0; i < egricbksys; i++)
        {
            for (j = 0; j < egriprcsys; j++)
            {
                egridelx[j] = Xt[Ky[i][j] - 1] - Xt[Ry[i][j] - 1];
                egridely[j] = Yt[Ky[i][j] - 1] - Yt[Ry[i][j] - 1];
                egriAci[i] = acibul(egridelx[j], egridely[j]);

                if ((egridelx[j] < 0) && (egridely[j] < 0))
                {
                    egriAci1[i] = (3.0 * M_PI / 2.0) - egriAci[i];
                    Wy[i][j] = -W[egricbknolar[i] - 1] * pow(cos(egriAci1[i]), 2.0);
                    Nj[i][j] = -W[egricbknolar[i] - 1] * sin(egriAci1[i]) * cos(egriAci1[i]);
                }
                if ((egridelx[j] < 0) && (egridely[j] > 0))
                {
                    egriAci1[i] = egriAci[i] - (M_PI / 2);
                    Wy[i][j] = -W[egricbknolar[i] - 1] * pow(cos(egriAci1[i]), 2.0);
                    Nj[i][j] = W[egricbknolar[i] - 1] * sin(egriAci1[i]) * cos(egriAci1[i]);
                }
            }
        }

        cout << "Egri Eksenli Cubuklarin Cubuk Bilgileri = " << endl << endl;
        yaz << "Egri Eksenli Cubuklarýn Cubuk Bilgileri = " << endl << endl;
        cout << setw(16) << "i";
        cout << setw(5) << "k";
        cout << setw(8) << "A(" << uzunlukbrm << "^2)";
        cout << setw(13) << "E(" << kuvvetbrm << "/" << uzunlukbrm << "^2)";
        cout << setw(8) << "I(" << uzunlukbrm << "^4)" << endl;
        yaz << setw(16) << "i";
        yaz << setw(5) << "k";
        yaz << setw(8) << "A(" << uzunlukbrm << "^2)";
        yaz << setw(13) << "E(" << kuvvetbrm << "/" << uzunlukbrm << "^2)";
        yaz << setw(8) << "I(" << uzunlukbrm << "^4)" << endl;
        for (i = 0; i <= 65; i++)
        {
            cout << "-";
            yaz << "-";
        }
        cout << endl;
        yaz << endl;
        for (i = 0; i < egricbksys; i++)
        {
            l = n + 1;
            if (i != 0)
                l = l1 + 1;
            for (j = 0; j < egriprcsys; j++)
            {
                cout << l << ". Cubuk = ";
                yaz << l << ". Cubuk = ";
                cout << fixed << setprecision(6) << setw(5) << Ry[i][j];
                cout << fixed << setprecision(6) << setw(5) << Ky[i][j];
                cout << fixed << setprecision(6) << setw(12) << Ay[i][j];
                cout << fixed << setprecision(6) << setw(20) << Ey[i][j];
                cout << fixed << setprecision(6) << setw(12) << Iy[i][j] << endl;
                yaz << fixed << setprecision(6) << setw(5) << Ry[i][j];
                yaz << fixed << setprecision(6) << setw(5) << Ky[i][j];
                yaz << fixed << setprecision(6) << setw(12) << Ay[i][j];
                yaz << fixed << setprecision(6) << setw(20) << Ey[i][j];
                yaz << fixed << setprecision(6) << setw(12) << Iy[i][j] << endl;
                l = l + 1;
                l1 = l - 1;
            }
        }
        cout << endl;
        yaz << endl;

        cout << "Egri Eksenli Cubuklarin Cubuk Yuk Bilgileri = " << endl << endl;
        yaz << "Egri Eksenli Cubuklarýn Cubuk Yuk Bilgileri = " << endl << endl;
        cout << setw(18) << "W(" << kuvvetbrm << "/" << uzunlukbrm << ")";
        cout << setw(9) << "P(" << kuvvetbrm << ")";
        cout << setw(9) << "N(" << kuvvetbrm << ")";
        cout << setw(10) << "a(" << uzunlukbrm << ")";
        cout << setw(10) << "nj(" << kuvvetbrm << "/" << uzunlukbrm << ")" << endl;
        yaz << setw(18) << "W(" << kuvvetbrm << "/" << uzunlukbrm << ")";
        yaz << setw(9) << "P(" << kuvvetbrm << ")";
        yaz << setw(9) << "N(" << kuvvetbrm << ")";
        yaz << setw(10) << "a(" << uzunlukbrm << ")";
        yaz << setw(10) << "nj(" << kuvvetbrm << "/" << uzunlukbrm << ")" << endl;
        for (i = 0; i <= 71; i++)
        {
            cout << "-";
            yaz << "-";
        }
        cout << endl;
        yaz << endl;
        for (i = 0; i < egricbksys; i++)
        {
            l2 = n + 1;
            if (i != 0)
                l2 = l3 + 1;
            for (j = 0; j < egriprcsys; j++)
            {
                cout << l2 << ". Cubuk = ";
                yaz << l2 << ". Cubuk = ";
                cout << fixed << setprecision(6) << setw(12) << Wy[i][j];
                cout << fixed << setprecision(6) << setw(12) << Py[i][j];
                cout << fixed << setprecision(6) << setw(12) << Ny[i][j];
                cout << fixed << setprecision(6) << setw(12) << ay[i][j];
                cout << fixed << setprecision(6) << setw(12) << Nj[i][j] << endl;
                yaz << fixed << setprecision(6) << setw(12) << Wy[i][j];
                yaz << fixed << setprecision(6) << setw(12) << Py[i][j];
                yaz << fixed << setprecision(6) << setw(12) << Ny[i][j];
                yaz << fixed << setprecision(6) << setw(12) << ay[i][j];
                yaz << fixed << setprecision(6) << setw(12) << Nj[i][j] << endl;
                l2 = l2 + 1;
                l3 = l2 - 1;
            }
        }
        cout << endl;
        yaz << endl;

        cout << "Egri Eksenli Cubuklarin Dugum Bilgileri = " << endl << endl;
        yaz << "Egri Eksenli Cubuklarýn Dugum Bilgileri = " << endl << endl;
        cout << setw(20) << "X" << "(" << uzunlukbrm << ")";
        cout << setw(9) << "Y" << "(" << uzunlukbrm << ")";
        cout << setw(5) << "U";
        cout << setw(5) << "V";
        cout << setw(7) << "Teta" << endl;
        yaz << setw(20) << "X" << "(" << uzunlukbrm << ")";
        yaz << setw(9) << "Y" << "(" << uzunlukbrm << ")";
        yaz << setw(5) << "U";
        yaz << setw(5) << "V";
        yaz << setw(7) << "Teta" << endl;
        for (i = 0; i <= 52; i++)
        {
            cout << "-";
            yaz << "-";
        }
        cout << endl;
        yaz << endl;
        for (i = 0; i < egricbksys; i++)
        {
            k = x + 1;
            if (i != 0)
                k = k1 + 1;
            for (j = 0; j < egriprcsys - 1; j++)
            {
                cout << k << ". Dugum = ";
                yaz << k << ". Dugum = ";
                cout << fixed << setprecision(6) << setw(12) << Xy[i][j];
                cout << fixed << setprecision(6) << setw(12) << Yy[i][j];
                cout << setw(5) << uy[i][j];
                cout << setw(5) << vy[i][j];
                cout << setw(7) << tetay[i][j] << endl;
                yaz << fixed << setprecision(6) << setw(12) << Xy[i][j];
                yaz << fixed << setprecision(6) << setw(12) << Yy[i][j];
                yaz << setw(5) << uy[i][j];
                yaz << setw(5) << vy[i][j];
                yaz << setw(7) << tetay[i][j] << endl;
                k = k + 1;
                k1 = k - 1;
            }
        }
        cout << endl;
        yaz << endl;

        bool yok;
        sayac = 0;
        for (i = 0; i < n; i++)
        {
            yok = true;
            j = 0;
            while (yok && j < egricbksys)
            {
                if (i == egricbknolar[j] - 1)
                    yok = false;
                j++;
            }
            if (yok)
            {
                Rt[sayac] = R[i];
                Kt[sayac] = K[i];
                At[sayac] = A[i];
                Et[sayac] = E[i];
                It[sayac] = I[i];
                Wt[sayac] = W[i];
                Pt[sayac] = P[i];
                Nt[sayac] = N[i];
                at[sayac] = a[i];
                njt[sayac] = nj[i];
                sayac++;
            }
        }
        for (i = 0; i < egricbksys; i++)
        {
            for (j = 0; j < egriprcsys; j++)
            {
                Rt[sayac] = Ry[i][j];
                Kt[sayac] = Ky[i][j];
                At[sayac] = Ay[i][j];
                Et[sayac] = Ey[i][j];
                It[sayac] = Iy[i][j];
                Wt[sayac] = Wy[i][j];
                Pt[sayac] = Py[i][j];
                Nt[sayac] = Ny[i][j];
                at[sayac] = ay[i][j];
                njt[sayac] = Nj[i][j];
                sayac++;
            }
        }
        cout << endl;
        yaz << endl;
        cout << "Sistemin Toplam Cubuk Bilgileri = " << endl << endl;
        yaz << "Sistemin Toplam Cubuk Bilgileri = " << endl << endl;
        cout << setw(16) << "i";
        cout << setw(5) << "k";
        cout << setw(8) << "A(" << uzunlukbrm << "^2)";
        cout << setw(13) << "E(" << kuvvetbrm << "/" << uzunlukbrm << "^2)";
        cout << setw(8) << "I(" << uzunlukbrm << "^4)" << endl;
        yaz << setw(16) << "i";
        yaz << setw(5) << "k";
        yaz << setw(8) << "A(" << uzunlukbrm << "^2)";
        yaz << setw(13) << "E(" << kuvvetbrm << "/" << uzunlukbrm << "^2)";
        yaz << setw(8) << "I(" << uzunlukbrm << "^4)" << endl;
        for (i = 0; i <= 65; i++)
        {
            cout << "-";
            yaz << "-";
        }
        cout << endl;
        yaz << endl;
        for (i = 0; i < yenicbksys; i++)
        {
            cout << i + 1 << ". Cubuk = ";
            yaz << i + 1 << ". Cubuk = ";
            cout << fixed << setprecision(6) << setw(5) << Rt[i];
            cout << fixed << setprecision(6) << setw(5) << Kt[i];
            cout << fixed << setprecision(6) << setw(12) << At[i];
            cout << fixed << setprecision(6) << setw(20) << Et[i];
            cout << fixed << setprecision(6) << setw(12) << It[i] << endl;
            yaz << fixed << setprecision(6) << setw(5) << Rt[i];
            yaz << fixed << setprecision(6) << setw(5) << Kt[i];
            yaz << fixed << setprecision(6) << setw(12) << At[i];
            yaz << fixed << setprecision(6) << setw(20) << Et[i];
            yaz << fixed << setprecision(6) << setw(12) << It[i] << endl;
        }
        cout << endl;
        yaz << endl;
        cout << "Sistemin Toplam Cubuk Yuk Bilgileri = " << endl << endl;
        yaz << "Sistemin Toplam Cubuk Yuk Bilgileri = " << endl << endl;
        cout << setw(18) << "W(" << kuvvetbrm << "/" << uzunlukbrm << ")";
        cout << setw(9) << "P(" << kuvvetbrm << ")";
        cout << setw(9) << "N(" << kuvvetbrm << ")";
        cout << setw(10) << "a(" << uzunlukbrm << ")";
        cout << setw(10) << "nj(" << kuvvetbrm << "/" << uzunlukbrm << ")" << endl;
        yaz << setw(18) << "W(" << kuvvetbrm << "/" << uzunlukbrm << ")";
        yaz << setw(9) << "P(" << kuvvetbrm << ")";
        yaz << setw(9) << "N(" << kuvvetbrm << ")";
        yaz << setw(10) << "a(" << uzunlukbrm << ")";
        yaz << setw(10) << "nj(" << kuvvetbrm << "/" << uzunlukbrm << ")" << endl;
        for (i = 0; i <= 71; i++)
        {
            cout << "-";
            yaz << "-";
        }
        cout << endl;
        yaz << endl;
        for (i = 0; i < yenicbksys; i++)
        {
            cout << i + 1 << ". Cubuk = ";
            yaz << i + 1 << ". Cubuk = ";
            cout << fixed << setprecision(6) << setw(12) << Wt[i];
            cout << fixed << setprecision(6) << setw(12) << Pt[i];
            cout << fixed << setprecision(6) << setw(12) << Nt[i];
            cout << fixed << setprecision(6) << setw(12) << at[i];
            cout << fixed << setprecision(6) << setw(12) << njt[i] << endl;
            yaz << fixed << setprecision(6) << setw(12) << Wt[i];
            yaz << fixed << setprecision(6) << setw(12) << Pt[i];
            yaz << fixed << setprecision(6) << setw(12) << Nt[i];
            yaz << fixed << setprecision(6) << setw(12) << at[i];
            yaz << fixed << setprecision(6) << setw(12) << njt[i] << endl;

        }
        cout << endl;
        yaz << endl;
        cout << "Sistemin Toplam Dugum Bilgileri = " << endl << endl;
        yaz << "Sistemin Toplam Dugum Bilgileri = " << endl << endl;
        cout << setw(20) << "X" << "(" << uzunlukbrm << ")";
        cout << setw(9) << "Y" << "(" << uzunlukbrm << ")";
        cout << setw(5) << "U";
        cout << setw(5) << "V";
        cout << setw(7) << "Teta" << endl;
        yaz << setw(20) << "X" << "(" << uzunlukbrm << ")";
        yaz << setw(9) << "Y" << "(" << uzunlukbrm << ")";
        yaz << setw(5) << "U";
        yaz << setw(5) << "V";
        yaz << setw(7) << "Teta" << endl;
        for (i = 0; i <= 52; i++)
        {
            cout << "-";
            yaz << "-";
        }
        cout << endl;
        yaz << endl;
        for (i = 0; i < yenix; i++)
        {
            cout << i + 1 << ". Dugum = ";
            yaz << i + 1 << ". Dugum = ";
            cout << setw(12) << Xt[i];
            cout << setw(12) << Yt[i];
            cout << setw(5) << ut[i];
            cout << setw(5) << vt[i];
            cout << setw(7) << tetat[i] << endl;
            yaz << fixed << setprecision(6) << setw(12) << Xt[i];
            yaz << fixed << setprecision(6) << setw(12) << Yt[i];
            yaz << setw(5) << ut[i];
            yaz << setw(5) << vt[i];
            yaz << setw(7) << tetat[i] << endl;
        }
        cout << endl;
        yaz << endl;

    } // elsei kapaatýrr egricbksys 0 deilse :))) 

    L = new double[yenicbksys];
    delx = new double[yenicbksys];
    dely = new double[yenicbksys];
    Aci = new double[yenicbksys];

    if ((L == NULL) || (delx == NULL) || (dely == NULL) || (Aci == NULL))
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }

    cout << "Delta X ve Delta Y Degerleri = " << endl << endl;
    yaz << "Delta X ve Delta Y Degerleri = " << endl << endl;
    cout << setw(20) << "Delta X" << "(" << uzunlukbrm << ")";
    cout << setw(9) << "Delta Y" << "(" << uzunlukbrm << ")" << endl;
    yaz << setw(20) << "Delta X" << "(" << uzunlukbrm << ")";
    yaz << setw(9) << "Delta Y" << "(" << uzunlukbrm << ")" << endl;
    for (i = 0; i <= 35; i++)
    {
        cout << "-";
        yaz << "-";
    }
    cout << endl;
    yaz << endl;
    for (i = 0; i < yenicbksys; i++)
    {
        delx[i] = Xt[(Kt[i] - 1)] - Xt[(Rt[i] - 1)];
        dely[i] = Yt[(Kt[i] - 1)] - Yt[(Rt[i] - 1)];
        cout << i + 1 << ". Cubuk = ";
        yaz << i + 1 << ". Cubuk = ";
        cout << fixed << setprecision(6) << setw(12) << delx[i];
        cout << fixed << setprecision(6) << setw(12) << dely[i] << endl;
        yaz << fixed << setprecision(6) << setw(12) << delx[i];
        yaz << fixed << setprecision(6) << setw(12) << dely[i] << endl;
    }
    cout << endl;
    yaz << endl;
    cout << "L Degerleri = " << endl << endl;
    yaz << "L Degerleri = " << endl << endl;

    for (i = 0; i < yenicbksys; i++)
    {
        L[i] = sqrt(pow(delx[i], 2) + pow(dely[i], 2));
        cout << fixed << setprecision(6) << setw(10) << "L[" << i + 1 << "]= " << L[i] << " " << uzunlukbrm << endl;
        yaz << fixed << setprecision(6) << setw(10) << "L[" << i + 1 << "]= " << L[i] << " " << uzunlukbrm << endl;
    }
    cout << endl;
    yaz << endl;
    cout << "Aci Degerleri = " << endl << endl;
    yaz << "Acý Degerleri = " << endl << endl;
    for (i = 0; i < yenicbksys; i++)
    {
        Aci[i] = acibul(delx[i], dely[i]);
        cout << fixed << setprecision(6) << setw(10) << "Derece Cinsinden Aci[" << i + 1 << "]= " << Aci[i] * 180 / M_PI << endl;
        yaz << fixed << setprecision(6) << setw(10) << "Derece Cinsinden Acý[" << i + 1 << "]= " << Aci[i] * 180 / M_PI << endl;
    }

    Dj = new int* [yenicbksys];
    if (Dj == NULL)
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < yenicbksys; i++)
    {
        Dj[i] = new int[6];
        if (Dj[i] == NULL)
        {
            cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            system("pause");
            return 0;
        }
    }
    cout << endl;
    yaz << endl;
    cout << "Dj Matrisi Verilerin Kaydedildigi Cikti Dosyasindadir. " << endl;
    yaz << "Dj Matrisi = " << endl;
    yaz << endl;
    for (i = 0; i < yenicbksys; i++)
    {
        Dj[i][0] = ut[Rt[i] - 1];
        Dj[i][1] = vt[Rt[i] - 1];
        Dj[i][2] = tetat[Rt[i] - 1];
        Dj[i][3] = ut[Kt[i] - 1];
        Dj[i][4] = vt[Kt[i] - 1];
        Dj[i][5] = tetat[Kt[i] - 1];
        for (j = 0; j < 6; j++)
            yaz << fixed << setw(12) << Dj[i][j] << " ";
        yaz << endl;
    }
    Q = new double* [yenicbksys];
    if (Q == NULL)
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < yenicbksys; i++)
    {
        Q[i] = new double[6];
        if (Q[i] == NULL)
        {
            cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            system("pause");
            return 0;
        }
    }
    cout << endl;
    yaz << endl;
    cout << "Q Matrisi Verilerin Kaydedildigi Cikti Dosyasindadir. " << endl;
    yaz << "Q Matrisi = " << endl;
    yaz << endl;
    for (i = 0; i < yenicbksys; i++)
    {
        Q[i][0] = (cos(Aci[i]) * ((Nt[i] * ((L[i] - at[i]) / L[i])) + (njt[i] * L[i] / 2.0))) - (sin(Aci[i]) * ((Wt[i] * L[i] / 2.0) + ((Pt[i] * pow((L[i] - at[i]), 2.0)) * (3.0 * at[i] + (L[i] - at[i])) / pow(L[i], 3.0))));
        Q[i][1] = (sin(Aci[i]) * ((Nt[i] * ((L[i] - at[i]) / L[i])) + (njt[i] * L[i] / 2.0))) + (cos(Aci[i]) * ((Wt[i] * L[i] / 2.0) + ((Pt[i] * pow((L[i] - at[i]), 2.0)) * (3.0 * at[i] + (L[i] - at[i])) / pow(L[i], 3.0))));
        Q[i][2] = (Wt[i] * pow(L[i], 2.0) / 12.0) + (Pt[i] * at[i] * (pow((L[i] - at[i]), 2.0)) / pow(L[i], 2.0));
        Q[i][3] = (cos(Aci[i]) * ((Nt[i] * (at[i] / L[i])) + (njt[i] * L[i] / 2.0))) - (sin(Aci[i]) * ((Wt[i] * L[i] / 2.0) + (Pt[i] * pow(at[i], 2.0) * (3.0 * (L[i] - at[i]) + at[i]) / pow(L[i], 3.0))));
        Q[i][4] = (sin(Aci[i]) * ((Nt[i] * (at[i] / L[i])) + (njt[i] * L[i] / 2.0))) + (cos(Aci[i]) * ((Wt[i] * L[i] / 2.0) + (Pt[i] * pow(at[i], 2.0) * (3.0 * (L[i] - at[i]) + at[i]) / pow(L[i], 3.0))));
        Q[i][5] = (-Wt[i] * pow(L[i], 2.0) / 12.0) - (Pt[i] * (L[i] - at[i]) * (pow(at[i], 2.0)) / pow(L[i], 2.0));
        for (j = 0; j < 6; j++)
            yaz << fixed << setprecision(6) << setw(12) << Q[i][j] << " ";
        yaz << endl;
    }
    Pj = new double[yenisd];
    if (Pj == NULL)
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < yenisd; i++)
        Pj[i] = 0;
    cout << endl;
    cout << "Yuklu Serbestlik Sayisi = " << endl;
    cin >> yss;
    yaz << endl << "Yuklu Serbestlik Sayýsý = " << yss << endl << endl;
    if (yss == 0)
    {
        cout << endl;
        cout << "Yuklu Serbestlik Yok" << endl;
        yaz << "Yuklu Serbestlik Yok" << endl << endl;
    }
    else
    {
        for (i = 0; i < yss; i++)
        {
            cout << "Serbestlik Numarasi = " << endl;
            cin >> sno;
            cout << "Yuk Degeri = " << endl;
            cin >> Pj[sno - 1];
            yaz << "Serbestlik Numarasý =  " << sno << endl;
            yaz << "Yuk Degeri = " << Pj[sno - 1] << endl << endl;
        }
    }
    cout << endl;
    cout << "Pj Matrisimiz Verilerin Kaydedildigi Cikti Dosyasindadir. " << endl;
    yaz << "Pj Matrisimiz = " << endl;
    yaz << endl;
    for (i = 0; i < yenisd; i++)
        yaz << fixed << setprecision(6) << setw(12) << Pj[i] << endl;
    cout << endl;
    yaz << endl;
    Sj = new double* [6];
    if (Sj == NULL)
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < 6; i++)
    {
        Sj[i] = new double[6];
        if (Sj[i] == NULL)
        {
            cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            system("pause");
            return 0;
        }
    }
    S = new double* [yenisd];
    if (S == NULL)
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < yenisd; i++)
    {
        S[i] = new double[yenisd];
        if (S[i] == NULL)
        {
            cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            system("pause");
            return 0;
        }
    }
    for (i = 0; i < yenisd; i++)
    {
        for (int j = 0; j < yenisd; j++)
            S[i][j] = 0;
    }
    for (i = 0; i < yenicbksys; i++)
    {
        Sj[0][0] = (pow(cos(Aci[i]), 2.0) * (Et[i] * At[i]) / L[i]) + (pow(sin(Aci[i]), 2.0) * (12.0 * Et[i] * It[i]) / pow(L[i], 3.0));
        Sj[0][1] = (sin(Aci[i]) * cos(Aci[i]) * (Et[i] * At[i]) / L[i]) - (sin(Aci[i]) * cos(Aci[i]) * (12.0 * Et[i] * It[i]) / pow(L[i], 3.0));
        Sj[0][2] = -(sin(Aci[i]) * (6.0 * Et[i] * It[i]) / pow(L[i], 2.0));
        Sj[0][3] = -Sj[0][0];
        Sj[0][4] = -Sj[0][1];
        Sj[0][5] = Sj[0][2];
        Sj[1][0] = Sj[0][1];
        Sj[1][1] = (pow(sin(Aci[i]), 2.0) * (Et[i] * At[i]) / L[i]) + (pow(cos(Aci[i]), 2.0) * (12.0 * Et[i] * It[i]) / (pow(L[i], 3.0)));
        Sj[1][2] = (cos(Aci[i]) * (6.0 * Et[i] * It[i]) / pow(L[i], 2.0));
        Sj[1][3] = -Sj[0][1];
        Sj[1][4] = -Sj[1][1];
        Sj[1][5] = Sj[1][2];
        Sj[2][0] = Sj[0][2];
        Sj[2][1] = Sj[1][2];
        Sj[2][2] = (4.0 * Et[i] * It[i] / L[i]);
        Sj[2][3] = -Sj[0][2];
        Sj[2][4] = -Sj[1][2];
        Sj[2][5] = (Sj[2][2]) / 2.0;
        Sj[3][0] = -Sj[0][0];
        Sj[3][1] = -Sj[0][1];
        Sj[3][2] = -Sj[0][2];
        Sj[3][3] = Sj[0][0];
        Sj[3][4] = Sj[0][1];
        Sj[3][5] = -Sj[0][2];
        Sj[4][0] = -Sj[0][1];
        Sj[4][1] = -Sj[1][1];
        Sj[4][2] = -Sj[1][2];
        Sj[4][3] = Sj[0][1];
        Sj[4][4] = Sj[1][1];
        Sj[4][5] = -Sj[1][2];
        Sj[5][0] = Sj[0][2];
        Sj[5][1] = Sj[1][2];
        Sj[5][2] = Sj[2][5];
        Sj[5][3] = -Sj[0][2];
        Sj[5][4] = -Sj[1][2];
        Sj[5][5] = Sj[2][2];
        yaz << i + 1 << ".Sj Matrisi = " << endl;
        yaz << endl;
        for (i1 = 0; i1 < 6; i1++)
        {
            for (j = 0; j < 6; j++)
                yaz << fixed << setprecision(6) << setw(12) << Sj[i1][j] << " ";
            yaz << endl;
        }
        yaz << endl;
        for (int i1 = 0; i1 < 6; i1++)
        {
            for (int j = 0; j < 6; j++)
            {
                int sx = Dj[i][i1];
                int sy = Dj[i][j];
                if (sx == 0) continue;
                if (sy == 0) continue;
                {
                    S[sx - 1][sy - 1] = S[sx - 1][sy - 1] + Sj[i1][j];
                }
            }
        }
    }
    yaz << endl;
    Qj = new double[yenisd];
    if (Qj == NULL)
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < yenisd; i++)
        Qj[i] = 0;
    cout << "Toplanmis S Matrisi Verilerin Kaydedildigi Cikti Dosyasindadir. " << endl;
    yaz << "Toplanmýs S Matrisi = " << endl;
    yaz << endl;
    for (i1 = 0; i1 < yenisd; i1++)
    {
        for (j = 0; j < yenisd; j++)
            yaz << fixed << setprecision(6) << setw(12) << S[i1][j] << " ";
        yaz << endl;
    }
    yaz << endl;
    cout << endl;
    for (i = 0; i < yenicbksys; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            int qx = Dj[i][j];
            if (qx == 0) continue;
            {
                Qj[qx - 1] = Qj[qx - 1] + Q[i][j];
            }
        }
    }
    cout << "Toplanmis Qj Matrisi Verilerin Kaydedildigi Cikti Dosyasindadir. " << endl;
    yaz << "Toplanmýs Qj Matrisi = " << endl;
    yaz << endl;
    for (i = 0; i < yenisd; i++)
        yaz << fixed << setprecision(6) << setw(12) << Qj[i] << endl;
    cout << endl;
    yaz << endl;
    Qt = new double[yenisd];
    if (Qt == NULL)
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    cout << "Sistemin Toplam Yuk Matrisi Verilerin Kaydedildigi Cikti Dosyasindadir. " << endl;
    yaz << "Sistemin Toplam Yuk Matrisi = " << endl;
    yaz << endl;
    for (i = 0; i < yenisd; i++)
    {
        Qt[i] = Pj[i] - Qj[i];
        yaz << fixed << setprecision(6) << setw(12) << Qt[i] << endl;
    }
    cout << endl;
    yaz << endl;

    cout << "Gauss Islemleri Verilerin Kaydedilgi Cikti Dosyasina Yazilsin Mi ?? " << endl << endl;;
    cout << "Evet Icin 1, Hayir Icin 2 Yazin" << endl;
    cin >> gaussevethayir;

    Xizle = new int[yenisd];
    if (Xizle == NULL)
    {
        cout << "Hayy Aksi Bellek Yetersiz" << endl;
        yaz << "Hayy Aksi Bellek Yetersiz" << endl;
        system("pause");
        return 0;
    }
    X = new double[yenisd];
    if (X == NULL)
    {
        cout << "Hayy Aksi Bellek Yetersiz" << endl;
        yaz << "Hayy Aksi Bellek Yetersiz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < yenisd; i++)
        Xizle[i] = i + 1;
    for (i = 0; i < yenisd; i++)
    {
        pivot = S[i][i];
        pivotkol = i;
        for (j = i + 1; j < yenisd; j++)
        {
            if (fabs(pivot) < (fabs(S[i][j])))
            {
                pivot = S[i][j];
                pivotkol = j;
            }
        }
        if (fabs(pivot) <= fabs(pow(10.0, -10.0)))
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cout << "\a\a\a!!! Sistem Labil !!!" << endl;
            yaz << "!!! Sistem Labil !!!" << endl;
            system("pause");
            return 0;
        }
        if (gaussevethayir == 1)
        {
            yaz << fixed << setw(12) << "Pivotumuz = " << pivot << endl;
            yaz << fixed << setw(12) << "Pivot Kolonumuz = " << pivotkol << endl;
            yaz << fixed << setw(12) << "Pivot Kolonumuz Basa Alýndý = " << endl << endl;
        }
        for (j = 0; j < yenisd; j++)
        {
            rep1 = S[j][pivotkol];
            S[j][pivotkol] = S[j][i];
            S[j][i] = rep1;
        }
        if (gaussevethayir == 1)
        {
            for (i1 = 0; i1 < yenisd; i1++)
            {
                for (j = 0; j < yenisd; j++)
                    yaz << fixed << setprecision(6) << setw(12) << S[i1][j];
                yaz << endl;
            }
            yaz << endl;
        }
        rep = Xizle[pivotkol];
        Xizle[pivotkol] = Xizle[i];
        Xizle[i] = rep;
        if (pivot == 0)continue;
        for (j = 0; j < yenisd; j++)
            S[i][j] = S[i][j] / pivot;
        if (gaussevethayir == 1)
        {
            yaz << "Pivota Bolunmus Hali = " << endl << endl;
            for (i1 = 0; i1 < yenisd; i1++)
            {
                for (j = 0; j < yenisd; j++)
                    yaz << fixed << setprecision(6) << setw(12) << S[i1][j];
                yaz << endl;
            }
            yaz << endl;
        }
        Qt[i] = Qt[i] / pivot;
        for (j = i + 1; j < yenisd; j++)
        {
            eksiilecarp = -(S[j][i]);
            Qt[j] = Qt[j] + Qt[i] * eksiilecarp;
            for (j1 = 0; j1 < yenisd; j1++)
                S[j][j1] = S[i][j1] * eksiilecarp + S[j][j1];
        }
        if (gaussevethayir == 1)
        {
            yaz << "Pivotumuzun Altý Sýfýrlandý = " << endl << endl;
            for (i1 = 0; i1 < yenisd; i1++)
            {
                for (j = 0; j < yenisd; j++)
                    yaz << fixed << setprecision(6) << setw(12) << S[i1][j];
                yaz << endl;
            }
            yaz << endl;
        }
    }
    if (gaussevethayir == 1)
    {
        cout << endl << "Ust Ucgen Matrisimiz Verilerin Kaydedildigi Cikti Dosyasindadir. " << endl;
        yaz << "Ust ucgen Matrisimiz = " << endl << endl;
        for (i = 0; i < yenisd; i++)
        {
            for (j = 0; j < yenisd; j++)
                yaz << fixed << setprecision(6) << setw(12) << S[i][j];
            yaz << endl;
        }
        cout << endl;
        yaz << endl;
    }
    if (gaussevethayir == 1)
    {
        cout << "Sistemin Toplam Yuk Matrisinin Islemler Sonucundaki Hali Verilerin Kaydedildigi Cikti Dosyasindadir. " << endl;
        yaz << "Sistemin Toplam Yuk Matrisinin Islemler Sonucundaki Hali = " << endl << endl;
        for (i = 0; i < yenisd; i++)
            yaz << fixed << setprecision(6) << setw(10) << "Qt[" << i + 1 << "]= " << Qt[i] << endl;
        yaz << endl;
    }
    for (i = yenisd - 1; i >= 0; i--)
    {
        Xyeni = Xizle[i];
        X[Xyeni - 1] = Qt[i];
        for (j = yenisd - 1; j >= 0; j--)
            Qt[j] = Qt[j] - S[j][i] * X[Xyeni - 1];
    }
    cout << endl;
    cout << "Sistemin Deplasmanlari = " << endl << endl;
    yaz << "Sistemin Deplasmanlarý = " << endl << endl;
    cout << setw(20) << "U(" << uzunlukbrm << ")";
    cout << setw(9) << "V(" << uzunlukbrm << ")";
    cout << setw(9) << "Teta(" << "Rad)" << endl;
    yaz << setw(20) << "U(" << uzunlukbrm << ")";
    yaz << setw(9) << "V(" << uzunlukbrm << ")";
    yaz << setw(9) << "Teta(" << "Rad)" << endl;
    for (i = 0; i <= 47; i++)
    {
        cout << "-";
        yaz << "-";
    }
    cout << endl;
    yaz << endl;
    for (i = 0; i < yenix; i++)
    {
        if (ut[i] == 0) continue;
        if (vt[i] == 0) continue;
        if (tetat[i] == 0) continue;
    }
    for (i = 0; i < yenix; i++)
    {
        cout << i + 1 << ". Dugum = ";
        yaz << i + 1 << ". Dugum = ";
        cout << fixed << setprecision(6) << setw(12) << X[ut[i] - 1];
        cout << fixed << setprecision(6) << setw(12) << X[vt[i] - 1];
        cout << fixed << setprecision(6) << setw(12) << X[tetat[i] - 1] << endl;
        yaz << fixed << setprecision(6) << setw(12) << X[ut[i] - 1];
        yaz << fixed << setprecision(6) << setw(12) << X[vt[i] - 1];
        yaz << fixed << setprecision(6) << setw(12) << X[tetat[i] - 1] << endl;
    }
    cout << endl;
    yaz << endl;
    Djyeni = new double* [yenicbksys];
    if (Djyeni == NULL)
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < yenicbksys; i++)
    {
        Djyeni[i] = new double[6];
        if (Djyeni[i] == NULL)
        {
            cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            system("pause");
            return 0;
        }
    }
    cout << "DjYeni Matrisi Verilerin Kaydedildigi Cikti Dosyasindadir. " << endl << endl;
    yaz << "DjYeni Matrisi = " << endl;
    yaz << endl;
    for (i = 0; i < yenicbksys; i++)
    {
        for (j = 0; j < 6; j++)
            Djyeni[i][j] = 0;
    }
    for (i = 0; i < yenicbksys; i++)
    {
        for (j = 0; j < 6; j++)
        {
            if (Dj[i][j] == 0) continue;
            Djyeni[i][j] = X[Dj[i][j] - 1];
        }
        for (j = 0; j < 6; j++)
            yaz << fixed << setw(12) << Djyeni[i][j] << " ";
        yaz << endl;
    }
    yaz << endl;
    qussu = new double* [yenicbksys];
    if (qussu == NULL)
    {
        cout << "Hopp Hey Aksi Bellek Yetersizz" << endl;
        yaz << "Hopp Hey Aksi Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < yenicbksys; i++)
    {
        qussu[i] = new double[6];
        if (qussu[i] == NULL)
        {
            cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            system("pause");
            return 0;
        }
    }
    qussucizgi = new double* [yenicbksys];
    if (qussucizgi == NULL)
    {
        cout << "Hopp Hey Aksi Bellek Yetersizz" << endl;
        yaz << "Hopp Hey Aksi Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < yenicbksys; i++)
    {
        qussucizgi[i] = new double[6];
        if (qussucizgi[i] == NULL)
        {
            cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            system("pause");
            return 0;
        }
    }
    qcubuk = new double* [yenicbksys];
    if (qcubuk == NULL)
    {
        cout << "Hopp Hey Aksi Bellek Yetersizz" << endl;
        yaz << "Hopp Hey Aksi Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < yenicbksys; i++)
    {
        qcubuk[i] = new double[6];
        if (qcubuk[i] == NULL)
        {
            cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            system("pause");
            return 0;
        }
    }
    for (i = 0; i < yenicbksys; i++)
    {
        qussucizgi[i][0] = (Nt[i] * (L[i] - at[i]) / L[i]) + (njt[i] * L[i] / 2.0);
        qussucizgi[i][1] = (Wt[i] * L[i] / 2.0) + (Pt[i] * pow((L[i] - at[i]), 2.0) * ((3 * at[i]) + (L[i] - at[i])) / pow(L[i], 3.0));
        qussucizgi[i][2] = (Wt[i] * (pow(L[i], 2.0) / 12.0)) + (Pt[i] * at[i] * pow((L[i] - at[i]), 2.0) / pow(L[i], 2.0));
        qussucizgi[i][3] = (Nt[i] * at[i] / L[i]) + (njt[i] * L[i] / 2.0);
        qussucizgi[i][4] = (Wt[i] * L[i] / 2.0) + (Pt[i] * pow(at[i], 2.0) * ((3 * (L[i] - at[i])) + at[i]) / pow(L[i], 3.0));
        qussucizgi[i][5] = -(Wt[i] * pow(L[i], 2.0) / 12.0) - (Pt[i] * (L[i] - at[i]) * pow(at[i], 2.0) / pow(L[i], 2.0));

        qussu[i][0] = -(At[i] * Et[i] / L[i]) * (((Djyeni[i][3] - Djyeni[i][0]) * cos(Aci[i])) + ((Djyeni[i][4] - Djyeni[i][1]) * sin(Aci[i])));
        qussu[i][1] = -(12.0 * Et[i] * It[i] / pow(L[i], 3.0)) * ((Djyeni[i][4] - Djyeni[i][1]) * cos(Aci[i]) - ((Djyeni[i][3] - Djyeni[i][0]) * sin(Aci[i]))) + ((6.0 * Et[i] * It[i] / pow(L[i], 2.0)) * (Djyeni[i][2] + Djyeni[i][5]));
        qussu[i][2] = -(6.0 * Et[i] * It[i] / pow(L[i], 2.0)) * ((Djyeni[i][4] - Djyeni[i][1]) * cos(Aci[i]) - (Djyeni[i][3] - Djyeni[i][0]) * sin(Aci[i])) + (2.0 * Et[i] * It[i] / L[i]) * (Djyeni[i][2] + Djyeni[i][5]) + (2.0 * Et[i] * It[i] / L[i]) * (Djyeni[i][2]);
        qussu[i][3] = -qussu[i][0];
        qussu[i][4] = -qussu[i][1];
        qussu[i][5] = -(6.0 * Et[i] * It[i] / pow(L[i], 2.0)) * ((Djyeni[i][4] - Djyeni[i][1]) * cos(Aci[i]) - (Djyeni[i][3] - Djyeni[i][0]) * sin(Aci[i])) + (2.0 * Et[i] * It[i] / L[i]) * (Djyeni[i][2] + Djyeni[i][5]) + (2.0 * Et[i] * It[i] / L[i]) * (Djyeni[i][5]);

        qcubuk[i][0] = qussucizgi[i][0] + qussu[i][0];
        qcubuk[i][1] = qussucizgi[i][1] + qussu[i][1];
        qcubuk[i][2] = qussucizgi[i][2] + qussu[i][2];
        qcubuk[i][3] = qussucizgi[i][3] + qussu[i][3];
        qcubuk[i][4] = qussucizgi[i][4] + qussu[i][4];
        qcubuk[i][5] = qussucizgi[i][5] + qussu[i][5];
    }
    cout << "qussucizgi Matrisi Verilerin Kaydedildigi Cikti Dosyasindadir. " << endl << endl;
    yaz << "qussucizgi Matrisi = " << endl;
    yaz << endl;
    for (i = 0; i < yenicbksys; i++)
    {
        for (j = 0; j < 6; j++)
            yaz << fixed << setw(12) << qussucizgi[i][j] << " ";
        yaz << endl;
    }
    yaz << endl;
    cout << "qussu Matrisi Verilerin Kaydedildigi Cikti Dosyasindadir. " << endl << endl;
    yaz << "qussu Matrisi = " << endl;
    yaz << endl;
    for (i = 0; i < yenicbksys; i++)
    {
        for (j = 0; j < 6; j++)
            yaz << fixed << setw(12) << qussu[i][j] << " ";
        yaz << endl;
    }
    yaz << endl;
    cout << "Cubuk Ucu Kuvvetleri =" << endl << endl;
    yaz << "Cubuk Ucu Kuvvetleri =" << endl << endl;
    cout << setw(18) << "Ni" << "(" << kuvvetbrm << ")";
    cout << setw(7) << "Si" << "(" << kuvvetbrm << ")";
    cout << setw(5) << "Mi" << "(" << kuvvetbrm << "x" << uzunlukbrm << ")";
    cout << setw(7) << "Nk" << "(" << kuvvetbrm << ")";
    cout << setw(7) << "Sk" << "(" << kuvvetbrm << ")";
    cout << setw(5) << "Mk" << "(" << kuvvetbrm << "x" << uzunlukbrm << ")" << endl;
    yaz << setw(18) << "Ni" << "(" << kuvvetbrm << ")";
    yaz << setw(7) << "Si" << "(" << kuvvetbrm << ")";
    yaz << setw(5) << "Mi" << "(" << kuvvetbrm << "x" << uzunlukbrm << ")";
    yaz << setw(7) << "Nk" << "(" << kuvvetbrm << ")";
    yaz << setw(7) << "Sk" << "(" << kuvvetbrm << ")";
    yaz << setw(5) << "Mk" << "(" << kuvvetbrm << "x" << uzunlukbrm << ")" << endl;
    for (i = 0; i <= 77; i++)
    {
        cout << "-";
        yaz << "-";
    }
    cout << endl;
    yaz << endl;
    for (i = 0; i < yenicbksys; i++)
    {
        cout << i + 1 << ". Cubuk = ";
        yaz << i + 1 << ". Cubuk = ";
        for (j = 0; j < 6; j++)
        {
            cout << setw(11) << qcubuk[i][j];
            yaz << setw(11) << qcubuk[i][j];
        }
        cout << endl;
        yaz << endl;
    }
    cout << endl;
    yaz << endl;
    yaz.close();
    system("pause");
    return 0;
}
double acibul(double dx, double dy)
{
    double acifonk;
    acifonk = atan(dy / dx);
    if (dx > 0 && dy == 0)
        acifonk = 0;
    if (dx < 0 && dy == 0)
        acifonk = M_PI;
    if (dx == 0 && dy < 0)
        acifonk = 3 * M_PI / 2;
    if (dx == 0 && dy > 0)
        acifonk = M_PI / 2;
    if (dx < 0 && dy>0)
        acifonk = acifonk + M_PI;
    if (dx < 0 && dy < 0)
        acifonk = acifonk + M_PI;
    if (dx > 0 && dy < 0)
        acifonk = acifonk + 2 * M_PI;
    return acifonk;
}