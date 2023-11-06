#ifndef UTILS_CUSTOMER_HPP
#define UTILS_CUSTOMER_HPP

#include <bits/stdc++.h>
#include <conio.h>
#include "additional.hpp"
#include "items.hpp"
#include "admin.hpp"

using namespace std;
void menuCustomer(NodeTransaksi *headParam, Node *headx);
void saveToFile(NodeTransaksi *headParam);

void addLast(NodeTransaksi *headParam, Node *itemsList) {
    string username;
    int itemNumber, amount;
    cout << "Username: ";
    getline(cin, username);

    cout << "Pilih nomor barang yang ingin dibeli: ";

    int itemCounter = 0;
    Node *currentItem = itemsList;
    while (currentItem != nullptr) {
        itemCounter++;
        currentItem = currentItem->next;
    }

    cin >> itemNumber;
    cout << "Jumlah: ";
    cin >> amount;

    if (itemNumber < 1 || itemNumber > itemCounter) {
        cout << "Nomor barang tidak valid." << endl;
        return;
    }

    int selectedItem = 1;
    Node *selectedItemNode = itemsList;
    while (selectedItem < itemNumber && selectedItemNode != nullptr) {
        selectedItemNode = selectedItemNode->next;
        selectedItem++;
    }

    if (selectedItemNode == nullptr) {
        cout << "Nomor barang tidak valid." << endl;
        return;
    }

    NodeTransaksi *newNodeTransaksi = new NodeTransaksi;
    newNodeTransaksi->barang.username = username;
    newNodeTransaksi->barang.item_names = selectedItemNode->barang.namaBarang;
    newNodeTransaksi->barang.amount = amount;
    newNodeTransaksi->next = nullptr;


    if (headParam == nullptr) {
        headParam = newNodeTransaksi;
    } else {
        NodeTransaksi *temp = headParam;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNodeTransaksi;
    }
    saveToFile(headParam);

    cout << "Barang berhasil ditambahkan"; 
    getch();
    cout << endl;
    menuCustomer(headParam, itemsList);
}


// DeleteFirst
void deleteFirst(NodeTransaksi *headParam) {
    NodeTransaksi *temp = headParam;
    if (temp == nullptr) {
        cout << "Tidak ada barang" << endl;
        cout << "Silahkan tambah barang terlebih dahulu" << endl;
        return;
    } else {
        headParam = temp->next;
        delete temp;
        cout << "Barang berhasil dihapus" << endl;
    }
    saveToFile(headParam);
}

void saveToFile(NodeTransaksi *head){
    ofstream DataNodeTransaksi;
    DataNodeTransaksi.open("db/transactions.tsv");
    NodeTransaksi *temp = head;
    while (temp != NULL){
        DataNodeTransaksi << temp->barang.username << "\t" 
        << temp->barang.item_names << "\t"
        << temp->barang.amount<< "\t" << endl;
        temp = temp->next;
    }
    DataNodeTransaksi.close();
}

//LoadFrom File
void loadFromFile(NodeTransaksi *headParam) {
    ifstream dataNodeTransaksi("db/transactions.tsv");
    if (!dataNodeTransaksi.is_open()) {
        cout << "Gagal membuka file items.tsv" << endl;
        return;
    }

    string line, username, itemNames, amount;
    while (getline(dataNodeTransaksi, line)) {
        stringstream ss(line);
        if (getline(ss, username, '\t') &&
            getline(ss, itemNames, '\t') &&
            getline(ss, amount, '\t')) {

            try {
                NodeTransaksi *barang = new NodeTransaksi;
                barang->barang.username = username;
                barang->barang.item_names = itemNames;
                barang->barang.amount = stoi(amount);
                barang->next = nullptr;

                if (headParam == nullptr) {
                    headParam = barang;
                } else {
                    NodeTransaksi *temp = headParam;
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

    dataNodeTransaksi.close();
}


// DisplayData
void displayData(NodeTransaksi* head) {
    if (head == NULL) {
        cout << "Tidak ada barang" << endl;
        cout << "Silahkan tambah barang terlebih dahulu" << endl;
        return;
    }
    NodeTransaksi* temp = head;
    int no = 0;
    while (temp != nullptr) {
        cout << "Nama Barang: " << temp->barang.username << endl;
        cout << "Harga Barang: " << temp->barang.item_names << endl;
        cout << "Fitur Barang: " << temp->barang.amount << endl;
        cout << endl;
        no++;
        temp = temp->next;
    }
    cout << "TAMPILAN MASIH BURIK !!, NEXT KUPERBAIKI (~Agus)" << endl;
}

void menuCustomer(NodeTransaksi *headParam, Node *headx)
{
    string pilihanTemp; int pilih;

    system("cls");
    cout << "Selamat datang di menu customer" << endl;
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
            displayTSV();
            addLast(headParam, headx);
            menuCustomer(headParam, headx);
            break;
        case 2:
            system("cls");
            displayData(headParam);
            cout<<"\nTekan Enter untuk kembali ke menu";getch();cout<<endl;
            menuCustomer(headParam, headx);
            break;
        case 3:
            system("cls");
            cout << "Ubah Barang" << endl;
            menuCustomer(headParam, headx);
            break;
        case 4:
            system("cls");
            deleteFirst(headParam);
            menuCustomer(headParam, headx);
            break;
        case 0:
            cout << "Terima kasih telah menggunakan KerisBow" << endl;
            endOfFunction(1);
            exit(0);
            break;

        default:
            cout << "Pilihan tidak tersedia" << endl;
            menuCustomer(headParam, headx);
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