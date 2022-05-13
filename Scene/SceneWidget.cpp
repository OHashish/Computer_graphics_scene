#include <GL/glu.h>
#include <cmath>
#include <QGLWidget>
#include <QTimer>
#include "SceneWidget.h"
#include <QImage>
#include <QDebug>
#include <QDir>

int wallpaperChoice;

// Setting up material properties
typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;


static materialStruct brassMaterials = {
  { 1, 1, 1, 1},
  { 0.78, 0.57, 0.10, 0.25},
  { 0.25, 0.25, 0.1, 0.25},
  20
};

static materialStruct chromeMaterials = {
    {0.25f, 0.25f, 0.25f, 1.0f  },
    {0.4f, 0.4f, 0.4f, 1.0f },
    {0.774597f, 0.774597f, 0.774597f, 1.0f },
    76.8f
};
static materialStruct whiteShinyMaterials = {
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  100.0 
};

static materialStruct wallwhiteShinyMaterials = {
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  50.0
};

static materialStruct customShinyMaterials = {
  { 0.5, 1.0, 1.0, 1.0},
  { 0.5, 1.0, 1.0, 1.0},
  { 0.5, 1.0, 1.0, 1.0},
  100.0
};

static materialStruct customShinyMaterials2 = {
  { 0.2, 0.3, 0.5, 1.0},
  { 0.2, 0.3, 0.5, 1.0},
  { 0.5, 0.1, 0.5, 1.0},
  100.0
};

static materialStruct black = {
  { 0, 0.0, 0.0, 0},
  { 0, 0.0, 0.0, 0},
  { 0, 0.0, 0.0, 0},
  0
};

static materialStruct redPlasticMaterials = {
    { 1.0f,0.0f,0.0f,1.0f },
    { 1.5f,0.0f,0.0f,1.0f},
    {0.7f,0.6f,0.6f,1.0f },
    100.f ,
};




// constructor
SceneWidget::SceneWidget(QWidget *parent):
  QGLWidget(parent),_angle(0.0),_tempfanSpeed(1.0),_tempglobeSpeed(1.0),_temptapSpeed(1.0),rotangle(0),_speed(1),_scale(0),_cx(0),_cy(0),_oscSize(25)
	{ // constructor
    globePic.load("C:/Users/omarh/Desktop/Graphics/CW2/textures/Mercator-projection.ppm");
    markusPic.load("C:/Users/omarh/Desktop/Graphics/CW2/textures/markus.ppm");
    marcPic.load("C:/Users/omarh/Desktop/Graphics/CW2/textures/Marc_Dekamps.ppm");
    floorPic.load("C:/Users/omarh/Desktop/Graphics/CW2/textures/floor.jpg");
    wallPic.load("C:/Users/omarh/Desktop/Graphics/CW2/textures/blackwall2.jpg");
    topPic.load("C:/Users/omarh/Desktop/Graphics/CW2/textures/top.jpg");
    wall2Pic.load("C:/Users/omarh/Desktop/Graphics/CW2/textures/wall2.jpg");
    wall3Pic.load("C:/Users/omarh/Desktop/Graphics/CW2/textures/wall3.jpg");
	} // constructor


// called when OpenGL context is set up
void SceneWidget::initializeGL(){ // initializeGL()
	// set the widget background colour
    glClearColor(0,0, 0, 0);
} // initializeGL()


