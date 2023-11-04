#ifndef UTILS_ADMIN_HPP
#define UTILS_ADMIN_HPP

#include <bits/stdc++.h>
#include "items.hpp"
#include "additional.hpp"
using namespace std;

// add first ke stack
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
    newNode->barang.hargaBarang = stoll(hargaBarang);
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

// del first ke stack (data kehapus, tapi infinity loop pas display stack.)
void deleteFirst(Node *&headParam)
{
    if (headParam == nullptr)
    {
        cout << "Stack kosong" << endl;
        return;
    }

    Node *temp = headParam;
    headParam = headParam->next;
    delete temp;

    system("cls");
    cout << "Barang berhasil dihapus" << endl;
}

// export data yang ada di stack ke TSV buat long-term storage
void exportToFile(Node *head)
{
    ofstream fileStream("db/items.tsv");
    Node *current = head;
    while (current != nullptr)
    {
        fileStream << current->barang.namaBarang << '\t' << current->barang.hargaBarang << '\t' << current->barang.fiturBarang << '\t' << current->barang.deskripsiBarang << '\n';
        current = current->next;
    }
    fileStream.close();
}

// import data yang ada di TSV ke stack
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
        newNode->barang.hargaBarang = stoll(hargaBarang);
        newNode->barang.fiturBarang = fiturBarang;
        newNode->barang.deskripsiBarang = deskripsiBarang;

        newNode->next = head;
        head = newNode;
    }
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

// liat data yg tersimpan di stack
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
            exportToFile(headParam);
            endOfFunction(1);
            break;
        case 2:
            system("cls");
            importFromFile(headParam);
            displayLinkedList(headParam);
            cout << "Tekan apapun untuk lanjut" << endl;
            getch();
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
            exportToFile(headParam);
            endOfFunction(1);
            break;
        case 5:
            system("cls");
            cout << "Tambah Admin" << endl;
            endOfFunction(1);
            break;
        case 99:
            system("cls");
            displayTSV();
            cout << "Tekan apapun untuk lanjut" << endl;
            getch();
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