#include <stdio.h>
#include <stdlib.h>
#include "binarySearchTree.h"

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    printf("Error -1: Txt filepath was not given in the command line arguments.\n");
    return -1;
  }

  FILE *fp;
  int length;
  int *array;
  treeNode *root = NULL;

  fp = fopen(argv[1], "r");

  fscanf(fp, "%d\n", &length);
  array = (int *)malloc(sizeof(int) * length);

  for (int i = 0; i < length; i++)
    fscanf(fp, "%d, ", &array[i]);

  for (int i = 0; i < length; i++)
    root = insertValue(root, array[i]);

  printf("\nPreorder traversal: \n");
  traversePreorder(root);

  printf("Inorder traversal: \n");
  traverseInorder(root);

  for (int i = 0; i < length; i++)
  {
    root = deleteValue(root, array[i]);
    printf("\nPreorder traversal: \n");
    traversePreorder(root);

    printf("Inorder traversal: \n");
    traverseInorder(root);
  }

  freeTree(root);
  fclose(fp);
  return 0;
}
