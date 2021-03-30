/*
	Inverted Pendulum Simulation
	g++ -o pend vect2d.cc bar.cc pend.cpp `root-config --cflags --glibs`
	sistemare .cc GravStabVert	
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
#include "TStopwatch.h"

//personali
#include"vect2d.h"
#include"bar.h"

using namespace std;
//#define N 123

int main (int numArg, char * listArg[])
{
	TStopwatch sw;

	//Parametri e condizioni iniziali: setting quickly
	//generale
	double dt = 0.0001 ;
	int Steps = 49750 ;
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
	double veltheta = 1. ;
	
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
//	c1->cd(4)->SetGrid();
	
	//Grivity(): approssimazione al secondo ordine sullalegge del moto	
	//disegno il primo grafico, in cui riporto la posizione del perno e dell'estermo
	TMultiGraph *mg_pos = new TMultiGraph();
	TGraph *graph_x = new TGraph (); //perno
	TGraph *graph_y = new TGraph (); //estremo


	graph_x->SetMarkerStyle(20);
	graph_x->SetMarkerColor(kBlue);
	mg_pos->Add(graph_x);
	graph_y->SetMarkerStyle(20);
	graph_y->SetMarkerColor(kRed);
	mg_pos->Add(graph_y);
	mg_pos->SetTitle("pendulum: trajectories of the pivot (blue) and the extreme (red) (y vs x)") ;

	//disegno il secondo grafico, in cui riporto il valore dell'angolo theta
	TMultiGraph *mg_ang = new TMultiGraph();
	TGraph *graph_theta = new TGraph ();
	graph_theta->SetMarkerStyle(20);
	graph_theta->SetMarkerColor(kBlue);
	mg_ang->Add(graph_theta);
	mg_ang->SetTitle (" angle (theta vs time) ") ;

	//disegno il terzo grafico: spazio fasi theta vs veltheta
	TMultiGraph *mg_phase = new TMultiGraph();	
	TGraph *graph_phase = new TGraph(); //theta_p vs veltheta_p
//	graph_phase->SetMarkerStyle(20);
	graph_phase->SetMarkerColor(kGreen);
	mg_phase->Add(graph_phase);
	mg_phase->SetTitle("Phase Space (d(theta)/dt vs theta)");
	
	//eseguo il ciclo, ovvero lascio che Gravity() agisca su asta per 100000 step dalla durata di 0.0001
	//a ogni step aggiorno entrambi i grafici
	sw.Start();
	for (int i=0; i<Steps ; i++ ) {
		asta.GravStabVert(dt,i,A,w,theta,perno) ; 	
//		asta.GravStabVert(dt,i,A,w,theta,perno) ;	
		graph_x->SetPoint(i, asta.GetPosPerno().GetX(), asta.GetPosPerno().GetY());
		graph_y->SetPoint(i, asta.GetPosEstremo().GetX(), asta.GetPosEstremo().GetY());
		graph_theta->SetPoint(i, i, asta.GetTheta());
		graph_phase->SetPoint(i, asta.GetTheta(), asta.GetVelTheta());
	}
	cout <<"GravStabVert()\n" ;
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
	mg_phase->Draw("ap");
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

	// theApp->Run();


	return 0;
}
