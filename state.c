#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include "globaldefs.h"
#include "state.h"
#include "shadershitter.h"

#define STATESENABLEDEPTH 1
#define STATESENABLEBLEND 2
#define STATESENABLECULLFACE 4
#define STATESENABLEMULTISAMPLE 8
#define STATESENABLEALPHATEST 16


#define STATESTEXTUREUNITCOUNT 8
#define STATESUBOBLOCKCOUNT 2
#define STATESTENABLEDTRACK char

#define GL_GLEXT_PROTOTYPES
#define GLX_GLXEXT_PROTOTYPES


typedef struct glstate_s {
	char enabledstates;

	GLenum blendsource;
	GLenum blenddest;

	GLenum depthfunc;

	GLenum cullface;

	GLboolean depthmask;

	GLenum alphafunc;
	GLclampf alpharef;

	GLuint vaoid;

	GLuint vboid;
	GLenum vbotype;
	GLuint vborangei;
	GLintptr vborangeo;
	GLsizeiptr vboranges;

	GLuint shaderid;

//	GLenum activetexture;
	unsigned char activetexture;
	//todo i only need one array... textureid. If different and not 0, change
	//IF I CHANGE STATESTEXTUREUNITCOUNT, I HAVE TO MAKE THIS BIGGER
//	STATESTENABLEDTRACK enabledtextures; //only used when applying a whole state
	GLuint textureunitid[STATESTEXTUREUNITCOUNT];
	GLenum textureunittarget[STATESTEXTUREUNITCOUNT];

	GLuint uboblockid[STATESUBOBLOCKCOUNT];
	GLintptr uboblockrangeo[STATESUBOBLOCKCOUNT];
	GLsizeiptr uboblockranges[STATESUBOBLOCKCOUNT];
} glstate_t;

glstate_t state = {0};



unsigned int activetexturecalls = 0;
unsigned int activetextureredun = 0;
unsigned int alphafunccalls = 0;
unsigned int alphafuncredun = 0;
unsigned int bindtexturecalls = 0;
unsigned int bindtextureredun = 0;
unsigned int bindvertexarraycalls = 0;
unsigned int bindvertexarrayredun = 0;
unsigned int blendfunccalls = 0;
unsigned int blendfuncredun = 0;
unsigned int cullfacecalls = 0;
unsigned int cullfaceredun = 0;
unsigned int depthfunccalls = 0;
unsigned int depthfuncredun = 0;
unsigned int depthmaskcalls = 0;
unsigned int depthmaskredun = 0;
unsigned int useprogramcalls = 0;
unsigned int useprogramredun = 0;

void state_status(void){
	printf("State status:\n");
	printf("\tglActiveTexture redundant/total:\t%u/%u\n", activetextureredun, activetexturecalls);
	printf("\tglAlphaFunc redundant/total:\t%u/%u\n", alphafuncredun, alphafunccalls);
	printf("\tglBindTexture redundant/total:\t%u/%u\n", bindtextureredun, bindtexturecalls);
	printf("\tglBindVertexArray redundant/total:\t%u/%u\n", bindvertexarrayredun, bindvertexarraycalls);
	printf("\tglBlendFunc redundant/total:\t%u/%u\n", blendfuncredun, blendfunccalls);
	printf("\tglCullFace redundant/total:\t%u/%u\n", cullfaceredun, cullfacecalls);
	printf("\tglDepthFunc redundant/total:\t%u/%u\n", depthfuncredun, depthfunccalls);
	printf("\tglDepthMask redundant/total:\t%u/%u\n", depthmaskredun, depthmaskcalls);
	printf("\tglUseProgram redundant/total:\t%u/%u\n", useprogramredun, useprogramcalls);
	activetexturecalls = activetextureredun = 0;
	alphafunccalls = alphafuncredun = 0;
	bindtexturecalls = bindtextureredun = 0;
	bindvertexarraycalls = bindvertexarrayredun = 0;
	blendfunccalls = blendfuncredun = 0;
	cullfacecalls = cullfaceredun = 0;
	depthfunccalls = depthfuncredun = 0;
	depthmaskcalls = depthmaskredun = 0;
	useprogramcalls = useprogramredun = 0;
}


void (*glActiveTexture_orig)(const GLenum activetexture) = NULL;
void glActiveTexture(const GLenum activetexture){
	activetexturecalls++;
	if(activetexture != state.activetexture){
		if(!glActiveTexture_orig)init();
		glActiveTexture_orig(activetexture);
		state.activetexture = activetexture;
	} else activetextureredun++;
}
void (*glAlphaFunc_orig)(const GLenum func, const GLclampf ref) = NULL;
void glAlphaFunc(const GLenum func, const GLclampf ref){
	alphafunccalls++;
	if(func != state.alphafunc || ref != state.alpharef){
		if(!glAlphaFunc_orig) init();
		glAlphaFunc_orig(func, ref);
		state.alphafunc = func;
		state.alpharef = ref;
	} else alphafuncredun++;
}
void (*glBindTexture_orig)(const GLenum target, const GLuint id) = NULL;
void glBindTexture(const GLenum target, const GLuint id){
	bindtexturecalls++;
	if(id != state.textureunitid[state.activetexture] ||target != state.textureunittarget[state.activetexture]){
		if(!glBindTexture_orig)init();
		glBindTexture_orig(target, id);
		state.textureunitid[state.activetexture] = id;
		state.textureunittarget[state.activetexture] = target;
	} else bindtextureredun++;
}
void (*glBindVertexArray_orig)(const GLuint id) = NULL;
void glBindVertexArray(const GLuint id){
	bindvertexarraycalls++;
	if(id != state.vaoid){
		if(!glBindVertexArray_orig) init();
		glBindVertexArray_orig(id);
		state.vaoid = id;
	} else bindvertexarrayredun++;
}
void (*glBlendFunc_orig)(const GLenum source, const GLenum dest) = NULL;
void glBlendFunc(const GLenum source, const GLenum dest){
	blendfunccalls++;
	if(source != state.blendsource || dest != state.blenddest){
		if(!glBlendFunc_orig)init();
		glBlendFunc_orig(source, dest);
		state.blendsource = source;
		state.blenddest = dest;
	} else blendfuncredun++;
}
void (*glCullFace_orig)(const GLenum face) = NULL;
void glCullFace(const GLenum face){
	cullfacecalls++;
	if(face != state.cullface){
		if(!glCullFace_orig)init();
		glCullFace_orig(face);
		state.cullface = face;
	} else cullfaceredun++;
}
void (*glDepthFunc_orig)(const GLenum dfunc) = NULL;
void glDepthFunc(const GLenum dfunc){
	depthfunccalls++;
	if(dfunc != state.depthfunc){
		if(!glDepthFunc_orig)init();
		glDepthFunc_orig(dfunc);
		state.depthfunc = dfunc;
	} else depthfuncredun++;
}
void (*glDepthMask_orig)(const GLboolean mask);
void glDepthMask(const GLboolean mask){
	depthmaskcalls++;
	if(mask != state.depthmask){
		glDepthMask_orig(mask);
		state.depthmask = mask;
	} else depthmaskredun++;
}
void (*glUseProgram_orig)(const GLuint shaderid) = NULL;
void glUseProgram(const GLuint shaderid){
	useprogramcalls++;
	if(shaderid != state.shaderid){
		if(!glUseProgram_orig)init();
		glUseProgram_orig(shaderid);
		state.shaderid = shaderid;
	} else useprogramredun++;
}
