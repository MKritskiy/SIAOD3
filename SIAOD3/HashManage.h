#pragma once
#include <string>
#include <iostream>
#include "Product.h"
using namespace std;



int HashOpenAdress(const int& key, int table_size);

struct Node
{
    int key;
    bool state; // ���� �������� ����� state = false, ������ ������� ������� ��� ������ (deleted)
    int recNum;
    Node(const int& val) : key(val), state(true), recNum(-1) {}
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
    int Find(const int& value);
    Node GetNode(int ind);
    bool Remove(const int& value);
    bool Add(const int& value, int recNum);
    int getLastPos();
    int THash(const int& p) const;
    void printIndexes();
    ~HashTable();
};