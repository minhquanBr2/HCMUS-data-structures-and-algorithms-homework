#include "RBNode.h"
#include "common.h"
#include <iostream>
#include <sstream>

/*
    Add the following at the beginning of the program:
        *nil = RBNode(0, BLACK, nil, nil, nil);
*/

// Constructor
RBNode::RBNode(int key, bool color,
               RBRef parent, RBRef left, RBRef right)
{
    _key = key;
    _color = color;
    _parent = parent;
    _left = left;
    _right = right;
}

/* MAIN OPERATIONS */
RBRef getNode(int key, int color)
{
    RBRef newNode = new RBNode(key, color, nil, nil, nil);
    return newNode;
}

RBRef lookUp(RBRef pRoot, int key)
{
    if (pRoot == nil)
        return nullptr;
    if (key < pRoot->_key)
        return lookUp(pRoot->_left, key);
    if (key > pRoot->_key)
        return lookUp(pRoot->_right, key);
    return pRoot;
}

void Insert(RBRef &pRoot, int key)
{
    RBRef insertee = getNode(key, RED);
    insert_BST(pRoot->_parent, pRoot, insertee);
    FixUp_insertion(pRoot, insertee);
}

void Remove(RBRef &pRoot, int key)
{
    RBRef removee = lookUp(pRoot, key);

    if (removee != nil)
    {
        RBRef substitute, heir;

        findSubstituteAndTransfer(pRoot, removee, substitute, heir);
        // heir inherits a 'black' from his parent (black token marked)
        if (substitute->_color == BLACK)
            FixUp_removal(pRoot, heir);

        delete substitute;
    }
}

int Height(RBRef pRoot)
{
    if (pRoot == nil)
        return 0;

    int leftHeight = Height(pRoot->_left);
    int rightHeight = Height(pRoot->_right);
    return std::max(leftHeight, rightHeight) + 1;
}

int BlackHeight(RBRef pRoot)
{
    if (pRoot == nil)
        return 0;

    int currentBlack = (pRoot->_color == BLACK) ? 1 : 0;
    int leftBlackH = BlackHeight(pRoot->_left);
    int rightBlackH = BlackHeight(pRoot->_right);

    if (leftBlackH != rightBlackH)
        return -1;
    else
        return leftBlackH + currentBlack;
}

RBRef createTree(int a[], int n)
{
    RBRef pRoot = nil;
    for (int i = 0; i < n; ++i)
        Insert(pRoot, a[i]);
    return pRoot;
}

void removeTree(RBRef &pRoot)
{
    while (pRoot != nil)
        Remove(pRoot, pRoot->_key);
}

void print2D(RBRef pRoot)
{
    int h = Height(pRoot);
    std::string splitter = duplicate("-", h * SPACE_COUNT + 3);

    std::cout << "\n" << splitter << "\n";
    internalPrint2D(pRoot, 0);
    std::cout << "\n" << splitter << "\n";
}

/* SUPPORTING OPERATIONS */

// Basic helpers
void swapColor(RBRef &x)
{
    if (x->_color == RED)
        x->_color = BLACK;
    else
        x->_color = RED;
}

void rotateRight(RBRef &pRoot, RBRef subRoot)
{
    RBRef altRoot = subRoot->_left;
    subRoot->_left = altRoot->_right;

    if (altRoot->_right != nil)
        altRoot->_right->_parent = subRoot;

    altRoot->_parent = subRoot->_parent;

    if (subRoot == pRoot)
        pRoot = altRoot;
    else if (subRoot == subRoot->_parent->_right)
        subRoot->_parent->_right = altRoot;
    else
        subRoot->_parent->_left = altRoot;

    altRoot->_right = subRoot;
    subRoot->_parent = altRoot;
}

void rotateLeft(RBRef &pRoot, RBRef subRoot)
{
    RBRef altRoot = subRoot->_right;
    subRoot->_right = altRoot->_left;

    if (altRoot->_left != nil)
        altRoot->_left->_parent = subRoot;

    altRoot->_parent = subRoot->_parent;

    if (subRoot == pRoot)
        pRoot = altRoot;
    else if (subRoot == subRoot->_parent->_left)
        subRoot->_parent->_left = altRoot;
    else
        subRoot->_parent->_right = altRoot;

    altRoot->_left = subRoot;
    subRoot->_parent = altRoot;
}

