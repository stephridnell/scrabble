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

void str_to_upper(char *stringPointer) {
  while (*stringPointer != '\0') {
    *stringPointer = toupper(*stringPointer);
    ++stringPointer;
  }
}

/**
 * finds how many of the specified needle char exists in the string haystack
 * FROM PAUL MILLER ASS2PARTB SOLUTION
 **/
int count_char(const char haystack[], char needle) {
  const char* find;
  int charcount = 0;
  const char* rest;
  int len = strlen(haystack);

  rest = haystack;

  /* find the first char */
  find = strchr(rest, needle);
  /* if one is not found at all, return 0 as none where found */
  if (!find) {
    return 0;
  }
  /* increment the pointer so we are searching over the rest of the
   * string
   */
  rest = ++find;
  /* continue to search over the rest of the string until there are
   * no further instances of the char specified */
  while (find && find - haystack < len) {
    ++charcount;
    find = strchr(rest, needle);
    if (!find) {
      break;
    }
    rest = ++find;
  }
  return charcount;
}

/**
 *  splits the string passed in into substrings at each occurence of a char in
 * delims. The expected parameter specified how many tokens are expected.
 * Please note that both the char ** return value and each of the elements held
 * in that array is also malloced. It is the responsibility of the code that
 * recieves this return value to free all the memory allocated.
 * 
 * FROM PAUL MILLER ASS2PARTB SOLUTION
 **/
char** tokenize(const char line[], const char delims[], int expected) {
  char** token_list;
  char* tok;
  char* linecpy;
  int tokens_seen = 0;
  int count_test, delim_counter;
  int len;

  assert(expected > 0);
  /* grab the length of the string so we don't have to call it multiple
   * times
   */
  len = strlen(delims);
  /* count_test checks that the numnber of delimiters matches the number
   * expected
   */
  count_test = 0;
  for (delim_counter = 0; delim_counter < len; ++delim_counter) {
    int count = count_char(line, delims[delim_counter]);
    if (count > 0) {
      count_test += count;
    }
  }
  /* the number of tokens is one more than the delimiters */
  ++count_test;

  if (count_test != expected) {
    error_print("Error: %s does not have the right number of delimiters.\n", line);
    return NULL;
  }

  /* allocate the space for the array of strings */
  token_list = (char**)malloc(sizeof(char*) * (expected));
  if (!token_list) {
    return NULL;
  }

  /* make a copy of the line as strtok modifies the line passed into it */
  linecpy = strdup(line);
  if (!linecpy) {
    perror("memory allocation");
    free(token_list);
    return NULL;
  }
  /* grab the first token */
  tok = strtok(linecpy, delims);
  while (tok) {
    /* allocate memory and copy the string */
    char* tokcpy = strdup(tok);
    if (!tokcpy) {
      free_tokens(token_list, tokens_seen);
      return NULL;
    }
    /* insert it into the array */
    token_list[tokens_seen++] = tokcpy;
    /* get the next token */
    tok = strtok(NULL, delims);
  }
  /* free the line */
  free(linecpy);
  return token_list;
}

/**
 * frees each token allocated by the tokenize() function as well as the tokens
 * pointer itself.
 * 
 * FROM PAUL MILLER ASS2PARTB SOLUTION
 **/
void free_tokens(char** tokens, int len) {
  int count;

  assert(len > 0);
  assert(tokens);
  /* free each token */
  for (count = 0; count < len; ++count) {
    free(tokens[count]);
  }
  /* free the token ponter */
  free(tokens);
}

/**
 * extracts an integer from a string
 * FROM PAUL MILLER ASS2PARTB SOLUTION
 **/
BOOLEAN strtoint(const char input[], int* output) {
  char* end;
  long lout;
  /* try to extract a long from a string */
  lout = strtol(input, &end, DECIMAL);
  /* if there is leftover data in the string this is not a valid number */
  if (*end) {
    error_print("Error: %s is not numeric.\n", input);
    return FALSE;
  }
  /* if the number is out of the allowed range, reject the result */
  if (lout < INT_MIN || lout > INT_MAX) {
    error_print("Error: %s is not within the range of an int.\n", input);
    return FALSE;
  }
  /* all good so store the result */
  *output = lout;
  return TRUE;
}
