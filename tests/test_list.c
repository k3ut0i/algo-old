#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <error.h>
#include <errno.h>
#include <list.h>
#include <libguile.h>

/* This testing process works by working two different programs,
here  list.c and list.scm i.e, in different languages, on the same
data and verifing that the results are same
 */

static void null_test_success(void** state)
{
  (void) state;
}

static void list_insert_test(LIST*);
static void list_retrieve_test(LIST*);

char* print_string(void* s){
  return (char*) s;
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
  fclose(outfile);
  destroy_list(l);
}

/* write a simple search algorithm that tests list for searching and sorting. */
static void list_search_test(LIST*);

int main(void){
  list_dump_test("resources/simple.list");
  const struct CMUnitTest tests[] = {cmocka_unit_test(null_test_success)};
  return cmocka_run_group_tests(tests, NULL, NULL);
}

