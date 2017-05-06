#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <string.h>
#include <error.h>
#include <errno.h>
#include <libguile.h>

#include "list.h"
/* This testing process works by working two different programs,
here  list.c and list.scm i.e, in different languages, on the same
data and verifing that the results are same
 */

char* print_string(void* s)
{
  return (char*) s;
}
int compare_string(void* s1, void* s2)
{
  return strcmp(s1, s2);
}
static void null_test_success(void** state)
{
  (void) state;
}

static void list_insert_retrieve_test(char* f)
{
  /* read an array of values from a file.
     insert those values into the list. 
     check if the insertion is valid using list_retrive func
 */
  FILE *in_fp = fopen(f, "r");
  char* line = malloc(100 * sizeof(char));
  LIST* l = list_create(&compare_string);
  int rval;
  do{
    rval = fscanf(in_fp, "%s\n", line);
    char* data = malloc(strlen(line) + 1);
    strcpy(data, line);
    list_insert(data, l->end_pos, l);
  }while(rval != EOF);
  list_dump(l, print_string);

  
  fclose(in_fp);
  free(line);
  list_destroy(l);
}


void __wrap_list_dump(LIST* l){
  check_expected_ptr(l);
}

static void list_dump_test(char* f){

  LIST* l = list_create(NULL);
  
  char* line = malloc(100 * sizeof(char));
  FILE *infile = fopen(f, "r");
  if(infile == NULL) error(-1, EBADF, "%s\n", f);
  int rval = 0;
  do{
    rval = fscanf(infile, "%s\n", line);
    /* new memory that just belongs to the list */
    char* data = (malloc (strlen(line) + 1));
    strcpy(data, line);
    if(rval != EOF) list_insert(data, l->end_pos, l);
  }while (rval  != EOF);
  fclose(infile);
  
  char* outfilename = malloc(30 * sizeof(char));
  outfilename[0] = '\0';
  strcat(outfilename, f);
  strcat(outfilename,"__TEST");
  FILE *outfile = fopen(outfilename, "w");
  if(outfile == NULL) error(-1, EBADF, "%s\n", outfilename);
  list_dump_to(l, print_string, outfile);

  free(line);
  free(outfilename);
  fclose(outfile);
  list_destroy(l);
}

/* write a simple search algorithm that tests list for searching and sorting. */
static void list_search_test(LIST*);

int main(void){
  SCM func_symbol;
  SCM func;
  SCM ret_val;
  scm_init_guile();
  scm_c_primitive_load("tests/list.scm");
  func_symbol = scm_c_lookup("list-dump");
  func = scm_variable_ref(func_symbol);
  ret_val = scm_call_1(func, scm_from_locale_string("resources/simple.list"));
  printf("scheme list-dump:\n[%s]\n", scm_to_locale_string(ret_val));
  
  list_dump_test("resources/simple.list");
  list_insert_retrieve_test("resources/simple.list");
  //const struct CMUnitTest tests[] = {cmocka_unit_test(null_test_success)};
  //return cmocka_run_group_tests(tests, NULL, NULL);
}

