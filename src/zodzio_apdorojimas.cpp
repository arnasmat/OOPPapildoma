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
    // VIS DAR – NEVEIKIA DEL ENCODING URGHZTHIZWD! As myliu programavima ir problemu sprendima !

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
    if (!in || !in.is_open()) {
        throw std::runtime_error("Failed to open file");
    }
    in.imbue(std::locale());

    std::wstring line;
    int lineNumber = 1;

    while (std::getline(in, line)) {
        std::wstringstream lineStream(line);
        eilutes_apdorojimas(lineStream);

        std::wstring zodis;
        int zodzioNumber{1};
        while (lineStream >> zodis) {
            Tree.insert(zodis, lineNumber, zodzioNumber);
            zodzioNumber++;
        }

        lineNumber++;
    }

    in.close();
}
