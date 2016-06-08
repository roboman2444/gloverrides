#ifndef MISCHEADER
#define MISCHEADER
	extern GLXFBConfig * (*glXChooseFBConfig_orig)(Display *dpy, int screen, const int * attrib_list, int *nelements);
	extern GLFWwindow * (*glfwCreateWindow_orig)(int width, int height, const char * title, GLFWmonitor * monitor, GLFWwindow * share);

/*
	extern void (*glXSwapInterval_orig)(Display *dpy, GLXDrawable drawable, int interval);
	extern void (*glXSwapIntervalSGI_orig)(int interval);
	extern void (*glXSwapBuffers_orig)(Display *dpy, GLXDrawable drawable);

	void glXSwapBuffers(Display *dpy, GLXDrawable drawable);
	void glXSwapInterval(Display *dpy, GLXDrawable drawable, int interval);
	void glXSwapIntervalSGI(int interval);
*/
#endif
