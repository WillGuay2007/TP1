#include "definition.h"

#include <stdio.h>

// Il est important de faire l'implementation de vos fonctions dans un fichier .c
// Si vous le faites dans le fichier "header", chaque fichier qui l'include va compiler l`implementation
// et cela causeras des definitions de symboles multiples.

void monprojet_ajouter_item(Inventory* inv, Item item){
	Node* CurrentSlot = inv->Head;
	while (CurrentSlot->Next != NULL)
	{
		CurrentSlot = CurrentSlot->Next;
	}
	Node* NewSlot = (Node*)allocate(sizeof(Node));
	NewSlot->Item = item;
	NewSlot->Next = NULL;

	CurrentSlot->Next = NewSlot;
};
void monprojet_enlever_item(Inventory* inv, char* nom) {

}
void monprojet_trier_inventaire(void) {

}
int monprojet_get_quantite(void) {

}
Item* monprojet_trouver_item_par_nom(Inventory* inv, char* nom) {
	Node* CurrentSlot = inv->Head;
	while (CurrentSlot->Item.nom != nom)
	{
		if (CurrentSlot == NULL) {
			printf("Couldnt find item by name.");
			return;
		}
		CurrentSlot = CurrentSlot->Next;
	}
	return CurrentSlot;
}
Item* monprojet_trouver_item_par_position(Inventory* inv, int position) {
	// Position 0 = head

}

Inventory* monprojet_CreerInventory(Item firstItem) {
	Inventory* inv = (Inventory*)allocate(sizeof(Inventory));
	inv->Head = (Node*)allocate(sizeof(Node));
	inv->Head->Item = firstItem;
	inv->Head->Next = NULL;
	return inv;
}