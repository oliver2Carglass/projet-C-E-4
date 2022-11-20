#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"
#include "tree.h"
#include "Functions.h"
#include <unistd.h>
#define BUFFER_SIZE 100
#include <time.h>
#define BUFFER_SIZE 100


int main() {


    char test[size_word]="";
    t_tree temp_tree;
    p_letter_node temp_node;

    int random;
    char directory_dico[size_word] ="C:\\Users\\jerem\\CLionProjects\\projet c UwU\\dico.txt"; // PUT ABSOLUTE PATH HERE OF dico.txt

    int buffer=0;
    t_groot g =create_tree(directory_dico);
    while(buffer!=5)
    {
        printf("\n###########################\n");
        printf("Que souhaitez-vous faire ?\n\n");
        printf("1 : generer un mot aleatoire \n");
        printf("2 : generer une phrase aleatoire \n");
        printf("3 : chercher un mot \n");
        printf("4 : generer une phrase \n");
        printf("5 : quitter le programme\n");
        scanf("%d",&buffer);
        switch(buffer)
        {
            case 1:
                srand(time(NULL));
                random=rand()%4;
                switch(random)
                {
                    case 1: temp_tree=*g.Verb_tree;
                    case 2: temp_tree=*g.Adj_tree;
                    case 3: temp_tree=*g.Adv_tree;
                    case 4: temp_tree=*g.Nom_tree;
                }
                temp_node=random_word(temp_tree);
                printf("\nle mot aleatoire est: %s\n",temp_node->end_word->base_word);
                break;
            case 2:
                srand(time(NULL));
                random_base_sentence(g,test);
                printf("\nPhrase aleatoire: %s\n",test);
                break;
            case 3:
                find_word(g,directory_dico);
                break;

            case 4:
            {
                srand(time(NULL));
                random_variate_sentence(g,test);
                printf("%s\n",test);
                break;
            }
            case 5:
                printf("Le programme est ferme avec succes!\n");
                break;
            default:
                printf("Merci de rentrer un nombre valide\n");
        }
        for (int k = 0; k < size_word; k++)
        {
            test[k] = 0; // vide la chaine de caractere test
        }
    }

    return 0;
}
