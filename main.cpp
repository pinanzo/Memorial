#include <windows.h>
#include <assert.h>
#include <fstream>

#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#pragma comment(lib, "winmm.lib")
#include "imageloader.h"

using namespace std;

void drawTriangle(GLuint texid, GLfloat texRepetation, GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x2,GLfloat y2,GLfloat z2,GLfloat x3,GLfloat y3,GLfloat z3);
void drawLines(GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x2,GLfloat y2,GLfloat z2);
void drawQuadrangle(GLuint texid, GLfloat texRepetation1, GLfloat texRepetation2, GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x2,GLfloat y2,GLfloat z2,GLfloat x3,GLfloat y3,GLfloat z3, GLfloat x4,GLfloat y4,GLfloat z4 );
void drawBase();
void drawWater();
void drawMonument();
void drawFlag();
void drawYard();

int angle_y=0;
bool can_rotate = false;
GLfloat ZOOM = -10.0;

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
			break;
        case ' ':
            can_rotate = !can_rotate;
            break;
        case '+':
            ZOOM+=0.1;
            break;
        case '-':
            ZOOM-=0.1;
            break;
        case 'w':
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            break;
        case 'a':
            glClearColor(0.22f, 0.69f, 0.87f, 1.0f);
            break;
        case 'b':
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            break;


	}
}



//loadTexture function takes an Image object and returns a GLuint (which is kind of like an unsigned int) giving the id that OpenGL assigned to the texture.
//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;

	//The first argument is the number of textures we need, and the second is an array where OpenGL will store the id's of the textures.
	glGenTextures(1, &textureId); //Make room for our texture
	// to assign the texture id to our image data.
//	We call glBindTexture(GL_TEXTURE_2D, textureId) to let OpenGL know
// that we want to work with the texture we just created. Then, we call glTexImage2D to load the image into OpenGL.
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture
GLuint _textureId1;
GLuint _textureId2;
GLuint _textureId3;
GLuint _textureId4;
GLuint _textureId5;
GLuint _textureId6;


void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);


	//Take a look at imageloader.h. This gives us the basic idea of what loadBMP does.
	//(The actual code for loadBMP is in imageloader.cpp.) Given a filename, it returns an Image object,
	//which contains the width and height of the image, as well as the array pixels,
	//which stores the pixels' colors in the format we want.
	//Image* image = loadBMP("C:\\Users\\student\\Desktop\\Desktop\\working-texture\\a.bmp");

	Image* image = loadBMP("C:\\Users\\User\\Documents\\GLUT_Projects\\Memorial\\concrete.bmp");

	//Image* image1 = loadBMP("C:\\Users\\student\\Desktop\\Desktop\\working-texture\\vtr.bmp");
	Image* image1 = loadBMP("C:\\Users\\User\\Documents\\GLUT_Projects\\Memorial\\brick.bmp");

	Image* image2 = loadBMP("C:\\Users\\User\\Documents\\GLUT_Projects\\Memorial\\grass.bmp");

	Image* image3 = loadBMP("C:\\Users\\User\\Documents\\GLUT_Projects\\Memorial\\darkconcrete.bmp");

    Image* image4 = loadBMP("C:\\Users\\User\\Documents\\GLUT_Projects\\Memorial\\Flag.bmp");

    Image* image5 = loadBMP("C:\\Users\\User\\Documents\\GLUT_Projects\\Memorial\\water.bmp");

    Image* image6 = loadBMP("C:\\Users\\User\\Documents\\GLUT_Projects\\Memorial\\brick2.bmp");



	//Once we've got the image, we have to send it to OpenGL. We do this in a function we write called loadTexture.
	_textureId = loadTexture(image);
	delete image;
	_textureId1 = loadTexture(image1);
	delete image1;
	_textureId2 = loadTexture(image2);
	delete image2;
	_textureId3 = loadTexture(image3);
	delete image3;
	_textureId4 = loadTexture(image4);
	delete image4;
	_textureId5 = loadTexture(image5);
	delete image5;
    _textureId6 = loadTexture(image6);
	delete image6;



	//Note that we should only use images whose widths and heights are 64, 128, or 256, since computers like powers of 2.
    //	Other sizes of images might not work properly.



}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glRotatef(180,0.0f,1.0f,0.0f);

	glTranslatef(0.0f, -1.0f, ZOOM);
    glRotatef(angle_y,0.0f,1.0f,0.0f);
	GLfloat ambientLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat directedLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat directedLightPos[] = {5.0f, 5.0f, 5.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);


    drawMonument();
    drawBase();
    drawYard();
    drawFlag();

}
void drawYard(){
    drawQuadrangle(_textureId6, 20,20,        -10, -0.401, 5,    0, -0.401, 15,    10, -0.401, 5,    0, -0.401, -5);///memorial er samner mejhe
    int i=0;
    for(GLfloat x=-9,z=5; i<3; i++, x+=1.5, z-=1.5){
        drawQuadrangle(_textureId2, 1,1,        x, -0.4, z,    x+1, -0.4, z-1,    x+2, -0.4, z,    x+1, -0.4, z+1);///grass
        drawQuadrangle(_textureId2, 1,1,        -x, -0.4, z,    -(x+1), -0.4, z-1,    -(x+2), -0.4, z,    -(x+1), -0.4, z+1);///grass
    }
    i=0;
    for(GLfloat x=-9,z=5; i<3; i++, x+=1.5, z+=1.5){
        if(i==0)continue;
        drawQuadrangle(_textureId2, 1,1,        x, -0.4, z,    x+1, -0.4, z-1,    x+2, -0.4, z,    x+1, -0.4, z+1);///grass
        drawQuadrangle(_textureId2, 1,1,        -x, -0.4, z,    -(x+1), -0.4, z-1,    -(x+2), -0.4, z,    -(x+1), -0.4, z+1);///grass
    }
    drawTriangle(_textureId2, 1, -6, -0.4, 5,    -4, -0.4, 7,   -4, -0.4, 3);
    drawTriangle(_textureId2, 1, 6, -0.4, 5,    4, -0.4, 7,   4, -0.4, 3);
}

