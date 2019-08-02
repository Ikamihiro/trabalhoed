#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int id;
    char pokemon[20];
    int hp;
    int ataque;
    int defesa;
} TItem;

typedef struct No {
    TItem item;
    struct No *left, *right;
} TNo;

/* Método para a criação de um nó através de alocação dinâmica */
TNo *createnode (TItem item) {
    TNo *a = (TNo *) malloc(sizeof(TNo));
    a->left = NULL;
    a->right = NULL;
    a->item = item;
    return a;
}

/*  Método para inserção em árvore binária*/
TNo *insertTree(TNo *tree, TItem item) {
    if(tree == NULL)
        // o nó que for null ele adiciona o valor
        tree = createnode(item);
    else {
        if(item.id < tree->item.id) 
            // valor menor que o nó corrente
            tree->left = insertTree(tree->left, item);
        else
            // nó maior que o nó corrente
            tree->right = insertTree(tree->right, item);
    }
    return tree;
}

/* Método para percorrer a árvore em ordem */
void showtree(TNo *tree) {
    // Só irá percorrer a árvore se ela não for vazia
    if(tree != NULL) {
        // Percorre primeiro a subárvore esquerda do nó corrente
        showtree(tree->left);
        // E então mostra o valor do nó corrente
        printf(" %s: %d |", tree->item.pokemon, tree->item.id);
        // Para depois mostrar a subárvore direita do nó corrente
        showtree(tree->right);
    }
}

int main() {
    int numPokemons;
    TNo *arvoreHp = NULL;
    TNo *arvoreAtaque = NULL;
    TNo *arvoreDefesa = NULL;
    FILE *file;

    file = fopen("pokemon.txt", "r");
    if(file == NULL) {
        printf("Erro! Arquivo não existe\n");
        return 0;
    }
    if(file != NULL) {
        fscanf(file, "%d\n", &numPokemons);
        TItem pokemons[numPokemons];
        for(int i = 0; i < numPokemons; i++) {
            TItem item;
            fscanf(file, "%s %d %d %d\n", item.pokemon, &item.hp, &item.ataque, &item.defesa);
            item.id = item.hp;
            arvoreHp = insertTree(arvoreHp, item);
            item.id = item.ataque;
            arvoreAtaque = insertTree(arvoreAtaque, item);
            item.id = item.defesa;
            arvoreDefesa = insertTree(arvoreDefesa, item);
            pokemons[i] = item;
        }
        showtree(arvoreHp);
        printf("\n\n");
        showtree(arvoreAtaque);
        printf("\n\n");
        showtree(arvoreDefesa);
        printf("\n\n");
    }
    fclose(file);
    return 0;
}