// called every time the widget is resized
void SceneWidget::resizeGL(int w, int h){ // resizeGL()
	// set the viewport to the entire widget
	glViewport(0, 0, w, h);

    glEnable(GL_LIGHTING); // enable lighting in general
    glEnable(GL_LIGHT0);   // each light source must also be enabled

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    GLfloat light_pos[] = {-9, 0-28, 50+28, 0.};

    GLfloat spot_direction [] = {-1, 0, 0, 0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
   //glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, 90.);
    glLightfv (GL_LIGHT0, GL_SPOT_DIRECTION,spot_direction);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    glFrustum(-15.0, 15.0, -15.0, 15.0, 17, 220);
} // resizeGL()

void SceneWidget::cone(){
  materialStruct* p_front = &chromeMaterials;
  glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

  GLUquadricObj *quadObj = gluNewQuadric();
  gluCylinder(quadObj, 1, 2, 3, 100, 100);
}

void SceneWidget::smallCylinder1(){
  materialStruct* p_front = &chromeMaterials;

  glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

  GLUquadricObj *smallCylinder = gluNewQuadric();
  gluDisk(smallCylinder,0, 1,20,1);
}

void SceneWidget::smallCylinder2(){
  materialStruct* p_front = &chromeMaterials;
  glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

  GLUquadricObj *smallCylinder = gluNewQuadric();
  glTranslatef(0,0,-3);
  gluCylinder(smallCylinder, 0.5, 0.5, 3, 100, 100);
}

void SceneWidget::bigFanPart(){
  glEnable(GL_NORMALIZE);
  materialStruct* p_front = &brassMaterials;
  glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

  GLUquadricObj *beans = gluNewQuadric();
  glTranslatef(0,0,-2);
  gluCylinder(beans, 4, 5, 2, 100, 100);
}

//Hierarchial Model made from cones , cylinders ,2D circles and 3 fan blades;
void SceneWidget::fan(){
    this->cone();
    this->smallCylinder1();
    this->smallCylinder2();
    this->bigFanPart();
    glPushMatrix();
        glScalef(4,4,1);
        this->smallCylinder1();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,0,2);
        glScalef(5,5,1);
        this->smallCylinder1();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,12,1.5);
        glRotatef(0, 0.,0, 1.);
        glScalef(4.1,17.4,1);
        this->fanBlade();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-10.5,-6,1.5);
        glRotatef(120, 0.,0, 1.);
        glScalef(4.1,17.4,1);
        this->fanBlade();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(10.5,-6,1.5);
        glRotatef(240, 0.,0, 1.);
        glScalef(4.1,17.4,1);
        this->fanBlade();
    glPopMatrix();
}

//Update time for all speeds
void SceneWidget::updateTime(){
  _globeSpeed=_globeSpeed+_tempglobeSpeed;
  _fanSpeed=_fanSpeed+_tempfanSpeed;
  _tapSpeed=_tapSpeed+_temptapSpeed;
  _angle += _speed;
  this->repaint();
}	

void SceneWidget::updateSpeed(int speed){
    _speed=speed;
}

void SceneWidget::updateGlobe(int speed){
    _tempglobeSpeed=speed;
}

void SceneWidget::updateFan(int speed){
    _tempfanSpeed=speed;
}

void SceneWidget::updateTap(int speed){
    _temptapSpeed=speed;

}

//Fan blade conves poylgon made from 6 sides with normals
void SceneWidget::fanBlade(){
    materialStruct* p_front = &chromeMaterials;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);
    GLfloat normals[][3] = { {0., 0., 1.},{0., 0., -1.} ,{1., 0. ,0.}
                           , {-1., 0., 0.},{0., 1, 0.},{0., -1., 0.} };

    // BOTTOM
    glNormal3fv(normals[0]);
    glBegin(GL_POLYGON);
     glVertex3f(  0.5, -0.5, 0.5 );
     glVertex3f(  0.5,  0.5, 0.5 );
     glVertex3f( -0.5,  0.5, 0.5 );
     glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();

    // TOP
    glNormal3fv(normals[1]);
    glBegin(GL_POLYGON);
     glVertex3f(  0.5, -0.5, -0.5 );
     glVertex3f(  0.5,  0.5,-0.5 );
     glVertex3f( -0.5,  0.5,- 0.5 );
     glVertex3f( -0.5, -0.5,- 0.5 );
    glEnd();

    //SIDES
    glNormal3fv(normals[2]);
    glBegin(GL_POLYGON);
     glVertex3f( 0.5, -0.5, -0.5 );
     glVertex3f( 0.5,  0.5, -0.5 );
     glVertex3f( 0.5,  0.5,  0.5 );
     glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();

    glNormal3fv(normals[3]);
    glBegin(GL_POLYGON);
     glVertex3f( -0.5, -0.5,  0.5 );
     glVertex3f( -0.5,  0.5,  0.5 );
     glVertex3f( -0.5,  0.5, -0.5 );
     glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();

    // FRONT
    glNormal3fv(normals[4]);
    glBegin(GL_POLYGON);
     glVertex3f(  0.5,  0.5,  0.5 );
     glVertex3f(  0.5,  0.5, -0.5 );
     glVertex3f( -0.5,  0.5, -0.5 );
     glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();

    // BACK
    glNormal3fv(normals[5]);
    glBegin(GL_POLYGON);
     glVertex3f(  0.5, -0.5, -0.5 );
     glVertex3f(  0.5, -0.5,  0.5 );
     glVertex3f( -0.5, -0.5,  0.5 );
     glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();

}

