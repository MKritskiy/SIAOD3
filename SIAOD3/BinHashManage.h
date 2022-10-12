#pragma once
#include "BinManage.h"
#include "HashManage.h"

bool readAndInsert(string binName, int pos, HashTable& table);
bool delRecFromFileAndTable(string binName, HashTable& table, int key);
Product findRec(string binName, HashTable& table, int key);