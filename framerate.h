#ifndef FRAMERATEHEADER
#define FRAMERATEHEADER

	extern void (*glXSwapInterval_orig)(Display *dpy, GLXDrawable drawable, int interval);
	extern void (*glXSwapIntervalSGI_orig)(int interval);
	extern void (*glXSwapBuffers_orig)(Display *dpy, GLXDrawable drawable);

	void glXSwapBuffers(Display *dpy, GLXDrawable drawable);
	void glXSwapInterval(Display *dpy, GLXDrawable drawable, int interval);
	void glXSwapIntervalSGI(int interval);

#endif
