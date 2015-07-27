#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Implements a simple string set using a binary search tree (BST).
 * More info: https://en.wikipedia.org/wiki/Binary_search_tree
 *
 * Note that this implementation assumes that the strings will not be modified
 * once they are stored in the set (i.e., it does not make copies of the
 * strings).
 *
 * To test, run `$CC -o stringset stringset.c && ./stringset`, where `CC` is
 * your favorite C compiler (e.g., `gcc` or `clang`). The expected output is:
 *
 *     bear
 *     dorothy
 *     lion
 *     scarecrow
 *     tiger
 *     tin man
 *     witch
 *     wizard
 *
 *     Set contains 8 elements
 *
 *     Found dorothy: yes
 *     Found elphaba: no
 */

/** Stores a single string in a binary search tree. */
struct node {
    char *str;             /* String value */
    struct node *left;     /* Left subtree */
    struct node *right;    /* Right subtree */
};

/* We can't typedef this above because the struct refers to itself */
typedef struct node node;

/** Stores information about the entire set. */
typedef struct {
    node *root;                      /* Root node of the BST */
    int size;                        /* Number of elements in the set */
    int (*cmpfn)(char *, char *);    /* String comparison function */
    void (*destroyfn)(char *);       /* String cleanup function */
} stringset;

/** Compare strings in standard lexicographic order. */
int StringCompare(char *left, char *right) {
    return strcmp(left, right);
}

/** Clean up a dynamically allocated string. */
void StringDestroy(char *str) {
    free(str);
}

/**
 * Initialize `set` to be empty, and use the provided functions for ordering
 * and disposing of strings.
 *
 * The comparison function `cmpfn` must not be `NULL`. If `destroyfn` is
 * `NULL`, then no action will be taken to clean up the strings when
 * `SetDestroy` is called on `set`. This is useful, for example, when the
 * strings in the set are statically allocated (i.e. not created with
 * `malloc`).
 *
 * This function runs in constant time.
 *
 * Hint: no allocation should be performed in this function. It's just
 * assigning values to the fields of `set`.
 */
void SetNew(stringset *set,
            int (*cmpfn)(char *, char*),
            void (*destroyfn)(char *)) {
    /* TODO */
}

/** Return the number of elements in `set`. Runs in constant time. */
int SetSize(stringset *set) {
    /* TODO */
    return -1;
}

/**
 * Add `str` to `set`, handling duplicate values appropriately.
 *
 * Return `true` if `str` was not already in `set`, `false` otherwise.
 *
 * This function should execute in time proportional to the height of the BST.
 *
 * Hint: this function will make use of `malloc` (to create a node for `str`)
 * and `set->cmpfn` (to determine where `str` should be inserted).
 */
bool SetAdd(stringset *set, char *str) {
    /* TODO */
    return false;
}

/**
 * Look for an element of `set` that matches `str` according to `set->cmpfn`.
 *
 * Return a pointer to the element if found, and `NULL` otherwise.
 *
 * This function should execute in time proportional to the height of the BST.
 */
char *SetSearch(stringset *set, char *str) {
    /* TODO */
    return NULL;
}

/**
 * Write the elements of `set` to standard output, one per line.
 *
 * Runs in time proportional to the size of the set.
 *
 * Hint: use recursion and `printf()`.
 */
void SetPrint(stringset *set) {
    /* TODO */
}

/**
 * Free all memory used by `set`; use `set->destroyfn` to dispose of the
 * elements.
 *
 * If `set->destroyfn` is `NULL`, then no action is performed on the stored
 * strings, but the nodes of the tree must still be freed correctly.
 *
 * Runs in time proportional to the size of the set.
 *
 * Hint: use recursion and `free()`.
 */
void SetDestroy(stringset *set) {
    /* TODO */
}

int main() {
    stringset strset;
    SetNew(&strset, StringCompare, NULL);

    assert(SetAdd(&strset, "lion"));
    assert(SetAdd(&strset, "tiger"));
    assert(SetAdd(&strset, "bear"));

    SetAdd(&strset, "dorothy");
    SetAdd(&strset, "scarecrow");
    SetAdd(&strset, "witch");
    SetAdd(&strset, "tin man");
    SetAdd(&strset, "wizard");

    assert(!SetAdd(&strset, "lion"));
    assert(!SetAdd(&strset, "tiger"));
    assert(!SetAdd(&strset, "bear"));

    SetPrint(&strset);

    printf("\nSet contains %d elements\n", SetSize(&strset));

    char *dorothy = SetSearch(&strset, "dorothy");
    char *elphaba = SetSearch(&strset, "elphaba");

    printf("\n");
    printf("Found dorothy: %s\n", dorothy == NULL ? "no" : "yes");
    printf("Found elphaba: %s\n", elphaba == NULL ? "no" : "yes");

    SetDestroy(&strset);

    return 0;
}
