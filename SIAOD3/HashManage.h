#pragma once
#include <string>
#include <iostream>
#include "Product.h"
using namespace std;



int HashOpenAdress(const Product& s, int table_size);

struct Node
{
    Product value;
    bool state; // ���� �������� ����� state = false, ������ ������� ������� ��� ������ (deleted)
    int recNum;
    Node(const Product& val) : value(val), state(true) {}
};

class HashTable
{
private:
    static const int default_size = 8; // ��������� ������ ����� �������
    constexpr static const double rehash_size = 0.75; // �����������, ��� ������� ���������� ���������� �������
    Node** arr; // �������������� � ������� ����� �������� ��������� Node*
    int size; // ������� ��������� � ��� ������ � ������� (��� ����� deleted)
    int buffer_size; // ������ ������ �������, ������� ������ �������� ��� �������� ����� �������
    int size_all_non_nullptr; // ������� ��������� � ��� ������ � ������� (� ������ deleted)
    int lastPos;
public:
    HashTable();
    void Resize();
    void Rehash();
    int Find(const Product& value);
    bool Remove(const Product& value);
    bool Add(const Product& value);
    int getLastPos();
    int THash(const Product& p) const;
    void printIndexes();
    ~HashTable();
};