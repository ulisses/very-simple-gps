#include "all.h"

Grafo *criaGrafo(int size)
{
	Grafo *g = (Grafo *) malloc(sizeof(Grafo));
	int i;

	g->size=size;

	*g->vertices = (Arestas *) malloc (size*sizeof(Arestas));

	for(i=0 ; i<=size ; i++)
	{
		g->vertices[i]=NULL;
	}

	return g;
}

Grafo *carregaRuas(AvlRuas **lr, AvlPontosInteresse **lpi)
{
	FILE *fp = fopen("teste.txt","r");
	
	FILE *fpG = fopen("b","w");
	
	int nrRuas,nrArestas, nrVertices, i,nodo1,nodo2,valorArquitectonico, valorPaisagistico, valorHistorico, valorComercial, limite1,j;
	float tempoMedio, distancia, distanciaPonto, tempoMedioPonto;
	char *linha=(char *)malloc(1000*sizeof(char));
	char *nomeRua=(char *)malloc(1000*sizeof(char));
	char *nomePontoInteresse=(char *)malloc(1000*sizeof(char));
	char *tipo=(char *)malloc(1000*sizeof(char));
	char *descricao=(char *)malloc(1000*sizeof(char));
	
	fscanf(fp, "Ruas:%d%*c", &nrRuas);
	
	fscanf(fp, "Vertices:%d%*c", &nrVertices);
	
	fscanf(fp, "Arestas:%d%*c", &nrArestas);
	
	Grafo* g = criaGrafo(nrVertices);
	
	for(j=1,i=0 ; i < nrArestas ; i++, j++)
	{
		fscanf(fp, "%[^\n]%*c", linha);
		sscanf(strtok(linha,"-"),"%d",&nodo1);
		sscanf(strtok(NULL," "),"%d",&nodo2);
		nomeRua = strtok(NULL,":");
		sscanf(strtok(NULL,":"),"%f",&distancia);
		sscanf(strtok(NULL,":"),"%f",&tempoMedio);
		
		fprintf(fpG, "node%d [label=\"%d\"];\n",nodo1,i);
		fprintf(fpG, "node%d [label=\"%d\"];\n",nodo2,j);
		fprintf(fpG, "node%d -- node%d[label=\"%s(%f,%f)\"];\n",nodo1,nodo2,nomeRua,distancia,tempoMedio);
// 		node1 -- node2[label="nomeRua"];
// 		node1 [label="1"];
// 		node2 [label="2"];
		
		g = insereRua(g, novaRua(strdup(nomeRua),nodo1,nodo2,distancia,tempoMedio,lr));
	}
	
	fscanf(fp, "%[^\n]%*c", linha);
	
	for( ; fscanf(fp, "%[^\n]%*c", linha) != EOF ; )
	{
		nomePontoInteresse = strtok(linha,":");
		
		tipo = strtok(NULL,":");
		sscanf(strtok(NULL,":"),"%d",&valorArquitectonico);
		sscanf(strtok(NULL,":"),"%d",&valorPaisagistico);
		sscanf(strtok(NULL,":"),"%d",&valorHistorico);
		sscanf(strtok(NULL,":"),"%d",&valorComercial);
		descricao = strtok(NULL,":");
		sscanf(strtok(NULL,":"),"%d",&limite1);
		sscanf(strtok(NULL,":"),"%f",&distanciaPonto);
		sscanf(strtok(NULL,":"),"%f",&tempoMedioPonto);
		nomeRua = strtok(NULL,":");
		
		Rua *rua = procuraRua(strdup(nomeRua), *lr);
		
		novoPonto(rua->listaPontos,strdup(nomePontoInteresse), strdup(descricao), limite1,
			distanciaPonto, valorHistorico, valorPaisagistico, valorComercial,
			valorArquitectonico, ePontoTuristico(tipo), tempoMedioPonto, rua, lpi,strdup(tipo));
	}
	return g;
}

void PesquisaLargura(Grafo *g, int vertice, int * d, int * parentes, AvlPontosInteresse ** lpi)
{
	FIFO * fifo = criaFIFO(), *adjacentes;
	int i, adjacente, aux;
	Cor cor[g->size+1];

    for(i=0; i<=g->size;i++)
    {
        cor[i] = WHITE;
        parentes[i] = -1;
    }

    d[vertice] = 0;
    cor[vertice] = GRAY;

    fifo = acrescentaFIFO(g->vertices[vertice], fifo);

    while(!isEmpty(fifo))
    {
        fifo = removeFIFO(fifo, g,&aux);
        adjacentes = adjVer(aux, g);

        while (!isEmpty(adjacentes))
        {
		adjacentes = removeFIFO(adjacentes,g,&adjacente);
                if (cor[adjacente] == WHITE)
                {
                    cor[adjacente] = GRAY;
                    d[adjacente] = d[aux] + daPeso(adjacente,g->vertices[aux]);
                    parentes[adjacente] = aux;
                    fifo = acrescentaFIFO(g->vertices[adjacente],fifo);
                }
        }
        A
        cor[aux] = BLACK;
    }
}

