/****************************************************************************/
/*	SOURIS V1.0     				    Derniere mise a jour le : 07/06/97  */
/****************************************************************************/
/* Programm‚ par ALTAR :												    */
/*		E-MAIL : altar@neuronnexion.fr									    */
/*		WWW	   : http://www.neuronnexion.fr/~altar/main.htm				    */
/****************************************************************************/
/*	BibliothŠque Souris											            */
/*          															    */
/*	Options de compilation :											    */
/*  ------------------------                                                */
/*		Model 		    : Large											    */
/*		Floating Point  : 80287/387                                         */
/*		Instruction set : 80386                                             */
/****************************************************************************/
/* Tous conseils, remarques et commentaires sont les bienvenus				*/
/****************************************************************************/
#define byte unsigned char

unsigned int SourisX,SourisY,Boutons;
unsigned int TabZone[5][255];

Sprite Curseur,FdCurseur;

/* Initialisation de la souris pour le mode texte et le mode 13h*/
void Initialiser_Souris(void);
/* Initialisation de la souris pour les modes SVGA
	ATTENTION : Il faut d'abord charger le sprite du curseur
	avec la commande Charger_Curseur("Curseur.BMP")				*/
void Initialiser_Souris_SVGA(void);
/* Affiche le pointeur de la souris dans le mode texte et 13h*/
void Show_Pointeur(void);
/* Masque le pointeur de la souris dans le mode texte et 13h*/
void Hide_Pointeur(void);
/* Retourne l'‚tat de la souris dans les variables globales : SourisX
															: SourisY
															: Boutons*/
void Etat_Souris(void);
/* Deplace le curseur aux coordonn‚es X,Y */
void Deplacer_Souris(unsigned int X,unsigned int Y);
/* Definit la valeur minimal en X et la valeur maximal en X*/
void Definir_Largeur(unsigned int MinX,unsigned int MaxX);
/* Definit la valeur minimal en Y et la valeur maximal en Y*/
void Definir_Hauteur(unsigned int MinY,unsigned int MaxY);
/* Definit un zone d'exclusion pour l'affichage de la souris pour le mode
	texte et 13h*/
void Zone_Exclusion(int X1,int Y1,int X2,int Y2);
/* Definit le num‚ro de page ‚cran pour le mode texte et 13h*/
void Definir_NumPage(int Num);
/* Lit le num‚ro de page ‚cran pour le mode texte et 13h*/
int Lire_NumPage(void);
/*Definit la zone ou le deplacement est autoris‚*/
void Zone_Deplacement(int X1,int Y1,int X2,int Y2);
/*Initialise le fond du curseur*/
void Initialiser_FdCurseur(void);
/*Definit une zone d'action 255 zones maimum peuvent ˆtre defnit*/
void Zone(unsigned int X1,unsigned int Y1,unsigned int X2,unsigned int Y2,byte Boutons,byte Num);
/*Test, si une zone est active*/
byte TestZone(byte Num);
/*Afficher le pointeur de la souris graphique*/
void Afficher_Souris(void);
/*Efface le pointeur de la souris graphique*/
void Effacer_Souris(void);
/*Charge le sprite servant de curseur*/
void Charger_Curseur(char *nom);