// Insertion helpers
void insert_BST(RBRef &rootParent, RBRef &pRoot, RBRef &insertee)
{
    if (pRoot == nil)
    {
        /*
            Why need to pass rootParent?
            --> nil parent is always nil, so we can't
            access the node right before it directly.
        */
        pRoot = insertee;
        pRoot->_parent = rootParent;
        return;
    }

    if (insertee->_key < pRoot->_key)
        insert_BST(pRoot, pRoot->_left, insertee);
    else if (insertee->_key > pRoot->_key)
        insert_BST(pRoot, pRoot->_right, insertee);
}

void AdjustLeft_insertion(RBRef &pRoot, RBRef &insertee)
{
    // Context: insertee's parent is a left child
    RBRef uncle = insertee->_parent->_parent->_right;

    if (uncle->_color == RED)
    {
        swapColor(insertee->_parent->_parent);
        swapColor(insertee->_parent);
        swapColor(uncle);
        // next turn to be checked
        insertee = insertee->_parent->_parent;
    }
    else
    {
        // internal grandchild
        if (insertee == insertee->_parent->_right)
        {
            // transform to external grandchild
            insertee = insertee->_parent;
            rotateLeft(pRoot, insertee);
        }

        // external grandchild
        swapColor(insertee->_parent->_parent);
        swapColor(insertee->_parent);
        rotateRight(pRoot, insertee->_parent->_parent);
    }
}

void AdjustRight_insertion(RBRef &pRoot, RBRef &insertee)
{
    // Context: insertee's parent is a right child
    RBRef uncle = insertee->_parent->_parent->_left;

    if (uncle->_color == RED)
    {
        swapColor(insertee->_parent->_parent);
        swapColor(insertee->_parent);
        swapColor(uncle);
        // next turn to be checked
        insertee = insertee->_parent->_parent;
    }
    else
    {
        // internal grandchild
        if (insertee == insertee->_parent->_left)
        {
            // transform to external grandchild
            insertee = insertee->_parent;
            rotateRight(pRoot, insertee);
        }

        // external child
        swapColor(insertee->_parent->_parent);
        swapColor(insertee->_parent);
        rotateLeft(pRoot, insertee->_parent->_parent);
    }
}

void FixUp_insertion(RBRef &pRoot, RBRef &accused)
{
    while (accused->_parent->_color == RED)
    {
        if (accused->_parent == accused->_parent->_parent->_left)
            AdjustLeft_insertion(pRoot, accused);
        else
            AdjustRight_insertion(pRoot, accused);
    }
    pRoot->_color = BLACK;
}

// Deletion helpers
RBRef findLMS(RBRef pRoot)
{
    if (pRoot->_left == nil)
        return pRoot;
    return findLMS(pRoot->_left);
}

int countChildren(RBRef pNode)
{
    int count = 0;
    if (pNode->_left != nil)
        count++;
    if (pNode->_right != nil)
        count++;
    return count;
}

void findSubstituteAndTransfer(RBRef &pRoot, RBRef &removee, RBRef &substitute, RBRef &heir)
{
    // Find substitute for removee
    substitute = (countChildren(removee) == 2)
                     ? findLMS(removee->_right)
                     : removee;

    // Removee copies living information
    removee->_key = substitute->_key;

    // Substitute transfers property before death
    heir = (substitute->_left != nil) ? substitute->_left : substitute->_right;

    heir->_parent = substitute->_parent;

    if (substitute->_parent == nil)
        pRoot = heir;
    else if (substitute == substitute->_parent->_left)
        substitute->_parent->_left = heir;
    else
        substitute->_parent->_right = heir;
}

