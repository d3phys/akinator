#include <assert.h>
#include <logs.h>
#include <tree.h>
#include <string.h>
#include <stack.h>

node *tree_find_path(node *root, const char *const data, stack_t *path)
{
        assert(root);
        assert(data);
        assert(path);

        node *found = nullptr;

        if (!strcmp(root->data, data))
                found = root;
        if (root->left  && !found)  
                found = tree_find_path(root->left,  data, path);
        if (root->right && !found) 
                found = tree_find_path(root->right, data, path);

        if (found)
                push_stack(path, root);

        return found;
}

node *tree_find(node *root, const char *const data)
{
        assert(root);
        assert(data);

        if (!strcmp(root->data, data))
                return root; 

        node *found = nullptr;
        if (root->left)  
                found = tree_find(root->left,  data);

        if (root->right && !found) 
                found = tree_find(root->right, data);

        return found;
}

void visit_tree(node *root, void (*action)(node *nd))
{
        assert(root);
        assert(action);

        if (!root)
                return;

        action(root);

        if (root->left)  
                visit_tree(root->left, action);
        if (root->right) 
                visit_tree(root->right, action);
}

