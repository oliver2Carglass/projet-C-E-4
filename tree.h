//
// Created by raphb on 06/11/2022.
//

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

#endif //PROJET_GENERATEUR_DE_MOTS_TREE_H