void drawFlag(){
    glLineWidth(5.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawLines(0, -0.4, 2.0,    0, 2.0, 2.0); /// flag stand
    glLineWidth(1.0f);
    drawQuadrangle(_textureId4, 1,1, 0, 2.0, 2.0,    0, 1.5, 2.0,    0.8, 1.5, 2.0,    0.8, 2.0, 2.0);///flag
    drawWater();
	glutSwapBuffers();
}
void drawMonument(){
    glLineWidth(5.0f);
    glColor3f(0.27f, 0.27f, 0.4f);
    drawLines(-0.285, 1.5, -0.214,    0.285, 1.5, -0.214);
    glLineWidth(1.0f);
    //drawTriangle(_textureId, 5.0,    -0.285, 1.5, -0.214, 0.285, 1.5, -0.214, 0.0, 1.5, -0.5);


    drawTriangle(_textureId3, 5.0,    -0.285, 1.5, -0.214, 0.285, 1.5, -0.214, 0.0, 2.5, -0.5);
    drawTriangle(_textureId3, 5.0,    -0.285, 1.5, -0.214, 0.285, 1.5, -0.214, 0.0, 0.5, -0.5);


    for (GLfloat x1=0.5f, y1=0.0f, z1=0.0f, x2=0.0f, y2=3.5f, z2=-0.5f, x3=0.0f,y3=0.0f,z3=-0.5f;x1<=3.5f; x1+=0.5f, y2-=0.5f, z2-=0.5f, z3-=0.5f){
        drawTriangle(_textureId, 5.0f, -x1,y1,z1,  x2,y2,z2,   x3,y3,z3);
        drawTriangle(_textureId, 5.0f, x1,y1,z1,  x2,y2,z2,   x3,y3,z3);
    }
    for (GLfloat x1=0.5f, y1=0.0f, z1=0.0f, x2=0.0f, y2=3.5f, z2=-0.5f, x3=0.0f,y3=0.0f,z3=-0.5f;x1<=3.5f; x1+=0.5f, y2-=0.5f, z2-=0.5f, z3-=0.5f){
        glColor3f(0.3f, 0.3f, 0.3f);
        drawLines(-x1,y1,z1,  x2,y2,z2);
        drawLines(x2,y2,z2,   x3,y3,z3);
        drawLines(-x1,y1,z1,   x3,y3,z3);

        drawLines(x1,y1,z1,  x2,y2,z2);
        drawLines(x2,y2,z2,   x3,y3,z3);
        drawLines(x1,y1,z1,   x3,y3,z3);

    }
}
void drawWater(){
    drawQuadrangle(_textureId5, 1,2, -1.5, -0.3, 3.0,    -1.5, -0.3, 10.0,    1.5, -0.3, 10.0,    1.5, -0.3, 3.0);///pani
    drawQuadrangle(_textureId1, 8,1, -1.5, -0.25, 3.0,     -1.5, -0.4, 3.0,     -1.5, -0.4, 10.0,    -1.5, -0.25, 10.0);
    drawQuadrangle(_textureId1, 8,1, 1.5, -0.25, 3.0,     1.5, -0.4, 3.0,     1.5, -0.4, 10.0,    1.5, -0.25, 10.0);
    drawQuadrangle(_textureId1, 4,1, -1.5, -0.25, 3.0,     -1.5, -0.4, 3.0,    1.5, -0.4, 3.0,    1.5, -0.25, 3.0);
    drawQuadrangle(_textureId1, 4,1, -1.5, -0.25, 10.0,     -1.5, -0.4, 10.0,    1.5, -0.4, 10.0,    1.5, -0.25, 10.0);
}


void drawBase(){

    drawTriangle(_textureId1, 10.0,        -5.5, 0, 0.5,    5.5, 0, 0.5,    0, 0, -5);///memorial er nicher mejhe

    for(GLfloat x1=-5.5, y1=0.0, z1=0.5, x2=-5.5, y2=-0.05, z2=0.5, x3=5.5, y3=-0.05, z3=0.5, x4=5.5, y4=0.0, z4=0.5; y1>-0.4;x1+=0.2,x2+=0.2, x3-=0.2, x4-=0.2, y1-=0.05, y2-=0.05, y3-=0.05, y4-=0.05, z1+=0.125, z2+=0.125, z3+=0.125, z4+=0.125){
        drawLines(x1, y1, z1,    x4, y4, z4);
        drawQuadrangle(_textureId1, 5,5,  x1, y1, z1,    x2, y2, z2,    x3, y3, z3,    x4, y4, z4);///vertical stairs
        drawLines(x2, y2+0.001f, z2+0.001f,    x3, y3+0.001f, z3+0.001f);
    }


    for(GLfloat x1=-5.5, y1=-0.05, z1=0.5, x2=-5.3, y2=-0.05, z2=0.625, x3=5.3, y3=-0.05, z3=0.625, x4=5.5, y4=-0.05, z4=0.5;y1>-0.401; x1+=0.2,x2+=0.2, x3-=0.2, x4-=0.2, y1-=0.05, y2-=0.05, y3-=0.05, y4-=0.05, z1+=0.125, z2+=0.125, z3+=0.125, z4+=0.125){
        drawQuadrangle(_textureId1, 5,5,  x1, y1, z1,    x2, y2, z2,    x3, y3, z3,    x4, y4, z4);///horizontal stairs
    }

    //drawTriangle(_textureId2, 10.0,        -5, -0.4, 1.0,    5, -0.4, 1.0,    0, -0.4, 5.5);///memorial er samner mejhe
    drawLines(0,0,-5,    0,-0.4,-5);
    drawQuadrangle(_textureId1, 10,10,    0,0,-5,    0,-0.4,-5,    -5.5,-0.4,0.5,    -5.5,0,0.5);
    drawLines(0,0,-5,    -5.5,0,0.5);
    drawLines(0,-0.4,-5,    -5.5,-0.4,0.5);
    drawQuadrangle(_textureId1, 10,10,    0,0,-5,    0,-0.4,-5,    5.5,-0.4,0.5,    5.5,0,0.5);
    drawLines(0,0,-5,    5.5,0,0.5);
    drawLines(0,-0.4,-5,    5.5,-0.4,0.5);
    drawTriangle(_textureId1, 3,    -5.5,-0.4,0.5,    -3.9,-0.4, 1.5,     -5.5,0,0.5);
    drawTriangle(_textureId1, 3,     5.5,-0.4,0.5,    3.9,-0.4, 1.5,    5.5,0,0.5);
    drawLines(-5.5,-0.4,0.5,     -5.5,0,0.5);
    drawLines(5.5,-0.4,0.5,    5.5,0,0.5);

}


void drawLines(GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x2,GLfloat y2,GLfloat z2){

	glBegin(GL_LINES);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glEnd();
}

void drawTriangle(GLuint texid, GLfloat texRepetation, GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x2,GLfloat y2,GLfloat z2,GLfloat x3,GLfloat y3,GLfloat z3){
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(0.5f, 0.5f, 0.7f);
	glBegin(GL_TRIANGLES);

	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(texRepetation, 0.0f);
	glVertex3f(x1, y1, z1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x2, y2, z2);
	glTexCoord2f(texRepetation, texRepetation);
	glVertex3f(x3, y3, z3);
	glEnd();
    glDisable(GL_TEXTURE_2D);
}
void drawQuadrangle(GLuint texid, GLfloat texRepetation1, GLfloat texRepetation2, GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x2,GLfloat y2,GLfloat z2,GLfloat x3,GLfloat y3,GLfloat z3, GLfloat x4,GLfloat y4,GLfloat z4 ){
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(0.5f, 0.5f, 0.7f);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x1, y1, z1);
	glTexCoord2f(0.0f, texRepetation2);
	glVertex3f(x2, y2, z2);
	glTexCoord2f(texRepetation1, texRepetation2);
	glVertex3f(x3, y3, z3);
	glTexCoord2f(texRepetation1, 0.0f);
	glVertex3f(x4, y4, z4);
	glEnd();
    glDisable(GL_TEXTURE_2D);
}

