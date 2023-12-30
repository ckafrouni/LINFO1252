#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define RED(x) "\033[31m" x "\033[0m"
#define GREEN(x) "\033[32m" x "\033[0m"
#define BLUE(x) "\033[34m" x "\033[0m"

/**
 * @pre file_name != NULL, nom du fichier source
 *      new_file_name != NULL, nom du fichier destination
 *
 * @post copie le contenu de {file_name} dans {new_file_name} en préservant les permissions.
 * @return le nombre de bytes copiées si la fonction se termine correctement, -1 en cas d'erreur
 */
int myfunc(char *file_name, char *new_file_name)
{
    // TODO
    // Open the old file
    int fd_old = open(file_name, O_RDONLY);
    if (fd_old < 0)
        return -1;

    // Collect its filemode
    struct stat statbuf;
    if (fstat(fd_old, &statbuf))
        return -1;

    // Create the new file with the filemode
    int fd_new = open(new_file_name, O_WRONLY | O_CREAT, statbuf.st_mode);
    if (fd_new < 0)
        return -1;

    // Loop, to read data from fd_old, and write in fd_new
    ssize_t ncopied = 0;
    ssize_t bufsize = 1024;
    char *buf = (char *)malloc(bufsize);
    while (1)
    {
        ssize_t b_read = read(fd_old, buf, bufsize);
        if (b_read < 0)
            return -1;

        ssize_t b_write = write(fd_new, buf, b_read);
        if (b_write < 0)
            return -1;

        ncopied += b_write;

        if (b_read != b_write)
            return -1;
        if (b_read < bufsize)
            break;
    }

    return ncopied;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, BLUE("Usage:\n%s <src_filename> <dest_filename>\n"), argv[0]);
        return 1;
    }

    char *src_filename = argv[1];
    char *dest_filename = argv[2];

    int ret = myfunc(src_filename, dest_filename);
    if (ret == -1)
    {
        fprintf(stderr, RED("There was an error...\n"));
        return 1;
    }

    printf(GREEN("Number of bytes copied = %d\n"), ret);

    return 0;
}
