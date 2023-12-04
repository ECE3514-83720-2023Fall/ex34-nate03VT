#include "binary_tree.hpp"

#include <stdexcept>
#include <iostream>

template <typename TreeItemType, typename FunctionType>
BinaryTree<TreeItemType, FunctionType>::BinaryTree(
    const TreeItemType &rootItem) {
  root = new NodeType(rootItem);
}

template <typename TreeItemType, typename FunctionType>
BinaryTree<TreeItemType, FunctionType>::BinaryTree(const TreeItemType &rootItem,
                                                   BinaryTree &leftTree,
                                                   BinaryTree &rightTree) {
  root = new NodeType(rootItem);

  attachLeftSubtree(leftTree);
  attachRightSubtree(rightTree);
}

template <typename TreeItemType, typename FunctionType>
BinaryTree<TreeItemType, FunctionType>::BinaryTree(NodeType *nodePtr) {
  root = nodePtr;
}

template <typename TreeItemType, typename FunctionType>
BinaryTree<TreeItemType, FunctionType>::BinaryTree(const BinaryTree &tree) {
  copyTree(tree.root, root);
}

template <typename TreeItemType, typename FunctionType>
BinaryTree<TreeItemType, FunctionType> &
BinaryTree<TreeItemType, FunctionType>::operator=(const BinaryTree &rhs) {
  if (this != &rhs) {
    destroyTree(root);        // deallocate left-hand side
    copyTree(rhs.root, root); // copy right-hand side
  }
  return *this;
}

template <typename TreeItemType, typename FunctionType>
BinaryTree<TreeItemType, FunctionType>::~BinaryTree() {
  destroyTree(root);
}

template <typename TreeItemType, typename FunctionType>
bool BinaryTree<TreeItemType, FunctionType>::isEmpty() const noexcept {
  return (root == nullptr);
}

template <typename TreeItemType, typename FunctionType>
TreeItemType BinaryTree<TreeItemType, FunctionType>::rootData() const

