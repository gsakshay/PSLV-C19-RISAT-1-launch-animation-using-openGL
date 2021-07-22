#include <GL/glut.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define ROCKET_CONE 1
#define ROCKET_BODY 2

static double x = 0.0, x1 = 0.0, y1 = 0.1, z1 = 0.0, r = 0, y2 = 0, z2 = 0;

// Variable and their usage:
// x used for : positioning and monitoring of all objects
// x1 & y1 & z1 used for : right and left rockets
// r used for : rotation of main cone, satellite container, left & right
// rockets y2 used for : backward positioning of satellite container z2 used
// for : downward positioning of main cone

// pivotal points for x:
// At 0.0 - program starts
// At 2.0 - Rocket obtains its stationary position and starts to detach
// At 3.0 - Side rockets starts to detach and roates wrt r factor and x1, y1,
// z1 positions At 5.0 - satellite container will detach and rotates wrt r
// factor and moves backward wrt y2 At 5.5 - Main cone of rocket detaches and
// starts falling by rotating wrt r factor and z2 positioning At 6.0 -
// Satellite body changes to solid cube form torus and panels will appear
// At 6.5 - Earth obtains its stationary position and starts rotating wrt y
// axis and x factor At 6.8 - Satellite obtains its position and starts
// rotating

void stroke_output(GLfloat x, GLfloat y, GLfloat a, GLfloat b, GLfloat c,
                   GLint m, const char *format, ...) {
  va_list args;
  size_t size = 200;
  char buffer[200], *p;
  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);
  glPushMatrix(); // character output
  if (m == 4) {
    glColor3f(1.0, 0.54, 0.0);
  } else if (m == 2) {
    glColor3f(0, 1.0, 0);
  } else if (m == 3) {
    glColor3f(1.0, 1.0, 1.0);
  } else if (m == 1) {
    glColor3f(1.0, 1.0, 0.0);
  }
  glTranslatef(x, y, 0);
  glScaled(a, b, c);
  for (p = buffer; *p; p++)
    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *p);
  glPopMatrix(); // character output
}

// RISAT-1 satellite
void risat_1() {

  glPushMatrix(); // complete satellite

  // Core
  glPushMatrix(); // core of satellite
  glColor3f(1, 0.7, 0);
  glTranslatef(0, 2, 0);
  glScaled(0.3, 1, 0.3);
  glRotatef(90, 1, 0, 0);

  if (x >= 6)
    glutSolidCube(1);
  else
    glutSolidTorus(0.5, 1, 30, 30); // iRadius, oRadius, noSides, noRings

  glPopMatrix(); // core of satellite

  // Solar Panel
  // Panel - 1
  glPushMatrix(); // pannel-1
  glColor3f(0, 0, 1);
  glTranslatef(1, 2, 0);

  if (x >= 6) {
    glScaled(4, 1.5, 0.1); // length, breadth & height - pannel unwraps
  } else
    glScaled(0, 0, 0); // length, breadth & height

  glRotatef(-20, 1, 0, 0);
  glutSolidCube(0.5);
  glPopMatrix(); // pannel-1

  // Panel - 2
  glPushMatrix(); // pannel-2
  glColor3f(0, 0, 1);
  glTranslatef(-1, 2, 0);

  if (x >= 6)
    glScaled(4, 1.5, 0.1); // length, breadth & height - pannel unwraps
  else
    glScaled(0, 0, 0); // length, breadth & height

  glRotatef(-20, 1, 0, 0);
  glutSolidCube(0.5);
  glPopMatrix(); // pannel-2

  glPopMatrix(); // complete satellite
}

