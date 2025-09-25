#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include <math.h>

class Vector3D {
	protected:
		double u[4];
         
	public:
		double& operator [] (int k);

		Vector3D(double xx=0, double yy= 0, double zz= 0);
		Vector3D(const Vector3D& a);
		double x() const { return u[0]; };
		double y() const { return u[1]; };
		double z() const { return u[2]; };

         Vector3D& operator = (const Vector3D&);
        };
        

Vector3D operator + (const Vector3D& a, const Vector3D& b);
Vector3D operator - (const Vector3D& a, const Vector3D& b);
Vector3D operator % (const Vector3D& a, const Vector3D& b);
Vector3D operator * (double a, const Vector3D& b);
double   operator * (const Vector3D& a, const Vector3D& b);
Vector3D operator / (const Vector3D& a, const double b);
Vector3D operator - (const Vector3D& a);
bool     operator == (const Vector3D&, const Vector3D& );
double   abs(const Vector3D& a);
double   infty(const Vector3D& a);
Vector3D unit(const Vector3D& v);

std::istream& operator >> (std::istream& is, Vector3D& a);
std::ostream& operator << (std::ostream& os, const Vector3D& a);

Vector3D line(double t, Vector3D& b, Vector3D& e);

#endif
