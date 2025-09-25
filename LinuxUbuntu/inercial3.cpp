#include <cstdlib>
#include <iostream>
#include <cmath>
#include <complex>
#include <vector>
#include "Vector3D.hpp"

#include <GL/gl.h>
#include <GL/glut.h>

typedef std::complex<double>  dcomplex;

double sqr(double x)
{
    return x*x;
}


double K(double k)
{
   double x= 1.0;
   double y= std::sqrt(1.0-sqr(k));
   for (int n=0; n<20; n++)
      {
       double xx= (x+y) / 2.0;
       double yy= std::sqrt(x*y);
       x= xx;
       y= yy;
      }
   return M_PI / (2.0 * y);
}


double q(double k)
{
    return exp( -M_PI * K(std::sqrt(1.0-sqr(k))) / K(k));
}

double Te(double u, double k)
{
    double sum= 0.0;
    double sig= -1.0;
    double qk= q(k);
    double Kk= K(k);
    for (int j=1; j<=20; j++)
        {
         sum+= sig * pow(qk, sqr(j)) * cos((M_PI *j*u)/Kk);
         sig= -sig;
        }
    return  1.0 + 2.0 * sum;
}


dcomplex Te(dcomplex u, double k)
{
    dcomplex sum= 0.0;
    double   sig= -1.0;
    double   qk= q(k);
    double   Kk= K(k);
    for (int j=1; j<=20; j++)
        {
         sum+= sig * pow(qk, sqr(j)) * cos((M_PI *j*u)/Kk);
         sig= -sig;
        }
    return  1.0 + 2.0 * sum;
}

double H(double u, double k)
{
    double sum= 0.0;
    double sig= 1;

    double qk= q(k);
    double Kk= K(k);
    for (int j=0; j<=20; j++)
        {
         double e= (j+0.5);
         sum+= sig * pow(qk, sqr(e)) * sin((M_PI*e*u)/Kk);
         sig= -sig;
        }
    return  2.0 * sum;
}


double kp(double k)
{
   return std::sqrt(1.0-sqr(k));
}


double cn(double u, double k)
{
    return std::sqrt(kp(k)/k) * H(u+K(k), k) / Te(u,k);
}


double sn(double u, double k)
{
    return H(u,k) / (std::sqrt(k) * Te(u,k));
}

double dn(double u, double k)
{
    return std::sqrt(kp(k)) * Te(u+K(k),k)/Te(u,k);
}


double e0, e1, e2, e3;
double k1, k2;
double v;

GLuint MyScene;
Vector3D Pos(4.0, 0.0, 0.0);
Vector3D Sky(0.0, 1.0, 0.0);
Vector3D LookAt(0.0, 0.0, 0.0);
double angley= 0;
double anglex= 0;


class List : public std::vector<GLuint> {
      public:
         List(void) : std::vector<GLuint> () {};
};



void box(const Vector3D& pos,
         const Vector3D& a, 
         const Vector3D& b, 
         const Vector3D& c, double r)
{
     double bo[36][3] = {
        {-1,-1,-1},
        { 1,-1,-1},
        {-1, 1,-1},

        { 1, 1,-1},
        { 1,-1,-1},
        {-1, 1,-1},

        {-1,-1, 1},
        { 1,-1, 1},
        {-1, 1, 1},

        { 1, 1, 1},
        { 1,-1, 1},
        {-1, 1, 1},
//
        {-1,-1,-1},
        { 1,-1,-1},
        {-1,-1, 1}, 

        { 1,-1, 1},
        { 1,-1,-1},
        {-1,-1, 1}, 

        {-1, 1,-1},
        { 1, 1,-1},
        {-1, 1, 1}, 

        { 1, 1, 1},
        { 1, 1,-1},
        {-1, 1, 1}, 
//
        {-1,-1,-1},
        {-1, 1,-1},
        {-1,-1, 1},

        {-1, 1, 1},
        {-1, 1,-1},
        {-1,-1, 1},

        { 1,-1,-1},
        { 1, 1,-1},
        { 1,-1, 1},

        { 1, 1, 1},
        { 1, 1,-1},
        { 1,-1, 1}
     };

    glBegin(GL_TRIANGLES);
    for (int k=0; k<36; k++)
       {
        Vector3D v= pos + r*(bo[k][0]*a + bo[k][1]*b + bo[k][2]*c);
        glVertex3d(v.x(), v.y(), v.z());
       }
    glEnd();
}