//Room made from 4 walls(objects) ,floor and ceiling.All of these have textures
void SceneWidget::room(){
    glPushMatrix();
        glPushMatrix();
            glTranslatef(0,0,54);
            glScalef(88,78,78);
            this->floor();
            glTranslatef(0,-1,0);
            this->floor();
            glTranslatef(-1,0,0);
            this->floor();
            glTranslatef(0,1,0);
            this->floor();
            glTranslatef(1,0,-2);
            glScalef(1,1,2);
        glPopMatrix();
        glPushMatrix();
            //CEILING
            glPushMatrix();
                glTranslatef(-88,-78,-105);
                glScalef(164,156,159);

                this->wall(topPic,1);
            glPopMatrix();
            //FACE WALL
            glPushMatrix();
                glTranslatef(78,79,55);
                glScalef(164,158,159);
                glRotatef(90, 0.,1., 0.);
                glRotatef(-90, 0.,0., 1.);
                this->wall(wallPic,0);
            glPopMatrix();
            //RIGHT WALL
            glPushMatrix();
                glTranslatef(78,78,55);
                glScalef(166,164,159);
                glRotatef(90, 1.,0., 0.);
                glRotatef(-180, 0.,0., 1.);
                this->wall(wallPic,0);
            glPopMatrix();
            //LEFT WALL
            glPushMatrix();
                glTranslatef(78,-78,55);
                glScalef(166,164,159);
                glRotatef(90, 1.,0., 0.);
                glRotatef(-180, 0.,0., 1.);
                this->wall(wallPic,0);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void SceneWidget::wall(QImage texChoice,int ceil){
    if(wallpaperChoice==1 && ceil==0){
        texChoice=wall2Pic;
    }else if(wallpaperChoice==2 && ceil==0){
        texChoice=wall3Pic;
    }
    QImage picSwap =texChoice.rgbSwapped().mirrored();
    unsigned char* imageData =picSwap.bits();
    int height= picSwap.height();
    int width= picSwap.width();

    materialStruct* p_front = &wallwhiteShinyMaterials;
    GLuint texture_map;
    glEnable(GL_TEXTURE_2D);
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    glGenTextures(1, &texture_map);
    glBindTexture(GL_TEXTURE_2D, texture_map);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    glBegin(GL_POLYGON);
     glTexCoord2f(0, 1);
     glVertex2f(0, 1);
     glTexCoord2f(0, 0);
     glVertex2f(0, 0);
     glTexCoord2f(1, 0);
     glVertex2f(1, 0);
     glTexCoord2f(1,1);
     glVertex2f(1,1);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDeleteTextures(1, &texture_map);
}

//Sphere with Mercator texture wrapped around
void SceneWidget::globe(){
    QImage picSwap =globePic.rgbSwapped().mirrored();
    unsigned char* imageData =picSwap.bits();
    int height= picSwap.height();
    int width= picSwap.width();

    materialStruct* p_front = &whiteShinyMaterials;
    GLuint texture_map;
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    glGenTextures(1, &texture_map);
    glBindTexture(GL_TEXTURE_2D, texture_map);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    GLUquadricObj *globeSphere = gluNewQuadric();
    gluQuadricDrawStyle(globeSphere,GLU_FILL);
    gluQuadricTexture(globeSphere,GL_TRUE);
    gluQuadricNormals(globeSphere,GLU_SMOOTH);
    gluSphere(globeSphere,1,32,16);

    glDisable(GL_NORMALIZE);
    glDisable(GL_TEXTURE_2D);
    glDeleteTextures(1, &texture_map);

}

void SceneWidget::floor(){
   QImage picSwap =floorPic.rgbSwapped().mirrored();
   unsigned char* imageData =picSwap.bits();
   int height= picSwap.height();
   int width= picSwap.width();

   GLuint texture_map;
   glEnable(GL_TEXTURE_2D);

   glGenTextures(1, &texture_map);
   glBindTexture(GL_TEXTURE_2D, texture_map);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

   glBegin(GL_POLYGON);
    glTexCoord2f(0, 1);
    glVertex2f(0, 1);
    glTexCoord2f(0, 0);
    glVertex2f(0, 0);
    glTexCoord2f(1, 0);
    glVertex2f(1, 0);
    glTexCoord2f(1,1);
    glVertex2f(1,1);
   glEnd();

   glDisable(GL_TEXTURE_2D);
   glDeleteTextures(1, &texture_map);
}

void SceneWidget::markus(){
    QImage picSwap =markusPic.rgbSwapped().mirrored();
    unsigned char* imageData =picSwap.bits();
    int height= picSwap.height();
    int width= picSwap.width();

    GLuint texture_map;
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture_map);
    glBindTexture(GL_TEXTURE_2D, texture_map);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    glBegin(GL_POLYGON);
     glTexCoord2f(0, 1);
     glVertex2f(0, 1);
     glTexCoord2f(0, 0);
     glVertex2f(0, 0);
     glTexCoord2f(1, 0);
     glVertex2f(1, 0);
     glTexCoord2f(1,1);
     glVertex2f(1,1);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_2D);
    glDeleteTextures(1, &texture_map);
}

