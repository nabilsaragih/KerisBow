#ifndef UTILS_CUSTOMER_HPP
#define UTILS_CUSTOMER_HPP

#include <bits/stdc++.h>
#include "additional.hpp"
#include "items.hpp"

using namespace std;

void loadFromFile(Node **headParam) {
    ifstream dataNode("db/items.tsv");
    dataNode.open("db/items.tsv");
    if (!dataNode.is_open()) {
        cout << "Gagal membuka file items.tsv" << endl;
        return;
    }
    string line, nama, harga, fitur, deskripsi;
    // getline(dataNode, line);
    while (getline(dataNode, line)) {
        stringstream ss(line);
        getline(ss, nama, '\t');
        getline(ss, harga, '\t');
        getline(ss, fitur, '\t');
        getline(ss, deskripsi, '\t');

        Node *barang = new Node;
        barang->barang.namaBarang = nama;
        barang->barang.hargaBarang = stoll(harga);
        barang->barang.fiturBarang = fitur;
        barang->barang.deskripsiBarang = deskripsi;
        barang->next = nullptr;

        if (*headParam == nullptr) {
            *headParam = barang;
        } else {
            Node *temp = *headParam;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = barang;
        }
    }
    dataNode.close();
}

// DisplayData
void displayData(Node* head) {
    if (head == NULL) {
        cout << "Tidak ada barang" << endl;
        cout << "Silahkan tambah barang terlebih dahulu" << endl;
        return;
    }
    Node* temp = head;
    int no = 0;
    while (temp != nullptr) {
        cout << "Nama Barang: " << temp->barang.namaBarang << endl;
        cout << "Harga Barang: " << temp->barang.hargaBarang << endl;
        cout << "Fitur Barang: " << temp->barang.fiturBarang << endl;
        cout << "Deskripsi Barang: " << temp->barang.deskripsiBarang << endl;
        cout << endl;
        no++;
        temp = temp->next;
    }
}

void menuCustomer(int *pilih, Node *headParam)
{
    string pilihanTemp;

    system("cls");
    cout << "Selamat datang di menu admin" << endl;
    cout << "1. Tambah Barang" << endl;
    cout << "2. Lihat Barang" << endl;
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
            displayData(headParam);
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