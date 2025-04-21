#include "functions.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// Cria a árvore RB
struct RB_tree_t *create_tree() {
    struct RB_tree_t *tree = malloc(sizeof(struct RB_tree_t));
    struct node_t *nil_node = malloc(sizeof(struct node_t));
    nil_node->color = 'p';
    nil_node->key = 0;
    nil_node->left = nil_node;
    nil_node->right = nil_node;
    tree->nil = nil_node;
    tree->root = nil_node;
    return tree;
}

// Cria um nó
struct node_t *create_node(struct RB_tree_t *tree, int key) {
    struct node_t *nodo = malloc(sizeof(struct node_t));
    nodo->key = key;
    nodo->left = tree->nil;
    nodo->right = tree->nil;
    nodo->father = tree->nil;
    nodo->color = 'v'; // novo nó é vermelho
    return nodo;
}

// Busca um nó na árvore
struct node_t *search(struct RB_tree_t *tree, int key) {
    struct node_t *nodo = tree->root;
    while (nodo != tree->nil && key != nodo->key) {
        if (key < nodo->key) {
            nodo = nodo->left;
        } else {
            nodo = nodo->right;
        }
    }
    return nodo;
}

// Retorna o nó mínimo da árvore/subárvore
struct node_t *tree_minimum(struct RB_tree_t *tree, struct node_t *nodo) {
    while (nodo->left != tree->nil) {
        nodo = nodo->left;
    }
    return nodo;
}

// Retorna o nó máximo da árvore/subárvore
struct node_t *tree_maximum(struct RB_tree_t *tree, struct node_t *nodo) {
    while (nodo->right != tree->nil) {
        nodo = nodo->right;
    }
    return nodo;
}

// Retorna o sucessor de um nó
struct node_t *tree_successor(struct RB_tree_t *tree, struct node_t *nodo) {
    if (nodo == tree->nil) {
        return tree->nil;
    }
    if (nodo->right != tree->nil) {
        return tree_minimum(tree, nodo->right);
    }
    struct node_t *y = nodo->father;
    while (y != tree->nil && nodo == y->right) {
        nodo = y;
        y = y->father;
    }
    return y;
}

// Retorna o antecessor de um nó
struct node_t *tree_antecessor(struct RB_tree_t *tree, struct node_t *nodo) {
    if (nodo == tree->nil) {
        return tree->nil;
    }
    if (nodo->left != tree->nil) {
        return tree_maximum(tree, nodo->left);
    }
    struct node_t *y = nodo->father;
    while (y != tree->nil && nodo == y->left) {
        nodo = y;
        y = y->father;
    }
    return y;
}

// Rotação à esquerda
void left_rotate(struct RB_tree_t *tree, struct node_t *x) {
    struct node_t *y = x->right; // `y` é o filho direito de `x`
    if (y == tree->nil) {
        printf("Erro: Tentativa de realizar left_rotate em um nó sem filho direito.\n");
        return;
    }

    x->right = y->left; // Move o filho esquerdo de `y` para ser o filho direito de `x`
    if (y->left != tree->nil) {
        y->left->father = x;
    }

    y->father = x->father; // Conecta o pai de `x` a `y`
    if (x->father == tree->nil) {
        tree->root = y; // Atualiza a raiz se `x` era a raiz
    } else if (x == x->father->left) {
        x->father->left = y;
    } else {
        x->father->right = y;
    }

    y->left = x; // Faz `x` o filho esquerdo de `y`
    x->father = y;
}

// Rotação à direita
void right_rotate(struct RB_tree_t *tree, struct node_t *y) {
    struct node_t *x = y->left; // `x` é o filho esquerdo de `y`
    if (x == tree->nil) {
        printf("Erro: Tentativa de realizar right_rotate em um nó sem filho esquerdo.\n");
        return;
    }

    y->left = x->right; // Move o filho direito de `x` para ser o filho esquerdo de `y`
    if (x->right != tree->nil) {
        x->right->father = y;
    }

    x->father = y->father; // Conecta o pai de `y` a `x`
    if (y->father == tree->nil) {
        tree->root = x; // Atualiza a raiz se `y` era a raiz
    } else if (y == y->father->left) {
        y->father->left = x;
    } else {
        y->father->right = x;
    }

    x->right = y; // Faz `y` o filho direito de `x`
    y->father = x;
}

