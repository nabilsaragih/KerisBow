#ifndef UTILS_ITEMS_HPP
#define UTILS_ITEMS_HPP

#include <bits/stdc++.h>

struct Barang
{
    string namaBarang;
    long long hargaBarang;
    string fiturBarang;
    string deskripsiBarang;
};

struct Node
{
    Barang barang;
    Node *next;
};

#endif