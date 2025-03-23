//Bonne pratique, pour les includes systemes toujours utiliser <> et "" pour les includes de votre projet.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "definition.h"
#include <time.h>

#define HEAP_SIZE 2048 * 2048 * 4
static uint8_t* heap = NULL;
static size_t heap_top = 0;
void* allocate(size_t size) {
	size_t old_top = heap_top;
	heap_top += size;
	assert(heap_top <= HEAP_SIZE);
	return &heap[old_top];
}

Item Items[6];

int main(int argc, char** argv) {
	heap = (uint8_t*)malloc(HEAP_SIZE);
	assert(heap != NULL);

	//Commencer à écrire le code ici:

	srand(time(NULL));

	FILE* file = fopen("tp1_data.csv", "r");
	if (file == NULL) {
		printf("Erreur lors de l'ouverture du fichier CSV.\n");
		return;
	}
	monprojet_populate(file, Items); //Initialiser la table Items (noms et valeurs) a partir du fichier CSV

	Item Fiole = {0};
	Fiole.nom = "Fiole";
	Fiole.valeur = 30;

	Inventory* Inv = monprojet_CreerInventory(Fiole);
	int RandomAmount = rand() % 10 + 1;

	for (int i = 0; i < RandomAmount; i++) {
		int RandomItem = rand() % 6;
		monprojet_ajouter_item(Inv, Items[RandomItem]);
	}

	monprojet_printinventory(Inv);
	monprojet_trier_inventaire(Inv);
	monprojet_enlever_item(Inv, "Fiole");
	monprojet_printinventory(Inv);

}