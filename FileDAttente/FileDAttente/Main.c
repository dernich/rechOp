#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SMIN 4
#define SMAX 30
#define TEMPSSIMULATION 640
#define MAXTAB 80000

void initFilesEtStations(void);
int genererArrivees(void);
void trierFiles(int tab[]);
void gestionCoupUnitaire(void);
void calculCout(void);
void parcourirFiles(int iStations, int iFiles);
void VerifEjectionClient(int iStations);

enum TypeClient { PRIOR = 1, ORDINAIRE = 2, VIDE = 3 };
typedef struct stations Stations;
struct stations {
	int typeClient;
	int dureeService;
	int tempsOccupation;
	int tempsInoccupation;
};

int TabPrior[MAXTAB];
int TabOrdinaire[MAXTAB];
int TabOrdinaireEjecte[MAXTAB];
Stations TabStations[MAXTAB];


void main(void) {
	int  s, temps, tempsOccupPrior, tempsOccupOrd, nbArrivees, iArrivee, iStations, iFiles;

	s = SMIN;
	while (s < SMAX) {

		void initFilesEtStations();
		temps = tempsOccupPrior = tempsOccupOrd = 0;

		while (temps < TEMPSSIMULATION) {

			nbArrivees = genererArrivees();
			iArrivee = 0;

			while (iArrivee < nbArrivees) {

				iArrivee++;
			}
			trierTab(TabOrdinaire);
			trierTab(TabPrior);
			trierTab(TabOrdinaireEjecte);
			iStations = 0;
			iFiles = 0;
			trierTab(TabStations);
			while (iStations < s) {
				if (TabStations[iStations].typeClient == VIDE) {
					parcourirFiles(iStations, iFiles);
				}
				else {
					VerifEjectionClient(iStations);
				}
				iFiles++;
				//*****************			Ajouter un module pour parcourir le tableau des stations et diminuer le DS de chacun
				iStations++;
			}
			gestionCoupUnitaire();
			temps++;
		}
		calculCout();
		s++;
	}
}

void initFilesEtStations(void) {
	int i;
	for (i = 0; i < MAXTAB; i++) {
		TabOrdinaire[i] = 0;
		TabOrdinaireEjecte[i] = 0;
		TabPrior[i] = 0;
		TabStations[i].dureeService = 0;
		TabStations[i].typeClient = VIDE;
		TabStations[i].tempsOccupation = 0;
		TabStations[i].tempsInoccupation = 0;
	}
}

int genererArrivees(void) {

}

void trierTab(int tab[]) {
	int i = 0;
	int tmp = 0;
	int j = 0;

	for (i = 0; i < sizeof(tab); i++) {
		for (j = i + 1; j < sizeof(tab); j++) {                  
			if (tab[j] < tab[i]) {
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
		}
	}
}

void gestionCoupUnitaire(void) {
	//***************************************	Ajouter le tableau des couts mais aussi faire le PP qui n'est pas encore fait
}

void calculCout(void) {

}

void parcourirFiles(int iStations, int iFiles) {
	if (TabPrior[iFiles] != 0) {								//**************************************
		TabStations[iStations].typeClient = PRIOR;				//**************************************
		TabStations[iStations].dureeService = TabPrior[iFiles];	// Probleme a gerer pour quand on change de file
	}															//Il faut revenir au 1er element de la file
	else {														//Solutions possibles : 
		if (TabOrdinaireEjecte[iFiles] != 0) {					//Retrier chaque fois la file ou utiliser un indice a incrementer mais indice different pour chaque file
			TabStations[iStations].typeClient = ORDINAIRE;
			TabStations[iStations].dureeService = TabPrior[iFiles];
		}
		else {
			if (TabOrdinaire[iFiles] != 0) {
				TabStations[iStations].typeClient = ORDINAIRE;
				TabStations[iStations].dureeService = TabPrior[iFiles];
			}
		}
	}
}

void VerifEjectionClient(int iStations) {
	if (TabStations[iStations].typeClient == ORDINAIRE) {
		//Faire l'ejection du client
	}
}