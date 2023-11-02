#ifndef UTILS_ADMIN_HPP
#define UTILS_ADMIN_HPP

#include <bits/stdc++.h>
#include "items.hpp"
#include "additional.hpp"
using namespace std;

// void addFirst(Node *headParam)
// {
//     string namaBarang, hargaBarang, fiturBarang, deskripsiBarang;
//     Node *newNode = new Node;

// cout << "Nama Barang: ";
// getline(cin, namaBarang);
// fflush(stdin);
// cout << "Harga Barang: ";
// getline(cin, hargaBarang);
// fflush(stdin);
// cout << "Fitur Barang: ";
// getline(cin, fiturBarang);
// fflush(stdin);
// cout << "Deskripsi Barang: ";
// getline(cin, deskripsiBarang);
// fflush(stdin);

//     try
//     {
//         newNode->barang.namaBarang = namaBarang;
//         newNode->barang.hargaBarang = stoll(hargaBarang);
//         newNode->barang.fiturBarang = fiturBarang;
//         newNode->barang.deskripsiBarang = deskripsiBarang;
//     }
// catch (invalid_argument &e)
// {
//     cout << "Masukkan input dengan benar" << endl;
//         endOfFunction(1);
//     }

// if (headParam == nullptr)
// {
//     newNode->next = nullptr;
//     headParam = newNode;

//     system("cls");
//     cout << "Barang berhasil ditambahkan" << endl;
// }
// else
// {
//     newNode->next = headParam;
//     headParam = newNode;

//     system("cls");
//     cout << "Barang berhasil ditambahkan" << endl;
// }
// }

void addFirst(Node *headParam)
{
    ofstream fileStream("db/items.tsv", ios::app);
    string line, namaBarang, hargaBarang, fiturBarang, deskripsiBarang;

    Node *newNode = new Node;
    Node *temp = headParam;

    cout << "Nama Barang: ";
    getline(cin, namaBarang);
    fflush(stdin);
    cout << "Harga Barang: ";
    getline(cin, hargaBarang);
    fflush(stdin);
    cout << "Fitur Barang: ";
    getline(cin, fiturBarang);
    fflush(stdin);
    cout << "Deskripsi Barang: ";
    getline(cin, deskripsiBarang);
    fflush(stdin);

    try
    {
        fileStream << namaBarang << '\t' << hargaBarang << '\t' << fiturBarang << '\t' << deskripsiBarang << '\n';
    }
    catch (invalid_argument &e)
    {
        cout << "Masukkan input dengan benar" << endl;
        endOfFunction(1);
    }

    if (headParam == nullptr)
    {
        newNode->next = nullptr;
        headParam = newNode;

        system("cls");
        cout << "Barang berhasil ditambahkan" << endl;
    }
    else
    {
        newNode->next = headParam;
        headParam = newNode;

        system("cls");
        cout << "Barang berhasil ditambahkan" << endl;
    }
    fileStream.close();
}

void deleteFirst(Node *headParam)
{
    Node *temp = headParam;
    headParam = headParam->next;
    delete temp;

    system("cls");
    cout << "Barang berhasil dihapus" << endl;
}

void menuAdmin(int *pilih, Node *headParam)
{
    string pilihanTemp;

    system("cls");
    cout << "Selamat datang di menu admin" << endl;
    cout << "1. Tambah Barang" << endl;
    cout << "2. Lihat Barang" << endl;
    cout << "3. Ubah Barang" << endl;
    cout << "4. Hapus Barang" << endl;
    cout << "5. Tambah Admin (Prototype)" << endl;
    cout << "Masukkan pilihan anda: ";
    cin >> pilihanTemp;
    fflush(stdin);

    try
    {
        *pilih = stoi(pilihanTemp);
        switch (*pilih)
        {
        case 1:
            system("cls");
            addFirst(headParam);
            endOfFunction(1);
            break;
        case 2:
            system("cls");
            cout << "Lihat Barang" << endl;
            endOfFunction(1);
            break;
        case 3:
            system("cls");
            cout << "Ubah Barang" << endl;
            endOfFunction(1);
            break;
        case 4:
            system("cls");
            deleteFirst(headParam);
            endOfFunction(1);
            break;
        case 5:
            system("cls");
            cout << "Tambah Admin" << endl;
            endOfFunction(1);
            break;

        default:
            cout << "Pilihan tidak tersedia" << endl;
            endOfFunction(1);
            break;
        }
    }
    catch (invalid_argument &e)
    {
        cout << "Pilihan tidak tersedia" << endl;
        endOfFunction(1);
    }
}

#endif