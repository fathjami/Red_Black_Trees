#include "BST.hpp"
#include "RDT.hpp"

//void print_8_colours()
//{
//    for (int i = 0; i < 108; i++)
//    {
//        if (i % 9 == 0 && i != 0)
//            std::cout << std::endl;
//        printf("\033[%dm %3d\033[m", i, i);
//    }
//}

int main(){



    ft::RedBlackTree<int> tree;

//    tree.RBT_insert(7);
//    tree.RBT_insert(3);
//    tree.RBT_insert(18);
//    tree.RBT_insert(10);
//    tree.RBT_insert(22);
//    tree.RBT_insert(8);
//    tree.RBT_insert(11);
//    tree.RBT_insert(26);
//    tree.RBT_insert(2);
//    tree.RBT_insert(6);
//    tree.RBT_insert(13);


    tree.RBT_insert(1);
    tree.RBT_insert(2);
    tree.RBT_insert(3);
    tree.RBT_insert(4);
    tree.RBT_insert(5);
    tree.RBT_insert(6);


//for (int i = 1 ; i < 10 ; ++i)
//    tree.RBT_insert(i);

    tree.inorder_traverse((tree.root()));

    std::cout << "----------------------------------------------" << std::endl;
//
 tree.delete_elem(1);
//    tree.delete_elem(11);
//    tree.delete_elem(3);
//    tree.delete_elem(10);
//    tree.delete_elem(22);
    tree.inorder_traverse((tree.root()));

//
//    tree.print2D((tree.root()));


//    tree.inorder_traverse(tree.root());
//    tree.LeftRotation(tree.root_ref());
//tree.delete_elem(20);
//    std::cout << "----------------------------------------------" << std::endl;
//    std::cout << "----------------------------------------------" << std::endl;


//    tree.print2D((tree.root()));

//    tree.inorder_traverse(tree.root());

//    tree.rdt_insert(38);
//    tree.rdt_insert(45);
//    tree.rdt_insert(44);
//    tree.rdt_insert(60);
//std::cout << "root: " << tree.root()->_data << std::endl;

//    std::cout << tree.search(90, tree._root)->_data << std::endl;
//    std::cout << tree.successor(tree.search(45, tree._root))->_data << std::endl;
//    tree.clear_tree(tree._tree);
//    tree.delete_elem(50);
//    std::cout << "after deletion\n" << std::endl;
//    tree.inorder_traverse(tree._root);
////    tree.print2D(tree._root);

//std::cout << tree.node_uncle(tree.search(11, tree._root))->_data << std::endl;

    return 0;
}

//int main(){
//    ft::RedBlackTree<int> bst;
//    bst.insert(10);
//    bst.insert(5);
//    bst.insert(2);
//    bst.insert(7);
//    bst.insert(20);
//    bst.insert(25);
//    bst.insert(15);
//    bst.insert(12);
////    bst.insert(17);
////    bst.insert(16);
//
//    bst.print2D(bst.root());
//
//        std::cout << "----------------------------------------------" << std::endl;
//    std::cout << "----------------------------------------------" << std::endl;
//    bst.delete_elem(20);
//        bst.print2D(bst.root());
//
//}