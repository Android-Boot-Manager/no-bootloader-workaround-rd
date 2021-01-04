#include <stdio.h>
#include <dirent.h>
 
int dir_count_entries(const char *path) {
    struct dirent *pDirent;
    DIR *pDir;

    // Ensure we can open directory.

    pDir = opendir (path);
    if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", path);
        return 1;
    }

    // Process each entry.
    int res=0;
    while ((pDirent = readdir(pDir)) != NULL) {
        if(pDirent->d_type==DT_DIR){
            res+=1;
            printf ("[%s]\n", pDirent->d_name);
        }
    }

    // Close directory and exit.
    printf("Found: %d dirs", res-2);
    closedir (pDir);
    return res-2;
}
