//ROMULO FERNANDES

//Bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*C�digo para manipula��o de um arquivo, contendo Nomes e o N�mero de telefone de cada pessoa, 
e criando uma �rvore bin�ria para a manipula��o.
	-Ao executar, ter� um menu com as op��es disponiveis para o usu�rio escolher
		1 - Inserir um novo nome (no Arquivo)
        2 - Imprimir a lista inteira (Ler do Arquivo, Gerar Arvore, Percorrer Arvore
        3 - Buscas na arvore um nome especifico (Ler do Arquivo, Gerar Arvore, Buscar Palavra
        4 - Eliminar um nome existente         
        5 - Finalizar
    -Op��o 1: 
		- Primeiramente o usu�rio informar� quantos nomes deseja inserir
		- Ap�s, o usu�rio ir� informar os nomes e os n�meros desejados
		- Com isso os dados ser�o inseridos no arquivo chamado "teste"
    -Op��o 2:
    	-Programa ir� imprimir todos os nomes e n�meros armazenados no arquivo
    -Op��o 3:
    	- O usu�rio ir� informar o nome que deseja buscar
    	- Ap�s informar o programa ir� imprimir o nome digitado pelo usu�rio
    	e o seu respectivo n�mero de telefone
    -Op��o 4:
    	- O usu�rio ir� informar o nome que deseja eliminar
    	- O nome e n�mero ser� removido do arquivo
    -Op��o 5:
		- O programa ir� encerrar
    	
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
  
 
// Fun��o para criar uma nova �rvore
ARV nova_arv() 
{ 
    return NULL; 
} 
  
int EMPTY (ARV a)
{ return (a == NULL);}  
  
  
//  Fun��o para inserir um novo elemento b na �rvore a
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
        a->esq = insere(a->esq, b);  // Repeti��es s�o inseridas na esquerda 
      return a; 
    } 
} 


// Fun��o para procurar um elemento na �rvore  
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

  
// Fun��o para percorrer a �rvore respeitando o crit�rio IN ORDER  
void inOrder (ARV a) 
{ 
  if (! EMPTY(a) ) 
    { inOrder(a->esq);
      printf("\n%s: %s ", a->e.palavra,a->e.cg);
      inOrder(a->dir); 
    } 
} 

  
//Fun��o para buscar uma palavra na �rvore  
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

//Fun��o para inser��o de novos nomes e n�meros no arquivo
void inserirContrib(){
VOCAB e;
int i=0;     
    system("cls"); 
    printf("\n\n Quantos nomes deseja inserir? ");
    scanf("%d",&i);
    
    arquivo = fopen("teste","ab");  // ab: op��o de abertura do arquivo (append binary)
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
					//Neste caso chama a fun��o inOrder que ir� imprimir todos os nomes e n�meros da lista 
                    inOrder(a);  
                    system("pause>>null");            
                    break;
            case 3: system("cls");
                    printf("Digite o nome que deseja procurar: ");
                    scanf("%s", &termo);
                    a=NULL;
                    a=gerarArv(a);  // L� do arquivo e gera a �rvore
                    b=busca(termo,a); 
                    
                    // Printa o nome encontrado e o n�mero de telefone correspondente ao nome
                    if (b!=NULL) printf("\nNome encontrado: %s - %s", b->e.palavra, a->e.cg); 
                    system("pause>>null");            
                    break;
			case 4:	system("cls");               
            
        }              
    }   

    return 0;    
    }
