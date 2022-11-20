#ifndef PROJET_GENERATEUR_DE_MOTS_TREE_H
#define PROJET_GENERATEUR_DE_MOTS_TREE_H

#include "node.h"

typedef struct s_tree
{
	p_letter_node root ;
} t_tree,* p_tree ;

typedef struct s_groot
{
    p_tree Verb_tree;
    p_tree Adj_tree;
    p_tree Nom_tree;
    p_tree Adv_tree;
}t_groot,* p_groot;

p_letter_node Add_word_in_tree(t_tree t, char word[size_word]);//Ajoute les noeuds des lettres du mot dans l'arbre
p_letter_node Add_basic_word(char word[size_word], t_tree t); //Ajoute un mot basique dans l'abre
void add_variate_word(t_tree t,char sentence[size_word]);//Ajoute un mot fléchi
t_groot create_tree(char directory_dico[size_word]);// Créé l'arbre

#endif //PROJET_GENERATEUR_DE_MOTS_TREE_H