void dijkstraMenor(Grafo * g, int vertice1, int vertice2, float * peso, int * parentes)
{
    int x, i, p, fim;
    FIFO *adj = criaFIFO();
    Cor cor[g->size+1];


    for(i=1;i<=g->size;i++)
    {
        cor[i] = WHITE;
        parentes[i] = -1;
        peso[i] = INF;
    }

    x = vertice1;
    peso[vertice1] = 0;

    while (x != -1 && x!=vertice2)
    {

          adj = adjVer(x, g);

          while (!isEmpty(adj))
          {
          	  adj = removeFIFO(adj,g,&fim);
              if ((cor[darVertice(g->vertices[fim],g)] == WHITE) && (peso[darVertice(g->vertices[fim],g)] > (peso[x] + daPeso(x,g->vertices[fim]))))
              {
                      peso[darVertice(g->vertices[fim],g)] = peso[x] + daPeso(x,g->vertices[fim]);
				      parentes[darVertice(g->vertices[fim],g)] = x;
              }
          }
          cor[x] = BLACK;

          p = INF;
          x = -1;

          for(i=1; i<=g->size; i++)
          {   //O(V) no maximo uma vez por vertice
	           	if(p>peso[i] && !cor[i])
	           	{
		          	x = i;
			        p = peso[i];
	           	}
		  }
    }
}

ListaPontosInteresse *dijkstraMenorAteN(Grafo * g, int vertice, float * peso, int * parentes, int n)
{
    int x, i, p, fim, len = 0;
    FIFO *adj = criaFIFO();
    Cor cor[g->size+1];
    ListaPontosInteresse * lpi = NULL;

    for(i=1;i<=g->size;i++)
    {
        cor[i] = WHITE;
        parentes[i] = -1;
        peso[i] = INF;
    }

    x = vertice;
    peso[vertice] = 0;

	while (x != -1 && len <n)
    {
          adj = adjVer(x, g);

          while (!isEmpty(adj))
          {
          	  adj = removeFIFO(adj,g,&fim);
              if (cor[darVertice(g->vertices[fim],g)] == WHITE)
              {
              	  if(peso[darVertice(g->vertices[fim],g)] > (peso[x] + daPeso(x,g->vertices[fim])))
              	  {
                      peso[darVertice(g->vertices[fim],g)] = peso[x] + daPeso(x,g->vertices[fim]);
				      parentes[darVertice(g->vertices[fim],g)] = x;
              	  }

				  lpi = daPontosLpimM(Restaurante,daRua(x, g->vertices[fim]), x,&len,peso, lpi);
              }
          }

          cor[x] = BLACK;

          p = INF;
          x = -1;

          for(i=1; i<=g->size; i++)
          {   //O(V) no maximo uma vez por vertice
	           	if(p>peso[i] && !cor[i])
	           	{
		          	x = i;
			        p = peso[i];
	           	}
		  }
    }

    return lpi;
}

ListaPontosInteresse *dijkstraMenorAteXMetros(Grafo * g, int vertice, float * peso, int * parentes, float xis)
{
    int x, i, p, fim;
    float len=0.0;
    FIFO *adj = criaFIFO();
    Cor cor[g->size+1];
    ListaPontosInteresse * lpi = NULL;

    for(i=1;i<=g->size;i++)
    {
        cor[i] = WHITE;
        parentes[i] = -1;
        peso[i] = INF;
    }
	
    x = vertice;
    peso[vertice] = 0.0;
	while (x != -1 && len <= xis)
    {
          if(peso[x] >= xis)
		  	cor[x] = BLACK;
		  	
          adj = adjVer(x, g);
          
          while (!isEmpty(adj))
          {
          	  adj = removeFIFO(adj,g,&fim);
              if (cor[darVertice(g->vertices[fim],g)] == WHITE)
              {
              	  if(peso[darVertice(g->vertices[fim],g)] > (peso[x] + daPeso(x,g->vertices[fim])))
              	  {
                      peso[darVertice(g->vertices[fim],g)] = peso[x] + daPeso(x,g->vertices[fim]);
				      parentes[darVertice(g->vertices[fim],g)] = x;
              	  }
				  lpi = daPontosLpiMm(xis,daRua(x, g->vertices[fim]), x,&len,peso, lpi);
              }


          }

          cor[x] = BLACK;

          p = INF;
          x = -1;

          for(i=1; i<=g->size; i++)
          {   //O(V) no maximo uma vez por vertice
	           	if(p>peso[i] && !cor[i])
	           	{
		          	x = i;
			        p = peso[i];
	           	}
		  }


    }
    return lpi;
}

