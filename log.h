#ifndef __LOG_H__
#define __LOG_H__
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdarg.h>
#include <errno.h>


#define DEBUGLOG(fmt,arg...) \
                printf_log(__FILE__, __func__, __LINE__,"DEBUG", fmt, ##arg)
#define INFOLOG(fmt, arg...) \
                printf_log(__FILE__, __func__, __LINE__,"INFO",fmt, ##arg)
#define ERRORLOG(fmt, arg...) \
                printf_log(__FILE__, __func__, __LINE__, "ERROR",fmt, ##arg)


// 日志缓冲区大小
#define LOG_SIZE_BUFF    1024*1024
// 单个文件大小
#define LOG_FILE_SIZE    1024*1024*10

int printf_log(const char * const filename, const char * funname, int      linenumber, const char * level, const char * fmt, ...);


#endif
