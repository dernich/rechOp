#include "Header.h"

int TabPrior[MAXTAB];
int TabOrdinaire[MAXTAB];
int TabOrdinaireEjecte[MAXTAB];
Stations TabStations[MAXTAB];
int TabCouts[26];

unsigned int x0 = 123456789;
int nbPrior = 0;
int nbNormal = 0;
int tempsOccupPrior, tempsOccupOrd;

void main(void) {
	printf("********************DEBUT**********************\n");
	int  s, temps, nbArrivees, iArrivee, iStations;
	int DS = 0;

	for (int i = 0; i < 26; i++) {
		TabCouts[i] = 0;
	}
	int iCout = 0;
	s = SMIN;
	while (s < SMAX) {

		initFilesEtStations();
		temps = tempsOccupPrior = tempsOccupOrd = 0;
		int iO = 0, iP = 0;

		while (temps < TEMPSSIMULATION) {

			nbArrivees = genererArrivees();
			if (s == 4 || s == 5 && temps <= 30) {
				printf("Nb arrivées : %d\n", nbArrivees);
			}
			for (int iArrivees = 0; iArrivees < nbArrivees; iArrivees++) {
				DS = genererDS();
				printf("\tDS : %d\n", DS);
				double u_n = x0 / M;
				if (u_n < 0.2) {
					TabPrior[iP] = DS;
					printf("\tTypeClient : %d\n", PRIOR);
					iP++;
					nbPrior++;
				}
				else {
					TabOrdinaire[iO] = DS;
					printf("\tTypeClient : %d\n", ORDINAIRE);
					iO++;
					nbNormal++;
				}
				x0 = (A * x0 + C);
			}
			//printf("pourc de prior : %.2f pour un total d'arrivee de %d", ((double)nbPrior / (nbNormal + nbPrior)) * 100, (nbNormal + nbPrior));
			
			trierFiles(TabOrdinaire);
			trierFiles(TabPrior);
			trierFiles(TabOrdinaireEjecte);

			affichageFilesPrior();
			affichageFilesOrdinaireEject();
			affichageFilesOrdinaire();

			iStations = 0;
			
			while (iStations < s) {
				if (TabStations[iStations].typeClient == VIDE) {
					parcourirFiles(iStations);
				}
				/*else {
					VerifEjectionClient(iStations);
				}*/
				
				iStations++;
			}
			trierTabStations(s);
			affichageStations(s);
			ParcoursTabStations(s);
			/*gestionCoupUnitaire();*/
			temps++;
		}
		/*calculCout(iStations, iCout);
		iCout++;*/
		s++;
	}
	system("pause");
}

void initFilesEtStations(void) {
	int i;
	for (i = 0; i < MAXTAB; i++) {
		TabOrdinaire[i] = 10;
		TabOrdinaireEjecte[i] = 10;
		TabPrior[i] = 10;
		TabStations[i].dureeService = 0;
		TabStations[i].typeClient = VIDE;
		TabStations[i].tempsOccupation = 0;
		TabStations[i].tempsInoccupation = 0;
	}
}

