#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bintree.h"

typedef struct BinTreeNode BinTreeNode;

struct BinTreeNode {
  void *_value;
  BinTreeNode *_left,
	      *_right;
};

struct GenBinTree {
  BinTreeNode *_t_root;
  Cmpfunction _cmp_node_value; /* pointer to compare function, returns
				 < 0 if value1 < value2,
				 0 if value1==value2 * and
				 > 0 if value1 > value2 */
  Combinefunction _combine_node_value; /* pointer to function that handles
                                         duplicate values */
  Freefunction _free_node_value; /* pointer to Funktion that frees the contents
				   of a node pointed to by value */
};

GenBinTree *gbt_new(Cmpfunction cmp_node_value,
                    Combinefunction combine_node_value,
                    Freefunction free_node_value){

  GenBinTree *gbt = (GenBinTree*) malloc(sizeof(GenBinTree));

  assert(gbt != NULL);

  gbt->_cmp_node_value = cmp_node_value;
  gbt->_combine_node_value = combine_node_value;
  gbt->_free_node_value = free_node_value;

  return gbt;
}

/* add a new element to binary tree, uses cmp_node_value. Return
   true if node corresponding to value was added. Otherwise
   combine_node_value function was called and the gtb_add returns false */
bool gbt_add(GenBinTree *bintree,void *new_value){

  BinTreeNode *currentNode = bintree->_t_root;

  while(currentNode != NULL){

      if(bintree->_cmp_node_value(currentNode->_value,new_value)<0){

        currentNode = currentNode->_right;

      }

      if(bintree->_cmp_node_value(currentNode->_value,new_value)>0){

        currentNode = currentNode->_left;

      }

      if(bintree->_cmp_node_value(currentNode->_value,new_value)==0){

        bintree->_combine_node_value(currentNode->_value,new_value);
        return false;

      }


  }

    BinTreeNode *new = malloc(sizeof(BinTreeNode));
    assert(new != NULL);

    new->_value=new_value;
    new->_left=NULL;
    new->_right=NULL;

    currentNode = new;

    return true;

}

void delete_all(BinTreeNode *node,Freefunction _freeN){

  if(node != NULL){

    if(node->_left != NULL){
      delete_all(node->_left, _freeN);
    }
    if(node->_right!=NULL){
      delete_all(node->_right, _freeN);
    }

    _freeN(node);

  }
}

void gbt_delete(GenBinTree *bintree){
  delete_all(bintree->_t_root,bintree->_free_node_value);
  //free(bintree);
}

void apply_all(BinTreeNode *node,Applyfunction _applyF, void *data){

  if(node != NULL){

    if(node->_left != NULL){
      apply_all(node->_left, _applyF, data);
    }

    _applyF(node->_value, data);

    if(node->_right!=NULL){
      apply_all(node->_right, _applyF, data);
    }
  }
}

void gbt_enumvalues(const GenBinTree *bintree,Applyfunction apply_node_value,
                    void *data)
{
    apply_all(bintree->_t_root,apply_node_value, data);
}