void update(int v){
    if(can_rotate)angle_y=(angle_y+1)%360;
    glutPostRedisplay();
    glutTimerFunc(50,update,0);
}

int main(int argc, char** argv) {
    PlaySound("C:\\Users\\User\\Documents\\GLUT_Projects\\Memorial\\National_Anthem.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
    glutTimerFunc(50,update,0);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1500, 750);

	glutCreateWindow("National Memorial");
	initRendering();

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutMainLoop();

	//PlaySound("C:\\Users\\User\\Documents\\GLUT_Projects\\Memorial\\National_Anthem.wav", NULL, SND_FILENAME);
	return 0;
}
/*Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h) {

}

Image::~Image() {
	delete[] pixels;
}*/

namespace {
	//Converts a four-character array to an integer, using little-endian form
	int toInt(const char* bytes) {
		return (int)(((unsigned char)bytes[3] << 24) |
					 ((unsigned char)bytes[2] << 16) |
					 ((unsigned char)bytes[1] << 8) |
					 (unsigned char)bytes[0]);
	}

	//Converts a two-character array to a short, using little-endian form
	short toShort(const char* bytes) {
		return (short)(((unsigned char)bytes[1] << 8) |
					   (unsigned char)bytes[0]);
	}

	//Reads the next four bytes as an integer, using little-endian form
	int readInt(ifstream &input) {
		char buffer[4];
		input.read(buffer, 4);
		return toInt(buffer);
	}