void SceneWidget::marcDekamps(){
    glEnable(GL_NORMALIZE);
    QImage picSwap =marcPic.rgbSwapped().mirrored();
    unsigned char* imageData =picSwap.bits();
    int height= picSwap.height();
    int width= picSwap.width();

    GLuint texture_map;
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);

    glGenTextures(1, &texture_map);
    glBindTexture(GL_TEXTURE_2D, texture_map);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    glBegin(GL_POLYGON);
     glTexCoord2f(0, 1);
     glVertex2f(0, 1);
     glTexCoord2f(0, 0);
     glVertex2f(0, 0);
     glTexCoord2f(1, 0);
     glVertex2f(1, 0);
     glTexCoord2f(1,1);
     glVertex2f(1,1);
    glEnd();

    glDisable(GL_NORMALIZE);
    glDisable(GL_TEXTURE_2D);
    glDeleteTextures(1, &texture_map);
}

//Finger made from sphere and cylinders that takes in angle to bend the finger
void SceneWidget::finger(int fingerAngle){
    materialStruct* p_front = &whiteShinyMaterials;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    glScalef(10,10,10);
    this->cylinderBodyPart();
    this->fingerJoint();

    glRotatef(fingerAngle, 1.,0., 0.);
    glTranslatef(0,0,-3);
    this->cylinderBodyPart();
    this->fingerJoint();

    glRotatef(fingerAngle, 1.,0., 0.);
    glTranslatef(0,0,-3);
    this->cylinderBodyPart();
    this->fingerJoint();
}

//Object used to cover openings in polygons
void SceneWidget::circleCover(){
    GLUquadricObj *quadObj2 = gluNewQuadric();
    gluDisk(quadObj2, 0, 2, 50, 1);
}

//Tapping hand that is made from 4 finger objects ,palm (made from a flattened cone)and 1 thumb object
//Uses Sin to animate tapping fingers
void SceneWidget::hand(){
    glPushMatrix();
        glRotatef(90,0,1,0);
        glRotatef(24,1,0,0);
        glTranslatef(-52,1,-21);
        this->thumb(5);
    glPopMatrix();
    glPushMatrix();
        double lowangle = 30*sin(0.2*_tapSpeed) + 30;
        this->finger(lowangle);
    glPopMatrix();
    glPushMatrix();
        double lowangle2 = 30*sin(0.2*_tapSpeed+30) + 30;
        glTranslatef(22,1,1);
        this->finger(lowangle2);
    glPopMatrix();
    glPushMatrix();
        double lowangle3 = 30*sin(0.2*_tapSpeed+60) + 30;
        glTranslatef(43,1,1);
        this->finger(lowangle3);
    glPopMatrix();
    glPushMatrix();
        double lowangle4 = 30*sin(0.2*_tapSpeed+90) + 30;
        glTranslatef(66,1,1);
        this->finger(lowangle4);
    glPopMatrix();
}

