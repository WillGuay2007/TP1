#include "definition.h"

#include <stdio.h>
#include <stdlib.h>

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
	printf("Ajoute: %s dans l'inventaire.", item.nom);
};
void monprojet_enlever_item(Inventory* inv, char* nom) {
	Node* SlotToRemove = monprojet_trouver_item_par_nom(inv, nom);
	if (SlotToRemove == NULL) return;
	
	if (SlotToRemove == inv->Head) {
		inv->Head = SlotToRemove->Next;
	}
	else {
		Node* CurrentSlot = inv->Head;
		while (CurrentSlot->Next != SlotToRemove) {
			CurrentSlot = CurrentSlot->Next;
		}
		CurrentSlot->Next = SlotToRemove->Next;
	}
	
	printf("Item: %s a ete enleve de l'inventaire.", SlotToRemove->Item.nom);

	SlotToRemove->Next = NULL;
	SlotToRemove->Item.nom = NULL;
	SlotToRemove->Item.valeur = 0;

	//free(SlotToRemove);

}
void monprojet_trier_inventaire(void) {

}
int monprojet_get_quantite(Inventory* inv) {
	if (inv->Head == NULL) return 0;
	int ItemCount = 0;
	Node* CurrentNode = inv->Head;
	while (CurrentNode != NULL) {
		ItemCount++;
		CurrentNode = CurrentNode->Next;
	}
	return ItemCount;
}
Item* monprojet_trouver_item_par_nom(Inventory* inv, char* nom) {
	if (inv->Head == NULL) return NULL;
	Node* CurrentSlot = inv->Head;
	while (CurrentSlot != NULL && strcmp(CurrentSlot->Item.nom, nom) != 0)
	{
		CurrentSlot = CurrentSlot->Next;
	}
	if (CurrentSlot != NULL && strcmp(CurrentSlot->Item.nom, nom) == 0) {
		return &CurrentSlot->Item;
	}
	return NULL;
}
Item* monprojet_trouver_item_par_position(Inventory* inv, int position) {
	if (inv->Head == NULL || position < 0) return NULL;

	int CurrentPos = 0;
	Node* CurrentNode = inv->Head;

	while (CurrentNode != NULL && CurrentPos < position) {
		CurrentNode = CurrentNode->Next;
		CurrentPos++;
	}

	if (CurrentNode != NULL) {
		return &CurrentNode->Item;
	}

	printf("Position invalide.\n");
	return NULL;
}

void PrintInventory(Inventory* inv) {
	if (inv->Head != NULL) {
		Node* CurrentNode = inv->Head;
		int CurrentPos = 0;
		while (CurrentNode != NULL) {
			printf("Position de l'item: %d\nNom de l'item: %s\nValeur de l'item: %d\n\n--------------------\n\n", CurrentPos, CurrentNode->Item.nom, CurrentNode->Item.valeur);
			CurrentNode = CurrentNode->Next;
			CurrentPos++;
		}
	}
}

Inventory* monprojet_CreerInventory(Item firstItem) {
	Inventory* inv = (Inventory*)allocate(sizeof(Inventory));
	inv->Head = (Node*)allocate(sizeof(Node));
	inv->Head->Item = firstItem;
	inv->Head->Next = NULL;
	return inv;
}