{
  if (root == nullptr) {
    throw std::logic_error("Empty tree in BinaryTree:rootData");
  }
  return root->item;
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::setRootData(
    const TreeItemType &newItem) {
  if (root != nullptr) {
    root->item = newItem;
  } else {
    root = new NodeType(newItem);
  }
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::attachLeft(
    const TreeItemType &newItem) {
  if (root == nullptr) {
    throw std::logic_error("Empty tree in BinaryTree::attachLeft");
  } else if (root->leftChildPtr != nullptr) {
    throw std::logic_error("Cannot overwrite left subtree");
  } else {
    root->leftChildPtr = new NodeType(newItem);
  }
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::attachRight(
    const TreeItemType &newItem) {
    if (root == nullptr) { //copied from left attach
        throw std::logic_error("Empty tree in BinaryTree::attachRight");
    }
    else if (root->rightChildPtr != nullptr) {
        throw std::logic_error("Cannot overwrite right subtree");
    }
    else {
        root->rightChildPtr = new NodeType(newItem);
    }
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::attachLeftSubtree(
    BinaryTree &leftTree) {
  if (root == nullptr) {
    throw std::logic_error("Empty tree in BinaryTree::attachLeftSubtree");
  } else if (root->leftChildPtr != nullptr) {
    throw std::logic_error("Cannot overwrite left subtree");
  } else {
    root->leftChildPtr = leftTree.root;
    leftTree.root = nullptr;
  }
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::attachRightSubtree(
    BinaryTree &rightTree) {
    if (root == nullptr) {
        throw std::logic_error("Empty tree in BinaryTree::attachRightSubtree");
    }
    else if (root->rightChildPtr != nullptr) {
        throw std::logic_error("Cannot overwrite right subtree");
    }
    else {
        root->rightChildPtr = rightTree.root;
        rightTree.root = nullptr;
    }
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::detachLeftSubtree(
    BinaryTree &leftTree) {
  if (root == nullptr) {
    throw std::logic_error("Empty tree in BinaryTree::detachLeftSubtree");
  } else {
    leftTree = BinaryTree(root->leftChildPtr);
    root->leftChildPtr = nullptr;
  }
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::detachRightSubtree(
    BinaryTree &rightTree) {
    if (root == nullptr) {
        throw std::logic_error("Empty tree in BinaryTree::detachRightSubtree");
    }
    else {
        rightTree = BinaryTree(root->rightChildPtr);
        root->rightChildPtr = nullptr;
    }
}

template <typename TreeItemType, typename FunctionType>
BinaryTree<TreeItemType, FunctionType>
BinaryTree<TreeItemType, FunctionType>::leftSubtree() const {
  NodeType *subTreePtr = nullptr;
  copyTree(root->leftChildPtr, subTreePtr);
  return BinaryTree(subTreePtr);
}

template <typename TreeItemType, typename FunctionType>
BinaryTree<TreeItemType, FunctionType>
BinaryTree<TreeItemType, FunctionType>::rightSubtree() const {
    NodeType* subTreePtr = nullptr;
    copyTree(root->rightChildPtr, subTreePtr);
    return BinaryTree(subTreePtr);
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::preorderTraverse(
    FunctionType visit) {
  preorder(root, visit);
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::inorderTraverse(
    FunctionType visit) {
  inorder(root, visit);
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::postorderTraverse(
    FunctionType visit) {
  postorder(root, visit);
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::copyTree(
    NodeType *treePtr, NodeType *&newTreePtr) const {
  // preorder traversal
  if (treePtr != nullptr) { 
      // Copy root node
      newTreePtr = new NodeType(treePtr->item);
      //recursively copies the nodes until you get to the end of the tree
      // Copy left subtree
      copyTree(treePtr->leftChildPtr, newTreePtr->leftChildPtr);

      // Copy right subtree
      copyTree(treePtr->rightChildPtr, newTreePtr->rightChildPtr);
  } else {
    newTreePtr = nullptr; // copy empty tree
  }
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::destroyTree(NodeType *&treePtr) {
  // postorder traversal
  if (treePtr != nullptr) {
    //TODO
    //destroy left subtree
     destroyTree(treePtr->leftChildPtr);
    //destroy right subtree
     destroyTree(treePtr->rightChildPtr);
    // delete root
    delete treePtr;
    treePtr = nullptr;
  }
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::preorder(NodeType *treePtr,
                                                      FunctionType visit) {
  if (treePtr != nullptr) {
      //visits current nod then left then right
      // Visit the current node
      visit(treePtr->item);

      // Traverse left subtree
      preorder(treePtr->leftChildPtr, visit);

      // Traverse right subtree
      preorder(treePtr->rightChildPtr, visit);
  }
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::inorder(NodeType *treePtr,
                                                     FunctionType visit) {
  if (treePtr != nullptr) {
      // Traverse left subtree
      inorder(treePtr->leftChildPtr, visit);

      // Visit the current node
      visit(treePtr->item);

      // Traverse right subtree
      inorder(treePtr->rightChildPtr, visit);
  }
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::postorder(NodeType *treePtr,
                                                       FunctionType visit) {
  if (treePtr != nullptr) {
      // Traverse left subtree
      postorder(treePtr->leftChildPtr, visit);

      // Traverse right subtree
      postorder(treePtr->rightChildPtr, visit);

      // Visit the current node
      visit(treePtr->item);
  }
}

template <typename TreeItemType, typename FunctionType>
BinaryTree<TreeItemType, FunctionType> BinaryTree<TreeItemType, FunctionType>::makeBinaryTree(const TreeItemType *array, int low, int high) {
    std::cout << "low, high = " << low << " " << high << std::endl;
    if (low < high) { //handes low< high case
        root = nullptr;
        return *this;
    }
    if (low == high) { //handles == case
        root = new NodeType(array[low]);
        return *this;
    }
    //find average
    int mid = low + (high - low) / 2;
    BinaryTree leftT;
    BinaryTree rightT;
    leftT.makeBinaryTree(array, low, mid - 1);
    rightT.makeBinaryTree(array, mid + 1, high);

        root = new NodeType(array[mid]);
        //handles the tricky case
        if (!leftT.isEmpty()) {
            attachLeftSubtree(leftT);
    }
        if (!rightT.isEmpty()) {
            attachRightSubtree(rightT);
        }
        return *this;
}
