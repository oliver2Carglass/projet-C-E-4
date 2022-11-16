//
// Created by raphb on 06/11/2022.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "Functions.h"
#include "tree.h"
#include <time.h>

int WordType(char sentence[TAILLE_MAX]) //prend une ligne et renvoie son type(verbe 1,adj 2,nom 3,adverbe 4,NULL 0 )
{
    char temp[TAILLE_MAX] = "";
    int cpt_temp = 0; //compteur buffer
    for (int i = 0; sentence[i] != '\0'; i++) {
        if(((sentence[i]!=':')&(sentence[i] != '\t')&(sentence[i] != ' '))&&sentence[i+1]!='\0') { //si le caractere n'est pas une une séparation (;,+\t) on l'ajoute le caractere au buffer temp{
            temp[cpt_temp] = sentence[i];
            cpt_temp++;
        }
        else{
            if(sentence[i+1]=='\0'){
                temp[cpt_temp] = sentence[i];
            }

            if (strcmp(temp, "Ver") == 0) {
                return 1; // on changera les nombres plus tard
            }
            if (strcmp(temp, "Adj") == 0) {
                return 2; // on changera les nombres plus tard
            }
            if (strcmp(temp, "Nom") == 0) {
                return 3; // on changera les nombres plus tard
            }
            if (strcmp(temp, "Adv") == 0) {
                return 4; // on changera les nombres plus tard
            }
        }
        if(sentence[i]=='\t'||sentence[i]==':'||sentence[i]==' '){
            cpt_temp = 0;
            for (int k = 0; k < TAILLE_MAX; k++) {
                temp[k] = 0; // le mot est terminé on reinitialise la le buffer temp à "" (vide)
            }
        }
    }
    if (strcmp(temp,"Adv\n") == 0)
    {
        return 4; // on changera les nombres plus tard
    }
    return 0;

}
p_letter_node Go_to(char word[TAILLE_MAX],t_tree t)
{
    int i,j;
    i=0,j=0;
    p_letter_node temp;
    temp=t.root;
    while(word[i] != '\0')
    {
        while(temp->nb_sons>0 && temp->sons[j].letter!=word[i] && j!=temp->nb_sons)
        {
            j++;
        }
        if (j==temp->nb_sons) //Si la lettre n'a pas été trouvée parmi les fils
        {
            //printf("La lettre %c n'a pas ete trouvee\n", word[i]);
            return NULL;
        }
        else
        {
            //printf("La lettre %c a ete trouvee\n", word[i]);
            temp=temp->sons+j; //On affecte à temp le fils qui contient la lettre suivante
            j=0;
        }
        i++;
    }
    return temp;
}


p_letter_node Add_basic_word(char sentence[TAILLE_MAX], t_tree t)
{
    p_letter_node temp;
    temp=t.root;
    int i=0;
    int j=0;
    char word[TAILLE_MAX];
    char variation[TAILLE_MAX];
    //On va extraire le mot à ajouter et la troisieme colonne de la phrase entière
    word_from_sentence(sentence,word);
    end_sentence(sentence,variation);
    //On s'occupe maintenant de l'ajout du mot end_word à l'arbre
    temp= Add_word_in_tree(t,word);
    temp->end_word=(p_end_word) malloc(sizeof(t_end_word));
    strcpy(temp->end_word->base_word,word);
    strcpy(temp->end_word->base_bloc,variation); // Pour ajouter le bloc des variations à la structure
    temp->end_word->nb_variations=0;
    temp->end_word->type= WordType(sentence);
    temp->end_word->variations_word=NULL;
}

p_letter_node Add_word_in_tree(t_tree t, char word[TAILLE_MAX])
{
    p_letter_node temp;
    temp=t.root;
    int i=0;
    int j=0;
    while(word[i] != '\0')
    {
        while(temp->nb_sons>0 && temp->sons[j].letter!=word[i] && j!=temp->nb_sons)
        {
            j++;
        }
        if (j==temp->nb_sons) //Si la lettre n'a pas été trouvée parmi les fils
        {
            //printf("La lettre %c n'a pas ete trouvee\n", word[i]);
            AddSon(temp, word[i]); //On ajoute la lettre qui n'a pas été trouvée dans les enfants
            temp=temp->sons+(temp->nb_sons-1); //On dirige temp dans cette lettre qui vient d'être ajoutée
            j=0;
        }
        else
        {
            //printf("La lettre %c a ete trouvee\n", word[i]);
            temp=temp->sons+j; //On affecte à temp le fils qui contient la lettre suivante
            j=0;
        }
        i++;
    }
    return temp;
}


