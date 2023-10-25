#ifndef UTILS_ACCOUNT_HPP
#define UTILS_ACCOUNT_HPP

#include <bits/stdc++.h>
#include <string>
#include "additional.hpp"
using namespace std;

void menuLogin(int *pilih, unordered_map<string, string> *accountsParam, bool *loginStatus);

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

void addRoles(unordered_map<string, string> *accountsParam, string role)
{
    ofstream fileStream("db/accounts_role.tsv", ios::trunc);
    fileStream << "username\trole" << endl;
    for (auto it = accountsParam->begin(); it != accountsParam->end(); it++)
    {
        fileStream << it->first << "\t" << role << endl;
    }
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
    addRoles(accountsParam, "customer");
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
    addRoles(accountsParam, "Admin");
    std::cout << "Register berhasil" << endl;
    endOfFunction(1);
}

void registerAccount(unordered_map<string, string> *accountsParam, int *pilih, bool *loginStatus)
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
            menuLogin(pilih, accountsParam, loginStatus);
            break;
        }
    }
    catch (invalid_argument &e)
    {
        cout << "Pilihan tidak tersedia" << endl;
        endOfFunction(1);
    }

    system("cls");
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
    std::cout << "Register berhasil" << endl;
    endOfFunction(1);
}

void login(unordered_map<string, string> *accountsParam, bool *loginStatus, unordered_map<string, string> *accountRoles)
{
    string username, password;
    cout << "Username: ";
    cin >> username;
    fflush(stdin);
    cout << "Password: ";
    cin >> password;
    fflush(stdin);

    if (accountsParam->find(username) != accountsParam->end())
    {
        if (accountsParam->at(username) == password)
        {
            cout << "Login berhasil" << endl;
            endOfFunction(1);
            if (accountRoles->at(username) == "customer")
            {
                *loginStatus = true;
                return;
            }
            else if (accountRoles->at(username) == "Admin")
            {
                *loginStatus = true;
                return;
            }
        }
    }

    cout << "Login gagal" << endl;
    endOfFunction(1);
}

void menuLogin(int *pilih, unordered_map<string, string> *accountsParam, bool *loginStatus, unordered_map<string, string> *accountRoles)
{
    string pilihanTemp;

    readFromFile(accountsParam);
    readRoles(accountRoles);

    system("cls");
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
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
            login(accountsParam, loginStatus, accountRoles);
            break;

        case 2:
            system("cls");
            registerAccount(accountsParam, pilih, loginStatus);
            break;

        default:
            cout << "Pilihan tidak tersedia" << endl;
            endOfFunction(1);
            menuLogin(pilih, accountsParam, loginStatus);
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