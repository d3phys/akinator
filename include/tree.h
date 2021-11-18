#ifndef TREE_H
#define TREE_H

#include <stack.h>

struct node {
        node *left  = nullptr;
        node *right = nullptr;
        const char *data;
};

/*
 * Jumps from node to node recursively. 
 * Then applies 'action' to the current node.
 *
 * Note! It calls action() before next jump.
 */
void visit_tree(node *root, void (*action)(node *nd));

/*
 * Finds node with 'data' data.
 * If no such node found nullptr is returned.
 */
node *tree_find(node *root, const char *const data);

/*
 * Finds node with 'data' data.
 * If no such node found nullptr is returned.
 *
 * Fills 'path' stack with addresses of nodes that lie on the path.
 * Note! Path is in direct order.
 *
 *                      A
 *                    /  \
 *                   B   E
 *                 /  \
 *                C   D
 *
 * Path to D node by stack pop(): A->B->D 
 */
node *tree_find_path(node *root, const char *const data, stack_t *path);

#define TREE_DEBUG

#ifdef TREE_DEBUG
void dump_tree(node *root);
#else /* TREE_DEBUG */
static inline void dump_tree(node *root) {}
#endif /* TREE_DEBUG */


#endif /* TREE_H */

