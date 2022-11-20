#ifndef PROJET_GENERATEUR_DE_MOTS_NODE_H
#define PROJET_GENERATEUR_DE_MOTS_NODE_H

#define size_word 100
#define ALPHABET_SIZE 26

typedef struct s_variation
{
    char word[size_word]; //mot fléchi
    char variation_bloc[size_word];
} t_variation,* p_variation;

typedef struct s_end_word
{
    char base_word[size_word]; //mot basique
    char base_bloc[size_word]; //temps et genre du mot de base
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

p_letter_node Create_Node(char c);
int Add_Son(p_letter_node p, char c);

#endif //PROJET_GENERATEUR_DE_MOTS_NODE_H
