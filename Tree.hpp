#ifndef DSV_TREE_H
#define DSV_TREE_H


#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <tuple>

enum Color {
    RED,
    BLACK
};

template <typename T>
struct Node 
{
    T data;
    Node<T> *left;
    Node<T> *right;
    Node<T> *parent;
    Color color;
    
    Node (T data): data(data), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};

template <typename T>
class RedBlackTree 
{
    Node<T> *root;
    
    void leftRotate(Node<T> *node);
    void rightRotate(Node<T> *node);
    void insertFixUp(Node<T> *node);
    void deleteFixUp(Node<T> *node, Node<T> *parent);
    void transplant(Node<T> *u, Node<T> *v);
    Node<T> *findMin(Node<T> *node);
    Node<T> *findMax(Node<T> *node);
    Node<T> *findSuccessor(Node<T> *node);
    void clear(Node<T> *node);    
    
public:
    RedBlackTree (): root(nullptr) {}
    ~RedBlackTree ();
    
    void insert(T data);
    void remove(T data);
    void printTree();
    void clear();
    std::vector< std::tuple< int, char, int, int > > getTree();
};


template <typename T>
RedBlackTree<T>::~RedBlackTree() {
    clear(root);
}

template <typename T>
void RedBlackTree<T>::printTree() {
    std::queue< std::tuple< Node<T>*, int, int > > q;
    q.push(std::make_tuple(root, 1, 1));

    while (!q.empty()) {
        int size = q.size();

        while (size--) {
            std::tuple< Node<T>*, int, int > curr = q.front();
            q.pop();

            Node<T>* currentNode = std::get<0>(curr);
            int currentTier = std::get<1>(curr);
            int positionInTier = std::get<2>(curr);

            if (currentNode == nullptr) {
                std::cout << "NULL:" << currentTier;
            } else {
                std::cout << currentNode->data << "(" << (currentNode->color == RED ? "RED" : "BLACK") << "):" << currentTier << " (" << positionInTier << ")";
            }

            std::cout << " ";

            if (currentNode != nullptr) {
                q.push(std::make_tuple(currentNode->left, currentTier + 1, positionInTier * 2 - 1));
                q.push(std::make_tuple(currentNode->right, currentTier + 1, positionInTier * 2));
            }
        }

        std::cout << std::endl;
    }
}


template <typename T>
std::vector< std::tuple< int, char, int, int > > RedBlackTree<T>::getTree() {
    std::vector< std::tuple< int, char, int, int > > r; // data, color, tier, pos

    if (root == nullptr)
    {
        r.push_back(std::make_tuple(0, 'n', 1, 1));
        return r;
    }

    std::queue< std::tuple< Node<T>*, int, int > > q;
    q.push(std::make_tuple(root, 1, 1));

    while (!q.empty()) {
        int size = q.size();

        while (size--) {
            std::tuple< Node<T>*, int, int > curr = q.front();
            q.pop();

            Node<T>* currentNode = std::get<0>(curr);
            int currentTier = std::get<1>(curr);
            int positionInTier = std::get<2>(curr);

            if (currentNode == nullptr) {
                r.push_back(std::make_tuple(0, 'n', currentTier, 0));
            } else {
                r.push_back(std::make_tuple(currentNode->data, (currentNode->color == RED ? 'r' : 'b'), currentTier, positionInTier));
            }

            if (currentNode != nullptr) {
                q.push(std::make_tuple(currentNode->left, currentTier + 1, positionInTier * 2 - 1));
                q.push(std::make_tuple(currentNode->right, currentTier + 1, positionInTier * 2));
            }
        }
    }

    return r;
}

template <typename T>
void RedBlackTree<T>::leftRotate(Node<T> *node) {
    Node<T> *rightChild = node->right;
    node->right = rightChild->left;
    if (rightChild->left != nullptr) {
        rightChild->left->parent = node;
    }
    rightChild->parent = node->parent;
    if (node->parent == nullptr) {
        root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }
    rightChild->left = node;
    node->parent = rightChild;
}

template <typename T>
void RedBlackTree<T>::rightRotate(Node<T> *node) {
    Node<T> *leftChild = node->left;
    node->left = leftChild->right;
    if (leftChild->right != nullptr) {
        leftChild->right->parent = node;
    }
    leftChild->parent = node->parent;
    if (node->parent == nullptr) {
        root = leftChild;
    } else if (node == node->parent->right) {
        node->parent->right = leftChild;
    } else {
        node->parent->left = leftChild;
    }
    leftChild->right = node;
    node->parent = leftChild;
}

