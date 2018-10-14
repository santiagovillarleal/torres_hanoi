#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_SACAR_TOR_BALEIRA -4
#define ERR_METER_ELEM_GRANDE -3
#define ERR_METER_TOR_CHEA    -2
#define ERR_METER_ELEM_0      -1
#define OK                     0
#define ERR_USO                1

#define TRUE                   1
#define FALSE                  0
#define TAM_MAX_OPC           50

void imprimir_uso(char *prog)
{
  printf("%s <N>\n", prog);
}

void zeros(unsigned int *torre, unsigned int tam)
{
  for (unsigned int i = 0;i<tam;i++)
  {
    torre[i]=0;
  }
}

void inicializar(unsigned int *torre1, unsigned int *torre2, unsigned int *torre3, unsigned int tam)
{
  for (unsigned int i = 0;i<tam;i++)
  {
    torre1[i]=i+1;
  }
  zeros(torre2, tam);
  zeros(torre3, tam);
}

unsigned char torre_baleira(unsigned int *torre)
{
  return ((!torre)||(!torre[0]));
}

unsigned char torre_chea(unsigned int *torre, unsigned int tam)
{
  return ((torre)&&(torre[tam-1]));
}

int sacar(unsigned int *torre, unsigned int tam)
{
  int elemento = 0, i=0;
  if (torre_baleira(torre)) return ERR_SACAR_TOR_BALEIRA;
  elemento=torre[0];
  for (i=1;(i<tam)||(torre[i]);i++)
  {
    torre[i-1]=torre[i];
  }
  for (;i<=tam;i++)
  {
    torre[i-1]=0;
  }

  return elemento;

}

int meter(int elemento, unsigned int *torre, unsigned int tam)
{
  if (!elemento) return ERR_METER_ELEM_0;
  if (torre_chea(torre,tam)) return ERR_METER_TOR_CHEA;
  if ((!torre_baleira(torre))&&(elemento>torre[0])) return ERR_METER_ELEM_GRANDE;
  for (unsigned int i=tam-1;i>0;i--)
  {
    torre[i]=torre[i-1];
  }
  torre[0]=elemento;
  return OK;
}

int mover(unsigned int *torreA, unsigned int *torreB, unsigned int tam)
{
  int elemento = 0, res_meter = OK, res_sacar = OK;
  res_sacar = sacar(torreA, tam);
  if (res_sacar<0) return res_sacar;
  elemento=res_sacar;
  if ((res_meter = meter(elemento, torreB, tam)) == ERR_METER_ELEM_GRANDE)
  {
    meter(elemento, torreA, tam);
    return res_meter;
  }
  return res_meter;
}

void ler_torre(char *nome_torre, unsigned int *torre, unsigned int tam)
{
  printf("%s: ", nome_torre);
  if (torre_baleira(torre))
  {
    printf("baleira.\n");
    return;
  }

  for (unsigned int i = 0;i<tam;i++)
  {
    printf("%u ", torre[i]);
  }
  printf("\n");
}

void axuda()
{
  printf("valores validos:\n");
  printf("A-B: mover de torre A a torre B, sendo A,B={1,2,3}. Exemplos: 1-2, 3-1,...\n");
  printf("fora: acaba o xogo.\n\n");
}

void ler_torres(unsigned int *torre1, unsigned int *torre2, unsigned int *torre3, unsigned int tam)
{
  printf("Estado actual: \n");
  ler_torre("torre1", torre1, tam);
  ler_torre("torre2", torre2, tam);
  ler_torre("torre3", torre3, tam);
}

unsigned char torre_valida(char t)
{
  return ((t=='1')||(t=='2')||(t=='3'));
}

int main(int argc, char *argv[])
{
  unsigned int n = 0, *torre1, *torre2, *torre3, *torreA, *torreB;
  int res_mover=0;
  char opc[TAM_MAX_OPC];

  if (argc!=2)
  {
    imprimir_uso(argv[0]);
    exit(ERR_USO);
  }

  n = atoi(argv[1]);
  torre1=(unsigned int *)malloc(sizeof(unsigned int )*(n));
  torre2=(unsigned int *)malloc(sizeof(unsigned int )*(n));
  torre3=(unsigned int *)malloc(sizeof(unsigned int )*(n));

  inicializar(torre1, torre2, torre3, n);
  axuda();
  ler_torres(torre1, torre2, torre3, n);

  while (TRUE)
  {
    torreA=torreB=NULL;
    scanf("%s", opc);
    if (!strcmp(opc, "fora")) break;

    //A-B, onde A={1,2,3} e B={1,2,3}
    if ((strlen(opc)==3) && (opc[1]='-') &&
        torre_valida(opc[0]) && torre_valida(opc[2]))
    {
      switch (opc[0])
      {
        case '1': torreA=torre1;
                  break;
        case '2': torreA=torre2;
                  break;
        case '3': torreA=torre3;
                  break;
        default:  break;
      }
      switch (opc[2])
      {
        case '1': torreB=torre1;
                  break;
        case '2': torreB=torre2;
                  break;
        case '3': torreB=torre3;
                  break;
        default:  break;
      }
    }
    if ((!torreA)||(!torreB))
    {
      axuda();
      ler_torres(torre1, torre2, torre3, n);
      continue;
    }
    if ((res_mover = mover(torreA, torreB, n))<0)
    {
      if (res_mover == ERR_METER_ELEM_GRANDE) printf("O estado actual das torres non permite ese movemento.\n");
      else printf("Fallo ó mover: %d\n", res_mover);
    }
    ler_torres(torre1, torre2, torre3, n);

    if (torre_chea(torre2, n))
    {
      printf("Acabache.\n");
    }
  }
  free(torre1);
  free(torre2);
  free(torre3);
}

