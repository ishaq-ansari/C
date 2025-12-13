// counter: used to track if we’ve found the winner yet
int counter = 0;

// winner: generate a random number in the range [0, totaltickets-1]
int winner = getrandom(0, totaltickets);

// current: pointer to traverse the list of jobs
node_t *current = head;

while (current) {
    counter += current->tickets;  // increment counter by the job's tickets

    if (counter > winner) {
        // Found the winner
        break;
    }

    current = current->next;  // move to the next job
}

// 'current' is the winner; proceed with scheduling...
