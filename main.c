#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"
#include "tree.h"
#include "Functions.h"
#include <windows.h>
#include <unistd.h>
#define BUFFER_SIZE 100


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"
#include "tree.h"
#include "Functions.h"
#include <windows.h>
#include <unistd.h>
#include <time.h>
#define BUFFER_SIZE 100


int main(int argc, char* argv[]) {
    //printf("argc = %d argv = %s \n",argc,*argv);
    char *directory_dico[TAILLE_MAX];
    find_dico(argv,&directory_dico);
    printf("%s\n",directory_dico);
    t_groot g =create_tree(directory_dico);
    p_letter_node temp;
    char test[TAILLE_MAX]="";
    srand(time(NULL));
    for (int i = 0; i < 30; i++){
        printf("%d ", rand() % 30);
    }
    printf("\n");
    random_base_sentence(g,test);
    printf("\nPhrase aleatoire: %s\n",test);

    //printf("%d", WordType("abjectement     abjectement     Adv"));
    /*
    t_tree t;
    t.root= CreateNode('!');
    AddSon(t.root,'a');
    AddSon(t.root,'b');
    AddSon(t.root,'c');
    AddSon(t.root->sons,'a');
    AddSon(t.root->sons->sons,'a');
    char test[100]="bleu\tbleu\tAdj:Mas+SG";
    Add_basic_word(test,t);
    char test2[100]="bleu";
    p_letter_node temp=Go_to(test2,t);
    char test3[100]="bleue\tbleu\tAdj:Fem+SG";
    add_variate_word(temp->end_word,test3);
    printf("%s\n",temp->end_word->variations_word[0].variation_bloc);*/

    /*p_letter_node temp;
    char test[TAILLE_MAX];
    strcpy(test,"stabilisant");
    temp=g.Verb_tree->root;
    for(int i=0;i<10;i++)
    {
        temp=temp->sons;
    }
    for(int i=0;i<temp->end_word->nb_variations;i++)
    {
        printf("Variation numero %d\n",i);
        printf("%s   %s\n",temp->end_word->variations_word[i].word,temp->end_word->variations_word[i].variation_bloc);
    }*/
    return 0;
}