#ifndef STATEHEADER
#define STATEHEADER


#define STATESENABLEDEPTH 1
#define STATESENABLEBLEND 2
#define STATESENABLECULLFACE 4
#define STATESENABLEMULTISAMPLE 8
#define STATESENABLEALPHATEST 16


#define STATESTEXTUREUNITCOUNT 8
#define STATESUBOBLOCKCOUNT 2
#define STATESTENABLEDTRACK char


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

	vec4_t color;
} glstate_t;




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



	glstate_t state;
	unsigned int colorcalls;
	unsigned int colorredun;




#endif
