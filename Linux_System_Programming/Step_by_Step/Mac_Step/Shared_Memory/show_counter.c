#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define  KEY_NUM     9527
#define  MEM_SIZE    1024

/* shmget showcount.c
int
 main(int argc,
      char *argv[])
{
   int   shm_id;
   void *shm_addr;

   if ( -1 == ( shm_id = shmget( (key_t)KEY_NUM, MEM_SIZE, IPC_CREAT | 0666) ) )
   {
      printf("공유 메모리 생성 실패\n");
      return -1;
   }

   if ( (void *) - 1 == ( shm_addr = shmat( shm_id, (void *)0, 0 ) ) )
   {
      printf( "공유 메모리 첨부 실패\n");
      return -1;
   }

   while(1)
   {
      printf( "%s\n", (char *)shm_addr );
      sleep(1);
   }

   return 0;
}
*/

// shmet show_counter.c
int
 main(int argc,
      char *argv[])
{
   int   shm_id;
   void *shm_addr;

   if ( -1 == ( shm_id = shmget( (key_t)KEY_NUM, MEM_SIZE, IPC_CREAT | 0666) ) )
   {
      printf("공유 메모리 생성 실패\n");
      return -1;
   }

   while(1)
   {
     if ( (void *) - 1 == ( shm_addr = shmat( shm_id, (void *)0, 0 ) ) )
       {
          printf( "공유 메모리 첨부 실패\n");
          return -1;
       }
     else {
       printf("공유 메모리 첨부 성공\n");
     }
     printf("%s\n", (char*)shm_addr);

     if ( -1 == shmdt(shm_addr))
       {
         printf("공유 메모리 분리 실패\n");
         return -1;
       }
     else {
       printf("공유 메모리 분리 성공\n");
     }

     sleep(1);
   }

   return 0;
}
