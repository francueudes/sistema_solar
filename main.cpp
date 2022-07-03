#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include "imageloader.h"
#pragma comment(lib, "glew32.lib")

using namespace std;

// Funcao responsavel por criar os planetas
class Planeta{
public:
	float raio, distancia, orbita, velocidade, inclinacao, animacao;
	Planeta(float _raio, float _distance, float _orbit, float _orbitSpeed, float _axisTilt, float _axisAni){
		raio = _raio;
		distancia = _distance;
		orbita = _orbit;
		velocidade = _orbitSpeed;
		inclinacao = _axisTilt;
		animacao = _axisAni;
	}
};

float lightPos[] = { 0.0, 0.0, -75.0, 1.0 };
static float spotAngle = 40;
float spotDirection[] = { 1.0, 0.0, 0.0 };
static float spotExponent = 1.0;

GLuint carregarTextura(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return textureId;
}

GLuint texturaSol, texturaMercurio, texturaVenus, texturaTerra, texturaMarte, texturaJupiter, texturaSaturno, texturaUrano, texturaNetuno, texturaFundo, paginaInicialTextura;

void writeBitmapString(void *font, char *string)
{
	char *c;
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void configuracaoTextura(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	// Configura todas as texturas dos planetas do sistema solar
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	Image* fundo = loadBMP("texturas/fundo.bmp");
	texturaFundo = carregarTextura(fundo);
	delete fundo;

	Image* sol = loadBMP("texturas/sol.bmp");
	texturaSol = carregarTextura(sol);
	delete sol;

	Image* mercurio = loadBMP("texturas/mercurio.bmp");
	texturaMercurio = carregarTextura(mercurio);
	delete mercurio;

	Image* venus = loadBMP("texturas/venus.bmp");
	texturaVenus = carregarTextura(venus);
	delete venus;

	Image* terra = loadBMP("texturas/terra.bmp");
	texturaTerra = carregarTextura(terra);
	delete terra;

	Image* marte = loadBMP("texturas/marte.bmp");			
	texturaMarte = carregarTextura(marte);
	delete marte;

	Image* jupiter = loadBMP("texturas/jupiter.bmp");
	texturaJupiter = carregarTextura(jupiter);
	delete jupiter;

	Image* saturno = loadBMP("texturas/saturno.bmp");
	texturaSaturno = carregarTextura(saturno);
	delete saturno;

	Image* urano = loadBMP("texturas/urano.bmp");
	texturaUrano = carregarTextura(urano);
	delete urano;

	Image* netuno = loadBMP("texturas/netuno.bmp");
	texturaNetuno = carregarTextura(netuno);
	delete netuno;

	Image* paginaInicial = loadBMP("texturas/paginainicial.bmp");
	paginaInicialTextura = carregarTextura(paginaInicial);
	delete paginaInicial;

	//LIGHTING SETUP
	glEnable(GL_LIGHTING);
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float globAmb[] = { 0.5, 0.5, 0.5, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
	glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotAngle);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);
}


// Cria a tela inicial
void drawLogoScene(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, paginaInicialTextura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(-100, -100, -100);
	glTexCoord2f(1.0, 0.0); glVertex3f(100, -100, -100);
	glTexCoord2f(1.0, 1.0); glVertex3f(100, 100, -100);
	glTexCoord2f(0.0, 1.0); glVertex3f(-100, 100, -100);
	glEnd();

	glutSwapBuffers();
}

// Cria o Sol
Planeta sol(5.0, 0, 0, 0, 0, 0);
// Cria o planeta Mercurio
Planeta mercurio(1.0, 7, 0, 4.74, 02.11, 0);
// Cria o planeta Venus
Planeta venus(1.5, 11, 0, 3.50, 177.0, 0);
// Cria o planeta Terra
Planeta terra(2.0, 16, 0, 2.98, 23.44, 0);
// Cria o planeta Marte
Planeta marte(1.2, 21, 0, 2.41, 25.00, 0);
// Cria o planeta Jupiter
Planeta jupiter(3.5, 28, 0, 1.31, 03.13, 0);
// Cria o planeta Saturno
Planeta saturno(3.0, 37, 0, 0.97, 26.70, 0);
// Cria o planeta Urano
Planeta urano(2.5, 45.5, 0, 0.68, 97.77, 0);
// Cria o planeta Netuno
Planeta netuno(2.3, 53.6, 0, 0.54, 28.32, 0);

int comecarAnimacao = 0;
int frameCount = 0;
int zoom = 80;
int logoScene = 1;

