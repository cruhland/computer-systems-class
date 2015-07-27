#include "string.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

/**
 * See string.h for function documentation. Please use the assert() function to
 * ensure that requirements are satisfied.
 */


/* Should make use of: malloc() */
void StringNew(string *s, int initialAllocation) {
    assert(initialAllocation > 0);
    s->logical_length = 0;
    s->allocated_length = initialAllocation;
    s->data = malloc(initialAllocation);
}


/* Should make use of: free() */
void StringDispose(string *s) {
    free(s->data);
    s->logical_length = 0;
    s->allocated_length = 0;
    s->data = NULL;
}


/* Should make use of: realloc() */
void StringAppend(string *s, char c) {
    if (s->logical_length == s->allocated_length) {
        s->allocated_length *= 2;
        s->data = realloc(s->data, s->allocated_length);
    }
    s->data[s->logical_length] = c;
    s->logical_length++;
}


int StringLength(const string *s) {
    return s->logical_length;
}


char *StringNth(string *s, int position) {
    assert(position < s->logical_length);
    return s->data + position;
}


void StringReplace(string *s, char c, int position) {
    assert(position < s->logical_length);
    s->data[position] = c;
}


/* Should make use of: realloc(), memmove() */
void StringInsert(string *s, char c, int position) {
    assert(position <= s->logical_length);
    if (s->logical_length == s->allocated_length) {
        s->allocated_length *= 2;
        s->data = realloc(s->data, s->allocated_length);
    }
    memmove(s->data + position + 1, s->data + position, s->logical_length - position);
    s->data[position] = c;
    s->logical_length++;
}


/* Should make use of: memmove() */
void StringDelete(string *s, int position) {
    assert(position < s->logical_length);
    memmove(s->data + position, s->data + position + 1, s->logical_length - position - 1);
    s->logical_length--;
}


/* Should make use of: qsort() */
void StringSort(string *s) {
    qsort(s->data, s->logical_length, sizeof(char), CompareChar);
}


/* Should make use of: bsearch(), CompareChar */
int StringSearch(const string *s, char key, int startIndex, bool isSorted) {
    assert(startIndex < s->logical_length);
    if (isSorted) {
        void *base = s->data + startIndex;
        int num = s->logical_length - startIndex;
        size_t size = sizeof(char);
        void *result = bsearch(&key, base, num, size, CompareChar);
        if (result == NULL) {
            return -1;
        } else {
            return (int) ((char *) result - s->data);
        }
    } else {
        for (int i=startIndex; i<s->logical_length; i++) {
            if (s->data[i] == key) {
                return i;
            }
        }
        return -1;
    }
}
