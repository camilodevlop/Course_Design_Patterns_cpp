// Created by Camilo Castillo on 27/06/2024
// Iterator Pattern

#include <iostream>
#include <type_traits>

//------------------------------------------------------------------------------

template <typename T>
concept Element = std::is_copy_constructible_v<T> && std::is_copy_assignable_v<T>;

template <typename U>
concept ElementU = std::is_copy_constructible_v<U> && std::is_copy_assignable_v<U>;

//template <typename T> requires Element<T> struct BinaryTree;
template <Element T> struct BinaryTree;

template <Element T >
class Node
{
    public:
        T value_ = T();
        Node<T>* left_ = nullptr;
        Node<T>* right_ = nullptr;
        Node<T>* parent_ = nullptr;
        BinaryTree<T>* tree_ = nullptr;

        Node(T value) : value_(value) {}
        Node(T value, Node<T>* left, Node<T>* right) : value_(value), 
            left_(left), right_(right) 
        {
            left_->tree_ = right_->tree_ = tree_;
            left_->parent_ = right_->parent_ = this;
        }
        void setTree(BinaryTree<T> *tree);
        
        ~Node() {
            if (left_) delete left_;
            if (right_) delete right_;
        }
};

template <Element T> void Node<T>::setTree(BinaryTree<T> *tree)
{
    this->tree_ = tree;
    if (left_) left_->setTree(tree);
    if (right_) right_->setTree(tree);
}

//------------------------------------------------------------------------------

template <Element T>
struct BinaryTree
{
    Node<T>* root_ = nullptr;

    BinaryTree(Node<T>* root) : root_(root), preOrder(*this) {
        root_->setTree(this); 
    }
    ~BinaryTree() { if (root_) delete root_; }

    template <ElementU U> struct PreOrderIterator;
    using Iterator = PreOrderIterator<T>;

    Iterator begin() {
        Node<T>* n = root_;
        if (n) 
            while (n->left_) n = n->left_;
        return Iterator(n);
    }

    Iterator end() { return Iterator(nullptr); }

    class PreOrderTraversal
    {
        public:
            PreOrderTraversal(BinaryTree<T>& tree) : tree_(tree) {}
            Iterator begin() { return tree_.begin(); }
            Iterator end() { return tree_.end(); }
        private:
            BinaryTree<T>& tree_;
    } preOrder;
};

template <Element T>
template <ElementU U> 
struct BinaryTree<T>::PreOrderIterator
{
    Node<U>* current_;

    explicit PreOrderIterator(Node<U>* current) : current_(current) {}

    bool operator!=(const PreOrderIterator<U>& other) const {
        return current_ != other.current_;
    }

    PreOrderIterator<U>& operator++() {
        if (current_->right_) {
            current_ = current_->right_;
            while (current_->left_) 
                current_ = current_->left_;
        } else {
            Node<U>* p = current_->parent_;
            while (p && current_ == p->right_) {
                current_ = p;
                p = p->parent_;
            }
            current_ = p;
        }
        return *this;
    }
    
    Node<U>& operator*() { return *current_; }
};

//------------------------------------------------------------------------------

int main()
{
    BinaryTree<std::string> tree(new Node<std::string>("Me",
            new Node<std::string>("Mother",
            new Node<std::string>("Mother's mother"),
            new Node<std::string>("Mother's father")),
            new Node<std::string>("Father")));

    for (auto it = tree.begin(); it != tree.end(); ++it)
        std::cout << (*it).value_ << std::endl;

    /*
    for (auto it : tree.preOrder)
        std::cout << it.value_ << std::endl;
    */

    return 0;
}

//------------------------------------------------------------------------------
