#ifndef UTILS_CUSTOMER_HPP
#define UTILS_CUSTOMER_HPP

#include <bits/stdc++.h>
#include <conio.h>
#include "additional.hpp"
#include "items.hpp"
#include "admin.hpp"
#include "logIn.hpp"

using namespace std;
void menuCustomer(NodeTransaksi *headParam, Node *headx, NodeCheckout *headCheckout);
void saveToFile(NodeTransaksi *headParam);
void displayData(NodeTransaksi *head, loginCustomer userData);

void addFirst(NodeTransaksi *headParam, Node *itemsList, loginCustomer userData, NodeCheckout *&headCheckout) {
    // Inisialisasi variabel yang dibutuhkan
    string username, input;
    int itemNumber, amount;
    int itemCounter = 0;
    Node *currentItem = itemsList;
    int selectedItem = 1;
    Node *selectedItemNode = itemsList;

    // Input nomor barang yang ingin dibeli
    cout << "Pilih nomor barang yang ingin dibeli: ";
    getline(cin, input);

    // Validasi nomor barang
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
    // Cek apakah nomor barang yang dimasukkan valid
    if (itemNumber < 1 || itemNumber > itemCounter) {
        cout << "Nomor barang tidak valid." << endl;
        system("pause");
        return;
    }

    // Input jumlah barang
    cout << "Jumlah: ";
    getline(cin, input);
    try {
        amount = stoi(input);
    } catch (const invalid_argument& e) {
        cout << "Jumlah tidak valid." << endl;
        system("pause");
        return;
    }

    // Validasi jumlah barang
    if (amount < 1) {
        cout << "Jumlah tidak valid." << endl;
        system("pause");
        return;
    }

    // Menemukan barang yang dipilih
    while (selectedItem < itemNumber && selectedItemNode != nullptr) {
        selectedItemNode = selectedItemNode->next;
        selectedItem++;
    }

    // Validasi nomor barang yang dipilih
    if (selectedItemNode == nullptr) {
        cout << "Nomor barang tidak valid." << endl;
        system("pause");
        return;
    }

    // Membuat node transaksi baru
    NodeTransaksi *newNodeTransaksi = new NodeTransaksi;
    newNodeTransaksi->barang.username = userData.username;
    newNodeTransaksi->barang.item_names = selectedItemNode->barang.namaBarang;
    newNodeTransaksi->barang.amount = amount;
    newNodeTransaksi->barang.status = "Belum dibayar";
    newNodeTransaksi->next = nullptr;

    // Menambahkan node ke awal daftar transaksi
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
    // Menyimpan perubahan ke file dan melanjutkan ke menu customer
    saveToFile(headParam);
    system("pause");
    menuCustomer(headParam, itemsList, headCheckout);
}


// DeleteFirst
void deleteFirst(NodeTransaksi **headParam, Node *itemsList, int idx, NodeCheckout *&headCheckout) {
    // Menangani kasus jika tidak ada transaksi
    if (*headParam == NULL) {
        cout << "Anda belum memesan Barang" << endl;
        cout << "Barang kosong......" << endl;
        system("pause");
        menuCustomer(*headParam, itemsList, headCheckout);
        return;
    }

    // Menghitung jumlah transaksi secara traversal
    int count = 0;
    NodeTransaksi *temp = *headParam;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    // Validasi indeks input
    if (idx < 1 || idx > count) {
        cout << "Input diluar rentang yang valid" << endl;
        system("pause");
        menuCustomer(*headParam, itemsList, headCheckout);
        return;
    }

    // Menghapus node transaksi pertama
    if (idx == 1) {
        NodeTransaksi *deletedNode = *headParam;
        *headParam = (*headParam)->next;
        delete deletedNode;
        deletedNode = NULL;
    } else {
        // Menghapus node transaksi pada indeks tertentu
        temp = *headParam;
        for (int i = 1; i < idx - 1; i++) {
            temp = temp->next;
        }
        NodeTransaksi *deletedNode = temp->next;
        temp->next = deletedNode->next;
        delete deletedNode;
        deletedNode = NULL;
    }

    // Menyimpan perubahan ke file dan melanjutkan ke menu customer
    saveToFile(*headParam);
    cout << "\n---Barang Berhasil Dihapus---" << endl;
    system("pause");
    menuCustomer(*headParam, itemsList, headCheckout);
}

// Simpan data transaksi ke dalam sebuah file
void saveToFile(NodeTransaksi *head){
    ofstream fileStream("db/transactions.tsv");

    // Iterasi melalui linked list dan menulis data ke dalam file
    NodeTransaksi *current = head;
    while (current != nullptr)
    {
        fileStream 
        << current->barang.username << '\t' 
        << current->barang.item_names << '\t' 
        << current->barang.amount << '\t'
        << current->barang.status << '\n';
        current = current->next;
    }
    fileStream.close();
}

