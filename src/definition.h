// Vous devez ajouter ce #pragma a tous vos fichiers .h de votre projet.
// Il garantit que le fichier "header" n'est inclus qu'une seule fois par compilation,
// ce qui evite les erreurs de redefinition et les conflits de symboles.
#pragma once

#include <stdint.h>

typedef struct Item{
    char* nom;
    int valeur;
} Item;

typedef struct Node {
    Item Item;
    Node* Next;
} Node;

typedef struct Inventory {
    Node* Head;
} Inventory;



void* allocate(size_t size);
// Vous devez definir les structures et fonctions que vous voulez exposer dans les "headers"
// Si jamais vous avez des fonctions avec des noms commun, vous devez les prefixer pour eviter des conflits de symboles
// Le prefix peut etre le nom de votre projet, exemple: forhonor_nom_de_fonction

void monprojet_ajouter_item(Inventory* inv, Item item);
void monprojet_enlever_item(Inventory* inv, char* nom);
void monprojet_trier_inventaire(void);
int monprojet_get_quantite(void);
Item* monprojet_trouver_item_par_nom(Inventory* inv, char* nom);
Item* monprojet_trouver_item_par_position(Inventory* inv, int position);
Inventory* monprojet_CreerInventory(Item firstItem);