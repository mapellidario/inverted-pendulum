/*
	Double Pendulum Simulation
	g++ -o test vect2d.cc bar.cc test.cpp `root-config --cflags --glibs`
	raccoglie tutti i vari test eseguiti nel file pend.cpp
	TDL: creare una cartella e scorporarli tutti in vari file .cpp
	
	http://www.myphysicslab.com/beta/Inverted-pendulum.html
	http://www.elmer.unibas.ch/pendulum/vpend.htm
*/

//STL
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

//Root
#include "TCanvas.h" // `root-config --glibs --cflags`
#include "TAxis.h" 
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TApplication.h"
#include "TStyle.h"

//personali
#include"vect2d.h"
#include"bar.h"

using namespace std;
//#define N 123

int main (int numArg, char * listArg[])
{
	//test del default ctor
	bar asta ; //test dell'oggetto
//	bar *astaPtr = new bar (); //test del puntatore a oggetto
	
	//test dei Get() - Print()
/*	std::cout << "massa: " << asta.GetMass() << endl << "lungh: " << asta.GetLenght() << endl
		<< "baricentro: " << asta.GetBaricentro() << endl
		<<"posizione perno: (" << asta.GetPosPerno().GetX() << " ; " << asta.GetPosPerno().GetY() << ") \n" 
		<<"velocità perno: (" << asta.GetVelPerno().GetX() << " ; " << asta.GetVelPerno().GetY() << ") \n" 
		<<"theta: " << asta.GetTheta() << endl << "velocità theta: " << asta.GetVelTheta() << endl
		<<"posizione estremo: (" << asta.GetPosEstremo().GetX() << " ; " << asta.GetPosEstremo().GetY() << ") \n" 
		<<"velocità estremo: (" << asta.GetVelEstremo().GetX() << " ; " << asta.GetVelEstremo().GetY() << ") \n" ;
	cout << endl;
	//test Print()
	asta.Print();
	cout << endl;
	astaPtr->Print();
	cout << endl;

	//test del copy ctor
	bar asta2 = asta;
//	asta2.Print();
//	cout << endl;
*/	

/*
	vect2d perno (0.,0.); //lo metto qui per vedere se ilmetodo Vincolo funziona
	vect2d vperno(.0, 0.);
	double theta = 3.14159265358979323846264338327950288/2. ;
	double veltheta = 0.1 ;
	//test dei Set()
	asta.SetPosPerno(perno) ;
	asta.SetVelPerno (vperno);
	asta.SetTheta(theta);
	asta.SetVelTheta (veltheta);
	asta.SetPosEstremo();
	asta.SetVelEstremo();
//	asta.Print();
//	cout << endl;

	//test del ctor parametri
	bar asta4 (2.45,1.89,.789);
	cout << endl << asta4 << endl;
	//test del ctor gradi di libertà
	bar asta5 (perno,theta/2.,vperno,-3.1);
	cout << endl << asta5 << endl;
*/


	//test del ctor completo
//	bar asta3 (0.1 ,1.,0.5,perno,theta+1.,vperno,veltheta);
//	asta3.Print();

	//test di overloading di operator<<
//	cout << asta3 << endl;

/*	
	//ulteriori test di copy ctor
	bar asta_1;
	bar asta_2;
	cout << asta_1 << endl << asta_2 << endl << asta3 << endl ;
	asta_1 = asta_2 = asta3 ;
	cout << asta_1 << endl << asta_2 << endl << asta3 << endl ;
*/
	
/*	//impostare un ciclo gravity su un asta
	for (int i=0; i<1000; i++) {
		asta3.Gravity(0.001);
	}
	asta3.Print();
*/

/*	//test: impostare ciclo gravity() con resa grafica by Root-Cern
	TApplication* theApp = new TApplication("App", &numArg, listArg);
	TCanvas *c1 = new TCanvas ("c1", "c1", 1000, 500);
	c1->Divide(2,1);
	c1->cd(1)->SetGrid();
	c1->cd(2)->SetGrid();
	//disegno il primo grafico, in cui riporto la posizione del perno e dell'estermo
	TMultiGraph *mg_pos = new TMultiGraph();
	TGraph *graph_x = new TGraph ();
	TGraph *graph_y = new TGraph ();
	graph_x->SetMarkerStyle(20);
	graph_x->SetMarkerColor(kBlue);
	mg_pos->Add(graph_x);
	graph_y->SetMarkerStyle(20);
	graph_y->SetMarkerColor(kRed);
	mg_pos->Add(graph_y);
	//disegno il secondo grafico, in cui riporto il valore dell'angolo theta
	TMultiGraph *mg_ang = new TMultiGraph();
	TGraph *graph_theta = new TGraph ();
	graph_theta->SetMarkerStyle(20);
	graph_theta->SetMarkerColor(kBlue);
	mg_ang->Add(graph_theta);
	mg_ang->Draw("ap");
	//eseguo il ciclo, ovvero lascio che Gravity() agisca su asta3 per 100000 step dalla durata di 0.0001
	//a ogni step aggiorno entrambi i grafici
	for (int i=0; i<100000; i++ ) {
		asta3.Gravity(0.0001) ; 
		graph_x->SetPoint(i, asta3.GetPosPerno().GetX(), asta3.GetPosPerno().GetY());
		graph_y->SetPoint(i, asta3.GetPosEstremo().GetX(), asta3.GetPosEstremo().GetY());
		graph_theta->SetPoint(i, i, asta3.GetTheta());
	}
	asta3.Print();//stampo le info su asta3 alla fine del ciclo
	//disegno i due grafici
	c1->cd(1);
	mg_pos->Draw("ap");
	c1->cd(2);
	mg_ang->Draw("ap");
*/

/*	Gravity al secondo ordine
	//Parametri e condizioni iniziali: setting quickly
	//generale
	double dt = 0.0001 ;
	int Steps = 1000 ;
	//pendolo
	double massa = 0.1 ;
	double lunghezza = 1. ;
	double baricentro = 0.5 ;
	vect2d perno (0.,0.);
	vect2d vperno(.0, 0.);
	double theta = 1. + 3.14159265358979323846264338327950288/2. ;
	double veltheta = 2. ;
	
	
	bar asta3 (massa , lunghezza, baricentro, perno, theta, vperno, veltheta);
	cout << asta3 << endl;

	TApplication* theApp = new TApplication("App", &numArg, listArg);
	TCanvas *c1 = new TCanvas ("c1", "c1", 1000, 500);
	c1->Divide(2,1); 
	c1->cd(1)->SetGrid();
	c1->cd(2)->SetGrid();
	//disegno il primo grafico, in cui riporto la posizione del perno e dell'estermo
	TMultiGraph *mg_pos = new TMultiGraph();
	TGraph *graph_x = new TGraph ();
	TGraph *graph_y = new TGraph ();
	TGraph *graph_reaz = new TGraph();
	graph_x->SetMarkerStyle(20);
	graph_x->SetMarkerColor(kBlue);
	mg_pos->Add(graph_x);
	graph_y->SetMarkerStyle(20);
	graph_y->SetMarkerColor(kRed);
	mg_pos->Add(graph_y);
	graph_reaz->SetMarkerStyle(20);
	graph_reaz->SetMarkerColor(kGreen);
	mg_pos->Add(graph_reaz);
	mg_pos->SetTitle(" pendulum: perno, estremo e reazione vicolare ") ;
	//disegno il secondo grafico, in cui riporto il valore dell'angolo theta
	TMultiGraph *mg_ang = new TMultiGraph();
	TGraph *graph_theta = new TGraph ();
	graph_theta->SetMarkerStyle(20);
	graph_theta->SetMarkerColor(kBlue);
	mg_ang->Add(graph_theta);
	mg_ang->SetTitle (" angle ") ;
	//eseguo il ciclo, ovvero lascio che Gravity() agisca su asta3 per 100000 step dalla durata di 0.0001
	//a ogni step aggiorno entrambi i grafici
	for (int i=0; i<Steps ; i++ ) {
		asta3.Gravity(dt) ; 
		vect2d vincolo = asta3.Vincolo() ;
		graph_x->SetPoint(i, asta3.GetPosPerno().GetX(), asta3.GetPosPerno().GetY());
		graph_y->SetPoint(i, asta3.GetPosEstremo().GetX(), asta3.GetPosEstremo().GetY());
		graph_theta->SetPoint(i, i, asta3.GetTheta());
		graph_reaz->SetPoint (i, vincolo.GetX(), vincolo.GetY() );
	}
	asta3.Print();//stampo le info su asta3 alla fine del ciclo
	//disegno i due grafici
	c1->cd(1);
	mg_pos->Draw("ap");
	c1->cd(2);
	mg_ang->Draw("ap");

*/

/*Gravity vs GRavity1
	TStopwatch sw;

	//Parametri e condizioni iniziali: setting quickly
	//generale
	double dt = 0.0001 ;
	int Steps = 1000000 ;
	cout << "*Parametri*\n" << "dt: " << dt << endl 
				<< "Steps: " << Steps << endl << endl ;
	//pendolo
	double massa = 0.1 ;
	double lunghezza = 1. ;
	double baricentro = 0.5 ;
	vect2d perno (0.,0.);
	vect2d vperno(0., 0.);
	double theta = 1. + 3.14159265358979323846264338327950288/2. ;
	double veltheta = 2. ;
	
	//definizione oggetto bar: creo il pendolo
	bar asta (massa , lunghezza, baricentro, perno, theta, vperno, veltheta);
	bar asta1 (massa , lunghezza, baricentro, perno, theta, vperno, veltheta);
	cout << asta << endl;

	//oggetti base per la grafica
	TApplication* theApp = new TApplication("App", &numArg, listArg);
	TCanvas *c1 = new TCanvas ("c1", "c1", 1900, 1000);
	c1->Divide(2,2); 
	c1->cd(1)->SetGrid();
	c1->cd(2)->SetGrid();
	c1->cd(3)->SetGrid();
	c1->cd(4)->SetGrid();
	
	//Grivity(): approssimazione al secondo ordine sullalegge del moto	
	//disegno il primo grafico, in cui riporto la posizione del perno e dell'estermo
	TMultiGraph *mg_pos = new TMultiGraph();
	TGraph *graph_x = new TGraph ();
	TGraph *graph_y = new TGraph ();
	TGraph *graph_reaz = new TGraph();
	
	graph_x->SetMarkerStyle(20);
	graph_x->SetMarkerColor(kBlue);
	mg_pos->Add(graph_x);
	graph_y->SetMarkerStyle(20);
	graph_y->SetMarkerColor(kRed);
	mg_pos->Add(graph_y);
	graph_reaz->SetMarkerStyle(20);
	graph_reaz->SetMarkerColor(kGreen);
	mg_pos->Add(graph_reaz);
	mg_pos->SetTitle(" pendulum: perno, estremo e reazione vicolare ") ;

	//disegno il secondo grafico, in cui riporto il valore dell'angolo theta
	TMultiGraph *mg_ang = new TMultiGraph();
	TGraph *graph_theta = new TGraph ();
	graph_theta->SetMarkerStyle(20);
	graph_theta->SetMarkerColor(kBlue);
	mg_ang->Add(graph_theta);
	mg_ang->SetTitle (" angle ") ;

	//eseguo il ciclo, ovvero lascio che Gravity() agisca su asta per 100000 step dalla durata di 0.0001
	//a ogni step aggiorno entrambi i grafici
	sw.Start();
	for (int i=0; i<Steps ; i++ ) {
		asta.Gravity(dt) ; 		
		vect2d vincolo = asta.Vincolo() ;		
		graph_x->SetPoint(i, asta.GetPosPerno().GetX(), asta.GetPosPerno().GetY());
		graph_y->SetPoint(i, asta.GetPosEstremo().GetX(), asta.GetPosEstremo().GetY());
		graph_theta->SetPoint(i, i, asta.GetTheta());
		graph_reaz->SetPoint (i, vincolo.GetX(), vincolo.GetY() );
	}
	cout <<"Gravity()\n" ;
	std::cout << "CpuTime calculations\t" << sw.CpuTime() <<std::endl;
	std::cout << "RealTime calculations\t" << sw.RealTime() <<std::endl;
	sw.Reset();
	//stampo le info su asta alla fine del ciclo
	cout << asta1 << endl ; //	asta.Print();


	//---------
	//Gravity1(): approssimazione al primo ordine sulla legge del moto
	TMultiGraph *mg_pos1 = new TMultiGraph();
	TGraph *graph_x1 = new TGraph ();
	TGraph *graph_y1 = new TGraph ();
	TGraph *graph_reaz1 = new TGraph();

	//disegno il primo grafico, in cui riporto la posizione del perno e dell'estermo	
	graph_x1->SetMarkerStyle(20);
	graph_x1->SetMarkerColor(kBlue);
	mg_pos1->Add(graph_x1);
	graph_y1->SetMarkerStyle(20);
	graph_y1->SetMarkerColor(kRed);
	mg_pos1->Add(graph_y1);
	graph_reaz1->SetMarkerStyle(20);
	graph_reaz1->SetMarkerColor(kGreen);
	mg_pos1->Add(graph_reaz1);
	mg_pos1->SetTitle(" pendulum: perno, estremo e reazione vicolare (1)") ;

	//disegno il secondo grafico, in cui riporto il valore dell'angolo theta	
	TMultiGraph *mg_ang1 = new TMultiGraph();
	TGraph *graph_theta1 = new TGraph ();
	graph_theta1->SetMarkerStyle(20);
	graph_theta1->SetMarkerColor(kBlue);
	mg_ang1->Add(graph_theta1);
	mg_ang1->SetTitle (" angle (1) ") ;

	//eseguo il ciclo, ovvero lascio che Gravity() agisca su asta per 100000 step dalla durata di 0.0001
	//a ogni step aggiorno entrambi i grafici	
	sw.Start();
	for (int i=0; i<Steps ; i++ ) {
		asta1.Gravity1(dt) ; 		
		vect2d vincolo = asta1.Vincolo() ;		
		graph_x1->SetPoint(i, asta1.GetPosPerno().GetX(), asta1.GetPosPerno().GetY());
		graph_y1->SetPoint(i, asta1.GetPosEstremo().GetX(), asta1.GetPosEstremo().GetY());
		graph_theta1->SetPoint(i, i, asta1.GetTheta());
		graph_reaz1->SetPoint (i, vincolo.GetX(), vincolo.GetY() );
	}
	cout <<"Gravity1()\n" ;
	std::cout << "CpuTime calculations\t" << sw.CpuTime() <<std::endl;
	std::cout << "RealTime calculations\t" << sw.RealTime() <<std::endl;
	sw.Reset();
	//stampo le info su asta alla fine del ciclo
	cout << asta1 << endl ; //	asta.Print();

	//---------
	//disegno i quattro grafici
	sw.Start();
	c1->cd(1);
	mg_pos->Draw("ap");
	c1->cd(2);
	mg_ang->Draw("ap");
	c1->cd(3);
	mg_pos1->Draw("ap");
	c1->cd(4);
	mg_ang1->Draw("ap");
	cout <<"Rendering Grafico\n" ;
	std::cout << "CpuTime calculations\t" << sw.CpuTime() <<std::endl;
	std::cout << "RealTime calculations\t" << sw.RealTime() <<std::endl;
	sw.Reset();
*/

/*Gravity vs GravFriction
	TStopwatch sw;

	//Parametri e condizioni iniziali: setting quickly
	//generale
	double dt = 0.0001 ;
	int Steps = 300000 ;
	cout << "*Parametri*\n" << "dt: " << dt << endl 
				<< "Steps: " << Steps << endl << endl ;
	double coeff = 0.01 ;
	//pendolo
	double massa = 0.1 ;
	double lunghezza = 1. ;
	double baricentro = 0.5 ;
	vect2d perno (0.,0.);
	vect2d vperno(0., 0.);
	double theta = 1. + 3.14159265358979323846264338327950288/2. ;
	double veltheta = 2. ;
	
	//definizione oggetto bar: creo il pendolo
	bar asta (massa , lunghezza, baricentro, perno, theta, vperno, veltheta);
	bar asta1 (massa , lunghezza, baricentro, perno, theta, vperno, veltheta);
	cout << asta << endl;

	//oggetti base per la grafica
	TApplication* theApp = new TApplication("App", &numArg, listArg);
	TCanvas *c1 = new TCanvas ("c1", "c1", 1900, 1000);
	c1->Divide(2,2); 
	c1->cd(1)->SetGrid();
	c1->cd(2)->SetGrid();
	c1->cd(3)->SetGrid();
	c1->cd(4)->SetGrid();
	
	//Grivity(): approssimazione al secondo ordine sullalegge del moto	
	//disegno il primo grafico, in cui riporto la posizione del perno e dell'estermo
	TMultiGraph *mg_pos = new TMultiGraph();
	TGraph *graph_x = new TGraph ();
	TGraph *graph_y = new TGraph ();
	TGraph *graph_reaz = new TGraph();

	graph_x->SetMarkerStyle(20);
	graph_x->SetMarkerColor(kBlue);
	mg_pos->Add(graph_x);
	graph_y->SetMarkerStyle(20);
	graph_y->SetMarkerColor(kRed);
	mg_pos->Add(graph_y);
	graph_reaz->SetMarkerStyle(20);
	graph_reaz->SetMarkerColor(kGreen);
	mg_pos->Add(graph_reaz);
	mg_pos->SetTitle(" pendulum: perno, estremo e reazione vicolare ") ;

	//disegno il secondo grafico, in cui riporto il valore dell'angolo theta
	TMultiGraph *mg_ang = new TMultiGraph();
	TGraph *graph_theta = new TGraph ();
	graph_theta->SetMarkerStyle(20);
	graph_theta->SetMarkerColor(kBlue);
	mg_ang->Add(graph_theta);
	mg_ang->SetTitle (" angle ") ;

	//eseguo il ciclo, ovvero lascio che Gravity() agisca su asta per 100000 step dalla durata di 0.0001
	//a ogni step aggiorno entrambi i grafici
	sw.Start();
	for (int i=0; i<Steps ; i++ ) {
		asta.Gravity(dt) ; 		
		vect2d vincolo = asta.Vincolo() ;		
		graph_x->SetPoint(i, asta.GetPosPerno().GetX(), asta.GetPosPerno().GetY());
		graph_y->SetPoint(i, asta.GetPosEstremo().GetX(), asta.GetPosEstremo().GetY());
		graph_theta->SetPoint(i, i, asta.GetTheta());
		graph_reaz->SetPoint (i, vincolo.GetX(), vincolo.GetY() );
	}
	cout <<"Gravity()\n" ;
	std::cout << "CpuTime calculations\t" << sw.CpuTime() <<std::endl;
	std::cout << "RealTime calculations\t" << sw.RealTime() <<std::endl;
	sw.Reset();
	//stampo le info su asta alla fine del ciclo
	cout << asta1 << endl ; //	asta.Print();


	//---------
	//Gravity1(): approssimazione al primo ordine sulla legge del moto
	TMultiGraph *mg_pos1 = new TMultiGraph();
	TGraph *graph_x1 = new TGraph ();
	TGraph *graph_y1 = new TGraph ();
	TGraph *graph_reaz1 = new TGraph();

	//disegno il primo grafico, in cui riporto la posizione del perno e dell'estermo	
	graph_x1->SetMarkerStyle(20);
	graph_x1->SetMarkerColor(kBlue);
	mg_pos1->Add(graph_x1);
	graph_y1->SetMarkerStyle(20);
	graph_y1->SetMarkerColor(kRed);
	mg_pos1->Add(graph_y1);
	graph_reaz1->SetMarkerStyle(20);
	graph_reaz1->SetMarkerColor(kGreen);
	mg_pos1->Add(graph_reaz1);
	mg_pos1->SetTitle(" pendulum: perno, estremo e reazione vicolare (1)") ;

	//disegno il secondo grafico, in cui riporto il valore dell'angolo theta	
	TMultiGraph *mg_ang1 = new TMultiGraph();
	TGraph *graph_theta1 = new TGraph ();
	graph_theta1->SetMarkerStyle(20);
	graph_theta1->SetMarkerColor(kBlue);
	mg_ang1->Add(graph_theta1);
	mg_ang1->SetTitle (" angle (1) ") ;

	//eseguo il ciclo, ovvero lascio che Gravity() agisca su asta per 100000 step dalla durata di 0.0001
	//a ogni step aggiorno entrambi i grafici	
	sw.Start();
	for (int i=0; i<Steps ; i++ ) {
		asta1.GravFriction(dt,coeff) ; 		
		vect2d vincolo = asta1.Vincolo() ;		
		graph_x1->SetPoint(i, asta1.GetPosPerno().GetX(), asta1.GetPosPerno().GetY());
		graph_y1->SetPoint(i, asta1.GetPosEstremo().GetX(), asta1.GetPosEstremo().GetY());
		graph_theta1->SetPoint(i, i, asta1.GetTheta());
		graph_reaz1->SetPoint (i, vincolo.GetX(), vincolo.GetY() );
	}
	cout <<"Gravity1()\n" ;
	std::cout << "CpuTime calculations\t" << sw.CpuTime() <<std::endl;
	std::cout << "RealTime calculations\t" << sw.RealTime() <<std::endl;
	sw.Reset();
	//stampo le info su asta alla fine del ciclo
	cout << asta1 << endl ; //	asta.Print();

	//---------
	//disegno i quattro grafici
	sw.Start();
	c1->cd(1);
	mg_pos->Draw("ap");
	c1->cd(2);
	mg_ang->Draw("ap");
	c1->cd(3);
	mg_pos1->Draw("ap");
	c1->cd(4);
	mg_ang1->Draw("ap");
	cout <<"Rendering Grafico\n" ;
	std::cout << "CpuTime calculations\t" << sw.CpuTime() <<std::endl;
	std::cout << "RealTime calculations\t" << sw.RealTime() <<std::endl;
	sw.Reset();
*/	

/* GravStabInverted()
	TStopwatch sw;

	//Parametri e condizioni iniziali: setting quickly
	//generale
	double dt = 0.0001 ;
	int Steps = 50000 ;
	cout << "*Parametri*\n" << "dt: " << dt << endl 
				<< "Steps: " << Steps << endl << endl ;
	double A = 0.2 ;
	double w = 50. ;
	//pendolo
	double massa = 0.1 ;
	double lunghezza = 1. ;
	double baricentro = 0.5 ;
	vect2d perno (0.,0.);
	vect2d vperno(0., 0.);
	double theta = 3.14159265358979323846264338327950288 + 0.1;
	double veltheta = 0.01 ;
	
	//definizione oggetto bar: creo il pendolo
	bar asta (massa , lunghezza, baricentro, perno, theta, vperno, veltheta);
	bar asta1 (massa , lunghezza, baricentro, perno, theta, vperno, veltheta);
	cout << asta << endl;

	//oggetti base per la grafica
	TApplication* theApp = new TApplication("App", &numArg, listArg);
	TCanvas *c1 = new TCanvas ("c1", "c1", 1900, 1000);
	c1->Divide(2,1); 
	c1->cd(1)->SetGrid();
	c1->cd(2)->SetGrid();
//	c1->cd(3)->SetGrid();
//	c1->cd(4)->SetGrid();
	
	//Grivity(): approssimazione al secondo ordine sullalegge del moto	
	//disegno il primo grafico, in cui riporto la posizione del perno e dell'estermo
	TMultiGraph *mg_pos = new TMultiGraph();
	TGraph *graph_x = new TGraph (); //perno
	TGraph *graph_y = new TGraph (); //estremo
//	TGraph *graph_reaz = new TGraph();

	graph_x->SetMarkerStyle(20);
	graph_x->SetMarkerColor(kBlue);
	mg_pos->Add(graph_x);
	graph_y->SetMarkerStyle(20);
	graph_y->SetMarkerColor(kRed);
	mg_pos->Add(graph_y);
//	graph_reaz->SetMarkerStyle(20);
//	graph_reaz->SetMarkerColor(kGreen);
//	mg_pos->Add(graph_reaz);
	mg_pos->SetTitle(" pendulum: perno (blu), estremo (rosso)") ;

	//disegno il secondo grafico, in cui riporto il valore dell'angolo theta
	TMultiGraph *mg_ang = new TMultiGraph();
	TGraph *graph_theta = new TGraph ();
	graph_theta->SetMarkerStyle(20);
	graph_theta->SetMarkerColor(kBlue);
	mg_ang->Add(graph_theta);
	mg_ang->SetTitle (" angle ") ;

	//eseguo il ciclo, ovvero lascio che Gravity() agisca su asta per 100000 step dalla durata di 0.0001
	//a ogni step aggiorno entrambi i grafici
	sw.Start();
	for (int i=0; i<Steps ; i++ ) {
		asta.GravStabVert(dt,i,A,w,theta,perno) ; 		
		//vect2d vincolo = asta.Vincolo() ;		
		graph_x->SetPoint(i, asta.GetPosPerno().GetX(), asta.GetPosPerno().GetY());
		graph_y->SetPoint(i, asta.GetPosEstremo().GetX(), asta.GetPosEstremo().GetY());
		graph_theta->SetPoint(i, i, asta.GetTheta());
		//graph_reaz->SetPoint (i, vincolo.GetX(), vincolo.GetY() );
	}
	cout <<"Gravity()\n" ;
	std::cout << "CpuTime calculations\t" << sw.CpuTime() <<std::endl;
	std::cout << "RealTime calculations\t" << sw.RealTime() <<std::endl;
	sw.Reset();
	//stampo le info su asta alla fine del ciclo
	cout << asta1 << endl ; //	asta.Print();


	//---------
	//disegno i quattro grafici
	sw.Start();
	c1->cd(1);
	mg_pos->Draw("ap");
	c1->cd(2);
	mg_ang->Draw("ap");
	c1->cd(3);
//	mg_pos1->Draw("ap");
	c1->cd(4);
//	mg_ang1->Draw("ap");
	cout <<"Rendering Grafico\n" ;
	std::cout << "CpuTime calculations\t" << sw.CpuTime() <<std::endl;
	std::cout << "RealTime calculations\t" << sw.RealTime() <<std::endl;
	sw.Reset();


	//print del canvas, estremamente lento
	sw.Start();	
	char img[64];
	sprintf(img,"cfr_Gr-v-Gr1_dt-%f_Steps-%d.gif",dt,Steps);
	c1->Print(img, "gif");
	cout <<"Print Canvas\n" ;
	std::cout << "CpuTime calculations\t" << sw.CpuTime() <<std::endl;
	std::cout << "RealTime calculations\t" << sw.RealTime() <<std::endl;
	sw.Reset();

*/


	theApp->Run();

	return 0;
}
