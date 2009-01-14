#include "all.h"

int numVerAdj(Arestas * aresta, int vertice)
{
    int adjacente;

    if (aresta->rua->limite1 == vertice)
    {
        adjacente = aresta->rua->limite2;
    }
    else
    {
        adjacente = aresta->rua->limite1;
    }

    return adjacente;
}

int darVertice (Arestas * aresta, Grafo * g)
{
        int i;

        if (g->vertices[aresta->rua->limite2] == aresta)
                i = aresta->rua->limite2;
        else
                i = aresta->rua->limite1;

        return i;
}

float daPeso(int aux,Arestas * arestas)
{
    float a=0;
    Arestas * aresta = arestas;
    for (;aresta != NULL; aresta = aresta->prox)
    {
        if (aresta->rua->limite1 == aux || aresta->rua->limite2 == aux)
        {
            a = aresta->rua->comprimento;
            break;
        }
    }
    return a;
}

Rua * daRua(int vertice, Arestas * arestas)
{
	Arestas * aresta = arestas;
	Rua * rua=NULL;

	for(;aresta!=NULL;aresta=aresta->prox)
	{
		if(aresta->rua->limite1 == vertice || aresta->rua->limite2 == vertice)
		{
			rua = aresta->rua;
			break;
		}
	}
	return rua;

}

float daTempoRua(int x,Arestas * arestas)
{
	Arestas * aresta = arestas;
	
	for(;aresta!=NULL;aresta=aresta->prox)
		if(aresta->rua->limite1 == x || aresta->rua->limite2 == x)
			return aresta->rua->tempoMedio;
	
	return 0.0;
}


float daTempo(AvlRuas *tree)
{
	float acc = 0;
	
	return(daTempoAux(tree,&acc));
}

float daTempoAux(AvlRuas *tree, float *acc)
{
	if(tree!=NULL)
	{
		*acc += daTempoRuaAux(tree->ruas);
		daTempoAux(tree->left,acc);
		daTempoAux(tree->right,acc);
	}
	return *acc;
}

float daTempoRuaAux(LLRuas *ll)
{
	LLRuas *aux = ll;
	float i=0.0;
	
	for( ; aux != NULL ; aux = aux->prox)
		i += aux->rua->tempoMedio;
	
	return i;
}

float daPesoPontoDist(int vertice,Ponto* ponto)
{
	if(vertice == ponto->limite1)
		return ponto->distancia;
	else
		return (ponto->rua->comprimento - ponto->distancia);
}

Ponto * daPontoInteresse(char *ponto,Rua * rua)
{
	Ponto * pontos = rua->listaPontos;
	
	for(;pontos!=NULL;pontos=pontos->prox)
		if(strcasecmp(pontos->nome, ponto) == 0)
			return pontos;
			
	return pontos;
}

float daPesoTotPontoInteresse(Ponto * ponto, int x, float * peso)
{
	float xis;
	
	xis = daPesoPontoTemp(x,ponto);
	xis+=peso[x];
	
	return xis;
}

float daPesoPontoTemp(int vertice,Ponto* ponto)
{
	if(vertice == ponto->limite1)
		return ponto->tempoMedio;
	else
		return (ponto->rua->tempoMedio - ponto->tempoMedio);
}
