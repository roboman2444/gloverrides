#ifndef COLORHEADER
#define COLORHEADER


extern void (*glColor4fv_orig)(const GLfloat *);

void APIENTRY glColor3ub(GLubyte, GLubyte, GLubyte);
void APIENTRY glColor3us(GLushort, GLushort, GLushort);
void APIENTRY glColor3ui(GLuint, GLuint, GLuint);
void APIENTRY glColor3f(GLfloat, GLfloat, GLfloat);


#endif
