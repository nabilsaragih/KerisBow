#ifndef UTILS_CUSTOMER_HPP
#define UTILS_CUSTOMER_HPP

#include <bits/stdc++.h>
#include <conio.h>
#include "additional.hpp"
#include "items.hpp"

using namespace std;
void menuCustomer(Node *headParam);
void saveToFile(Node *headParam);

//adLast
void addLast(Node **headParam) {
    string namaBarang, hargaBarang, fiturBarang, deskripsiBarang;
    Node *newNode = new Node;

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

    try {
        newNode->barang.namaBarang = namaBarang;
        newNode->barang.hargaBarang = stoll(hargaBarang);
        newNode->barang.fiturBarang = fiturBarang;
        newNode->barang.deskripsiBarang = deskripsiBarang;
    } catch (invalid_argument &e) {
        cout << "Masukkan input dengan benar" << endl;
        menuCustomer(*headParam);
    }

    if (*headParam == nullptr) {
        newNode->next = nullptr;
        *headParam = newNode;

    } else {
        Node *temp = *headParam;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = nullptr;
    }
    saveToFile(*headParam);
    system("cls");
        cout << "Barang berhasil ditambahkan" << endl; getch;
        menuCustomer(*headParam);
}


// DeleteFirst
void deleteFirst(Node **headParam) {
    Node *temp = *headParam;
    if (temp == nullptr) {
        cout << "Tidak ada barang" << endl;
        cout << "Silahkan tambah barang terlebih dahulu" << endl;
        return;
    } else {
        *headParam = temp->next;
        delete temp;
        cout << "Barang berhasil dihapus" << endl;
    }
    saveToFile(*headParam);
}

void saveToFile(Node *head){
    ofstream DataNode;
    DataNode.open("db/items.tsv");
    Node *temp = head;
    while (temp != NULL){
        DataNode << temp->barang.namaBarang << "\t" 
        << temp->barang.hargaBarang << "\t"
         << temp->barang.fiturBarang << "\t" 
         << temp->barang.deskripsiBarang<< "\t" << endl;
        temp = temp->next;
    }
    DataNode.close();
}

//LoadFrom File
void loadFromFile(Node **headParam) {
    ifstream dataNode("db/items.tsv");
    if (!dataNode.is_open()) {
        cout << "Gagal membuka file items.tsv" << endl;
        return;
    }

    string line, nama, harga, fitur, deskripsi;
    while (getline(dataNode, line)) {
        stringstream ss(line);
        if (getline(ss, nama, '\t') &&
            getline(ss, harga, '\t') &&
            getline(ss, fitur, '\t') &&
            getline(ss, deskripsi, '\t')) {

            try {
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
            } catch (const std::invalid_argument& e) {
                cout << "Kesalahan: Konversi harga gagal. Data dilewati." << endl;
            }
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
    cout << "TAMPILAN MASIH BURIK !!, NEXT KUPERBAIKI (~Agus)" << endl;
}

void menuCustomer(Node *headParam)
{
    string pilihanTemp; int pilih;

    system("cls");
    cout << "Selamat datang di menu admin" << endl;
    cout << "1. Tambah Barang" << endl;
    cout << "2. Lihat Barang" << endl;
    cout << "3. Ubah Barang (Coming Soon)" << endl;
    cout << "4. Hapus Barang" << endl;
    cout << "0. Keluar" << endl;
    cout << "Masukkan pilihan anda: ";
    cin >> pilihanTemp;
    fflush(stdin);

    try
    {
        pilih = stoi(pilihanTemp);
        switch (pilih)
        {
        case 1:
            system("cls");
            addLast(&headParam);
            menuCustomer(headParam);
            break;
        case 2:
            system("cls");
            displayData(headParam);
            cout<<"\nTekan Enter untuk kembali ke menu";getch();cout<<endl;
            menuCustomer(headParam);
            break;
        case 3:
            system("cls");
            cout << "Ubah Barang" << endl;
            menuCustomer(headParam);
            break;
        case 4:
            system("cls");
            deleteFirst(&headParam);
            menuCustomer(headParam);
            break;
        case 0:
            cout << "Terima kasih telah menggunakan KerisBow" << endl;
            endOfFunction(1);
            exit(0);
            break;

        default:
            cout << "Pilihan tidak tersedia" << endl;
            menuCustomer(headParam);
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