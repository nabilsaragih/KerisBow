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

struct BarangCus
{
    string username;
    string item_names;
    int amount;
};

struct NodeTransaksi
{
    BarangCus barang;
    NodeTransaksi *next;
};

#endif