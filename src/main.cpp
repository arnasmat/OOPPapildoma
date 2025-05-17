#include <sstream>

#include "rbtreemap.h"
#include "zodzio_apdorojimas.h"
#include "fstream"

int main() {
    /*RBTreeMap<int> tree;
    /*tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(5);
    tree.insert(7);
    for(int i=0; i<100; i++) {
        tree.insert(i);
    }

    tree.remove(10);
    for(int i=0; i<100; i=i+2) {
        tree.remove(i);
    }

    std::cout<<(tree.search(11) ? "Found" : "Not found")<<std::endl;
    std::cout<<(tree.search(10000) ? "Found" : "Not found")<<std::endl;#1#

    tree.insert(10);
    tree.insert(10);
    tree.insert(10);
    tree.insert(10);
    tree.insert(10);
    tree.remove(10);

    tree.navigate_tree();
    std::stringstream text{"Labas, rytas! Aš Noriu suvalgyti Tavo MOTINĄ! ! !         Kaip gyveni"};
    eilutes_apdorojimas(text);
    std::ofstream out{"../data/output/output.txt"};
    out << text.str();
    out.close();*/

    // TODO - padaryt sita grazesni
    RBTreeMap<std::wstring> zodziai;
    input(zodziai);
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

}