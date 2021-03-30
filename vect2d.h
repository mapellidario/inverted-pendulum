//Dario Mapelli 768248 d.mapelli7@campus.unimib.it
#ifndef vect2d_h
#define vect2d_h

class vect2d {

	public:
		//def ctor
		vect2d();
		//ctor vero e proprio
		vect2d(double x, double y);
		//dtor
		~vect2d();


		vect2d& operator= (const vect2d& original);
		vect2d operator+ (const vect2d& addendo); 
		vect2d operator- (const vect2d& sottraendo);
		vect2d operator* (const double k) ;
		vect2d PS (double k);
		double Mod () const;
		void Print() const;
		
		double GetX() const;
		double GetY() const;
		
	private:
		double x_p;
		double y_p;

};

#endif
