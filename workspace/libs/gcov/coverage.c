/*
 * This code is based on the GCOV-related code of the Linux kernel (kept under
 * "kernel/gcov"). It basically uses the convert_to_gcda function to generate
 * the .gcda files information upon application completion, and dump it on the
 * host filesystem via GDB scripting.
 *
 * Original Linux banner follows below - but note that the Linux guys have
 * nothing to do with these modifications, so blame me (and contact me)
 * if something goes wrong.
 *
 * Thanassis Tsiodras
 * Real-time Embedded Software Engineer 
 * System, Software and Technology Department
 * European Space Agency
 *
 * e-mail: ttsiodras@gmail.com / Thanassis.Tsiodras@esa.int (work)
 *
 */


/*
 *  This code maintains a list of active profiling data structures.
 *
 *    Copyright IBM Corp. 2009
 *    Author(s): Peter Oberparleiter <oberpar@linux.vnet.ibm.com>
 *
 *    Uses gcc-internal data definitions.
 *    Based on the gcov-kernel patch by:
 *		 Hubertus Franke <frankeh@us.ibm.com>
 *		 Nigel Hinds <nhinds@us.ibm.com>
 *		 Rajan Ravindran <rajancr@us.ibm.com>
 *		 Peter Oberparleiter <oberpar@linux.vnet.ibm.com>
 *		 Paul Larson
 */

#include "gcov_public.h"
#include "gcov.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct tagGcovInfo {
    struct gcov_info *info;
    struct tagGcovInfo *next;
} GcovInfo;
GcovInfo *headGcov = NULL;

/*
 * __gcov_init is called by gcc-generated constructor code for each object
 * file compiled with -fprofile-arcs.
 */
void __gcov_init(struct gcov_info *info)
{
    GcovInfo *newHead = malloc(sizeof(GcovInfo));
    if (!newHead) {
        exit(1);
    }
    newHead->info = info;
    newHead->next = headGcov;
    headGcov = newHead;
}

void __gcov_exit()
{
    GcovInfo *tmp = headGcov;
    while(tmp) {
        char *buffer;
        unsigned bytesNeeded = convert_to_gcda(NULL, tmp->info);
        buffer = malloc(bytesNeeded);
        if (!buffer) {
            puts("Out of memory!");
            exit(1);
        }
        convert_to_gcda(buffer, tmp->info);
        printf("Emitting %6d bytes for %s\n", bytesNeeded, gcov_info_filename(tmp->info));
        free(buffer);
        tmp = tmp->next;
    }
}

void __gcov_merge_add(gcov_type *counters, unsigned int n_counters)
{
    puts("__gcov_merge_add isn't called, right? Right? RIGHT?");
    fflush(stdout);
    exit(1);
}
