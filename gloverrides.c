//used http://www.tcm.phy.cam.ac.uk/sw/wrap.html as a ref
//used https://gist.github.com/Cloudef/9103499 as a ref
#include <stdlib.h>
#include <stdio.h>
//#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

#define __USE_GNU
#include <dlfcn.h>
#include "globaldefs.h"
#include "stringlib.h"
#include "framerate.h"
#include "shader.h"
#include "state.h"
#include "color.h"
#include "misc.h"

#define HOOKDLSYM

#ifdef HOOKDLSYM
static void * (* real_dlsym)(void *, const char *) = NULL;
#else
#define real_dlsym dlsym
#endif

void init(void){
	if(!glShaderSource_orig)glShaderSource_orig = real_dlsym(RTLD_NEXT, "glShaderSource");
	if(!glXSwapBuffers_orig)glXSwapBuffers_orig = real_dlsym(RTLD_NEXT, "glXSwapBuffers");
	if(!glXSwapInterval_orig)glXSwapInterval_orig = real_dlsym(RTLD_NEXT, "glXSwapIntervalEXT");
	if(!glXSwapIntervalSGI_orig)glXSwapIntervalSGI_orig = real_dlsym(RTLD_NEXT, "glXSwapIntervalSGI");
	if(!glCreateShader_orig)glCreateShader_orig = real_dlsym(RTLD_NEXT, "glCreateShader");
	if(!glActiveTexture_orig)glActiveTexture_orig = real_dlsym(RTLD_NEXT, "glActiveTexture");
	if(!glAlphaFunc_orig)glAlphaFunc_orig = real_dlsym(RTLD_NEXT, "glAlphaFunc");
	if(!glBindTexture_orig)glBindTexture_orig = real_dlsym(RTLD_NEXT, "glBindTexture");
	if(!glBindVertexArray_orig)glBindVertexArray_orig = real_dlsym(RTLD_NEXT, "glBindVertexArray");
	if(!glBlendFunc_orig)glBlendFunc_orig = real_dlsym(RTLD_NEXT, "glBlendFunc");
	if(!glCullFace_orig)glCullFace_orig = real_dlsym(RTLD_NEXT, "glCullFace");
	if(!glColor4fv_orig)glColor4fv_orig = real_dlsym(RTLD_NEXT, "glColor4fv");
	if(!glDepthFunc_orig)glDepthFunc_orig = real_dlsym(RTLD_NEXT, "glDepthFunc");
	if(!glDepthMask_orig)glDepthMask_orig = real_dlsym(RTLD_NEXT, "glDepthMask");
	if(!glUseProgram_orig)glUseProgram_orig = real_dlsym(RTLD_NEXT, "glUseProgram");
	if(!glfwCreateWindow_orig)glfwCreateWindow_orig = real_dlsym(RTLD_NEXT, "glfwCreateWindow");
	state.color[0] = 1.0; state.color[1] = 1.0; state.color[2] = 1.0; state.color[3] = 1.0;
}
static void * (*glutGetProcAddress_orig)(const char * procname) = NULL;

void * glutGetProcAddress(const char * procname){
	if(!glutGetProcAddress_orig)glutGetProcAddress_orig = real_dlsym(RTLD_NEXT, "glutGetProcAddress");
	//printf("DOPE %s\n", procname);
	return glutGetProcAddress_orig(procname);
}

static void * (*glXGetProcAddress_orig)(const GLubyte * procname) = NULL;
__GLXextFuncPtr glXGetProcAddress(const GLubyte * procname){
	printf("hooking glxgetprocaddress, %s\n", procname);
	if(!glXGetProcAddress_orig)glXGetProcAddress_orig = real_dlsym(RTLD_NEXT, "glXGetProcAddress");

	if(string_testEqualN("glShaderSource", (char*)procname, 14)){
		if(!glShaderSource_orig)glShaderSource_orig = glXGetProcAddress_orig((GLubyte *)"glShaderSource");
		printf("replaced %s\n", procname);
		return (__GLXextFuncPtr)glShaderSource;
	} else if(string_testEqualN("glUseProgram", (char*)procname, 12)){
		if(!glUseProgram_orig)glUseProgram_orig = glXGetProcAddress_orig((GLubyte *)"glUseProgram");
		printf("replaced %s\n", procname);
		return (__GLXextFuncPtr)glUseProgram;
	} else if(string_testEqualN("glXSwapBuffers", (char*)procname, 14)){
		if(!glXSwapBuffers_orig)glXSwapBuffers_orig = glXGetProcAddress_orig((GLubyte *)"glXSwapBuffers");
		printf("replaced %s\n", procname);
		return (__GLXextFuncPtr)glXSwapBuffers;
	} else if(string_testEqualN("glXSwapIntervalEXT", (char*)procname, 18)){
		if(!glXSwapInterval_orig)glXSwapInterval_orig = glXGetProcAddress_orig((GLubyte *)"glXSwapIntervalEXT");
		printf("replaced %s\n", procname);
		return (__GLXextFuncPtr)glXSwapInterval;
	} else if(string_testEqualN("glXSwapIntervalSGI", (char*)procname, 18) || string_testEqualN("glXSwapIntervalMESA", (char*) procname, 19)){
		if(!glXSwapIntervalSGI_orig)glXSwapIntervalSGI_orig = glXGetProcAddress_orig((GLubyte *)"glXSwapIntervalSGI");
		printf("replaced %s\n", procname);
		return (__GLXextFuncPtr)glXSwapIntervalSGI;
	} else if(string_testEqualN("glXChooseFBConfig", (char*)procname, 17)){
		if(!glXChooseFBConfig_orig)glXChooseFBConfig_orig = glXGetProcAddress_orig((GLubyte *)"glXChooseFBConfig");
		printf("replaced %s\n", procname);
		return (__GLXextFuncPtr)glXChooseFBConfig;
	} else if(string_testEqualN("glCreateShader", (char*)procname, 14)){
		if(!glCreateShader_orig)glCreateShader_orig = glXGetProcAddress_orig((GLubyte *)"glCreateShader");
		printf("replaced %s\n", procname);
		return (__GLXextFuncPtr)glCreateShader;
	}
	return glXGetProcAddress_orig(procname);
}
__GLXextFuncPtr glXGetProcAddressARB(const GLubyte * procname){
	return glXGetProcAddress(procname);
}
__GLXextFuncPtr glXGetProcAddressEXT(const GLubyte * procname){
	return glXGetProcAddress(procname);
}

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
	} else if(string_testEqualN(symbol, "glutGetProcAddress", 18)){
//		printf("--- HOOK GLXGETPROCADDRESS\n");
		glutGetProcAddress_orig = real_dlsym(handle, "glutGetProcAddress");
		return glutGetProcAddress;
	} else if(string_testEqualN(symbol, "glXSwapBuffers", 14)){
		glXSwapBuffers_orig = real_dlsym(handle, "glXSwapBuffers");
//		printf("replaced %s\n", symbol);
		return (__GLXextFuncPtr)glXSwapBuffers;
	} else if(string_testEqualN(symbol, "glXChooseFBConfig", 17)){
		glXChooseFBConfig_orig = real_dlsym(handle, "glXChooseFBConfig");
//		printf("replaced %s\n", symbol);
		return (__GLXextFuncPtr)glXChooseFBConfig;

	} else if(string_testEqualN(symbol, "glfwCreateWindow", 16)){
		glfwCreateWindow_orig = real_dlsym(handle, "glfwCreateWindow");
//		printf("replaced %s\n", symbol);
		return glfwCreateWindow;

	}
	return ret;
}
#endif

