#ifndef MAIN_C_FUNCTIONS_H
#define MAIN_C_FUNCTIONS_H
#define size_word 100
#include "tree.h"
#include "node.h"

//Génération de phrase
p_letter_node random_word(t_tree t); //renvoie un mot aleatoire de la'bre
void random_base_sentence(t_groot g, char* word);// Prend en argument la structure general_tree contenant les 4 arbres et remplit la chaine word avec une phrase contituée de mots de base aléatoires
void random_variate_sentence(t_groot g, char* word); //Fonction qui prend en argument un general_tree contenant 4 arbres et une chaine word et la remplit avec une phrase aléatoire de formes fléchies qui s'accordent (sauf le verbe qui est resté à l'infinitif) selon 3 modèles choisis aléatoirement
void random_variate_noun(t_tree t,char* word,char* bloc); //Fonction qui prend en argument un arbre et le bloc du sujet de la phrase (bloc) et va remplir la chaine word avec un nom aléatoires et le bloc du sujet avec le bloc de ce mot aléatoire
void random_variate_adj(t_tree t,char* word,char* bloc);// Fonction qui prend en argument un arbre et le bloc du sujet et remplit la chaine word avec un adjectif accordé avec le sujet renseigné
//Foncion générale
void find_dico(char **argv,char *result);//cherche le chemin absolu du dictionnaire
int Type_of_word(char sentence[size_word]);//prend une ligne et renvoie le type de mot contenu dans cette ligne(verbe 1,adj 2,nom 3,adverbe 4,NULL 0 )
void information_sentence(char sentence[size_word], char *word);//prend une ligne et remplit la chaine *word donnée avec la troisieme colonne de la ligne ("mas+SG") par exemple
void word_from_sentence(char sentence[size_word], char *word) ;//prend une ligne et remplit la chaine *word donnée avec la 1ère colonne de la ligne (le mot flechi de la ligne)
int basic_or_not(char sentence[size_word]); //détecte si c'est un mot fléchi ou basique (basique 1, fléchi 0)
p_letter_node location_word(char word[size_word], t_tree t); //Cherche dans l'arbre si le mot basique word est présent ou non: Elle renvoie un pointeur vers le noeud de la dernière lettre du mot ou NULL si le mot n'est pas présent dans l'arbre
//Fonction recherche d'un mot
void interface_information(char sentence[size_word], int type_word, char word[size_word]);//renvoie une phrase en fonction d'un bloc d'information (ex P1:SG → mot a la premiere personne du singulier)
void find_word(t_groot g_tree, char directory_dico[size_word]);//fonction afin de trouver un mot
int word_base_info(char directory_dico[size_word], char search_word[size_word], char str[size_word], int search_word_type, char bloc[size_word]);//renvoie le mot basique ainsi que son bloc et son type
#endif //MAIN_C_FUNCTIONS_H
