#include "all.h"

AvlRuas *addRua(AvlRuas *tree, Rua *rua)
{
	bool flag;
	
	return addRuaAux(tree, rua, &flag);
}

LLRuas *insereRuaLL(LLRuas *ll, Rua *rua)
{
	if(ll == NULL)
	{
		ll = (LLRuas *) malloc(sizeof(LLRuas));
		ll->rua = rua;
		ll->prox = NULL;
		
		return ll;
	}
	LLRuas *aux = (LLRuas *) malloc(sizeof(LLRuas));
	
	aux->rua = rua;
	aux->prox = ll;
	
	return aux;
}

AvlRuas * addRuaAux(AvlRuas *tree, Rua * rua, bool *flag)
{
	int cmp;
	
	if(tree == NULL)
	{
		tree = (AvlRuas *) malloc(sizeof(AvlRuas));
		
		tree->ruas = insereRuaLL(tree->ruas, rua);
		tree->nomeRua = daNomeRua(rua->nome);
		tree->left = tree->right = NULL;
		tree->bf = EB;
		*flag = 1;
	}
	else
	{
		cmp = strcasecmp(tree->nomeRua, daNomeRua(rua->nome));
		if(cmp == 0)
		{
			tree->ruas = insereRuaLL(tree->ruas, rua);
			*flag = 0;
		}
		else if(cmp > 0)
		{
			tree->left = addRuaAux(tree->left, rua, flag);
			if(*flag)
			{
				switch(tree->bf)
				{
					case LB:
						if(tree->left->bf == LB)
						{
							tree = rotateRight(tree);
							tree->bf = EB;
							tree->right->bf = EB;
						}
						else
						{
							tree->left = rotateLeft(tree->left);
							tree = rotateRight(tree);
							balanceFlags(tree);
						}
						*flag = 0;
						break;
					case EB:
						tree->bf = LB;
						break;
					case RB:
						tree->bf = EB;
						*flag = 0;
						break;
				}
			}
		}
		else
		{
			tree->right = addRuaAux(tree->right, rua, flag);
			if(*flag)
			{
				switch(tree->bf)
				{
					case LB:
						tree->bf = EB;
						*flag = 0;
						break;
					case EB:
						tree->bf = RB;
						break;
					case RB:
						if(tree->right->bf == RB)
						{
							tree = rotateLeft(tree);
							tree->bf = EB;
							tree->left->bf = EB;
						}
						else
						{
							tree->right = rotateRight(tree->right);
							tree = rotateLeft(tree);
							balanceFlags(tree);
						}
						*flag = 0;
						break;
				}
			}
		}
	}
	return tree;
}

AvlRuas *rotateLeft(AvlRuas *tree)
{
	AvlRuas *aux;
	
	aux = tree->right;
	tree->right = aux->left;
	aux->left = tree;
	
	return aux;
}

AvlRuas *rotateRight(AvlRuas *tree)
{
	AvlRuas *aux;
	
	aux = tree->left;
	tree->left = aux->right;
	aux->right = tree;
	
	return aux;
}

void balanceFlags(AvlRuas *tree)
{
	switch(tree->bf)
	{
		case LB:
			tree->left->bf = EB;
			tree->right->bf = RB;
			break;
		case EB:
			tree->left->bf = EB;
			tree->right->bf = EB;
			break;
		case RB:
			tree->left->bf = LB;
			tree->right->bf = EB;
			break;
	}
	tree->bf = EB;
}

void inorderAVL(AvlRuas *tree)
{
   if(tree != NULL)
   {
      inorderAVL(tree->left);
      printf("%s | ",tree->nomeRua);
      inorderAVL(tree->right);
   }
}

Grafo *insereRua(Grafo *grafo, Rua *rua)
{
	if(grafo->vertices[rua->limite1]==NULL)
	{
		Arestas* aresta = (Arestas *) malloc(sizeof(Arestas));
		aresta->rua = rua;
		aresta->prox=NULL;
		grafo->vertices[rua->limite1]=aresta;
	}
	else
	{
		Arestas* aresta = (Arestas *) malloc(sizeof(Arestas));
		aresta->rua = rua;
		aresta->prox=grafo->vertices[rua->limite1];
		grafo->vertices[rua->limite1]=aresta;
	}

	if(grafo->vertices[rua->limite2]==NULL)
	{
		Arestas* aresta = (Arestas *) malloc(sizeof(Arestas));
		aresta->rua = rua;
		aresta->prox=NULL;
		grafo->vertices[rua->limite2]=aresta;
	}
	else
	{
		Arestas* aresta = (Arestas *) malloc(sizeof(Arestas));
		aresta->rua = rua;
		aresta->prox=grafo->vertices[rua->limite2];
		grafo->vertices[rua->limite2]=aresta;
	}
	return grafo;
}

float lenRua(LLRuas *llTrocos)
{
	float i = 0.0;
	LLRuas *aux = llTrocos;
	
	for( ; aux != NULL ; aux = aux->prox)
		i += aux->rua->comprimento;
	
	return i;
}

LLRuas *procuraRuaDaLL(char *nomeRua, AvlRuas *tree)
{
	int cmp;
	LLRuas *ruas=NULL;
	
	if(tree != NULL)
	{
		cmp = strcasecmp(tree->nomeRua, nomeRua);
		if(cmp == 0)
		{
			ruas = tree->ruas;
		}
		else if(cmp > 0)
		{
			ruas = procuraRuaDaLL(nomeRua, tree->left);
		}
		else
		{
			ruas = procuraRuaDaLL(nomeRua, tree->right);
		}
	}
	return ruas;
}

Rua *procuraRua(char *nomeRua, AvlRuas *tree)
{
	int cmp;
	Rua *rua=NULL;
	
	if(tree != NULL)
	{
		cmp = strcasecmp(tree->nomeRua, daNomeRua(nomeRua));
		
		if(cmp == 0)
		{
			rua = procuraRuaLL(nomeRua,tree->ruas);
		}
		else if(cmp > 0)
		{
			rua = procuraRua(nomeRua, tree->left);
		}
		else
		{
			rua = procuraRua(nomeRua, tree->right);
		}
	}
	return rua;
}

Rua *procuraRuaLL(char *nomeRua, LLRuas *ruas)
{
	LLRuas *aux = ruas;
	
	for( ; aux!= NULL && strcasecmp(aux->rua->nome, nomeRua) != 0 ; aux = aux->prox);
	
	return aux->rua;
}

Rua *novaRua(char *nome, int limite1, int limite2, float comp, float tempo, AvlRuas ** tree)
{
	Rua *rua = (Rua *) malloc(sizeof(Rua));
	
	rua->nome = nome;
	rua->limite1 = limite1;
	rua->limite2 = limite2;
	rua->comprimento = comp;
	rua->tempoMedio = tempo;
	rua->listaPontos = NULL;
	
	(*tree) = addRua(*tree,rua);
	
	return rua;
}

char *daNomeRua(char *nomeTroco)
{
	char *copia1 = (char *) malloc(strlen(nomeTroco)*sizeof(char));
	char *copia2 = (char *) malloc(strlen(nomeTroco)*sizeof(char));
	char *ret = (char *) malloc(strlen(nomeTroco)*sizeof(char));
	
	copia1 = strcpy(copia1,nomeTroco);
	copia2 = strcpy(copia2,nomeTroco);
	ret = strcpy(ret,nomeTroco);
	
	copia1 = strtok(copia1, "_");
	
	copia1 = (strtok(NULL,""));
	
	if(copia1 == NULL)
		return copia2;
	else
		return strtok(copia2,"_");
}