void rocket() {
  // Main top cone
  glPushMatrix(); // Main cone

  if (x >= 5.5) {
    glTranslatef(z2, -z2, z2);
    glRotatef(r, 0, 1, 1);
  }

  glTranslatef(0, 2.5, 0);
  glColor3f(1, 1, 1);
  glScaled(2.2, 1.5, 2.2);
  glRotatef(270, 1, 0, 0);
  glutSolidCone(0.2, 1, 30, 30); // base, height, slices, stacks
  glPopMatrix();                 // Main cone

  glPushMatrix(); // Satelitte
  if (x >= 6.8) {
    glTranslatef(2, 0, 0);      // Moves 2 units right from origin
    glRotatef(x * 40, 0, 1, 0); // starts rotating after 6.8 with angle x*40
  }
  risat_1();
  glPopMatrix(); // Satelitte

  glPushMatrix(); // satelitte container
  // At 5, container will detach allowing satellite to unwrap
  if (x >= 5) {
    glTranslatef(0, y2, y2); // backward movement of container
    glRotatef(r, 0, 1, 1);   // rotation of container
  }

  glColor3f(1, 0.22, 0.22);
  glTranslatef(0, 0.0, 0);
  glScaled(0.3, 4.3, 0.3); // length, breadth and height
  glRotatef(90, 1, 0, 0);
  glutSolidTorus(0.5, 1, 30, 30); // iRadius, oRadius, noSides, noRings

  glPopMatrix(); // satelitte container

  glPushMatrix();            // Complete rightSide rocket
  glTranslatef(x1, -y1, z1); // Moves right and down
  glRotatef(r, 0, 1, 1);     // Rotates anti-clock_t wise along y & z axis

  glPushMatrix(); // Right cone
  glTranslatef(0.7, 1, 0);
  glCallList(ROCKET_CONE);
  glPopMatrix(); // Right cone

  glPushMatrix(); // Right body
  glTranslatef(0.7, -0.2, 0);
  glCallList(ROCKET_BODY);
  glPopMatrix(); // Right body

  glPopMatrix(); // Complete rightSide rocket

  glPushMatrix();             // Complete LeftSide rocket
  glTranslatef(-x1, -y1, z1); // Moves left and down
  glRotatef(-r, 0, 1, 1);     // Rotates clock_t-wise along y & z axis

  glPushMatrix(); // Left cone
  glTranslatef(-0.7, 1, 0);
  glCallList(ROCKET_CONE);
  glPopMatrix(); // Left cone

  glPushMatrix(); // Left body
  glTranslatef(-0.7, -0.2, 0);
  glCallList(ROCKET_BODY);
  glPopMatrix(); // Left body

  glPopMatrix(); // Complete LeftSide rocket
}

// Draw rocket having satellite
void pslv(double x) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -13.0f);
  glPushMatrix(); // Complete rocket containing satellite

  if (x <= 2) {
    glRotatef(x * 30, 1, 0, 0);
    glTranslatef(0, -2 + x, 0);
  }

  else {
    glRotatef(60, 1, 0, 0);
    glTranslatef(0, 0, 0);
  }

  glScaled(0.5, 0.5, 0.5);
  rocket();

  glPopMatrix(); // Complete rocket containing satellite

  glPushMatrix(); // Earth
  glColor3f(0.067, 0.39, 0.7);

  if (x >= 6.5) {
    glTranslatef(0, -23.5, -107.5);
    glRotatef(10 * x, 0, 1, 0);
  } else {
    glTranslatef(0, -15 - x, -10 - 15 * x);
  }

  glutSolidSphere(10, 100, 100); // radius, slices, stacks
  glPopMatrix();                 // Earth

  glFlush();
  glutSwapBuffers();
}

void start() {
  x += 0.01;

  if (x >= 3) {
    x1 += 0.1;
    y1 += 0.1;
    z1 += 0.01;
    r += 3;
  }

  if (x > 5)
    y2 -= 0.1;

  if (x > 5.5)
    z2 += 0.1;

  pslv(x);
}

// void start_animation() {
//   static long timestamp = clock_t();
//   // First frame will have zero delta, but this is just an example.
//   float delta = (float)(clock_t() - timestamp);

//   start(delta);

//   timestamp = clock_t();
// }