Ponto * dijkstraMaisRapido(Grafo * g, int vertice, float * peso, int * parentes, char * ponto, int *vertice2)
{
    int x, i, p, fim;
    FIFO *adj = criaFIFO();
    Cor cor[g->size+1];
    Ponto * pontos = NULL;


    for(i=1;i<=g->size;i++)
    {
        cor[i] = WHITE;
        parentes[i] = -1;
        peso[i] = INF;
    }

    x = vertice;
    peso[vertice] = 0.0;

    while (x != -1 && pontos==NULL)
    {

          adj = adjVer(x, g);

          while (!isEmpty(adj))
          {
          	  adj = removeFIFO(adj,g,&fim);
              if (cor[darVertice(g->vertices[fim],g)] == WHITE) 
              {
              	  if(peso[darVertice(g->vertices[fim],g)] > (peso[x] + daTempoRua(x,g->vertices[fim])))
              	  {
                      peso[darVertice(g->vertices[fim],g)] = peso[x] + daTempoRua(x,g->vertices[fim]);
				      parentes[darVertice(g->vertices[fim],g)] = x;
              	  }
              	  pontos = daPontoInteresse(ponto,daRua(x, g->vertices[fim]));
			  	  if(pontos!=NULL)
			  		   *vertice2=x;
              }
          }
          
          cor[x] = BLACK;

          p = INF;
          x = -1;

          for(i=1; i<=g->size; i++)
          {   //O(V) no maximo uma vez por vertice
	           	if(p>peso[i] && !cor[i])
	           	{
		          	x = i;
			        p = peso[i];
	           	}
		  }
    }
    
    return pontos;
}


AvlRuas * caminhoMaisRapido(int * parentes,int vertice, Rua * rua,Grafo *g, AvlRuas * lr)
{
	int i=vertice;
	
	while(parentes[i]!=-1)
	{
		lr = addRua(lr, daRua(parentes[i],g->vertices[i]));
		i=parentes[i];
	}
	
	lr = addRua(lr,rua);
	
	return lr;

}


AvlRuas * caminhoMaisCurto(int * parentes,int vertice, Grafo *g, AvlRuas * lr)
{
	int i=vertice;
	
	while(parentes[i]!=-1)
	{
		lr = addRua(lr, daRua(parentes[i],g->vertices[i]));
		i=parentes[i];
	}
	
	return lr;
}

void gravaPontos(AvlPontosInteresse *tree, FILE *fp)
{
	if(tree != NULL)
	{
		fprintf(fp, "%s:%s:%d:%d:%d:%d:%s:%d:%f:%f:%s\n", tree->ponto->nome, setTipo(tree->ponto->tipo)
			, tree->ponto->valorArquitectonico, tree->ponto->valorPaisagistico
			, tree->ponto->valorHistorico, tree->ponto->valorComercial
			, tree->ponto->descricao, tree->ponto->limite1, tree->ponto->distancia
			, tree->ponto->tempoMedio, tree->ponto->rua->nome);
		gravaPontos(tree->left, fp);
		gravaPontos(tree->right, fp);
	}
}

void gravaRuas(AvlRuas *tree, AvlPontosInteresse *treePts)
{
	FILE *fp = fopen("teste_.txt","w");
	
	fprintf(fp, "Ruas:%d\n", (int)12);
	fprintf(fp, "Vertices:%d\n", (int)23);
	fprintf(fp, "Arestas:%d\n", (int)245);
	
	gravaRuasAux(tree, fp);
	
	fputs("Pontos:\n", fp);
	
	gravaPontos(treePts, fp);
}

void gravaRuasAux(AvlRuas *lr, FILE *fp)
{
	if(lr != NULL)
	{
		for( ; lr->ruas != NULL ; lr->ruas = lr->ruas->prox)
		{
			fprintf(fp, "%d-%d %s:%f:%f\n", lr->ruas->rua->limite1, lr->ruas->rua->limite2
			                              , lr->ruas->rua->nome, lr->ruas->rua->comprimento
			                              , lr->ruas->rua->tempoMedio);
		}
		gravaRuasAux(lr->left, fp);
		gravaRuasAux(lr->right, fp);
	}
}
