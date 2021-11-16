#ifndef TREE_H
#define TREE_H

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

#define TREE_DEBUG

#ifdef TREE_DEBUG
void dump_tree(node *root);
#else /* TREE_DEBUG */
static inline void dump_tree(node *root) {}
#endif /* TREE_DEBUG */


#endif /* TREE_H */

