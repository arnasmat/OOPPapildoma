//
// Created by User on 2025-05-17.
//

#include "zodzio_apdorojimas.h"

void eilutes_apdorojimas(std::stringstream& eilute) {
    const std::set<char> punctuation_marks = {
        '.', ',', ';', ':', '!', '?', '-' , '(', ')', '[', ']', '{', '}', '\'', '"', '/', '\\', '|', '@', '#', '$', '%', '^', '&', '*', '_', '+', '=', '<', '>', '`', '~'
    };
    // '—' nesigauna idet, nes jis UTC8 ar 16, o ne ascii :(

    char eilutes_char{};
    std::string result;
    while (eilute.get(eilutes_char)) {
        if (!punctuation_marks.contains(eilutes_char)) {
            result += eilutes_char;
        }
    }

    eilute.clear();
    eilute.str(result);
    result.clear();

    std::string zodis{};
    // gal sita daryt atskirame cikle ner labai efektyvu, bet ajjjj tingiu
    while (eilute >> zodis) {
        if (!result.empty()) {
            result += " ";
        }
        result += zodis;
    }

    eilute.clear();
    eilute.str(result);
}
