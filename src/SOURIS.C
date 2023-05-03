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

#include "souris.h"

/* Initialisation de la souris pour le mode texte et le mode 13h*/
void Initialiser_Souris(void)
{
	word ResX,ResY;
	ResX=InfoMode.ResX-1;
	ResY=InfoMode.ResY-1;

	asm {
			mov ax,00h	//Initialise la souris
			int 33h
		}
	Zone_Deplacement(0,0,ResX,ResY);
}

/* Initialisation de la souris pour les modes SVGA
	ATTENTION : Il faut d'abord charger le sprite du curseur
	avec la commande Charger_Curseur("Curseur.BMP")				*/
void Initialiser_Souris_SVGA(void)
{
	word ResX,ResY;
	ResX=InfoMode.ResX-Curseur.Largeur;
	ResY=InfoMode.ResY-Curseur.Hauteur;
	asm {
			mov ax,00h	//Initialise la souris
			int 33h
		}

	Zone_Deplacement(0,0,ResX,ResY);
	Initialiser_FdCurseur();
}

/* Affiche le pointeur de la souris dans le mode texte et 13h*/
void Show_Pointeur(void)
{
	asm {
			mov ax,01h
			int 33h
		}
}

/* Masque le pointeur de la souris dans le mode texte et 13h*/
void Hide_Pointeur(void)
{
	asm {
			mov ax,02h
			int 33h
		}
}

/* Retourne l'‚tat de la souris dans les variables globales : SourisX
															: SourisY
															: Boutons*/
void Etat_Souris(void)
{
/* Boutons = 0 -> pas de bouton appuy‚
			 1 -> Bouton gauche appuy‚
			 2 -> Bouton droit appuy‚
			 3 -> Bouton gauche et droit appuy‚s */
	asm {
			mov ax,03h
			int 33h
			mov SourisX,cx
			mov SourisY,dx
			mov Boutons,bx
		}
}

/* Deplace le curseur aux coordonn‚es X,Y */
void Deplacer_Souris(unsigned int X,unsigned int Y)
{
	asm {
			mov ax,04h
			mov cx,X
			mov dx,Y
			int 33h
		}
}

/* Definit la valeur minimal en X et la valeur maximal en X*/
void Definir_Largeur(word MinX,word MaxX)
{
	asm {
			mov ax,07h
			mov cx,MinX
			mov dx,MaxX
			int 33h
		}
}

/* Definit la valeur minimal en Y et la valeur maximal en Y*/
void Definir_Hauteur(word MinY,word MaxY)
{
	asm {
			mov ax,08h
			mov cx,MinY
			mov dx,MaxY
			int 33h
		}
}

/* Definit un zone d'exclusion pour l'affichage de la souris pour le mode
	texte et 13h*/
void Zone_Exclusion(int X1,int Y1,int X2,int Y2)
{
	asm {
			mov ax,10h
			mov cx,X1
			mov dx,Y1
			mov si,X2
			mov di,Y2
			int 33h
		}
}

/* Definit le num‚ro de page ‚cran pour le mode texte et 13h*/
void Definir_NumPage(int Num)
{
	asm {
			mov ax,1dh
			mov bx,Num
			int 33h
		}
}

/* Lit le num‚ro de page ‚cran pour le mode texte et 13h*/
int Lire_NumPage(void)
{
	int Num;
	asm {
			mov ax,1eh
			mov Num,bx
			int 33h
		}
	return Num;
}

/*Definit la zone ou le deplacement est autoris‚*/
void Zone_Deplacement(int X1,int Y1,int X2,int Y2)
{
	Definir_Largeur(X1,X2);
	Definir_Hauteur(Y1,Y2);
}

/*Initialise le fond du curseur*/
void Initialiser_FdCurseur(void)
{
	int x,y;

	for(y=0;y<FdCurseur.Hauteur;y++)
		for(x=0;x<FdCurseur.Largeur;x++)
			FdCurseur.Data[y*FdCurseur.Largeur+x]=Prendre_Point(SourisX+x,SourisY+y);

}

/*Definit une zone d'action 255 zones maimum peuvent ˆtre defnit*/
void Zone(unsigned int X1,unsigned int Y1,unsigned int X2,unsigned int Y2,byte Boutons,byte Num)
{
	TabZone[0][Num]=X1;
	TabZone[1][Num]=Y1;
	TabZone[2][Num]=X2;
	TabZone[3][Num]=Y2;
	TabZone[4][Num]=Boutons;
}

/*Test, si une zone est active*/
byte TestZone(byte Num)
{
	Etat_Souris();
	if((SourisX>=TabZone[0][Num]) & (SourisY>=TabZone[1][Num]) &
	  (SourisX<=TabZone[2][Num]) & (SourisY<=TabZone[3][Num]) &
	  (Boutons==TabZone[4][Num])) return(1);
	else return(0);
}

/*Afficher le pointeur de la souris graphique*/
void Afficher_Souris(void)
{
	int x,y,OldX,OldY;

	OldX=SourisX;
	OldY=SourisY;

	Etat_Souris();

	if((SourisX!=OldX) || (SourisY!=OldY))
	{
		Afficher_Image(OldX,OldY,FdCurseur);
		for(y=0;y<FdCurseur.Hauteur;y++)
			for(x=0;x<FdCurseur.Largeur;x++)
				FdCurseur.Data[y*FdCurseur.Largeur+x]=Prendre_Point(SourisX+x,SourisY+y);
//		FdCurseur=Prendre_Image(SourisX,SourisY,SourisX+Curseur.Largeur,SourisY+Curseur.Hauteur);
		Afficher_Sprite(SourisX,SourisY,Curseur);
	}
}

/*Efface le pointeur de la souris graphique*/
void Effacer_Souris(void)
{
	Afficher_Image(SourisX,SourisY,FdCurseur);
}

/*Charger le sprite sevant de cursuer*/
void Charger_Curseur(char *nom)
{
	Curseur=Charger_Sprite(nom);
	FdCurseur=Charger_Sprite(nom);
}
