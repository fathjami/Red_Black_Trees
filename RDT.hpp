#pragma once
#include "BST.hpp"
#include <map>

namespace ft {


    template<typename T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
    class RedBlackTree : public BST<T, Compare, Allocator> {

        typedef T value_type;
        typedef BST<T, Compare, Allocator> RBT;
        typedef typename BST<T, Compare, Allocator>::node_ptr node_ptr;
        typedef typename BST<T, Compare, Allocator>::node_reference node_reference;

    public:
        RedBlackTree() {}

        ~RedBlackTree() {}


        void LeftRotation(node_ptr pivot) {
            if (pivot == this->_tnull || pivot->_right_c == this->_tnull)
                return;

            node_ptr r_child = pivot->_right_c;

            pivot->_right_c = r_child->_left_c;
            if (r_child->_left_c != this->_tnull)
                r_child->_left_c->_parent = pivot;

            r_child->_parent = pivot->_parent;

            this->Transplant(pivot, r_child); //replace the pivot by the right-child

            r_child->_left_c = pivot;
            pivot->_parent = r_child;
        }

        void RightRotation(node_ptr pivot) {
            if (pivot == this->_tnull || pivot->_left_c == this->_tnull)
                return;
            node_ptr l_child = pivot->_left_c;

            pivot->_left_c = l_child->_right_c;
            if (l_child->_right_c != this->_tnull)
                l_child->_right_c->_parent = pivot;

            l_child->_parent = pivot->_parent;

            this->Transplant(pivot, l_child); // replace the pivot by the left-child

            l_child->_right_c = pivot;
            pivot->_parent = l_child;
        }

        void RightLeftRotation(node_ptr &node) {
            if (node != this->_tnull) {
                this->RightRotation(node->_right_c);
                this->LeftRotation(node);
            }
        }

        void LeftRightRotation(node_ptr &node) {
            if (node != this->_tnull) {
                this->LeftRotation(node->_left_c);
                this->RightRotation(node);
            }
        }

        void fix_insert(node_ptr node) {

            node_ptr uncle;
            node_ptr grandPa;

            while (node->_parent->_color == RED) {
                uncle = this->node_uncle(node);
                grandPa = this->grand_parent(node);

                if (uncle->_color == RED) {
                    uncle->_color = BLACK;
                    node->_parent->_color = BLACK;
                    node->_parent->_parent->_color = RED;

                    node = grandPa;

                } else if (this->child_position(grandPa, node->_parent) == LEFT) { //parent is a left child

                    if (this->child_position(node->_parent, node) == RIGHT) { // node is right child
                        node = node->_parent; //move node to parent
                        LeftRotation(node); // left rotate the
                    }

                    node->_parent->_color = BLACK;
                    node->_parent->_parent->_color = RED;
                    RightRotation(node->_parent->_parent);

                } else {

                    if (this->child_position(node->_parent, node) == LEFT) {
                        node = node->_parent;
                        RightRotation(node);
                    }

                    node->_parent->_color = BLACK;
                    node->_parent->_parent->_color = RED;
                    LeftRotation(node->_parent->_parent);
                }
            }
            this->_root->_color = BLACK;
        }

        void RBT_insert(value_type key) {
            node_ptr node = this->insert(key);

            if (node != this->_tnull)
                fix_insert(node);
        }

        void delete_elem(value_type data) {
            node_ptr found = this->search(data);
            if (found) {
                color origin_color;
                node_ptr x;
                origin_color = found->_color;

                if (found->_left_c == this->_tnull) // if the node has only the right child we replace it by that child
                {
                    x = found->_right_c;
                    x->_parent = found->_parent;
                    this->Transplant(found, found->_right_c);
                } else if (found->_right_c == this->_tnull) // if the node has only the left child
                {
                    x = found->_left_c;
                    x->_parent = found->_parent;
                    this->Transplant(found, found->_left_c);
                } else {
                    node_ptr tmp = this->minimum(
                            found->_right_c); // if the node has both children we replace it by the min of the left subtree
                    origin_color = tmp->_color;

                    x = tmp->_right_c;
                    x->_parent = tmp->_parent;
                    if (tmp != found->_right_c) {
                        this->Transplant(tmp, tmp->_right_c);
                        tmp->_right_c = found->_right_c;
                        tmp->_right_c->_parent = tmp;
                    }
//                    else
//                        x->_parent = tmp;

                    this->Transplant(found, tmp);
                    tmp->_left_c = found->_left_c;
                    tmp->_left_c->_parent = tmp;

                    tmp->_color = found->_color;
                }
                if (origin_color == BLACK)
                    fix_delete(x);
            }
            this->_alloc.destroy(found);
            this->_alloc.deallocate(found, 1);
            this->_size--;

        }

        void fix_delete(node_ptr x) {
            node_ptr w;
            while (x != this->_root && x->_color == BLACK) {

                if (x == x->_parent->_left_c) {
                    w = x->_parent->_right_c;

                    // case 1.
                    if (w->_color == RED) { //sibling is RED
                        w->_color = BLACK;
                        x->_parent->_color = RED;
                        LeftRotation(x->_parent);

                        w = x->_parent->_right_c; // the double black problem still exits which lead us to the other cases.
                    } // case 2
                    if (w->_color == BLACK && w->_left_c->_color == BLACK && w->_right_c->_color == BLACK) { //sibling and it's both children are BLACK
                        w->_color = RED;   // subtract RED from the right subtree and add it to the parent (if p is RED all good, else a new double black in the x.p)
                        x = x->_parent;
                    } else { // case 3.
                        if (w->_right_c->_color == BLACK) { // the close nephew is RED , we'll make it the root of the subtree with the color of the original root.
                            w->_left_c->_color = BLACK; // switch left color with parent
                            w->_color = RED; // ...
                            RightRotation(w); // right rotate so w.left become w
                            w = x->_parent->_right_c; //...
                        } // case 4.
                        w->_color = x->_parent->_color; // if the far nephew (both) are RED. set w color x.p 's color.
                        x->_parent->_color = BLACK; // make x.p color ,so it removes the double black problem
                        w->_right_c->_color = BLACK; // if the right child is RED => make it black , if not w already switched colors before with the left child, so we go back to the original color.
                        LeftRotation(x->_parent);
                        x = this->_root; // all good.
                    }
                } else if (x == x->_parent->_right_c){ // Mirror of the four cases above.
                    w = x->_parent->_left_c;
                    // case /1
                    if (w->_color == RED){
                        w->_color = BLACK;
                        x->_parent->_color = RED;
                        RightRotation(x->_parent);

                        w = x->_parent->_left_c;
                    } // case /2
                    if (w->_color == BLACK && w->_left_c->_color == BLACK && w->_right_c->_color == BLACK){
                        w->_color = RED;
                        x = x->_parent;
                    } else { // case /3
                        if (w->_left_c->_color == BLACK){
                            w->_right_c->_color = BLACK;
                            w->_color = RED;
                            LeftRotation(w);
                            w = x->_parent->_left_c;
                        } // case /4
                        w->_color = x->_parent->_color;
                        x->_parent->_color = BLACK;
                        w->_left_c->_color = BLACK;
                        RightRotation(x->_parent);
                        x = this->_root;
                    }
                }
            }
        x->_color = BLACK;
}

};
};
