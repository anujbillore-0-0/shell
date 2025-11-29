#include <stdio.h>
#include <stdlib.h>
#include "lsh.h"

/* forward declaration of loop */
void lsh_loop(void);

int main(int argc, char **argv)
{
    /* Load config files, if any (not implemented). */

    /* Run command loop */
    lsh_loop();

    /* Perform any shutdown/cleanup (none for now). */

    return EXIT_SUCCESS;
}
