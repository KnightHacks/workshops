#include <stdlib.h>
#include <stdio.h>

typedef struct treeNode
{
  int val;
  struct treeNode *left;
  struct treeNode *right;
} treeNode;

treeNode *findParentNode(treeNode *root, int value);
int isLeaf(treeNode *node);
int onlyHasLeftChild(treeNode *node);
int onlyHasRightChild(treeNode *node);
int findMin(treeNode *root);
void preorderUtil(treeNode *root);
void inorderUtil(treeNode *root);
void postorderUtil(treeNode *root);

treeNode *createTreeNode(int value)
{
  treeNode *newNode;
  newNode = (treeNode *)malloc(sizeof(treeNode));

  newNode->val = value;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

treeNode *insertValue(treeNode *root, int value)
{
  if (root == NULL)
    return createTreeNode(value);

  if (root->val >= value)
    root->left = insertValue(root->left, value);
  else
    root->right = insertValue(root->right, value);

  return root;
}

treeNode *deleteValue(treeNode *root, int value)
{
  if (root == NULL)
    return root;

  treeNode *parent = findParentNode(root, value);

  if (parent == NULL) // root doesn't have any parents..
  {
    if (root->val != value) // value is not present in the tree..
      return root;

    if (isLeaf(root))
    {
      free(root);
      root = NULL;
    }
    else if (onlyHasLeftChild(root))
    {
      treeNode *temp = root->left;
      free(root);
      root = temp;
    }
    else if (onlyHasRightChild(root))
    {
      treeNode *temp = root->right;
      free(root);
      root = temp;
    }
    else // Has both children
    {
      int newValue = findMin(root->right);
      root->val = newValue;
      deleteValue(root, newValue);
    }
  }
  else if (parent->left != NULL && parent->left->val == value)
  {
    treeNode *node = parent->left;
    if (isLeaf(node))
    {
      free(node);
      parent->left = NULL;
    }
    else if (onlyHasLeftChild(node))
    {
      treeNode *temp = node->left;
      free(node);
      parent->left = temp;
    }
    else if (onlyHasRightChild(node))
    {
      treeNode *temp = node->right;
      free(node);
      parent->left = temp;
    }
    else // has both children nodes..
    {
      int newValue = findMin(node->right);
      node->val = newValue;
      deleteValue(node, newValue);
    }
  }
  else if (parent->right != NULL && parent->right->val == value)
  {
    treeNode *node = parent->right;
    if (isLeaf(node))
    {
      free(node);
      parent->right = NULL;
    }
    else if (onlyHasLeftChild(node))
    {
      treeNode *temp = node->left;
      free(node);
      parent->right = temp;
    }
    else if (onlyHasRightChild(node))
    {
      treeNode *temp = node->right;
      free(node);
      parent->right = temp;
    }
    else // has both children nodes..
    {
      int newValue = findMin(node->right);
      node->val = newValue;
      deleteValue(node, newValue);
    }
  }
  return root;
}

treeNode *findParentNode(treeNode *root, int value)
{
  if (root == NULL)
    return NULL;

  if (root->val > value)
  {
    if (root->left != NULL && root->left->val == value)
      return root;
    return findParentNode(root->left, value);
  }
  else // root->val <= value
  {
    if (root->right != NULL && root->right->val == value)
      return root;
    return findParentNode(root->right, value);
  }
}

int isLeaf(treeNode *node)
{
  if (node != NULL && node->left == NULL && node->right == NULL)
    return 1;
  return 0;
}

int onlyHasLeftChild(treeNode *node)
{
  if (node != NULL && node->left != NULL && node->right == NULL)
    return 1;
  return 0;
}

int onlyHasRightChild(treeNode *node)
{
  if (node != NULL && node->left == NULL && node->right != NULL)
    return 1;
  return 0;
}

int findMin(treeNode *root)
{
  if (root == NULL)
  {
    printf("findMin called on a node that is NULL");
    return -1;
  }
  while (root->left != NULL)
  {
    root = root->left;
  }

  return root->val;
}

void freeTree(treeNode *root)
{
  if (root == NULL)
    return;

  freeTree(root->left);
  freeTree(root->right);
  free(root);
}

void traversePreorder(treeNode *root)
{
  preorderUtil(root);
  printf("\n");
}

void traverseInorder(treeNode *root)
{
  inorderUtil(root);
  printf("\n");
}

void traversePostorder(treeNode *root)
{
  postorderUtil(root);
  printf("\n");
}

void preorderUtil(treeNode *root)
{
  if (root == NULL)
    return;

  printf("%d ", root->val);
  preorderUtil(root->left);
  preorderUtil(root->right);
}

void inorderUtil(treeNode *root)
{
  if (root == NULL)
    return;

  inorderUtil(root->left);
  printf("%d ", root->val);
  inorderUtil(root->right);
}

void postorderUtil(treeNode *root)
{
  if (root == NULL)
    return;

  postorderUtil(root->left);
  postorderUtil(root->right);
  printf("%d ", root->val);
}
