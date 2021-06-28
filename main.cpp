// ges project.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "my_table/table.h"

using namespace std;

int main()
{
    Table table1;
  
    table1.generate_random_floor(900, 910);

    //you can assign y_axis(surface altitudes) elements manually
    table1.y_axis[2] = 950.0;

    table1.run();
   
}

//Algoritma şu şekilde ilerlemektedir:

//önce arazideki kabul edilemez yükseklikleri sil 
//arazinin bu haliyle olabilecek en düzgün lineer doğruyu ve bu doğrunun eğimini bul
//bulunan eğime uygun bir şekilde silenen aykırı değerlerin yerine yeni değerler ekle
//bacak boylarını ve eklenip çıkarılacak toprak miktarını lineer doğru ile üretilen rastgele yüzeyin farkını alarak bul.
//bacak boyu min 0.78cm max 0.118 cm optimum 0.98 cm


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
    //for (auto it = begin(ivec); it != end(ivec); ++it) {
    //    
    //}


/*
    opengl ile canlandurma yap : bir düzlem oluştur altta kalanlar kırmızı olsun

*/