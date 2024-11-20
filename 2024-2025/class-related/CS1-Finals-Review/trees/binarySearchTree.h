#pragma once

typedef struct treeNode {
  int val;
  struct treeNode* left;
  struct treeNode* right;
} treeNode;

treeNode* createTreeNode(int value);
treeNode *insertValue(treeNode* root, int value);
treeNode *deleteValue(treeNode* root, int value);
void freeTree(treeNode *root);
void traversePreorder(treeNode* root);
void traverseInorder(treeNode* root);
void traversePostorder(treeNode* root);
