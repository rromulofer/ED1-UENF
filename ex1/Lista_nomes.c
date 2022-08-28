//ROMULO FERNANDES

//Bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Código para manipulação de um arquivo, contendo Nomes e o Número de telefone de cada pessoa, 
e criando uma árvore binária para a manipulação.
	-Ao executar, terá um menu com as opções disponiveis para o usuário escolher
		1 - Inserir um novo nome (no Arquivo)
        2 - Imprimir a lista inteira (Ler do Arquivo, Gerar Arvore, Percorrer Arvore
        3 - Buscas na arvore um nome especifico (Ler do Arquivo, Gerar Arvore, Buscar Palavra
        4 - Eliminar um nome existente         
        5 - Finalizar
    -Opção 1: 
		- Primeiramente o usuário informará quantos nomes deseja inserir
		- Após, o usuário irá informar os nomes e os números desejados
		- Com isso os dados serão inseridos no arquivo chamado "teste"
    -Opção 2:
    	-Programa irá imprimir todos os nomes e números armazenados no arquivo
    -Opção 3:
    	- O usuário irá informar o nome que deseja buscar
    	- Após informar o programa irá imprimir o nome digitado pelo usuário
    	e o seu respectivo número de telefone
    -Opção 4:
    	- O usuário irá informar o nome que deseja eliminar
    	- O nome e número será removido do arquivo
    -Opção 5:
		- O programa irá encerrar
    	
*/

FILE *arquivo;

typedef struct vocabulo{
   char palavra[40];
   char cg[10];
   char def[100];     
}VOCAB;

typedef struct nodo{ 
   VOCAB e; 
   struct nodo *esq; 
   struct nodo *dir; 
} NO; 
  
typedef NO *ARV; 
  
 
// Função para criar uma nova árvore
ARV nova_arv() 
{ 
    return NULL; 
} 
  
int EMPTY (ARV a)
{ return (a == NULL);}  
  
  
//  Função para inserir um novo elemento b na árvore a
ARV insere (ARV a, VOCAB b) 
{ ARV nova; 
  if (EMPTY(a))
    { 
      nova = (ARV) malloc (sizeof(NO)); 
      nova->esq = NULL; 
      nova->dir = NULL;
      nova->e = b; 
      return nova; 
    } 
  else 
    { if ( strcmp(a->e.palavra,b.palavra) < 0 ) 
        a->dir = insere(a->dir, b); 
      else 
        a->esq = insere(a->esq, b);  // Repetições são inseridas na esquerda 
      return a; 
    } 
} 


// Função para procurar um elemento na árvore  
ARV procura (ARV a , char *b) 
{ 
  VOCAB c;
  if (EMPTY(a))          return NULL; 
  else 
    if ( strcmp(a->e.palavra,b) == 0 )  return a; 
    else 
      if ( strcmp(a->e.palavra,b) < 0 ) 
                      return procura (a->dir, b); 
      else            return procura (a->esq, b); 
} 

  
// Função para percorrer a árvore respeitando o critério IN ORDER  
void inOrder (ARV a) 
{ 
  if (! EMPTY(a) ) 
    { inOrder(a->esq);
      printf("\n%s: %s ", a->e.palavra,a->e.cg);
      inOrder(a->dir); 
    } 
} 

  
//Função para buscar uma palavra na árvore  
ARV busca (char termo[], ARV a) 
{ 
  ARV b;
  b = a;
  while (!EMPTY(b)){
     if (strcmp(b->e.palavra, termo) == 0) 
          return b;
     else 
         if (strcmp(b->e.palavra,termo) > 0)
             b = b->esq;
         else b = b->dir;
  }
  return NULL;
} 

//Função para inserção de novos nomes e números no arquivo
void inserirContrib(){
VOCAB e;
int i=0;     
    system("cls"); 
    printf("\n\n Quantos nomes deseja inserir? ");
    scanf("%d",&i);
    
    arquivo = fopen("teste","ab");  // ab: opção de abertura do arquivo (append binary)
    while(i > 0){
      printf("\n\nNovo nome:  ");
      scanf("%s",e.palavra);
      printf("Numero de telefone:  ");
      scanf("%s",e.cg);
      fflush(stdin); 
      fflush(stdin);
      fwrite(&e,sizeof(e),1,arquivo);
      i--;
   }   
   fclose(arquivo);     
}

ARV gerarArv(ARV a){
VOCAB e;    
    arquivo = fopen("teste","rb");
    do{
    if (fread(&e,sizeof(e),1, arquivo) == 1) 
        a=insere(a,e);   
    }while (!feof(arquivo));
    
    fclose(arquivo);   
    return a;  
}    


int main(){
    
    char termo[50];
    ARV a;   
    ARV b;
    int opcao=0;
   
    while (opcao != 5){
        system("cls");    
        printf("->->->->->->->->->-> MENU PRINCIPAL <-<-<-<-<-<-<-<-<-<-"); 
        printf("\n\n  1 - Inserir um novo nome (no Arquivo)"); 
        printf("\n  2 - Imprimir a lista inteira (Ler do Arquivo, Gerar Arvore, Percorrer Arvore)"); 
        printf("\n  3 - Buscas na arvore um nome especifico (Ler do Arquivo, Gerar Arvore, Buscar Palavra)"); 
        printf("\n  4 - Eliminar um nome existente");          
        printf("\n  5 - Finalizar");
		printf("\n->->->->->->->->->->->->->-><-<-<-<-<-<-<-<-<-<-<-<-<-<-");          
        printf("\n\n  Digite a opcao desejada: ");
        scanf("%d", &opcao);
        
        switch(opcao){
            case 1: inserirContrib();
                    break; 
            case 2: system("cls");
                    a=NULL;
                    a=gerarArv(a);
					//Neste caso chama a função inOrder que irá imprimir todos os nomes e números da lista 
                    inOrder(a);  
                    system("pause>>null");            
                    break;
            case 3: system("cls");
                    printf("Digite o nome que deseja procurar: ");
                    scanf("%s", &termo);
                    a=NULL;
                    a=gerarArv(a);  // Lê do arquivo e gera a árvore
                    b=busca(termo,a); 
                    
                    // Printa o nome encontrado e o número de telefone correspondente ao nome
                    if (b!=NULL) printf("\nNome encontrado: %s - %s", b->e.palavra, a->e.cg); 
                    system("pause>>null");            
                    break;
			case 4:	system("cls");               
            
        }              
    }   

    return 0;    
    }
