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
{#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "Functions.h"
#include "tree.h"
#include <time.h>


p_letter_node location_word(char word[size_word], t_tree t)
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
        if (j==temp->nb_sons) //Si la lettre n'a pas été trouvée 
        {
            return NULL;
        }
        else
        {
            temp=temp->sons+j; //On affecte à temp le fils qui contient la lettre suivante
            j=0;
        }
        i++;
    }
    return temp;
}







int basic_or_not(char sentence[size_word])
{
    char temp1[size_word] = "";
    char temp2[size_word] = "";
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
    if (strcmp(temp1,temp2)==0)
    {
        return 1; //Mot basique
    }
    return 0;
}


void information_sentence(char sentence[size_word], char *word)
{
    char temp[size_word] = "";
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
            for (int k = 0; k < size_word; k++)
            {
                temp[k] = 0; // vide la chaine de caractere temp
            }
        }

    }
    strcpy(word,temp);

}

void word_from_sentence(char sentence[size_word], char *word)
{
    char temp[size_word] = "";

    for (int i = 0; sentence[i] != '\t'; i++)
        temp[i] = sentence[i];


    strcpy(word,temp);

}






p_letter_node random_word(t_tree t)
{
    // Initialise le générateur pseudo-aléatoire
    p_letter_node temp;
    temp=t.root;
    int random;
    while(temp->nb_sons>0)
    {
        if(rand() %5==0)
        {
            if(temp->end_word!=NULL)
            {
                return temp;
            }
        }
        random=rand() %(temp->nb_sons);
        temp=temp->sons+(random);
    }
    return temp;

}