void SceneWidget::oscSize(int osc){
    _oscSize=osc;
    this->repaint();
}

//Another hand made from 4 finger objects , palm (made from cube polygon) and 1 thumb object
void SceneWidget::pinchingHand(){
        glPushMatrix();
        glTranslatef(-70,-16,2);
        glRotatef(2, 1.,0., 0.);

        glRotatef(100, 0.,1., 0.);
//        double lowangle = 25*sin(0.2*_angle) -25 ;
        double lowangle = _oscSize*sin(0.2*_angle) -25 ;
        glRotatef(-90+lowangle, 0.,0, 1.);

        glScalef(0.15,0.15,0.15);
        glPushMatrix();
            glPushMatrix();
            glTranslatef(8,-29,26);
                glRotatef(-34,1,0,0);
                glRotatef(-11,0,1,0);
                glScalef(1,1,1.5);
                this->thumb(10);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0,-16,0);
                glRotatef(-44,1,0,0);
                //double lowangle = 30*sin(0.2*_angle) + 30;
                this->finger(-10);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0,-16,0);
                glRotatef(-44,1,0,0);
                glTranslatef(22,1,1);
                this->finger(-10);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(43,1,1);
                this->finger(-10);
            glPopMatrix();
            glPushMatrix();
            glTranslatef(11,7,15);
                glRotatef(24,1,0,0);
                glScalef(0.8,0.8, 0.8);
                glTranslatef(66,1,1);
                this->finger(-10);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(32,-1,95);
                glRotatef(180,1,0,0);
                glScalef(26,10.5,26);
                GLUquadricObj *quadObj = gluNewQuadric();
                gluCylinder(quadObj, 1, 2, 3, 100, 100);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(32,-1,17);
                glScalef(26,10.5,1);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(78,-213,-44);
                glRotatef(-80, 1.,0., 0.);
                glRotatef(-21, 0.,1., 0.);
                glScalef(2,2,2);
                this->littleString();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(95,-253,-53);
                glRotatef(-90, 1.,0., 0.);
                glRotatef(_globeSpeed, 0.,0., 1.);
                glScalef(52+_cy,52+_cy,52+_cy);
                this->globe();
            glPopMatrix();
        glPopMatrix();
     glPopMatrix();
}

//Basic cube polygon
void SceneWidget::feet(){
    materialStruct* p_front = &black;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

     glBegin(GL_POLYGON);
      glVertex3f(1.0, -1, 0.0);
      glVertex3f(-1, -1, 0.0);
      glVertex3f(-1.0, 1, 0.0);
      glVertex3f(1.0,1, 0.0);
     glEnd();

     glBegin(GL_POLYGON);
      glVertex3f(1, -1, 1.0);
      glVertex3f(-1, -1, 1.0);
      glVertex3f(-1.0, 1, 1.0);
      glVertex3f(1.0,1, 1.0);
     glEnd();

     glBegin(GL_POLYGON);
      glVertex3f(1.0, -1.0, 0.0);
      glVertex3f(1, -1.0, 1.0);
      glVertex3f(1.0,1.0, 1.0);
      glVertex3f(1, 1.0, 0);
     glEnd();
     glBegin(GL_POLYGON);
      glVertex3f(-1.0, -1, 0.0);
      glVertex3f(-1, -1, 1.0);
      glVertex3f(-1.0, 1, 1.0);
      glVertex3f(-1.0,1, 0.0);
     glEnd();

     glBegin(GL_POLYGON);
      glVertex3f(1.0, 1, 0.0);
      glVertex3f(1, 1, 1.0);
      glVertex3f(-1.0, 1, 1.0);
      glVertex3f(-1.0,1, 0.0);
     glEnd();

     glBegin(GL_POLYGON);
      glVertex3f(-1.0, -1, 0.0);
      glVertex3f(-1, -1, 1.0);
      glVertex3f(1.0, -1, 1.0);
      glVertex3f(1.0,-1, 0.0);
     glEnd();
}

