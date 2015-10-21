//used http://www.tcm.phy.cam.ac.uk/sw/wrap.html as a ref
//used https://gist.github.com/Cloudef/9103499 as a ref
#include <stdlib.h>
#include <stdio.h>
//#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>

#define __USE_GNU
#include <dlfcn.h>
#include "stringlib.h"
#include "framerate.h"
#include "shader.h"
#define HOOKDLSYM

#ifdef HOOKDLSYM
static void * (* real_dlsym)(void *, const char *) = NULL;
#else
static void * (* real_dlsym)(void *, const char *) = dlsym;
#endif

void init(void){
	if(!glShaderSource_orig)glShaderSource_orig = real_dlsym(RTLD_NEXT, "glShaderSource");
	if(!glXSwapBuffers_orig)glXSwapBuffers_orig = real_dlsym(RTLD_NEXT, "glXSwapBuffers");
	if(!glCreateShader_orig)glCreateShader_orig = real_dlsym(RTLD_NEXT, "glCreateShader");
}


static void * (*glXGetProcAddress_orig)(const GLubyte * procname) = NULL;
__GLXextFuncPtr glXGetProcAddress(const GLubyte * procname){
//	printf("hooking glxgetprocaddress, %s\n", procname);
#ifndef HOOKDLSYM
	if(!glXGetProcAddress_orig)glXGetProcAddress_orig = dlsym(RTLD_NEXT, "glxGetProcAddress");
#endif
	__GLXextFuncPtr ret = glXGetProcAddress_orig(procname);
	if(!ret) return ret;

	if(string_testEqualN("glShaderSource", (char*)procname, 14)){
		printf("replaced %s\n", procname);
		if(!glShaderSource_orig)glShaderSource_orig = glXGetProcAddress_orig((GLubyte *)"glShaderSource");
		return (__GLXextFuncPtr)glShaderSource;
	} else if(string_testEqualN("glXSwapBuffers", (char*)procname, 14)){
		printf("replaced %s\n", procname);
		if(!glXSwapBuffers_orig)glXSwapBuffers_orig = glXGetProcAddress_orig((GLubyte *)"glXSwapBuffers");
		return (__GLXextFuncPtr)glXSwapBuffers;
	} else if(string_testEqualN("glCreateShader", (char*)procname, 14)){
		printf("replaced %s\n", procname);
		if(!glCreateShader_orig)glCreateShader_orig = glXGetProcAddress_orig((GLubyte *)"glCreateShader");
		return (__GLXextFuncPtr)glCreateShader;
	}
	return ret;
}
/*
static void * (*glXGetProcAddressEXT_orig)(const GLubyte * procname)=NULL;
__GLXextFuncPtr glXGetProcAddressEXT(const GLubyte * procname){
	printf("hooking glxgetprocaddressEXT\n");
#ifndef HOOKDLSYM
	if(!glXGetProcAddressEXT_orig)glXGetProcAddressEXT_orig = dlsym(RTLD_NEXT, "glxGetProcAddressEXT");
#endif
	__GLXextFuncPtr ret = glXGetProcAddressEXT_orig(procname);
	if(!ret) return ret;

	if(string_testEqual("glShaderSource", (char*)procname)){
		glShaderSource_orig = (void*)ret;
		return (__GLXextFuncPtr)glShaderSource;
	}
	return ret;
}
static void * (*glXGetProcAddressARB_orig)(const GLubyte * procname)=NULL;
__GLXextFuncPtr glXGetProcAddressARB(const GLubyte * procname){
	printf("hooking glxgetprocaddressARB\n");
#ifndef HOOKDLSYM
	if(!glXGetProcAddressARB_orig)glXGetProcAddressARB_orig = dlsym(RTLD_NEXT, "glxGetProcAddressARB");
#endif
	__GLXextFuncPtr ret = glXGetProcAddressARB_orig(procname);
	if(!ret) return ret;

	if(string_testEqual("glShaderSource", (char*)procname)){
		glShaderSource_orig = (void*)ret;
		return (__GLXextFuncPtr)glShaderSource;
	}
	return ret;
}
*/
#ifdef HOOKDLSYM
extern void *_dl_sym(void *, const char *, void *);
extern void * dlsym(void * handle, const char * symbol){
	if(!real_dlsym){
		real_dlsym = _dl_sym(RTLD_NEXT, "dlsym", dlsym);
	}
	void *ret = NULL;
	if(symbol && string_testEqual(symbol, "dlsym")) return dlsym;
	if(!(ret = real_dlsym(handle, symbol))) return ret;

	printf("hooked dlsym, %s\n", symbol);
	if(string_testEqualN(symbol, "glXGetProcAddress", 17)){
//		printf("--- HOOK GLXGETPROCADDRESS\n");
		glXGetProcAddress_orig = real_dlsym(handle, "glXGetProcAddress");
		return glXGetProcAddress;
	} else if(string_testEqualN(symbol, "glCreateShader", 14)){
//		printf("--- HOOK GLXGETPROCADDRESS\n");
		glCreateShader_orig = real_dlsym(handle, "glCreateShader");
		return glCreateShader;
	} else if(string_testEqualN(symbol, "glShaderSource", 14)){
//		printf("--- HOOK GLXGETPROCADDRESS\n");
		glShaderSource_orig = real_dlsym(handle, "glShaderSource");
		return glShaderSource;
	}
	return ret;
}
#endif

