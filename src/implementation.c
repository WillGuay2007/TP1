#include "definition.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	printf("Ajoute: %s dans l'inventaire.\n", item.nom);
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
	
	printf("Item: %s a ete enleve de l'inventaire.\n", SlotToRemove->Item.nom);

	SlotToRemove->Next = NULL;
	SlotToRemove->Item.nom = NULL;
	SlotToRemove->Item.valeur = 0;

	memset(SlotToRemove, 0, sizeof(Node));

}
void monprojet_trier_inventaire(Inventory* inv) {
	if (inv->Head == NULL) return;

	int Swapped = 1;
	Node* CurrentNode;
	Node* LastNode = NULL;

	while (Swapped == 1) {
		Swapped = 0;
		CurrentNode = inv->Head;

		while (CurrentNode->Next != LastNode) {
			if (CurrentNode->Item.valeur > CurrentNode->Next->Item.valeur) {
				Item tempItem = CurrentNode->Item;
				CurrentNode->Item = CurrentNode->Next->Item;
				CurrentNode->Next->Item = tempItem;

				Swapped = 1;
			}
			CurrentNode = CurrentNode->Next;
		}
		LastNode = CurrentNode;
	}
	printf("L'inventaire a ete trie.\n");
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
void monprojet_printinventory(Inventory* inv) {
	if (inv->Head != NULL) {
		Node* CurrentNode = inv->Head;
		int CurrentPos = 0;

		printf("\033[1;33m\n\nINVENTAIRE\n\n\033[0m\n");

		while (CurrentNode != NULL) {
			printf("Position de l'item: %d\nNom de l'item: %s\nValeur de l'item: %d\n\n--------------------\n\n", CurrentPos, CurrentNode->Item.nom, CurrentNode->Item.valeur);
			CurrentNode = CurrentNode->Next;
			CurrentPos++;
		}
	}
}
void monprojet_populate(FILE* file, Item* Items) {
	char Buffer[256];
	int count = 0;

	while (fgets(Buffer, 256, file) != NULL) {
		char* word = strtok(Buffer, " \n");

		while (word != NULL) {
			if (strcmp(word, "Name,") == 0) {
				word = strtok(NULL, " \n");
				if (word != NULL) {
					word[strcspn(word, ",")] = '\0';
					Items[count].nom = strdup(word);
				}
			}
			else if (strcmp(word, "Value,") == 0) {
				word = strtok(NULL, " \n");
				if (word != NULL) {
					Items[count].valeur = atoi(word);
				}
			}
			word = strtok(NULL, " \n");
		}
		count++;
	}
}
Inventory* monprojet_CreerInventory(Item firstItem) {
	Inventory* inv = (Inventory*)allocate(sizeof(Inventory));
	inv->Head = (Node*)allocate(sizeof(Node));
	inv->Head->Item = firstItem;
	inv->Head->Next = NULL;
	printf("Nouvel inventaire initialise avec item: %s\n", firstItem.nom);
	return inv;
}