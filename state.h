#ifndef STATEHEADER
#define STATEHEADER



	void state_status(void);


	extern void (*glActiveTexture_orig)(const GLenum);
	void glActiveTexture(const GLenum);
	extern void (*glAlphaFunc_orig)(const GLenum, const GLclampf);
	void glAlphaFunc(const GLenum, const GLclampf);
	extern void (*glBindTexture_orig)(const GLenum, const GLuint);
	void glBindTexture(const GLenum, const GLuint);
	extern void (*glBindVertexArray_orig)(const GLuint);
	void glBindVertexArray(const GLuint);
	extern void (*glBlendFunc_orig)(const GLenum, const GLenum);
	void glBlendFunc(const GLenum, const GLenum);
	extern void (*glCullFace_orig)(const GLenum);
	void glCullFace(const GLenum);
	extern void (*glDepthFunc_orig)(const GLenum);
	void glDepthFunc(const GLenum);
	extern void (*glDepthMask_orig)(const GLboolean);
	void glDepthMask(const GLboolean);
	extern void (*glUseProgram_orig)(const GLuint);
	void glUseProgram(const GLuint);




#endif
