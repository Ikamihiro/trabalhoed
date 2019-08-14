#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

void mergeIntercala(TItem *vetor, int inicio, int meio, int tamanho) {
    int i, j, k, a_size  = meio - inicio + 1, b_size = tamanho - meio;
    TItem *vetA = (TItem *) malloc(sizeof(TItem) * a_size);
    TItem *vetB = (TItem *) malloc(sizeof(TItem) * b_size);
    //dividindo o vetor nos dois vetores alocados
    for(i = 0; i < a_size; i++) {
        vetA[i] = vetor[i + inicio];
    }
    for(i = 0; i < b_size; i++) {
        vetB[i] = vetor[i + meio + 1];  
    }
    // colocando ordenadamente no vetor original
    for(i = 0, j = 0, k = inicio; k <= tamanho; k++) {
        if(i == a_size) {
            vetor[k] = vetB[j++];
        }
        else if(j == b_size) {
            vetor[k] = vetA[i++];
        }
        else if(vetA[i].id < vetB[j].id) {
            vetor[k] = vetA[i++];
        }
        else {
            vetor[k] = vetB[j++];
        }
    }
    //liberando o espaço alocado
    free(vetA);
    free(vetB);
}

void mergeSort(TItem *vetor, int inicio, int tamanho) {
    int meio;
    if(inicio < tamanho) {
        meio = floor((inicio + tamanho) / 2);
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio + 1, tamanho);
        mergeIntercala(vetor, inicio, meio, tamanho);
    }
}

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
    else if(item.id < tree->item.id)
        // valor menor que o nó corrente
        tree->left = insertTree(tree->left, item);
    else
        // nó maior que o nó corrente
        tree->right = insertTree(tree->right, item);
    return tree;
}

/* Método para percorrer a árvore em ordem */
void showtree(TNo *tree) {
    // Só irá percorrer a árvore se ela não for vazia
    if(tree != NULL) {
        // Percorre primeiro a subárvore esquerda do nó corrente
        showtree(tree->left);
        // E então mostra o valor do nó corrente
        printf("| %s: %d |\n", tree->item.pokemon, tree->item.id);
        // Para depois mostrar a subárvore direita do nó corrente
        showtree(tree->right);
    }
}

TItem *pesquisa(TNo *tree, int id) {
    if (tree == NULL)
        // se a árvore for vazia, retorna item vazio
        return NULL;
    if (id < tree->item.id)
        // se o valor esperado for menor que o nó pai,
        // procurar na subárvore da esquerda
        return pesquisa(tree->left, id);
    if (id > tree->item.id)
        // se o valor esperado for maior que o nó pai,
        // procurar na subárvore da direita
        return pesquisa(tree->right, id);
    // no final, retorna o item com o valor esperado
    return &(tree->item);
}

TItem *pesquisaModificada(TNo *tree, int id) {
    if(tree == NULL) {
        printf("Nenhum pokemon foi utilizado na comparação!\n");
        return NULL;
    }
    if(id < tree->item.id) {
        printf("Pokemon utilizado na comparação: %s\n", tree->item.pokemon);
        return pesquisaModificada(tree->left, id);
    }
    if(id > tree->item.id) {
        printf("Pokemon utilizado na comparação: %s\n", tree->item.pokemon);
        return pesquisaModificada(tree->right, id);
    }
    return &(tree->item);
}

void pesquisaTodosAtaque(TNo *tree, int ataque) {
    if(tree != NULL) {
        if(tree->item.ataque == ataque) 
            printf("| %s: %d |\n", tree->item.pokemon, tree->item.ataque);
        pesquisaTodosAtaque(tree->left, ataque);
        pesquisaTodosAtaque(tree->right, ataque);
    }
}

void dezMaioresAtaques(TItem *pokemons, int numPokemons) {
    //quickSort(pokemons,0,numPokemons - 1);
    mergeSort(pokemons, 0, numPokemons-1);
    for(int i = numPokemons - 1; i >= numPokemons-10; i--) {
        printf("| %s: %d |\n", pokemons[i].pokemon, pokemons[i].id);
    }
}

void dezMenoresDefesas(TItem *pokemons, int numPokemons) {
    mergeSort(pokemons, 0, numPokemons-1);
    for(int i = 0; i < 10; i++) {
        printf("| %s: %d |\n", pokemons[i].pokemon, pokemons[i].id);
    }
}

