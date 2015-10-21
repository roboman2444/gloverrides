#ifndef SHADERHEADER
#define SHADERHEADER
	extern void (*glShaderSource_orig)(GLuint shader, GLsizei count, const GLchar ** string, const GLint * length);
	void glShaderSource(GLuint shader, GLsizei count, const GLchar ** string, const GLint * length);

	extern GLuint (*glCreateShader_orig)(GLenum type);
	GLuint glCreateShader(GLenum type);
#endif