void doInit() {
  // Creating display list for side rocket cones
  glNewList(ROCKET_CONE, GL_COMPILE);
  glPushMatrix();
  glColor3f(1, 0.22, 0.22);
  glScaled(1.5, 1, 1.5);
  glRotatef(270, 1, 0, 0);
  glutSolidCone(0.2, 1, 30, 30);
  glPopMatrix();
  glEndList();

  // Creating display lists for side rocket bodies
  glNewList(ROCKET_BODY, GL_COMPILE);
  glPushMatrix();
  glColor3f(1, 1, 1);
  glScaled(0.2, 6.5, 0.2);
  glRotatef(90, 1, 0, 0);
  glutSolidTorus(0.2, 1, 30, 30);
  glPopMatrix();
  glEndList();
  // Background and foreground color
  glClearColor(0.0, 0.0, 0.0, 0);
  glViewport(0, 0, 640, 480);

  // Select the projection matrix and reset it then setup our view perspective
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0f, (GLfloat)640 / (GLfloat)480, 0.1f, 200.0f);

  // Select the modelview matrix, which we alter with rotatef()
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

  stroke_output(-3.0, 2.5, 0.003, 0.005, 0.05, 1, "I     S     R     O");
  stroke_output(-1.3, 1.9, 0.0015, 0.002, 0.002, 1, "Earth observation");

  stroke_output(-4.0, 1.3, 0.0015, 0.002, 0.002, 2, "Rocket     : PSLV-C19");
  stroke_output(0.5, 1.3, 0.0015, 0.002, 0.002, 2,
                "Cost       : ₹4.90 billion");
  stroke_output(-4.0, 0.9, 0.0015, 0.002, 0.002, 2, "Satellite  : RISAT-1");
  stroke_output(0.5, 0.9, 0.0015, 0.002, 0.002, 2, "Mass       : 1,858 kg");
  stroke_output(-4.0, 0.3, 0.0015, 0.002, 0.002, 2,
                "Operator   : Indian Space Research Organisation");
  stroke_output(-4.0, -0.1, 0.0015, 0.002, 0.002, 2,
                "Launch date: 26 April 2012, 00:17 UTC");
  stroke_output(-4.0, -0.5, 0.0015, 0.002, 0.002, 2,
                "Launch site: Satish Dhawan Space Centre, FLP");

  stroke_output(-2.2, -1.2, 0.0015, 0.002, 0.002, 3,
                "Akshay GS       - 1AY18CS008");
  stroke_output(-2.2, -1.6, 0.0015, 0.002, 0.002, 3,
                "D Pruthvi Kumar - 1AY18CS035");

  stroke_output(-4.0, -2.5, 0.0015, 0.002, 0.002, 4,
                "THEME           - AIR SHOW");
  stroke_output(-4.0, -2.9, 0.0015, 0.002, 0.002, 4,
                "PROJECT NAME    - Polar satellite launch simulation");

  GLfloat mat_ambient[] = {0.0f, 1.0f, 2.0f, 1.0f};
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

  GLfloat mat_diffuse[] = {0.0f, 1.5f, .5f, 1.0f};
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  // Diffuse and specular lighting calculations take the light's direction, but
  // not its actual position, into account, and attenuation is disabled.

  GLfloat mat_specular[] = {5.0f, 1.0f, 1.0f, 1.0f};
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

  GLfloat mat_shininess[] = {50.0f};
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  GLfloat lightIntensity[] = {1.7f, 1.7f, 1.7f, 1.0f};
  GLfloat light_position3[] = {
      0.0f, 5.0f, 3.0f,
      0.0f}; // Light position (resembling position of sun here)
  glLightfv(GL_LIGHT0, GL_POSITION, light_position3);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

  glEnable(GL_COLOR_MATERIAL);

  glFlush();
  glutSwapBuffers(); // Performs a buffer swap on the layer in use for the
                     // current window. Specifically, glutSwapBuffers promotes
                     // the contents of the back buffer of the layer in use of
                     // the current window to become the contents of the front
                     // buffer. The contents of the back buffer then become
                     // undefined
}

void menu(int id) {
  switch (id) {
  case 1:
    glutIdleFunc(start);
    break;
  case 2:
    exit(0);
    break;
  }
  glFlush();
  glutSwapBuffers();
  glutPostRedisplay();
}

void key_input(unsigned char key, int x, int y) {
  if (key == 'l' || key == 'L') {
    glutIdleFunc(start);
  }

  if (key == 'q' || key == 'Q') {
    exit(0);
  }
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  glutInitWindowSize(1000, 800);
  glutInitWindowPosition(500, 100);
  glutCreateWindow("Polar Satellite Launch Vehicle-XL");

  glutDisplayFunc(display);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);

  glutKeyboardFunc(key_input);

  glutCreateMenu(menu);
  glutAddMenuEntry("Launch PSLV-C19	or	press L", 1);
  glutAddMenuEntry("Abort mission	or	press Q", 2);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  doInit();
  glutMainLoop();
  return 0;
}