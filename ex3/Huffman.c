//ROMULO FERNANDES

// Bibliotecas
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

/*
- O programa primeiramente pergunta se o usu�rio deseja:
	1- Codificar
	2- Decodificar
- Caso o usu�rio digite 1:
	- O programa ir� pedir a palavra que deseja Codificar
- Caso o usu�rio digite 2:
	

*/

#define MAX_TREE_HT 100 
 char mat[30][13];
 int conti=0;
 
// N� da �rvore de Huffman 
struct MinHeapNode { 
  
    // Um dos caracteres de entrada
    char data; 
  
    // Frequencia do caracter 
    unsigned freq; 
  
    // Filho esquerdo e direito deste n� 
    struct MinHeapNode *left, *right; 
}; 
  
// Min Heap: Cole��o de n�s min-heap (ou �rvore de Huffman)
struct MinHeap { 
  
    unsigned size; 

    unsigned capacity; 
  
    // Matriz de ponteiros de n� de minheap 
    struct MinHeapNode** array; 
}; 
  
/* Fun��o aloca um novo min heap node com determinado 
caractere e frequ�ncia do personagem */
struct MinHeapNode* newNode(char data, unsigned freq) 
{ 
    struct MinHeapNode* temp 
        = (struct MinHeapNode*)malloc
(sizeof(struct MinHeapNode)); 
  
    temp->left = temp->right = NULL; 
    temp->data = data; 
    temp->freq = freq; 
  
    return temp; 
} 
  
// Fun��o para criar uma pilha m�nima de determinada capacidade
struct MinHeap* createMinHeap(unsigned capacity) 
  
{ 
  
    struct MinHeap* minHeap 
        = (struct MinHeap*)malloc(sizeof(struct MinHeap)); 
  
    // o tamanho atual � 0 
    minHeap->size = 0; 
  
    minHeap->capacity = capacity; 
  
    minHeap->array 
        = (struct MinHeapNode**)malloc(minHeap-> 
capacity * sizeof(struct MinHeapNode*)); 
    return minHeap; 
} 
  
// Fun��o para troca dois n�s de heap m�nimo
void swapMinHeapNode(struct MinHeapNode** a, 
                     struct MinHeapNode** b) 
  
{ 
  
    struct MinHeapNode* t = *a; 
    *a = *b; 
    *b = t; 
} 
  
// Fun��o minHeapify p
void minHeapify(struct MinHeap* minHeap, int idx) 
  
{ 
  
    int smallest = idx; 
    int left = 2 * idx + 1; 
    int right = 2 * idx + 2; 
  
    if (left < minHeap->size && minHeap->array[left]-> 
freq < minHeap->array[smallest]->freq) 
        smallest = left; 
  
    if (right < minHeap->size && minHeap->array[right]-> 
freq < minHeap->array[smallest]->freq) 
        smallest = right; 
  
    if (smallest != idx) { 
        swapMinHeapNode(&minHeap->array[smallest], 
                        &minHeap->array[idx]); 
        minHeapify(minHeap, smallest); 
    } 
} 
  
// Fun��o para verificar se o tamanho da pilha � 1 ou n�o
int isSizeOne(struct MinHeap* minHeap) 
{ 
  
    return (minHeap->size == 1); 
} 
  
// Fun��o para extrair n� de valor m�nimo do heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap) 
  
{ 
  
    struct MinHeapNode* temp = minHeap->array[0]; 
    minHeap->array[0] 
        = minHeap->array[minHeap->size - 1]; 
  
    --minHeap->size; 
    minHeapify(minHeap, 0); 
  
    return temp; 
} 
  
// Fun��o para inserir um novo n� para Min Heap
void insertMinHeap(struct MinHeap* minHeap, 
                   struct MinHeapNode* minHeapNode) 
  
{ 
  
    ++minHeap->size; 
    int i = minHeap->size - 1; 
  
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) { 
  
        minHeap->array[i] = minHeap->array[(i - 1) / 2]; 
        i = (i - 1) / 2; 
    } 
  
    minHeap->array[i] = minHeapNode; 
} 
  
// Fun��o para construir pilha m�nima 
void buildMinHeap(struct MinHeap* minHeap) 
  
{ 
  
    int n = minHeap->size - 1; 
    int i; 
  
    for (i = (n - 1) / 2; i >= 0; --i) 
    
        minHeapify(minHeap, i); 
} 
  
  
// Fun��o para imprimir um array de tamanho n
void printArr(int arr[], int n , int x) 
{ 
    int i; 
    char p;
    for (i = 0; i < n; ++i) {
	
        printf("%d", arr[i]);  
        mat[x][i+1]=arr[i];
}
  
    printf("\n"); 
} 


void codifica(char *input)
{
	int x;
	printf("  Resultado -> ");
	for(int i=0;i<strlen(input);i++)
	{
		for(int j=0;j<29;j++)
		{		
			conti=0;			
			if(input[i]==mat[j][0])
			{	
				x=0;
				while(mat[j][x+1]!=9)
				{					
					printf("%d ", mat[j][x+1]);
					x++;
				}
			}
		}
	}
	printf("\n");
	
}
	
	
int decodifica(int *input,int QuantCodigos)
{
	int x;
	printf("  Resultado -> ");
	int salvapos=0;
	int i=salvapos;
	
	for(int linha=0;linha<29;linha++)		
	{ 
		for(int coluna=0;coluna<11;coluna++)
		{				
			if(mat[linha][coluna+1]==input[i])
			{
				if(mat[linha][coluna+2]!=0 && mat[linha][coluna+2]!=1)
				{
					printf("%c",mat[linha][0]);
					i++;
					salvapos=i;
					if(salvapos==QuantCodigos)
						{
							return 0;
						}
						else
						{
							linha=0;
							break;	
						}				
				}
				else
				{
				i++;
				}
			} 
			else
			{
				i=salvapos;
				break;
			}
		
		}
		
	}
	printf("\n\n");
}

