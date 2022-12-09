#include "BinManage.h"

bool createBinFromTxt(string txtName, string binName)
{
    ifstream fin(txtName);
    if (!fin.is_open())
        return false;
    ofstream fout(binName, ios::binary | ios::trunc);
    if (!fout.is_open())
        return false;
    Product tmp;
    while (fin.good()) 
    {
        fin >> tmp.ID;
        if (!fin.good())
            break;
        fin.get();
        fin.getline(tmp.name, 256);
        fin >> tmp.cost;
        fin.get();
        fin.getline(tmp.date, 11);
        fout.write((char*)&tmp, sizeof Product);
    }
    fin.close();
    fout.close();
    return true;
}

bool addRecInBin(Product& p, string binName) 
{
    bool res = false;
    ofstream fout(binName, ios::binary | ios::app);
    if (!fout.is_open())
    {
        res = false;
        return res;
    }
    fout.write((char*)&p, sizeof(Product));
    fout.close();
    res = true;
    return res;
}

bool delIDRecInBin(string binName, int ID)
{
    bool res = false;
    ifstream fin(binName, ios::binary | ios::beg);
    if (!fin.is_open())
    {
        res = false;
        return res;
    }
    fin.seekg(0, ios::end);
    int size = fin.tellg();
    size = size / sizeof(Product);
    Product* tmp = new Product[size];
    fin.seekg(0, ios::beg);
    int z = 0;
    while (z < size)
    {
        fin.read((char*)&tmp[z], sizeof(Product));
        z++;
    }
    fin.close();
    ofstream fout(binName, ios::binary | ios::trunc);
    if (!fout.is_open())
    {
        res = false;
        return res;
    }
    for (int i = 0; i < size; i++)
    {
        if (tmp[i].ID != ID)fout.write((char*)&tmp[i], sizeof(Product));
        if (tmp[i].ID == ID)
            res = true;
    }
    fout.close();
    return res;
}

Product getOneProduct(string binName, int pos)
{
    ifstream fin(binName, ios::binary | ios::beg);
    Product res;
    fin.seekg(0, ios::end);
    int size = fin.tellg();
    size = size / sizeof(Product);
    if (pos<size)
    {
        pos = pos * sizeof(Product);
        fin.seekg(pos);
        fin.read((char*)&res, sizeof(Product));
    }
    fin.close();
    return res;
}

void printBinFile(string binName)
{
    ifstream fin(binName, ios::binary);
    fin.seekg(0, ios::end);
    int size = fin.tellg();
    size = size / sizeof(Product);
    fin.seekg(0, ios::beg);
    Product* tmp = new Product[size];
    fin.seekg(0, ios::beg);
    int z = 0;
    while (z < size)
    {
        fin.read((char*)&tmp[z], sizeof(Product));
        z++;
    }
    fin.close();
    for (int i = 0; i < size; i++)
    {
        cout << "ID: " << tmp[i].ID;
        cout << "\tName: " << tmp[i].name;
        cout << "\tCost: " << tmp[i].cost;
        cout << "\tDate: " << tmp[i].date << endl;
    }
}