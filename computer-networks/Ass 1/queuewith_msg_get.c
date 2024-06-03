#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
main()
{
    int msgid; /*return value from msgget()*/
    key_t key; /*key to be passed to msgget()*/
    int mykey;
    msgid = msgget((key) | mykey, IPC_CREAT | 0);
    printf("Message queue is created with key value %d", msgid);
}