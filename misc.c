//used https://stackoverflow.com/questions/16764276/measuring-time-in-millisecond-precision as a ref
#include <stdlib.h>
#include <stdio.h>


#include <GL/gl.h>
#include <GL/glx.h>
#include <GLFW/glfw3.h>

#include "misc.h"

#include "globaldefs.h"
#include "gloverrides.h"

#include "state.h"

GLXFBConfig * (*glXChooseFBConfig_orig) (Display *dpy, int screen, const int * attrib_list, int * nelements) = NULL;
GLFWwindow * (*glfwCreateWindow_orig)(int width ,int height, const char * title, GLFWmonitor * monitor, GLFWwindow * share) = NULL;


GLXFBConfig * glXChooseFBConfig(Display *dpy, int screen, const int * attrib_list, int * nelements){
	printf("yolo\n");
	return glXChooseFBConfig_orig(dpy, screen, attrib_list, nelements);
}

GLFWwindow * glfwCreateWindow(int width ,int height, const char * title, GLFWmonitor * monitor, GLFWwindow * share){
	glfwWindowHint(GLFW_SAMPLES, 4);
	if(!glfwCreateWindow_orig) init();
	return glfwCreateWindow_orig(width, height, title, monitor, share);
}

/*
void glXSwapInterval(Display * dpy, GLXDrawable drawable, int interval){
	if(!glXSwapInterval_orig) init();
	glXSwapInterval_orig(dpy, drawable, 0);
}

void (*glXSwapIntervalSGI_orig)(int interval) = NULL;

void glXSwapIntervalSGI(int interval){
	if(!glXSwapIntervalSGI_orig) init();
	glXSwapIntervalSGI_orig(0);
}

void (*glXSwapBuffers_orig)(Display * dpy, GLXDrawable drawable) = NULL;

void glXSwapBuffers(Display * dpy, GLXDrawable drawable){
	if(!glXSwapBuffers_orig) init();
	glXSwapBuffers_orig(dpy, drawable);
	if(framecount < 0){
		gettimeofday(&tem, NULL);
		framecount = 0;
	}
	framecount++;
	if(framecount % 10){
		struct timeval tem2, tem3;
		gettimeofday(&tem2, NULL);
		timersub(&tem2, &tem, &tem3);
		//print da time
		if(tem3.tv_sec){
			float milli = ((float)tem3.tv_sec * 1000.0) + ((float)tem3.tv_usec / 1000.0);
			float gsec = milli/1000.0;
			float fps = (float)framecount/gsec;
			printf("%i frames in %f milliseconds = %f fps\n", framecount, milli, fps);
			state_status();
//			tem = tem2;
			framecount = -1;
		}
	}
}
*/
