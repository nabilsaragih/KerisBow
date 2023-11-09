#ifndef UTILS_ANONYMOUSREAD_HPP
#define UTILS_ANONYMOUSREAD_HPP

#include <bits/stdc++.h>
#include "items.hpp"
using namespace std;

void addLast(Node *headParam)
{
    ifstream fileStream("db/items.tsv");
    string line, namaBarang, hargaBarang, fiturBarang, deskripsiBarang;
    getline(fileStream, line);
    while (getline(fileStream, line))
    {
        Node *newNode = new Node;
        Node *temp = headParam;

        stringstream lineStream(line);
        getline(lineStream, namaBarang, '\t');
        getline(lineStream, hargaBarang, '\t');
        getline(lineStream, fiturBarang, '\t');
        getline(lineStream, deskripsiBarang, '\t');

        newNode->barang.namaBarang = namaBarang;
        newNode->barang.hargaBarang = hargaBarang;
        newNode->barang.fiturBarang = fiturBarang;
        newNode->barang.deskripsiBarang = deskripsiBarang;

        if (headParam == nullptr)
        {
            newNode->next = nullptr;
            headParam = newNode;
        }
        else
        {
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = nullptr;
        }
    }
    fileStream.close();
}

void display(Node *headParam)
{
    addLast(headParam);

    Node *temp = headParam;

    if (temp->barang.namaBarang == "nama")
    {
        cout << "Tidak ada barang yang tersedia" << endl;
        return;
    }
    else
    {
        while (temp != nullptr)
        {
            cout << "Nama Barang: " << temp->barang.namaBarang << endl;
            cout << "Harga Barang: " << temp->barang.hargaBarang << endl;
            cout << "Fitur Barang: " << temp->barang.fiturBarang << endl;
            cout << "Deskripsi Barang: " << temp->barang.deskripsiBarang << endl;
            cout << endl;
            temp = temp->next;
        }
    }
}

#endif