	//Reads the next two bytes as a short, using little-endian form
	short readShort(ifstream &input) {
		char buffer[2];
		input.read(buffer, 2);
		return toShort(buffer);
	}

	//Just like auto_ptr, but for arrays
	template<class T>
	class auto_array {
		private:
			T* array;
			mutable bool isReleased;
		public:
			explicit auto_array(T* array_ = NULL) :
				array(array_), isReleased(false) {
			}

			auto_array(const auto_array<T> &aarray) {
				array = aarray.array;
				isReleased = aarray.isReleased;
				aarray.isReleased = true;
			}

			~auto_array() {
				if (!isReleased && array != NULL) {
					delete[] array;
				}
			}

			T* get() const {
				return array;
			}

			T &operator*() const {
				return *array;
			}

			void operator=(const auto_array<T> &aarray) {
				if (!isReleased && array != NULL) {
					delete[] array;
				}
				array = aarray.array;
				isReleased = aarray.isReleased;
				aarray.isReleased = true;
			}

			T* operator->() const {
				return array;
			}

			T* release() {
				isReleased = true;
				return array;
			}

			void reset(T* array_ = NULL) {
				if (!isReleased && array != NULL) {
					delete[] array;
				}
				array = array_;
			}

			T* operator+(int i) {
				return array + i;
			}

			T &operator[](int i) {
				return array[i];
			}
	};
}