// Cria a janela do Sistema Solar
void drawScene(void){
	frameCount++;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Configura a perspectiva de visualização do Sistema Solar, no caso é frontal
	gluLookAt(0.0, 0.0, zoom, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	GLUquadric *quadric;
	quadric = gluNewQuadric();

	// SOL ---------------------------------------------------------------------------------------------

	// Configura a posição do Sol
	glPushMatrix();
	glRotatef(sol.orbita, 0.0, 1.0, 0.0);
	glTranslatef(sol.distancia, 0.0, 0.0);
	
	// Coloca o nome do Sol
	glRasterPos3f(-1.2, 7.0, 0.0);
	glColor3ub(255, 255, 255);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Sol");
	
	// Configura a inclinacao, animacao e textura do Sol
	glPushMatrix();
	glRotatef(sol.inclinacao, 1.0, 0.0, 0.0);
	glRotatef(sol.animacao, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaSol);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, sol.raio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// MERCURIO ---------------------------------------------------------------------------------------------

	// Configura a posição do planeta
	glPushMatrix();
	glRotatef(mercurio.orbita, 0.0, 1.0, 0.0);
	glTranslatef(mercurio.distancia, 0.0, 0.0);

	// Coloca o nome do planeta
	glRasterPos3f(0.0, 3, 0.0);
	glColor3ub(255, 255, 255);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Mercurio");
	
	// Configura a inclinacao, animacao e textura do planeta
	glPushMatrix();
	glRotatef(mercurio.inclinacao, 1.0, 0.0, 0.0);
	glRotatef(mercurio.animacao, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaMercurio);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, mercurio.raio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// VENUS ---------------------------------------------------------------------------------------------

	// Configura a posição do planeta
	glPushMatrix();
	glRotatef(venus.orbita, 0.0, 1.0, 0.0);
	glTranslatef(venus.distancia, 0.0, 0.0);

	// Coloca o nome do planeta
	glRasterPos3f(0.0, 3, 0.0);
	glColor3ub(255, 255, 255);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Venus");
	
	// Configura a inclinacao, animacao e textura do planeta
	glPushMatrix();
	glRotatef(venus.inclinacao, 1.0, 0.0, 0.0);
	glRotatef(venus.animacao, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaVenus);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, venus.raio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// TERRA ---------------------------------------------------------------------------------------------

	// Configura a posição do planeta
	glPushMatrix();
	glRotatef(terra.orbita, 0.0, 1.0, 0.0);
	glTranslatef(terra.distancia, 0.0, 0.0);

	// Coloca o nome do planeta
	glRasterPos3f(0.0, 3, 0.0);
	glColor3ub(255, 255, 255);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Terra");

	// Configura a inclinacao, animacao e textura do planeta
	glPushMatrix();
	glRotatef(terra.inclinacao, 1.0, 0.0, 0.0);
	glRotatef(terra.animacao, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaTerra);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, terra.raio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// MARTE ---------------------------------------------------------------------------------------------

	// Configura a posição do planeta
	glPushMatrix();
	glRotatef(marte.orbita, 0.0, 1.0, 0.0);
	glTranslatef(marte.distancia, 0.0, 0.0);

	// Coloca o nome do planeta
	glRasterPos3f(0.0, 3, 0.0);
	glColor3ub(255, 255, 255);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Marte");
	
	// Configura a inclinacao, animacao e textura do planeta
	glPushMatrix();
	glRotatef(marte.inclinacao, 1.0, 0.0, 0.0);
	glRotatef(marte.animacao, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaMarte);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, marte.raio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// JUPITER ---------------------------------------------------------------------------------------------

	// Configura a posição do planeta
	glPushMatrix();
	glRotatef(jupiter.orbita, 0.0, 1.0, 0.0);
	glTranslatef(jupiter.distancia, 0.0, 0.0);

	// Coloca o nome do planeta
	glRasterPos3f(0.0, 4.4, 0.0);
	glColor3ub(255, 255, 255);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Jupiter");
	
	// Configura a inclinacao, animacao e textura do planeta
	glPushMatrix();
	glRotatef(jupiter.inclinacao, 1.0, 0.0, 0.0);
	glRotatef(jupiter.animacao, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaJupiter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, jupiter.raio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// SATURNO ---------------------------------------------------------------------------------------------

	// Configura a posição do planeta
	glPushMatrix();
	glRotatef(saturno.orbita, 0.0, 1.0, 0.0);
	glTranslatef(saturno.distancia, 0.0, 0.0);

	// Coloca o nome do planeta
	glRasterPos3f(0.0, 4.4, 0.0);
	glColor3ub(255, 255, 255);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Saturno");
	
	// Configura a inclinacao, animacao e textura do planeta
	glPushMatrix();
	glRotatef(saturno.inclinacao, 1.0, 0.0, 0.0);
	glRotatef(saturno.animacao, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaSaturno);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, saturno.raio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// URANO ---------------------------------------------------------------------------------------------

	// Configura a posição do planeta
	glPushMatrix();
	glRotatef(urano.orbita, 0.0, 1.0, 0.0);
	glTranslatef(urano.distancia, 0.0, 0.0);

	// Coloca o nome do planeta
	glRasterPos3f(0.0, 4.4, 0.0);
	glColor3ub(255, 255, 255);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Urano");
	
	// Configura a inclinacao, animacao e textura do planeta
	glPushMatrix();
	glRotatef(urano.inclinacao, 1.0, 0.0, 0.0);
	glRotatef(urano.animacao, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaUrano);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, urano.raio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// NETUNO ---------------------------------------------------------------------------------------------

	// Configura a posição do planeta
	glPushMatrix();
	glRotatef(netuno.orbita, 0.0, 1.0, 0.0);
	glTranslatef(netuno.distancia, 0.0, 0.0);

	// Coloca o nome do planeta
	glRasterPos3f(0.0, 4.4, 0.0);
	glColor3ub(255, 255, 255);
	writeBitmapString(GLUT_BITMAP_HELVETICA_12, "Netuno");

	// Configura a inclinacao, animacao e textura do planeta
	glPushMatrix();
	glRotatef(netuno.inclinacao, 1.0, 0.0, 0.0);
	glRotatef(netuno.animacao, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaNetuno);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluQuadricTexture(quadric, 1);
	gluSphere(quadric, netuno.raio, 20.0, 20.0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	// FUNDO ---------------------------------------------------------------------------------------------

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaFundo);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_POLYGON);
	glTexCoord2f(-1.0, 0.0); glVertex3f(-200, -200, -100);
	glTexCoord2f(2.0, 0.0); glVertex3f(200, -200, -100);
	glTexCoord2f(2.0, 2.0); glVertex3f(200, 200, -100);
	glTexCoord2f(-1.0, 2.0); glVertex3f(-200, 200, -100);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texturaFundo);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(-200, -83, 200);
	glTexCoord2f(8.0, 0.0); glVertex3f(200, -83, 200);
	glTexCoord2f(8.0, 8.0); glVertex3f(200, -83, -200);
	glTexCoord2f(0.0, 8.0); glVertex3f(-200, -83, -200);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glutSwapBuffers();
}

