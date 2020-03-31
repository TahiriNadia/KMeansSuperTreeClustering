#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <boost/regex.hpp>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>

#ifdef _OPENMP
#include <omp.h>
#endif

#include "hgt_int.cpp"
#include "Super-trees.cc"


using namespace std;

struct TNode{
    int NoNoeud;
	char *seq;
	TNode * gauche;
	TNode * droit;
	int nbFils;
};


//==Prototypes des fonctions
int ExtraireDonneesLC(const char * chaine, char *champs, char * contenu);
void validation(int &intParam);
void validationAlpha(double &alpha);
void validationKmin(int intParam, int &kmin);

 void presenterProgramme(){
	printf ("Generate Tree similar\n");
	printf("Nadia Tahiri and Vladimir Makarenkov - Departement d'informatique - Universite du Quebec a Montreal\n");
 }


//=============================================================
//=========================== MAIN ============================
//=============================================================
int main(int nargs,char ** argv){

	// Déclaration et initialisation de variables
	#define INFINI 999999.99
	#define MaxRF 0
	double MaxLong=0;
	double MinLong = INFINI;
	double seuil;
	double epsilona = 0.00005;
	int n;
	char champs[100];
	char contenu[100];

	if(nargs < 2){
		printf("\nbad input..\nusage:%s {-simulation|-matrice|-tree}\n",argv[0]);
		exit(1);
	}

	if(ExtraireDonneesLC(argv[1],champs,contenu)==1){
		if(strcmp("tree",champs) == 0){
			fstream fichier(argv[2]);
			int intParam;
			double alpha;
			int kmin=0;
			int kmax=0;
			if(nargs==3){
				intParam = 1;
				alpha = 1;
				kmin = 2;
			}else if (nargs==4){
				intParam = atoi(argv[3]);
				validation(intParam);
				alpha = 1;
				validationKmin(intParam,kmin);
			}else if (nargs==5){
				intParam = atoi(argv[3]);
				validation(intParam);
				alpha = atof(argv[4]);
				validationAlpha(alpha);
				validationKmin(intParam,kmin);
			}else if (nargs==6){
				intParam = atoi(argv[3]);
				validation(intParam);
				alpha = atof(argv[4]);
				validationAlpha(alpha);
				kmin = atoi(argv[5]);
				validationKmin(intParam,kmin);
			}else if (nargs==7){
				intParam = atoi(argv[3]);
				validation(intParam);
				alpha = atof(argv[4]);
				validationAlpha(alpha);
				kmin = atoi(argv[5]);
				validationKmin(intParam,kmin);
				kmax = atoi(argv[6]);
			}else{
				if(nargs > 7){
					printf("\nbad input..\nusage:%s -tree nameFile [cluster_validity_index] [alpha] [kmin] [kmax]\n",argv[0]);
					exit(1);
				}
			}

			vector <string> mesTrees;
			int ligne = 1;
			char ** cl2 = new char*[4];
			for (int i=0;i<4;i++){
				cl2[i] = new char[10];
			}

			strcpy(cl2[0], "*");
			strcpy(cl2[1], "?");
			strcpy(cl2[2], "?");
			strcpy(cl2[3], "?");
			vector <int> tabIndices;
			if( !fichier ){
				cout << "File "<<argv[2]<<" no exist."<<endl;
			}else{
				while( !fichier.eof()){
					mesTrees.push_back("");//creation d'une ligne vide
					getline(fichier, mesTrees.back());//lecture d'une ligne du fichier
					ligne = mesTrees.size() - 1;//je recupere la taille du tableau (-1 pour la ligne 0)

					if(mesTrees[ligne].empty())//si la ligne est vide
						mesTrees.pop_back();//on la retire du tableau
				}
				tabIndices.push_back(mesTrees.size());
				if (kmax>mesTrees.size()-1||kmax<1){
					kmax=mesTrees.size()-1;
				}
				main_consense(cl2,tabIndices,mesTrees,intParam,alpha,kmin,kmax);

				//vider les vecteurs
				mesTrees.clear();
				tabIndices.clear();
			}
		}else if(strcmp("matrice",champs) == 0){
			if(nargs > 7){
				printf("\nbad input..\nusage:%s {-matrice} nameFile [cluster_validity_index] [alpha] [kmin] [kmax]\n",argv[0]);
				exit(1);
			}
			fstream fichier(argv[2]);
			int intParam = atoi(argv[3]);
			int alpha = atof(argv[4]);
			int kmin = atoi(argv[5]);
			int kmax = atoi(argv[6]);
			validation(intParam);
			vector <string> mesTrees;
			char ** cl2 = new char*[4];
			for (int i=0;i<4;i++){
				cl2[i] = new char[10];
			}

			//Varriables
			double **Matrice_RF;
			double **Ww;
			double **n_identique;
			double *distances = new double[4];
			int n = 0; //taille de la matrice RF
			string contenu = "";


			strcpy(cl2[0], "*");
			strcpy(cl2[1], "?");
			strcpy(cl2[2], "?");
			strcpy(cl2[3], "?");
			vector <int> tabIndices;
			size_t pos = 0;
			string delimiter = "\n";
			string space = " ";
			string val = "";
			int ligne = 0;
			int colonne = 0;

			if( !fichier ){
				cout << "File "<<argv[2]<<" no exist."<<endl;
			}else{

				//lecture de la premiere ligne (taille de la matrice)
				getline(fichier, contenu);//lecture d'une ligne du fichier

				val = contenu.substr(0, contenu.find(delimiter));
				istringstream(val) >> n;

				Matrice_RF= new double*[n];
				Ww= new double*[n];
				n_identique= new double*[n];

				for(int lineDist=0;lineDist<n;lineDist++){
					Matrice_RF[lineDist]= new double[n];
					Ww[lineDist]= new double[n];
					n_identique[lineDist]= new double[n];
					mesTrees.push_back("");//creation d'une ligne vide
				}


				//Initialisation des matrices : Matrice_RF, Ww et n_identique
				for (int i=0; i<n; i++)
				{
					for (int j=0; j<n; j++)
					{
						Matrice_RF[i][j]=0.0;
						Ww[i][j]=1;
						n_identique[i][j]=n;
					}
				}

				while( !fichier.eof()){
					getline(fichier, contenu);//lecture d'une ligne du fichier
					colonne = 0;
					while ((pos = contenu.find(space))!= std::string::npos) {
						val = contenu.substr(0, pos);
						istringstream(val) >> Matrice_RF[ligne][colonne];

						contenu.erase(0, pos + space.length());
						colonne++;
					}
					ligne++;

				}
				tabIndices.push_back(n);

				int *n_leaves = new int[mesTrees.size()+1];
				//appel de l'algorithme de K-means:
				if(mesTrees.size()>3){
					main_kmeans(cl2,mesTrees,Matrice_RF,n_identique,Ww,tabIndices,intParam, n_leaves,kmin,kmax);
				}

				//vider les vectors
				mesTrees.clear();
				tabIndices.clear();

				//Liberation of memory
				for (int i=0;i<n;i++){
					delete [] Matrice_RF[i];
					delete [] Ww[i];
					delete [] n_identique[i];
				}
				delete [] Matrice_RF;
				delete [] Ww;
				delete [] n_identique;
				delete [] distances;
				for (int i=0;i<4;i++){
					delete [] cl2[i];
				}
				delete [] cl2;
			}
		}

	}
	printf("END OF PROGRAM!\n");
	return 0;
}

