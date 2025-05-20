#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <fstream>
#include <vector>

// Cia yra mano ADS uzduociai semestro pradzioje implementuotas RB Medis. Truputi ji modifikavau, kad jis butu kaip std::map :)
// cia sitam pritaikymui tiesiog implementuoju, kad pair visada yra int ir ji naudoju kiekio skaiciavimui, nes tam jo ir reikia sioje uzduotyje

template <typename T>
class RBTreeMap {
private:
    struct Node {
        // TODO - cj cia pair net nereikia, jeigu naudoju vektoriu. Galima cj tsg padaryt pasikartojimo_vietos.size(). aj tng keist db
        T key{};
        int pair{0};
        std::vector<std::pair<int,int>> pasikartojimo_vietos{};
        bool red{true};
        Node* parent{};
        Node* left{};
        Node* right{};
        Node(T key, Node* parent) : key(key), red(true), parent(parent), left(nullptr), right(nullptr){}
    };

    Node* root{nullptr};

    void rotate_left(Node* node) {
        Node* child = node->right;
        node->right = child->left;
        if (node->right != nullptr)
            node->right->parent = node;
        child->parent = node->parent;
        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->left)
            node->parent->left = child;
        else
            node->parent->right = child;
        child->left = node;
        node->parent = child;
    }

    void rotate_right(Node* node) {
        Node* child = node->left;
        node->left = child->right;
        if (node->left != nullptr)
            node->left->parent = node;
        child->parent = node->parent;
        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->left)
            node->parent->left = child;
        else
            node->parent->right = child;
        child->right = node;
        node->parent = child;
    }

    void insert_fixup(Node* node) {
        while (node->parent && node->parent->red) {
            if (node->parent == node->parent->parent->left) {
                Node* uncle = node->parent->parent->right;

                if (uncle && uncle->red) {  // Case 1: Red uncle
                    node->parent->red = false;
                    uncle->red = false;
                    node->parent->parent->red = true;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {  // Case 2: Left rotation needed
                        node = node->parent;
                        rotate_left(node);
                    }
                    // Case 3: Right rotation
                    node->parent->red = false;
                    node->parent->parent->red = true;
                    rotate_right(node->parent->parent);
                }
            } else {  // Symmetric cases for the right child
                Node* uncle = node->parent->parent->left;

                if (uncle && uncle->red) {  // Case 1: Red uncle
                    node->parent->red = false;
                    uncle->red = false;
                    node->parent->parent->red = true;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {  // Case 2: Right rotation needed
                        node = node->parent;
                        rotate_right(node);
                    }
                    // Case 3: Left rotation
                    node->parent->red = false;
                    node->parent->parent->red = true;
                    rotate_left(node->parent->parent);
                }
            }
        }
        root->red = false;
    }

    void navigate_tree_helper(Node* node, std::wstringstream& out) {
        if (node == nullptr) {
            return;
        }
        navigate_tree_helper(node->left, out);
        out << node->key << " " << node->pair<< "\n";
        navigate_tree_helper(node->right, out);
    }

    void navigate_tree_lentele_helper(Node* node, std::wstringstream& out) {
        if (node == nullptr) {
            return;
        }

        navigate_tree_lentele_helper(node->left, out);

        out << node->key << " " << node->pair << " | ";
        for (int i = 0; i < node->pasikartojimo_vietos.size(); i++) {
            out << node->pasikartojimo_vietos[i].first << "eil. "
                << node->pasikartojimo_vietos[i].second;
            if (i < node->pasikartojimo_vietos.size() - 1) {
                out << ", ";
            }
        }
        out << "\n";

        navigate_tree_lentele_helper(node->right, out);
    }


