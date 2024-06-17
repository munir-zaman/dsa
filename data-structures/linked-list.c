#include <stdio.h>
#include <stdlib.h>

#define item_type int

#define error_msg(msg) fprintf(stderr, msg)

typedef struct list {
    item_type value;
    struct list* next;
} list;

int length_list(list *l) {
    int len = 0;
    while (l != NULL) {
        len++;
        l = l->next;
    }
    return len;
}

list *get_nth_list(list *l, int n) {
    // get the n-th node from list
    int index = 0;
    while (index <= n && l != NULL) {
        index++;
        l = l->next;
    }
    if (index != n) {
        return NULL; // return NULL if not found
    } else return l; // otherwise return the current node
}

list *search_list(list *l, item_type x) {
    // searches the list l for x
    if (l == NULL) return NULL;
    else if (l->value == x) return l;
    else return search_list(l->next, x);
}

list **insert_list(list **head, item_type x) {
    // inserts [x]->[..] at the start of list
    // first we need to create a new node for [x]
    list *l = (list *) malloc(sizeof(list)); // reserve space of [x]
    if (l == NULL) {
        // safety check
        error_msg("malloc failed when allocating space for new node\n");
        return NULL;
    }

    l->value = x; // set value of l
    l->next = *head; // point to the start of head
    *head = l; // change head to point to our newly added node
}

list **remove_list(list **head, item_type x) {
    // removes the node that has the value x
    if (*head == NULL) {
        // we have to check for empty lists 
        // otherwise we'll get an error at `list *next = current->next;` 
        // if the current node is NULL ()
        return head;
    }
    list *prev = NULL;
    list *current = *head;
    // we can maybe get rid of `list *next`
    // but i am not going to bother cuz i think this is more readable
    list *next = current->next;

    while (current->value != x && current != NULL) {
        // traverse the list untill the value is found or at the end of the list;
        prev = current;
        current = next;
        next = current->next;
    }

    if (current->value == x) {
        // the value was found
        if (prev == NULL) {
            // start of list
            *head = current->next;
            free(current);
        } else {
            prev->next = next;
            free(current);
        }
    } else {
        // the value was not found. return the original head
        return head;
    }
}

list **reverse_list(list **head) {
    // reverses a linked list
    // recursive solution?
    // reverse(a -> b -> c ..) = reverse(b -> c ..) -> a = ... -> c -> b -> a

    list **p = &((*head)->next);
    reverse_list(p);
    // TODO
}