void arrow(const Vector3D& a, 
           const Vector3D& b, 
           const Vector3D& c, double r)
{
    const int N= 8;
    Vector3D p[N+1], q[N+1], s[N+1];
    Vector3D u= (1.0 - 3.0 * r * (1.0 + std::sqrt(5.0)) / 2.0) * a;

    double h = 2.0 * M_PI / N;
    for (int k=0; k<=N; k++) 
       {
        p[k]= r * ( cos(k*h) * b  + sin(k*h) * c);
        q[k]= u + p[k];
        s[k]= u + 2.0 * p[k];
       }

    glBegin(GL_TRIANGLES);
    for (int k=0; k<N; k++)
        {
         glVertex3d(p[k  ].x(), p[k  ].y(), p[k  ].z()); 
         glVertex3d(p[k+1].x(), p[k+1].y(), p[k+1].z()); 
         glVertex3d(q[k  ].x(), q[k  ].y(), q[k  ].z()); 

         glVertex3d(p[k+1].x(), p[k+1].y(), p[k+1].z()); 
         glVertex3d(q[k+1].x(), q[k+1].y(), q[k+1].z()); 
         glVertex3d(q[k  ].x(), q[k  ].y(), q[k  ].z()); 

         glVertex3d( u.x(), u.y(), u.z() );
         glVertex3d( s[k].x(), s[k].y(), s[k].z() );
         glVertex3d( s[k+1].x(), s[k+1].y(), s[k+1].z() );
  
         glVertex3d( s[k].x(), s[k].y(), s[k].z() );
         glVertex3d( s[k+1].x(), s[k+1].y(), s[k+1].z() );
         glVertex3d( a.x(), a.y(), a.z() );
        }
}

GLuint  DrawPixel( const Vector3D& a, 
                   const Vector3D& b, 
                   const Vector3D& c,
                   double r)
{
    GLuint L= glGenLists(1);
    glNewList(L, GL_COMPILE);	

    r*= 0.5;
    glColor3f(1.0f, 0.0f, 0.0f);
    box((1.0+r)*a, a, b, c, r);
    glColor3f(0.0f, 1.0f, 0.0f);
    box((1.0+r)*b, b, c, a, r);
    glColor3f(0.0f, 0.0f, 1.0f);
    box((1.0+r)*c, c, a, b, r);

    glEndList();
    return L;
}

GLuint DrawBody(const Vector3D& a, 
                const Vector3D& b, 
                const Vector3D& c,
                double r)
{
    GLuint L= glGenLists(1);
    glNewList(L, GL_COMPILE);	

    const Vector3D z= Vector3D(0.0, 0.0, 0.0);

    glColor3f(1.0f, 1.0f, 1.0f);
    box(z, a, b, c, 2.0*r);

    glColor3f(1.0f, 0.0f, 0.0f);
    arrow(a, b, c, r);

    glColor3f(0.0f, 1.0f, 0.0f);
    arrow(b, c, a, r);

    glColor3f(0.0f, 0.0f, 1.0f);
    arrow(c, a, b, r);

    glEnd();
    glEndList();
    return L;
}

List Pixels;
List Bodies;
List::iterator BodiesPtr;


double f(double z)
{
   return sn(z,k2) - std::sqrt((e1-e0)/(e1-e3));
}

double fp(double z)
{
   return cn(z,k2) * dn(z,k2);
}

double Newton(void)
{
    double x0;
    double x1= 3.0*K(k2)/2.0;
    do {
       x0 = x1;
//       x1= x0 - (sn(x0, k2) - v)/(cn(x0,k2) * dn(x0,k2));
       x1= x0 - f(x0) / fp(x0);
std::cerr << "Newton: " << x1 << std::endl;
    } while ( fabs(x0-x1) > 1E-8 );
    return x1;
}

void Lists(double a, double e, int N) 
{
   a= M_PI/a;

std::cerr << "a= " << a << std::endl;

   e0= e;

std::cerr << "e0= " << e0 << std::endl;

   e1= cos(a);

std::cerr << "e1= " << e1 << std::endl;

   e2= cos(a-2.0*M_PI/3.0);

std::cerr << "e2= " << e2 << std::endl;

   e3= cos(a+2.0*M_PI/3.0);

std::cerr << "e3= " << e3 << std::endl;

   k1= std::sqrt( ((e0-e3)*(e1-e2)) / ((e1-e0)*(e2-e3)) ); 

std::cerr << "k1= " << k1 << std::endl;

   k2= std::sqrt( ((e1-e3)*(e2-e0)) / ((e1-e0)*(e2-e3)) ); 

std::cerr << "k2= " << k2 << std::endl;

   v= std::sqrt((e1-e0)/(e1-e3));

//   double p= 2.24128360630659;

std::cerr << "K(k2)= " << K(k2) << std::endl;
   double z;
   z= Newton();
//     z= 2.91830585300929;

std::cerr << "z= " << z << std::endl;

   const dcomplex I(0.0, 1.0);
   for (int i=0; i<N; i++)
      {
       double u= 4*i*K(k1)/N;

       double h2= sn(z,k2) * dn(u,k1);
       double h1= dn(z,k2) * sn(u,k1);
       double h0= cn(z,k2) * cn(u,k1);

       dcomplex c=  cn(z,k2)/std::sqrt(1.0-sqr(sn(z,k2))*sqr(dn(u,k1))) *
                    Te(0.0, k1) / (Te(z*I, k1) * Te(u, k1)) *
                    Te(u+z*I, k1);

       double Re= real(c);
       double Im= imag(c);

       double den= std::sqrt(1.0-sqr(h2));
       double r0=  ( h1 * Re - h2*h0*Im) / den;
       double r1=  (-h0 * Re - h2*h1*Im) / den;
       double r2=  Im * den;

       double s0= ( h1 * Im + h2*h0*Re ) / den;
       double s1= (-h0 * Im + h2*h1*Re ) / den;
       double s2=  -Re * den;

       Vector3D h(h0, r0, s0);
       Vector3D r(h1, r1, s1);
       Vector3D s(h2, r2, s2);
          
       std::cout << h << r << s << std::endl;

       if (abs( h%r - s ) > 1E-12)
           std::cerr << "ERROR - std::vectors are not orthogonal\n";
           
       Bodies.push_back(DrawBody(h, r, s, 0.05));

       Pixels.push_back(DrawPixel(h, r, s, 0.0125));
      }
   BodiesPtr= Bodies.begin();
}

