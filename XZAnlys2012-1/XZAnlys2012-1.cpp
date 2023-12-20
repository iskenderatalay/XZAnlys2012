// XZAnlys2012-1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

#include <fstream>
#include <iomanip>
#include <windows.h> 
#define karakter 100
using namespace std;
int main(int argc, char* argv[])
{

    // n      : Cubuk Sayisi
    // x      : Duðum Sayisi
    // sd     : Serbestlik Sayisi
    // *R     : Refefans Duðum No Vektoru
    // *K     : Referans Olmayan Duðum No Vektoru
    // sno    : Serbestlik Numarasi
    // yss    : Yuklu Seerbestlik Sayisi
    // A      : Alan
    // E      : Elastisite Modulu
    // I      : Atalaet Momenti
    // *Dx    : Duðum Noktasinin X Koordinat Vektoru
    // *Dy    : Duðum Noktasinin Y Koordinat Vektoru
    // *delx  : X Koordinatlari Arasindaki Fark Vektoru
    // *dely  : Y Koordinatlar Arasindaki Fark Vektoru

    int n, i, i1, j, j1, x, * R, * K, sd, * u, * v, * teta, ** Dj, sno, pivotkol, * Xizle, Xyeni, rep, yss, das, dgmno;
    double* A, * E, * I, * Dx, * Dy, * Aci, * AciDugum, * AciDugumRad, * L, * delx, * dely, ** Sj, ** S, * P, * N, * W, * a, ** Q, * Qj, * Qt, * Pj, * X;
    double pivot, eksiilecarp, rep1, ** qussu, ** qussucizgi, ** qcubuk, ** Djyeni;

    double* nu, * poisson, * alfa, * G, * kata, * katb, * katc, * Mj, * nj;

    ofstream yaz;
    ifstream oku;
    char* yazad, * okuad, * uzunlukbrm, * kuvvetbrm;
    yazad = new char[karakter];
    okuad = new char[karakter];
    uzunlukbrm = new char[karakter];
    kuvvetbrm = new char[karakter];
    cout << endl << endl;

    //Aciklama Basla
    for (i = 0; i < 3; i++)   //dikey sayac
    {
        if (i > 0 && i < 2)
        {
            cout << "* Isleme Baslamadan Once                                                    *" << endl;
            cout << "* Program Dosyasinin Bulundugu Yerde Bir Veri Dosyasi Olusturmalisin        *" << endl;
            cout << "* Veri Dosyasinin Yazimi Su Sekilde Olmalidir                               *" << endl;
            cout << "* Ilk Once Cubuk Bilgileri Olan i k A E I Poisson Sekil Faktoru Verileri    *" << endl;
            cout << "* Birinci Cubuk Icin Aralarinda Bosluk Birakilarak Girilmeli,               *" << endl;
            cout << "* Sonra Alt Satira Gecilerek Ayni Islem Diger Cubuklar Icin de Yapilmalidir *" << endl;
            cout << "* Daha Sonra Cubuk Yuk Bilgileri Olan W P N a nj Mj Verileri                *" << endl;
            cout << "* Birinci Cubuk Icin Aralarinda Bosluk Birakilarak Girilmeli,               *" << endl;
            cout << "* Sonra Alt Satira Gecilerek Ayni Islem Diger Cubuklar Icin de Yapilmalidir *" << endl;
            cout << "* Sonraki Islem Olarak Dugum Bilgileri Olan x y u v teta Verileri           *" << endl;
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
    //Aciklama Son

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
    yaz << "Yapilan Ýulemdeki Uzunluk Birimi = " << uzunlukbrm << endl;
    yaz << "Yapilan Ýulemdeki Kuvvet Birimi = " << kuvvetbrm << endl << endl;
    cout << endl << "Cubuk Sayisini Girin " << endl;
    cin >> n;
    yaz << "Cubuk Sayisi = " << n << endl;
    cout << endl << "Dugum Sayisi Girin " << endl;
    cin >> x;
    yaz << "Duðum Sayisi= " << x << endl;
    cout << endl << "Serbestlik Derecesini Girin " << endl;
    cin >> sd;
    yaz << "Serbestlik Derecesi = " << sd << endl;

    R = new int[n];
    K = new int[n];
    A = new double[n];
    E = new double[n];
    I = new double[n];
    L = new double[n];
    delx = new double[n];
    dely = new double[n];
    Aci = new double[n];
    AciDugum = new double[x];
    AciDugumRad = new double[x];
    W = new double[n];
    P = new double[n];
    N = new double[n];
    a = new double[n];

    Mj = new double[n];
    nj = new double[n];

    nu = new double[n];
    alfa = new double[n];
    poisson = new double[n];
    G = new double[n];
    kata = new double[n];
    katb = new double[n];
    katc = new double[n];

    if ((R == NULL) || (K == NULL) || (A == NULL) || (E == NULL) || (I == NULL) || (W == NULL) || (P == NULL) || (N == NULL) || (a == NULL) || (Mj == NULL) || (nj == NULL))
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }

    if ((nu == NULL) || (alfa == NULL) || (poisson == NULL) || (G == NULL) || (kata == NULL) || (katb == NULL) || (katc == NULL))
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
        oku >> poisson[i];
        oku >> alfa[i];
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

    cout << endl;
    yaz << endl;
    cout << "Cubuk Bilgileri = " << endl << endl;
    yaz << "Cubuk Bilgileri = " << endl << endl;
    cout << setw(30) << "Poisson Orani";
    cout << setw(20) << "Sekil Katsayisi" << endl;
    yaz << setw(30) << "Poisson Orani";
    yaz << setw(20) << "Sekil Katsayisi" << endl;
    for (i = 0; i <= 50; i++)
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
        cout << fixed << setprecision(6) << setw(16) << poisson[i];
        cout << fixed << setprecision(6) << setw(19) << alfa[i] << endl;
        yaz << fixed << setprecision(6) << setw(16) << poisson[i];
        yaz << fixed << setprecision(6) << setw(19) << alfa[i] << endl;
    }
    cout << endl << "Cubuk Yuk Bilgileri Olusturdugunuz Veri Dosyasindan Alinacak" << endl;
    for (i = 0; i < n; i++)
    {
        oku >> W[i];
        oku >> P[i];
        oku >> N[i];
        oku >> a[i];
        oku >> nj[i];
        oku >> Mj[i];
    }
    cout << endl;
    yaz << endl;
    cout << "Cubuk Yuk Bilgileri = " << endl << endl;
    yaz << "Cubuk Yuk Bilgileri = " << endl << endl;
    cout << setw(18) << "W(" << kuvvetbrm << "/" << uzunlukbrm << ")";
    cout << setw(9) << "P(" << kuvvetbrm << ")";
    cout << setw(9) << "N(" << kuvvetbrm << ")";
    cout << setw(10) << "a(" << uzunlukbrm << ")";
    cout << setw(10) << "nj(" << kuvvetbrm << "/" << uzunlukbrm << ")";
    cout << setw(10) << "Mj(" << kuvvetbrm << "/" << uzunlukbrm << "^2" << ")" << endl;
    yaz << setw(18) << "W(" << kuvvetbrm << "/" << uzunlukbrm << ")";
    yaz << setw(9) << "P(" << kuvvetbrm << ")";
    yaz << setw(9) << "N(" << kuvvetbrm << ")";
    yaz << setw(10) << "a(" << uzunlukbrm << ")";
    yaz << setw(10) << "nj(" << kuvvetbrm << "/" << uzunlukbrm << ")";
    yaz << setw(10) << "Mj(" << kuvvetbrm << "/" << uzunlukbrm << "^2" << ")" << endl;
    for (i = 0; i <= 59; i++)
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
        cout << fixed << setprecision(6) << setw(12) << nj[i];
        cout << fixed << setprecision(6) << setw(12) << Mj[i] << endl;
        yaz << fixed << setprecision(6) << setw(12) << W[i];
        yaz << fixed << setprecision(6) << setw(12) << P[i];
        yaz << fixed << setprecision(6) << setw(12) << N[i];
        yaz << fixed << setprecision(6) << setw(12) << a[i];
        yaz << fixed << setprecision(6) << setw(12) << nj[i];
        yaz << fixed << setprecision(6) << setw(12) << Mj[i] << endl;

    }
    u = new int[sd];
    v = new int[sd];
    teta = new int[sd];
    Dx = new double[x];
    Dy = new double[x];

    if ((u == NULL) || (v == NULL) || (teta == NULL) || (Dx == NULL) || (Dy == NULL) || (delx == NULL) || (dely == NULL))
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }

    cout << endl << "Dugum Bilgileri Olusturdugunuz Veri Dosyasindan Alinacak" << endl;
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
    yaz << "Duðum Bilgileri = " << endl << endl;
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
        yaz << i + 1 << ". Duðum = ";
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
    cout << "Delta X ve Delta Y Degerleri = " << endl << endl;
    yaz << "Delta X ve Delta Y Deðerleri = " << endl << endl;
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
    for (i = 0; i < n; i++)
    {
        delx[i] = Dx[(K[i] - 1)] - Dx[(R[i] - 1)];
        dely[i] = Dy[(K[i] - 1)] - Dy[(R[i] - 1)];
        cout << i + 1 << ". Cubuk = ";
        yaz << i + 1 << ". Cubuk = ";
        cout << fixed << setprecision(6) << setw(12) << delx[i];
        cout << fixed << setprecision(6) << setw(12) << dely[i] << endl;
        yaz << fixed << setprecision(6) << setw(12) << delx[i];
        yaz << fixed << setprecision(6) << setw(12) << dely[i] << endl;
    }
    if (L == NULL)
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    cout << endl;
    yaz << endl;
    cout << "L Degerleri = " << endl << endl;
    yaz << "L Deðerleri = " << endl << endl;
    for (i = 0; i < n; i++)
    {
        L[i] = sqrt(pow(delx[i], 2) + pow(dely[i], 2));
        cout << fixed << setprecision(6) << setw(10) << "L[" << i + 1 << "]= " << L[i] << " " << uzunlukbrm << endl;
        yaz << fixed << setprecision(6) << setw(10) << "L[" << i + 1 << "]= " << L[i] << " " << uzunlukbrm << endl;
    }
    if ((Aci == NULL) || (AciDugum == NULL) || (AciDugumRad == NULL))
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    cout << endl;
    yaz << endl;
    for (i = 0; i < x; i++)
        AciDugum[i] = 0;
    cout << "Acili Konumdaki Dugum Sayisini Girin = " << endl;
    cin >> das;
    if (das == 0)
    {
        cout << endl;
        cout << "Acili Konumda Dugum Yok" << endl;
        yaz << "Acili Konumda Duðum Yok" << endl;
    }
    else
    {
        for (i = 0; i < das; i++)
        {
            cout << "Dugum Numarasi = " << endl;
            cin >> dgmno;
            cout << "Aci Degeri = " << endl;
            cin >> AciDugum[dgmno - 1];
            yaz << "Duðum Numarasi =  " << dgmno << endl;
            yaz << "Aci Deðeri = " << AciDugum[dgmno - 1] << endl << endl;
        }
    }
    cout << endl;
    yaz << endl;
    cout << "Dugum Acilari Matrisimiz = " << endl;
    yaz << "Duðum Acilari Matrisimiz = " << endl;
    cout << endl;
    yaz << endl;
    for (i = 0; i < x; i++)
        AciDugumRad[i] = AciDugum[i] * M_PI / 180;
    for (i = 0; i < x; i++)
    {
        cout << fixed << setprecision(6) << setw(12) << AciDugumRad[i] << endl;
        yaz << fixed << setprecision(6) << setw(12) << AciDugumRad[i] << endl;
    }
    cout << endl;
    yaz << endl;
    cout << "Aci Degerleri = " << endl << endl;
    yaz << "Aci Deðerleri = " << endl << endl;
    for (i = 0; i < n; i++)
    {
        Aci[i] = atan(dely[i] / delx[i]);
        if (delx[i] > 0 && dely[i] == 0)
            Aci[i] = 0;
        if (delx[i] < 0 && dely[i] == 0)
            Aci[i] = M_PI;
        if (delx[i] == 0 && dely[i] < 0)
            Aci[i] = 3 * M_PI / 2;
        if (delx[i] == 0 && dely[i] > 0)
            Aci[i] = M_PI / 2;
        if (delx[i] < 0 && dely[i]>0)
            Aci[i] = Aci[i] + M_PI;
        if (delx[i] < 0 && dely[i] < 0)
            Aci[i] = Aci[i] + M_PI;
        if (delx[i] > 0 && dely[i] < 0)
            Aci[i] = Aci[i] + 2 * M_PI;
        cout << fixed << setprecision(6) << setw(10) << "Derece Cinsinden Aci[" << i + 1 << "]= " << Aci[i] * 180 / M_PI << endl;
        yaz << fixed << setprecision(6) << setw(10) << "Derece Cinsinden Aci[" << i + 1 << "]= " << Aci[i] * 180 / M_PI << endl;
    }
    Dj = new int* [n];
    if (Dj == NULL)
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < n; i++)
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
    cout << "Dj Matrisi Verilerin Kaydedildigi Cikti Dosyasindadir. " << endl << endl;
    yaz << "Dj Matrisi = " << endl;
    yaz << endl;
    for (i = 0; i < n; i++)
    {
        Dj[i][0] = u[R[i] - 1];
        Dj[i][1] = v[R[i] - 1];
        Dj[i][2] = teta[R[i] - 1];
        Dj[i][3] = u[K[i] - 1];
        Dj[i][4] = v[K[i] - 1];
        Dj[i][5] = teta[K[i] - 1];
        for (j = 0; j < 6; j++)
            yaz << fixed << setw(12) << Dj[i][j] << " ";
        yaz << endl;
    }
    cout << "G ve Nu Degerleri = " << endl << endl;
    yaz << "G ve Nu Deðerleri = " << endl << endl;
    cout << setw(15) << "G" << "(" << kuvvetbrm << "/" << uzunlukbrm << "^2" << ")";
    cout << setw(9) << "Nu" << endl;
    yaz << setw(20) << "G" << "(" << kuvvetbrm << "/" << uzunlukbrm << "^2" << ")";
    yaz << setw(9) << "Nu" << endl;
    for (i = 0; i <= 35; i++)
    {
        cout << "-";
        yaz << "-";
    }
    cout << endl;
    yaz << endl;
    for (i = 0; i < n; i++)
    {
        G[i] = E[i] / (2 + (2 * poisson[i]));
        nu[i] = (alfa[i] * E[i] * I[i]) / (A[i] * G[i] * pow(L[i], 2));
        cout << i + 1 << ". Cubuk = ";
        yaz << i + 1 << ". Cubuk = ";
        cout << fixed << setprecision(6) << setw(12) << G[i];
        cout << fixed << setprecision(6) << setw(12) << nu[i] << endl;
        yaz << fixed << setprecision(6) << setw(12) << G[i];
        yaz << fixed << setprecision(6) << setw(12) << nu[i] << endl;
    }
    cout << endl;
    yaz << endl;
    for (i = 0; i < n; i++)
    {
        kata[i] = (1.0 - (6.0 * nu[i])) / (1.0 + (12.0 * nu[i]));
        katb[i] = (1.0 + (3.0 * nu[i])) / (1.0 + (12.0 * nu[i]));
        katc[i] = 1.0 / (1.0 + (12.0 * nu[i]));
    }
    Q = new double* [n];
    if (Q == NULL)
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < n; i++)
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
    cout << "Q Matrisi Verilerin Kaydedildigi Cikti Dosyasindadir. " << endl << endl;
    yaz << "Q Matrisi = " << endl;
    yaz << endl;
    for (i = 0; i < n; i++)
    {
        Q[i][0] = (cos(Aci[i] - AciDugumRad[R[i] - 1]) * ((N[i] * (L[i] - a[i]) / L[i]) + ((nj[i] * L[i]) / 2.0))) - (sin(Aci[i] - AciDugumRad[R[i] - 1]) * ((W[i] * L[i] / 2.0) + (((P[i] * pow((L[i] - a[i]), 2.0) * ((3.0 * a[i]) + (L[i] - a[i]))) + (12.0 * P[i] * (L[i] - a[i]) * pow(L[i], 2.0) * nu[i])) / (pow(L[i], 3.0) * (1.0 + (12.0 * nu[i])))) - ((6.0 * Mj[i] * a[i] * (L[i] - a[i])) / (pow(L[i], 3.0) * (1.0 + (12.0 * nu[i]))))));
        Q[i][1] = (sin(Aci[i] - AciDugumRad[R[i] - 1]) * ((N[i] * (L[i] - a[i]) / L[i]) + ((nj[i] * L[i]) / 2.0))) + (cos(Aci[i] - AciDugumRad[R[i] - 1]) * ((W[i] * L[i] / 2.0) + (((P[i] * pow((L[i] - a[i]), 2.0) * ((3.0 * a[i]) + (L[i] - a[i]))) + (12.0 * P[i] * (L[i] - a[i]) * pow(L[i], 2.0) * nu[i])) / (pow(L[i], 3.0) * (1.0 + (12.0 * nu[i])))) - ((6.0 * Mj[i] * a[i] * (L[i] - a[i])) / (pow(L[i], 3.0) * (1.0 + (12.0 * nu[i]))))));
        Q[i][2] = ((W[i] * pow(L[i], 2.0)) / 12.0) + (((P[i] * pow((L[i] - a[i]), 2.0) * a[i]) + (P[i] * (L[i] - a[i]) * a[i] * 6.0 * nu[i] * L[i])) / (pow(L[i], 2.0) + (12.0 * pow(L[i], 2.0) * nu[i]))) + (((Mj[i] * (L[i] - a[i])) / pow(L[i], 2.0)) * (((L[i] - (3 * a[i])) + (12.0 * L[i] * nu[i])) / (1.0 + (12.0 * nu[i]))));
        Q[i][3] = (cos(Aci[i] - AciDugumRad[K[i] - 1]) * ((N[i] * a[i] / L[i]) + ((nj[i] * L[i]) / 2.0))) - (sin(Aci[i] - AciDugumRad[K[i] - 1]) * ((W[i] * L[i] / 2.0) + (((P[i] * pow(a[i], 2.0) * ((3.0 * (L[i] - a[i])) + a[i])) + (12.0 * P[i] * (L[i] - a[i]) * pow(L[i], 2.0) * nu[i])) / (pow(L[i], 3.0) * (1.0 + (12.0 * nu[i])))) + ((6.0 * Mj[i] * a[i] * (L[i] - a[i])) / (pow(L[i], 3.0) * (1.0 + (12.0 * nu[i]))))));
        Q[i][4] = (sin(Aci[i] - AciDugumRad[K[i] - 1]) * ((N[i] * a[i] / L[i]) + ((nj[i] * L[i]) / 2.0))) + (cos(Aci[i] - AciDugumRad[K[i] - 1]) * ((W[i] * L[i] / 2.0) + (((P[i] * pow(a[i], 2.0) * ((3.0 * (L[i] - a[i])) + a[i])) + (12.0 * P[i] * (L[i] - a[i]) * pow(L[i], 2.0) * nu[i])) / (pow(L[i], 3.0) * (1.0 + (12.0 * nu[i])))) + ((6.0 * Mj[i] * a[i] * (L[i] - a[i])) / (pow(L[i], 3.0) * (1.0 + (12.0 * nu[i]))))));
        Q[i][5] = (-(W[i] * pow(L[i], 2.0)) / 12.0) - (((P[i] * pow(a[i], 2.0) * (L[i] - a[i])) + (P[i] * (L[i] - a[i]) * a[i] * 6.0 * nu[i] * L[i])) / (pow(L[i], 2.0) + (12.0 * pow(L[i], 2.0) * nu[i]))) + (((Mj[i] * a[i]) / pow(L[i], 2.0)) * ((((3 * a[i]) - (2.0 * L[i])) + (12.0 * L[i] * nu[i])) / (1.0 + (12.0 * nu[i]))));

        for (j = 0; j < 6; j++)
            yaz << fixed << setprecision(6) << setw(12) << Q[i][j] << " ";
        yaz << endl;
    }
    Pj = new double[sd];
    if (Pj == NULL)
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < sd; i++)
    {
        Pj[i] = 0;
    }
    cout << "Yuklu Serbestlik Sayisi = " << endl;
    cin >> yss;
    yaz << endl << "Yuklu Serbestlik Sayisi = " << yss << endl << endl;
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
            yaz << "Serbestlik Numarasi =  " << sno << endl;
            yaz << "Yuk Deðeri = " << Pj[sno - 1] << endl << endl;
        }
    }
    cout << endl;
    cout << "Pj Matrisimiz Verilerin Kaydedildigi Cikti Dosyasindadir. " << endl;
    yaz << "Pj Matrisimiz = " << endl;
    yaz << endl;
    for (i = 0; i < sd; i++)
        yaz << fixed << setprecision(6) << setw(12) << Pj[i] << endl;
    yaz << endl;
    cout << endl;
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
    S = new double* [sd];
    if (S == NULL)
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < sd; i++)
    {
        S[i] = new double[sd];
        if (S[i] == NULL)
        {
            cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
            system("pause");
            return 0;
        }
    }
    for (i = 0; i < sd; i++)
    {
        for (int j = 0; j < sd; j++)
            S[i][j] = 0;
    }
    for (i = 0; i < n; i++)
    {
        Sj[0][0] = (pow(cos(Aci[i] - AciDugumRad[R[i] - 1]), 2.0) * (E[i] * A[i]) / L[i]) + (pow(sin(Aci[i] - AciDugumRad[R[i] - 1]), 2.0) * ((12.0 * E[i] * I[i]) / pow(L[i], 3.0)) * katc[i]);
        Sj[0][1] = (sin(Aci[i] - AciDugumRad[R[i] - 1]) * cos(Aci[i] - AciDugumRad[R[i] - 1]) * (E[i] * A[i]) / L[i]) - (sin(Aci[i] - AciDugumRad[R[i] - 1]) * cos(Aci[i] - AciDugumRad[R[i] - 1]) * ((12.0 * E[i] * I[i]) / pow(L[i], 3.0)) * katc[i]);
        Sj[0][2] = -(sin(Aci[i] - AciDugumRad[R[i] - 1]) * ((6.0 * E[i] * I[i]) / pow(L[i], 2.0)) * katc[i]);
        Sj[0][3] = ((cos(Aci[i] - AciDugumRad[R[i] - 1]) * cos(Aci[i] - AciDugumRad[K[i] - 1])) * (-E[i] * A[i]) / L[i]) - ((sin(Aci[i] - AciDugumRad[R[i] - 1]) * sin(Aci[i] - AciDugumRad[K[i] - 1])) * ((12.0 * E[i] * I[i]) / pow(L[i], 3.0)) * katc[i]);
        Sj[0][4] = ((cos(Aci[i] - AciDugumRad[R[i] - 1]) * sin(Aci[i] - AciDugumRad[K[i] - 1])) * (-E[i] * A[i]) / L[i]) + ((sin(Aci[i] - AciDugumRad[R[i] - 1]) * cos(Aci[i] - AciDugumRad[K[i] - 1])) * ((12.0 * E[i] * I[i]) / pow(L[i], 3.0)) * katc[i]);
        Sj[0][5] = Sj[0][2];
        Sj[1][0] = ((cos(Aci[i] - AciDugumRad[R[i] - 1]) * sin(Aci[i] - AciDugumRad[R[i] - 1])) * (E[i] * A[i]) / L[i]) - ((sin(Aci[i] - AciDugumRad[R[i] - 1]) * cos(Aci[i] - AciDugumRad[R[i] - 1])) * ((12.0 * E[i] * I[i]) / pow(L[i], 3.0)) * katc[i]);
        Sj[1][1] = (pow(sin(Aci[i] - AciDugumRad[R[i] - 1]), 2.0) * (E[i] * A[i]) / L[i]) + (pow(cos(Aci[i] - AciDugumRad[R[i] - 1]), 2.0) * ((12.0 * E[i] * I[i]) / pow(L[i], 3.0)) * katc[i]);
        Sj[1][2] = (cos(Aci[i] - AciDugumRad[R[i] - 1]) * ((6.0 * E[i] * I[i]) / pow(L[i], 2.0)) * katc[i]);
        Sj[1][3] = (-sin(Aci[i] - AciDugumRad[R[i] - 1]) * cos(Aci[i] - AciDugumRad[K[i] - 1]) * (E[i] * A[i]) / L[i]) + (cos(Aci[i] - AciDugumRad[R[i] - 1]) * sin(Aci[i] - AciDugumRad[K[i] - 1]) * ((12.0 * E[i] * I[i]) / pow(L[i], 3.0)) * katc[i]);
        Sj[1][4] = (-sin(Aci[i] - AciDugumRad[R[i] - 1]) * sin(Aci[i] - AciDugumRad[K[i] - 1]) * (E[i] * A[i]) / L[i]) - (cos(Aci[i] - AciDugumRad[R[i] - 1]) * cos(Aci[i] - AciDugumRad[K[i] - 1]) * ((12.0 * E[i] * I[i]) / pow(L[i], 3.0)) * katc[i]);
        Sj[1][5] = Sj[1][2];
        Sj[2][0] = Sj[0][2];
        Sj[2][1] = Sj[1][5];
        Sj[2][2] = (4.0 * E[i] * I[i] / L[i]) * katb[i];
        Sj[2][3] = (sin(Aci[i] - AciDugumRad[K[i] - 1]) * ((6.0 * E[i] * I[i]) / pow(L[i], 2.0)) * katc[i]);
        Sj[2][4] = -(cos(Aci[i] - AciDugumRad[K[i] - 1]) * ((6.0 * E[i] * I[i]) / pow(L[i], 2.0)) * katc[i]);
        Sj[2][5] = (2.0 * E[i] * I[i] / L[i]) * kata[i];
        Sj[3][0] = (-cos(Aci[i] - AciDugumRad[K[i] - 1]) * cos(Aci[i] - AciDugumRad[R[i] - 1]) * (E[i] * A[i]) / L[i]) - (sin(Aci[i] - AciDugumRad[K[i] - 1]) * sin(Aci[i] - AciDugumRad[R[i] - 1]) * ((12.0 * E[i] * I[i]) / pow(L[i], 3.0)) * katc[i]);
        Sj[3][1] = (-cos(Aci[i] - AciDugumRad[K[i] - 1]) * sin(Aci[i] - AciDugumRad[R[i] - 1]) * (E[i] * A[i]) / L[i]) + (sin(Aci[i] - AciDugumRad[K[i] - 1]) * cos(Aci[i] - AciDugumRad[R[i] - 1]) * ((12.0 * E[i] * I[i]) / pow(L[i], 3.0)) * katc[i]);
        Sj[3][2] = (sin(Aci[i] - AciDugumRad[K[i] - 1]) * ((6.0 * E[i] * I[i]) / pow(L[i], 2.0)) * (1.0 / (1.0 + (12 * nu[i]))));
        Sj[3][3] = (pow(cos(Aci[i] - AciDugumRad[K[i] - 1]), 2.0) * (E[i] * A[i]) / L[i]) + (pow(sin(Aci[i] - AciDugumRad[K[i] - 1]), 2.0) * ((12.0 * E[i] * I[i]) / pow(L[i], 3.0)) * (1.0 / (1.0 + (12 * nu[i]))));
        Sj[3][4] = (cos(Aci[i] - AciDugumRad[K[i] - 1]) * sin(Aci[i] - AciDugumRad[K[i] - 1]) * (E[i] * A[i]) / L[i]) - (sin(Aci[i] - AciDugumRad[K[i] - 1]) * cos(Aci[i] - AciDugumRad[K[i] - 1]) * ((12.0 * E[i] * I[i]) / pow(L[i], 3.0)) * katc[i]);
        Sj[3][5] = Sj[3][2];
        Sj[4][0] = (-sin(Aci[i] - AciDugumRad[K[i] - 1]) * cos(Aci[i] - AciDugumRad[R[i] - 1]) * (E[i] * A[i]) / L[i]) + (cos(Aci[i] - AciDugumRad[K[i] - 1]) * sin(Aci[i] - AciDugumRad[R[i] - 1]) * ((12.0 * E[i] * I[i]) / pow(L[i], 3.0)) * katc[i]);
        Sj[4][1] = (-sin(Aci[i] - AciDugumRad[K[i] - 1]) * sin(Aci[i] - AciDugumRad[R[i] - 1]) * (E[i] * A[i]) / L[i]) - (cos(Aci[i] - AciDugumRad[K[i] - 1]) * cos(Aci[i] - AciDugumRad[R[i] - 1]) * ((12.0 * E[i] * I[i]) / pow(L[i], 3.0)) * katc[i]);
        Sj[4][2] = -(cos(Aci[i] - AciDugumRad[K[i] - 1]) * ((6.0 * E[i] * I[i]) / pow(L[i], 2.0)) * katc[i]);
        Sj[4][3] = (sin(Aci[i] - AciDugumRad[K[i] - 1]) * cos(Aci[i] - AciDugumRad[K[i] - 1]) * (E[i] * A[i]) / L[i]) - (sin(Aci[i] - AciDugumRad[K[i] - 1]) * cos(Aci[i] - AciDugumRad[K[i] - 1]) * ((12.0 * E[i] * I[i]) / pow(L[i], 3.0)) * katc[i]);
        Sj[4][4] = (pow(sin(Aci[i] - AciDugumRad[K[i] - 1]), 2.0) * (E[i] * A[i]) / L[i]) + (pow(cos(Aci[i] - AciDugumRad[K[i] - 1]), 2.0) * ((12.0 * E[i] * I[i]) / pow(L[i], 3.0)) * katc[i]);
        Sj[4][5] = Sj[4][2];
        Sj[5][0] = Sj[0][2];
        Sj[5][1] = Sj[1][2];
        Sj[5][2] = Sj[2][5];
        Sj[5][3] = Sj[2][3];
        Sj[5][4] = Sj[4][2];
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
    Qj = new double[sd];
    if (Qj == NULL)
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < sd; i++)
        Qj[i] = 0;
    cout << "Toplanmis S Matrisi Verilerin Kaydedildigi Cikti Dosyasindadir. " << endl;
    yaz << "Toplanmis S Matrisi = " << endl;
    yaz << endl;
    for (i1 = 0; i1 < sd; i1++)
    {
        for (j = 0; j < sd; j++)
            yaz << fixed << setprecision(6) << setw(12) << S[i1][j] << " ";
        yaz << endl;
    }
    yaz << endl;
    cout << endl;
    for (i = 0; i < n; i++)
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
    yaz << "Toplanmis Qj Matrisi = " << endl;
    yaz << endl;
    for (i = 0; i < sd; i++)
        yaz << fixed << setprecision(6) << setw(12) << Qj[i] << endl;
    yaz << endl;
    cout << endl;
    Qt = new double[sd];
    if (Qt == NULL)
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    cout << "Sistemin Toplam Yuk Matrisi Kaydedildigi Cikti Dosyasindadir. " << endl;
    yaz << "Sistemin Toplam Yuk Matrisi = " << endl;
    yaz << endl;
    for (i = 0; i < sd; i++)
    {
        Qt[i] = Pj[i] - Qj[i];
        yaz << fixed << setprecision(6) << setw(12) << Qt[i] << endl;
    }
    yaz << endl;
    cout << endl;
    Xizle = new int[sd];
    if (Xizle == NULL)
    {
        cout << "Hayy Aksi Bellek Yetersiz" << endl;
        yaz << "Hayy Aksi Bellek Yetersiz" << endl;
        system("pause");
        return 0;
    }
    X = new double[sd];
    if (X == NULL)
    {
        cout << "Hayy Aksi Bellek Yetersiz" << endl;
        yaz << "Hayy Aksi Bellek Yetersiz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < sd; i++)
        Xizle[i] = i + 1;
    for (i = 0; i < sd; i++)
    {
        pivot = S[i][i];
        pivotkol = i;
        for (j = i + 1; j < sd; j++)
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
        yaz << fixed << setw(12) << "Pivotumuz = " << pivot << endl;
        yaz << fixed << setw(12) << "Pivot Kolonumuz = " << pivotkol << endl;
        yaz << fixed << setw(12) << "Pivot Kolonumuz Basa Alindi = " << endl << endl;
        for (j = 0; j < sd; j++)
        {
            rep1 = S[j][pivotkol];
            S[j][pivotkol] = S[j][i];
            S[j][i] = rep1;
        }
        for (i1 = 0; i1 < sd; i1++)
        {
            for (j = 0; j < sd; j++)
                yaz << fixed << setprecision(6) << setw(12) << S[i1][j];
            yaz << endl;
        }
        yaz << endl;
        rep = Xizle[pivotkol];
        Xizle[pivotkol] = Xizle[i];
        Xizle[i] = rep;
        if (pivot == 0)continue;
        yaz << "Pivota Bolunmus Hali = " << endl << endl;
        for (j = 0; j < sd; j++)
            S[i][j] = S[i][j] / pivot;
        for (i1 = 0; i1 < sd; i1++)
        {
            for (j = 0; j < sd; j++)
                yaz << fixed << setprecision(6) << setw(12) << S[i1][j];
            yaz << endl;
        }
        yaz << endl;
        Qt[i] = Qt[i] / pivot;
        for (j = i + 1; j < sd; j++)
        {
            eksiilecarp = -(S[j][i]);
            Qt[j] = Qt[j] + Qt[i] * eksiilecarp;
            for (j1 = 0; j1 < sd; j1++)
                S[j][j1] = S[i][j1] * eksiilecarp + S[j][j1];
        }
        yaz << "Pivotumuzun Alti Sifirlandi = " << endl << endl;
        for (i1 = 0; i1 < sd; i1++)
        {
            for (j = 0; j < sd; j++)
                yaz << fixed << setprecision(6) << setw(12) << S[i1][j];
            yaz << endl;
        }
        yaz << endl;
    }
    cout << "Ust Ucgen Matrisimiz Verilerin Kaydedildigi Cikti Dosyasindadir. " << endl;
    yaz << "Ust ucgen Matrisimiz = " << endl << endl;
    for (i = 0; i < sd; i++)
    {
        for (j = 0; j < sd; j++)
            yaz << fixed << setprecision(6) << setw(12) << S[i][j];
        yaz << endl;
    }
    cout << endl;
    yaz << endl;
    cout << "Sistemin Toplam Yuk Matrisinin Islemler Sonucundaki Hali Verilerin Kaydedildigi Cikti Dosyasindadir. " << endl;
    yaz << "Sistemin Toplam Yuk Matrisinin Islemler Sonucundaki Hali = " << endl << endl;
    for (i = 0; i < sd; i++)
        yaz << fixed << setprecision(6) << setw(10) << "Qt[" << i + 1 << "]= " << Qt[i] << endl;
    yaz << endl;
    for (i = sd - 1; i >= 0; i--)
    {
        Xyeni = Xizle[i];
        X[Xyeni - 1] = Qt[i];
        for (j = sd - 1; j >= 0; j--)
            Qt[j] = Qt[j] - S[j][i] * X[Xyeni - 1];
    }
    cout << endl;
    cout << "Sistemin Deplasmanlari = " << endl << endl;
    yaz << "Sistemin Deplasmanlari = " << endl << endl;
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
    for (i = 0; i < x; i++)
    {
        if (u[i] == 0) continue;
        if (v[i] == 0) continue;
        if (teta[i] == 0) continue;
    }
    for (i = 0; i < x; i++)
    {
        cout << i + 1 << ". Dugum = ";
        yaz << i + 1 << ". Duðum = ";
        cout << fixed << setprecision(6) << setw(12) << X[u[i] - 1];
        cout << fixed << setprecision(6) << setw(12) << X[v[i] - 1];
        cout << fixed << setprecision(6) << setw(12) << X[teta[i] - 1] << endl;
        yaz << fixed << setprecision(6) << setw(12) << X[u[i] - 1];
        yaz << fixed << setprecision(6) << setw(12) << X[v[i] - 1];
        yaz << fixed << setprecision(6) << setw(12) << X[teta[i] - 1] << endl;
    }
    cout << endl;
    yaz << endl;
    Djyeni = new double* [n];
    if (Djyeni == NULL)
    {
        cout << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        yaz << "Hopp Hay Aksii Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < n; i++)
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
    cout << "DjYeni Matrisi Kaydedildigi Cikti Dosyasindadir. " << endl << endl;
    yaz << "DjYeni Matrisi = " << endl;
    yaz << endl;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 6; j++)
            Djyeni[i][j] = 0;
    }
    for (i = 0; i < n; i++)
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
    qussu = new double* [n];
    if (qussu == NULL)
    {
        cout << "Hopp Hey Aksi Bellek Yetersizz" << endl;
        yaz << "Hopp Hey Aksi Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < n; i++)
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
    qussucizgi = new double* [n];
    if (qussucizgi == NULL)
    {
        cout << "Hopp Hey Aksi Bellek Yetersizz" << endl;
        yaz << "Hopp Hey Aksi Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < n; i++)
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
    qcubuk = new double* [n];
    if (qcubuk == NULL)
    {
        cout << "Hopp Hey Aksi Bellek Yetersizz" << endl;
        yaz << "Hopp Hey Aksi Bellek Yetersizz" << endl;
        system("pause");
        return 0;
    }
    for (i = 0; i < n; i++)
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
    for (i = 0; i < n; i++)
    {
        qussucizgi[i][0] = (N[i] * (L[i] - a[i]) / L[i]) + ((nj[i] * L[i]) / 2.0);
        qussucizgi[i][1] = (W[i] * L[i] / 2.0) + (((P[i] * pow((L[i] - a[i]), 2.0) * ((3.0 * a[i]) + (L[i] - a[i]))) + (12.0 * P[i] * (L[i] - a[i]) * pow(L[i], 2.0) * nu[i])) / (pow(L[i], 3.0) * (1.0 + (12.0 * nu[i])))) - ((6.0 * Mj[i] * a[i] * (L[i] - a[i])) / (pow(L[i], 3.0) * (1.0 + (12.0 * nu[i]))));
        qussucizgi[i][2] = ((W[i] * pow(L[i], 2.0)) / 12.0) + (((P[i] * pow((L[i] - a[i]), 2.0) * a[i]) + (P[i] * (L[i] - a[i]) * a[i] * 6.0 * nu[i] * L[i])) / (pow(L[i], 2.0) + (12.0 * pow(L[i], 2.0) * nu[i]))) + (((Mj[i] * (L[i] - a[i])) / pow(L[i], 2.0)) * (((L[i] - (3 * a[i])) + (12.0 * L[i] * nu[i])) / (1.0 + (12.0 * nu[i]))));
        qussucizgi[i][3] = (N[i] * a[i] / L[i]) + ((nj[i] * L[i]) / 2.0);
        qussucizgi[i][4] = (W[i] * L[i] / 2.0) + (((P[i] * pow(a[i], 2.0) * ((3.0 * (L[i] - a[i])) + a[i])) + (12.0 * P[i] * (L[i] - a[i]) * pow(L[i], 2.0) * nu[i])) / (pow(L[i], 3.0) * (1.0 + (12.0 * nu[i])))) + ((6.0 * Mj[i] * a[i] * (L[i] - a[i])) / (pow(L[i], 3.0) * (1.0 + (12.0 * nu[i]))));
        qussucizgi[i][5] = (-(W[i] * pow(L[i], 2.0)) / 12.0) - (((P[i] * pow(a[i], 2.0) * (L[i] - a[i])) + (P[i] * (L[i] - a[i]) * a[i] * 6.0 * nu[i] * L[i])) / (pow(L[i], 2.0) + (12.0 * pow(L[i], 2.0) * nu[i]))) + (((Mj[i] * a[i]) / pow(L[i], 2.0)) * ((((3 * a[i]) - (2.0 * L[i])) + (12.0 * L[i] * nu[i])) / (1.0 + (12.0 * nu[i]))));

        qussu[i][0] = ((A[i] * E[i]) / L[i]) * ((cos(Aci[i] - AciDugumRad[R[i] - 1]) * Djyeni[i][0]) + (sin(Aci[i] - AciDugumRad[R[i] - 1]) * Djyeni[i][1]) - (cos(Aci[i] - AciDugumRad[K[i] - 1]) * Djyeni[i][3]) - (sin(Aci[i] - AciDugumRad[K[i] - 1]) * Djyeni[i][4]));
        qussu[i][1] = (katc[i] * ((12.0 * E[i] * I[i]) / pow(L[i], 3.0))) * ((-sin(Aci[i] - AciDugumRad[R[i] - 1]) * Djyeni[i][0]) + (cos(Aci[i] - AciDugumRad[R[i] - 1]) * Djyeni[i][1]) + (sin(Aci[i] - AciDugumRad[K[i] - 1]) * Djyeni[i][3]) - (cos(Aci[i] - AciDugumRad[K[i] - 1]) * Djyeni[i][4])) + ((katc[i] * ((6.0 * E[i] * I[i]) / pow(L[i], 2.0))) * (Djyeni[i][2] + Djyeni[i][5]));
        qussu[i][2] = (katc[i] * ((6.0 * E[i] * I[i]) / pow(L[i], 2.0))) * ((-sin(Aci[i] - AciDugumRad[R[i] - 1]) * Djyeni[i][0]) + (cos(Aci[i] - AciDugumRad[R[i] - 1]) * Djyeni[i][1]) + (sin(Aci[i] - AciDugumRad[K[i] - 1]) * Djyeni[i][3]) - (cos(Aci[i] - AciDugumRad[K[i] - 1]) * Djyeni[i][4])) + (katb[i] * ((4 * E[i] * I[i]) / L[i]) * Djyeni[i][2]) + (kata[i] * ((2 * E[i] * I[i]) / L[i]) * Djyeni[i][5]);
        qussu[i][3] = -qussu[i][0];
        qussu[i][4] = -qussu[i][1];
        qussu[i][5] = (katc[i] * ((6.0 * E[i] * I[i]) / pow(L[i], 2.0))) * ((-sin(Aci[i] - AciDugumRad[R[i] - 1]) * Djyeni[i][0]) + (cos(Aci[i] - AciDugumRad[R[i] - 1]) * Djyeni[i][1]) + (sin(Aci[i] - AciDugumRad[K[i] - 1]) * Djyeni[i][3]) - (cos(Aci[i] - AciDugumRad[K[i] - 1]) * Djyeni[i][4])) + (katb[i] * (4 * E[i] * I[i] / L[i]) * Djyeni[i][5]) + (kata[i] * ((2 * E[i] * I[i]) / L[i]) * Djyeni[i][2]);

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
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 6; j++)
            yaz << fixed << setw(12) << qussucizgi[i][j] << " ";
        yaz << endl;
    }
    yaz << endl;
    cout << "qussu Matrisi Verilerin Kaydedildigi Cikti Dosyasindadir. " << endl << endl;
    yaz << "qussu Matrisi = " << endl;
    yaz << endl;
    for (i = 0; i < n; i++)
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
    for (i = 0; i < n; i++)
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