#include "HashManage.h"
using namespace std;



int HashOpenAdress(const int& key, int table_size)
{
    int hash_result = key % table_size;
    return hash_result;
}
HashTable::HashTable()
{
    buffer_size = default_size;
    size = 0;
    size_all_non_nullptr = 0;
    arr = new Node*[buffer_size];
    for (int i = 0; i < buffer_size; ++i)
        arr[i] = nullptr; // заполняем nullptr - то есть если значение отсутствует, и никто раньше по этому адресу не обращался
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
            Add(arr2[i]->key, arr2[i]->recNum); // добавляем элементы в новый массив
    }
    // удаление предыдущего массива
    for (int i = 0; i < past_buffer_size; ++i)
        if (arr2[i])
            delete arr2[i];
    delete[] arr2;
}

void HashTable::Rehash()
{
    size_all_non_nullptr = 0;
    size = 0;
    if (size_all_non_nullptr > buffer_size / 2)
        buffer_size /= 2;
    Node** arr2 = new Node*[buffer_size];
    for (int i = 0; i < buffer_size; ++i)
        arr2[i] = nullptr;
    std::swap(arr, arr2);
    for (int i = 0; i < buffer_size; ++i)
    {
        if (arr2[i] && arr2[i]->state)
            Add(arr2[i]->key, arr2[i]->recNum);
    }
    // удаление предыдущего массива
    for (int i = 0; i < buffer_size; ++i)
        if (arr2[i])
            delete arr2[i];
    delete[] arr2;
}

int HashTable::Find(const int& key)
{
    int h1 = THash(key); // значение, отвечающее за начальную позицию
    int h2 = 1; // значение, ответственное за "шаг" по таблице
    int i = 0;
    while (arr[h1] != nullptr && i < buffer_size)
    {
        if (arr[h1]->key == key && arr[h1]->state)
            return h1; // такой элемент есть
        h1 = (h1 + h2) % buffer_size;
        ++i; // если у нас i >=  buffer_size, значит мы уже обошли абсолютно все ячейки.
    }
    return -1;
}
Node HashTable::GetNode(int ind)
{
    if (ind < 0)
        return Node(-1);
    return *arr[ind];
}
bool HashTable::Remove(const int& key)
{
    int h1 = THash(key);
    int h2 = 1;
    int i = 0;
    while (arr[h1] != nullptr && i < buffer_size)
    {
        if ((arr[h1]->key == key) && arr[h1]->state)
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

bool HashTable::Add(const int& key, int recNum)
{
    if (size + 1 > int(rehash_size * buffer_size))
        Resize();
    else if (size_all_non_nullptr > 2 * size)
        Rehash(); // происходит рехеш, так как слишком много deleted-элементов
    int h1 = THash(key);
    int h2 = 1;
    int i = 0;
    int first_deleted = -1; // запоминаем первый подходящий (удаленный) элемент
    while (arr[h1] != nullptr && i < buffer_size)
    {
        if (arr[h1]->key == key && arr[h1]->state)
            return false; // такой элемент уже есть, а значит его нельзя вставлять повторно
        if (!arr[h1]->state) // находим место для нового элемента
        {
            cout << "Colision was solved!\n";
            first_deleted = h1;
            break;
        }
        h1 = (h1 + h2) % buffer_size;
        ++i;
    }
    if (first_deleted == -1) // если не нашлось подходящего места, создаем новый Node
    {
        arr[h1] = new Node(key);
        arr[h1]->recNum = recNum;
        ++size_all_non_nullptr; // так как мы заполнили один пробел, не забываем записать, что это место теперь занято
    }
    else
    {
        arr[first_deleted]->key = key;
        arr[first_deleted]->recNum = recNum;
        arr[first_deleted]->state = true;
    }
    lastPos = h1;
    ++size; // и в любом случае мы увеличили количество элементов
    return true;
}

int HashTable::getLastPos()
{
    return lastPos;
}
int HashTable::THash(const int& key) const
{
    return HashOpenAdress(key, buffer_size);
}

void HashTable::printIndexes()
{
    for (int i = 0; i < buffer_size; i++)
    {
        if (arr[i] && arr[i]->state)
            cout << "ID: " << arr[i]->key<<"\tRecord number: "<< arr[i]->recNum << "\tPos: " << i << endl;
    }
}
HashTable::~HashTable()
{
    for (int i = 0; i < buffer_size; ++i)
        if (arr[i])
            delete arr[i];
    delete[] arr;
}

