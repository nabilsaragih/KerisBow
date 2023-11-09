#ifndef UTILS_ADMIN_HPP
#define UTILS_ADMIN_HPP

#include <bits/stdc++.h>
#include "items.hpp"
#include "additional.hpp"
#include "searching.hpp"
using namespace std;

// add first ke LL
void addFirst(Node *&headParam)
{
    string namaBarang, hargaBarang, fiturBarang, deskripsiBarang;

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

    newNode->barang.namaBarang = namaBarang;
    newNode->barang.hargaBarang = hargaBarang;
    newNode->barang.fiturBarang = fiturBarang;
    newNode->barang.deskripsiBarang = deskripsiBarang;

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
}

// del spesifik menggunakan nama
void deleteSpecific(Node *&headParam)
{
    if (headParam == nullptr)
    {
        cout << "Data kosong" << endl;
        return;
    }

    string target;
    cout << "Masukkan nama barang yang ingin dihapus : ";
    getline(cin, target);
    cin.sync();

    if (headParam->barang.namaBarang == target)
    {
        Node *temp = headParam;
        headParam = headParam->next;
        delete temp;

        cout << "Barang berhasil dihapus" << endl;
        return;
    }

    Node *current = headParam;
    while (current->next != nullptr)
    {
        if (current->next->barang.namaBarang == target)
        {
            Node *temp = current->next;
            current->next = temp->next;
            delete temp;

            cout << "Barang berhasil dihapus" << endl;
            return;
        }
        current = current->next;
    }
    cout << "Barang berhasil dihapus" << endl;
}

// edit/update/ubah spesifik menggunakan nama
void updateSpecific(Node *&headParam)
{
    if (headParam == nullptr)
    {
        cout << "Data kosong" << endl;
        return;
    }

    string target, namaBarang, hargaBarang, fiturBarang, deskripsiBarang;
    cout << "Masukkan nama barang yang ingin dihapus : ";
    getline(cin, target);
    cin.sync();

    cout << "Masukkan nama barang baru : ";
    getline(cin, namaBarang);
    cout << "Masukkan harga barang baru : ";
    getline(cin, hargaBarang);
    cout << "Masukkan fitur barang baru : ";
    getline(cin, fiturBarang);
    cout << "Masukkan deskripsi barang baru : ";
    getline(cin, deskripsiBarang);

    Node *current = headParam;
    while (current != nullptr)
    {
        if (current->barang.namaBarang == target)
        {
            current->barang.namaBarang = namaBarang;
            current->barang.hargaBarang = hargaBarang;
            current->barang.fiturBarang = fiturBarang;
            current->barang.deskripsiBarang = deskripsiBarang;

            cout << "Barang berhasil diubah" << endl;
            return;
        }
        current = current->next;
    }

    cout << "Barang tidak ditemukan." << endl;
}

// export data yang ada di LL ke TSV buat long-term storage
void exportToFile(Node *head)
{
    ofstream fileStream("db/items.tsv", ios::app);
    Node *current = head;
    while (current != nullptr)
    {
        fileStream << current->barang.namaBarang << '\t' << current->barang.hargaBarang << '\t' << current->barang.fiturBarang << '\t' << current->barang.deskripsiBarang << '\n';
        current = current->next;
    }
    fileStream.close();
}

// import data yang ada di TSV ke LL
void importFromFile(Node *&head)
{
    ifstream fileStream("db/items.tsv");
    if (!fileStream.is_open())
    {
        cout << "File not found!" << endl;
        return;
    }

    string line;
    while (getline(fileStream, line))
    {
        stringstream ss(line);
        string namaBarang, hargaBarang, fiturBarang, deskripsiBarang;
        getline(ss, namaBarang, '\t');
        getline(ss, hargaBarang, '\t');
        getline(ss, fiturBarang, '\t');
        getline(ss, deskripsiBarang, '\t');

        Node *newNode = new Node;
        newNode->barang.namaBarang = namaBarang;
        newNode->barang.hargaBarang = hargaBarang;
        newNode->barang.fiturBarang = fiturBarang;
        newNode->barang.deskripsiBarang = deskripsiBarang;

        newNode->next = head;
        head = newNode;
    }
    fileStream.close();
}

// clear  semua data di dalam tsv
void clearFile(const string &filename)
{
    ofstream fileStream(filename, ofstream::trunc);
    fileStream.close();
}

// liat data yg tersimpan di TSV
void displayTSV()
{
    ifstream fileStream("db/items.tsv");
    string line;

    while (getline(fileStream, line))
    {
        istringstream iss(line);
        vector<string> tokens;
        string token;
        while (getline(iss, token, '\t'))
        {
            tokens.push_back(token);
        }

        if (tokens.size() == 4)
        {
            cout << "Nama: " << tokens[0] << endl;
            cout << "Harga: " << tokens[1] << endl;
            cout << "Fitur: " << tokens[2] << endl;
            cout << "Deskripsi: " << tokens[3] << endl;
            cout << "---------------------------------" << endl;
        }
        else
        {
            cout << "Terjadi kerusakan pada data. Data tidak dapat ditampilkan" << endl;
        }
    }
    fileStream.close();
}

// liat data yg tersimpan di LL
void displayLinkedList(Node *head)
{
    Node *current = head;
    while (current != nullptr)
    {
        cout << "Nama Barang: " << current->barang.namaBarang << endl;
        cout << "Harga Barang: " << current->barang.hargaBarang << endl;
        cout << "Fitur Barang: " << current->barang.fiturBarang << endl;
        cout << "Deskripsi Barang: " << current->barang.deskripsiBarang << endl;
        cout << "-----------------------" << endl;
        current = current->next;
    }
}

void menuAdmin(int *pilih, Node *headParam)
{
    string pilihanTemp, target;

    system("cls");
    cout << "Selamat datang di menu admin" << endl;
    cout << "1. Tambah Barang" << endl;
    cout << "2. Lihat Barang" << endl;
    cout << "3. Ubah Barang" << endl;
    cout << "4. Hapus Barang" << endl;
    // cout << "5. Tambah Admin (Prototype)" << endl;
    cout << "0. Keluar" << endl;
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
            system("pause");
            menuAdmin(pilih, headParam);
            break;
        case 2:
            system("cls");
            displayLinkedList(headParam);
            system("pause");
            menuAdmin(pilih, headParam);
            break;
        case 3:
            system("cls");
            displayLinkedList(headParam);
            updateSpecific(headParam);
            system("pause");
            menuAdmin(pilih, headParam);
            break;
        case 4:
            system("cls");
            displayLinkedList(headParam);
            deleteSpecific(headParam);
            system("pause");
            menuAdmin(pilih, headParam);
            break;
        case 0:
            cout << "Terima kasih telah menggunakan KerisBow" << endl;
            clearFile("db/items.tsv");
            exportToFile(headParam);
            endOfFunction(1);
            exit(0);
            break;
        case 98:
            system("cls");
            cout<< "Masukkan nama barang yang ingin dicari : ";
            getline(cin, target);
            searchBM(headParam, target);
            system("pause");
            break;
        case 99:
            system("cls");
            displayTSV();
            system("pause");
            menuAdmin(pilih, headParam);
            break;

        default:
            cout << "Pilihan tidak tersedia" << endl;
            menuAdmin(pilih, headParam);
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