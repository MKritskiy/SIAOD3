#include "HashManage.h"
using namespace std;



int HashOpenAdress(const Product& s, int table_size)
{
    int hash_result = s.ID % table_size;
    return hash_result;
}
HashTable::HashTable()
{
    buffer_size = default_size;
    size = 0;
    size_all_non_nullptr = 0;
    arr = new Node*[buffer_size];
    for (int i = 0; i < buffer_size; ++i)
        arr[i] = nullptr; // ��������� nullptr - �� ���� ���� �������� �����������, � ����� ������ �� ����� ������ �� ���������
}
void HashTable::Resize()
{
    int past_buffer_size = buffer_size;
    buffer_size *= 2;
    size_all_non_nullptr = 0;
    size = 0;
    Node** arr2 = new Node*[buffer_size];
    for (int i = 0; i < buffer_size; ++i)
        arr2[i] = nullptr;
    std::swap(arr, arr2);
    for (int i = 0; i < past_buffer_size; ++i)
    {
        if (arr2[i] && arr2[i]->state)
            Add(arr2[i]->value); // ��������� �������� � ����� ������
    }
    // �������� ����������� �������
    for (int i = 0; i < past_buffer_size; ++i)
        if (arr2[i])
            delete arr2[i];
    delete[] arr2;
}

void HashTable::Rehash()
{
    size_all_non_nullptr = 0;
    size = 0;
    Node** arr2 = new Node*[buffer_size];
    for (int i = 0; i < buffer_size; ++i)
        arr2[i] = nullptr;
    std::swap(arr, arr2);
    for (int i = 0; i < buffer_size; ++i)
    {
        if (arr2[i] && arr2[i]->state)
            Add(arr2[i]->value);
    }
    // �������� ����������� �������
    for (int i = 0; i < buffer_size; ++i)
        if (arr2[i])
            delete arr2[i];
    delete[] arr2;
}

int HashTable::Find(const Product& value)
{
    int h1 = THash(value); // ��������, ���������� �� ��������� �������
    int h2 = 1; // ��������, ������������� �� "���" �� �������
    int i = 0;
    while (arr[h1] != nullptr && i < buffer_size)
    {
        if (arr[h1]->value.ID == value.ID && arr[h1]->state)
            return h1; // ����� ������� ����
        h1 = (h1 + h2) % buffer_size;
        ++i; // ���� � ��� i >=  buffer_size, ������ �� ��� ������ ��������� ��� ������.
    }
    return -1;
}

bool HashTable::Remove(const Product& value)
{
    int h1 = THash(value);
    int h2 = 1;
    int i = 0;
    while (arr[h1] != nullptr && i < buffer_size)
    {
        if ((arr[h1]->value.ID == value.ID) && arr[h1]->state)
        {
            arr[h1]->state = false;
            --size;
            lastPos = h1;
            return true;
        }
        h1 = (h1 + h2) % buffer_size;
        ++i;
    }
    return false;
}

bool HashTable::Add(const Product& value)
{
    if (size + 1 > int(rehash_size * buffer_size))
        Resize();
    else if (size_all_non_nullptr > 2 * size)
        Rehash(); // ���������� �����, ��� ��� ������� ����� deleted-���������
    int h1 = THash(value);
    int h2 = 1;
    int i = 0;
    int first_deleted = -1; // ���������� ������ ���������� (���������) �������
    while (arr[h1] != nullptr && i < buffer_size)
    {
        if (arr[h1]->value.ID == value.ID && arr[h1]->state)
            return false; // ����� ������� ��� ����, � ������ ��� ������ ��������� ��������
        if (!arr[h1]->state) // ������� ����� ��� ������ ��������
        {
            first_deleted = h1;
            break;
        }
        h1 = (h1 + h2) % buffer_size;
        ++i;
    }
    if (first_deleted == -1) // ���� �� ������� ����������� �����, ������� ����� Node
    {
        arr[h1] = new Node(value);
        ++size_all_non_nullptr; // ��� ��� �� ��������� ���� ������, �� �������� ��������, ��� ��� ����� ������ ������
    }
    else
    {
        arr[first_deleted]->value = value;
        arr[first_deleted]->state = true;
    }
    lastPos = h1;
    ++size; // � � ����� ������ �� ��������� ���������� ���������
    return true;
}

int HashTable::getLastPos()
{
    return lastPos;
}
int HashTable::THash(const Product& p) const
{
    return HashOpenAdress(p, buffer_size);
}

void HashTable::printIndexes()
{
    for (int i = 0; i < buffer_size; i++)
    {
        if (arr[i] && arr[i]->state)
            cout << "ID: " << arr[i]->value.ID << "\tPos: " << i << endl;
    }
}
HashTable::~HashTable()
{
    for (int i = 0; i < buffer_size; ++i)
        if (arr[i])
            delete arr[i];
    delete[] arr;
}