//=====================================================================
//
//=====================================================================
int ExtraireDonneesLC(const char * chaine, char *champs, char * contenu){

	int cpt=0;
	int tailleChaine;

	if(chaine[0] != '-'){
		return 0;
	}else{
		tailleChaine = (int)strlen(chaine);
		for(int i=0;i<tailleChaine;i++){
			champs[i] = chaine[i+1];
		}
	}

	return 1;
}

void validation(int &intParam){

	while(intParam<0 || intParam>2){
		cout<<"Invalid Parameter. Help (CH using by default). Help"<<endl;
		cout<<"Parameter 1: CH "<<endl;
		cout<<"Parameter 2: BH "<<endl;
		cout<<"Parameter 0: Exit "<<endl;
		intParam=1;
	}

	if(intParam==0){
		cout<<"Invalid Parameter. Help (CH using by default). Help"<<endl;
		cout<<"Parameter 1: CH (Calinski-Harabasz) "<<endl;
		cout<<"Parameter 2: BH (Ball-Hall)"<<endl;		
		cout<<"Parameter 0: Exit "<<endl;
		cout<<"====END OF PROGRAM!===="<<endl;
		exit(0);
	}
}

void validationAlpha(double &alpha){
	if(alpha<0){
		alpha=0;
	}else if(alpha>1){
		alpha=1;
	}
}

void validationKmin(int intParam, int &kmin){
	if(intParam==1 && kmin<1){
		kmin = 2;
	}
	if(intParam==2 && kmin<1){
		kmin = 1;
	}
}
