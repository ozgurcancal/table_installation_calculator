
// ges project.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "my_table/table.h"

using namespace std;

int main()
{
     Table table1;
//   Table table1(700,710);
//   Table table1{900,901,902.0,903.0,904.0,905.0,906.0,907.0};

    //you can assign y_axis(surface altitudes) elements manually
    table1.y_points[2] = 950.0;
    table1.y_points[5] = 950.0;

    table1.run();
   
}

//Algoritma şu şekilde ilerlemektedir:

//önce arazideki kabul edilemez yükseklikleri sil 
//arazinin bu haliyle olabilecek en düzgün lineer doğruyu ve bu doğrunun eğimini bul
//bulunan eğime uygun bir şekilde silenen aykırı değerlerin yerine yeni değerler ekle
//bacak boylarını ve eklenip çıkarılacak toprak miktarını lineer doğru ile üretilen rastgele yüzeyin farkını alarak bul.
//bacak boyu min 0.78cm max 0.118 cm optimum 0.98 cm



