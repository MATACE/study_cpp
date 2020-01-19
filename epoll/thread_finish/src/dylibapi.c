#include "dylibapi.h"

/**
 * @brief Loading dynamic library.
 */
void *LoadDLL(char *dllname)
{
	void *handle;
	handle = dlopen(dllname, RTLD_LAZY | RTLD_GLOBAL);
	if (!handle) {
		printf("%s->%s\n", dllname, dlerror());
		return NULL;
	}

	return handle;
}

/**
 * @brief Close dynamic library.
 */
int ReLoadDLL(void *handle)
{
	return dlclose(handle);
}

/**
 *@brief Get api from dynamic library. 
 */
void *GetDLLAPI(void *handle, const char *symbol)
{
	void *api;
	api = (void*)dlsym(handle, symbol);
	if (!api) {
		printf("%s->%s%d\n", symbol, dlerror(), __LINE__);
		ReLoadDLL(handle);
		return NULL;
	}

	return api;
}

void GetMyselfDLLAPI(char *lib_func_name)
{
    // void *handle;

    // handle = LoadDLL("./libxxx.so.1");
	// if (!handle) {
	// 	printf("%s->%d err\n", __func__, __LINE__);
	// 	return;
	// }

	// // Get DrvInit function form libxxx.so.1 library.
	// FuncType_DrvInit DrvInit = GetDLLAPI(handle, lib_func_name);
	// if (!DrvInit) {
	// 	printf("%s->%d err\n", __func__, __LINE__);
	// 	return;
	// }

    // DrvInit();    
}