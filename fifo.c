#include "all.h"

FIFO *acrescentaFIFO(Arestas *aresta, FIFO * fifo)
{
    FIFO *aux1 = fifo;

    if(aux1->aresta == NULL)
    {
        aux1->aresta = aresta;
        aux1->prox = NULL;
    }
    else
    {
        FIFO * aux = (FIFO *) malloc (sizeof(FIFO));

        aux->aresta = aresta;
        aux->prox = fifo;
        aux1 = aux;
    }

    return aux1;
}

FIFO* criaFIFO()
{
        FIFO * fifo = (FIFO *) malloc(sizeof(FIFO));
        fifo->aresta = NULL;
        fifo->prox = NULL;

        return fifo;
}

FIFO * adjVer(int vertice, Grafo * grafo)
{
    FIFO * adjacentes = criaFIFO();
    Arestas * aresta = grafo->vertices[vertice];

    for(;aresta != NULL; aresta = aresta->prox)
    {
        if(aresta->rua->limite1 == vertice)
            adjacentes=acrescentaFIFO(grafo->vertices[aresta->rua->limite2], adjacentes);
        else
            adjacentes=acrescentaFIFO(grafo->vertices[aresta->rua->limite1], adjacentes);
    }

    return adjacentes;
}

bool isEmpty(FIFO *fifo)
{
    if(fifo == NULL || (fifo->aresta == NULL && fifo->prox==NULL))
        return true;
    else
        return false;
}

FIFO * removeFIFO(FIFO *fifo, Grafo *g, int *vertice)
{
        FIFO* aux = fifo;

        if(aux->prox == NULL)
        {
            *vertice = darVertice(aux->aresta, g);
            free(aux);
            aux = criaFIFO();

            return aux;
        }

        FIFO* aux1 = fifo;
        for(;aux->prox!=NULL;aux=aux->prox)
        {
               aux1 = aux;
        }

        *vertice = darVertice(aux->aresta, g);
        aux1->prox=NULL;
        aux = NULL;

        return fifo;
}
