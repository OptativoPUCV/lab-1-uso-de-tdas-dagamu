#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "arraylist.h"
#include "stack.h"

//#include "exercises.h"

//Funciones auxiliares que puedes utilizar para debuggear tus ejercicios
//NO MODIFICAR
void imprime_lista(List *L) {
   int *dato;
   dato = (int*)first(L);
   printf("[");
   while(dato != NULL) {
      printf("%d ", *dato);
      dato = (int*)next(L);
   }
   printf("]\n");

}

//Ojo que la pila se vacía al imprimir y se imprime en orden inverso
//NO MODIFICAR
void imprime_y_vacia_pila(Stack *P) {
   void *dato;
   printf("[");
   while((dato = pop(P)) != NULL) {
      printf("%d ", *(int*)dato);
   }
   printf("]\n");
}

/* 
Ejercicio 1.
Crea una Lista y agrega punteros a elementos del 1 al 10.
Recuerda que la lista almacena punteros, por lo que
debes reservar memoria para cada elemento que agregues.
Al finalizar retorna la lista creada.
*/

List* crea_lista() {
   List* L = create_list();
   int *ptr;

   for(int i = 1; i <= 10; i++)
   {
      ptr = malloc(sizeof(int));
      *ptr = i;
      pushBack(L, ptr); 
   }

   return L;
}

/*
Ejercicio 2.
Crea una función que reciba una lista de enteros (int*) y 
retorne la suma de sus elementos.
*/
int sumaLista(List *L) {
   int *ptr = first(L);
   int sum = 0;
   while( ptr != NULL )
   {
      sum += *ptr;
      ptr = next(L);
   }
   return sum;
}

/*
Ejercicio 3.
Crea una función que reciba una lista de punteros a int (int*) y
un entero elem. La función debe eliminar todos los elementos 
de la lista que sean iguales a elem.
Asume que popCurrent luego de eliminar un elemento se
posiciona en el elemento anterior.
*/

void eliminaElementos(List*L, int elem){
   int *ptr = first(L);

   do if( *ptr == elem ) popCurrent(L);
   while( (ptr = next(L)) != NULL );
}

/*
Ejercicio 4.
La función copia los punteros de la pila P1 en la pila P2.
El orden de ambas pilas se debe mantener.
Puedes usar una pila auxiliar.
*/

void copia_pila(Stack* P1, Stack* P2) {
   Stack* aux_stack = create_stack();

   void *ptr;
   while( (ptr = top(P1)) != NULL )
   {
      push(aux_stack, ptr);
      pop(P1);
   }

   while( (ptr = top(aux_stack)) != NULL )
   {
      push(P1, ptr);
      push(P2, ptr);
      pop(aux_stack);
   }

   free(aux_stack);

}

/*
Ejercicio 5.
La función verifica si la cadena de entrada tiene sus 
paraéntesis balanceados. Retorna 1 si están balanceados,
0 en caso contrario.
*/

int parentesisBalanceados(char *cadena) {
   Stack* pila = create_stack();
    
    for (int i = 0; cadena[i] != '\0'; i++) {
        char c = cadena[i];

        if (c == '(' || c == '[' || c == '{') {
            char *charPtr = malloc(sizeof(char));
            *charPtr = c;
            pushBack(pila, charPtr);
        } 
        else if (c == ')' || c == ']' || c == '}') {
            char *topChar = (char *) top(pila);
            if (topChar == NULL) {  // Pila vacía
                free(pila);
                return 0;
            }

            if ((c == ')' && *topChar != '(') ||
                (c == ']' && *topChar != '[') ||
                (c == '}' && *topChar != '{')) {
                free(topChar);
                free(pila);
                return 0;
            }

            free(pop(pila));
        }
    }

    int resultado = top(pila) == NULL;

    // Liberar memoria restante
    while (top(pila) != NULL) {
        free(pop(pila));
    }
    free(pila);

    return resultado;
}

