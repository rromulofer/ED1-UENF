//ROMULO FERNANDES

// C++
// Bibliotecas
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

/*
- Programa calcula o balanceamento de uma �rvore bin�ria-
- O usu�rio ter� que digitar a quantidade de n�s que deseja 
- Ap�s, informar� o elemento que deseja inserir em cada n�
- Em seguida o programa ir� informar:
	- Altura da �rvore
	- Altura esquerda
	- Altura direita
	- Fator de Balanceamento
*/

using namespace std;

class No {
public:
    int info;   // Chave
    No* sae;    // Ponteiro para a sub-�rvore da esquerda
    No* sad;    // Ponteiro para a sub-�rvore da direita

    No (int i){ // Construtor
        info = i;
        sae = sad = 0;
    }

    bool isFolha(){
        return (this->sae==0 && this->sad==0);
    }
};

class Arvore {
public:
    No* raiz;

    Arvore(){ // Construtor-padr�o
        raiz = 0;
    }

    No* localiza(int valor){
        No* atual = raiz;      // Come�amos pela raiz
        if (!atual) return 0;  // �rvore vazia!
        while (atual->info != valor) {
            if (valor < atual->info) {
            	atual = atual->sae;
            } else {
                atual = atual->sad;
            }
            if (!atual) return 0;  // N�o h� filho, n�o encontrou!
        }
        return atual;              // Encontrou
    }

    void insere(int valor) {
        No* novo = new No(valor);  // Cria o novo n�
        if (!raiz) {
            raiz = novo;
            return;
        }
        No* atual = raiz;  // Come�amos pela raiz
        No* pai = 0;       // Guardamos o pai de cada um
        while (true) {
            pai = atual;   // Atualiza o pai a cada itera��o
            if (valor < atual->info) { // Vai para esquerda?
                atual = atual->sae;
                if (!atual) {          // Fim da linha?
                    pai->sae = novo;   // Insere aqui
                    return;
                }
            } else {
                atual = atual->sad;    // Vai para direita?
                if (!atual) {          // Fim da linha?
                    pai->sad = novo;   // Insere aqui
                    return;
                }
            }
        }
    }

    void emOrdem(No* atual) {
        if (!atual) return;  // N� vazio
        emOrdem(atual->sae);
        cout << atual->info << " ";
        emOrdem(atual->sad);
    }

    void preOrdem(No* atual) {
        if (!atual) return;
        cout << atual->info << " ";
        preOrdem(atual->sae);
        preOrdem(atual->sad);
    }

    void posOrdem(No* atual) {
        if (!atual) return;
        posOrdem(atual->sae);
        posOrdem(atual->sad);
        cout << atual->info << " ";
    }

    int menor(){
        No* atual = raiz;
        if (!atual) return 0;
        while(atual->sae){
            atual = atual->sae;
        }
        return atual->info;
    }

    int maior(){
        No* atual = raiz;
        if (!atual) return 0;
        while(atual->sad){
            atual = atual->sad;
        }
        return atual->info;
    }

    No* sucessor(No* atual){
        No* pai = atual;
        atual = atual->sad; // Primeira � direita
        if (atual->sae != 0){
            while(atual->sae != 0){
                pai = atual;
                atual=atual->sae;
            }
            if (atual->sad != 0){
                pai->sae = atual->sad;
            } else {
                pai->sae = 0;
            }
        } else {
            pai->sad = atual->sad;
        }
        return atual;
    }

