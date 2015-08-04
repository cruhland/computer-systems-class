#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>


struct node {
    char *str;
    struct node *left;
    struct node *right;
};

typedef struct node node;

typedef struct {
    node *root;
    int size;
    int (*cmpfn)(char *, char *);
    void (*destroyfn)(char *);
} sortedset;


int StringCompare(char *left, char *right)
{
    return strcmp(left, right);
}


/* Free up the memory of the string */
void StringDestroy(char *str)
{
    free(str);
}


void SetNew(sortedset *set, int (*cmpfn)(char *, char *), void (*destroyfn)(char *))
{
    assert(cmpfn != NULL);

    set->root = NULL;
    set->size = 0;
    set->cmpfn = cmpfn;
    set->destroyfn = destroyfn;
}

int SetSize(sortedset *set)
{
    return set->size;
}



bool RecSetAdd(int (*cmpfn)(char *, char *), node *n, node *new)
{
    int cmp = cmpfn(new->str, n->str);

    if (cmp == 0) {
        // string is in the set, don't add it
        free(new);
        return false;
    } else if (cmp < 0) {
        if (n->left == NULL) {
            n->left = new;
            return true;
        } else {
            return RecSetAdd(cmpfn, n->left, new);
        }
    } else {
        if (n->right == NULL) {
            n->right = new;
            return true;
        } else {
            return RecSetAdd(cmpfn, n->right, new);
        }
    }
}

/* 
 * Returns `true` if and only if the item was added to the set
 */
bool SetAdd(sortedset *set, char *elemPtr)
{
    node *newNode = malloc(sizeof(node));
    newNode->str = elemPtr;
    newNode->left = NULL;
    newNode->right = NULL;

    // find the place in the set to add the element
    if (set->root == NULL) {
        set->root = newNode;
        set->size = 1;
        return true;
    } else {
        bool added = RecSetAdd(set->cmpfn, set->root, newNode);
        if (added) {
            set->size++;
        }
        return added;
    }
}


/*
 * Helper function for SetSearch
 */
char *RecSetSearch(int (*cmpfn)(char *, char *), node *n, char *e)
{
    if (n == NULL) {
        return NULL;
    }
    
    int cmp = cmpfn(e, n->str);
    
    if (cmp == 0) {
        return e;
    } else if (cmp < 0) {
        return RecSetSearch(cmpfn, n->left, e);
    } else {
        return RecSetSearch(cmpfn, n->right, e);
    }
}

/*
 * Finds the element using the provided comparison function.
 * Returns NULL if the element is not found
 */
char *SetSearch(sortedset *set, char *elemPtr)
{
    return RecSetSearch(set->cmpfn, set->root, elemPtr);
}



void dfs(node *n, void (*handle)(char *))
{
    if (n != NULL) {
        dfs(n->left, handle);
        handle(n->str);
        dfs(n->right, handle);
    }
}


void NodeDestroy(node *n)
{
    if (n != NULL) {
        NodeDestroy(n->left);
        NodeDestroy(n->right);
        free(n);
    }
}


void printString(char *s)
{
    printf("%s\n", s);
}

/*
 * Output the elements of the set in order, one per line
 * Hint: DFS
 */
void SetPrint(sortedset *set)
{
    if (set->root == NULL) {
        printf("Nothing to do here!");
    }
    dfs(set->root, printString);
}


/*
 * Free all of the memory used by the Set
 */
void SetDestroy(sortedset *set)
{
    if (set->destroyfn != NULL) {
        dfs(set->root, set->destroyfn);
        NodeDestroy(set->root);
    } 
    set->root = NULL;
    set->size = 0;
    set->cmpfn = NULL;
    set->destroyfn = NULL;
}

int main()
{
    sortedset strset;
    SetNew(&strset, StringCompare, NULL);

    SetAdd(&strset, "lion");
    SetAdd(&strset, "tiger");
    SetAdd(&strset, "bear");

    SetAdd(&strset, "dorothy");
    SetAdd(&strset, "scarecrow");
    SetAdd(&strset, "witch");
    SetAdd(&strset, "tin man");
    SetAdd(&strset, "wizard");

    SetAdd(&strset, "lion");
    SetAdd(&strset, "tiger");
    SetAdd(&strset, "bear");

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