//LoadFrom File
void importFromFile(NodeTransaksi *&head)
{
    ifstream fileStream("db/Transactions.tsv");

    // Periksa apakah file terbuka
    if (!fileStream.is_open())
    {
        cout << "File not found!" << endl;
        return;
    }

    // Baca setiap baris dari file dan buat simpul baru dalam linked list
    string line;
    while (getline(fileStream, line))
    {
        stringstream ss(line);
        string username, item_names, amount, status;

        // Parse setiap field dari baris yang dipisahkan oleh tab
        if (getline(ss, username, '\t') &&
            getline(ss, item_names, '\t') &&
            getline(ss, amount, '\t') &&
            getline(ss, status, '\n'))
        {
            // Buat simpul transaksi baru
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

            newNodeTransaksi->barang.status = status;

            // Tambahkan simpul baru ke awal linked list
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

// Import data checkout dari file ke linked list
void importFromCheckout(NodeCheckout *&head)
{
    ifstream fileStream("db/checkout.tsv");
    if (!fileStream.is_open())
    {
        cout << "File not found!" << endl;
        return;
    }

    string line;
    while (getline(fileStream, line))
    {
        stringstream ss(line);
        string username, item_names, amount, status;
        if (getline(ss, username, '\t') &&
            getline(ss, item_names, '\t') &&
            getline(ss, amount, '\t') &&
            getline(ss, status, '\n'))
        {
            NodeCheckout *newNodeCheckout = new NodeCheckout;
            newNodeCheckout->barang.username = username;
            newNodeCheckout->barang.item_names = item_names;

            try
            {
                newNodeCheckout->barang.amount = stoi(amount);
            }
            catch (const invalid_argument &e)
            {
                cout << "Invalid integer value in the file: " << e.what() << endl;
                delete newNodeCheckout;
                continue;
            }

            newNodeCheckout->barang.status = status;
            newNodeCheckout->next = head;
            head = newNodeCheckout;
        }
        else
        {
            cout << "" << endl;
        }
    }
    fileStream.close();
}

// Simpan data checkout ke dalam sebuah file
void saveToCheckout(NodeTransaksi *headParam, loginCustomer userData) {
    ofstream fileStream("db/checkout.tsv", ios::app);

    if (!fileStream) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    NodeTransaksi *current = headParam;
    while (current != nullptr) {
        if (current->barang.username == userData.username) {
            fileStream
                << current->barang.username << '\t'
                << current->barang.item_names << '\t'
                << current->barang.amount << '\t';
                if (current->barang.status == "Belum dibayar") {
                    fileStream << "Diproses" << '\n';
                }
        }
        current = current->next;
    }
    fileStream.close();
}

// Delete all transaksi yang dimiliki oleh pengguna yang sedang login
void deleteAll(NodeTransaksi **headParam, Node *itemsList, loginCustomer userData) {
    NodeTransaksi *current = *headParam;
    NodeTransaksi *prev = nullptr;

    // Iterasi melalui linked list transaksi
    while (current != nullptr) {
        // Mengecek apakah transaksi terkait dengan pengguna
        if (current->barang.username == userData.username) {
            // Menghapus transaksi dari linked list
            if (prev == nullptr) {
                *headParam = current->next;
            } else {
                prev->next = current->next;
            }
            // Menghapus node transaksi dan melanjutkan ke iterasi berikutnya
            NodeTransaksi *temp = current;
            current = current->next;
            delete temp;
            continue;
        }
        // Pindah ke node berikutnya dalam linked list
        prev = current;
        current = current->next;
    }
    // Menyimpan perubahan ke dalam file
    saveToFile(*headParam);
}

// Checkout semua transaksi yang dimiliki oleh pengguna yang sedang login
void checkOut(NodeTransaksi *&headParam, Node *&headx, loginCustomer userData, NodeCheckout *&headCheckout) {
    // Mengecek apakah ada transaksi yang dipilih
    if (headParam == nullptr) {
        cout << "Tidak ada barang" << endl;
        cout << "Silahkan tambah barang terlebih dahulu" << endl;
        system("pause");
        menuCustomer(headParam, headx, headCheckout);
        return;
    }

    // Menanyakan konfirmasi untuk checkout
    cout << "Apakah anda yakin ingin checkout? (y/n) : ";
    string pilihan;
    cin >> pilihan;
    fflush(stdin);

    if (pilihan == "y") {
        // Menyimpan transaksi yang akan di-checkout ke dalam file checkout
        saveToCheckout(headParam, userData);
        // Menghapus semua transaksi yang terkait dengan pengguna dari linked list
        deleteAll(&headParam, headx, userData);
        // Menampilkan pesan checkout berhasil
        system("cls");
        cout << "+---------------------------------------------+" << endl;
        cout << "|  Terima kasih telah berbelanja di KerisBow  |" << endl;
        cout << "+---------------------------------------------+" << endl;
        cout << "|  Code Pembayaran : XXXX-XXXX-XXXX-XXXX      |" << endl;
        cout << "+---------------------------------------------+" << endl;
        cout << "|       Silahkan melakukan pembayaran di      |" << endl;
        cout << "|      gerai terdekat dengan menunjukkan      |" << endl;
        cout << "|           code pembayaran diatas            |" << endl;
        cout << "+---------------------------------------------+" << endl;
        system("pause");
        menuCustomer(headParam, headx, headCheckout);
    } else if (pilihan == "n") {
        // Batal checkout dan kembali ke menu customer  
        system("pause");
        menuCustomer(headParam, headx, headCheckout);
    } else {
        // Pesan untuk pilihan yang tidak valid
        cout << "Pilihan tidak tersedia" << endl;
        system("pause");
        menuCustomer(headParam, headx, headCheckout);
    }
}
// Menampilkan data transaksi yang dimiliki oleh pengguna yang sedang login
void displayData(NodeTransaksi *head, loginCustomer userData)
{
    // Mengecek apakah terdapat data transaksi
    if (head == nullptr)
    {
        cout << "Tidak ada barang" << endl;
        cout << "Silahkan tambah barang terlebih dahulu" << endl;
        return;
    }

    int counter = 1;
    NodeTransaksi *current = head;

    // Menampilkan header tabel
    cout << "========================================================================================" << endl;
    cout << "| No.|  Nama Pembeli  |   Nama Barang yang dibeli     |     Jumlah     |     status    |" << endl;
    cout << "========================================================================================" << endl;

    // Iterasi melalui linked list transaksi
    while (current != nullptr)
    {
        // Menampilkan data transaksi jika terkait dengan pengguna
        if (current->barang.username == userData.username)
        {
            cout << "[ " << counter << ". ] " << 
            setw(15) << left << current->barang.username << "| " <<
            setw(28) << left << current->barang.item_names << "| " << 
            setw(13) << left << current->barang.amount << "| " << 
            setw(13) << left << current->barang.status << "| " << endl;
            cout << "========================================================================================" << endl;
            counter++;
        }
        current = current->next;
    }

    // Menampilkan pesan jika tidak ada transaksi untuk pengguna
    if (counter == 1)
    {
        cout << "Tidak ada transaksi untuk pengguna dengan username: " << userData.username << endl;
    }
}

void displayCheckout(NodeCheckout *head, loginCustomer userData)
{
    importFromCheckout(head);
    if (head == nullptr)
    {
        cout << "Tidak ada data checkout" << endl;
        return;
    }

    int counter = 1;
    NodeCheckout *current = head;
    cout << "+====================================================+" << endl;
    cout << "| No.|   Nama Barang yang dibeli  |      Status      |" << endl;
    cout << "+====================================================+" << endl;
    while (current != nullptr)
    {
        if (current->barang.username == userData.username)
        {
            cout << "[ " << counter << ". ] "
                 << setw(27) << left << current->barang.item_names << "|"
                 << setw(13) << left << current->barang.status << "|" << endl;
            cout << "========================================" << endl;
            counter++;
        }
        current = current->next;
    }

    if (counter == 1)
    {
        cout << "Tidak ada data checkout untuk pengguna dengan username: " << userData.username << endl;
    }
}

// Menu customer
void menuCustomer(NodeTransaksi *headParam, Node *headx, NodeCheckout *headCheckout)
{
    string pilihanTemp, temp; int pilih,idx;
    loginCustomer userData;
    readLogin(userData);

    system("cls");
    cout << "+=================================+" << endl;
    cout << "| Selamat datang di menu customer |" << endl;
    cout << "+=================================+" << endl;
    cout << "| 1. Tambah Barang                |" << endl;
    cout << "| 2. Keranjang                    |" << endl;
    cout << "| 3. Barang yang sudah dibeli     |" << endl;
    cout << "| 4. Checkout                     |" << endl;
    cout << "| 5. Hapus Barang di Keranjang    |" << endl;
    cout << "| 6. Cari Barang                  |" << endl;
    cout << "| 0. Keluar                       |" << endl;
    cout << "+=================================+" << endl;
    cout << "+--- Masukkan pilihan anda => ";
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
            addFirst(headParam, headx, userData, headCheckout);
            menuCustomer(headParam, headx, headCheckout);
            break;
        case 2:
            system("cls");
            displayData(headParam, userData);
            system("pause");
            menuCustomer(headParam, headx, headCheckout);
            break;
        case 3:
            system("cls");
            displayCheckout(headCheckout, userData);
            system("pause");
            menuCustomer(headParam, headx, headCheckout);
            break;
        case 4:
            system("cls");
            displayData(headParam, userData);
            checkOut(headParam, headx, userData, headCheckout);
            break;
        case 5:
            system("cls");
            displayData(headParam, userData);
            try{
                cout << "\nMasukkan pilihan : "; getline(cin, temp);
                idx = stoi(temp);
                deleteFirst(&headParam, headx, idx, headCheckout);
            }catch(invalid_argument &e){
                cout<<"Inputan harus Integer";getch();cout<<endl;
                menuCustomer(headParam, headx, headCheckout);
            }
            break;
        case 6:
            system("cls");
            cout << "Masukkan keyword: ";
            getline(cin, temp);
            searchBM(headx, temp);
            system("pause");
            menuCustomer(headParam, headx, headCheckout);
            break;
        case 0:
            cout << "Terima kasih telah menggunakan KerisBow" << endl;
            endOfFunction(1);
            exit(0);
            break;

        default:
            cout << "Pilihan tidak tersedia" << endl;
            menuCustomer(headParam, headx, headCheckout);
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