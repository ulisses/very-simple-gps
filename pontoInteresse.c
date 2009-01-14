#include "all.h"

bool ePontoTuristico(char *tipo)
{
	return (strcasecmp(tipo,"igreja")==0 || strcasecmp(tipo,"teatro")==0
	     || strcasecmp(tipo,"pontoturismo")==0 || strcasecmp(tipo,"museu")==0
	     || strcasecmp(tipo,"monumento")==0
	     );
}

Ponto *novoPonto(Ponto * ponto,char *nome, char *descricao, int limite1, float distancia, int valorHistorico, int valorPaisagistico, int valorComercial,  int valorArquitectonico, bool pontoTuristico, float tempoMedio,Rua* rua, AvlPontosInteresse ** lpi, char * tipo)
{
	if(ponto == NULL)
	{
		Ponto *ponto = (Ponto *) malloc(sizeof(Ponto));
		rua->listaPontos = ponto;
		ponto->nome=nome;
		ponto->tipo=daTipo(tipo);
		ponto->descricao=descricao;
		ponto->limite1=limite1;
		ponto->distancia=distancia;
		ponto->tempoMedio=tempoMedio;
		ponto->valorHistorico=valorHistorico;
		ponto->valorPaisagistico=valorPaisagistico;
		ponto->valorComercial=valorComercial;
		ponto->valorArquitectonico=valorArquitectonico;
		ponto->pontoTuristico=pontoTuristico;
		ponto->rua=rua;
		ponto->prox = NULL;
		
		rua->valorComercial+=valorComercial;
		rua->valorHistorico+=valorHistorico;
		rua->valorPaisagistico+=valorPaisagistico;
		rua->valorArquitectonico+=valorArquitectonico;
		
		*lpi = addPontosInteresse(ponto,*lpi);
		
		return ponto;
	}
	Ponto *aux = (Ponto *) malloc(sizeof(Ponto));
	aux->nome=nome;
	aux->tipo=daTipo(tipo);
	aux->descricao=descricao;
	aux->limite1=limite1;
	aux->distancia=distancia;
	aux->tempoMedio=tempoMedio;
	aux->valorHistorico=valorHistorico;
	aux->valorPaisagistico=valorPaisagistico;
	aux->valorComercial=valorComercial;
	aux->valorArquitectonico=valorArquitectonico;
	aux->pontoTuristico=pontoTuristico;
	aux->rua=rua;
	aux->prox = ponto;
	
	rua->listaPontos=aux;
	rua->valorComercial+=valorComercial;
	rua->valorHistorico+=valorHistorico;
	rua->valorPaisagistico+=valorPaisagistico;
	rua->valorArquitectonico+=valorArquitectonico;
	
	*lpi = addPontosInteresse(aux,*lpi);
	
	return aux;
}

Ponto *procuraPonto(char *nome, AvlPontosInteresse *tree)
{
	int cmp;
	Ponto *ponto=NULL;
	
	if(tree != NULL)
	{
		cmp = strcasecmp(tree->nome, nome);
		if(cmp == 0)
		{
			ponto = tree->ponto;
		}
		else if(cmp > 0)
		{
			ponto = procuraPonto(nome, tree->left);
		}
		else
		{
			ponto = procuraPonto(nome, tree->right);
		}
	}
	return ponto;
}

AvlPontosInteresse *addPontosInteresse(Ponto *ponto, AvlPontosInteresse *tree)
{
	bool flag;
	
	return addPontosInteresseAux(tree, ponto, &flag);
}

AvlPontosInteresse *addPontosInteresseAux(AvlPontosInteresse *tree, Ponto *ponto, bool *flag)
{
	int cmp;
	
	if(tree == NULL)
	{
		tree = (AvlPontosInteresse *) malloc(sizeof(AvlPontosInteresse));
		tree->ponto = ponto;
		tree->nome = ponto->nome;
		tree->left = tree->right = NULL;
		tree->bf = EB;
		*flag = 1;
	}
	else
	{
		cmp = strcasecmp(tree->nome, ponto->nome);
		
		if(cmp == 0)
		{
			*flag = 0;
		}
		else if(cmp > 0)
		{
			tree->left = addPontosInteresseAux(tree->left, ponto, flag);
			if(*flag)
			{
				switch(tree->bf)
				{
					case LB:
						if(tree->left->bf == LB)
						{
							tree = rotateRightpi(tree);
							tree->bf = EB;
							tree->right->bf = EB;
						}
						else
						{
							tree->left = rotateLeftpi(tree->left);
							tree = rotateRightpi(tree);
							balanceFlagspi(tree);
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
			tree->right = addPontosInteresseAux(tree->right, ponto, flag);
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
							tree = rotateLeftpi(tree);
							tree->bf = EB;
							tree->left->bf = EB;
						}
						else
						{
							tree->right = rotateRightpi(tree->right);
							tree = rotateLeftpi(tree);
							balanceFlagspi(tree);
						}
						*flag = 0;
						break;
				}
			}
		}
	}
	return tree;
}

