
#include <stddef.h>
#include "rb_node.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/* Static sentinel structure for root and leaves cuts the required storage in half. */
static struct rb_node RB_NULL; // members statically initialized to zero, so color is RB_BLACK

struct rb_node *
rb_find(const struct rb_node *tree, const struct rb_node *node){
    //If we found our node then we return it
    if(strcmp(node->word,tree->word)==0){
        return (struct rb_node*)tree;
    }else if(strcmp(node->word,tree->word)<0){
        return rb_find(tree->left,node);
    }else if(strcmp(node->word,tree->word)>0){
        return rb_find(tree->left,node);
    }else{
        return NULL;
    }

}

void
rb_left_rotate(struct rb_node *tree, struct rb_node *node){
    struct rb_node * nodeToSwap=node->left;
    node->right=nodeToSwap->left;
    if(nodeToSwap->left!=&RB_NULL){
        nodeToSwap->left->parent=node;
    }
    nodeToSwap->parent=node->parent;
    if(node->parent==&RB_NULL){
        tree=nodeToSwap;
    }else if(node==node->parent->left){
        node->parent->left=nodeToSwap;
    }else{
        node->parent->right=nodeToSwap;
    }
    nodeToSwap->left=node;
    node->parent=nodeToSwap;

}

void
rb_right_rotate(struct rb_node *tree, struct rb_node *node){
    struct rb_node * nodeToSwap=node->right;
    node->left=nodeToSwap->right;
    if(nodeToSwap->right!=&RB_NULL){
        nodeToSwap->right->parent=node;
    }
    nodeToSwap->parent=node->parent;
    if(node->parent==&RB_NULL){
        tree=nodeToSwap;
    }else if(node==node->parent->right){
        node->parent->right=nodeToSwap;
    }else{
        node->parent->left=nodeToSwap;
    }
    nodeToSwap->right=node;
    node->parent=nodeToSwap;

}

struct rb_node *rb_insert(struct rb_node* tree, struct rb_node *node){


    //printf("\n");
   //printf(node->word);
    if(node->parent==NULL){
        node->parent=&RB_NULL;
    }
    node->left=&RB_NULL;
    node->right=&RB_NULL;
    node->count=1;
    node->color=RB_RED;
    //If we encounter an empty tree(If the tree has a proper nonempty root
    //then the parent of the root will be &RB_NULL
    if(tree->parent==NULL){
        tree->parent=&RB_NULL;

        tree->word=node->word;
        tree->left=&RB_NULL;
        tree->right=&RB_NULL;
        tree->count=1;
        tree->color=RB_RED;
        free(node);
        return tree;
    }

    if(strcmp(node->word,tree->word)<0){
        //if the word we are inserting is "less then" the root
        //we traverse to the left child, we also set the nodes parent to the current tree before calling again
        node->parent=tree;
        if(tree->left==&RB_NULL){
            tree->left=node;
            return node;
        }
        return rb_insert(tree->left,node);

    }else if(strcmp(node->word,tree->word)>0){
        //if the word we are inserting is "larger then" the root
        //we traverse to the right child, we also set the nodes parent to the current tree before calling again
        node->parent=tree;
        if(tree->right==&RB_NULL){
            tree->right=node;
            return node;
        }

        return rb_insert(tree->right,node);
    }else if(strcmp(node->word,tree->word)==0){
        //if we found our word then we increment it and return null
        tree->count++;
        return NULL;
    }
}

void rb_restore_after_insert(struct rb_node *tree, struct rb_node *node){
    //Code used from the introduction to algorithms, 3rd eddition textbook, page316
    //as well as https://azrael.digipen.edu/~mmead/www/Courses/CS280/Red-Black-code-diagrams.pdf
    //right now it does not work.
    while((node->parent!=&RB_NULL)&node->parent->color==RB_RED&node!=tree){
        if(node->parent==node->parent->parent->left){
            struct rb_node *uncle=node->parent->parent->right;

            if(uncle!=NULL&uncle!=&RB_NULL&uncle->color==RB_RED){
                node->parent->color=RB_BLACK;
                uncle->color=RB_BLACK;
                node->parent->parent->color=RB_RED;
            }else{
                if(node->parent->right==node){
                    node=node->parent;
                    rb_left_rotate(tree,node);
                }
                node->parent->color=RB_BLACK;
                node->parent->parent->color=RB_RED;
                rb_right_rotate(tree,node->parent->parent);
            }
        }else{
            struct rb_node *uncle=node->parent->parent->left;

            if(uncle!=NULL&uncle!=&RB_NULL&uncle->color==RB_RED){
                node->parent->color=RB_BLACK;
                uncle->color=RB_BLACK;
                node->parent->parent->color=RB_RED;
            }else{
                if(node->parent->left==node){
                    node=node->parent;
                    rb_right_rotate(tree,node);
                }
                node->parent->color=RB_BLACK;
                node->parent->parent->color=RB_RED;
                rb_left_rotate(tree,node->parent->parent);
            }
        }
    }
    //get the trees new root


}


struct rb_node * rb_min(struct rb_node *tree){

}

void rb_transplant(struct rb_node *tree, struct rb_node *old_root, struct rb_node *new_root){

}

struct rb_node * rb_delete(struct rb_node *tree, struct rb_node *node){

}


void rb_restore_after_delete(struct rb_node *tree, struct rb_node *orphan){

}