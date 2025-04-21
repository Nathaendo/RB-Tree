#include "functions.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    struct RB_tree_t *tree = create_tree();
    char operation;
    int value;

    // Ler operações da entrada padrão (stdin)
    while (fscanf(stdin, " %c %d", &operation, &value) != EOF) {
        if (operation == 'i' && search(tree, value) == tree->nil) {
            struct node_t *node = create_node(tree, value);
            insert(tree, node);
        } else if (operation == 'r' && search(tree,value) != tree->nil) {
            // Remover o valor da árvore
            struct node_t *node = search(tree, value);
            if (node != tree->nil) {
                delete_node(tree, node);
            } else {
                fprintf(stdout, "Value %d not found in the tree.\n", value);
            }
        } else {
            fprintf(stdout, "Unknown operation or Invalid value: %c %d\n", operation,value);
        }
    }

    // Imprimir a árvore em ordem na saída padrão (stdout)
    in_order_traversal(tree, tree->root,0);
    fprintf(stdout, "\n");

    // Liberar memória
    destroy_tree(tree);

    return 0;
}