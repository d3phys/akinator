#include <app/database.h>
#include <parse.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <tree.h>
#include <stack.h>
#include <logs.h>


static void init_connect_entries(node *const root, node *nd, ptrdiff_t n_entries);
static size_t fill_tree_data(char *const buf, node *nodes, size_t n_nodes);
static void save_tree(node *const root, node *nd, FILE *const file);

/*
 * Fills database tree with data, that is contained in 'buf'.
 * It simply wolks through 'nodes' and writes stripped entry 
 * lines to the 'data' field. 
 *
 * Important! It does not create dependencies between nodes.
 */
static size_t fill_tree_data(char *const buf, node *nodes, size_t n_nodes)
{
        assert(buf);
        assert(nodes);
        assert(n_nodes);

        size_t n_real = 0;

        char *cur   = buf;
        char *entry = buf;

        entry = strip_spaces(cur, &cur);
        while (*entry != '\0' && n_nodes-- > 0) {
                nodes->data = entry;
                entry = strip_spaces(cur, &cur);
                n_real++;
                nodes++;
        }

        return n_real;
}

int save_data(database *const db, const char *file)
{
        assert(db);
        assert(file);
        errno = 0;

        FILE *f = fopen(file, "w");
        if (!f) {
                perror("Can't open temp file");
                return errno;
        }

        save_tree(db->tree, db->tree, f);
        fclose(f);

        return 0;
}

static void save_tree(node *const root, node *nd, FILE *const file)
{
        assert(nd);
        assert(root);
        assert(file);

        static int indent = 0;

        if (!nd->left || !nd->right) {
                fprintf(file, "%*s%s\n",  indent, "", nd->data);
                return;
        }

        fprintf(file, "%*s?%s\n", indent, "", nd->data);

        indent += 4;
        save_tree(root, nd->left,  file);
        save_tree(root, nd->right, file);
        indent -= 4;

        if (nd == root)
                indent = 0;
}

node *make_data_entry(database *const db, node *location, 
                      const char *ans, const char *quest)
{
        assert(db);
        assert(location);
        assert(quest && ans);

        node *entry = (node *)calloc(2, sizeof(node));
        if (!entry)
                return nullptr;

        push_stack(&db->cleaner, entry);

        location->left  = entry;
        location->right = entry + 1;

        entry->data = ans;
        (entry+1)->data = location->data;

        location->data = quest;
        return location;
}

node *load_data(database *const db, const char *file)
{
        assert(file);
        assert(db);

$       (int err = mmap_in(&db->data, file);)
        if (err) {
                perror("Can't mmap memory for data");
                return nullptr;
        }

        size_t n = occurs(db->data.buf, '\n');

$       (node *nodes = (node *)calloc(sizeof(node), n);)
        if (!nodes) {
                fprintf(stderr, "Can't allocate memory for database tree\n");
                return nullptr;
        }

        n = fill_tree_data(db->data.buf, nodes, n);
$       (nodes = (node *)realloc(nodes, sizeof(node) * n);)

$       (init_connect_entries(nodes, nodes, n);)
$       (push_stack(&db->cleaner, nodes);)

        db->tree = nodes;
        return db->tree;
}

/*
 * Recursively makes dependencies between data tree nodes. 
 */
static void init_connect_entries(node *const root, node *nd, ptrdiff_t n_entries)
{
        assert(nd);
        assert(root);

        static ptrdiff_t iter = 0;
        iter++;

        if (nd->data[0] != '?')
                return;

        nd->data++;

        if (iter < n_entries) {
                nd->left  = root + iter;
                init_connect_entries(root, root + iter, n_entries);
        }

        if (iter < n_entries) {
                nd->right = root + iter;
                init_connect_entries(root, root + iter, n_entries);
        }

        if (root == nd)
                iter = 0;
}

stack_t *construct_database(database *const db)
{
        assert(db && !db->tree);

        db->tree = nullptr;
        db->data = {
                .buf  = nullptr,
                .size = 0,
        };

$       (stack_t *stk = construct_stack(&db->cleaner);)
        if (!stk)
                fprintf(stderr, "Can't create stack");

        return stk;
}

void free_data(database *const db)
{
        assert(db);

$       (mmap_free(&db->data);)

        while (db->cleaner.size) {
$               (free(pop_stack(&db->cleaner));)
        }
}

void destruct_database(database *const db)
{
        assert(db);

        if (db->data.buf) 
                free_data(db);

$       (destruct_stack(&db->cleaner);)
}
