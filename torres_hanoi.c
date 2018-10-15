#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_MOVER_ELEM_OFFLINE -5
#define ERR_SACAR_TOR_BALEIRA  -4
#define ERR_METER_ELEM_GRANDE  -3
#define ERR_METER_TOR_CHEA     -2
#define ERR_METER_ELEM_0       -1
#define OK                      0
#define ERR_USO                 1

#define TRUE                    1
#define FALSE                   0
#define TAM_MAX_OPC            50

#define TORRE_1 "torre 1"
#define TORRE_2 "torre 2"
#define TORRE_3 "torre 3"

unsigned int *torre1, *torre2, *torre3;

void imprimir_uso(char *prog)
{
  printf("%s <N> [-b|-i]\n", prog);
  printf("N: número de elementos.\n");
  printf("-b: offline, imprime a solución.\n");
  printf("-i: online, permite ao usuario buscar a solución.\n");
  printf("Por defecto a execución será online.\n");
  exit(ERR_USO);
}

unsigned int nome_torre_to_int(char *nome_torre)
{
  if (!strcmp(nome_torre, TORRE_1)) return 1;
  else if (!strcmp(nome_torre, TORRE_2)) return 2;
  else if (!strcmp(nome_torre, TORRE_3)) return 3;
  else return 0;
}

void zeros(unsigned int *torre, unsigned int tam)
{
  for (unsigned int i = 0;i<tam;i++)
  {
    torre[i]=0;
  }
}

void inicializar(unsigned int tam)
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
  int elemento = 0;
  unsigned int i = 0;
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
  printf("O obxetivo é mover os elementos da torre 1 á torre 2, usando como torre auxiliar a torre 3.\n");
  printf("Valores validos:\n");
  printf("A-B: mover de torre A a torre B, sendo A,B={1,2,3}. Exemplos: 1-2, 3-1,...\n");
  printf("fora: acaba o xogo.\n\n");
}

void ler_torres(unsigned int tam)
{
  printf("Estado actual: \n");
  ler_torre(TORRE_1, torre1, tam);
  ler_torre(TORRE_2, torre2, tam);
  ler_torre(TORRE_3, torre3, tam);
}

unsigned char torre_valida(char t)
{
  return ((t=='1')||(t=='2')||(t=='3'));
}

void ler_opcion(unsigned int **p_torreA, unsigned int **p_torreB)
{
  char opc[TAM_MAX_OPC];
  scanf("%s", opc);
  if (!strcmp(opc, "fora")) exit(OK);;
  //A-B, onde A={1,2,3} e B={1,2,3}
  if ((strlen(opc)==3) && (opc[1]='-') &&
      torre_valida(opc[0]) && torre_valida(opc[2]))
  {
    if (opc[0]==opc[2])
    {
      printf("A torre destino non pode ser a mesma que a torre orixe, escolla outra.\n");
      return;
    }
    switch (opc[0])
    {
      case '1': *p_torreA=torre1;
                break;
      case '2': *p_torreA=torre2;
                break;
      case '3': *p_torreA=torre3;
                break;
      default:  break;
    }
    switch (opc[2])
    {
      case '1': *p_torreB=torre1;
                break;
      case '2': *p_torreB=torre2;
                break;
      case '3': *p_torreB=torre3;
                break;
      default:  break;
    }
  }
}

void bucle_xogo_online(unsigned int n)
{
  unsigned int *torreA, *torreB;
  int res_mover=0;

  while (TRUE)
  {
    torreA=torreB=NULL;

    ler_opcion(&torreA, &torreB);
    if ((!torreA)||(!torreB))
    {
      axuda();
      ler_torres(n);
      continue;
    }

    if ((res_mover = mover(torreA, torreB, n))<0)
    {
      if (res_mover == ERR_METER_ELEM_GRANDE) printf("O estado actual das torres non permite ese movemento.\n");
      else printf("Fallo ó mover: %d\n", res_mover);
    }
    ler_torres(n);

    if (torre_chea(torre2, n))
    {
      printf("Acabache.\n");
    }
  }
}

void mover_elem_offline(unsigned int n,
                char *torre_orix,
                char *torre_dest)
{
  unsigned int torre_orix_int = nome_torre_to_int(torre_orix);
  unsigned int torre_dest_int = nome_torre_to_int(torre_dest);
  if ((!torre_orix_int)||(!torre_dest_int))
  {
    printf("Error mover_elem(..): torre non válida.\n");
    exit(ERR_MOVER_ELEM_OFFLINE);
  }
  printf("%u-%u\n", torre_orix_int, torre_dest_int);
}

void hanoi_rec(unsigned int n,
               char *nome_torre_orix,
               char *nome_torre_dest,
               char *nome_torre_aux)
{
  if (n==1)
  {
    mover_elem_offline(n, nome_torre_orix, nome_torre_dest);
    return;
  }
  else
  {
    hanoi_rec(n-1, nome_torre_orix, nome_torre_aux, nome_torre_dest);
  }
  mover_elem_offline(n, nome_torre_orix, nome_torre_dest);
  hanoi_rec(n-1, nome_torre_aux, nome_torre_dest, nome_torre_orix);
}

void xogar(unsigned int n, unsigned char online)
{
  if (online)
  {
    torre1=(unsigned int *)malloc(sizeof(unsigned int )*(n));
    torre2=(unsigned int *)malloc(sizeof(unsigned int )*(n));
    torre3=(unsigned int *)malloc(sizeof(unsigned int )*(n));

    inicializar(n);
    axuda();
    ler_torres(n);

    bucle_xogo_online(n);

    free(torre1);
    free(torre2);
    free(torre3);
  }
  else
  {
    hanoi_rec(n, TORRE_1, TORRE_2, TORRE_3);
  }
}

int main(int argc, char *argv[])
{
  unsigned int n = 0;
  unsigned char online = TRUE;

  if ((argc!=2) && (argc!=3)) imprimir_uso(argv[0]);
  if (argc==3)
  {
    if ((strlen(argv[2])==2) && (argv[2][0]=='-'))
    {
      if (argv[2][1]=='i') online = TRUE;
      else if (argv[2][1]=='b') online = FALSE;
      else imprimir_uso(argv[0]);
    }
    else imprimir_uso(argv[0]);
  }

  n = atoi(argv[1]);
  xogar(n, online);

}
