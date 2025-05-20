#include <sstream>

#include "rbtreemap.h"
#include "zodzio_apdorojimas.h"
#include "fstream"
#include <vector>

int main() {

    //veikia tik su vs kompiliatorium, nes mignw tik linuxams normaliai supportina lol
    try {
        std::locale::global(std::locale(::setlocale(LC_ALL,"lt_LT.UTF-8")));
    } catch (std::runtime_error& e) {
        std::cout << "Tarptautinės raidės gali veikti neteisingai" << e.what() << std::endl;
    }

    // TODO - padaryt sita grazesni
    std::vector<std::wstring> links;
    RBTreeMap<std::wstring> zodziai;
    input(zodziai, links, "../data/input/input.txt");
    std::wstringstream out{};
    zodziai.navigate_tree(out);
    std::wofstream out2{"../data/output/output.txt"};
    out2 << out.str();
    out2.close();

    std::wstringstream out22{};
    std::wofstream out3{"../data/output/lentele.txt"};
    zodziai.navigate_tree_lentele(out22);
    out3 << out22.str();
    out3.close();

    std::wofstream out4{"../data/output/links.txt"};
    for (const auto& link : links) {
        out4 << link << std::endl;
    }
    out4.close();
}


/*std::ifstream inTLD{"../data/input/inputTLD.txt"};
std::ofstream outTLD{"../data/output/TLDS"};

outTLD << "std::set<std::wstring> tlds = {";
std::string line;
std::getline(inTLD, line);

while (inTLD >> line) {
    outTLD << "L\"" << line <<"\", ";
}
outTLD << "};";
inTLD.close();
outTLD.close();*/
