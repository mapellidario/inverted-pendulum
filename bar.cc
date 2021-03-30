#include <cmath>
#include <iostream>
#include <cstdlib>
#include "vect2d.h"
#include "bar.h"

	//default ctor
	bar::bar() :
		mass_p (1.) ,
		lenght_p (1.),
		baricentro_p (0.5),
		theta_p (0.), //theta_p (0.- (3.14159265358979323846264338327950288/2.))
		veltheta_p (0.)
	{
		vect2d perno_p (0., 0.);
		vect2d velperno_p (0., 0.);	
		SetPosEstremo ();
		SetVelEstremo ();
	}	//NB per chiamare questo costruttore scrivere:
		//bar asta ;
		//e non
		//bar asta() ;
		//otherwise the compiler think `bar asta ()` as of function declaration with name `asta` and the return type `bar`.
		
	//copy ctor
	bar::bar (const bar& original)
	{
		mass_p = original.mass_p ; 
		lenght_p = original.lenght_p ;
		baricentro_p = original.baricentro_p ;
		perno_p = original.perno_p ;
		velperno_p = original.velperno_p ;
		theta_p = original.theta_p ;
		veltheta_p = original.veltheta_p ;		 
		estremo_p = original.estremo_p ; 
		velestremo_p = original.velestremo_p;
	}	

	//ctor: solo parametri strutturali
	bar::bar(double mass, double lenght, double baricentro):
		mass_p (mass),
		lenght_p (lenght),
		baricentro_p(baricentro),
		theta_p (0.), //theta_p (0.- (3.14159265358979323846264338327950288/2.))
		veltheta_p (0.)
	{
		vect2d perno_p (0., 0.);
		vect2d velperno_p (0., 0.);	
		SetPosEstremo ();
		SetVelEstremo ();
	}
	//ctor: solo parametri cinetici
	bar::bar(vect2d& perno, double theta, vect2d& velperno, double veltheta):
		mass_p (1.) ,
		lenght_p (1.),
		baricentro_p (0.5),
		theta_p (theta),
		veltheta_p (veltheta)
	{
		perno_p = perno ;
		velperno_p = velperno;
		SetPosEstremo ();
		SetVelEstremo ();
	}
	//ctor: completo, setta tutto
	bar::bar(double mass, double lenght, double baricentro, vect2d& perno, double theta, vect2d& velperno, double veltheta):
		mass_p (mass),
		lenght_p (lenght),
		baricentro_p(baricentro),
		theta_p (theta),
		veltheta_p (veltheta)
	{
		perno_p = perno ;
		velperno_p = velperno;
		SetPosEstremo ();
		SetVelEstremo ();
	}
	//dtor
	bar::~bar() {}


	//OPERATORS
	bar& bar::operator= (const bar& original)
	{
		mass_p = original.mass_p ; 
		lenght_p = original.lenght_p ;
		baricentro_p = original.baricentro_p ;
		perno_p = original.perno_p ;
		velperno_p = original.velperno_p ;
		theta_p = original.theta_p ;
		veltheta_p = original.veltheta_p ;
		SetPosEstremo ();
		SetVelEstremo ();
		return *this ;
	}

	//SETTINGS
	void bar::SetPosPerno (vect2d& pos) 
	{
		perno_p = pos ;
	}	
	void bar::SetVelPerno (vect2d& vel)
	{
		velperno_p = vel ;
	}
	void bar::SetTheta (double& theta)
	{
		theta_p = theta;
	}
	void bar::SetVelTheta (double& vel)
	{
		veltheta_p = vel ;
	}
	void bar::SetPosEstremo ()
	{
		vect2d estremo (perno_p.GetX() + lenght_p * sin(theta_p), perno_p.GetY() - lenght_p * cos(theta_p));
		estremo_p = estremo;
	}
	void bar::SetVelEstremo ()
	{
		vect2d velestremo (veltheta_p * lenght_p * sin(theta_p) , - veltheta_p * lenght_p * cos(theta_p) ) ;
		velestremo_p = velestremo ;
	}
	
	
	//GETS
	double bar::GetMass() const {
		return mass_p;
	}
	double bar::GetLenght() const {
		return lenght_p;
	}
	double bar::GetBaricentro() const {
		return baricentro_p;
	}
	vect2d bar::GetPosPerno () const
	{
		return perno_p;
	}
	vect2d bar::GetVelPerno () const
	{
		return velperno_p;
	}
	double bar::GetTheta () const
	{
		return theta_p ;
	}
	double bar::GetVelTheta () const
	{
		return veltheta_p ;
	}
	vect2d bar::GetPosEstremo () const
	{
		return estremo_p ;
	}
	vect2d bar::GetVelEstremo () const
	{
		return velestremo_p ;
	}		
	
	//Varie
	void bar::Gravity (double deltaStep) 
	{
		perno_p = velperno_p * deltaStep + perno_p ; //sposta il perno, moto rett uniforme
		//velperno_p suppongo rimnga uguale
		double Fperp = - mass_p * 9.806 * sin(theta_p) ; //calcolo la forza perpendicolare alla sbarra, quindi quella efficace, che ruota il pendolo.
		double accTheta = Fperp / (mass_p * lenght_p * baricentro_p ) ; //calcolo l'accelerazione angolare
		theta_p += accTheta * deltaStep * deltaStep /2. + veltheta_p * deltaStep ; //imposto il nuovo angolo
		veltheta_p += accTheta * deltaStep ; //imposto la nuova velocità angolare
		SetPosEstremo();
		SetVelEstremo();
	}
	//fa agire la bar per un periodo di tempo delta t.
	//deltaStep: lunghezza dell'intervallo di tempo che corrisponde a ciascuno step
	/*poichè per calcolare la nuova posizione angolare faccio uso della velocità angolare 
	*all'inizio del deltastep (secondo le formule del moto circolaer uniformemente accelerato), 
	*aggiorno la velocità angolare (veltheta) dopo aver calcolato la nuova posizione angolare (theta)
	*/
	//la posizione angolare è calcolata tramite approssimazione quadratica

	void bar::Gravity1 (double deltaStep) 
	{
		perno_p = velperno_p * deltaStep + perno_p ; //sposta il perno, moto rett uniforme
		//velperno_p suppongo rimnga uguale
		double Fperp = - mass_p * 9.806 * sin(theta_p) ; //calcolo la forza perpendicolare alla sbarra, quindi quella efficace, che ruota il pendolo.
		double accTheta = Fperp / (mass_p * lenght_p * baricentro_p ) ; //calcolo l'accelerazione angolare
		theta_p += accTheta * deltaStep * deltaStep /2. + veltheta_p * deltaStep ; //imposto il nuovo angolo
		veltheta_p += accTheta * deltaStep ; //imposto la nuova velocità angolare
		SetPosEstremo();
		SetVelEstremo();
	}//la posizione angolare è fissata tramite approssimazione lineare.


	void bar::GravFriction (double deltaStep, double k) 
	{
		perno_p = velperno_p * deltaStep + perno_p ; //sposta il perno, moto rett uniforme
		//velperno_p suppongo rimnga uguale
		double Fperp = - mass_p * 9.806 * sin(theta_p) - k*veltheta_p ; //calcolo la forza perpendicolare alla sbarra, quindi quella efficace, che ruota il pendolo, tenendo conto degli effetti dell'attrito, modellizzato come "viscoso", -k*velocitàangolare
		double accTheta = Fperp / (mass_p * lenght_p * baricentro_p ) ; //calcolo l'accelerazione angolare
		theta_p += veltheta_p * deltaStep ; //imposto il nuovo angolo (lineare)
		veltheta_p += accTheta * deltaStep ; //imposto la nuova velocità angolare
		SetPosEstremo();
		SetVelEstremo();
	}//la posizione angolare è fissata tramite approssimazione lineare.

	void bar::GravStabVert (double deltaStep, int i, double A, double w, double phi, vect2d perno ) 
	{
		//parametri 
		double arg = w*i*deltaStep + phi ;
		//imposto la posizione del perno
		vect2d traslazione (0., A*sin(arg));
		perno_p	= perno + traslazione ;	
		//calcolo 3l'accelerazione angolare
		double accTheta = A*w*w*sin(arg)*sin(theta_p) - 9.806*sin(theta_p) ; 
		theta_p += veltheta_p * deltaStep ; //imposto il nuovo angolo
//		theta_p += accTheta*deltaStep*deltaStep/2. + veltheta_p * deltaStep ; //imposto il nuovo angolo
		veltheta_p += accTheta * deltaStep ; //imposto la nuova velocità angolare
		//imposto la posizione dell'estremo
		SetPosEstremo();
		SetVelEstremo();
	}//la posizione angolare è fissata tramite approssimazione lineare.

	void bar::GravStabVert1 (double deltaStep, int i, double A, double w, double phi, vect2d perno ) 
	{
		//parametri 
		double arg = w*i*deltaStep + phi ;
		//imposto la posizione del perno
		vect2d traslazione (0., A*sin(arg));
		perno_p	= perno + traslazione ;	
		//calcolo 3l'accelerazione angolare
		double accTheta = A*w*w*sin(arg)*sin(theta_p) - 9.806*sin(theta_p) ; 
//		theta_p += veltheta_p * deltaStep ; //imposto il nuovo angolo
		theta_p += accTheta*deltaStep*deltaStep/2. + veltheta_p * deltaStep ; //imposto il nuovo angolo
		veltheta_p += accTheta * deltaStep ; //imposto la nuova velocità angolare
		//imposto la posizione dell'estremo
		SetPosEstremo();
		SetVelEstremo();
	}//la posizione angolare è fissata tramite approssimazione lineare.

	vect2d bar::Vincolo ()
	{
		vect2d vel_cm = velestremo_p * baricentro_p ; //CM significa baricentro
		double mod_vel_cm = vel_cm.Mod() ;
		double ModuloReazione = mass_p * ( 9.806 * cos(theta_p) + mod_vel_cm * mod_vel_cm / lenght_p ) ; //calcolo il modulo della tensione
		double Reazione_x = -ModuloReazione * sin ( theta_p ) ;
		double Reazione_y = ModuloReazione * cos ( theta_p ) ;
		vect2d Reazione ( Reazione_x , Reazione_y ) ; 
		return Reazione ;
	}
	/*lo scopo di questo metodo è calcolare la reazione vincolare del perno necessaria per ruotare la barra.
	* poichè modellizzo la barra con un punto materiale posizionato nel baricentro della barra stessa e massa pari all'intera massa della barra,
	* vincolato al perno per mezzo di un'asta inestensibile con massa trascurabile (assimilabile perciò a un pendolo semplice.)
	* la reazione vincolare esercitata dal perno è uguale alla tensione dell'asta stessa, calcolata con le tradizionali formule del pendolo semplice.
	* il modulo della tensione dell'asta è perciò: T = m ( g * cos(theta) + v^2 / l )
	* la direzione della tensione è parallela all'asta stessa con verso opposto a quello del vettore perno->baricentro 
	* (quindi dal baricentro verso il perno).
	* perciò le sue componenti in funzione di teta sono opposte a quelle della barra: x=-sin(theta), y=cos(theta) 
	* a relazione scritta è istantanea.
	*/


	void bar::Print() const
	{
		std::cout << "massa: " << mass_p << std::endl << "lungh: " << lenght_p << std::endl
			<< "baricentro: " << baricentro_p << std::endl
			<<"posizione perno: (" << perno_p.GetX() << " ; " << perno_p.GetY() << ") \n" 
			<<"velocità perno: (" << velperno_p.GetX() << " ; " << velperno_p.GetY() << ") \n" 
			<<"theta: " << theta_p << std::endl << "velocità theta: " << veltheta_p << std::endl
			<<"posizione estremo: (" << estremo_p.GetX() << " ; " << estremo_p.GetY() << ") \n" 
			<<"velocità estremo: (" << velestremo_p.GetX() << " ; " << velestremo_p.GetY() << ") \n" ;
	}
	
	std::ostream& operator<< (std::ostream& printer, const bar& other)
	{
		printer << "massa: " << other.GetMass() << std::endl << "lungh: " << other.GetLenght() << std::endl
			<< "baricentro: " << other.GetBaricentro() << std::endl
			<<"posizione perno: (" << other.GetPosPerno().GetX() << " ; " << other.GetPosPerno().GetY() << ") \n" 
			<<"velocità perno: (" << other.GetVelPerno().GetX() << " ; " << other.GetVelPerno().GetY() << ") \n" 
			<<"theta: " << other.GetTheta() << std::endl << "velocità theta: " << other.GetVelTheta() << std::endl
			<<"posizione estremo: (" << other.GetPosEstremo().GetX() << " ; " << other.GetPosEstremo().GetY() << ") \n" 
			<<"velocità estremo: (" << other.GetVelEstremo().GetX() << " ; " << other.GetVelEstremo().GetY() << ") \n" ;
		return printer;
	}
	//uso il metodo Get perchè gli attributi di other non sono raggiungibili direttamente dal main, mi serve un metodo interno alla classe (in quanto privati)
	//per definire questa funzione, serve che tutti i metodi chiamati su other siano di tipo const in quanto ho richiesto che other fosse const. quindi devo aggiungere const nella posizione opportuna a tutti i metodi Get()
	