TItem buscaBinaria(TItem *vetor, int id, int tamanho) {
    int inicio = 0, size = tamanho - 1;
    while(inicio <= size) {
        int meio = (inicio + size) / 2;
        if(vetor[meio].id == id) return vetor[meio];
        if(vetor[meio].id < id) {
            printf("Pokemon utilizado na comparação: %s\n", vetor[meio].pokemon);
            inicio = meio + 1;
        }
        else size = meio;
    }
}

void menu() {
    printf("\tPokemon Tree\n");
    printf("1 - Listar os 10 maiores pokemons com maiores ataques\n");
    printf("2 - Listar os 10 menores pokemons com menores ataques\n");
    printf("3 - Listar os pokemons em ordem crescente de acordo com seu hp\n");
    printf("4 - Listar todos os pokemons com ataque igual a 130\n");
    printf("5 - Buscar pokemons com ataque igual a 131\n");
    printf("6 - Sair\n");
    printf(">: ");
}

int main() {
    // variáveis necessárias
    int numPokemons, opcao;
    TNo *arvoreHp = NULL;
    TNo *arvoreAtaque = NULL;
    TNo *arvoreDefesa = NULL;
    FILE *file;
    // abrindo arquivo com permissão de leitura
    file = fopen("pokemon.txt", "r");
    // caso o arquivo não exista
    if(file == NULL) {
        printf("Erro! Arquivo não existe \nBaixe e coloque na mesma pasta do programa.\n\n");
        return 0;
    }
    // leitura da primeira linha do arquivo
    fscanf(file, "%d\n", &numPokemons);
    //declarando um vetor com o número exato de pokemons do arquivo
    TItem pokemons[numPokemons], pokemonsAtaque[numPokemons], pokemonsDefesa[numPokemons];
    // leitura do arquivo restante
    for(int i = 0; i < numPokemons; i++) {
        TItem item;
        fscanf(file, "%s %d %d %d\n", item.pokemon, &item.hp, &item.ataque, &item.defesa);
        // alimentando a árvore com base no hp
        item.id = item.hp;
        arvoreHp = insertTree(arvoreHp, item);
        // alimentando a árvore com base no ataque
        item.id = item.ataque;
        arvoreAtaque = insertTree(arvoreAtaque, item);
        pokemonsAtaque[i] = item;
        // alimentando a árvore com base na defesa
        item.id = item.defesa;
        arvoreDefesa = insertTree(arvoreDefesa, item);
        pokemonsDefesa[i] = item;
        // alimentando um vetor na ordem do arquivo
        pokemons[i] = item;
    }
    do {
        menu();
        scanf("%d", &opcao);
        if(opcao == 1) {
            // listando os pokemons com os dez maiores ataques
            printf("\nListando os pokemons com os dez maiores ataques:\n");
            dezMaioresAtaques(pokemonsAtaque, numPokemons);
            printf("\n");
        }
        else if(opcao == 2) {
            // listando os pokemons com os dez menores ataques
            printf("\nListando os pokemons com os dez maiores ataques:\n");
            dezMenoresDefesas(pokemonsDefesa, numPokemons);
            printf("\n");
        }
        else if(opcao == 3) {
            // listando os pokemons em ordem crescente de acordo com o seu HP
            printf("\nListando os pokemons em ordem crescente de acordo com o seu HP:\n");
            showtree(arvoreHp);
        }
        else if(opcao == 4) {
            // pesquisando todos os pokemons com ataque igual a 130
            printf("\nPesquisando todos os pokemons com ataque igual a 130:\n");
            pesquisaTodosAtaque(arvoreAtaque, 130);
            printf("\n");
        }
        else if (opcao == 5) {
            // pesquisando pokemon com ataque igual a 131 na arvore
            TItem *itemArvore = pesquisaModificada(arvoreAtaque, 131);
            printf("Pokemon %s com ataque igual a 131 achado na árvore!\n", itemArvore->pokemon);
            printf("\n");
            //ordenando o vetor para empreender a busca binaria
            mergeSort(pokemonsAtaque, 0, numPokemons-1);
            // pesquisando pokemon com ataque igual a 131 no vetor
            TItem itemVetor = buscaBinaria(pokemonsAtaque, 131, numPokemons);
            printf("Pokemon %s com ataque igual a 131 achado no vetor!\n", itemVetor.pokemon);
            printf("\n");
        }
        else if(opcao == 6) printf("Adeus!\n");
        else printf("Opção Inválida!\n");
    } while (opcao != 6);
    fclose(file);
    return 0;
}