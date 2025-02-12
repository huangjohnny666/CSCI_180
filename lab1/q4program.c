#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>  // Include this for sleep function
#include <sys/types.h> // Include this for setuid, getuid, and fork functions


void main() {
    int fd;
    /* Assume that /etc/readonlyfile is an important system file,
       and it is owned by root with permission 0644.
       Before running this program, you should create
       the file /etc/readonlyfile first. */
    fd = open("/etc/readonlyfile", O_RDWR | O_APPEND);
    if (fd == -1) {
        printf("Cannot open /etc/readonlyfile\n");
        exit(0);
    }
    
    /* Simulate the tasks conducted by the program */
    sleep(1);

    /* After the task, the root privileges are no longer needed,
       it’s time to relinquish the root privileges permanently. */
    setuid(getuid()); // getuid() returns the real uid

    if (fork()) { // In the parent process
        close (fd);
        exit(0);
    } else { // in the child process
        /* Now, assume that the child process is compromised,
        malicious attackers have injected the following
        statements into this process */
        write (fd, "Malicious Data\n", 15);
        close (fd);
    }
}