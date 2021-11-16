#ifndef DATABASE_H
#define DATABASE_H

#include <tree.h>
#include <stack.h>
#include <iommap.h>

struct database {
        node *tree;
        mmap_data data;
        stack_t cleaner;
};

/*
 * Saves database tree to 'file'. 
 *
 * Important! Do not pass file you loaded.
 * Because memory mapping is used...
 */
int save_data(database *const db, const char *file);

/*
 * Loads 'file' database to 'db' tree. It is designed to read 
 * any bullshit at least a little like the real format. 
 *
 * Note! If your file has a format error - that is undefined behaviour.
 * But if you are lucky it will be probably ok...
 */
node *load_data(database *const db, const char *file);

/*
 * Frees allocated data. 
 *
 * Note! You can use database in the future to load another file.
 */
void free_data(database *const db);

/*
 * Creates two nodes. And then makes dependencies with 'location' node.
 *
 *  - 'location' data becomes 'question'. 
 *  - 'yes' node data becomes 'answer'.
 *  - 'no'  node data becomes previous location data.
 */
node *make_data_entry(database *const db, node *location, 
                      const char *answer, const char *question);

/*
 * Note! It is also calls 'free_data' if needed.
 */
void destruct_database(database *const db);

stack_t *construct_database(database *const db);


#endif /* DATABASE_H */
