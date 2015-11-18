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
int TabCouts[2];
Stations TabStations[MAXTAB];


void main(void) {
	int  s, temps, tempsOccupPrior, tempsOccupOrd, nbArrivees, iArrivee, iStations, iFiles;
	TabCouts[0] = 0;
	TabCouts[1] = 0;

	s = SMIN;
	while (s < SMAX) {

		void initFilesEtStations();
		temps = tempsOccupPrior = tempsOccupOrd = 0;
		int iO = 0, iP = 0;

		while (temps < TEMPSSIMULATION) {

			nbArrivees = genererArrivees();
			iArrivee = 0;
			//Boucler sur nbArrivees, pour chacune => Générer Statut(0 : Prior, 1 : Ord) et DS, Ensuite placer dans le bon tableau
			while (iArrivee < nbArrivees) {
				//Génération statuts
				double nb = genererNbAleatoires();
				//Placer dans la bonne File
				if (nb < 0,2) {
					TabPrior[iP] = Ds;
					iP++;
				}
				else {
					TabOrdinaire[iO] = Ds;
					iO++;
				}
				iArrivee++;
			}
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

//int genererArrivees(void) {
//	//***************************************	A MODIFIER
//	unsigned static int x = 144;
//	unsigned int a = 17;
//	unsigned int c = 53;
//	unsigned int nbArrivees;
//	nbArrivees = (int)x / (UINT_MAX);
//	x = (a*x) + c;
//	return nbArrivees;
//}
double genererNbAleatoires(void) {
	//***************************************	A MODIFIER
	static int x = 144;
	int a = 17;
	int c = 53;
	double nbAleatoire;
	nbAleatoire = (double)x / (UINT_MAX);
	x = (a*x) + c;
	return nbAleatoire;
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

//void parcourirFiles(int iStations, int iFiles) {
	//if (TabPrior[iFiles] != 0) {								//**************************************
	//	TabStations[iStations].typeClient = PRIOR;				//**************************************
	//	TabStations[iStations].dureeService = TabPrior[iFiles];	// Probleme a gerer pour quand on change de file
	//}															//Il faut revenir au 1er element de la file
	//else {														//Solutions possibles : 
	//	if (TabOrdinaireEjecte[iFiles] != 0) {					//Retrier chaque fois la file ou utiliser un indice a incrementer mais indice different pour chaque file
	//		TabStations[iStations].typeClient = ORDINAIRE;
	//		TabStations[iStations].dureeService = TabPrior[iFiles];
	//	}
	//	else {
	//		if (TabOrdinaire[iFiles] != 0) {
	//			TabStations[iStations].typeClient = ORDINAIRE;
	//			TabStations[iStations].dureeService = TabPrior[iFiles];
	//		}
	//	}
	//}
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
		cpt ++;
	}
}