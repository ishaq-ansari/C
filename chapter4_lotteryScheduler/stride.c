#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define STRIDE_CONST 10000

struct node_t {
    int tickets;
    int stride;
    int pass;
    struct node_t *next;
};

struct node_t *head = NULL;

/*
 * Insert node into list sorted by pass value (ascending)
 */
void insert_sorted(struct node_t *node) {
    if (head == NULL || node->pass < head->pass) {
        node->next = head;
        head = node;
        return;
    }

    struct node_t *curr = head;
    while (curr->next && curr->next->pass <= node->pass) {
        curr = curr->next;
    }

    node->next = curr->next;
    curr->next = node;
}

/*
 * Create a new job and insert it
 */
void insert_job(int tickets) {
    struct node_t *tmp = malloc(sizeof(struct node_t));
    assert(tmp != NULL);

    tmp->tickets = tickets;
    tmp->stride  = STRIDE_CONST / tickets;
    tmp->pass    = 0;
    tmp->next    = NULL;

    insert_sorted(tmp);
}

/*
 * Remove and return the job with minimum pass
 */
struct node_t *remove_min() {
    assert(head != NULL);
    struct node_t *min = head;
    head = head->next;
    min->next = NULL;
    return min;
}

void print_list() {
    struct node_t *curr = head;
    printf("Queue: ");
    while (curr) {
        printf("[tickets=%d pass=%d stride=%d] ",
               curr->tickets, curr->pass, curr->stride);
        curr = curr->next;
    }
    printf("\n");
}

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: stride <loops>\n");
        exit(1);
    }

    int loops = atoi(argv[1]);

    // create jobs
    insert_job(50);
    insert_job(100);
    insert_job(25);

    print_list();

    for (int i = 0; i < loops; i++) {

        // pick job with minimum pass
        struct node_t *curr = remove_min();

        // "schedule" it
        printf("Running job: tickets=%d pass=%d stride=%d\n",
               curr->tickets, curr->pass, curr->stride);

        // update pass
        curr->pass += curr->stride;

        // reinsert into queue
        insert_sorted(curr);

        print_list();
        printf("\n");
    }

    return 0;
}


/*
curr = remove_min(queue); // pick client with min pass
schedule(curr); // run for quantum
curr->pass += curr->stride; // update pass using stride
insert(queue, curr); // return curr to queue
*/