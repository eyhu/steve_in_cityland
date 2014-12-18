#include "Window.h"

using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

// Scene Graph-related
static MatrixTransform* rtWorld;
static MatrixTransform* objectWorld;
static MatrixTransform* scale;
static MatrixTransform* translate;
static MatrixTransform* rotation;
static MatrixTransform* movement;
static City* city;
//static Character* person;
static SkyBox* box;

// Trackball related
static int xMouse;
static int yMouse;
static bool leftClick = false;
static bool rightClick = false;
static Vector3 lastPoint;


int lightCounter = 0;
static Light spot;
static Light point;
bool toggleSpot = false;
bool togglePoint = true;


float ambientP[] = {1.0, 1.0, 1.0, 1.0};
//---
float diffuseP[] = {0.3, 0.8, 0.3, 1.0};
float diffuseS[] = {0.7, 0.2, 0.7, 1.0};
//---
float specularS[] = {1.0, 1.0, 1.0, 1.0};
//---
float positionP[] = {0.0, 20.0, 0.0, 1.0};
float positionS[] = {-10.0, 0.0, 5.0, 1.0};
//---
float direction[] = {1.0, 0.0, -1.0};

float cutOff = 10.0;
float expo = 1.0;

//Material related
Material shiner;
Material diffuser;
Material extra;

bool toggleMat = false;

float no_mat[] = {0.0, 0.0, 0.0, 1.0};
//---
float mat_ambient[] = {0.7, 0.7, 0.7, 1.0};
float mat_ambient_color[] = { 0.2, 0.8, 0.8, 1.0 };
//---
float mat_diffuse[] = {0.1, 0.5, 0.8, 1.0};
float mat_specular[] ={1.0, 1.0, 1.0, 1.0};
//---
float no_shine = 0.0;
float low_shine = 5.0;
float high_shine = 128;
//---
float mat_emission[] = {0.2, 0.2, 0.3, 0.0};


// Shader related
//Shader* shader;
bool toggleShader = false;

//static double time_wave = 0.0;


//RANDOM RELATED
unsigned int seedT = 1590955;
unsigned int seedC = 12201184;
unsigned int seedE = 1891933;


//TONY'S CRAP ---------------------------------------------------------------
//Flags
int degree = 0;
int t = 0;
bool forw = true;
bool cam = false;
bool altCam = false;
bool back = false;
bool automatic = true;
bool walk = false;

//Directions
Vector4 ahead = Vector4(0, 0, -1, 0);
Vector4 side = Vector4(-1, 0, 0, 0);
//Camera
Vector3 e = Vector3(0, 7, 10);
Vector3 d = Vector3(0, 7, 9);
Vector3 up = Vector3(0, 1, 0);

//Belz Camera
Vector3 belzD = Vector3(0, 0, 0);
Vector3 belzUp = Vector3(0, 1, 0);
//Patch settings
Vector4 endV = Vector4(-100, 50, -100, 0);
Vector4 inter1 = Vector4(-50, 100, -50, 0);
Vector4 inter2 = Vector4(50, 100, 50, 0);
Vector4 initial = Vector4(100, 50, 100, 0);
BezierCurve bCurve;

//Random Variables
Camera belzCamera;
Camera camera;
Projection projection;
Viewport viewport;
Vector3 mouse;
Object cameraObject;
Object person;
Vector3 points[100];

//Textures
GLuint head[6];
GLuint body[6];
GLuint leg[6];
GLuint arm[6];

//Character parts
Group character;

//Controller
MatrixTransform control;

//Head
Cube headCube;
MatrixTransform headTranslation;
MatrixTransform headRotation;
MatrixTransform headScaling;

//Body
Cube bodyCube;
MatrixTransform bodyTranslation;
MatrixTransform bodyRotation;
MatrixTransform bodyScaling;

//Arms
Cube armCube;
MatrixTransform leftArmTranslation;
MatrixTransform rightArmTranslation;
MatrixTransform leftArmRotation;
MatrixTransform rightArmRotation;
MatrixTransform leftArmScaling;
MatrixTransform rightArmScaling;

//Legs
Cube legCube;
MatrixTransform leftLegTranslation;
MatrixTransform rightLegTranslation;
MatrixTransform leftLegRotation;
MatrixTransform rightLegRotation;
MatrixTransform leftLegScaling;
MatrixTransform rightLegScaling;