// Insere um nó na árvore
void insert(struct RB_tree_t *tree, struct node_t *node) {
    struct node_t *y = tree->nil;
    struct node_t *x = tree->root;
    while (x != tree->nil) {
        y = x;
        if (node->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    node->father = y;
    if (y == tree->nil) {
        tree->root = node;
    } else if (node->key < y->key) {
        y->left = node;
    } else {
        y->right = node;
    }
    insert_fixup(tree, node);
}

// Corrige a árvore após a inserção
void insert_fixup(struct RB_tree_t *tree, struct node_t *node) {
    while (node->father->color == 'v') {
        if (node->father->father == tree->nil) {
            break; // O avô não existe, então não há mais nada a corrigir
        }
        if (node->father == node->father->father->left) {
            struct node_t *y = node->father->father->right;
            if (y->color == 'v') { // Caso 1: tio vermelho
                node->father->color = 'p';
                y->color = 'p';
                node->father->father->color = 'v';
                node = node->father->father;
            } else {
                if (node == node->father->right) { // Caso 2: zigzag
                    node = node->father;
                    left_rotate(tree, node);
                }
                node->father->color = 'p'; // Caso 3: zigzig
                node->father->father->color = 'v';
                right_rotate(tree, node->father->father);
            }
        } else {
            struct node_t *y = node->father->father->left;
            if (y->color == 'v') { // Caso 4: tio vermelho
                node->father->color = 'p';
                y->color = 'p';
                node->father->father->color = 'v';
                node = node->father->father;
            } else {
                if (node == node->father->left) { // Caso 5: zigzag
                    node = node->father;
                    right_rotate(tree, node);
                }
                node->father->color = 'p'; // Caso 6: zigzig
                node->father->father->color = 'v';
                left_rotate(tree, node->father->father);
            }
        }
    }
    tree->root->color = 'p';
}

// Transplanta um nó
void transplant(struct RB_tree_t *tree, struct node_t *u, struct node_t *v) {
    if (u->father == tree->nil) {
        tree->root = v;
    } else if (u == u->father->left) {
        u->father->left = v;
    } else {
        u->father->right = v;
    }
    v->father = u->father;
}

// Remove um nó da árvore
void delete_node(struct RB_tree_t *tree, struct node_t *nodo) {
    struct node_t *y = nodo;
    char y_color = y->color;
    struct node_t *x;
    if (nodo->left == tree->nil) {
        x = nodo->right;
        transplant(tree, nodo, nodo->right);
    } else if (nodo->right == tree->nil) {
        x = nodo->left;
        transplant(tree, nodo, nodo->left);
    } else {
        y = tree_successor(tree, nodo);
        y_color = y->color;
        x = y->right;
        if (y->father != nodo) {
            transplant(tree, y, y->right);
            y->right = nodo->right;
            y->right->father = y;
        }
        transplant(tree, nodo, y);
        y->left = nodo->left;
        y->left->father = y;
        y->color = nodo->color;
    }
    free(nodo);
    if (y_color == 'p') {
        delete_fixup(tree, x);
    }
}

// Corrige a árvore após a remoção
void delete_fixup(struct RB_tree_t *tree, struct node_t *x) {
    while (x != tree->root && x->color == 'p') {
        if (x == x->father->left) {
            struct node_t *w = x->father->right;
            if (w->color == 'v') { // Caso 1: irmão vermelho
                w->color = 'p';
                x->father->color = 'v';
                left_rotate(tree, x->father);
                w = x->father->right;
            }
            if (w->left->color == 'p' && w->right->color == 'p') { // Caso 2: ambos filhos pretos
                w->color = 'v';
                x = x->father;
            } else {
                if (w->right->color == 'p') { // Caso 3: filho esquerdo vermelho
                    w->left->color = 'p';
                    w->color = 'v';
                    right_rotate(tree, w);
                    w = x->father->right;
                }
                w->color = x->father->color; // Caso 4: filho direito vermelho
                x->father->color = 'p';
                w->right->color = 'p';
                left_rotate(tree, x->father);
                x = tree->root;
            }
        } else {
            struct node_t *w = x->father->left;
            if (w->color == 'v') { // Caso 5: irmão vermelho
                w->color = 'p';
                x->father->color = 'v';
                right_rotate(tree, x->father);
                w = x->father->left;
            }
            if (w->right->color == 'p' && w->left->color == 'p') { // Caso 6: ambos filhos pretos
                w->color = 'v';
                x = x->father;
            } else {
                if (w->left->color == 'p') { // Caso 7: filho direito vermelho
                    w->right->color = 'p';
                    w->color = 'v';
                    left_rotate(tree, w);
                    w = x->father->left;
                }
                w->color = x->father->color; // Caso 8: filho esquerdo vermelho
                x->father->color = 'p';
                w->left->color = 'p';
                right_rotate(tree, x->father);
                x = tree->root;
            }
        }
    }
    x->color = 'p';
}

// Percorre a árvore em ordem
void in_order_traversal(struct RB_tree_t *tree, struct node_t *nodo,int nivel) {
    if (nodo->left != tree->nil) {
        in_order_traversal(tree, nodo->left,nivel+1);
    }
    printf("%d,%d,%d", nodo->key,nivel,nodo->color == 'v' ? 1 : 0); //(vermelho = 1, preto = 0);
    if(nodo != tree_maximum(tree, tree->root)){
        printf("\n");
    }
    if(nodo->right != tree->nil){
        in_order_traversal(tree, nodo->right,nivel+1);
    }
}

// Destroi os nós da árvore
void destroy_nodes(struct RB_tree_t *tree, struct node_t *nodo) {
    if (nodo->left != tree->nil) {
        destroy_nodes(tree, nodo->left);
    }
    if (nodo->right != tree->nil) {
        destroy_nodes(tree, nodo->right);
    }
    free(nodo);
}

// Destroi a árvore
void destroy_tree(struct RB_tree_t *tree) {
    if (tree->root != tree->nil) {
        destroy_nodes(tree, tree->root);
    }
    free(tree->nil);
    free(tree);
}




