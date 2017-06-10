/**********************************************************************
 * Algoritmo de treinamento de redes perceptron (saida digital).
 * Otimização de resultados (n iteracoes com erro menor que o desejado).
***********************************************************************/
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>

using namespace std;

#define NUMENT          3	     // numero de entradas da rede.
#define NUMLIN          10	     // numero de linhas da matriz de entradas.
#define NUMCOL          3	     // numero de colunas da matriz de entradas.
#define NUMITE          300      // numero de iteracoes com erro menor que ERRO
#define BETA            0.05	 // fator de ajuste das correcoes (taxa de aprendizado).
#define ERRO            0.0001

FILE *Arq;
double W[NUMENT];
double X[NUMLIN][NUMCOL] = {
/*{0.9,0.25,0},

{0.833333333,0.55,1},
{0.866666667,0.63,1},
{0.166666667,0.2,0},
{0.1,0.65,0},
{0.333333333,0.8,1},
{0.533333333,0.87,1},
{0.6,0.46,0},
{0.233333333,1,1}};
*/
{2,2,4},
{8,8,16},
{32,32,64},
{84,84,168},
{15,15,30},
{5,5,10},
{8,8,16},
{5,7,12},
{5,8,13},
{5,9,14}
};


/*********************************************************************************/
double Somatorio(int Linha)
{
  int i;
  double Som=0;

  for (i=0; i<NUMENT; i++)
    Som += X[Linha][i]*W[i];

  return Som;
}

/*********************************************************************************/
double Atualiza_Pesos(double Som, int Linha)
{
  int i;
  double Erro;

  Erro = X[Linha][NUMCOL-1] - Som;

  fprintf(Arq,"\nErro = %f na linha %i",Erro,Linha);

  for(i=0; i<NUMENT; i++)
  {
    W[i] += BETA*Erro*X[Linha][i];
    fprintf(Arq,"\nPeso W%i atualizado para %f",i,W[i]);
  }

  return Erro;
}

double Calcula_Erro()
{
  int i,j;
  double Saida, Erro = 0;

  for(j=0; j<NUMLIN; j++)
  {
    Saida = 0;
    for(i=0; i<NUMENT; i++)
      Saida += (X[j][i]*W[i]);
    Erro += X[j][NUMCOL-1] - Saida;
  }
  Erro = Erro/NUMLIN;

  return Erro;
}

void Treinar (void)
{
  int i, j, Cont, Linha;
  double Soma, Erro = 1;

  fprintf(Arq,"\nTreinando a rede\n\nPesos Iniciais");

  srand ( time(NULL) );

  for (i=0;i < NUMENT;i++)
  {
    W[i] = (float)((rand()%11)/10.0) * ((rand()%3)-1);
    fprintf(Arq,"\nW%i = %f",i,W[i]);
  }

  i = 0;
  while(Erro > ERRO)
  {
    fprintf(Arq,"\nErro = %f na linha %i",Erro,Linha);
    Linha = i%NUMLIN;
    Soma = Somatorio(Linha);
    Atualiza_Pesos(Soma,Linha);
    Erro = Calcula_Erro();
    i++;
  }

  cout << "\n> Rede treinada" << i;
}

/*********************************************************************************/

int main()
{
	int i;
  double Vet[NUMCOL], Saida;

  char Continua = 'r';

  Arq= fopen("lala.txt","w");

  while(Continua != 'n')
  {
    system("cls");

    if(Continua == 'r')
      Treinar();

    for(i=0; i<NUMENT; i++)
      printf("\nW[%i] = %f",i,W[i]);

    printf("\n\n> Insira os valores de entrada:\n");

    for(i=0; i<NUMENT; i++)
    {
      cout << "\nX[" << i << "] = ";
      cin >> Vet[i];
    }

    Saida = 0;
    for(i=0; i<NUMENT; i++)
      Saida += (Vet[i]*W[i]);

    cout << "\nSaida: " << Saida;
    cout << "\n\nContinua ? (s/n/r)";
    cin >> Continua;
  }
  fclose(Arq);
	return 0;
}
