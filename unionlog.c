#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <strings.h>

#include "unionlog.h"

//#define unionDebug(...) unionLog(__FILE__, __func__, __LINE__, )
#define FPOS(type,field)   ((unsigned int)&((type*)0)->field)
#define DPOS(type,field)   (type->field)
typedef struct {
	int len;
	char name[19];
	char logname[128];
	int leve;
} LOG,*LOGPTR;


int main()
{
	LOG log;
	LOGPTR  logptr = &log;
	char * name = NULL;
	unsigned int len = FPOS(LOG,logname);
	printf("len = [%d]\n", len);

	strcpy(log.name,"houhaiou");
	strcpy(log.logname,"houhaiou.log");


	log.len = 100;
	printf("log.name = [%d]\n", FPOS(LOG,name));
	printf("log.logname = [%d]\n", FPOS(LOG,logname));

	printf("logptr = [%0x]\n", (unsigned int)logptr);
	printf("len = [%0x]\n", (unsigned int)((char*)logptr+4));
	printf("log.name = [%0x]\n", log.name);
	printf("log.logname = [%0x]\n", log.logname);
	printf("logname ======== [%s]\n", ((char*)&log)+sizeof(int));


	printf("logptr = [%d]\n", *(int *)logptr);
	printf("len = [%s]\n", ((char*)logptr)+4);
	printf("log.name = [%s]\n", ((char*)logptr)+len);
	printf("log.logname = [%s]\n", log.logname);

	return 0;


}
