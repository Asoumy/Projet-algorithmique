#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct etat
			{
				int init;
				int fini;
				etat *succ;
			};
struct trans
		{
			char transition[2];
			etat *tete_etat;
			trans *succ;
		};
		typedef trans* TRANS;
		typedef etat* ETAT;

	TRANS automate()
	{
		//On commence donc par la construction de notre autumate

		int replicate(ETAT tete_etat,int init,ETAT tete_trans);
		char condition1 [4],condition2 [4];
		trans* tete_trans=NULL;
		trans *p_trans;
		etat *p_etat;
		trans* suiv=NULL;
		etat* ref=NULL;
		int l=0;
        printf("Bienvenue sur la creation de votre automate fini\n");
		do
		{
			p_trans= (trans*)malloc(sizeof (trans));

		printf("Donnez une transition a votre automate\n");
		scanf("%s",(*p_trans).transition);
		if (tete_trans==NULL) p_trans->tete_etat=NULL;
		else{ p_trans->tete_etat=tete_trans->tete_etat;
		ref=tete_trans->tete_etat;
		}
			do
			{
				p_etat=(etat*)malloc(sizeof (etat));

				do
				{
			printf("Donnez etat initial\n");
			scanf("%i",&(*p_etat).init);

			l=replicate(p_trans->tete_etat,p_etat->init,ref);
			if (l==1) printf("Il existe deja une transition commencant par cet etat initial\n");
				}
				while(l!=0);
			printf("Donnez etat final\n");
			scanf("%i",&(*p_etat).fini);
			p_etat->succ=p_trans->tete_etat;
				(*p_trans).tete_etat=p_etat;
			printf("Voulez vous ajouter d'autres etats pour cette transition ? (oui/non)\n");
			scanf("%s",condition1);
			l=strcmp(condition1,"non");
		    }
			while (l!=0);
			(*p_trans).succ=tete_trans;
				tete_trans=p_trans;

			printf("Voulez vous ajouter d'autres transitions a l'automate ? (oui/non)\n");
			scanf("%s",condition2);
			l=strcmp(condition2,"non");

		}
			while(l!=0);
			p_trans=tete_trans;

		do
		{
			suiv=p_trans->succ;

			do
			{
				printf("%s\t",p_trans->transition);
				printf("%i\t",p_etat->init);
				printf("%i\t",p_etat->fini);
				printf("\n");
				p_etat=p_etat->succ;
				if ((suiv==NULL)||(p_etat != suiv->tete_etat)) l=1;
				else l=0;
			}
			while ((p_etat!= NULL) &&  l!=0);
		p_trans=p_trans->succ;

		} while (p_etat != NULL);
		return (TRANS)tete_trans;
	}
		int replicate(etat *tete_etat,int init,etat* ref)
		{// Ici on verifie est ce qu'il y a une transition a une etat initiale identique à celui qu'on a juste tapez auparavant.
			int replicate=0;

			while ((tete_etat!=NULL) && (replicate==0) && (tete_etat!=ref))

			{
				if (tete_etat->init ==init) replicate=1;
				else tete_etat=tete_etat->succ;
			}

			return replicate;
		}
		char* mot()
		{
			//Ici on determine le mot qu'on va vérifier avec l'AFD.
			int nb,i;
			char *tab;
			printf("Donnez la taille de votre mot\n");
			scanf("%d",&nb);
			tab= (char *) malloc((nb+1)*sizeof(char));

			for(i=0;i<nb;i++)
			{
				printf("Donner les differentes lettre(s) une a une en appuyant a chaque fois sur entrer %d\n",i+1);
				scanf("%s",&tab[i]);
			}
			tab[nb]='\0';
			return &tab[0];

		}
		char check(char* adrtab,TRANS adrcombo)
		{
			int res=0,trouv=1,i=0;
			//Ici on vérifie l'appartenance du notre mot au language de notre automate.
			int etatinit,v=0;
			trans *ptrcombo=adrcombo;
			etat *ptretat;
			etat *ref=NULL;

			printf("Donner etat de depart\n");
			scanf("%i",&etatinit);


				while (res==0 && trouv==1)
			{
				  do
				  {
				  if ((*ptrcombo).transition[0]==adrtab[i]) {v=1;
															ptretat=ptrcombo->tete_etat;
															if (ptrcombo->succ != NULL)
															ref=(*ptrcombo).succ->tete_etat;
															}
				else ptrcombo=(*ptrcombo).succ;

			}

				while ((v!=1)&&( ptrcombo!=NULL));
				if (ptrcombo==NULL) trouv=5;
				else
				{
					i++;
					   do
				if ((*ptretat).init==etatinit) {v=2;
												etatinit=(*ptretat).fini;
											}
				else ptretat=(*ptretat).succ;
				while ((v!=2)&&( ptretat!=NULL)&&( ptretat!=ref));
				if ((ptretat==NULL)||( ptretat==ref)) trouv=0;
				else
		           if (adrtab[i]=='\0') res=1;
		           ptrcombo=adrcombo;
			   }

		   }


		  if (res==1) return etatinit;
		  else {
			  printf("Mot rejete vous n'avez pas assez de transitions ou celles-ci on ete mal faites\n");
			  return -1;
		  }
	   }
		int main()
		{
			//C'est la fonction main.
			char rep[3];
			int final[1],i,nb;
			TRANS k=automate();
			do
			{
			char* tab=mot();
			printf("Votre mot est %s. Passons au test ce celui-ci\n",tab);
			int s = check(tab,k);
			if (s!=-1)
			{
				printf("Donnez le nombre des etats finaux\n");
				scanf("%i",&nb);
			for(i=0;i<nb;i++)
			{
				printf("Donnez etat final %i\n",i+1);
				scanf("%i",&final[i]);
			}

			do
			{
				i--;
				if (s==final[i]) printf("Mot Accepte\n");
			}
			while ((i>=0)&&(s!=final[i]));
			if (i<0) printf("\nMot rejete !!!!!!");
		}
		printf("Voulez vous essayez un autre mot ? (oui/non)\n");
		scanf("%s",rep);
	}
		while(strcmp(rep,"non")!=0);
			return 0;
		}
