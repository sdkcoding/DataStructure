// Driver Program for Red Black Tree

#include <bits/stdc++.h>
#include "RBTree.h"
using namespace std;

int main() {
    int data;
    RBTree rbTree1, rbTree2;

    cin >> data;
    while (data != 0)
    {
        rbTree1.insertValue(data);
        cin >> data;
    }

    rbTree1.preorder();
	rbTree1.draw_tree_hor();

    cin >> data;
    while (data != 0)
    {
        rbTree2.insertValue(data);
        cin >> data;
    }

    rbTree2.preorder();
	rbTree2.draw_tree_hor();

    rbTree1.merge(rbTree2);
    rbTree1.preorder();
	rbTree1.draw_tree_hor();



    return 0;
}