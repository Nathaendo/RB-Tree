#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


// Define um tipo de dado para o nó da árvore
struct node_t{
    struct node_t *father;  //pai
    struct node_t *left;    //filho da esquerda
    struct node_t *right;   //filho da direita
    
    int key;    //chave
    char color; //define a cor do nó(p = preto, v = vermelho)
} ;

// Define um tipo de dado para a árvore
struct RB_tree_t{

    struct node_t *root; //aponta para a raiz da árvore
    struct node_t *nil; //nó sentinela (sempre preto)
};


struct RB_tree_t *create_tree(); //cria a árvore

struct node_t *create_node(struct RB_tree_t *tree, int key); //cria o nó

void destroy_tree(struct RB_tree_t *tree); //destrói a árvore

void destroy_node(struct RB_tree_t *tree,struct node_t *nodo); //destrói o nó

struct node_t *search(struct RB_tree_t *tree, int key); //busca um nó na árvore

void left_rotate(struct RB_tree_t *tree, struct node_t *x); //faz a rotação a esquerda

void right_rotate(struct RB_tree_t *tree, struct node_t *y); //faz a rotação a direita

void insert(struct RB_tree_t *tree, struct node_t *node); //insere um nó na árvore

void insert_fixup(struct RB_tree_t *tree, struct node_t *node); //corrige a árvore após a inserção

void transplant(struct RB_tree_t *tree, struct node_t *u, struct node_t *v); //transplanta um nó u por um nó v

struct node_t *antecessor(struct RB_tree_t *tree, struct node_t *nodo); //retorna o nó antecessor

struct node_t *successor(struct RB_tree_t *tree, struct node_t *nodo); //retorna o nó sucessor

void delete_node(struct RB_tree_t *tree, struct node_t *nodo); //deleta um nó da árvore

void delete_fixup(struct RB_tree_t *tree, struct node_t *nodo); //corrige a árvore após a deleção

void in_order_traversal(struct RB_tree_t *tree, struct node_t *nodo,int nivel); //imprime as chaves da árvore em ordem.

#endif // FUNCTIONS