void random_base_sentence(t_groot g, char* word)
{
    p_letter_node temp;
    int random;
    random=rand();
    srand(time(NULL));
    if(random%3==0)
    {
        //Modèle 1: nom – adjectif – verbe – nom
        printf("Phrase du type modele 1:\n");
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
    if(random%3==1)
    {
        //Modèle 2: nom – ‘qui’ – verbe – verbe – nom – adjectif
        printf("Phrase du type modele 2:\n");
        temp= random_word(*g.Nom_tree);
        strcat(word,temp->end_word->base_word);
        strcat(word," qui ");
        temp= random_word(*g.Verb_tree);
        strcat(word,temp->end_word->base_word);
        strcat(word," ");
        temp= random_word(*g.Verb_tree);
        strcat(word,temp->end_word->base_word);
        strcat(word," ");
        temp= random_word(*g.Nom_tree);
        strcat(word,temp->end_word->base_word);
        strcat(word," ");
        temp= random_word(*g.Adj_tree);
        strcat(word,temp->end_word->base_word);
    }
    if(random%3==2)
    {
        //Modèle 3: Nom Verbe+ Adverbe
        printf("Phrase du type modele 3:\n");
        temp= random_word(*g.Nom_tree);
        strcat(word,temp->end_word->base_word);
        strcat(word," ");
        temp= random_word(*g.Verb_tree);
        strcat(word,temp->end_word->base_word);
        strcat(word," ");
        temp= random_word(*g.Adv_tree);
        strcat(word,temp->end_word->base_word);
    }
}
int Type_of_word(char sentence[size_word]) //verbe=1,adj=2,nom=3,adverbe=4,NULL=0
{
    char temp[size_word] = "";
    int cpt_temp = 0; //compteur buffer
    for (int i = 0; sentence[i] != '\0'; i++) {
        if(((sentence[i]!=':')&(sentence[i] != '\t')&(sentence[i] != ' '))&&sentence[i+1]!='\0') { 
            cpt_temp++;
        }
        else{
            if(sentence[i+1]=='\0'){
                temp[cpt_temp] = sentence[i];
            }

            if (strcmp(temp, "Ver") == 0) {
                return 1; 
            }
            if (strcmp(temp, "Adj") == 0) {
                return 2; 
            }
            if (strcmp(temp, "Nom") == 0) {
                return 3; 
            }
            if (strcmp(temp, "Adv") == 0) {
                return 4; 
            }
        }
        if(sentence[i]=='\t'||sentence[i]==':'||sentence[i]==' '){
            cpt_temp = 0;
            for (int k = 0; k < size_word; k++) {
                temp[k] = 0; // reset chaine
            }
        }
    }
    if (strcmp(temp,"Adv\n") == 0)
    {
        return 4;
    }
    return 0;

}


//TENTATIVE DE GENERATION DE PHRASE AVEC DES FORMES FLECHIES
void random_variate_noun(t_tree t,char* word,char* bloc)
{
    p_letter_node temp;
    int random;
    char bloc_copy[size_word]="";
    random=rand();
    if(random%2==0) {
        //Mot basique
        temp= random_word(t);
        if(strcmp(temp->end_word->base_bloc,"Mas+SG\n")==0)
        {
            strcat(word,"le ");
        }
        else
        {
            if(strcmp(temp->end_word->base_bloc,"Fem+SG\n")==0)
            {
                strcat(word,"la ");
            }
            else
            {
                strcat(word,"les ");
            }
        }
        strcat(word,temp->end_word->base_word);
        strcat(bloc,temp->end_word->base_bloc);
        return;
    }
    //Le premier mot sera fléchi
    temp= random_word(t);
    //Si le mot n'a pas de variations on en prend un autre
    while(temp->end_word->nb_variations==0)
    {
        temp= random_word(t);
    }
    random= rand()%(temp->end_word->nb_variations);
    strcat(bloc_copy,temp->end_word->variations_word[random].variation_bloc);
    if(strcmp(bloc_copy,"Mas+SG\n")==0)
    {
        strcat(word,"le ");
    }
    else
    {
        if(strcmp(bloc_copy,"Fem+SG\n")==0)
        {
            strcat(word,"la ");
        }
        else
        {
            strcat(word,"les ");
        }
    }
    strcat(word,temp->end_word->variations_word[random].word);
    strcat(bloc,temp->end_word->variations_word[random].variation_bloc);
}
void random_variate_sentence(t_groot g, char* word)
{
    p_letter_node temp;
    char temp_str[size_word]="";
    int random;
    srand(time(NULL));
    random=rand();
    if(random%3==2)
    {
        //Modèle 3: Nom Verbe+ Adverbe
        printf("Phrase du type modele 3:\n");
        //Pour le nom
        random_variate_noun(*g.Nom_tree,word,temp_str);
        //Pour le verbe
        strcat(word," ");
        temp= random_word(*g.Verb_tree);
        strcat(word,temp->end_word->base_word);
        //Pour l'adjectif
        strcat(word," ");
        temp= random_word(*g.Adv_tree);
        strcat(word,temp->end_word->base_word);
    }
    if(random%3==1)
    {
        //Modèle 1: nom – adjectif – verbe – nom
        printf("Phrase du type modele 1:\n");
        //Pour le nom
        random_variate_noun(*g.Nom_tree,word,temp_str);
        //Pour l'adjectif
        strcat(word," ");
        random_variate_adj(*g.Adj_tree,word,temp_str);
        //Pour le verbe
        temp= random_word(*g.Verb_tree);
        strcat(word,temp->end_word->base_word);
        strcat(word," ");
        //Pour le nom
        random_variate_noun(*g.Nom_tree,word,temp_str);
    }
    if (random%3==0)
    {
        //Modèle  nom – ‘qui’ – verbe – verbe – nom – adjectif
        printf("Phrase du type modele 2:\n");
        //Pour le nom
        random_variate_noun(*g.Nom_tree,word,temp_str);
        strcat(word," qui ");
        //Pour le verbe
        temp= random_word(*g.Verb_tree);
        strcat(word,temp->end_word->base_word);
        strcat(word," ");
        //Pour le verbre
        temp= random_word(*g.Verb_tree);
        strcat(word,temp->end_word->base_word);
        strcat(word," ");
        random_variate_noun(*g.Nom_tree,word,temp_str);
        strcat(word," ");
        random_variate_adj(*g.Adj_tree,word,temp_str);
    }
    for (int k=0; k < size_word; k++)
    {
        temp_str[k]='\0';
    }
}
//TENTATIVE DE GENERATION DE PHRASE AVEC DES FORMES FLECHIES

void find_word(t_groot g_tree, char directory_dico[size_word]){
    char temp[size_word]="";
    char bloc[size_word]="";
    char word_search[size_word]="";
    int type_of_word = 0;
    p_letter_node p;
    while(type_of_word == 0){
        printf("Quelle type de mot souhaitez vous chercher? \n(Ver pour un verbe, Adj pour un adjectif, Adv pour un adverbe et Nom pour un nom et aucun si vous voulez rechercher  parmi tous les mots\n");
        scanf("%s",&temp);
        strcat(temp,"  ");
        if(strcmp(temp,"aucun  ")==0) { //cas particulier
            type_of_word = -1;
        }
        if(type_of_word != -1) //exception du cas particulier
            type_of_word= Type_of_word(temp);
        if(type_of_word == 0){
            printf("Merci de rentrer une valeur valide");
        }

    }
    printf("Quelle mot rechercher vous ?");
    scanf("%s",&word_search);
    printf("\n");

    if(1){
        char temp[size_word]="";
        char word_type[size_word]="";
        char bloc[size_word]="";
        word_base_info(directory_dico, word_search, temp, type_of_word, bloc);
        type_of_word= Type_of_word(bloc);// on cherche le type du mot
        if(type_of_word != 0)
            printf("\nLe mot a comme forme de base %s.  \n",temp);
        information_sentence(bloc, bloc);//on enleve la partie 'type:'
        interface_information(bloc, type_of_word, word_search);
    }


    }

void interface_information(char sentence[size_word], int type_word, char word[size_word]){ //prend en parametre le bloc et le transforme en phrase
    //rappel le bloc est, dans une ligne de dico.txt, ce qu'il y a apres le type de mot (exemple IPre+SG+P3)
    int cpt =0;
    char temp[size_word]="";
    printf("Le mot %s est ",word);
    if(type_word==1)
        printf("un verbe ");
    if(type_word==2)
        printf("un adjectif ");
    if(type_word==3)
        printf("un nom ");
    if(type_word==4)
        printf("un adverbe ");
    if(type_word==0)
        printf("un mot indefinie ");
    if(type_word!=0)
        printf("et est ");

    for(int i =0;sentence[i]!='\0';i++){
        if(sentence[i]!=':'&sentence[i]!='+'&sentence[i]!='\n'&sentence[i+1]!='\0'){
            temp[cpt]=sentence[i];
            cpt++;
        }
        else{
            if(sentence[i+1]=='\0'){
                temp[cpt]=sentence[i];
            }
            if (strcmp(temp, "P1") == 0||strcmp(temp, "P1\n")==0) {
                printf("a la premiere personne ");
            }
            if (strcmp(temp, "P2") == 0||strcmp(temp, "P2\n")==0) {
                printf("a la deuxieme personne ");
            }
            if (strcmp(temp, "P3") == 0||strcmp(temp, "P3\n")==0) {
                printf("a la troisieme personne ");
            }

            if (strcmp(temp, "IPre") == 0||strcmp(temp, "IPre\n")==0) {
                printf("au present de l'indicatif ");
            }
            if (strcmp(temp, "IImp") == 0||strcmp(temp, "IImp\n")==0) {
                printf("a l'imparfait de l'indicatif ");
            }
            if (strcmp(temp, "SPre") == 0||strcmp(temp, "SPre\n")==0) {
                printf("au present du subjonctif ");
            }
            if (strcmp(temp, "IPSim") == 0||strcmp(temp, "IPSim\n")==0) {
                printf("au passe simple de l'indicatif ");
            }
            if (strcmp(temp, "IFut") == 0||strcmp(temp, "IFut\n")==0) {
                printf("au futur simple de l'indicatif ");
            }
            if (strcmp(temp, "PPas") == 0||strcmp(temp, "PPas\n")==0) {
                printf("au participe passe");
            }
            if (strcmp(temp, "SImp") == 0||strcmp(temp, "SImp\n")==0) {
                printf("a l'imparfait du subjonctif ");
            }
            if (strcmp(temp, "Mas") == 0||strcmp(temp, "Mas\n")==0) {
                printf("au masculin ");
            }
            if (strcmp(temp, "Fem") == 0||strcmp(temp, "Fem\n")==0) {
                printf("au feminin ");
            }
            if (strcmp(temp, "SG") == 0||strcmp(temp, "SG\n")==0) {
                printf("au singulier ");
            }
            if (strcmp(temp, "PL") == 0||strcmp(temp, "PL\n")==0) {
                printf("au pluriel ");
            }
            if (strcmp(temp, "InvGen") == 0||strcmp(temp, "InvGen\n")==0) {
                printf("au feminin et au masculin ");
            }
            if (sentence[i]== ':') {
                printf("\nmais aussi : \n");
            }
            if (sentence[i]=='+') {
                printf("et ");
            }

        }
        if(sentence[i]=='+'||sentence[i]==':'||sentence[i]=='\n'){
            cpt = 0;
            for (int k = 0; k < size_word; k++) {
                temp[k] = 0; // le mot est terminé on reinitialise la le buffer temp à "" (vide)
            }
    }

}
    printf("\n");
}
void random_variate_adj(t_tree t,char* word,char* bloc)
{
    p_letter_node temp;
    int random;
    temp= random_word(t);
    char delim[]="+";
    char bloc_copy[size_word]="";
    char random_bloc_copy[size_word]="";
    strcat(bloc_copy,bloc);
    strcat(random_bloc_copy,temp->end_word->base_bloc);
    //Tant qu'on a un mot de base qui n'a pas le même genre que le bloc ou aucun variation, on change de mot

    while(strcmp(strtok(bloc_copy,delim), strtok(random_bloc_copy,delim))!=0 || temp->end_word->nb_variations==0)
    {
        temp= random_word(t);
        for (int i=0; i < size_word; i++)
        {
            random_bloc_copy[i]='\0';
        }
        strcat(random_bloc_copy,temp->end_word->base_bloc);
    }
    if (strcmp(bloc,temp->end_word->base_bloc)==0)
    {
        strcat(word,temp->end_word->base_word);
        strcat(bloc,temp->end_word->base_bloc);
        return;
    }
    for (int i=0;i<temp->end_word->nb_variations;i++)
    {
        if (strcmp(bloc,temp->end_word->variations_word[i].variation_bloc)==0)
        {
            strcat(word,temp->end_word->variations_word[i].word);
            strcat(bloc,temp->end_word->variations_word[i].variation_bloc);
            return;
        }
    }
    printf("probleme!!!!\n");
}
int word_base_info(char directory_dico[size_word], char search_word[size_word], char str[size_word], int search_word_type, char bloc[size_word]){
    //directory_dico chemin du dico.txt,search word le mot que l'on cherche,str la ou on va mettre le mom
    //type_word indique le type du mot(verbe nom adj , ect)
    char buffer[size_word] = "";
    FILE *fichier = NULL;
    int space = 0;
    fichier = fopen(directory_dico, "r");
    char temp[size_word];//mot temporaire pour le parcours
    int cpt_temp = 0;
    int bool_find = 0;
    int temp_word_type=0; //type du mot des lignes parcourue

    if (fichier != NULL) {
        while (fgets(buffer, size_word, fichier) != NULL) {
            temp_word_type= Type_of_word(buffer);
            bool_find = 0;
            cpt_temp = 0;
            space = 0;
            if((temp_word_type==search_word_type)||search_word_type==-1){
            //si le mot est du meme type que le mot recherche ou que l'utilisateur n'a désirer rechercher
            //aucun type de mot specifique (search_word_type==-1)
                for (int i = 0; i < size_word; i++) {
                    temp[i] = 0;
                }

                    for (int i = 0; buffer[i] != '\0'; i++) {
                        if (buffer[i] != '\t') {
                            temp[cpt_temp] = buffer[i];
                            cpt_temp++;
                        } else {
                            if (strcmp(temp, search_word) == 0) { //la ligne en question est la mot trouvé
                                bool_find = 1;
                            }
                            if (bool_find == 1 & space == 1) {
                                strcpy(str, temp); //on renvoie le mot basique dans str


                            }
                            space++;

                            for (int k = 0; k < size_word; k++) {
                                temp[k] = 0;
                                cpt_temp = 0;
                            }
                        }


                    }
                    if(bool_find==1){
                        strcpy(bloc,temp);
                    }

            }
        }
    }

}
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