//object made from spheres and cylinders to make a thumb
void SceneWidget::thumb(int fingerAngle){
    materialStruct* p_front = &whiteShinyMaterials;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    glScalef(10,10,10);
    this->cylinderBodyPart();
    this->fingerJoint();
    glRotatef(fingerAngle, 1.,0., 0.);
    glTranslatef(0,0,-3);
    this->cylinderBodyPart();
    this->fingerJoint();
}

//Spheres use to make joints in thumb and finger objects
void SceneWidget::fingerJoint(){
    GLUquadricObj *circleto3 = gluNewQuadric();
    gluSphere(circleto3, 1, 20, 20);

}

void SceneWidget::palm(){
    materialStruct* p_front = &whiteShinyMaterials;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    glScalef(43,28 ,32);
    glRotatef(-90,1,0,0);
    glTranslatef(0.75,-1.5,-0.5);

    glBegin(GL_POLYGON);
     glVertex3f(1.0, -1, 0.0);
     glVertex3f(-1, -1, 0.0);
     glVertex3f(-1.0, 1, 0.0);
     glVertex3f(1.0,1, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
     glVertex3f(1, -1, 1.0);
     glVertex3f(-1, -1, 1.0);
     glVertex3f(-1.0, 1, 1.0);
     glVertex3f(1.0,1, 1.0);
    glEnd();

    glBegin(GL_POLYGON);
     glVertex3f(1, -1.0, 0.0);
     glVertex3f(1, -1.0, 1.0);
     glVertex3f(1.0,1.0, 1.0);
     glVertex3f(1.0, 1.0, 0);
    glEnd();

    glBegin(GL_POLYGON);
     glVertex3f(-1.0, -1, 0.0);
     glVertex3f(-1, -1, 1.0);
     glVertex3f(-1.0, 1, 1.0);
     glVertex3f(-1.0,1, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
     glVertex3f(1.0, 1, 0.0);
     glVertex3f(1, 1, 1.0);
     glVertex3f(-1.0, 1, 1.0);
     glVertex3f(-1.0,1, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
     glVertex3f(-1.0, -1, 0.0);
     glVertex3f(-1, -1, 1.0);
     glVertex3f(1.0, -1, 1.0);
     glVertex3f(1,-1, 0.0);
    glEnd();
}

//Small radius cone used to make string that is attached to globe
void SceneWidget::littleString(){
    glScalef(20,20,20);
    GLUquadricObj *smallCylinder = gluNewQuadric();
    gluCylinder(smallCylinder, 0.05, 0.05, 5, 20, 20);
}

//Spherical body part to make joints and head of body figure
void SceneWidget::circularBodyPart(){
    materialStruct* p_front = &customShinyMaterials2;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    GLUquadricObj *bodySphere = gluNewQuadric();
    gluSphere(bodySphere,1,32,16);
}

//Cylinderical body part to make joints and head of body figure
void SceneWidget::cylinderBodyPart(){
    materialStruct* p_front = &customShinyMaterials;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    GLUquadricObj *bodyCylinder = gluNewQuadric();
    gluCylinder(bodyCylinder, 1, 1, 3, 20, 20);
}

//Main figure body made from both hand hierarchical object  ,globe and feet
void SceneWidget::figureBody(){
    materialStruct* p_front = &customShinyMaterials;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    glPushMatrix();
        glPushMatrix();
            glTranslatef(0,0,-2-_cx);
            glScalef(12,12,12);
            this->circularBodyPart();
            glPopMatrix();
            //NECK
            glPushMatrix();
                glScalef(7,7,5+_cx);
                this->cylinderBodyPart();
            glPopMatrix();
        glPopMatrix();
        //SHOULDERS
        glPushMatrix();

            glScalef(7,7,7);
            glTranslatef(0,3,2);
            this->circularBodyPart();
        glPopMatrix();
        glPushMatrix();
            glScalef(7,7,7);
            glTranslatef(0,-3,2);
            this->circularBodyPart();
        glPopMatrix();
        //BODY
        glPushMatrix();
            glScalef(15,15,15);
            glTranslatef(0,0,1);
            this->cylinderBodyPart();
            GLUquadricObj *smallCylinder = gluNewQuadric();
            gluDisk(smallCylinder,0, 1,20,1);
        glPopMatrix();
        //UPPER ARMS
        glPushMatrix();
            glRotatef(-105,0,1,0);
            glTranslatef(16,-21,-2);
            glScalef(6,6,9);
            this->cylinderBodyPart();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,21,17);
            glRotatef(-21,0,1,0);
            glRotatef(-21,1,0,0);
            glScalef(6,6,9);
            this->cylinderBodyPart();
        glPopMatrix();
        //LOWER ARMS
        glPushMatrix();
        glRotatef(-105,0,1,0);
            glTranslatef(16,-21,28);
            glScalef(6,6,9);
            this->cylinderBodyPart();
            glTranslatef(0,0,3);
            gluDisk(smallCylinder,0, 1,20,1);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-10,32,47);
            glRotatef(70,1,0,0);
            glRotatef(-73,0,1,0);
            glScalef(6,6,9);
            this->cylinderBodyPart();
        glPopMatrix();
        //ELBOWS
        glPushMatrix();
        glRotatef(-105,0,1,0);
            glTranslatef(16,-21,25);
            glScalef(7,7,7);
            this->circularBodyPart();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-10,32,44);
            glRotatef(70,1,0,0);
            glRotatef(-73,0,1,0);
            glScalef(7,7,7);
            this->circularBodyPart();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-45,21,46);
            glRotatef(10,1,0,0);
            glRotatef(63,0,1,0);
            glRotatef(77,0,0,1);
            glScalef(0.15,0.15,0.15);
            this->hand();
            this->palm();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(16,0,66);
            glRotatef(-90, 0.,1., 0.);
            //THIGH JOINTS
            glPushMatrix();
                glTranslatef(0,-7,19);
                glScalef(7,7,7);
                this->circularBodyPart();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0,7,19);
                glScalef(7,7,7);
                this->circularBodyPart();
            glPopMatrix();
            //UPPER LEGS
            glPushMatrix();
                glTranslatef(0,-7,17);
                glScalef(6,6,9);
                this->cylinderBodyPart();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0,7,17);
                glScalef(6,6,9);
                this->cylinderBodyPart();
            glPopMatrix();
            glPushMatrix();
                //LOWER LEGS and FEET
                glRotatef(90,0,1,0);
                glTranslatef(-44,0,-41);
                glPushMatrix();
                    glTranslatef(0,-7,47);
                    glScalef(6,6,9);
                    this->cylinderBodyPart();
                    glTranslatef(0,0,3);
                    this->circularBodyPart();
                    glTranslatef(-0.65,0,0);
                    glScalef(1.7,1,1);
                    this->feet();
                glPopMatrix();
                glPushMatrix();
                    glTranslatef(0,7,47);
                    glScalef(6,6,9);
                    this->cylinderBodyPart();
                    glTranslatef(0,0,3);
                    this->circularBodyPart();
                    glTranslatef(-0.65,0,0);
                    glScalef(1.7,1,1);
                    this->feet();
                glPopMatrix();
                //KNEES
                glPushMatrix();
                    glTranslatef(0,-7,44);
                    glScalef(7,7,7);
                    this->circularBodyPart();
                glPopMatrix();
                glPushMatrix();
                    glTranslatef(0,7,44);
                    glScalef(7,7,7);
                    this->circularBodyPart();
                glPopMatrix();
            glPopMatrix();
    glPopMatrix();
    this->pinchingHand();

}