//Bounding Box
Box bbox;
MatrixTransform bBoxTranslation;
MatrixTransform bBoxRotation;
MatrixTransform bBoxScaling;

//Cindy's Stuff---------------------------------------
ParticleSys rain;


//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::loadData()
{
  // Seeds Random
  srand(seedE);
  //Globals::sys.init();
  
  // Light-related stuff -------------------------------------------- ==
  /*glViewport(0, 0, width, height);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // set perspective projection viewing frustum
  gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0);
  // move camera back 20 units so that it looks at the origin
  // (or else it's in the origin)
  //glTranslatef(0, -2, 0);
  glTranslatef(0, -10, -25);*/
  
  Matrix4 ident;
  ident.identity();
  
  setMatrix(ident);
  
  // Sets up spotlight
  spot = Light();
  spot.setSpotlight(true);
  spot.setNum(lightCounter);
  spot.setAmbient(ambientP);
  spot.setSpecular(specularS);
  spot.setDiffuse(diffuseS);
  spot.setPosition(positionS);
  spot.setSpotCutoff(cutOff);
  spot.setSpotExponent(expo);
  spot.setSpotDirection(direction);
  lightCounter++;
  
  // sets up point light
  point = Light();
  point.setNum(lightCounter);
  point.setDiffuse(diffuseP);
  point.setPosition(positionP);
  lightCounter++;
  
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  
  
  // sets up more diffuse material
  diffuser = Material();
  diffuser.setAmbient(no_mat);
  diffuser.setDiffuse(mat_diffuse);
  diffuser.setSpecular(no_mat);
  diffuser.setShine(no_shine);
  diffuser.setEmmission(no_mat);
  
  // sets up shinier material
  shiner = Material();
  shiner.setAmbient(mat_ambient);
  shiner.setDiffuse(no_mat);
  shiner.setSpecular(mat_specular);
  shiner.setShine(high_shine);
  shiner.setEmmission(no_mat);
  
  // IDK BUT IT'S FUN
  extra = Material();
  extra.setAmbient(mat_ambient_color);
  extra.setDiffuse(mat_diffuse);
  extra.setSpecular(mat_specular);
  extra.setShine(low_shine);
  extra.setEmmission(mat_emission);
  
  
  // Tony's Crap -------------------------------------------------------- ==
  camera.set(e, d, up);
  cameraObject.set(initial.get(0),initial.get(1),initial.get(2));
  bCurve.setPoints(initial, inter1, inter2, endV);
  for (int i = 0; i < 100; i++) {
    points[i] = bCurve.evalBCurve((double)i / 100);
  }
  belzCamera.set(points[0], belzD, belzUp);
  
  // Loads Texture for character
  loadTexture();
  // makes character
  makeCharacter();
  // =============
  
  
  makeModel();

  rain.init(city->getWinX(city->getMap()), 50.0, city->getWinZ(city->getMap()));
  
}


//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
  animate();
  
  //Globals::sys.wake();
  rain.wake();
  //Globals::sys.update();
  rain.update();
  displayCallback();         // call display routine to show the cube
