//
// Created by User on 2025-05-17.
//

#ifndef ZODZIO_APDOROJIMAS_H
#define ZODZIO_APDOROJIMAS_H

#include <iosfwd>
#include <set>
#include <sstream>
#include "rbtreemap.h"
#include <cwchar>
#include <wctype.h>
#include <cwctype>

void eilutes_apdorojimas(std::wstringstream& eilute);
void input(RBTreeMap<std::wstring>& Tree, const std::string& input="../data/input/input.txt");

#endif //ZODZIO_APDOROJIMAS_H
