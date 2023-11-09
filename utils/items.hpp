#ifndef UTILS_ITEMS_HPP
#define UTILS_ITEMS_HPP

#include <bits/stdc++.h>

struct Barang
{
    string namaBarang;
    string hargaBarang;
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
    string status;
};

struct NodeTransaksi
{
    BarangCus barang;
    NodeTransaksi *next;
};

struct BarangCheckout
{
    string username;
    string item_names;
    int amount;
    string status;
};

struct NodeCheckout
{
    BarangCheckout barang;
    NodeCheckout *next;
};

#endif