int Wich_word(char sentence[TAILLE_MAX])
{
    char temp1[TAILLE_MAX] = "";
    char temp2[TAILLE_MAX] = "";
    int cpt=0;
    int space=0;
    for (int i = 0; space<2; i++)
    {
        if((sentence[i]==' ')  || (sentence[i]=='\t'))
        {
            space++;
            cpt=0;
        }
        else
        {
            if(space==0)
            {
                temp1[cpt] = sentence[i];
            }
            else
            {
                temp2[cpt]=sentence[i];
            }
            cpt++;
        }

    }
    //printf("temp1:%s temp2:%s",temp1,temp2);
    if (strcmp(temp1,temp2)==0)
    {
        return 1; //Mot basique
    }
    return 0;
}


void find_dico(char **argv,char *result){ //permet de retrouver le chemin du dico
    char dico_name[50]="dico.txt" ;//laisser les deux \ en cas de changement

    char buffer[50]="";
    char full_directory[50]="";//le chemin complet vers le .exe du programme
    char directory_dico[50]="";//chemin vers le dictionnaire
    int stop = 0;
    strcat(full_directory, *argv);
    //printf("full directory %s \n", full_directory);
    //printf("result = %s full directory = %s\n",result,full_directory);
    //printf("directory dico = %s",directory_dico);

    char temp[TAILLE_MAX] = "";
    int cpt = 0;
    int cpt_temp
    = 0;
    for (int i = 0; full_directory[i] != '\0'; i++) //on essaye de prendre seulement le début du chemin de full_directory
    {
        // printf("la lettre est %c \n", sentence[i]);
        if ((full_directory[i] == '\\')&(stop==0)) {
            if (strcmp(temp, "cmake-build-debug") == 0) {
                //printf("%s", directory_dico);
                strcat(directory_dico,dico_name);
                strcpy(result,directory_dico);

            }
            else {

                strcat(directory_dico,temp);
                cpt_temp = 0;
                strcat(directory_dico,"\\");
                for (int k = 0; k < TAILLE_MAX; k++) {
                    temp[k] = 0; // vide la chaine de caractere temp
                }
            }
        }
        else
        {
            temp[cpt_temp] = full_directory[i];
            cpt_temp++;
        }
        //printf("chaine = %s \n",directory_dico);
    }
}

void end_sentence(char sentence[TAILLE_MAX],char *word)
{
    char temp[TAILLE_MAX] = "";
    int cpt = 0;
    int cpt_temp = 0;
    int cpt_point = 0;

    for (int i = 0; sentence[i] != '\0'; i++){
        //Test
        // printf("la lettre est %c \n", sentence[i]);

        temp[cpt_temp] = sentence[i];
        cpt_temp++;


        if(( (sentence[i] == ':')&(cpt_point==0 ))){ //si le caractere n'est pas un mot
            cpt_point++;

            cpt_temp = 0;
            for (int k = 0; k < TAILLE_MAX; k++)
            {
                temp[k] = 0; // vide la chaine de caractere temp
            }
        }

    }
    strcpy(word,temp);

}

void word_from_sentence(char sentence[TAILLE_MAX],char *word)
{
    char temp[TAILLE_MAX] = "";

    for (int i = 0; sentence[i] != '\t'; i++)
        temp[i] = sentence[i];


    strcpy(word,temp);

}

