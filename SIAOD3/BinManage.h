#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Product.h"
using namespace std;
bool createBinFromTxt(string txtName, string binName);
bool addRecInBin(Product& p, string binName);
bool delIDRecInBin(string binName, int ID);
Product getOneProduct(string binName, int pos);
void printBinFile(string binName);