/*  patch->wave(4.0, time_wave);
  time_wave += 0.01;*/
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
  cerr << "Window::reshapeCallback called" << endl;
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  viewport.set(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // set perspective projection viewing frustum
  gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0);
  // move camera back 20 units so that it looks at the origin
  // (or else it's in the origin)
  projection.set(60.0, double(width) / double(height), 1.0, 1000.0);
  glMatrixMode(GL_MODELVIEW);
  
  
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when
// glutPostRedisplay() was called.
void Window::displayCallback()
{
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  //glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
  //glLoadIdentity();
  //clock_t begin = clock();
  
  Matrix4 glmatrix;
  
  setMatrix(glmatrix);
  
  // =============
  glColor3f(0, 0, 1);
  //Setting moving camera
  if (cam) {
    if (t == 99) {
      back = true;
    }
    if (t == 0) {
      back = false;
    }
    Vector3 upd = belzCamera.upd;
    Vector3 ex = Vector3(0,0,0);
    belzCamera.set(points[t], ex, upd);
  }
  if (altCam) {
    glmatrix = belzCamera.getInverse();
  }
  else {
    glmatrix = camera.getInverse();
  }
  
  
  // HERE I AM
  glColor3f(1.0, 1.0, 1.0);
  setMatrix(glmatrix);
  rtWorld->draw(glmatrix);
  rain.render();
  
  
  //Drawing Bezier Curve
  glLineWidth(3.0);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < 99; i++) {
    Vector3 current = points[i];
    Vector3 next = points[i + 1];
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(current.getX(), current.getY(), current.getZ());
    glVertex3f(next.getX(), next.getY(), next.getZ());
  }
  glEnd();
  
  //Drawing Head
  Matrix4 temp;
  temp = glmatrix;
  control.setMatrix(person.getMatrix());
  double deg = 0;
  deg = abs(degree);
  if( deg > 12 ) {
    bbox.setT(((double)deg - 12.0)/3.0);
  }
  else {
    bbox.setT(0.0);
  }
  character.draw(temp);
  
  //Drawing Camera
  setMatrix(glmatrix, cameraObject.getMatrix());
  glColor3f(0, 1, 1);
  glutSolidSphere(.5,100,100);
  if (cam) {
    Vector3 current;
    current = points[t];
    cameraObject.set(current.getX(), current.getY(), current.getZ());
    if (automatic) {
      if (!back) {
        t++;
      }
      else {
        t--;
      }
    }
  }

  
  // =============
  
  /*clock_t end = clock();
  double sec = double (end - begin) / CLOCKS_PER_SEC;
  double fps = 1/ sec;
  cerr << "Frames per second: " << fps << endl;*/

  
  glFlush();
  glutSwapBuffers();
}


