#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <strings.h>

#include <sys/stat.h>
#include <sys/sysproto.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/types.h>
#include <sys/ucred.h>
#include <sys/param.h>

int
main (int argc, char **argv)
{
  int arg2 = (argc == 2);

  if (!arg2) {
    printf("usage: setkey <key>\n");
    return 1;
  }

  unsigned long k = strtol(argv[1], NULL, 0);
  unsigned long keyOne = k & 0xffffffff;
  unsigned long keyTwo = k >> 32;

  syscall(548, keyOne, keyTwo);
  //  struct thread *td;
  //struct ucred *cred;
  // cred = td->td_proc->p_ucred;
  
  // unsigned int k0 = cred->keyOne;
  // unsigned int k1 = cred->keyTwo;
  // printf("%u\n", k0);
  // printf("%u\n", k1);
}
