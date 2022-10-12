#include "BinHashManage.h"

bool readAndInsert(string binName, int pos, HashTable& table)
{
    Product tmp = getOneProduct(binName, pos);
    if (tmp.ID >= 0 && table.Add(tmp.ID, pos))
        return true;
    else
        return false;
}

bool delRecFromFileAndTable(string binName, HashTable& table, int key)
{
    if (delIDRecInBin(binName, key) && table.Remove(key))
        return true;
    else
        return false;
}

Product findRec(string binName, HashTable& table, int key)
{
    int recNum = table.GetNode(table.Find(key)).recNum;
    if (recNum < 0)
        throw 0;
    Product tmp = getOneProduct(binName, recNum);
    return tmp;
}
