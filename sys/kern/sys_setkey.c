#include <sys/sysproto.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/systm.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/sysent.h>
#include <sys/vnode.h>
#include <sys/syslog.h>

#define KEYBITS 128
#define KEYLENGTH(keybits) ((keybits)/8)

#ifndef _SYS_SYSPROTO_H_
struct setkey_args{
  unsigned int keyOne;
  unsigned int keyTwo;
};
#endif


int
sys_setkey(struct thread *td, struct setkey_args *args)
{
  unsigned int keyOne = args->keyOne;
  unsigned int keyTwo = args->keyTwo;
  
  struct ucred *cred = td->td_proc->p_ucred;
  uid_t id = cred->cr_uid;

  unsigned char key[KEYLENGTH(KEYBITS)];

  bzero(key,sizeof(key));
  bcopy (&keyOne, &(key[0]), sizeof (keyOne));
  bcopy (&keyTwo, &(key[sizeof(keyOne)]), sizeof (keyTwo));

  
  /*Disable setting key if both keys provided were zeros*/
  if (keyOne == 0 && keyTwo == 0) {
    cred->keyOne = 0;
    cred->keyTwo = 0;
    return 0;
    
  }

  else {
    cred->keyOne = keyOne;
    cred->keyTwo = keyTwo;
    printf("Added\n");
  log(-1,"Added");
  }

  static struct ucred userList[16];

  int userExistFlag = 0;

  for (int i = 0; i< 16;i++){
    printf("User: %lu\n",(unsigned long int)userList[i].cr_uid);
    printf("K0: %u\n", userList[i].keyOne);
    printf("K1: %u\n", userList[i].keyTwo);
  }


  for(int i = 0; i<16;i++){
    if (id == userList[i].cr_uid){
      userExistFlag = 1;
      if (keyOne == 0 && keyTwo == 0){
	userList[i].keyOne = keyOne;
	userList[i].keyTwo = keyTwo;


	for (int i = 0; i< 16;i++){
    printf("User: %lu\n",(unsigned long int)userList[i].cr_uid);
    printf("K0: %u\n", userList[i].keyOne);
    printf("K1: %u\n", userList[i].keyTwo);
  }
	
	return 0;
      }
      else if (userList[i].keyOne == 0 && userList[i].keyTwo == 0){
	userList[i].keyOne = keyOne;
	userList[i].keyTwo = keyTwo;
	
	return 0;
      }

  }

  if (!userExistFlag){
    for(int i = 0; i<16;i++){
      if(userList[i].cr_uid==0){
	userList[i].keyOne = keyOne;
	userList[i].keyTwo = keyTwo;
	userList[i].cr_uid = id;

	for (int i = 0; i< 16;i++){
    printf("User: %lu\n",(unsigned long int)userList[i].cr_uid);
    printf("K0: %u\n", userList[i].keyOne);
    printf("K1: %u\n", userList[i].keyTwo);
  }

	
	printf("Key Added\n");
	log(-1,"KEY ADDED");
	return 0;
      }
    }
    printf("List is Full\n");
    return 0;
    
  }

  for (int i = 0; i< 16;i++){
    printf("User: %lu\n",(unsigned long int)userList[i].cr_uid);
    printf("K0: %u\n", userList[i].keyOne);
    printf("K1: %u\n", userList[i].keyTwo);
  }
  return 0;

  }
  return 0;
}
