#include "vect2d.h"
#include <cmath>
#include <iostream>

using namespace std;

		//distruttori e costruttori non vogliono il return
		vect2d::vect2d() 
		{
			x_p = 0;
			y_p = 0;
		}
		//ctor vero e proprio
		vect2d::vect2d(double x, double y)
		{
			x_p = x;
			y_p = y;
		}

		vect2d::~vect2d() {} 

		//voglio uguaglianza tra vettori: overloadin operatori: operator=
		vect2d& vect2d::operator= (const vect2d& original)
		{
			x_p = original.x_p;
			y_p = original.y_p;
			return *this;
		}//qui paso la referenza
		
		vect2d vect2d::operator+ (const vect2d& addendo) 
		{
			double xsum = x_p + addendo.x_p ;
			double ysum = y_p + addendo.y_p ;
			vect2d somma (xsum, ysum);
			return somma;			
		}//non posso passare per referenza un oggetto definito nel metodo
		
		vect2d vect2d::operator- (const vect2d& sottraendo)
		{
			double xdiff = x_p - sottraendo.x_p ;
			double ydiff = y_p - sottraendo.y_p ;
			vect2d diff (xdiff, ydiff);
			return diff;			
		}
		
		vect2d vect2d::operator* (const double k)
		{
			double xprod = x_p * k;
			double yprod = y_p * k;
			vect2d prod (xprod, yprod);
			return prod;
		}//prima mettere l'oggetto vect2d, poi tutti gli scalari del caso
		
		//Prodotto per uno Scalare.
		//uguale all'overloading di operator*
		vect2d vect2d::PS (double k) 
		{
			double xprod = x_p * k;
			double yprod = y_p * k;
			vect2d prod (xprod, yprod);
			return prod;
		}
		
		double vect2d::Mod () const
		{
			double mod = sqrt(x_p*x_p + y_p*y_p);
			return mod;
		}
		
		void vect2d::Print() const
		{
			cout << "( " << x_p << " ; "<< y_p << " )" << endl;
		}
		
		double vect2d::GetX() const
		{
			return x_p;
		}
		double vect2d::GetY() const
		{
			return y_p;
		}
		