AvlPontosInteresse *rotateLeftpi(AvlPontosInteresse *tree)
{
	AvlPontosInteresse *aux;
	
	aux = tree->right;
	tree->right = aux->left;
	aux->left = tree;
	
	return aux;
}

AvlPontosInteresse *rotateRightpi(AvlPontosInteresse *tree)
{
	AvlPontosInteresse *aux;
	
	aux = tree->left;
	tree->left = aux->right;
	aux->right = tree;
	
	return aux;
}

void balanceFlagspi(AvlPontosInteresse *tree)
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

TipoPontoInteresse daTipo(char * tipo)
{
	TipoPontoInteresse tip=0;
	if(strcasecmp(tipo,"Restaurante") == 0) tip = Restaurante;
	if(strcasecmp(tipo,"Igreja") == 0) tip = Igreja;
	if(strcasecmp(tipo,"Cinema") == 0) tip = Cinema;
	if(strcasecmp(tipo,"Teatro") == 0) tip = Teatro;
	if(strcasecmp(tipo,"Shopping") == 0) tip = Shopping;
	if(strcasecmp(tipo,"Hotel") == 0) tip = Hotel;
	if(strcasecmp(tipo,"PontoTurismo") == 0) tip = PontoTurismo;
	if(strcasecmp(tipo,"Museu") == 0) tip = Museu;
	if(strcasecmp(tipo,"Jardim") == 0) tip = Jardim;
	if(strcasecmp(tipo,"Monumento") == 0) tip = Monumento;
	if(strcasecmp(tipo,"Farmacia") == 0) tip = Farmacia;
	if(strcasecmp(tipo,"Hospital") == 0) tip = Hospital;
	if(strcasecmp(tipo,"Correios") == 0) tip = Correios;
	if(strcasecmp(tipo,"Cafe") == 0) tip = Cafe;
	if(strcasecmp(tipo,"Hipermercados") == 0) tip = Hipermercados;
	
	return tip;
}

char *setTipo(TipoPontoInteresse tipo)
{
	char *ret=NULL;
	
	if(tipo == Restaurante) ret = strdup("Restaurante");
	if(tipo == Hipermercados) ret = strdup("Hipermercados");
	if(tipo == Cinema) ret = strdup("Cinema");
	if(tipo == Teatro) ret = strdup("Teatro");
	if(tipo == Shopping) ret = strdup("Shopping");
	if(tipo == Hotel) ret = strdup("Hotel");
	if(tipo == PontoTurismo) ret = strdup("PontoTurismo");
	if(tipo == Museu) ret = strdup("Museu");
	if(tipo == Jardim) ret = strdup("Jardim");
	if(tipo == Monumento) ret = strdup("Monumento");
	if(tipo == Farmacia) ret = strdup("Farmacia");
	if(tipo == Hospital) ret = strdup("Hospital");
	if(tipo == Correios) ret = strdup("Correios");
	if(tipo == Cafe) ret = strdup("Cafe");
	
	return ret;
}

AvlPontosInteresse *daPontos(TipoPontoInteresse tipo, AvlPontosInteresse *tree)
{
	AvlPontosInteresse *list=NULL;
	
	list = daPontosAux(tipo,tree,&list);
	
	inorderAVLpi(list);
	
	return list;
}

AvlPontosInteresse *daPontosAux(TipoPontoInteresse tipo, AvlPontosInteresse *tree, AvlPontosInteresse **treeAcc)
{
	if(tree != NULL)
	{
		if(tipo == tree->ponto->tipo)
			*treeAcc = addPontosInteresse(tree->ponto, *treeAcc);
		*treeAcc = daPontosAux(tipo, tree->left, treeAcc);
		*treeAcc = daPontosAux(tipo, tree->right, treeAcc);
	}
	return *treeAcc;
}

