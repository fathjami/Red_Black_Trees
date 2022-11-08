#pragma once
#include <iostream>
#include <functional>
#include <memory>
#include <__tree>
#include <map>

# define BOLD_RED       "\033[1;31mRED\e[0m"
# define BLCK			"\e[33;2;37mBLACK\e[0m"
# define RESET			"\e[0m"

namespace ft
{
    enum color{
        RED,
        BLACK
    };

    enum _child{
        LEFT,
        RIGHT,
        NONE
    };

#define COUNT 10

    template<typename T, class Compare = std::less<T> , class Allocator = std::allocator<T> >
    class BST
    {

    public:
        typedef T           value_type;
        typedef size_t      size_type;


        struct _node
        {
            value_type  _data;
            _node*      _parent;
            _node*      _left_c;
            _node*      _right_c;
            color       _color;

        };

        typedef std::allocator<_node>   alloc_type;

        typedef _node* node_ptr;
        typedef _node& node_reference;
        typedef Compare compare_func;

    protected:
        alloc_type      _alloc;
        compare_func    _cmp;
        node_ptr        _root;
        node_ptr        _tnull;
        size_type       _size;


    public:

        BST() : _size(0) {
            this->_tnull = _alloc.allocate(1);
            _alloc.construct(this->_tnull, _node());
            this->_tnull->_right_c = nullptr;
            this->_tnull->_left_c = nullptr;
            this->_tnull->_parent = nullptr;
            this->_tnull->_color = BLACK;

            this->_root = this->_tnull;
        }

        ~BST(){
            clear_tree();
        }
        node_ptr new_node(value_type data = value_type())
        {
            node_ptr node = _alloc.allocate(1);
            _alloc.construct(node, _node());
            node->_data = data;
            node->_parent = _tnull;
            node->_left_c = _tnull;
            node->_right_c = _tnull;
            node->_color = RED;

            return node;
        }

        node_ptr insert(value_type data) {
            node_ptr tmp = this->_root;
            node_ptr insert_in = _tnull;

            while (tmp != _tnull){
                insert_in = tmp;
                if (_cmp(data, tmp->_data))
                    tmp = tmp->_left_c;
                else if (_cmp(tmp->_data, data))
                    tmp = tmp->_right_c;
            }

            tmp = new_node(data);
            tmp->_parent = insert_in;
            if (insert_in == _tnull)
                this->_root = tmp;
            else if (_cmp(data,insert_in->_data))
                insert_in->_left_c = tmp;
            else
                insert_in->_right_c = tmp;

            this->_size++;
            return tmp;
        }

        void Transplant(node_ptr old_node, node_ptr new_node){
            if ( old_node->_parent == _tnull )
                this->_root = new_node;
            else if (child_position(old_node->_parent, old_node) == LEFT)
                old_node->_parent->_left_c = new_node;
            else
                old_node->_parent->_right_c = new_node;
            if (new_node != _tnull)
                new_node->_parent = old_node->_parent;
        }

        _child child_position(node_ptr parent, node_ptr child) const {
            if (!parent || !child || parent == _tnull || child == _tnull)
                return NONE;
            if (parent->_left_c == child)
                return LEFT;
            else if (parent->_right_c == child)
                return RIGHT;
            return NONE;
        }

        bool is_leaf(node_ptr node) {
            return (node->_right_c == _tnull) && (node->_left_c == _tnull);
        }

        node_ptr search(value_type data) {

            node_ptr root = this->_root;
            while (root && root != _tnull){
                if (root->_data == data)
                    return  root;
                if (data > root->_data)
                    root = root->_right_c;
                else
                    root = root->_left_c;
            }
//            throw std::exception();
            return nullptr;
        }

        void inorder_traverse(node_ptr root) {
            if(root != nullptr && root != _tnull){
                inorder_traverse(root->_left_c);
                std::cout << "data: "<< root->_data << std::endl;
                std::cout << "parent data " << root->_parent->_data << std::endl;
                std::cout << "color " << (root->_color == RED ? "RED": "BLACK") << std::endl;
                std::cout << "\n";
                inorder_traverse(root->_right_c);
            }
        }

        void clear(node_ptr root) {
            if (root == _tnull)
                return;
            clear(root->_right_c);
            clear(root->_left_c);
            _alloc.destroy(root);
            _alloc.deallocate(root, 1);
            root  = nullptr;
        }

        void clear_tree() {
            clear(this->_root);
            _alloc.destroy(_tnull);
            _alloc.deallocate(_tnull, 1);
            _tnull = nullptr;
        }

        node_ptr maximum(node_ptr node) const { //max
            while (node && node != _tnull && node->_right_c != _tnull)
                node = node->_right_c;
            return  node;
        }

        node_ptr successor(node_ptr node) const {
            if (node->_right_c != _tnull)
                return minimum(node->_right_c);
            else{
                node_ptr p = node->_parent;
                while (p != _tnull && node == p->_right_c){// searching until the node is a left child or the parent is tnull
                    node = p;
                    p = p->_parent;
                }
                return p;
            }
        }

        node_ptr minimum(node_ptr node) const {//min
            while (node && node != _tnull && node->_left_c != _tnull)
                node = node->_left_c;
            return  node;
        }

        node_ptr predecessor(node_ptr node) const {
            if (node->_left_c != _tnull)
                return maximum(node->_left_c);
            else{
                node_ptr p = node->_parent;
                while (p != _tnull && node == p->_left_c){
                    node = p;
                    p = p->_parent;
                }
                return p;
            }
        }

        node_ptr grand_parent(node_ptr node) const {
            if (node && node->_parent && node->_parent->_parent)
                return node->_parent->_parent;
            return _tnull;
        }

        node_ptr node_uncle(node_ptr node) const {
            node_ptr grand_pa = grand_parent(node);
            if (grand_pa != _tnull)
                return (child_position(grand_pa, node->_parent) == LEFT ? grand_pa->_right_c : grand_pa->_left_c );
            return _tnull;
        }

        size_type size() const {
            return  this->_size;
        }

        node_ptr root() const {
            return this->_root;
        }

        void print2DUtil(node_ptr root, int space)
        {
            // Base case
            if (root == NULL)
                return;

            // Increase distance between levels
            space += COUNT;

            // Process right child first
            print2DUtil(root->_right_c, space);

            // Print current node after space
            // count
            std::cout << std::endl;
            for (int i = COUNT; i < space; i++)
                std::cout << " ";
            std::cout << root->_data << " " <<(root->_color == RED ? BOLD_RED : BLCK )<< "\n";

            // Process left child
            print2DUtil(root->_left_c, space);
        }

        void print2D(node_ptr root)
        {
            // Pass initial space count as 0
            print2DUtil(root, 0);
        }
    };
};