int genererArrivees(void) {
	x0 = (A * x0 + C);
	//printf("m : %f\n", M);
	//printf("X0 : %u\n", x0);
	double u_n = (double)x0 / M;
	//printf("U_n : %lf\n", u_n);
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

void trierFiles(int tab[]) {
	int i = 0;
	int tmp = 0;
	int j = 0;

	for (i = 0; i < MAXTAB; i++) {
		for (j = i + 1; j < MAXTAB; j++) {                  
			if (tab[j] < tab[i]) {
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
		}
	}
}

void trierTabStations(int s) {
	int i = 0;
	Stations tmp;
	int j = 0;

	for (i = 0; i < s; i++) {
		for (j = i + 1; j < s; j++) {
			if (TabStations[j].typeClient > TabStations[i].typeClient) {
				tmp = TabStations[i];
				TabStations[i] = TabStations[j];
				TabStations[j] = tmp;
			}
		}
	}
}

void gestionCoupUnitaire() {

	int iP = 0;
	int iOrd = 0;

	while (TabPrior[iP] != 10)
	{
		tempsOccupPrior++;
		iP++;
	}

	while (TabOrdinaire[iOrd] != 10)
	{
		tempsOccupOrd++;
		iOrd++;
	}

	iOrd = 0;
	while (TabOrdinaireEjecte[iOrd] != 10)
	{
		tempsOccupOrd++;
		iOrd++;
	}
}

void calculCout(int s, int iCout) {
	int couts = ((tempsOccupPrior % 60) * CUPRIORABSOLU) + ((tempsOccupOrd % 60) * CUPRIORORD);

	int iStations = 0;
	while (iStations < s)
	{
		couts += ((TabStations[iStations].tempsOccupation % 60) * CUOCC) + ((TabStations[iStations].tempsInoccupation % 60) * CUINOCC);
		iStations++;
	}
	TabCouts[iCout] = couts;
	printf("\nCouts total pour %d stations : %d\n", s, couts);
}

void parcourirFiles(int iStations) {
	if (TabPrior[0] != 10) {								//**************************************
		TabStations[iStations].typeClient = PRIOR;				//**************************************
		TabStations[iStations].dureeService = TabPrior[0];	// Probleme a gerer pour quand on change de file
		for (int iDec = 0; iDec < MAXTAB-1; iDec++) {
			TabPrior[iDec] = TabPrior[iDec + 1];
		}
		TabPrior[MAXTAB - 1] = 10;
	}															//Il faut revenir au 1er element de la file
	else {														//Solutions possibles : 
		if (TabOrdinaireEjecte[0] != 10) {					//Retrier chaque fois la file ou utiliser un indice a incrementer mais indice different pour chaque file
			TabStations[iStations].typeClient = ORDINAIRE;
			TabStations[iStations].dureeService = TabOrdinaireEjecte[0];
			for (int iDec = 0; iDec < MAXTAB - 1; iDec++) {
				TabOrdinaireEjecte[iDec] = TabOrdinaireEjecte[iDec + 1];
			}
			TabOrdinaireEjecte[MAXTAB - 1] = 10;
		}
		else {
			if (TabOrdinaire[0] != 10) {
				TabStations[iStations].typeClient = ORDINAIRE;
				TabStations[iStations].dureeService = TabOrdinaire[0];
				for (int iDec = 0; iDec < MAXTAB - 1; iDec++) {
					TabOrdinaire[iDec] = TabOrdinaire[iDec + 1];
				}
				TabOrdinaire[MAXTAB - 1] = 10;
			}
		}
	}
}

void VerifEjectionClient(int iStations) {
	if (TabStations[iStations].typeClient == ORDINAIRE) {

		int iF = 0;
		while (TabOrdinaireEjecte[iF] != 10) {
			iF++;
		}
		TabOrdinaireEjecte[iF] = TabStations[iStations].dureeService;
	}
}

void ParcoursTabStations(int s) {
	int cpt = 0;
	while (cpt < s) {
		if (TabStations[cpt].typeClient == VIDE)
			TabStations[cpt].tempsInoccupation++;
		else {
			TabStations[cpt].tempsOccupation++;
			if (TabStations[cpt].typeClient == PRIOR) {
				tempsOccupPrior++;
			}
			else {
				tempsOccupOrd++;
			}
		}
		TabStations[cpt].dureeService--;
		if (TabStations[cpt].dureeService == 0) {
			TabStations[cpt].typeClient = VIDE;
		}
		cpt++;
	}
}

void affichageStations(int s) {
	printf("\nTableau de stations : \n");
	for (int i = 0; i < s; i++) {
		//if (TabStations[i].typeClient != VIDE) {
			printf("\tType de client a la station %d : %u\n", i,TabStations[i].typeClient);
			printf("\tDuree de service restante du client a la station %d : %u\n", i, TabStations[i].dureeService);
		//}
	}
	printf("\n\n");
}

void affichageFilesPrior(void) {
	printf("\nTableau de files prior : \n");
	for (int i = 0; i < MAXTAB; i++) {
		if (TabPrior[i] != 10) {
			printf("\tDuree de service du client prior %u\n", TabPrior[i]);
		}
	}
	printf("\n\n");
}

void affichageFilesOrdinaire(void) {
	printf("\nTableau de files ordinaire : \n");
	for (int i = 0; i < MAXTAB; i++) {
		if (TabOrdinaire[i] != 10) {
			printf("\tDuree de service du client ordinaire %u\n", TabOrdinaire[i]);
		}
	}
	printf("\n\n");
}

void affichageFilesOrdinaireEject(void) {
	printf("\nTableau de files ejecte : \n");
	for (int i = 0; i < MAXTAB; i++) {
		if (TabOrdinaireEjecte[i] != 10) {
			printf("\tDuree de service du client ejecte %u\n", TabOrdinaireEjecte[i]);
		}
	}
	printf("\n\n");
}