void inorderAVLpi(AvlPontosInteresse *tree)
{
   if(tree != NULL)
   {
      inorderAVLpi(tree->left);
      printf("%s | ",tree->nome);
      inorderAVLpi(tree->right);
   }
}

ListaPontosInteresse * addListaPontosInteressemM (Ponto * ponto,int vertice,float *pes, ListaPontosInteresse * lpi)
{
    if (lpi == NULL)
    {
          lpi = (ListaPontosInteresse *) malloc(sizeof(ListaPontosInteresse));
          lpi->peso = pes[vertice] + daPesoPontoDist(vertice,ponto);
          lpi->ponto = ponto;
          lpi->prox = NULL;

          return lpi;
    }

    float peso = pes[vertice] + daPesoPontoDist(vertice,ponto);
	ListaPontosInteresse * aux = lpi, *aux1 = lpi;			
    ListaPontosInteresse * auxlpi = (ListaPontosInteresse *) malloc(sizeof(ListaPontosInteresse));

	while (peso > aux->peso)
	{
		aux1 = aux;
		aux=aux->prox;
		if(aux == NULL)
			break;

	}
	
	if(aux == lpi)
	{
		auxlpi->peso = peso;
	    auxlpi->ponto=ponto;
		auxlpi->prox=lpi;
		
		return auxlpi;	
	}


	auxlpi->peso = peso;
    auxlpi->ponto=ponto;
	auxlpi->prox=aux;
	aux1->prox = auxlpi;
    
	return lpi;	
	
}

ListaPontosInteresse * addListaPontosInteresseMm (float xis, Ponto * ponto,int vertice,float *pes, ListaPontosInteresse * lpi)
{
    float peso = pes[vertice] + daPesoPontoDist(vertice,ponto); 
	if(peso > xis)
    	return lpi;
    
    if (lpi == NULL)
    {
          lpi = (ListaPontosInteresse *) malloc(sizeof(ListaPontosInteresse));
          lpi->peso = pes[vertice] + daPesoPontoDist(vertice,ponto);
          lpi->ponto = ponto;
          lpi->prox = NULL;

          return lpi;
    }

	ListaPontosInteresse * aux = lpi, *aux1 = lpi;			
	ListaPontosInteresse * auxlpi = (ListaPontosInteresse *) malloc(sizeof(ListaPontosInteresse));

	while (peso < aux->peso)
	{
		aux1 = aux;
		aux=aux->prox;
		if(aux == NULL)
			break;
	}
	
	if(aux == lpi)
	{
		auxlpi->peso = peso;
		auxlpi->ponto=ponto;
		auxlpi->prox=lpi;
		
		return auxlpi;	
	}
	
	auxlpi->peso = peso;
	auxlpi->ponto=ponto;
	auxlpi->prox=aux;
	aux1->prox = auxlpi;
	
	return lpi;	
	
}

ListaPontosInteresse *daPontosLpimM(TipoPontoInteresse tipo,Rua * rua,int vertice,int * len,float *peso, ListaPontosInteresse * lpii)
{
	Ponto * lpi = rua->listaPontos;
	
	for(;lpi!=NULL;lpi=lpi->prox)
	{
		if (lpi->tipo == tipo)
		{
			lpii = addListaPontosInteressemM(lpi,vertice,peso,lpii);
			(*len)+=1;
		}
	}	
	return lpii;
}

ListaPontosInteresse *daPontosLpiMm(float xis, Rua * rua,int vertice,float * len,float *peso, ListaPontosInteresse * lpii)
{
	Ponto * lpi = rua->listaPontos;
	
	for(;lpi!=NULL;lpi=lpi->prox)
	{
		if (lpi->pontoTuristico)
		{
			lpii = addListaPontosInteresseMm(xis,lpi,vertice,peso,lpii);
			if(lpii == NULL);
			else
				(*len)=lpii->peso;
		}
	}
	return lpii;
}

ListaPontosInteresse * daPontosMaisProximos(int n,ListaPontosInteresse *lpi)
{
	int i;
	ListaPontosInteresse * lpii=lpi;	

	for(i=1;i<n && lpii->prox != NULL;i++)
	{
		lpii=lpii->prox;
	}

	lpii->prox = NULL; //temos de ver esta merda bem pa depois faxer um free;

	return lpi;
}
