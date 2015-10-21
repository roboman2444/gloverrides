#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include "shader.h"

#include "shadershitter.h"

typedef struct shader_s {
	GLuint id;
	GLenum type;
	GLchar ** strings;
	GLsizei count;
	GLint length;
	int status;
} shader_t;


shader_t *listshaders = 0;
unsigned int numshaders = 0;

typedef struct program_s {
	GLuint id;
	shader_t ** shaders;
	GLsizei shadercount;
} program_t;





void (*glShaderSource_orig)(GLuint shader, GLsizei count, const GLchar ** string, const GLint * length)=NULL;
void glShaderSource(GLuint shader, GLsizei count, const GLchar **string, const GLint *length){
	if(!glShaderSource_orig)init();

//	printf("shadershitter activated\n");

	printf("Shader source is:\n");
	GLsizei i;
	for(i = 0; i < count; i++){
		if(string[i] && string[i][0])puts(string[i]);
	}
	glShaderSource_orig(shader, count, string, length);
}

GLuint (*glCreateShader_orig)(GLenum type) = NULL;
GLuint glCreateShader(GLenum type){
	if(!glCreateShader_orig)init();
	GLuint ret = glCreateShader_orig(type);
	printf("creating shader\n");
	if(!ret) return ret;
	numshaders++;
	listshaders = realloc(listshaders, numshaders * sizeof(shader_t));
	shader_t *ms = &listshaders[numshaders-1];
	ms->id = ret;
	ms->type = type;
	ms->status = 1;
	ms->strings = 0;
	ms->count = 0;
	ms->length = 0;

	return ret;
}

/*
static void (*glShaderSourceEXT_orig)(GLuint shader, GLsizei count, const GLchar ** string, const GLint * length)=NULL;
void glShaderSourceEXT(GLuint shader, GLsizei count, const GLchar **string, const GLint *length){

	printf("shadershitter activated\n");

	printf("Shader source is:\n");
	GLsizei i;
	for(i = 0; i < count; i++){
		if(string[i] && string[i][0])puts(string[i]);
	}
	glShaderSourceEXT_orig(shader, count, string, length);
}
static void (*glShaderSourceARB_orig)(GLuint shader, GLsizei count, const GLchar ** string, const GLint * length)=NULL;
void glShaderSourceARB(GLuint shader, GLsizei count, const GLchar **string, const GLint *length){

	printf("shadershitter activated\n");

	printf("Shader source is:\n");
	GLsizei i;
	for(i = 0; i < count; i++){
		if(string[i] && string[i][0])puts(string[i]);
	}
	glShaderSourceARB_orig(shader, count, string, length);
}
*/

