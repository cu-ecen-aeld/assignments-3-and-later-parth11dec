#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>

int writeToFile(int fd, const void *writestr, size_t count) {
    ssize_t nr;
    nr = write(fd, writestr, strlen(writestr));

    if (nr == -1) {
        perror("Failed to write");
	syslog(LOG_ERR, "Write operation failed\n");
    }
    else
        syslog(LOG_INFO, "%zd bytes written to the file at %d\n", nr, fd);

    return nr;
}

int createFile(const char* writefile) {
    int fd = creat(writefile, 0644);

    if (fd == -1) {
        perror("Failed to open file");
	syslog(LOG_ERR, "Failed to open file %s\n", writefile);
    }
    else
        syslog(LOG_INFO, "Opened %s at fd %d\n", writefile, fd);

    return fd;
}

int main(int argc, char** argv) {
    int fd = -1;
    int nr = 0;
    const char* writefile;
    const char* writestr;

    openlog(NULL, 0, LOG_USER);

    if (argc != 3) {
        syslog(LOG_ERR, "Incorrect arguments, usage: ./writer.o <file-path> <write-str>\n");
	return 1;
    }

    writefile = argv[1];
    writestr = argv[2];

    // Create and open a new file or open if the file already exists
    fd = createFile(writefile);

    if (fd == -1) {
        return 1;
    }

    // Write bytes to the string - nr is number of bytes written
    nr = writeToFile(fd, writestr, strlen(writestr));

    if (nr == -1) {
        return 1;
    }

    // Close the file
    if (close(fd) == -1)
        perror("close");

    closelog();
    
    return 0;
}