//----------------------------------------------------------------------------
// Callback method called by GLUT when users press specific keys on the keyboard
void Window::keyboardCallback(unsigned char key, int x, int y) {
  glMatrixMode(GL_PROJECTION);
  Matrix4 temp;
    switch (key) {
      case 'w' : {
        camera.moveForward(1);
        break;
      }
      case 'a' : {
        camera.moveLeft(1);
        break;
      }
      case 's' : {
        camera.moveBackward(1);
        break;
      }
      case 'd' : {
        camera.moveRight(1);
        break;
      }
      case 'b': {
        city->toggleBound();
        if( city->isBound() ) {
          bbox.setCenter(person.getCenter());
          bbox.setT(0.0);
          person.getCenter().print("CENTER");
          control.addChild(&bbox);
        } else {
          control.removeChild("bound");
          bbox.setT(0.0);
          bbox.setCenter(person.getCenter());
        }
        break;
      }
      case 'C': {
        srand(seedC);
        city->reset();
        t = 0;
        cameraObject.set(initial.get(0), initial.get(1), initial.get(2));
        belzCamera.set(points[0], belzD, belzUp);
        person.reset();
        camera.set(e, d, up);
        ahead = Vector4(0, 0, -1, 0);
        side = Vector4(-1, 0, 0, 0);
        break;
      }
      case 'q': {
        camera.moveDown(1);
        break;
      }
      // Shader
      case 'e': {
        camera.moveUp(1);
        break;
      }
      case 'E': {
        srand(seedE);
        city->reset();
        t = 0;
        cameraObject.set(initial.get(0), initial.get(1), initial.get(2));
        belzCamera.set(points[0], belzD, belzUp);
        person.reset();
        camera.set(e, d, up);
        ahead = Vector4(0, 0, -1, 0);
        side = Vector4(-1, 0, 0, 0);
        break;
      }
        // SHRINKS THE MODEL
      case 'm': {
        Matrix4 scaMat = Matrix4();
        scaMat.identity();
        scaMat.makeScale(0.9, 0.9, 0.9);
        
        Matrix4 temp = objectWorld->getMatrix();
        temp = scaMat * temp;
        objectWorld->setMatrix(temp);
        break;
      }
        // ENLARGENS THE MODEL
      case 'M': {
        Matrix4 scaMat = Matrix4();
        scaMat.identity();
        scaMat.makeScale(1.1, 1.1, 1.1);
        
        Matrix4 temp = objectWorld->getMatrix();
        temp = scaMat * temp;
        objectWorld->setMatrix(temp);
        break;
      }
      case 'o': {
        altCam = !altCam;
        break;
      }
      case 'p': {
        cam = !cam;
        break;
      }
      case 'r': {
        city->reset();
        t = 0;
        cameraObject.set(initial.get(0), initial.get(1), initial.get(2));
        belzCamera.set(points[0], belzD, belzUp);
        person.reset();
        camera.set(e, d, up);
        ahead = Vector4(0, 0, -1, 0);
        side = Vector4(-1, 0, 0, 0);
        break;
      }
      
      case 'T': {
        srand(seedT);
        city->reset();
        t = 0;
        cameraObject.set(initial.get(0), initial.get(1), initial.get(2));
        belzCamera.set(points[0], belzD, belzUp);
        person.reset();
        camera.set(e, d, up);
        ahead = Vector4(0, 0, -1, 0);
        side = Vector4(-1, 0, 0, 0);
        break;
      }
      // ROTATE ABOUT THE X-AXIS COUNTERCLOCKWISE
      case 'X': {
        Matrix4 rotMat = Matrix4();
         rotMat.identity();
         rotMat.makeRotateX(1.0);
        
          Matrix4 temp = rotation->getMatrix();
          temp = rotMat * temp;
          rotation->setMatrix(temp);
        break;
      }
      // ROTATE ABOUT THE X-AXIS CLOCKWISE
      case 'x': {
        Matrix4 rotMat = Matrix4();
         rotMat.identity();
         rotMat.makeRotateX(-1.0);
        
          Matrix4 temp = rotation->getMatrix();
          temp = rotMat * temp;
          rotation->setMatrix(temp);
        break;
      }
      // ROTATE ABOUT THE Y-AXIS COUNTERCLOCKWISE
      case 'Y': {
        Matrix4 rotMat = Matrix4();
        rotMat.identity();
        rotMat.makeRotateY(1.0);
        
        Matrix4 temp = rotation->getMatrix();
        temp = rotMat * temp;
        rotation->setMatrix(temp);
        break;
      }
      // ROTATE ABOUT THE Y-AXIS CLOCKWISE
      case 'y': {
        Matrix4 rotMat = Matrix4();
        rotMat.identity();
        rotMat.makeRotateY(-1.0);
        
        Matrix4 temp = rotation->getMatrix();
        temp = rotMat * temp;
        rotation->setMatrix(temp);
        break;
      }
      // ROTATE ABOUT THE Z-AXIS COUNTERCLOCKWISE
      case 'Z': {
        Matrix4 rotMat = Matrix4();
        rotMat.identity();
        rotMat.makeRotateZ(1.0);
        
        Matrix4 temp = rotation->getMatrix();
        temp = rotMat * temp;
        rotation->setMatrix(temp);
        break;
      }
      // ROTATE ABOUT THE Z-AXIS CLOCKWISE
      case 'z': {
        Matrix4 rotMat = Matrix4();
        rotMat.identity();
        rotMat.makeRotateZ(-1.0);
        
        Matrix4 temp = rotation->getMatrix();
        temp = rotMat * temp;
        rotation->setMatrix(temp);
        break;
      }
      // SWITCHES TO BASE MAP
      case '0': {
        city->setMap(0);
        t = 0;
        cameraObject.set(initial.get(0), initial.get(1), initial.get(2));
        belzCamera.set(points[0], belzD, belzUp);
        person.reset();
        camera.set(e, d, up);
        ahead = Vector4(0, 0, -1, 0);
        side = Vector4(-1, 0, 0, 0);
        rain.relocate(city->getWinX(0), 50.0, city->getWinZ(0));
        break;
      }
        // SWITCHES TO MAP 1
      case '1': {
        city->setMap(1);
        t = 0;
        cameraObject.set(initial.get(0), initial.get(1), initial.get(2));
        belzCamera.set(points[0], belzD, belzUp);
        person.reset();
        camera.set(e, d, up);
        ahead = Vector4(0, 0, -1, 0);
        side = Vector4(-1, 0, 0, 0);
        rain.relocate(city->getWinX(1), 50.0, city->getWinZ(1));
        break;
      }
        // SWITCHES TO MAP 2
      case '2': {
        city->setMap(2);
        t = 0;
        cameraObject.set(initial.get(0), initial.get(1), initial.get(2));
        belzCamera.set(points[0], belzD, belzUp);
        person.reset();
        camera.set(e, d, up);
        ahead = Vector4(0, 0, -1, 0);
        side = Vector4(-1, 0, 0, 0);
        rain.relocate(city->getWinX(2), 50.0, city->getWinZ(2));
        break;
      }
      // TURNS THE SPOTLIGHT ON OR OFF
      case '3': {
        toggleSpot = !toggleSpot;
        if(toggleSpot) {
          spot.turnOn();
        }
        else {
          spot.turnOff();
        }
        break;
        
      }
      // TURNS THE POINT LIGHT ON OR OFF
      case '4': {
        togglePoint = !togglePoint;
        if( togglePoint ) {
          point.turnOn();
        }
        else {
          point.turnOff();
        }
        break;
      }
      case '+': {
        city->add();
        break;
      }
      case '=': {
        city->sub();
        break;
      }
      case '.': {
        automatic = !automatic;
        break;
      }
      case '-': {
        t++;
        if (t == 100)
          t = 99;
        break;
      }
      case '_': {
        t--;
        if (t == 0)
          t = 1;
        break;
      }
        // Something else
      default:
        cerr << "KEY " << key << " pressed." << endl;
        break;
    }
  	glMatrixMode(GL_MODELVIEW);

}


