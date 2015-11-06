#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include "shader.h"

#include "gloverrides.h"



//rule types
//0 not a rule?
//1 find/replace
//2 replace entire line
//3 replace entire source
typedef struct rule_s {
	char ** search;
	char ** replace;
	int type;
} rule_t;

//shader types
//0 = not a shader
//1 = Created
//2 = shadersource called

typedef struct shader_s {
	GLuint id;
	GLenum type;
	GLchar ** strings;
	GLsizei count;
	GLint * length;
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
void APIENTRY glShaderSource(GLuint shader, GLsizei count, const GLchar ** string, const GLint *length){
	if(!glShaderSource_orig)init();

	//silly linear search for the shader
	GLsizei i;
	shader_t *sh = 0;
	for(i = 0; i < numshaders; i++){
		if(listshaders[i].id == shader && listshaders[i].type > 0){
			sh = &listshaders[i];
			break;
		}
	}
	if(!sh) printf("NOOOOO\n");
	sh->count = count;
	if(sh->length)free(sh->length);
	sh->length = malloc(count * sizeof(GLint));
	if(sh->strings){
		for(i = 0; i < sh->count; i++){
			if(sh->strings[i]) free(sh->strings[i]);
			sh->strings[i] = 0;
		}
		free(sh->strings); //dont need to 0 because we are gonna set in the malloc
	}
	sh->strings = malloc(count * sizeof(GLchar *));
	printf("Shader source is:\n");
	for(i = 0; i < count; i++){
		printf("%i\n", i);
		if(!string[i]){
			sh->length[i] = 0;
			continue;
		}
		GLint len = length ? length[i] : strlen(string[i]);
		sh->length[i] = len;
		if(len){
			sh->strings[i] = malloc(len + 1);
			memcpy(sh->strings[i], string[i], len);
			sh->strings[i][len] = 0;
			puts(sh->strings[i]);
//			puts(string[i]);
		} else {
			sh->strings[i] = 0;
		}
		printf("%i\n", i);
	}
	printf("End shader source\n");
	sh->type = 2;
	glShaderSource_orig(shader, count, string, length);
	printf("End shader\n");
}

GLuint (*glCreateShader_orig)(GLenum type) = NULL;
GLuint APIENTRY glCreateShader(GLenum type){
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