t_groot create_tree(char file[TAILLE_MAX])
{
    t_groot t;
    p_tree temp_tree;
    t.Verb_tree=(p_tree)malloc(sizeof(t_tree));
    t.Adj_tree=(p_tree)malloc(sizeof(t_tree));
    t.Adv_tree=(p_tree)malloc(sizeof(t_tree));
    t.Nom_tree=(p_tree)malloc(sizeof(t_tree));
    t.Verb_tree->root= CreateNode('!');
    t.Adj_tree->root= CreateNode('!');
    t.Adv_tree->root= CreateNode('!');
    t.Nom_tree->root= CreateNode('!');

    FILE *fichier = NULL;
    char word[TAILLE_MAX]="";
    char temp_sentence[TAILLE_MAX]="";
    char base_word[TAILLE_MAX]="";
    char chaine[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX
    int spaces=0;
    int cpt_temp=0;
    fichier = fopen(file,"r");
    if (fichier != NULL)
       {
           while(fgets(chaine, TAILLE_MAX, fichier)!=NULL)
           {
               //printf("%s",chaine);
                if (WordType(chaine)==1)
                {
                    temp_tree=t.Verb_tree;
                }
                if (WordType(chaine)==2)
                {
                   temp_tree=t.Adj_tree;
                }
                if (WordType(chaine)==3)
                {
                   temp_tree=t.Nom_tree;
                }
                if (WordType(chaine)==4)
                {
                   temp_tree=t.Adv_tree;
                }
               if (WordType(chaine)==0)
               {
                   //printf("ERREUR! Impossible de detecter le type de mot dans la phrase\n");
                   //printf("%s",chaine);
               }
               else
               {
                   word_from_sentence(chaine,word);
                   if (Wich_word(chaine)==1) //Si on a affaire à un mot basique
                   {
                       if(Go_to(word,*temp_tree)==NULL)
                       {
                           Add_basic_word(chaine,*temp_tree);
                       }
                   }
                   else
                   {

                       add_variate_word(*temp_tree, chaine);

                   }
                   // On remet les chaines à vide
                   for (int k = 0; k < TAILLE_MAX; k++)
                   {
                       word[k] = 0;
                       base_word[k] = 0;
                       temp_sentence[k] = 0;
                   }
               }
           }
           fclose(fichier);
       }
    return t;
}


void add_variate_word(t_tree t,char sentence[TAILLE_MAX])
{
    p_end_word word;
    char temp[TAILLE_MAX] = "";
    int cpt_temp = 0;
    char word1[TAILLE_MAX];
    char word2[TAILLE_MAX];
    char base_word[TAILLE_MAX]="";
    int spaces=0;
    p_letter_node lastnode;
    //On récupère la deuxième colonne qu'on met dans base_word
    for (int i=0;spaces<2;i++)
    {
        if(sentence[i]==' '||sentence[i]=='\t')
            spaces++;
        else
        {
            if(spaces==1)
            {
                base_word[cpt_temp]=sentence[i];
                cpt_temp++;
            }
        }
    }
    end_sentence(sentence,word1);
    word_from_sentence(sentence,word2);
    //Si on a affaire à un mot fléchi alors que le mot de base n'a pas encore été ajouté
    if (Go_to(base_word,t)==NULL)
    {
        //Ajouter le mot de base dans l'arbre
        //printf("\n%s\n",base_word);
        lastnode=Add_word_in_tree(t,base_word);
        lastnode->end_word=(p_end_word)malloc(sizeof(t_end_word));
        strcpy(lastnode->end_word->base_word,base_word);
        lastnode->end_word->nb_variations=0;
        lastnode->end_word->type= WordType(sentence);
        if (lastnode->end_word->type==1)
        {
            strcpy(lastnode->end_word->base_bloc,"Inf");
        }
        else
        {
            strcpy(lastnode->end_word->base_bloc,"Mas+SG");
        }
    }
    else
    {
        lastnode=Go_to(base_word,t);
    }
    //Si on a une suite de lettre déjà présente dans un arbre mais pas de fin de mot définie
    if (lastnode->end_word==NULL)
    {
        lastnode->end_word=(p_end_word)malloc(sizeof(t_end_word));
        strcpy(lastnode->end_word->base_word,base_word);
        lastnode->end_word->nb_variations=0;
        lastnode->end_word->type= WordType(sentence);
        if (lastnode->end_word->type==1)
        {
            strcpy(lastnode->end_word->base_bloc,"Inf");
        }
        else
        {
            strcpy(lastnode->end_word->base_bloc,"Mas+SG");
        }
    }
    word=lastnode->end_word;
    if(word->nb_variations==0){
        word->nb_variations++;
        word->variations_word =(p_variation) malloc(word->nb_variations* sizeof(t_variation) );
    }
    else
    {
        word->nb_variations++;
        word->variations_word =(p_variation) realloc(word->variations_word,word->nb_variations* sizeof(t_variation) );
    }
    strcpy(word->variations_word[word->nb_variations-1].variation_bloc , word1);
    strcpy(word->variations_word[word->nb_variations-1].word,word2);
}

p_letter_node random_word(t_tree t)
{
    // Initialise le générateur pseudo-aléatoire
    p_letter_node temp;
    temp=t.root;
    printf("\n");
    while(temp->nb_sons>0)
    {
        printf("%d ",rand() %(temp->nb_sons));
        if(rand() %3==0)
        {
            if(temp->end_word!=NULL)
            {
                return temp;
            }
        }
        temp=temp->sons+(rand() %(temp->nb_sons));
    }
    return temp;

}

void random_base_sentence(t_groot g,char* word)
{
    // Initialise le générateur pseudo-aléatoire
    p_letter_node temp;
    char sentence[TAILLE_MAX]="";
    int random;
    //if(random==1)
    {
        temp= random_word(*g.Nom_tree);
        strcat(word,temp->end_word->base_word);
        strcat(word," ");
        temp= random_word(*g.Adj_tree);
        strcat(word,temp->end_word->base_word);
        strcat(word," ");
        temp= random_word(*g.Verb_tree);
        strcat(word,temp->end_word->base_word);
        strcat(word," ");
        temp= random_word(*g.Nom_tree);
        strcat(word,temp->end_word->base_word);
    }
}


