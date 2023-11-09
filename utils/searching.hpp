#ifndef UTILS_SEARCHING_HPP
#define UTILS_SEARCHING_HPP

#include <bits/stdc++.h>
#include "items.hpp"
using namespace std;

//// BM Search ft. posttest 5
//// cara pemakaian lihat di admin.hpp case 98
const int NO_OF_CHARS = 256;

void badCharHeuristic(string str, int size, int badChar[NO_OF_CHARS])
{
    for (int i = 0; i < NO_OF_CHARS; i++)
    {
        badChar[i] = -1;
    }
    for (int i = 0; i < size; i++)
    {
        badChar[(int)str[i]] = i;
    }
}

void searchBM(Node *head, string target)
{
    int m = target.size();
    Node *temp = head;
    while (temp != NULL)
    {
        int n = temp->barang.namaBarang.size();
        int badChar[NO_OF_CHARS];
        badCharHeuristic(target, m, badChar);
        int s = 0;
        while (s <= (n - m))
        {
            int j = m - 1;
            while (j >= 0 && target[j] == temp->barang.namaBarang[s + j])
            {

                j--;
            }
            if (j < 0)
            {
                cout << "Nama  : " << temp->barang.namaBarang << endl;
                cout << "Harga : " << temp->barang.hargaBarang << endl;
                cout << "Fitur : " << temp->barang.fiturBarang << endl;
                cout << "Deskripsi : " << temp->barang.deskripsiBarang << endl;

                break;
            }
            else
            {

                s += max(1, j - badChar[temp->barang.namaBarang[s + j]]);
            }
        }
        temp = temp->next;
    }
}
//// BM Search End

#endif