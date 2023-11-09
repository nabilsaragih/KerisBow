#ifndef UTILS_ACCOUNT_HPP
#define UTILS_ACCOUNT_HPP

#include <bits/stdc++.h>
#include <string>
#include "additional.hpp"
#include "admin.hpp"
#include "customer.hpp"
#include "items.hpp"
#include "logIn.hpp"
#include "menu.hpp"
#include "anonymousRead.hpp"
using namespace std;

void menuLoginRegister(int *pilih, unordered_map<string, string> *accountsParam, unordered_map<string, string> *accountRolesParam, Node *headParam, NodeTransaksi *headTransaksi);

enum Pilihan {
    LOGIN = 1,
    LIHAT_BARANG = 2,
    KELUAR = 0
};

void menu(int *pilih, unordered_map<string, string> *accountParam, unordered_map<string, string> *accountRolesParam, Node *headParam, NodeTransaksi *headTransaksi)
{
    string pilihanTemp;

    system("cls");

    frameAwal();
    gotoXY(72,11);std::cout << "Selamat datang di KerisBow" << std::endl;
	gotoXY(54,18);std::cout << "1. Login" << std::endl;
	gotoXY(78,18);std::cout << "2. Lihat Barang" << std::endl;
	gotoXY(108,18);std::cout << "0. Keluar" << std::endl;
    pilihanTemp = getch();

    try
    {
        *pilih = stoi(pilihanTemp);
        switch (*pilih)
        {
        case LOGIN:
            menuLoginRegister(pilih, accountParam, accountRolesParam, headParam, headTransaksi);
            break;

        case LIHAT_BARANG:
            display(headParam);
            system("pause");
            break;

        case KELUAR:
            cout << "Terima kasih telah menggunakan KerisBow" << endl;
            endOfFunction(1);
            exit(0);
            break;

        default:
            cout << "Pilihan tidak tersedia" << endl;
            endOfFunction(1);
            break;
        }
    }
    catch (invalid_argument &e)
    {
        cout << "Mohon isi dengan pilihan yang ada!" << endl;
        endOfFunction(1);
    }
}

void addToFile(unordered_map<string, string> *accountsParam)
{
    ofstream fileStream("db/accounts.tsv", ios::trunc);
    fileStream << "username\tpassword" << endl;
    for (auto it = accountsParam->begin(); it != accountsParam->end(); it++)
    {
        fileStream << it->first << "\t" << it->second << endl;
    }
    fileStream.close();
}

void readFromFile(unordered_map<string, string> *accountsParam)
{
    ifstream fileStream("db/accounts.tsv");
    string line, username, password;
    getline(fileStream, line);
    while (getline(fileStream, line))
    {
        stringstream lineStream(line);
        getline(lineStream, username, '\t');
        getline(lineStream, password, '\t');
        accountsParam->insert({username, password});
    }
    fileStream.close();
}

void addRoles(string username, string role)
{
    ofstream fileStream("db/accounts_role.tsv", ios::app);
    fileStream << username << "\t" << role << endl;
    fileStream.close();
}

void readRoles(unordered_map<string, string> *accountsParam)
{
    ifstream fileStream("db/accounts_role.tsv");
    string line, username, role;
    getline(fileStream, line);
    while (getline(fileStream, line))
    {
        stringstream lineStream(line);
        getline(lineStream, username, '\t');
        getline(lineStream, role, '\t');
        accountsParam->insert({username, role});
    }
    fileStream.close();
}

void registerCustomer(unordered_map<string, string> *accountsParam)
{
    string username, password;
    cout << "Register Customer" << endl;
    cout << "Username: ";
    cin >> username;
    fflush(stdin);
    cout << "Password: ";
    cin >> password;
    fflush(stdin);

    if (accountsParam->find(username) != accountsParam->end())
    {
        cout << "Username sudah terdaftar" << endl;
        endOfFunction(1);
        return;
    }

    accountsParam->insert({username, password});
    addToFile(accountsParam);
    addRoles(username, "customer");
    std::cout << "Register berhasil" << endl;
    endOfFunction(1);
}

