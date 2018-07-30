/******************************************************************************
 * Student Name    :     Steph Ridnell
 * RMIT Student ID :     s3272974
 * COURSE CODE     :     CPT 220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "helpers.h"
/******************************************************************************
 * the helpers module is a great place to store functions that don't logically
 * "live" in another module.
 *****************************************************************************/

/* some code from example at https://www.tutorialspoint.com/c_standard_library/c_function_strtol.htm
   and paul miller shared_files tutes */
BOOLEAN str_to_int(const char str[], int* ptrResult) {

  char *ptr;
  long ret;

  ret = strtol(str, &ptr, 10);

  /* check if there is any string - if there is return false */
  if (*ptr) {
    return FALSE;
  }

  *ptrResult = ret;
  return TRUE;
}
