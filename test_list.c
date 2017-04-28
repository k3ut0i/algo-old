#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>


#include "list.h"
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
static void list_dump_test(LIST*);

/* write a simple search algorithm that tests list for searching and sorting. */
static void list_search_test(LIST*);

int main(void){
  const struct CMUnitTest tests[] = {cmocka_unit_test(null_test_success)};
  return cmocka_run_group_tests(tests, NULL, NULL);
}