void drawScenesInOrder(void){
	if (logoScene == 1){
		drawLogoScene();
	}
	else {
		drawScene();
	}
}

void resize(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}

void animacao(int n){
	if (comecarAnimacao){
		mercurio.orbita += mercurio.velocidade;
		venus.orbita += venus.velocidade;
		terra.orbita += terra.velocidade;
		marte.orbita += marte.velocidade;
		jupiter.orbita += jupiter.velocidade;
		saturno.orbita += saturno.velocidade;
		urano.orbita += urano.velocidade;
		netuno.orbita += netuno.velocidade;
		if (mercurio, venus, terra, marte, jupiter, saturno, urano, netuno.orbita > 360.0){
			mercurio, venus, terra, marte, jupiter, saturno, urano, netuno.orbita -= 360.0;
		}
		mercurio.animacao += 10.0;
		venus.animacao += 10.0;
		terra.animacao += 10.0;
		marte.animacao += 10.0;
		jupiter.animacao += 10.0;
		saturno.animacao += 10.0;
		urano.animacao += 10.0;
		netuno.animacao += 10.0;
		if (mercurio, venus, terra, marte, jupiter, saturno, urano, netuno.animacao > 360.0){
			mercurio, venus, terra, marte, jupiter, saturno, urano, netuno.animacao -= 360.0;
		}
		glutPostRedisplay();
		glutTimerFunc(30, animacao, 1);
	}
}

void mouseControl(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		if (logoScene) logoScene = 0;

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) exit(0);
	glutPostRedisplay();
}

void mouseWheel(int wheel, int direction, int x, int y)
{
	if (direction > 0 && zoom < 100) zoom++;
	if (direction < 0 && zoom > -75) zoom--;
	glutPostRedisplay();
}

void keyInput(unsigned char key, int x, int y){
	switch (key){
	case 27: exit(0); break;
	case 'a': if (comecarAnimacao) {
		comecarAnimacao = 0;
	} else { 
		comecarAnimacao = 1; 
		animacao(1); 
	} 
			break;
	}
}

void intructions(void){
	cout << "Pressione 'A' para iniciar a animacao dos planetas." << endl;
	cout << "Pressione 'Esc' para fechar a janela." << endl;
}

int main(int argc, char **argv){

	intructions();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 2);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(350, 0);
	glutCreateWindow("AP1 de Computação Gráfica - Sistema Solar");
	glutDisplayFunc(drawScenesInOrder);
	glutReshapeFunc(resize);
	glutMouseFunc(mouseControl);
	glutKeyboardFunc(keyInput);
	glutMouseWheelFunc(mouseWheel);
	glewExperimental = GL_TRUE;
	glewInit();

	configuracaoTextura();
	glutMainLoop();
}