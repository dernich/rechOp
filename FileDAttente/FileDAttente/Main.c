#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SMIN 4
#define SMAX 30
#define TEMPSSIMULATION 640
#define MAXTAB 80000
#define CUOCC 35
#define CUINOCC 20
#define CUPRIORABSOLU 40
#define CUPRIORORD 25
#define M pow(2,sizeof(unsigned int)*8)
#define A 17
#define C 53


void initFilesEtStations(void);
int genererArrivees(void);
int genererDS(void);
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
int TabCouts[2];

unsigned int x0 = 123456789;
int nbPrior = 0;
int nbNormal = 0;

void main(void) {
	/*int  s, temps, tempsOccupPrior, tempsOccupOrd, nbArrivees, iArrivee, iStations, iFiles;
	unsigned int DS = 0;
	unsigned int typeClient = VIDE;

	for (int y = 0; y < 20; y++) {
		nbArrivees = genererArrivees();
		printf("Nb arrivées : %d\n", nbArrivees);
		for (int i = 0; i < nbArrivees; i++) {
			DS = genererDS();
			printf("\tDS : %d\n", DS);
			typeClient = genererTypeClient();
			printf("\tTypeClient : %d\n", typeClient);
			x0 = (A * x0 + C);
		}
	}
	printf("pourc de prior : %.2f pour un total d'arrivee de %d", ((double)nbPrior / (nbNormal + nbPrior)) * 100, (nbNormal + nbPrior));
	system("pause");*/
	
	int  s, temps, tempsOccupPrior, tempsOccupOrd, nbArrivees, iArrivee, iStations, iFiles;
	unsigned int DS = 0;
	TabCouts[0] = 0;
	TabCouts[1] = 0;

	s = SMIN;
	while (s < SMAX) {

		void initFilesEtStations();
		temps = tempsOccupPrior = tempsOccupOrd = 0;
		int iO = 0, iP = 0;

		while (temps < TEMPSSIMULATION) {

			nbArrivees = genererArrivees();
			//printf("Nb arrivées : %d\n", nbArrivees);
			for (int iArrivees = 0; iArrivees < nbArrivees; iArrivees++) {
				DS = genererDS();
				//printf("\tDS : %d\n", DS);
				double u_n = x0 / M;
				if (u_n < 0.2) {
					TabPrior[iP] = DS;
					iP++;
					nbPrior++;
				}
				else {
					TabOrdinaire[iO] = DS;
					iO++;
					nbNormal++;
				}
				//printf("\tTypeClient : %d\n", typeClient);
				x0 = (A * x0 + C);
			}
			//printf("pourc de prior : %.2f pour un total d'arrivee de %d", ((double)nbPrior / (nbNormal + nbPrior)) * 100, (nbNormal + nbPrior));
			
			trierTab(TabOrdinaire);
			trierTab(TabPrior);
			trierTab(TabOrdinaireEjecte);
			iStations = 0;
			iFiles = 0;
			trierTab(TabStations);
			int iPrior = 0;
			int iOrd = 0;
			int iOrdEj = 0;
			while (iStations < s) {
				if (TabStations[iStations].typeClient == VIDE) {
					//parcourirFiles(iStations, iFiles);
					parcourirFiles(iStations, iPrior, iOrd, iOrdEj);
				}
				else {
					VerifEjectionClient(iStations);
				}
				iFiles++;
				//*****************			Ajouter un module pour parcourir le tableau des stations et diminuer le DS de chacun
				ParcoursTabStations(s, TabStations);
				iStations++;
			}
			gestionCoupUnitaire(tempsOccupPrior, tempsOccupOrd, TabCouts);
			temps++;
		}
		calculCout(iStations);
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
	x0 = (A * x0 + C);
	printf("m : %f\n", M);
	printf("X0 : %u\n", x0);
	double u_n = (double)x0 / M;
	printf("U_n : %lf\n", u_n);
	if (u_n < 0.09) {
		return 0;
	} 
	else {
		if (u_n < 0.13) {
			return 1;
		}
		else {
			if (u_n < 0.18) {
				return 2;
			}
			else {
				if (u_n < 0.71) {
					return 3;
				}
				else {
					if (u_n < 0.89) {
						return 4;
					}
					else {
						return 5;
					}
				}
			}
		}
	}
}

int genererDS(void) {
	double u_n = x0 / M;

	if (u_n < 0.03) {
		return 1;
	}
	else {
		if (u_n < 0.08) {
			return 2;
		}
		else {
			if (u_n < 0.11) {
				return 3;
			}
			else {
				if (u_n < 0.29) {
					return 4;
				}
				else {
					if (u_n < 0.61) {
						return 5;
					}
					else {
						return 6;
					}
				}
			}
		}
	}
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

void gestionCoupUnitaire(int tempsOccupPrior, int tempsOccupOrd, int Tab[]) {
	//***************************************	Ajouter le tableau des couts mais aussi faire le PP qui n'est pas encore fait
	int iP = 0;
	int iOrd = 0;

	while (TabPrior[iP] != 0)
	{
		tempsOccupPrior++;
		iP++;
	}

	while (TabOrdinaire[iOrd] != 0)
	{
		tempsOccupOrd++;
		iOrd++;
	}

	iOrd = 0;
	while (TabOrdinaireEjecte[iOrd] != 0)
	{
		tempsOccupOrd++;
		iOrd++;
	}

	TabCouts[0] += tempsOccupPrior;
	TabCouts[1] += tempsOccupOrd;
}

void calculCout(int s) {
	int couts = ((TabCouts[0] % 60) * CUPRIORABSOLU) + ((TabCouts[1] % 60) * CUPRIORORD);

	int iStations = 0;
	while (iStations < s)
	{
		couts += ((TabStations[iStations].tempsOccupation % 60) * CUOCC) + ((TabStations[iStations].tempsInoccupation % 60) * CUINOCC);
		iStations++;
	}

	printf_s("%s", "Couts : " + couts);
}

void parcourirFiles(int iStations, int iP, int iO, int iOE) {
	if (TabPrior[iP] != 0) {								//**************************************
		TabStations[iStations].typeClient = PRIOR;				//**************************************
		TabStations[iStations].dureeService = TabPrior[iP];	// Probleme a gerer pour quand on change de file
		iP++;
	}															//Il faut revenir au 1er element de la file
	else {														//Solutions possibles : 
		if (TabOrdinaireEjecte[iOE] != 0) {					//Retrier chaque fois la file ou utiliser un indice a incrementer mais indice different pour chaque file
			TabStations[iStations].typeClient = ORDINAIRE;
			TabStations[iStations].dureeService = TabPrior[iOE];
			iOE++;
		}
		else {
			if (TabOrdinaire[iO] != 0) {
				TabStations[iStations].typeClient = ORDINAIRE;
				TabStations[iStations].dureeService = TabPrior[iO];
				iO++;
			}
		}
	}
}

void VerifEjectionClient(int iStations) {
	if (TabStations[iStations].typeClient == ORDINAIRE) {
		//Faire l'ejection du client
		int iF = 0;
		while (TabOrdinaireEjecte[iF] != 0) {
			iF++;
		}
		TabOrdinaireEjecte[iF] = TabStations[iStations].dureeService;
	}
}

void ParcoursTabStations(int s, Stations tab[]) {
	int cpt = 0;
	while (cpt < s) {
		if (TabStations[cpt].typeClient == VIDE)
			TabStations[cpt].tempsInoccupation++;
		else
			TabStations[cpt].tempsOccupation++;
		TabStations[cpt].dureeService--;
		cpt++;
	}
}