// Fun��o para verificar se este n� � folha 
int isLeaf(struct MinHeapNode* root) 
  
{ 
  
    return !(root->left) && !(root->right); 
} 
  
/*
Cria um heap m�nimo de capacidade igual ao tamanho e insere todos 
os caracteres de dados [] no heap m�nimo. 
Tamanho inicial de min heap � igual � capacidade  
*/
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) 
  
{ 
  
    struct MinHeap* minHeap = createMinHeap(size); 
  
    for (int i = 0; i < size; ++i) 
        minHeap->array[i] = newNode(data[i], freq[i]); 
  
    minHeap->size = size; 
    buildMinHeap(minHeap); 
  
    return minHeap; 
} 
  
// Fun��o principal que constr�i a �rvore Huffman 
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) 
  
{ 
    struct MinHeapNode *left, *right, *top; 
  
    /* Etapa 1: criar um heap m�nimo de capacidade
    igual ao tamanho. Inicialmente, existem
    modos iguais ao tamanho.. */
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size); 
  
    // Itera enquanto o tamanho do heap n�o se torna 1
    while (!isSizeOne(minHeap)) { 
  
        // Etapa 2: Extrai o m�nimo de dois
        // itens de freq do heap m�nimo 
        left = extractMin(minHeap); 
        right = extractMin(minHeap); 
           
        /* Etapa 3: Criar um novo n�
        interno com frequ�ncia igual a
        soma das frequ�ncias dos dois n�s.
        Faz os dois n�s extra�dos como
        filhos esquerdo e direito deste novo n�.
        Adiciona este n� ao heap m�nimo
        '$' � um valor especial para n�s internos, n�o usado.*/
        top = newNode('$', left->freq + right->freq); 
  
        top->left = left; 
        top->right = right; 
  
        insertMinHeap(minHeap, top); 
    } 

    // Etapa 4: o n� restante � o
    // n� raiz e a �rvore est� completa.
    return extractMin(minHeap); 
} 
  
// Imprime c�digos de Huffman da raiz da �rvore de Huffman.
// Ele usa arr [] para armazenar c�digos
   void MostraFolhas(MinHeapNode *a, int arr[])
{
	int i=0;
// OU poderia retornar assim que "a" fosse NULL
// if (a == NULL)
//   return;
  if(a != NULL)
  {
    if(a->left == NULL &&  a->right == NULL)
    {
      printf("%c -> %d\t\n", a->data,arr[i]);
      
      return;
    }
    
    MostraFolhas(a->left,arr);
    MostraFolhas(a->right,arr);
  }
} 
void printCodes(struct MinHeapNode* root, int arr[], int top) 
  
{ 
    if (root->left) { 
  
        arr[top] = 0; 
        printCodes(root->left, arr, top + 1); 
    } 
  
    if (root->right) { 
  
        arr[top] = 1; 
        printCodes(root->right, arr, top + 1); 
    } 
  
    /* Se este for um n� folha, ent�o
    cont�m uma das entradas
    caracteres, imprime o caractere
    e seu c�digo de arr [] */
    if (isLeaf(root)) { 
        
        printf("%c: ", root->data); 
        mat[conti][0]=root->data;
        printArr(arr, top, conti); 
        
        printf("%c\n",mat[conti][0]=root->data);
        conti++;
        
        
    } 
} 

//A fun��o principal que constr�i uma �rvore de Huffman 
void HuffmanCodes(char data[], int freq[], int size) 
  
{ 
    // Construir �rvore de Huffman
    struct MinHeapNode* root 
        = buildHuffmanTree(data, freq, size); 
  
    /*Imprimir c�digos Huffman usando
    a �rvore Huffman constru�da acima*/
    int arr[MAX_TREE_HT], top = 0; 
  
    printCodes(root, arr, top); 
} 	

 
  

int main() 
{ 
  
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g','h', 'i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' ','/','.'};
    int freq[] = {81, 15, 28, 43, 128, 23, 20, 61, 71, 2, 1, 40, 24, 69, 76, 20, 1, 61, 64, 91, 28, 10, 24, 1, 20, 1, 90,23,1};
   int i;
   char input[50];
   int linha, coluna;
   char num[50];
	

 
			for(linha=0;linha<29;linha++)
	{ 
		for(coluna=0;coluna<11;coluna++)
		{	
			mat[linha][coluna+1]=9;
			
		}
	
	} 
    //Pega o tamanho
    int size = sizeof(arr); // / sizeof(arr[0]); 
    HuffmanCodes(arr, freq, size); 

  	printf("\n\n->->->->->->->->-> MENU DE OPCOES <-<-<-<-<-<-<-<-<-");
    printf("\n\n  1- Codifica");
    printf("\n  2- Decodifica");
    printf("\n\n  -Digite a opcao desejada: ");
    scanf("%d", &i);
    system("cls");
   
   if(i == 1){
   	
   		printf("\n  -Digite a Palavra que deseja codificar: ");
   		scanf("%s",input);
   		codifica(input);
   }
   else{
   if(i == 2){
   	
		printf("\n  -Digite o Codigo que deseja decodificar: ");
		scanf ("%s",num);
		int passaInt[strlen(num)];
		
		for(int contador=0;contador<strlen(num);contador++)//Transforma a String para Inteiro
		{
	    	passaInt[contador]=(int)num[contador] -48;
		
		}	
		
		decodifica(passaInt,strlen(num));
	}
	else{
		printf("----- Opcao nao existe, tente novamente! -----\n\n");
	}
	}
	
	printf("\n\n");
	system("pause");
	return 0; 

} 
