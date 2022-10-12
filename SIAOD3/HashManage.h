#pragma once
#include <string>
#include <iostream>
#include "Product.h"
using namespace std;



int HashOpenAdress(const int& key, int table_size);

struct Node
{
    int key;
    bool state; // если значение флага state = false, значит элемент массива был удален (deleted)
    int recNum;
    Node(const int& val) : key(val), state(true), recNum(-1) {}
};

class HashTable
{
private:
    static const int default_size = 8; // начальный размер нашей таблицы
    constexpr static const double rehash_size = 0.75; // коэффициент, при котором произойдет увеличение таблицы
    Node** arr; // соответственно в массиве будут хранитс€ структуры Node*
    int size; // сколько элементов у нас сейчас в массиве (без учета deleted)
    int buffer_size; // размер самого массива, сколько пам€ти выделено под хранение нашей таблицы
    int size_all_non_nullptr; // сколько элементов у нас сейчас в массиве (с учетом deleted)
    int lastPos;
public:
    HashTable();
    void Resize();
    void Rehash();
    int Find(const int& value);
    Node GetNode(int ind);
    bool Remove(const int& value);
    bool Add(const int& value, int recNum);
    int getLastPos();
    int THash(const int& p) const;
    void printIndexes();
    ~HashTable();
};