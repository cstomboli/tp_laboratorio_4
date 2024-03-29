#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this;
    this = (LinkedList *)malloc(sizeof(LinkedList));
    if(this != NULL)
    {
        this->size=0;
        this->pFirstNode = NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        returnAux=this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* pNode = NULL;
    int i;

    if(this!=NULL && nodeIndex>=0 && nodeIndex<ll_len(this))
    {
        pNode=this->pFirstNode;
        for(i=0; i<nodeIndex; i++)
        {
            pNode=pNode->pNextNode;
        }
    }
    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* pNodoAnterior;
    Node* pNodoProximo;
    Node* pNodoNuevo;

    if(this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this))
    {
        if(nodeIndex == 0)
        {
            pNodoAnterior = this->pFirstNode;
        }
        else
        {
            pNodoAnterior = getNode(this,nodeIndex - 1);
        }

        if(pNodoAnterior != NULL) pNodoProximo = pNodoAnterior;
        if(pNodoAnterior == NULL) pNodoProximo = NULL;

        pNodoNuevo = (Node*)malloc(sizeof(Node));
        if(pNodoNuevo != NULL)
        {
            pNodoNuevo->pElement = pElement;
            pNodoNuevo->pNextNode = pNodoProximo;

            if(nodeIndex == 0)
            {

                this->pFirstNode = pNodoNuevo;

            }
            else
                pNodoAnterior->pNextNode = pNodoNuevo;

            this->size++;
            returnAux = 0;
        }
    }
    return returnAux;
}


/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}

