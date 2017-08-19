#ifndef PPNG_H
#define PPNG_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <cassert>
#include <png.h>

using namespace std;

void png_read(string filename, int& w, int& h, vector<uint8_t>& data, map<string, int>& meta);

void png_write(string filename, void* pv, int w, int h);

#endif
