//Dario Mapelli 768248 d.mapelli7@campus.unimib.it
#ifndef bar_h
#define bar_h

#include "vect2d.h"
#include <iostream> 

class bar
{
	public:
		bar();	
		bar (const bar& original);
		bar(double mass, double lenght, double baricentro);
		bar(vect2d& perno, double theta, vect2d& velperno, double veltheta);
		bar(double mass, double lenght, double baricentro, vect2d& perno, double theta, vect2d& velperno, double veltheta);
		~bar();

		bar& operator= (const bar& original);

		void SetPosPerno (vect2d& pos); 
		void SetVelPerno (vect2d& vel);
		void SetTheta (double& theta);	
		void SetVelTheta (double& vel);
		void SetPosEstremo (); //esegue il calcolo per impostarlo
		void SetVelEstremo (); //esegue il calcolo per impostarlo
		
		double GetMass() const;
		double GetLenght() const;
		double GetBaricentro() const;
		vect2d GetPosPerno () const;
		vect2d GetVelPerno () const;
		double GetTheta () const;
		double GetVelTheta () const; //angular velocity
		vect2d GetPosEstremo () const; 
		vect2d GetVelEstremo () const; //
		
		void Print() const;
		void Gravity (double deltaStep);
		void Gravity1 (double deltaStep) ;
		void GravFriction (double deltaStep, double k) ;
		void GravStabVert (double deltaStep, int i, double A, double w, double phi, vect2d perno) ;
		void GravStabVert1 (double deltaStep, int i, double A, double w, double phi, vect2d perno ) ;
		vect2d Vincolo ();
		
	private:
		//parametri geometrici
		double mass_p;
		double lenght_p;
		double baricentro_p;
		//dof
		vect2d perno_p; 
		vect2d velperno_p;
		double theta_p; 
		double veltheta_p;
		//valori comodi da avere
		vect2d estremo_p; //potrei calcolarlo ogni volta che serve, ma avere il membro è piu immediato
		vect2d velestremo_p;
};

std::ostream& operator<< (std::ostream&, const bar&);
//ho bisogno di passare il cout ed un bar come argomento

#endif

/*AVVERTENZE
	raffiguro la barra con un punto materiale posizionato nel baricentro della barra stessa e massa pari all'intera massa della barra.

	l'angolo theta è da considerarsi zero quando punta verso y neativi, e crescente in senso antiorario
	evo quindi scrivere in generale le componenti: x=sen(theta) e y=-cos(theta)

	ho desico di individuare la sbarra attraverso la posizione del perno e l'anglo rispetto all'asse y negativo. (e le corrispetive velocità)
	quindi la posizione dell'estremo è calcolata di conseguenza.


*/
