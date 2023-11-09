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
void deleteAllShoppingCart(Node *&head);
void displayData(NodeTransaksi *head);

void addFirst(NodeTransaksi *headParam, Node *itemsList) {
    string username, input;
    int itemNumber, amount;
    int itemCounter = 0;
    Node *currentItem = itemsList;
    int selectedItem = 1;
    Node *selectedItemNode = itemsList;

    cout << "Username anda: ";
    getline(cin, username);
    if(username == "") {
        cout << "Username tidak boleh kosong" << endl;
        system("pause");
        return;
    }

    cout << "Pilih nomor barang yang ingin dibeli: ";
    getline(cin, input);
    try {
        itemNumber = stoi(input);
        while (currentItem != nullptr) {
            itemCounter++;
            currentItem = currentItem->next;
        }
    } catch (const invalid_argument& e) {
        cout << "Nomor barang tidak valid." << endl;
        system("pause");
        return;
    }
    if (itemNumber < 1 || itemNumber > itemCounter) {
        cout << "Nomor barang tidak valid." << endl;
        system("pause");
        return;
    }

    cout << "Jumlah: ";
    getline(cin, input);
    try {
        amount = stoi(input);
    } catch (const invalid_argument& e) {
        cout << "Jumlah tidak valid." << endl;
        system("pause");
        return;
    }

    if (amount < 1) {
        cout << "Jumlah tidak valid." << endl;
        system("pause");
        return;
    }

    while (selectedItem < itemNumber && selectedItemNode != nullptr) {
        selectedItemNode = selectedItemNode->next;
        selectedItem++;
    }

    if (selectedItemNode == nullptr) {
        cout << "Nomor barang tidak valid." << endl;
        system("pause");
        return;
    }

    NodeTransaksi *newNodeTransaksi = new NodeTransaksi;
    newNodeTransaksi->barang.username = username;
    newNodeTransaksi->barang.item_names = selectedItemNode->barang.namaBarang;
    newNodeTransaksi->barang.amount = amount;
    newNodeTransaksi->barang.status = "Belum dibayar";
    newNodeTransaksi->next = nullptr;


    if (headParam == nullptr)
    {
        newNodeTransaksi->next = nullptr;
        headParam = newNodeTransaksi;
        cout << "Barang berhasil ditambahkan" << endl;
    }
    else
    {
        newNodeTransaksi->next = headParam;
        headParam = newNodeTransaksi;
        cout << "Barang berhasil ditambahkan" << endl;
    }
    saveToFile(headParam);
    system("pause");
    menuCustomer(headParam, itemsList);
}


// DeleteFirst
void deleteFirst(NodeTransaksi **headParam, Node *itemsList, int idx) {
    if (*headParam == NULL) {
        cout << "Anda belum memesan Barang" << endl;
        cout << "Barang kosong......" << endl;
        system("pause");
        menuCustomer(*headParam, itemsList);
        return;
    }

    int count = 0;
    NodeTransaksi *temp = *headParam;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    if (idx < 1 || idx > count) {
        cout << "Input diluar rentang yang valid" << endl;
        system("pause");
        menuCustomer(*headParam, itemsList);
        return;
    }

    if (idx == 1) {
        NodeTransaksi *deletedNode = *headParam;
        *headParam = (*headParam)->next;
        delete deletedNode;
        deletedNode = NULL;
    } else {
        temp = *headParam;
        for (int i = 1; i < idx - 1; i++) {
            temp = temp->next;
        }
        NodeTransaksi *deletedNode = temp->next;
        temp->next = deletedNode->next;
        delete deletedNode;
        deletedNode = NULL;
    }

    saveToFile(*headParam);

    cout << "\n---Barang Berhasil Dihapus---" << endl;
    system("pause");
    menuCustomer(*headParam, itemsList);
}


void saveToFile(NodeTransaksi *head){
    ofstream fileStream("db/transactions.tsv");
    NodeTransaksi *current = head;
    while (current != nullptr)
    {
        fileStream 
        << current->barang.username << '\t' 
        << current->barang.item_names << '\t' 
        << current->barang.amount << '\n';
        current = current->next;
    }
    fileStream.close();
}