void remove_fixup(Node*& node) {
    while (node != root && node && node->red == false) {
        if (node->parent == nullptr) break; // Added null check for parent
        if (node == node->parent->left) {
            Node* sibling = node->parent->right;
            if (sibling && sibling->red == true) {
                sibling->red = false;
                node->parent->red = true;
                rotate_left(node->parent);
                sibling = node->parent->right;
            }
            if ((sibling->left == nullptr || sibling->left->red == false) &&
                (sibling->right == nullptr || sibling->right->red == false)) {
                sibling->red = true;
                node = node->parent;
            } else {
                if (sibling->right == nullptr || sibling->right->red == false) {
                    if (sibling->left != nullptr)
                        sibling->left->red = false;
                    sibling->red = true;
                    rotate_right(sibling);
                    sibling = node->parent->right;
                }
                sibling->red = node->parent->red;
                node->parent->red = false;
                if (sibling->right != nullptr)
                    sibling->right->red = false;
                rotate_left(node->parent);
                node = root;
            }
        } else {
            Node* sibling = node->parent->left;
            if (sibling && sibling->red == true) {
                sibling->red = false;
                node->parent->red = true;
                rotate_right(node->parent);
                sibling = node->parent->left;
            }
            if ((sibling->left == nullptr || sibling->left->red == false) &&
                (sibling->right == nullptr || sibling->right->red == false)) {
                sibling->red = true;
                node = node->parent;
            } else {
                if (sibling->left == nullptr || sibling->left->red == false) {
                    if (sibling->right != nullptr)
                        sibling->right->red = false;
                    sibling->red = true;
                    rotate_left(sibling);
                    sibling = node->parent->left;
                }
                sibling->red = node->parent->red;
                node->parent->red = false;
                if (sibling->left != nullptr)
                    sibling->left->red = false;
                rotate_right(node->parent);
                node = root;
            }
        }
    }
    if (node) node->red = false;
}

    void transplant(Node*& u, Node*& v)
    {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v != nullptr)
            v->parent = u->parent;
    }

    static Node* minimum(Node* node) {
        while(node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

public:

    RBTreeMap() = default;
    ~RBTreeMap() = default;

    void insert(T key, int lineNumber, int zodzioNumber) {
        // TODO - gal cia padaryt, kad nesearchintu kiekviena karta, nes bsk redundant operacijos
        Node* found = this->search(key);
        if(found != nullptr) {
            ++found->pair;
            found->pasikartojimo_vietos.push_back({lineNumber, zodzioNumber});
            return;
        }
        Node* temp = root;
        Node* parent = nullptr;

        while (temp != nullptr) {
            parent = temp;
            if (key < temp->key) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }

        Node* newNode = new Node(key, parent);
        if (parent == nullptr) {
            root = newNode;
        } else if (key < parent->key) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        ++newNode->pair;
        newNode->pasikartojimo_vietos.push_back({lineNumber, zodzioNumber});
        insert_fixup(newNode);
    }

    void remove(T key) {

        Node* found = this->search(key);
        if(found->pair > 1) {
            --found->pair;
            return;
        }

        Node* node = root;
        Node* temp = nullptr;
        Node* temp2= nullptr;
        Node* temp3= nullptr;
        while (node != nullptr) {
            if (node->key == key) {
                temp = node;
            }

            if (node->key <= key) {
                node = node->right;
            }
            else {
                node = node->left;
            }
        }

        if (temp == nullptr) {
            return;
        }

        temp2= temp;
        bool yOriginalColor = temp2->red;
        if (temp->left == nullptr) {
            temp3= temp->right;
            transplant(temp, temp->right);
        }
        else if (temp->right == nullptr) {
            temp3= temp->left;
            transplant(temp, temp->left);
        }
        else {
            temp2= minimum(temp->right);
            yOriginalColor = temp2->red;
            temp3= temp2->right;
            if (temp2->parent == temp) {
                if (temp3!= nullptr)
                    temp3->parent = temp2;
            }
            else {
                transplant(temp2, temp2->right);
                temp2->right = temp->right;
                temp2->right->parent = temp2;
            }
            transplant(temp, temp2);
            temp2->left = temp->left;
            temp2->left->parent = temp2;
            temp2->red = temp->red;
        }
        delete temp;
        if (yOriginalColor == false) {
            remove_fixup(temp3);
        }
    }

    Node* search(T key) {
        Node* node = root;
        while(node != nullptr && node->key != key) {
            if(key<node->key) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return node;
    }

    void navigate_tree(std::wstringstream& out) {
        navigate_tree_helper(root, out);
    }

    void navigate_tree_lentele(std::wstringstream& out) {
        navigate_tree_lentele_helper(root, out);
    }

};

#endif // RBTREE_H