//----------------------------------------------------------------------------
// Callback method called by GLUT when users press special keys on the keyboard
void Window::keyboardRelease(unsigned char key, int xn, int yn) {
  switch (key) {
    case 'w': {
      walk = false;
      break;
    }
  }
  
}


//----------------------------------------------------------------------------
// Callback method called by GLUT when users press special keys on the keyboard
void Window::keyboardSpecialRelease(int key, int xn, int yn) {
  switch (key) {
    case GLUT_KEY_UP: {
      walk = false;
      bbox.setT(0.0);
      break;
    }
    case GLUT_KEY_DOWN: {
      walk = false;
      bbox.setT(0.0);
      break;
    }
  }
  
}


//----------------------------------------------------------------------------
// Callback method called by GLUT when users press special keys on the keyboard
void Window::keyboardSpecialCallback(int key, int x, int y) {
  Matrix4 ident;
  ident.identity();
  
  Matrix4 temp;
  glMatrixMode(GL_PROJECTION);
  
  switch (key) {
    default:
      cerr << "KEY " << key << " pressed." << endl;
      break;
    // BUNNY
    case GLUT_KEY_F1: {
      scale->removeChild("city");
      break;
    }
    // DRAGON
    case GLUT_KEY_F2: {
      scale->addChild(city);
      break;
    }
    // BEAR
    case GLUT_KEY_F3: {
      break;
    }
    // TURN ON THE MATERIALS
    case GLUT_KEY_F4: {
      break;
    }
    // SHINIER MATERIAL
    case GLUT_KEY_F5: {
      //patch->setMaterial(&shiner);
      city->setMaterial(&shiner);
      break;
    }
    // MATTE OR DIFFUSE MATERIAL
    case GLUT_KEY_F6: {
      //patch->setMaterial(&diffuser);
      city->setMaterial(&diffuser);
      break;
    }
    // OOOOOOO
    case GLUT_KEY_F7: {
      //patch->setMaterial(&extra);
      city->setMaterial(&extra);
      break;
    }
    //FORWARD
    case GLUT_KEY_UP: {
      if(city->isBound()) {
        bbox.setCenter(person.getCenter());
      }
      if( !city->checkBound(person.getCenter())) {
        walk = true;
        person.move(ahead.get(0), ahead.get(1), ahead.get(2));
        camera.move(Vector3(ahead.get(0), ahead.get(1), ahead.get(2)), 1);
      }
      else {
        walk = false;
        person.move(-ahead.get(0), -ahead.get(1), -ahead.get(2));
        camera.move(Vector3(-ahead.get(0), -ahead.get(1), -ahead.get(2)), 1);
        person.move(-ahead.get(0), -ahead.get(1), -ahead.get(2));
        camera.move(Vector3(-ahead.get(0), -ahead.get(1), -ahead.get(2)), 1);
      }
      break;
     }
    //BACK
    case GLUT_KEY_DOWN: {
      if(city->isBound()) {
        bbox.setCenter(person.getCenter());
      }
      if( !city->checkBound(person.getCenter())) {
        walk = true;
        person.move(-ahead.get(0), -ahead.get(1), -ahead.get(2));
        camera.move(Vector3(-ahead.get(0), -ahead.get(1), -ahead.get(2)), 1);
      }
      else {
        walk = false;
        person.move(ahead.get(0), ahead.get(1), ahead.get(2));
        camera.move(Vector3(ahead.get(0), ahead.get(1), ahead.get(2)), 1);
        person.move(ahead.get(0), ahead.get(1), ahead.get(2));
        camera.move(Vector3(ahead.get(0), ahead.get(1), ahead.get(2)), 1);
      }
      break;
    }
    //LEFT
    case GLUT_KEY_LEFT: {
      person.rotateY(5);
      temp.makeRotateY(5);
      ahead = temp * ahead;
      side = temp * side;
      camera.rotateDirectionY(5);
      break;
    }
    //RIGHT
    case GLUT_KEY_RIGHT: {
      person.rotateY(-5);
      temp.makeRotateY(-5);
      ahead = temp * ahead;
      side = temp * side;
      camera.rotateDirectionY(-5);
      break;
    }
  }
  glMatrixMode(GL_MODELVIEW);
}


