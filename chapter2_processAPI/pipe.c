int pipefd[2];
pipe(pipefd);          // create a pipe

int pid1 = fork();
if (pid1 == 0) {
    // first child: ls
    close(STDOUT_FILENO);        // close stdout
    dup2(pipefd[1], STDOUT_FILENO); // stdout → pipe write end
    close(pipefd[0]);            // close unused read end
    close(pipefd[1]);            // close original write FD
    execlp("ls", "ls", NULL);
}

int pid2 = fork();
if (pid2 == 0) {
    // second child: wc -l
    close(STDIN_FILENO);         // close stdin
    dup2(pipefd[0], STDIN_FILENO); // stdin → pipe read end
    close(pipefd[1]);             // close unused write end
    close(pipefd[0]);             // close original read FD
    execlp("wc", "wc", "-l", NULL);
}

// parent closes both ends and waits
close(pipefd[0]);
close(pipefd[1]);
wait(NULL);
wait(NULL);
