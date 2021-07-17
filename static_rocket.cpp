#include <GL/glut.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void rocket() {
  // Main top cone
  glPushMatrix();

  glPushMatrix();
  glTranslatef(0, 2.5, 0);
  glColor3f(0.5, 0.0, 0.0);
  glScaled(2.2, 1.5, 2.2);
  glRotatef(270, 1, 0, 0);
  glutSolidCone(0.2, 1, 30, 30);

  glPopMatrix();

  glPopMatrix();
  glPushMatrix();

  // part where satellite resides
  glPushMatrix();
  glPushMatrix();

  glColor3f(1, 0.7, 0);
  glTranslatef(0, 2, 0);
  glScaled(0.3, 1, 0.3);
  glRotatef(90, 1, 0, 0);
  glutSolidCube(1);
  glPopMatrix();

  glPopMatrix();

  glPopMatrix();
  glPushMatrix();

  glPushMatrix();
  glColor3f(0.5, 0, 0);
  glTranslatef(0, 0.0, 0);
  glScaled(0.3, 4.3, 0.3);
  glRotatef(90, 1, 0, 0);
  glColor3f(1.0, 1.0, 1.0);
  glutSolidTorus(0.5, 1, 30, 30);
  glPopMatrix();

  glPopMatrix();

  // RightSide rocket
  glPushMatrix();
  glTranslatef(0.0, -0.1, 0.0);
  glRotatef(0, 0, 1, 1);

  glPushMatrix();
  glTranslatef(0.7, 1, 0);
  glColor3f(1.0, 1.0, 1.0);
  glScaled(1.5, 1, 1.5);
  glRotatef(270, 1, 0, 0);
  glutSolidCone(0.2, 1, 30, 30);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.7, -0.2, 0);
  glColor3f(0.5, 0, 0);
  glScaled(0.2, 6.5, 0.2);
  glRotatef(90, 1, 0, 0);
  glutSolidTorus(0.2, 1, 30, 30);
  glPopMatrix();

  glPopMatrix();

  // LeftSide rocket

  glPushMatrix();
  glTranslatef(-0.0, -0.1, -0.0);
  glRotatef(-0, 0, 1, 1);

  glPushMatrix();
  glTranslatef(-0.7, 1, 0);
  glColor3f(1, 1.0, 1.0);
  glScaled(1.5, 1, 1.5);
  glRotatef(270, 1, 0, 0);
  glutSolidCone(0.2, 1, 30, 30);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.7, -0.2, 0);
  glColor3f(0.5, 0, 0);
  glScaled(0.2, 6.5, 0.2);
  glRotatef(90, 1, 0, 0);
  glutSolidTorus(0.2, 1, 30, 30);
  glPopMatrix();

  glPopMatrix();
}

void drawRocket() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -13.0f);
  glPushMatrix();

  glScaled(0.5, 0.5, 0.5);
  rocket();

  glPopMatrix();
  glFlush();
  glutSwapBuffers();
}

void doInit() {
  /* Background and foreground color */
  glClearColor(0.0, 0.0, 0.0, 0);
  glViewport(0, 0, 640, 480);

  /* Select the projection matrix and reset it then setup our view perspective
   */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0f, (GLfloat)640 / (GLfloat)480, 0.1f, 200.0f);

  /* Select the modelview matrix, which we alter with rotatef() */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearDepth(2.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void display() {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -13.0f);

  GLfloat mat_ambient[] = {0.0f, 1.0f, 2.0f, 1.0f};
  GLfloat mat_diffuse[] = {0.0f, 1.5f, .5f, 1.0f};
  GLfloat mat_specular[] = {5.0f, 1.0f, 1.0f, 1.0f};
  GLfloat mat_shininess[] = {50.0f};

  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  GLfloat lightIntensity[] = {1.7f, 1.7f, 1.7f, 1.0f};
  GLfloat light_position3[] = {0.0f, 5.0f, 0.0f, 0.0f};

  glLightfv(GL_LIGHT0, GL_POSITION, light_position3);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

  glEnable(GL_COLOR_MATERIAL);

  glFlush();
  glutSwapBuffers();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  glutInitWindowSize(1000, 800);
  glutInitWindowPosition(500, 100);
  glutCreateWindow("PSLV-C19");

  glutDisplayFunc(display);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);

  glutIdleFunc(drawRocket);

  doInit();
  glutMainLoop();
  return 0;
}