//----------------------------------------------------------------------------
// Callback method called by GLUT when users press special keys on the keyboard
void Window::mouseClick(int button, int state, int x, int y) {
  if( button == GLUT_LEFT_BUTTON ) {
    if( state == GLUT_DOWN ) {
      rightClick = false;
      leftClick = true;

      xMouse = x;
      yMouse = y;
      
      lastPoint = trackBallMapping(x, y);
      
    }
    else {
      leftClick = false;
    }
    
  }
  else if( button == GLUT_RIGHT_BUTTON ) {
    if( state == GLUT_DOWN ) {
      leftClick = false;
      rightClick = true;
      
      xMouse = x;
      yMouse = y;
      
      lastPoint = trackBallMapping(x, y);
      
    }
    else {
      rightClick = false;
    }
  }
  else {
    leftClick = false;
    rightClick = false;
    cerr << "How did you achieve this?" << endl;
  }
  
}


//----------------------------------------------------------------------------
// Callback method called by GLUT when users press special keys on the keyboard
void Window::mouseMove(int x, int y) {
  Vector3 direction;
  double pixel_diff;
  double rot_angle, zoom_factor;
  Vector3 curPoint = trackBallMapping(x, y);
  
  // ROTATION
  if( leftClick ) {
    if( x != xMouse || y != yMouse ) {
      direction = curPoint - lastPoint;
      double velocity = direction.length();
      
      if( velocity > 0.001 ) {
        Vector3 rotAxis;
        rotAxis.cross(lastPoint, curPoint);
        rot_angle = velocity * 90.0;
        
        Matrix4 rotM, rotated;
        rotM.identity();
        rotM.makeRotate(rot_angle, rotAxis);
        rotated = control.getMatrix();
        //rotated = rotation->getMatrix();
        rotated = rotM * rotated;
        //rotation->setMatrix(rotated);
        control.setMatrix(rotated);
        displayCallback();
        
      }
      
    }
    
  }
  // SCALING
  else if ( rightClick ) {
    pixel_diff = curPoint.getX() - lastPoint.getX();
    zoom_factor = 1.0 + pixel_diff * 2.0;
    
    Matrix4 scaM, scaled;
    scaM.identity();
    scaM.makeScale(zoom_factor, zoom_factor, zoom_factor);
    scaled = control.getMatrix();
    //scaled = objectWorld->getMatrix();
    scaled = scaM * scaled;
    control.setMatrix(scaled);
    //objectWorld->setMatrix(scaled);
    displayCallback();
    
  }
  
  lastPoint = curPoint;
}


