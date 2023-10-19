#include "log.h"

static char * logBuff;
static char * logfilename = NULL;
static size_t logBuffLenOffset = 0;
static int multWriteFlag = 0;
static size_t logFileSize = LOG_FILE_SIZE;

static int logwrite()
{
	int fd = 0;
	struct stat st;
	char syscmd[ 1024 ] = {0};
	time_t attime ;
	struct tm * tmtime;
	char timeBuf[1024] = {0};

	time(&attime);
	tmtime = localtime(&attime);
	snprintf(timeBuf, sizeof(timeBuf), "%04d%02d%02d%02d%02d%02d", tmtime->tm_year+1900, tmtime->tm_mon, tmtime->tm_mday,tmtime->tm_hour,tmtime->tm_min,tmtime->tm_sec);
	if(logfilename == NULL)
	{
		logfilename = "LOG.log";
	}
	if(stat(logfilename, &st) == 0)
	{
		if (st.st_blocks > logFileSize)
		{
			snprintf(syscmd, sizeof(syscmd), "mv %s %s.%s",logfilename,logfilename,timeBuf);
			system(syscmd);	
		}
	}

	if((fd = open(logfilename, O_RDWR|O_APPEND|O_CREAT, 0666)) < 0)
	{
		fprintf(stderr, "[%s] [%s] [%d] [%s]", __FILE__, __func__, __LINE__, "logwrite open file error!\n");
		fprintf(stderr, "open file error , errno = [%d] error:[%s]!\n", errno, strerror(errno));
		return -1;
	}

	if(logBuffLenOffset <= 0)
	{
		return 0;
	}
	if (write(fd, logBuff, logBuffLenOffset) != logBuffLenOffset)
	{
		fprintf(stderr, "[%s] [%s] [%d] [%s] ", __FILE__, __func__, __LINE__, "logwrite wrirte file error!\n");
		close(fd);
		return -1;
	}
	logBuffLenOffset = 0;
	close(fd);

}



int printf_log(const char * const filename, const char * funname, int  linenumber, const char * level, const char * fmt, ...)
{
	int len = 0;
	int offset = 0;
	offset = LOG_SIZE_BUFF - logBuffLenOffset;

	if (fmt == NULL)
	{
		return 0;
	}
	va_list argvs;


	if (logBuff == NULL)
	{
		if((logBuff = calloc(sizeof(char) , LOG_SIZE_BUFF)) == NULL)
		{
			fprintf(stderr, "[%s] [%s] [%d] [%s] ", __FILE__, __func__, __LINE__, "printf_log malloc error!\n");
			return -1;
		}
	}
	if (offset < 6*1024)
	{
		logwrite();	
	}
	va_start(argvs, fmt);
	len = sprintf(logBuff+logBuffLenOffset,"[%s] [%s] [%d] [%s]", \
					filename, funname, linenumber, level);
	if (len > offset)
	{
		logwrite();
		return len;
	}
	logBuffLenOffset += len;
	offset -= len;

	len = vsprintf(logBuff+logBuffLenOffset, fmt, argvs);
	va_end(argvs);
	// 缓冲空间满了， 写日志到文件中
	if (len >= offset)
	{
		// 写日志
		logwrite();
		// 
		return 0;
	}
	logBuffLenOffset += len;
	if (multWriteFlag == 0)
	{
		logwrite();
	}
	// 返回写入的数据
	return len;
}



#if 0
// test log
int main()
{

	logfilename = "log.test.log";
	DEBUGLOG("DEBUG:%s\n", "this is test");
	INFOLOG("%s\n", "this is a test");
	ERRORLOG("ERROR:%s\n", "this is test for error!");
	return 0;
}
#endif
