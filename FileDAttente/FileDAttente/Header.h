#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SMIN 4
#define SMAX 5
#define TEMPSSIMULATION 10
#define MAXTAB 5000
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
void trierTabStations(int s);
void gestionCoupUnitaire(void);
void calculCout(int iCout);
void parcourirFiles(int iStations);
void ParcoursTabStations(int s);
void VerifEjectionClient(int iStations);
void affichageStations(int s);
void affichageFilesPrior(void);
void affichageFilesOrdinaire(void);
void affichageFilesOrdinaireEject(void);

enum TypeClient { PRIOR = 1, ORDINAIRE = 2, VIDE = 3 };
typedef struct stations Stations;
struct stations {
	int typeClient;
	int dureeService;
	int tempsOccupation;
	int tempsInoccupation;
};