//----------------------------------------------------------------------------
// makes the scene graph
void Window::makeModel(){
  // Identity matrix as default
  Matrix4 ident = Matrix4();
  ident.identity();
  
  // creates a Root Matrix Transformer
  rtWorld = new MatrixTransform("rootWorld", ident);
  
  // Extra stuff
  objectWorld = new MatrixTransform("objectWorld", ident);
  
  // Creates the scaling matrix to be passed into the scale Matrix Transform
  Matrix4 scaling = Matrix4();
  scaling.identity();
  //scaling.makeScale(2.0, 2.0, 2.0);
  
  scale = new MatrixTransform("scale", scaling);
  
  // Creates the rotation matrix to be passed into the rotation Matrix Transform
  Matrix4 rotate = Matrix4();
  rotate.identity();
  
  rotation = new MatrixTransform("rotate", rotate);
  
  // Creates the translation matrix to be passed into the translate Matrix
  //Transform
  Matrix4 trans = Matrix4();
  trans.identity();
  //trans.makeTranslate(0.0, -5.0, 0.0);

  translate = new MatrixTransform("translate", trans);
  
  Matrix4 m = Matrix4();
  m.identity();
  
  movement = new MatrixTransform("movement", trans);
  
  // Creates the object and sets a material as a default
  city = new City("city", &extra, 0);
  
  box = new SkyBox("skybox");
  
  //person = new Character();
  
  // Create the scene graph
  scale->addChild(city);
  scale->addChild(box);
  movement->addChild(scale);
  rotation->addChild(movement);
  translate->addChild(rotation);
  objectWorld->addChild(translate);
  rtWorld->addChild(objectWorld);
  //rtWorld->addChild(&character);
  
}


//----------------------------------------------------------------------------
// makes Character
void Window::makeCharacter() {
  Matrix4 temp;
  Matrix4 id;
  id.identity();
  
  //Setting up Controller
  temp.makeTranslate(0, 0, 10);
  control = MatrixTransform("control", temp);
  
  //Setting up Head
  headCube = Cube(2);
  headCube.setTexture(head);
  headRotation = MatrixTransform("headRotation", id);
  headScaling = MatrixTransform("headScaling", id);
  temp.makeTranslate(0, 7, 0);
  headTranslation = MatrixTransform("headTranslation", temp);
  headRotation.addChild(&headCube);
  headScaling.addChild(&headRotation);
  headTranslation.addChild(&headScaling);
  control.addChild(&headTranslation);
  
  //Setting up body
  bodyCube = Cube(1);
  bodyCube.setTexture(body);
  bodyRotation = MatrixTransform("bodyRotation", id);
  temp.makeScale(2, 3, 1);
  bodyScaling = MatrixTransform("bodyScaling", temp);
  temp.makeTranslate(0, 4.5, 0);
  bodyTranslation = MatrixTransform("bodyTranslation", temp);
  bodyRotation.addChild(&bodyCube);
  bodyScaling.addChild(&bodyRotation);
  bodyTranslation.addChild(&bodyScaling);
  control.addChild(&bodyTranslation);
  
  //Setting up Arms
  armCube = Cube(1);
  armCube.setTexture(arm);
  leftArmRotation = MatrixTransform("leftArmRotation", id);
  rightArmRotation = MatrixTransform("rightArmRotation", id);
  temp.makeScale(1, 3, 1);
  leftArmScaling = MatrixTransform("leftArmScaling", temp);
  rightArmScaling = MatrixTransform("rightArmScaling", temp);
  temp.makeTranslate(1.5, 4.5, 0);
  leftArmTranslation = MatrixTransform("leftArmTranslation", temp);
  temp.makeTranslate(-(1.5), 4.5, 0);
  rightArmTranslation = MatrixTransform("rightArmTranslation", temp);
  leftArmScaling.addChild(&armCube);
  rightArmScaling.addChild(&armCube);
  leftArmRotation.addChild(&leftArmScaling);
  rightArmRotation.addChild(&rightArmScaling);
  leftArmTranslation.addChild(&leftArmRotation);
  rightArmTranslation.addChild(&rightArmRotation);
  control.addChild(&leftArmTranslation);
  control.addChild(&rightArmTranslation);
  
  //Setting up Legs
  legCube = Cube(1);
  legCube.setTexture(leg);
  leftLegRotation = MatrixTransform("leftLegRotation", id);
  rightLegRotation = MatrixTransform("rightLegRotation", id);
  temp.makeScale(1, 3, 1);
  leftLegScaling = MatrixTransform("leftLegScaling", temp);
  rightLegScaling = MatrixTransform("rightLegScaling", temp);
  temp.makeTranslate(.5, 1.5, 0);
  leftLegTranslation = MatrixTransform("leftLegTranslation", temp);
  temp.makeTranslate(-.5, 1.5, 0);
  rightLegTranslation = MatrixTransform("rightLegTranslation", temp);
  leftLegScaling.addChild(&legCube);
  rightLegScaling.addChild(&legCube);
  leftLegRotation.addChild(&leftLegScaling);
  rightLegRotation.addChild(&rightLegScaling);
  leftLegTranslation.addChild(&leftLegRotation);
  rightLegTranslation.addChild(&rightLegRotation);
  control.addChild(&leftLegTranslation);
  control.addChild(&rightLegTranslation);
  
  character.addChild(&control);
  
  bbox = Box("bound");

}


