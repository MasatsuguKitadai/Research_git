#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>

mode_t mode = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH;
double pi = 4 * atan(1.0);