//LoadFrom File
void importFromFile(NodeTransaksi *&head)
{
    ifstream fileStream("db/Transactions.tsv");
    if (!fileStream.is_open())
    {
        cout << "File not found!" << endl;
        return;
    }

    string line;
    while (getline(fileStream, line))
    {
        stringstream ss(line);
        string username, item_names, amount;
        if (getline(ss, username, '\t') &&
            getline(ss, item_names, '\t') &&
            getline(ss, amount, '\t'))
        {
            NodeTransaksi *newNodeTransaksi = new NodeTransaksi;
            newNodeTransaksi->barang.username = username;
            newNodeTransaksi->barang.item_names = item_names;
            
            // Menggunakan try-catch untuk mengatasi pengecualian yang mungkin terjadi saat mengonversi 'amount' ke integer.
            try
            {
                newNodeTransaksi->barang.amount = stoi(amount);
            }
            catch (const invalid_argument& e)
            {
                cout << "Invalid integer value in the file: " << e.what() << endl;
                delete newNodeTransaksi;
                continue; // Lanjutkan ke iterasi berikutnya jika ada kesalahan
            }

            newNodeTransaksi->next = head;
            head = newNodeTransaksi;
        }
        else
        {
            cout << "Invalid line format in the file." << endl;
        }
    }
    fileStream.close();
}

void saveToCheckout(NodeTransaksi *headParam) {
    ofstream fileStream("db/checkout.tsv", ios::app | ios::out);

    if (!fileStream) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    NodeTransaksi *current = headParam;
    while (current != nullptr) {
        fileStream
            << current->barang.username << '\t'
            << current->barang.item_names << '\t'
            << current->barang.amount << '\n';
        current = current->next;
    }
    fileStream.close();
}

void deleteAll(NodeTransaksi **headParam, Node *itemsList) {
    NodeTransaksi *current = *headParam;
    NodeTransaksi *next = nullptr;

    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }

    *headParam = nullptr;
    saveToFile(*headParam);
    menuCustomer(*headParam, itemsList);
}

void checkOut(NodeTransaksi *&headParam, Node *&headx) {
    if (headParam == nullptr) {
        cout << "Tidak ada barang" << endl;
        cout << "Silahkan tambah barang terlebih dahulu" << endl;
        system("pause");
        menuCustomer(headParam, headx);
    }

    cout << "Apakah anda yakin ingin checkout? (y/n) : ";
    string pilihan;
    cin >> pilihan;
    fflush(stdin);

    if (pilihan == "y") {
        saveToCheckout(headParam);
        deleteAll(&headParam, headx);

        cout << "Terima kasih telah berbelanja di KerisBow" << endl;
        cout << "Barang akan segera dikirimkan" << endl;
        cout << "Silahkan cek email anda untuk melihat detail transaksi" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "Tekan enter untuk kembali ke menu" << endl;
        system("pause");
        menuCustomer(headParam, headx);
    } else if (pilihan == "n") {
        system("pause");
        menuCustomer(headParam, headx);
    } else {
        cout << "Pilihan tidak tersedia" << endl;
        system("pause");
        menuCustomer(headParam, headx);
    }
}

// DisplayData
void displayData(NodeTransaksi *head)
{
    if (head == nullptr)
    {
        cout << "Tidak ada barang" << endl;
        cout << "Silahkan tambah barang terlebih dahulu" << endl;
        return;
    }
    int counter = 1;
    NodeTransaksi *current = head;
    while (current != nullptr)
    {
        cout << "----------------------------------------------" << endl;
        cout << "Barang ke-" << counter << endl;
        cout << "----------------------------------------------" << endl;
        cout << "Nama Pembeli          : " << current->barang.username << endl;
        cout << "Nama Barang yg dibeli : " << current->barang.item_names << endl;
        cout << "Jumlah Beli           : " << current->barang.amount << endl;
        cout << "----------------------------------------------" << endl;
        current = current->next;
        counter++;
    }
}

void menuCustomer(NodeTransaksi *headParam, Node *headx)
{
    string pilihanTemp, temp; int pilih,idx;

    system("cls");
    cout << "Selamat datang di menu customer" << endl;
    cout << "1. Tambah Barang" << endl;
    cout << "2. Keranjang" << endl;
    cout << "3. Checkout" << endl;
    cout << "4. Hapus Barang di Keranjang" << endl;
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
            displayLinkedList(headx);
            addFirst(headParam, headx);
            menuCustomer(headParam, headx);
            break;
        case 2:
            system("cls");
            displayData(headParam);
            system("pause");
            menuCustomer(headParam, headx);
            break;
        case 3:
            system("cls");
            displayData(headParam);
            checkOut(headParam, headx);
            break;
        case 4:
            system("cls");
            displayData(headParam);
            try{
                cout << "\nMasukkan pilihan : "; getline(cin, temp);
                idx = stoi(temp);
                deleteFirst(&headParam, headx, idx);
            }catch(invalid_argument &e){
                cout<<"Inputan harus Integer";getch();cout<<endl;
                menuCustomer(headParam, headx);
            }
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