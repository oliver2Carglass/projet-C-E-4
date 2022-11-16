//
// Created by raphb on 06/11/2022.
//

#ifndef MAIN_C_FUNCTIONS_H
#define MAIN_C_FUNCTIONS_H
#define TAILLE_MAX 100
#include "tree.h"
#include "node.h"

//Génération d'arbre
int WordType(char sentence[TAILLE_MAX]);//prend une ligne et renvoie son type(verbe 1,adj 2,nom 3,adverbe 4,NULL 0 )
void end_sentence(char sentence[TAILLE_MAX],char *word);
void word_from_sentence(char sentence[TAILLE_MAX],char *word) ;
int Wich_word(char sentence[TAILLE_MAX]); //détecte si c'est un mot fléchi ou basique (basique 1, fléchi 0)
p_letter_node Go_to(char word[TAILLE_MAX],t_tree t);
p_letter_node Add_word_in_tree(t_tree t, char word[TAILLE_MAX]);
p_letter_node Add_basic_word(char word[TAILLE_MAX], t_tree t); //ajoute un mot basique dans l'abre
void add_variate_word(t_tree t,char sentence[TAILLE_MAX]);
t_groot create_tree(char directory_dico[TAILLE_MAX]);

//Génération de phrase
p_letter_node random_word(t_tree t);
void find_dico(char **argv,char *result);//cherche le chemin absolue du dicitionnaire
void random_base_sentence(t_groot g,char* word);

#endif //MAIN_C_FUNCTIONS_H
