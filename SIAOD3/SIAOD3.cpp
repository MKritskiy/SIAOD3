#include <iostream>
#include <string>
#include <fstream>
#include "HashManage.h"
#include "BinManage.h"
#include "BinHashManage.h"
using namespace std;

int testHash()
{
    HashTable hTable;
    char choice;
    bool res;
    Product p;
    int pos;
    bool isBreaked = false;
    while (true) {
        while (true) {
            cout << "Write product ID: ";
            cin >> p.ID;
            if (cin.fail())
            {
                cout << "Oops! Incorrect input...\n";
                cin.clear();
                cin.ignore(32676, '\n');
            }
            else 
            {
                cin.ignore(32676, '\n');
                break;
            }
        }
        cout << "What do you want to do with that?(a - add, r - remove, f - find): ";
        cin >> choice;
        switch (choice)
        {
        case 'a':

            res = hTable.Add(p.ID, 0); //Добавление элемента
            if (res)
            {
                cout << "It was added on " << hTable.getLastPos() << endl;
                hTable.printIndexes();
            }
            else
                cout << "Oops! Element is not added...\n";
            break;
        case 'r':
            res = hTable.Remove(p.ID); //Добавление элемента
            if (res)
                cout << "Removed "<<hTable.getLastPos()<< " element" << endl;
            else
                cout << "Oops! Element was not removed...\n";
            break;
        case 'f':
            pos = hTable.Find(p.ID); //Добавление элемента
            if (pos >= 0)
            {
                cout << "Product was found on " << pos << " position" << endl;
            }
            else
                cout << "Product was not found\n";
            break;
        case 'b':
            isBreaked = true;
            break;
        default:
            cout << "Unknown choice!\n";
            cin.ignore(32676, '\n');
            break;
        }
        if (isBreaked)
            break;
    }
    return 0;
}
//test.txt
//bin.bin
//a
//20
//Sguschenka
//200
//12.12.2012
//4
//a
//10
//Moloko
//80
//05.10.2022
//2
int testBin()
{
    cout << "Enter txt file name: ";
    string txtName;
    cin >> txtName;
    cout << "Enter bin file name: ";
    string binName;
    cin >> binName;
    createBinFromTxt(txtName, binName);
    char choice;
    bool isBreaked = false;
    Product tmp;
    int pos;
    while (true) {
        cout << "What do you want to do?(a - add rec in bin, d - del rec from bin, g - get rec from bin, p - print bin file): ";
        cin >> choice;
        switch (choice)
        {
        case 'a':

            cout << "Fill new record: \n";
            cout << "ID: "; cin >> tmp.ID;
            cout << "Name: "; cin >> tmp.name;
            cout << "Cost: "; cin >> tmp.cost;
            cout << "Date: "; cin >> tmp.date;
            cout << "Write the position of new record in bin file: ";
            cin >> pos;
            addRecInBin(tmp, binName, pos);
            printBinFile(binName);
            break;
        case 'd':
            cout << "Write ID you want to delete: ";
            cin >> tmp.ID;
            if (delIDRecInBin(binName, tmp.ID))
                cout << "Deleting was successfull\n";
            else
                cout << "Oops! Something is wrong...\n";
            printBinFile(binName);
            break;
        case 'g':
            cout << "Write pos you want to get: ";
            cin >> pos;
            tmp = getOneProduct(binName, pos);
            cout << "Your product:\n";
            cout << "ID: " << tmp.ID;
            cout << "\tName: " << tmp.name;
            cout << "\tCost: " << tmp.cost;
            cout << "\tDate: " << tmp.date << endl;
            break;
        case 'p':
            printBinFile(binName);
            break;
        case 'b':
            isBreaked = true;
            break;
        default:
            cout << "Unknown choice!\n";
            cin.ignore(32676, '\n');
            break;
        }
        if (isBreaked)
            break;
    }
    return 0;
}

int testBinHash()
{
    cout << "Enter txt file name: ";
    string txtName;
    cin >> txtName;

    cout << "Enter bin file name: ";
    string binName;
    cin >> binName;

    createBinFromTxt(txtName, binName);

    Product tmp;
    HashTable table;

    char choice;
    bool isBreaked = false;
    int pos;

    while (true) {
        cout << "a - add rec in bin\nr - read from bin and add in table\nd - del rec\nf - find rec\np - print bin file and hash table\nWhat do you want to do: ";
        cin >> choice;
        switch (choice)
        {
        case 'a':

            cout << "Fill new record: \n";
            cout << "ID: "; cin >> tmp.ID;
            cout << "Name: "; cin >> tmp.name;
            cout << "Cost: "; cin >> tmp.cost;
            cout << "Date: "; cin >> tmp.date;
            cout << "Write the position of new record in bin file: ";
            cin >> pos;
            addRecInBin(tmp, binName, pos);
            printBinFile(binName);
            break;
        case 'r':
            cout << "Read all records in file?(y/n): ";
            cin >> choice;
            if (choice == 'y')
            {
                pos = 0;
                while (readAndInsert(binName, pos, table)) {
                    pos++;
                }
            }
            else if (choice == 'n') 
            {
                cout << "Write record number you want to read and add to table: ";
                cin >> pos;
                readAndInsert(binName, pos, table);
            }
            break;
        case 'd':
            cout << "Write ID you want to delete: ";
            cin >> tmp.ID;
            if (delRecFromFileAndTable(binName, table, tmp.ID))
                cout << "Deleting was successfull\n";
            else
                cout << "Oops! Something is wrong...\n";
            printBinFile(binName);
            table.printIndexes();
            break;
        case 'f':
            cout << "Write key you want to find: ";
            cin >> pos;
            try
            {
                tmp = findRec(binName, table, pos);
            }
            catch (const int exeption)
            {
                if (exeption == 0)
                    cout << "UNCORRECT KEY!\n";
                break;
            }
            cout << "Your product:\n";
            cout << "ID: " << tmp.ID;
            cout << "\tName: " << tmp.name;
            cout << "\tCost: " << tmp.cost;
            cout << "\tDate: " << tmp.date << endl;
            break;
        case 'p':
            printBinFile(binName);
            table.printIndexes();
            break;
        case 'b':
            isBreaked = true;
            break;
        default:
            cout << "Unknown choice!\n";
            cin.ignore(32676, '\n');
            break;
        }
        if (isBreaked)
            break;
    }
    return 0;
}
int main()
{
    testBinHash();
}
