#include <iostream>
#include <string>
#include <fstream>
#include "HashManage.h"
#include "BinManage.h"
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

            res = hTable.Add(p); //Добавление элемента
            if (res)
            {
                cout << "It was added on " << hTable.getLastPos() << endl;
                hTable.printIndexes();
            }
            else
                cout << "Oops! Element is not added...\n";
            break;
        case 'r':
            res = hTable.Remove(p); //Добавление элемента
            if (res)
                cout << "Removed "<<hTable.getLastPos()<< " element" << endl;
            else
                cout << "Oops! Element was not removed...\n";
            break;
        case 'f':
            pos = hTable.Find(p); //Добавление элемента
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
        cout << "What do you want to do?(a - add rec in bin, d - del rec from bin, g - get rec from bin): ";
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
    testBin();
}
