//
// Created by raphb on 06/11/2022.
//

#ifndef PROJET_GENERATEUR_DE_MOTS_NODE_H
#define PROJET_GENERATEUR_DE_MOTS_NODE_H

#define TAILLE_MAX 100
#define ALPHABET_SIZE 26

typedef struct s_variation
{
    char word[TAILLE_MAX]; //mot fléchi
    char variation_bloc[TAILLE_MAX];
} t_variation,* p_variation;

typedef struct s_end_word
{
    char base_word[TAILLE_MAX]; //mot basique
    char base_bloc[TAILLE_MAX]; //temps et genre du mot de base
    int type;  //type de mot
    int nb_variations; //nombre de mots fléchis dérivant de ce mot
    p_variation variations_word; //Tableau dynamique des variations à déclarer
} t_end_word,* p_end_word;



typedef struct s_letter_node
{
char letter;
int nb_sons;
p_end_word end_word;
struct s_letter_node * sons; //Tableau dynamique des fils à déclarer
} t_letter_node, * p_letter_node ;

p_letter_node CreateNode(char c);
void DisplayNode(t_letter_node n);
int AddSon(p_letter_node p,char c);

#endif //PROJET_GENERATEUR_DE_MOTS_NODE_H