//----------------------------------------------------------------------------
// loads Character Textures
void Window::loadTexture() {
  //Loading Head Texture
  head[0] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/headfront.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  head[1] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/headleft.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  head[2] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/headback.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  head[3] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/headright.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  head[4] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/headtop.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  head[5] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/headbottom.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  
  
  //Loading Body Textures
  
  body[0] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/bodyfront.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  body[1] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/bodyleft.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  body[2] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/bodyback.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  body[3] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/bodyright.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  body[4] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/bodytop.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  body[5] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/bodybottom.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  
  //Loading Arm Textures
  
  arm[0] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/armfront.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  arm[1] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/armleft.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  arm[2] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/armback.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  arm[3] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/armright.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  arm[4] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/armtop.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  arm[5] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/armbottom.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  
  //Loading Leg Textures
  
  leg[0] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/legfront.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  leg[1] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/legleft.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  leg[2] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/legback.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  leg[3] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/legright.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  leg[4] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/legtop.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  leg[5] = SOIL_load_OGL_texture
		(
     "/Users/xetajia/Desktop/Textures/legbottom.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
}


//----------------------------------------------------------------------------
// animates the person
void Window::animate() {
  Matrix4 transform;
  Matrix4 temp;
  Matrix4 reverseTemp;
  temp = leftArmRotation.getMatrix();
  reverseTemp = temp;
  if (walk) {
    if (forw) {
      temp.makeRotateX(degree);
      reverseTemp.makeRotateX(-degree);
      degree++;
      if (degree == 20)
        forw = !forw;
    }
    else {
      temp.makeRotateX(degree);
      reverseTemp.makeRotateX(-degree);
      degree--;
      if (degree == -20)
        forw = !forw;
    }
  }
  else {
    degree = 0;
    temp.identity();
    reverseTemp.identity();
  }
  transform.makeTranslate(0, -1.5, 0);
  temp = temp * transform;
  reverseTemp = reverseTemp * transform;
  transform.makeTranslate(0, 1.5, 0);
  temp = transform * temp;
  reverseTemp = transform * reverseTemp;
  leftArmRotation.setMatrix(temp);
  rightLegRotation.setMatrix(temp);
  rightArmRotation.setMatrix(reverseTemp);
  leftLegRotation.setMatrix(reverseTemp);
}


//----------------------------------------------------------------------------
//
Vector3 Window::trackBallMapping(int x, int y) {
  Vector3 v;    // Vector to hold synthesized 3D position of mouse on trackball
  double d;     // depth of the mouse location
  
  // Calculates all the coordinate positions
  v.setX( ((2.0 * x) - Window::width) / Window::width );
  v.setY( (Window::height - (2.0 * y)) / Window::height );
  v.setZ( 0.0 );
  
  // Distance of trackball from origin
  d = v.length();
  
  // limits d to values of 1.0 or less to avoid square roots of negative values
  d = ( d < 1.0 ) ? d : 1.0;
  
  // calculates Z with Pythagorean theorem
  v.setZ( sqrt(1.001 - d * d) );
  
  v.normalize();
  
  return v;
}


//----------------------------------------------------------------------------
//
void Window::setMatrix(Matrix4 camera, Matrix4 world) {
  glMatrixMode(GL_MODELVIEW);
  Matrix4 temp;
  temp = camera * world;
  temp.transpose();
  glLoadMatrixd(temp.getPointer());
}

//----------------------------------------------------------------------------
//
void Window::setMatrix(Matrix4 camera) {
  glMatrixMode(GL_MODELVIEW);
  Matrix4 temp = camera;
  temp.transpose();
  glLoadMatrixd(temp.getPointer());
}