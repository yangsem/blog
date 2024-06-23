#ifndef __ERRORNO_H
#define __ERRORNO_H

// public error 100-200
#define PUBLIC_MALLOC_FAILED 100        // %s 内存申请失败
#define PUBLIC_INVALID_PARAM 101        // 无效的输入参数 (%s = %s)
#define PUBLIC_INVALID_CALL 102         // 无效的调用 (name = %s, error = %s)
#define PUBLIC_OPEN_DIR_FAILED 103      // 打开文件夹 %s 失败，%s
#define PUBLIC_OPEN_FILE_FAILED 104     // 打开文件 %s 失败，%s
#define PUBLIC_READ_FILE_FAILED 105     // 读取文件 %s 失败，%s
#define PUBLIC_WRITE_FILE_FAILED 106    // 写入文件 %s 失败，%s
#define PUBLIC_CREATE_THREAD_FAILED 107 // 创建 %s 线程失败，%s

#endif //__ERRORNO_H
