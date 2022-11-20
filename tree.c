#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "Functions.h"
#include "tree.h"
#include <time.h>
p_letter_node Add_word_in_tree(t_tree t, char word[size_word])
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
        if (j==temp->nb_sons) 
        {
            Add_Son(temp, word[i]); 
            temp=temp->sons+(temp->nb_sons-1); 
            j=0;
        }
        else
        {
            temp=temp->sons+j; 
            j=0;
        }
        i++;
    }
    return temp;
}

p_letter_node Add_basic_word(char sentence[size_word], t_tree t)
{
    p_letter_node temp;
    temp=t.root;
    int i=0;
    int j=0;
    char word[size_word];
    char variation[size_word];
    word_from_sentence(sentence,word);
    information_sentence(sentence, variation);
    temp= Add_word_in_tree(t,word);
    temp->end_word=(p_end_word) malloc(sizeof(t_end_word));
    strcpy(temp->end_word->base_word,word);
    strcpy(temp->end_word->base_bloc,variation);
    temp->end_word->nb_variations=0;
    temp->end_word->type= Type_of_word(sentence);
    temp->end_word->variations_word=NULL;
}

void add_variate_word(t_tree t,char sentence[size_word])
{
    p_end_word word;
    char temp[size_word] = "";
    int cpt_temp = 0;
    char word1[size_word];
    char word2[size_word];
    char base_word[size_word]="";
    int spaces=0;
    p_letter_node lastnode;
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
    information_sentence(sentence, word1);
    word_from_sentence(sentence,word2);
    if (location_word(base_word, t) == NULL)
    {
        //Ajouter le mot de base dans l'arbre
        lastnode=Add_word_in_tree(t,base_word);
        lastnode->end_word=(p_end_word)malloc(sizeof(t_end_word));
        strcpy(lastnode->end_word->base_word,base_word);
        lastnode->end_word->nb_variations=0;
        lastnode->end_word->type= Type_of_word(sentence);
        if (lastnode->end_word->type==1)
        {
            strcpy(lastnode->end_word->base_bloc,"Inf\n");
        }
        else
        {
            strcpy(lastnode->end_word->base_bloc,"Mas+SG\n");
        }
    }
    else
    {
        lastnode= location_word(base_word, t);
    }
    if (lastnode->end_word==NULL)
    {
        lastnode->end_word=(p_end_word)malloc(sizeof(t_end_word));
        strcpy(lastnode->end_word->base_word,base_word);
        lastnode->end_word->nb_variations=0;
        lastnode->end_word->type= Type_of_word(sentence);
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

t_groot create_tree(char file[size_word])
{
    t_groot t;
    p_tree temp_tree;
    t.Verb_tree=(p_tree)malloc(sizeof(t_tree));
    t.Adj_tree=(p_tree)malloc(sizeof(t_tree));
    t.Adv_tree=(p_tree)malloc(sizeof(t_tree));
    t.Nom_tree=(p_tree)malloc(sizeof(t_tree));
    t.Verb_tree->root= Create_Node('!');
    t.Adj_tree->root= Create_Node('!');
    t.Adv_tree->root= Create_Node('!');
    t.Nom_tree->root= Create_Node('!');

    FILE *fichier = NULL;
    char word[size_word]="";
    char temp_sentence[size_word]="";
    char base_word[size_word]="";
    char chaine[size_word] = ""; 
    int spaces=0;
    int cpt_temp=0;
    fichier = fopen(file,"r");
    if (fichier != NULL)
    {
        while(fgets(chaine, size_word, fichier) != NULL)
        {
            if (Type_of_word(chaine) == 1)
            {
                temp_tree=t.Verb_tree;
            }
            if (Type_of_word(chaine) == 2)
            {
                temp_tree=t.Adj_tree;
            }
            if (Type_of_word(chaine) == 3)
            {
                temp_tree=t.Nom_tree;
            }
            if (Type_of_word(chaine) == 4)
            {
                temp_tree=t.Adv_tree;
            }
            if (Type_of_word(chaine) == 0)
            {
                //printf("ERREUR! Impossible de detecter le type de mot dans la phrase\n");
                //printf("%s",chaine);
            }
            else
            {
                word_from_sentence(chaine,word);
                if (basic_or_not(chaine) == 1) //Si c'est un mot basique
                {
                    if(location_word(word, *temp_tree) == NULL)
                    {
                        Add_basic_word(chaine,*temp_tree);
                    }
                }
                else
                {

                    add_variate_word(*temp_tree, chaine);

                }
                // On reset la chaine
                for (int k = 0; k < size_word; k++)
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
