#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include "globaldefs.h"
#include "shadershitter.h"
#include "state.h"
#include "color.h"
#include "mathlib.h"
#include "limits.h"

void (*glColor4fv_orig)(const GLfloat *) = NULL;

void glColor3ub(GLubyte red, GLubyte green, GLubyte blue){
	colorcalls++;
	vec4_t fcolor = {red/(float)UCHAR_MAX, green/(float)UCHAR_MAX, blue/(float)UCHAR_MAX, 1.0};
	if(vec4compare(fcolor, state.color)){
		colorredun++;
	} else {
		//printf("Fcolor3ub is %f %f %f %f\n", fcolor[0], fcolor[1], fcolor[2], fcolor[3]);
		if(!glColor4fv_orig)init();
		glColor4fv_orig(fcolor);
		vec4copy(state.color, fcolor);
	}
}
void glColor3us(GLushort red, GLushort green, GLushort blue){
	colorcalls++;
	vec4_t fcolor = {red/(float)USHRT_MAX, green/(float)USHRT_MAX, blue/(float)USHRT_MAX, 1.0};
	if(vec4compare(fcolor, state.color)){
		colorredun++;
	} else {
		//printf("Fcolor3us is %f %f %f %f\n", fcolor[0], fcolor[1], fcolor[2], fcolor[3]);
		if(!glColor4fv_orig)init();
		glColor4fv_orig(fcolor);
		vec4copy(state.color, fcolor);
	}
}
void glColor3ui(GLuint red, GLuint green, GLuint blue){
	colorcalls++;
	vec4_t fcolor = {red/(float)UINT_MAX, green/(float)UINT_MAX, blue/(float)UINT_MAX, 1.0};
	if(vec4compare(fcolor, state.color)){
		colorredun++;
	} else {
		//printf("Fcolor3ui is %f %f %f %f\n", fcolor[0], fcolor[1], fcolor[2], fcolor[3]);
		if(!glColor4fv_orig)init();
		glColor4fv_orig(fcolor);
		vec4copy(state.color, fcolor);
	}
}

void glColor3f(GLfloat red, GLfloat green, GLfloat blue){
	colorcalls++;
	vec4_t fcolor = {red, green, blue, 1.0};
	if(vec4compare(fcolor, state.color)){
		colorredun++;
	} else {
		//printf("Fcolor3f is %f %f %f %f\n", fcolor[0], fcolor[1], fcolor[2], fcolor[3]);
		if(!glColor4fv_orig)init();
		glColor4fv_orig(fcolor);
		vec4copy(state.color, fcolor);
	}
}
void glColor3d(GLdouble red, GLdouble green, GLdouble blue){
	colorcalls++;
	vec4_t fcolor = {red, green, blue, 1.0};
	if(vec4compare(fcolor, state.color)){
		colorredun++;
	} else {
		////printf("Fcolor is %f %f %f %f\n", fcolor[0], fcolor[1], fcolor[2], fcolor[3]);
		if(!glColor4fv_orig)init();
		glColor4fv_orig(fcolor);
		vec4copy(state.color, fcolor);
	}
}












void glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha){
	colorcalls++;
	vec4_t fcolor = {red/(float)UCHAR_MAX, green/(float)UCHAR_MAX, blue/(float)UCHAR_MAX, alpha/(float)UCHAR_MAX};
	if(vec4compare(fcolor, state.color)){
		colorredun++;
	} else {
		//printf("Fcolor4ub is %f %f %f %f\n", fcolor[0], fcolor[1], fcolor[2], fcolor[3]);
		if(!glColor4fv_orig)init();
		glColor4fv_orig(fcolor);
		vec4copy(state.color, fcolor);
	}
}
void glColor4us(GLushort red, GLushort green, GLushort blue, GLushort alpha){
	colorcalls++;
	vec4_t fcolor = {red/(float)USHRT_MAX, green/(float)USHRT_MAX, blue/(float)USHRT_MAX, alpha/(float)USHRT_MAX};
	if(vec4compare(fcolor, state.color)){
		colorredun++;
	} else {
		//printf("Fcolor4us is %f %f %f %f\n", fcolor[0], fcolor[1], fcolor[2], fcolor[3]);
		if(!glColor4fv_orig)init();
		glColor4fv_orig(fcolor);
		vec4copy(state.color, fcolor);
	}
}
void glColor4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha){
	colorcalls++;
	vec4_t fcolor = {red/(float)UINT_MAX, green/(float)UINT_MAX, blue/(float)UINT_MAX, alpha/(float)UINT_MAX};
	if(vec4compare(fcolor, state.color)){
		colorredun++;
	} else {
		//printf("Fcolor4ui is %f %f %f %f\n", fcolor[0], fcolor[1], fcolor[2], fcolor[3]);
		if(!glColor4fv_orig)init();
		glColor4fv_orig(fcolor);
		vec4copy(state.color, fcolor);
	}
}

void glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){
	colorcalls++;
	vec4_t fcolor = {red, green, blue, alpha};
	if(vec4compare(fcolor, state.color)){
		colorredun++;
	} else {
		//printf("Fcolor4f is %f %f %f %f\n", fcolor[0], fcolor[1], fcolor[2], fcolor[3]);
		if(!glColor4fv_orig)init();
		glColor4fv_orig(fcolor);
		vec4copy(state.color, fcolor);
	}
}
void glColor4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha){
	colorcalls++;
	vec4_t fcolor = {red, green, blue, alpha};
	if(vec4compare(fcolor, state.color)){
		colorredun++;
	} else {
		//printf("Fcolor is %f %f %f %f\n", fcolor[0], fcolor[1], fcolor[2], fcolor[3]);
		if(!glColor4fv_orig)init();
		glColor4fv_orig(fcolor);
		vec4copy(state.color, fcolor);
	}
}
