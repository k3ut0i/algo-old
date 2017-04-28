#include<stdio.h>
#include<libguile.h>

static SCM
my_hostname(void){
  char* ret_val = getenv("HOSTNAME");
  if(ret_val == NULL)return SCM_BOOL_F;
  else return scm_from_locale_string(ret_val);
  
}
static void
inner_main(void* data, int argc, char** argv){
  scm_c_define_gsubr("my-hostname", 0, 0, 0, my_hostname);
  scm_shell(argc, argv);
}

int main(int argc, char** argv){
  scm_boot_guile(argc, argv, inner_main, 0);
  return 0;
}