void SceneWidget::chair(){
    //SEAT
    glPushMatrix();
        glTranslatef(-5,0,73);
        glScalef(16,20,6);
        this->feet();
    glPopMatrix();
    //4 LEGS
    glPushMatrix();
        glTranslatef(9,-17,77);
        glScalef(2,2,31);
        this->feet();
        glTranslatef(-13,0,0);
        this->feet();
        glTranslatef(-1,17,0);
        this->feet();
        glTranslatef(14,0,0);
        this->feet();
    glPopMatrix();
}

//Table made from 2 different sized cylinders and 2D circles
void SceneWidget::furniture(){
    glEnable(GL_NORMALIZE);
    materialStruct* p_front = &redPlasticMaterials;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    glPushMatrix();
       glScalef(23,23,23);;
       this->circleCover();
       glTranslatef(0,0,0.1);
       this->circleCover();
    glPopMatrix();
    glPushMatrix();
       glTranslatef(0,0,45);
       glScalef(6,6,6);
       this->circleCover();
    glPopMatrix();
    glPushMatrix();
        glScalef(46,46,1);
        GLUquadricObj *quadObj = gluNewQuadric();
        gluCylinder(quadObj, 1, 1, 3, 100, 100);
    glPopMatrix();
    glPushMatrix();
        glScalef(1,1,15);
        gluCylinder(quadObj, 1, 1, 3, 100, 100);
    glPopMatrix();
}

