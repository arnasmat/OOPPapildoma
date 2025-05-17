//
// Created by User on 2025-05-17.
//

#include "zodzio_apdorojimas.h"

#include <regex>

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

//Cia su regexu parase mostly chatukas, nes busiu honest as regexo normaliai nepernesu
void link_apdorojimas(std::vector<std::wstring>& links, std::wstringstream& eilute) {
    // Use wregex instead of regex for wide strings
    std::wregex url_regex(LR"(\b((https?:\/\/)?([a-zA-Z0-9\-]+\.)+[a-zA-Z]{2,}(:\d+)?(\/\S*)?)\b)");

    std::wstring text = eilute.str();

    // Find all matches using wide character versions
    std::wsmatch matches;
    std::wstring::const_iterator searchStart(text.cbegin());

    while (std::regex_search(searchStart, text.cend(), matches, url_regex)) {
        // No conversion needed, already working with wstring
        std::wstring link = matches[1].str();
        links.push_back(link);

        // Move the search position forward
        searchStart = matches.suffix().first;
    }
}

/*
 *cia buvo mano bandymas be regexo, bet supratau, kad aj turbut geriau yra su regexu
 *
void link_apdorojimas(std::vector<std::wstring>& links, std:: wstringstream& eilute) {
// cia gal durnas metodas, bet aj galvoju tsg patikrint ar dalykas baigiasi su kazkokiu TLD, pvz. vu.lt baigiasi su .lt. Durnas sprendimas bet aj.
    // Alternatyva butu turbut ieskot kur keli zodziai yra.atskirti.tik.tasku, bet ajj kzn
    // su regexu butu sunku visus linkus aptikt

    //sita chatukas sugeneravo lmao
std::set<std::string> tlds = {
    // Generic top-level domains (gTLDs)
    "com", "org", "net", "int", "edu", "gov", "mil", "info", "biz", "name", "pro", "coop", "aero", "museum", "jobs",
    "mobi", "travel", "asia", "tel", "cat", "xxx", "post", "geo", "idv", "arpa", "dev", "app", "blog", "shop",
    "site", "online", "store", "tech", "xyz", "club", "website", "space", "fun", "top", "win", "art", "design",
    "cloud", "news", "live", "love", "life", "world", "today", "center", "digital", "email", "finance", "games",
    "group", "health", "media", "photo", "social", "solutions", "team", "tools", "video", "zone", "ai", "io", "co",

    // Country code TLDs (ccTLDs)
    "ac", "ad", "ae", "af", "ag", "ai", "al", "am", "ao", "aq", "ar", "as", "at", "au", "aw", "ax", "az",
    "ba", "bb", "bd", "be", "bf", "bg", "bh", "bi", "bj", "bm", "bn", "bo", "br", "bs", "bt", "bv", "bw", "by", "bz",
    "ca", "cc", "cd", "cf", "cg", "ch", "ci", "ck", "cl", "cm", "cn", "co", "cr", "cu", "cv", "cw", "cx", "cy", "cz",
    "de", "dj", "dk", "dm", "do", "dz",
    "ec", "ee", "eg", "er", "es", "et", "eu",
    "fi", "fj", "fk", "fm", "fo", "fr",
    "ga", "gb", "gd", "ge", "gf", "gg", "gh", "gi", "gl", "gm", "gn", "gp", "gq", "gr", "gt", "gu", "gw", "gy",
    "hk", "hm", "hn", "hr", "ht", "hu",
    "id", "ie", "il", "im", "in", "io", "iq", "ir", "is", "it",
    "je", "jm", "jo", "jp",
    "ke", "kg", "kh", "ki", "km", "kn", "kp", "kr", "kw", "ky", "kz",
    "la", "lb", "lc", "li", "lk", "lr", "ls", "lt", "lu", "lv", "ly",
    "ma", "mc", "md", "me", "mg", "mh", "mk", "ml", "mm", "mn", "mo", "mp", "mq", "mr", "ms", "mt", "mu", "mv", "mw", "mx", "my", "mz",
    "na", "nc", "ne", "nf", "ng", "ni", "nl", "no", "np", "nr", "nu", "nz",
    "om",
    "pa", "pe", "pf", "pg", "ph", "pk", "pl", "pm", "pn", "pr", "pt", "pw", "py",
    "qa",
    "re", "ro", "rs", "ru", "rw",
    "sa", "sb", "sc", "sd", "se", "sg", "sh", "si", "sj", "sk", "sl", "sm", "sn", "so", "sr", "ss", "st", "sv", "sx", "sy", "sz",
    "tc", "td", "tf", "tg", "th", "tj", "tk", "tl", "tm", "tn", "to", "tr", "tt", "tv", "tz",
    "ua", "ug", "uk", "um", "us", "uy", "uz",
    "va", "vc", "ve", "vg", "vi", "vn", "vu",
    "wf", "ws",
    "ye", "yt",
    "za", "zm", "zw"
};

    std::wstring zodis;
    while (eilute >> zodis) {
        size_t lastDotPos = zodis.find_last_of(L'.');
        if (lastDotPos != std::wstring::npos) {
            std::wstring tld = zodis.substr(lastDotPos + 1);
            if (!tld.empty()) {
                if (tld.back() == L'\\' || tld.back()==L'/') {
                    tld.pop_back();
                }
                // Convert wstring to string before checking in tlds set
                std::string narrow_tld(tld.begin(), tld.end());
                if (tlds.contains(narrow_tld)) {
                    links.push_back(zodis);
                }
            }
        }
    }
}*/

void input(RBTreeMap<std::wstring>& Tree, std::vector<std::wstring>& links , const std::string& input) {
    // Lietuviskos raides ir tam tikri lt simboliai neveikia normaliai, nes mingw c++20 nesupportina utc-8 normaliai. whatever
    try {
        std::locale::global(std::locale("lt-LT"));
    } catch (std::runtime_error& e) {
        std::cout << "Tarptautinės raidės gali veikti neteisingai" << e.what() << std::endl;
    }

    std::wifstream in{input};
    if (!in || !in.is_open()) {
        std::cerr<<"Failas nerastas"<<std::endl;
        throw std::runtime_error("Failed to open file");
    }

    in.imbue(std::locale());

    std::wstring line;
    int lineNumber = 1;

    while (std::getline(in, line)) {
        std::wstringstream lineStream(line);
        std::wstringstream linkStream(lineStream.str());
        link_apdorojimas(links, linkStream);
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
