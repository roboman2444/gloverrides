#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include "globaldefs.h"
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


unsigned int numrules = 0;
rule_t * listrules = 0;

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


//flags
//1 = copy search
//2 = copy replace
int addRule(char ** search, char ** replace, int type, int flags){
	if(!type|| !search || !replace || !search[0] || !replace[0]) return FALSE;
	numrules++;
	listrules = realloc(listrules, numrules * sizeof(rule_t));
	rule_t *rl = &listrules[numrules-1];
	rl->type = type;
	int i;
	if(flags & 1){
		//count number of em
		for(i = 0; search[i]; i++);
		rl->search = malloc((i+1) * sizeof(char *));
		//now copy them over
		for(i = 0; search[i]; i++){
			size_t sz = strlen(search[i])+1;
			rl->search[i] = malloc(sz);
			memcpy(rl->search[i], search[i], sz);
		}
		rl->search[i] = 0;
	} else {
		rl->search = search;
	}
	if(flags & 2){
		//count number of em
		for(i = 0; replace[i]; i++);
		rl->replace = malloc((i+1) * sizeof(char *));
		//now copy them over
		for(i = 0; replace[i]; i++){
			size_t sz = strlen(replace[i])+1;
			rl->replace[i] = malloc(sz);
			memcpy(rl->replace[i], replace[i], sz);
		}
		rl->replace[i] = 0;
	} else {
		rl->replace = replace;
	}
	//rule is there
	return numrules;
}





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

	//check rules
	///its first rule first applied
	//i should probably figure out a better rule system... regex maybe?

	for(i = 0; i < numrules; i++){
		rule_t rule = listrules[i];
		if(!rule.type) continue;
		if(!rule.search || !rule.replace) continue;
		int z;
		for(z = 0; z < count; z++){
			char * search = 0;
			if(rule.search[1]){
				if(!rule.search[z]) break;	// found end of our searchlist
				search = rule.search[z];
			} else search = rule.search[0];		//just one search, global
			char * replace = 0;
			if(rule.replace[1]){
				if(!rule.replace[z]) break;	// found end of our searchlist
				replace = rule.replace[z];
			} else replace = rule.replace[0];		//just one search, global


			char * ststring = sh->strings[z];
			GLint len = sh->length[z];
			if(!ststring) continue;
			char *stdstring = ststring;
			char *spstring = search;
			while(*stdstring){
				if(*stdstring == *spstring){
					spstring++;
					if(!*spstring){// reached the end of the search string, FOUND!
						printf("Found %s in shader %i on line %i %s\n", search, shader, z, stdstring);
						switch(rule.type){
							case 1 :
							//todo
								break;
							case 2 :
							//todo
								break;
							case 3 :
							//todo
								break;
						}
					}
				} else spstring = search;
				stdstring++;
			}
		}
	}

	glShaderSource_orig(shader, count, string, length);
	sh->type = 2;
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