void SceneWidget::rotasion(int viewAngle){
    rotangle=viewAngle;
}

void SceneWidget::yrotasion(int viewAngle){
    yrotangle=viewAngle;
}

void SceneWidget::updateWallpaper(int beanus){
    wallpaperChoice=beanus;
    this->repaint();
}

void SceneWidget::updateScale(double sc){
    _scale=sc;
    this->repaint();
}

void SceneWidget::updateNeckSize(double cx){
    _cx=cx;
    this->repaint();
}

void SceneWidget::updateGlobeSize(double cy){
    _cy=cy;
    this->repaint();
}

// called every time the widget needs painting
//Contains all main hierarchical objects with rotations matrices to animate
//spinning and moving in circles
//Contains texture and their translations
void SceneWidget::paintGL()
    { // paintGL()
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      	glMatrixMode(GL_MODELVIEW);
       	glEnable(GL_DEPTH_TEST);
        glEnable(GL_NORMALIZE);
        glLoadIdentity();
        gluLookAt(55.9,0,76,55,0.0,75, 0.0,0.0,1.0);


        glScalef(0.55+(_scale/100),0.55+(_scale/100),0.55+(_scale/100));
        glRotatef(135+yrotangle, 0.,1., 0.);
        glRotatef(rotangle, 0.,0., 1.);
        this->room();
        glPushMatrix();
            glTranslatef(0,0,-96);
            glRotatef(_fanSpeed, 0.,0, 1.);
            glRotatef(180, 1.,0., 0.);
            glScalef(2,2,2);
            this->fan();
        glPopMatrix();
        glPushMatrix();
            glPushMatrix();
                glTranslatef(-26,0,0);
                glScalef(0.5,0.5,0.5);
                glPushMatrix();
                    glTranslatef(0,0,53);
                    glScalef(1.2,1.2,1.2);
                    this->furniture();
                glPopMatrix();
            glPopMatrix();
            glTranslatef(-26,0,0);
            glRotatef(-_angle, 0.,0., 1);
            glTranslatef(36,0,0);
            glScalef(0.5,0.5,0.5);
            this->figureBody();
            this->chair();
        glPopMatrix();
        glPushMatrix();
            glPushMatrix();
                glTranslatef(77,19,-8);
                glScalef(49,49,49);
                glRotatef(-90,1,0,0);
                glRotatef(90,0,1,0);
                this->marcDekamps();
            glPopMatrix();
            glTranslatef(-29,-1,0);
            glPushMatrix();
                glTranslatef(-4,-18,26);
                glScalef(13,13,13);
                this->markus();
                glTranslatef(-1,2,0);
                glRotatef(-90,0,0,1);
                this->markus();
                glTranslatef(-1,2,0);
                glRotatef(-90,0,0,1);
                this->markus();
                glTranslatef(-1,2,0);
                glRotatef(-90,0,0,1);
                this->markus();
            glPopMatrix();
        glPopMatrix();
        glLoadIdentity();
     // flush to screen
        glFlush();
} // paintGL()
