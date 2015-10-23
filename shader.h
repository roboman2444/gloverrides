#ifndef SHADERHEADER
#define SHADERHEADER
	extern void (*glShaderSource_orig)(GLuint, GLsizei, const GLchar **, const GLint *);
	void APIENTRY glShaderSource(GLuint, GLsizei, const GLchar **, const GLint *);

	extern GLuint (*glCreateShader_orig)(GLenum);
	GLuint APIENTRY glCreateShader(GLenum);
#endif
