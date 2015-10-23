#ifndef STATEHEADER
#define STATEHEADER



	void state_status(void);


	extern void (*glActiveTexture_orig)(const GLenum);
	void APIENTRY glActiveTexture(const GLenum);
	extern void (*glAlphaFunc_orig)(const GLenum, const GLclampf);
	void APIENTRY glAlphaFunc(const GLenum, const GLclampf);
	extern void (*glBindTexture_orig)(const GLenum, const GLuint);
	void APIENTRY glBindTexture(const GLenum, const GLuint);
	extern void (*glBindVertexArray_orig)(const GLuint);
	void APIENTRY glBindVertexArray(const GLuint);
	extern void (*glBlendFunc_orig)(const GLenum, const GLenum);
	void APIENTRY glBlendFunc(const GLenum, const GLenum);
	extern void (*glCullFace_orig)(const GLenum);
	void APIENTRY glCullFace(const GLenum);
	extern void (*glDepthFunc_orig)(const GLenum);
	void APIENTRY glDepthFunc(const GLenum);
	extern void (*glDepthMask_orig)(const GLboolean);
	void APIENTRY glDepthMask(const GLboolean);
	extern void (*glUseProgram_orig)(const GLuint);
	void APIENTRY glUseProgram(const GLuint);




#endif