void registerAdmin(unordered_map<string, string> *accountsParam)
{
    string username, password;
    cout << "Register Admin" << endl;
    cout << "Username: ";
    cin >> username;
    fflush(stdin);
    cout << "Password: ";
    cin >> password;
    fflush(stdin);

    if (accountsParam->find(username) != accountsParam->end())
    {
        cout << "Username sudah terdaftar" << endl;
        endOfFunction(1);
        return;
    }

    accountsParam->insert({username, password});
    addToFile(accountsParam);
    addRoles(username, "admin");
    std::cout << "Register berhasil" << endl;
    endOfFunction(1);
}

void registerAccount(unordered_map<string, string> *accountsParam, int *pilih, unordered_map<string, string> *accountsRolesParam, Node *headParam, NodeTransaksi *headTransaksi)
{
    string username, password, pilihanTemp;

    cout << "Register sebagai: " << endl;
    cout << "1. Customer" << endl;
    cout << "2. Admin" << endl;
    cout << "Masukkan pilihan anda: "; cin >> pilihanTemp; fflush(stdin);

    try
    {
        *pilih = stoi(pilihanTemp);
        switch (*pilih)
        {
        case 1:
            system("cls");
            registerCustomer(accountsParam);
            break;

        case 2:
            system("cls");
            registerAdmin(accountsParam);
            break;

        default:
            cout << "Pilihan tidak tersedia" << endl;
            endOfFunction(1);
            menuLoginRegister(pilih, accountsParam, accountsRolesParam, headParam, headTransaksi);
            break;
        }
    }
    catch (invalid_argument &e)
    {
        cout << "Pilihan tidak tersedia" << endl;
        endOfFunction(1);
    }
}

void login(unordered_map<string, string> *accountsParam, unordered_map<string, string> *accountRolesParam, int *pilih, Node *headParam, NodeTransaksi *headTransaksi)
{
    string username, password;
    cout << "Username: ";
    cin >> username;
    fflush(stdin);
    cout << "Password: ";
    cin >> password;
    fflush(stdin);

    readRoles(accountRolesParam);

    if (accountsParam->find(username) != accountsParam->end())
    {
        if (accountsParam->at(username) == password)
        {
            loginCustomer currentUser;
            currentUser.username = username;
            currentUser.password = password;
            saveLogin(currentUser);
            
            cout << "Login berhasil" << endl;
            endOfFunction(1);
            if (accountRolesParam->at(username) == "customer")
            {
                menuCustomer(headTransaksi, headParam);
                return;
            }
            else if (accountRolesParam->at(username) == "admin")
            {
                menuAdmin(pilih, headParam);
                return;
            }
        }
    }

    cout << "Login gagal" << endl;
    endOfFunction(1);
}

void menuLoginRegister(int *pilih, unordered_map<string, string> *accountsParam, unordered_map<string, string> *accountRolesParam, Node *headParam, NodeTransaksi *headTransaksi)
{
    string pilihanTemp;

    enum menu_login {
        LOGIN = 1,
        REGISTER = 2,
        KEMBALI = 0
    };

    system("cls");

    frameAwal();
    gotoXY(80,11);std::cout << "MENU LOGIN" << std::endl;
	gotoXY(54,18);std::cout << "1. LOGIN" << std::endl;
	gotoXY(78,18);std::cout << "2. REGISTER" << std::endl;
	gotoXY(108,18);std::cout << "0. KEMBALI" << std::endl;
    pilihanTemp = getch();

    try
    {
        *pilih = stoi(pilihanTemp);
        switch (*pilih)
        {
        case LOGIN:
            system("cls");
            login(accountsParam, accountRolesParam, pilih, headParam, headTransaksi);
            break;

        case REGISTER:
            system("cls");
            registerAccount(accountsParam, pilih, accountRolesParam, headParam, headTransaksi);
            break;

        case KEMBALI:
            system("cls");
            menu(pilih, accountsParam, accountRolesParam, headParam, headTransaksi);
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