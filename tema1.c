/**
* isPath()           : checks if given pathern is legit
* displayPathInfo()  : display info required at tema1
* displayMilestone1(): for given arguments displays required info at tema1
*
**/

#include "util.h"

// Display info of given arguments
void displayMilestone1(int argc, char* argv[])
{
  for(int i = 1; i < argc; i++)
    displayPathInfo(argv[i]);
}

// Display required info of a path
void displayPathInfo (char *path)
{
    if(!isPath(path))
      return;

    // Used on extracting data
    struct stat fStat;
    if(lstat(path, &fStat) < 0)
    {
        printf("Eroare la fStat!");
        return;
    }

    printf("\n");
    printf("Informatii despre <%s>\n", path);
    printf("------------------------------------\n");
    printf("Dimensiune fisier  : %lld bytes\n",   (long long) fStat.st_size);
    printf("Numarul de legaturi: %ld legaturi\n", (long) fStat.st_nlink);
    printf("Numarul de inode   : %ld \n",         (long) fStat.st_blocks);

    printf("Permisiuni         : %c%c%c%c%c%c%c%c%c%c \n",
           (S_ISDIR(fStat.st_mode)) ? 'd' : (S_ISLNK(fStat.st_mode)) ? 'l' : '-',

           (fStat.st_mode & S_IRUSR) ? 'r' : '-',
           (fStat.st_mode & S_IWUSR) ? 'w' : '-',
           (fStat.st_mode & S_IXUSR) ? 'x' : '-',

           (fStat.st_mode & S_IRGRP) ? 'r' : '-',
           (fStat.st_mode & S_IWGRP) ? 'w' : '-',
           (fStat.st_mode & S_IXGRP) ? 'x' : '-',

           (fStat.st_mode & S_IROTH) ? 'r' : '-',
           (fStat.st_mode & S_IWOTH) ? 'w' : '-',
           (fStat.st_mode & S_IXOTH) ? 'x' : '-');

    printf((S_ISLNK(fStat.st_mode)) ? "Este link simbolic.\n" : "Nu este link simbolic.\n");

    printf("userid : %ld \ngroupid: %ld\n", (long)fStat.st_uid, (long)fStat.st_gid);
}

// Checks if path is legit
int isPath(char *path)
{
    if(realpath(path, NULL) == NULL)
        return 0;
    else
        return 1;
}