template <typename T>
void RedBlackTree<T>::insert(T data) {
    Node<T> *node = new Node<T>(data);
    Node<T> *current = root;
    Node<T> *parent = nullptr;
    while (current != nullptr) {
        parent = current;
        if (node->data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    node->parent = parent;
    if (parent == nullptr) {
        root = node;
    } else if (node->data < parent->data) {
        parent->left = node;
    } else {
        parent->right = node;
    }
    insertFixUp(node);
}

template <typename T>
void RedBlackTree<T>::insertFixUp(Node<T> *node) {
    while (node->parent != nullptr && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            Node<T> *uncle = node->parent->parent->right;
            if (uncle != nullptr && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightRotate(node->parent->parent);
            }
        } else {
            Node<T> *uncle = node->parent->parent->left;
            if (uncle != nullptr && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                leftRotate(node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

template <typename T>
void RedBlackTree<T>::remove(T data) {
    Node<T> *node = root;
    while (node != nullptr) {
        if (data == node->data) {
            break;
        } else if (data < node->data) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    if (node == nullptr) {
        return;
    }
    Color originalColor = node->color;
    Node<T> *child = nullptr;
    if (node->left == nullptr) {
        child = node->right;
        transplant(node, node->right);
    } else if (node->right == nullptr) {
        child = node->left;
        transplant(node, node->left);
    } else {
        Node<T> *successor = findSuccessor(node);
        originalColor = successor->color;
        child = successor->right;
        if (successor->parent == node) {
            if (child != nullptr) {
                child->parent = successor;
            }
        } else {
            transplant(successor, successor->right);
            successor->right = node->right;
            successor->right->parent = successor;
        }
        transplant(node, successor);
        successor->left = node->left;
        successor->left->parent = successor;
        successor->color = node->color;
    }
    delete node;
    if (originalColor == BLACK) {
        if (child != nullptr) {
            deleteFixUp(child, child->parent);
        }
    }
}

template <typename T>
void RedBlackTree<T>::deleteFixUp(Node<T> *node, Node<T> *parent) {
    while (node != root && (node == nullptr || node->color == BLACK)) {
        if (node == parent->left) {
            Node<T> *sibling = parent->right;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                parent->color = RED;
                leftRotate(parent);
                sibling = parent->right;
            }
            if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
            (sibling->right == nullptr || sibling->right->color == BLACK)) {
                sibling->color = RED;
                node = parent;
                parent = parent->parent;
            } else {
                if (sibling->right == nullptr || sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rightRotate(sibling);
                    sibling = parent->right;
                }
                sibling->color = parent->color;
                parent->color = BLACK;
                sibling->right->color = BLACK;
                leftRotate(parent);
                node = root;
            }
        } else {
            Node<T> *sibling = parent->left;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                parent->color = RED;
                rightRotate(parent);
                sibling = parent->left;
            }
            if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
            (sibling->right == nullptr || sibling->right->color == BLACK)) {
                sibling->color = RED;
                node = parent;
                parent = parent->parent;
            } else {
                if (sibling->left == nullptr || sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    leftRotate(sibling);
                    sibling = parent->left;
                }
                sibling->color = parent->color;
                parent->color = BLACK;
                sibling->left->color = BLACK;
                rightRotate(parent);
                node = root;
            }
        }
    }
    if (node != nullptr) {
        node->color = BLACK;
    }
}

template <typename T>
void RedBlackTree<T>::transplant(Node<T> *u, Node<T> *v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

template <typename T>
void RedBlackTree<T>::clear() {
    clear(root);
    root = nullptr;
}

template <typename T>
void RedBlackTree<T>::clear(Node<T> *node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template<typename T>
Node<T>* RedBlackTree<T>::findMin(Node<T>* node) {
    if (node == nullptr)
        return nullptr;
    
    while (node->left != nullptr)
        node = node->left;
    
    return node;
}

template<typename T>
Node<T>* RedBlackTree<T>::findMax(Node<T>* node) {
    if (node == nullptr)
        return nullptr;
    
    while (node->right != nullptr)
        node = node->right;
    
    return node;
}

template<typename T>
Node<T>* RedBlackTree<T>::findSuccessor(Node<T>* node) {
    if (node->right != nullptr)
        return findMin(node->right);
    
    Node<T>* parent = node->parent;
    
    while (parent != nullptr && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    
    return parent;
}


#endif //DSV_TREE_H