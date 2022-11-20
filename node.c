#include <stdlib.h>
#include <stdio.h>
#include "node.h"

p_letter_node Create_Node(char c)
{
    p_letter_node new;
    new=malloc(sizeof(t_letter_node));
    new->nb_sons=0;
    new->letter=c;
    new->sons=NULL;//Pour chaque ajout de fils, nous allons realloc() pour augmenter la taille du tableau et optimiser la mémoire
    new->end_word=NULL;
    return new;
}

void DisplayNode(t_letter_node n)
{
    printf("Lettre du noeud: %c \n",n.letter);
    if (n.end_word == NULL)
    {
        printf("Ce noeud n'a pas de mot associe \n");
    }
    if(n.nb_sons==0)
    {
        printf("Ce noeud n'a pas de fils \n");
    }
    else
    {
        printf("\nFils du noeud: \n");
        for (int i=0;i<n.nb_sons;i++)
        {
            printf("%c ",n.sons[i].letter);
        }
        printf("\n");
    }
}

int Add_Son(p_letter_node p, char c)
{
    if (p->nb_sons==ALPHABET_SIZE)
    {
        //printf("Le noeud possede deja tout l'alphabet en fils, donc la lettre %c n'a pas ete ajoutee \n",c);
        return 0; //On renvoie 0 si la lettre n'a pas été ajoutée
    }
    if (p->nb_sons==0)
    {
        p->nb_sons++;
        p->sons= malloc(1*sizeof(t_letter_node));
        p->sons= Create_Node(c);
        //printf("Le noeud n'avait aucun fils, donc la lettre %c a ete ajoutee \n",c);
        return 1;//On renvoie 1 si la lettre a été ajoutée
    }
    int i=0;
    while(p->sons[i].letter!=c && i<p->nb_sons)
    {
        i++;
    }
    if(i==p->nb_sons)
    {
        p->nb_sons++;
        p->sons=realloc(p->sons,p->nb_sons*sizeof(t_letter_node));//On agrandit la taille du tableau dynamique sons de une case
        p->sons[p->nb_sons-1]= *Create_Node(c);
        //printf("Le noeud n'avait pas la lettre %c dans ses fils, la lettre a donc ete ajoutee\n",c);
        return 1;
    }
    else
    {
        //printf("Le noeud possedait deja la lettre: %c dans ses fils, la lettre n'a donc pas ete ajoutee \n",c);
        return 0;
    }
}
