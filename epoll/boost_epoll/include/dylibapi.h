#ifndef DYLIBAPI_H
#define DYLIBAPI_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef int (*FuncType_DrvInit)(void);

void *LoadDLL(char *dllname);
int ReLoadDLL(void *handle);
int ReLoadDLL(void *handle);
void *GetDLLAPI(void *handle, const char *symbol);
void GetMyselfDLLAPI(char *lib_func_name);

#ifdef __cplusplus
}
#endif

#endif // DYLIBAPI_H