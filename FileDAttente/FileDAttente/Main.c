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
void parcourirFils(void);
void VerifEjectionClient(void);

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
	int  s, temps, tempsOccupPrior, tempsOccupOrd, nbArrivees, iArrivee, iStations;

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
			trierTab(TabStations);
			while (iStations < s) {
				if (TabStations[iStations].typeClient == 0) {
					parcourirFils();
				}
				else {
					VerifEjectionClient();
				}
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
		TabStations[i].typeClient = 0;
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

}

void calculCout(void) {

}

void parcourirFils(void) {

}

void VerifEjectionClient(void) {

}