//
// Created by User on 2025-05-17.
//

#include "zodzio_apdorojimas.h"

#include "rbtreemap.h"


void eilutes_apdorojimas(std::wstringstream& eilute) {


    const std::set<wchar_t> punctuation_marks = {
        L'.', L',', L';', L':', L'!', L'?', L'-', L'(', L')', L'[', L']', L'{', L'}', L'\'', L'"', L'/', L'\\', L'|', L'@', L'#', L'$', L'%', L'^', L'&', L'*', L'_', L'+', L'=', L'<', L'>', L'`', L'~',
        L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9', L'0',
        L'—', L'–', L'−', L'‐', L'‒', L'―'
    };
    // VIS DAR – NEVEIKIA KAZKODEL.

    wchar_t eilutes_char{};
    std::wstring result;
    while (eilute.get(eilutes_char)) {
        if (!punctuation_marks.contains(eilutes_char)) {
            result += towlower(eilutes_char);
        }
    }

    eilute.clear();
    eilute.str(result);
}

void input(RBTreeMap<std::wstring>& Tree, const std::string& input) {

    // Lietuviskos raides ir tam tikri lt simboliai neveikia normaliai, nes mingw c++20 nesupportina utc-8 normaliai. whatever
    try {
        std::locale::global(std::locale("lt-LT"));
    } catch (std::runtime_error& e) {
        std::cout << "Tarptautinės raidės gali veikti neteisingai" << e.what() << std::endl;
    }

    std::wifstream in{input};
    std::wstringstream buffer{};
    if (!in || !in.is_open()) {
        throw std::runtime_error("Failed to open file");
    }
    in.imbue(std::locale());

    buffer << in.rdbuf();
    in.close();
    eilutes_apdorojimas(buffer);
    std::wstring zodis{};
    while (buffer >> zodis) {
        Tree.insert(zodis);
    }
}