/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado             ///pElement nunca se verifica que sea !=NULL
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this !=NULL)
    {
        addNode(this,ll_len(this),pElement);
        returnAux=0;
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node *aux;

    if(this!=NULL && index >= 0 && index <= ll_len(this))
    {
        aux=getNode(this,index);
        if(aux!=NULL)
        {
            returnAux=aux->pElement;
        }
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node *aux;

    if(this!=NULL && index >= 0 && index<ll_len(this))
    {
        aux=getNode(this,index);
        aux->pElement=pElement;
        returnAux=0;
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node *nodoEliminar;
    Node *nodoPosterior;
    Node *nodoAnterior;

    if(this!=NULL && index >= 0 && index<ll_len(this))
    {
        nodoEliminar=getNode(this,index);
        nodoPosterior=nodoEliminar->pNextNode;

            if(index==0)
            {
                this->pFirstNode=nodoPosterior;
            }
            else if(this->size==1)
            {
                this->pFirstNode=NULL;
            }
            else
            {
                nodoAnterior=getNode(this,index-1);
                nodoAnterior->pNextNode=nodoEliminar->pNextNode;
            }

        free(nodoEliminar);
        this->size--;
        returnAux=0;


    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int i;

    if(this!=NULL)
    {
        for(i=0;i<ll_len(this);i++)
        {
            ll_remove(this,0);
        }
        returnAux=0;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        if(!ll_clear(this))
        {
            free(this);
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i;
    if(this!=NULL)
    {
        for(i=0;i<ll_len(this);i++)
        {
            if(pElement==ll_get(this,i))
            {
                returnAux=0;
            }
        }
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this!=NULL)
    {
        if(this->size==0) returnAux=1;
        else returnAux=0;
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;

    if(this!=NULL  && index>=0 && index<=ll_len(this))
    {
        if(!addNode(this,index,pElement))
        {
            returnAux=0;
        }
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    if(this!= NULL && index>=0 && index<ll_len(this))
    {
        returnAux=ll_get(this,index);
        ll_remove(this,index);
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    ///int i;
    ///void *aux=NULL;

    if(this!= NULL)
    {
        if(!ll_indexOf(this,pElement))
        {
          returnAux=1;
        }
        else
        {
            returnAux=0;
        }

       /* for(i=0;i<ll_len(this);i++)   ///LO PRENSE ASI TMB PERO NO ME FUNCIONA
        {

            aux=ll_get(this,i);
            if(aux!=NULL && aux==pElement)
            {
                returnAux=1;
                break;
            }
            else
            {
                returnAux=0;
            }
        }*/
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    Node *aux;
    int i;

    if(this!=NULL && this2!=NULL)
    {
        aux=this2->pFirstNode;
        returnAux = 1;
        for(i=0; i<ll_len(this2);i++)
        {
            if(!ll_contains(this,aux->pElement))
            {
                returnAux = 0;
                break;
            }
            aux=aux->pNextNode;
        }
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;

    if(this!=NULL && from>=0 && from<ll_len(this) &&   to<=ll_len(this))
    {
        cloneArray=ll_newLinkedList();
        for(from=0;from<to;from++)
        {
            if(cloneArray!=NULL)
            {
                ll_add(cloneArray,ll_get(this,from));
            }
        }
    }
    return cloneArray;
}

/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    int i;

    if(this!=NULL)
    {
        cloneArray=ll_newLinkedList();
        for(i=0;i<ll_len(this);i++)
        {
            if(cloneArray!=NULL)
            {
                ll_add(cloneArray,ll_get(this,i));
            }
        }
    }
    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux =-1;
    int j;
    int flag;
    void *auxElement1;
    void *auxElement2;
    void *aux;

    if(this!=NULL && pFunc!=NULL &&(order==0 || order==1))
    {
        do
        {
            flag=1;
            for(j=0;j<ll_len(this)-1;j++)
            {
                auxElement1=ll_get(this,j);
                auxElement2=ll_get(this,j+1);
                if((pFunc(auxElement1,auxElement2)<0 && !order) || (pFunc(auxElement1,auxElement2)>0 && order))
                {
                    aux=auxElement1;
                    auxElement1=auxElement2;
                    auxElement2=aux;
                    ll_set(this,j,auxElement1);
                    ll_set(this,j+1,auxElement2);
                    flag=0;
                    returnAux=0;
                }
            }
        }while(!flag);
    }
    return returnAux;
}

/** \brief  recorre la lista original, clone pero con criterio de agregado
 *
 * \param void* si es F no lo agrego si devuelvo V (0) lo agrego
 * \return int ll_filter(LinkedList this; int
 *
 */
int ll_filter(LinkedList* this, int (*pFunc)(void*))
{
     LinkedList* cloneArray = NULL;
    int returnAux=-1;
    void *element;
    int i;

    if(this!=NULL && pFunc!=NULL)
    {
        cloneArray=ll_newLinkedList();
        for(i=0;i<ll_len(this);i++)
        {
            element=ll_get(this,i);
            if(!pFunc(element))
            {
                ll_add(cloneArray,element);
                returnAux=0;
            }
        }
    }
    return returnAux;
}

/** \brief  Recorre el array y por cada elemento que recorro llamo
 *          reocorre con el elemento en la mano llama a la funcion que recibio como parametro
 * \param void*
 * \return int ll_map (LinkedList this, int
 *
 */
int ll_map (LinkedList* this, int (*pFunc)(void*))
{
    int returnAux=-1;
    void *element;
    int i;

    if(this != NULL && pFunc != NULL)
    {
        for(i=0;i<ll_len(this);i++)
        {
            element=ll_get(this,i);
            if(!pFunc(element))
            {
                returnAux=0;
            }
        }
    }
    return returnAux;
}

/** \brief  Elimina un elemento pasado por parametro
 *
 * \param
 * \param
 * \return
 *
 */
int ll_reduce (LinkedList* this, int (*pFunc)(void*))
{
    int returnAux=-1;
    void *element;
    int i;

    if(this != NULL && pFunc != NULL)
    {
        for(i=0;i<ll_len(this);i++)
        {
            element=ll_get(this,i);
            if(!pFunc(element))
            {
                if(!ll_remove(this,i))
                {
                    if(i==0) i--;
                }
                returnAux=0;
            }
        }
    }
    return returnAux;

}