void AdjustLeft_removal(RBRef &pRoot, RBRef &doublyBlack)
{
    /*
        Context: marked node doublyBlack is a left child .
        The function:
            + balances black height of marked node & its sibling,
            + transfers the black token to a suitable node.
        Ideal case: external nephew is red (direct fix-up).
    */

    RBRef sibling = doublyBlack->_parent->_right;

    // CASE 1: SIBLING IS RED (No red nephew available)
    if (sibling->_color == RED)
    {
        // Transform to switch to case 2
        swapColor(sibling);
        swapColor(sibling->_parent);
        rotateLeft(pRoot, doublyBlack->_parent);
        sibling = doublyBlack->_parent->_right;
    }

    // CASE 2: SIBLING IS BLACK

    // Case 2.1: No red nephew found
    if (sibling->_right->_color == BLACK && sibling->_left->_color == BLACK)
    {
        swapColor(sibling); // Balancing
        // Transfer token upwards
        doublyBlack = doublyBlack->_parent;
        return;
    }
    
    // Case 2.2: Red nephew found

    // Case 2.2.1: external nephew is not red
    if (sibling->_right->_color != RED)
    {
        // Transform to switch to case 2.2.2
        swapColor(sibling->_left);
        swapColor(sibling);
        rotateRight(pRoot, sibling);
        sibling = doublyBlack->_parent->_right;
    }
    
    // Case 2.2.2: external nephew is red
    sibling->_color = sibling->_parent->_color;
    sibling->_parent->_color = BLACK;
    sibling->_right->_color = BLACK;
    rotateLeft(pRoot, sibling->_parent);

    doublyBlack = pRoot; // notify completion
}

void AdjustRight_removal(RBRef &pRoot, RBRef &doublyBlack)
{
    /*
        Context: marked node doublyBlack is a right child .
        The function:
            + balances black height of marked node & its sibling,
            + transfers the black token to a suitable node.
        Ideal case: external nephew is red (direct fix-up).
    */

    RBRef sibling = doublyBlack->_parent->_left;

    // CASE 1: SIBLING IS RED (No red nephew available)
    if (sibling->_color == RED)
    {
        // Transform to switch to case 2
        swapColor(sibling);
        swapColor(sibling->_parent);
        rotateRight(pRoot, doublyBlack->_parent);
        sibling = doublyBlack->_parent->_left;
    }

    // CASE 2: SIBLING IS BLACK

    // Case 2.1: No red nephew found
    if (sibling->_left->_color == BLACK && sibling->_right->_color == BLACK)
    {
        swapColor(sibling); // Balancing
        // Transfer token upwards
        doublyBlack = doublyBlack->_parent;
        return;
    }
    
    // Case 2.2: Red nephew found

    // Case 2.2.1: external nephew is not red
    if (sibling->_left->_color != RED)
    {
        // Transform to switch to case 2.2.2
        swapColor(sibling->_right);
        swapColor(sibling);
        rotateLeft(pRoot, sibling);
        sibling = doublyBlack->_parent->_left;
    }
    // Case 2.2.2: external nephew is red
    sibling->_color = sibling->_parent->_color;
    sibling->_parent->_color = BLACK;
    sibling->_left->_color = BLACK;
    rotateRight(pRoot, sibling->_parent);

    doublyBlack = pRoot; // notify completion
}

void FixUp_removal(RBRef pRoot, RBRef pBlackTokenMarked)
{
    // Problem: Black height at marked node is unsatisfied
    // Solution:
    // + Case 1 (singly black node or root node): Color it black. Done.
    // + Case 2 (other doubly black node): Balance node and its sibling
    // then transfer black token to a suitable node until reach case 1.

    while (pBlackTokenMarked->_color == BLACK && pBlackTokenMarked != pRoot)
    {
        if (pBlackTokenMarked = pBlackTokenMarked->_parent->_left)
            AdjustLeft_removal(pRoot, pBlackTokenMarked);
        else
            AdjustRight_removal(pRoot, pBlackTokenMarked);
    }
    pBlackTokenMarked->_color = BLACK;
}

// Other helpers
std::string duplicate(std::string unit, int qtt)
{
    std::stringstream builder;
    for (int i = 0; i < qtt; ++i) 
        builder << unit;
    return builder.str();
}

void internalPrint2D(RBRef pRoot, int spaceQtt)
{
    spaceQtt += SPACE_COUNT;
    if (pRoot != nil)
    {
        internalPrint2D(pRoot->_right, spaceQtt);

        std::cout 
            << "\n" << duplicate(" ", spaceQtt - SPACE_COUNT)
            << pRoot->_key << "-" << pRoot->_color << "\n";

        internalPrint2D(pRoot->_left, spaceQtt);
    }
    else std::cout 
        << duplicate(" ", spaceQtt - SPACE_COUNT)
        << "x-" << pRoot->_color;
}
