#include <bits/stdc++.h>
#include <conio.h>
#include "utils/account.hpp"
#include "utils/additional.hpp"
#include "utils/admin.hpp"
#include "utils/customer.hpp"
#include "utils/items.hpp"
#include "utils/anonymousRead.hpp"
#include "utils/menu.hpp"
using namespace std;

int main()
{
    // Inisialisasi
    Node *head = nullptr;
    NodeTransaksi *headTransaksi = nullptr;
    int pilihan = 0;
    unordered_map<string, string> accounts;
    unordered_map<string, string> accountRoles;

    // Extract data dari file
    readFromFile(&accounts);
    readRoles(&accountRoles);
    importFromFile(headTransaksi);
    importFromFile(head);

    // Mengecek apakah file dan folder sudah ada
    directoryChecker("db");
    fileChecker("accounts.tsv", "db");
    fileChecker("accounts_role.tsv", "db");
    fileChecker("items.tsv", "db");
    fileChecker("transactions.tsv", "db");
    fileChecker("checkout.tsv", "db");
    fileChecker("login.tsv", "db");

    // Menjalankan program
    while (true)
    {
        menu(&pilihan, &accounts, &accountRoles, head, headTransaksi);
    }

    return 0;
}