    void remove(int valor){
        No* atual = raiz; // Come�amos pelo in�cio
        No* pai = 0; // Raiz n�o tem
        while(atual->info != valor){
            pai = atual;
            if (valor < atual->info) {
                atual = atual->sae;
            } else {
                atual = atual->sad;
            }
            if (atual == 0) return; // N�o encontrou o valor a remover
        }
        if (atual->sae==0 && atual->sad==0) { // Remove folhas
            if (atual == raiz) {
                raiz = 0;
                delete atual;
                return;
            }
            if (pai->sae == atual) {
                pai->sae = 0;
            } else {
                pai->sad = 0;
            }
            delete atual;
        } else if (atual->sad == 0) { // Tem um filho esquerdo
            if (atual==raiz){
                raiz = atual->sae;
                delete atual;
                return;
            }
            if (pai->sae == atual){
                pai->sae = atual->sae;
            } else {
                pai->sad = atual->sae;
            }
        } else if (atual->sae == 0) { // Tem um filho direito
            if (atual==raiz) {
                raiz = atual->sad;
                delete atual;
                return;
            }
            if (pai->sae == atual) {
                pai->sae = atual->sad;
            } else {
                pai->sad = atual->sad;
            }
            delete atual;
        }
        if (atual->sae!=0 && atual->sad!=0){ // Remove n� com dois filhos
            No* suces = sucessor(atual);
            if (pai->sae == atual) {
                pai->sae = suces;
            } else {
                pai->sad = suces;
            }
            suces->sae = atual->sae;
            suces->sad = atual->sad;
            delete atual;
        }
    }

    int nivel(int valor){
        No* atual = raiz;      // Come�amos pela raiz
        if (atual==0) return 0;  // �rvore vazia!
        int n = 1;
        while (atual->info != valor) {
            if (valor < atual->info) {
            	n++;
            	atual = atual->sae;
            } else {
                n++;
                atual = atual->sad;
            }
            if (atual==0) return 0;  // N�o h� filho, n�o encontrou!
        }
        return n;
    }

    int altura(No* atual) {
        if (atual == 0) return 0; // A altura de uma �rvore vazia � 0.
        int altEsq = altura(atual->sae);
        int altDir = altura(atual->sad);
        if (altEsq > altDir) return altEsq + 1;
        else return altDir + 1;
        
    }

    int qtdNos(No* atual) {
        if (atual == 0) return 0; // A altura de uma �rvore vazia � 0.
        int qtdEsq = qtdNos(atual->sae);
        int qtdDir = qtdNos(atual->sad);
        return qtdEsq + qtdDir;
    }

    void insereBal(int vet[], int ini, int fim) {
        if (fim < ini) return;
        int meio = (ini + fim)/2;
        insere(vet[meio]);
        insereBal(vet,ini,meio-1);
        insereBal(vet,meio+1,fim);
    }
    
    int balanceado(No* atual) {
        if (atual == 0) return 0; // A altura de uma �rvore vazia � 0.
        int altEsq = altura(atual->sae);
        int altDir = altura(atual->sad);
        cout << "\n  -Altura esquerda: " << altEsq << endl; // Printa a altura esquerda
        cout << "\n  -Altura direita: " << altDir << endl; // Printa a altura direita

		return altEsq - altDir;
    }
    
};

int main() {
    int tam;    // Tamanho do vetor ou quantidade de elementos da �rvore
    int *vet;   // Vetor auxiliar na montagem da �rvore balanceada
    Arvore arv; // �rvore
	
	cout << "->->->->-> Calcula Fator de Balanceamento <-<-<-<-<-\n\n";
    cout << "  -Informe a quantidade de nos da arvore: ";
    cin  >> tam;
    vet = new int[tam];
    
	system("cls");
	
    // Insere no vetor para depois ordenar
    for (int i = 0; i < tam; i++)	{
        cout << "  -Digite o elemento " << i << ": ";
        cin  >> vet[i];
	}

	// Ordenando o vetor
	int aux;
	for (int i = 0; i < tam-1; i++){
	    for (int j = 0; j < tam-1-i; j++){
	        if (vet[j] > vet[j+1]) { // Troca
	            aux = vet[j];
	            vet[j] = vet[j+1];
	            vet[j+1] = aux;
	        }
	    }
	}

    // Criando a �rvore balanceada!
    arv.insereBal(vet, 0, tam-1);
	
	system("cls");
    cout << "\n  -Altura da arvore: " << arv.altura(arv.raiz)-1 << endl;
    cout << "\n  -Balanceamento da arvore: " << arv.balanceado(arv.raiz) << endl;
    cout << "\n";
    cout << "->->->->->-> FIM <-<-<-<-<-<-\n\n";
	system("pause");
	return 0;
}