void changeSize(int width, int height)
{
     // Prevent a divide by zero, when window is too short
     // (you cant make a window of zero width).
     if (height == 0)
        height = 1;

     float ratio = (float)width / (float)height;

     // Reset the coordinate system before modifying
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

     // Set the viewport to be the entire window
     glViewport(0, 0, width, height);

     // Set the correct perspective.
     gluPerspective(45,ratio,1,1000);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     gluLookAt(Pos.x(),Pos.y(),Pos.z(),
     LookAt.x(),LookAt.y(),LookAt.z(),
     Sky.x(),Sky.y(),Sky.z());
}


void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef(angley, 0, 1, 0);
    double t= angley * M_PI /180;
    glRotatef(anglex, -sin(t), 0, cos(t));

    for (List::iterator p= Pixels.begin(); p!=Pixels.end(); p++)
       glCallList(*p);

    glCallList(*BodiesPtr);

    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void MyTimer(int v)
{
    if ( ++BodiesPtr == Bodies.end() )
       BodiesPtr= Bodies.begin();  
    renderScene();
    glutTimerFunc(50, MyTimer, v+1);
}

void processNormalKeys(unsigned char key, int x, int y) {
    switch (key)
      {
       case '+':  glMatrixMode(GL_MODELVIEW);
                  glLoadIdentity();
                  Pos= Pos + Vector3D(1,0,0);
                  gluLookAt(Pos.x(),Pos.y(),Pos.z(),
                  LookAt.x(),LookAt.y(),LookAt.z(),
                  Sky.x(),Sky.y(),Sky.z());
                  break;

       case '-':  glMatrixMode(GL_MODELVIEW);
                  glLoadIdentity();
                  Pos= Pos - Vector3D(1,0,0);
                  gluLookAt(Pos.x(),Pos.y(),Pos.z(),
                  LookAt.x(),LookAt.y(),LookAt.z(),
                  Sky.x(),Sky.y(),Sky.z());
                  break;

       case 27 :  exit(0);
      }
}


void processSpecialKeys(int key, int x, int y) {
    switch (key)
      {
       case GLUT_KEY_DOWN:  anglex-=2;
                            return;

       case GLUT_KEY_UP:    anglex+=2;
                            return;

       case GLUT_KEY_LEFT:  angley-=2;
                            return;

       case GLUT_KEY_RIGHT: angley+=2;
                            return;

       case '+':            std::cerr << "hola 0\n";


      }
}


int main(int narg, char* args[])
{
    double a= 5;
	do {
	    std::cerr << "Dar divisor de Pi (numero real mayor que 3):\n";
		std::cin >> a;
	} while( a<=3.0 );
    
    double e= -0.3;
	double e1= cos(M_PI/a - 2.0*M_PI/3.0);
	double e2= cos(M_PI/a + 2.0*M_PI/3.0);
	if (e1>e2) {
		double t= e1;
		e1= e2;
		e2= t;	
	}

	do {
	    std::cerr << "Dar e0 (numero real mayor que cos(Pi/a-2Pi/3)=" 
			<<	e1
			<<	" y menor que cos(Pi/a+2Pi/3)= " 
			<<	e2 << ":\n";
		std::cin >> e;
	} while (e < e1 || e2 < e);
    
    int N= 256;
    if ( narg>1 )
       N= atoi(args[1]);

    glutInit(&narg, args);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(720,480);
    glutCreateWindow(args[0]);
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);
    glEnable(GL_DEPTH_TEST);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    glutTimerFunc(50, MyTimer, 0);

    Lists(a, e, N);

    glutMainLoop();
    return EXIT_SUCCESS;
}


