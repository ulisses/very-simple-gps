#include "all.h"

int main()
{
	Grafo *g;
	AvlRuas *lr = NULL ;
	AvlPontosInteresse *lpi=NULL;
	
	g = carregaRuas(&lr, &lpi);
	A
	gravaRuas(lr,lpi);
	
// ZONA DE TESTES

//-----------------------TESTES DO GRAFO--------------------------------------
/*
	printf("gas=%d\n",g->vertices[4]->rua->listaPontos->pontoTuristico);
	printf("g=%d\n",g->vertices[34]->prox->rua->valorHistorico);
	printf("g=%d\n",g->vertices[4]->prox->prox->rua->valorHistorico);
	printf("g=%s\n",g->vertices[34]->prox->rua->nome);
	printf("g=%d\n",g->vertices[1]->rua->limite1);
	printf("g=%s\n",g->vertices[34]->prox->rua->nome);
	printf("g=%s\n",g->vertices[34]->prox->prox->rua->nome);
	printf("g=%s\n",g->vertices[34]->prox->prox->prox->rua->nome);
	printf("g=%s\n",g->vertices[34]->prox->prox->prox->prox->rua->nome);*/

//-----------------------------------------------------------------------------
//----------------------------TESTE DA ALGORITMIA------------------------------

//(1)--------------Percurso mais curto,distancia e tempo----------------------

/*	int parentes1[g->size+1], vertice1=41, vertice2=2;
	float peso1[g->size+1], distancia1, tempo1;
	AvlRuas *caminho1 = NULL;


	dijkstraMenor(g,vertice1,vertice2,peso1,parentes1);
	
	caminho1 = caminhoMaisCurto(parentes1,vertice2,g,caminho1);

	distancia1 = peso1[vertice2];

	tempo1 = daTempo(caminho1);

	inorderAVL(caminho1);
	
	printf("distancia = %f--------tempo = %f\n",distancia1, tempo1);

*/
//-----------------------------------------------------------------------------

//(3)---------Percurso mais rapido para chegar a ponto de interesse-----------

/*	int parentes3[g->size+1], vertice3, overtice = 35; //BUGBUG
	float peso3[g->size+1], tempo3;
	Ponto * ponto3 = NULL;
	AvlRuas *caminho3 = NULL;

	ponto3 = dijkstraMaisRapido(g,overtice,peso3, parentes3, strdup("Santuario do Bom Jesus do Monte"), &vertice3);

	tempo3=daPesoTotPontoInteresse(ponto3, vertice3,peso3);

	caminho3 = caminhoMaisRapido(parentes3, vertice3,ponto3->rua, g, caminho3);
	
	inorderAVL(caminho3);
	
	printf("tempo = %f\n", tempo3);
*/
//-----------------------------------------------------------------------------

//(6)---------Num raio de x metros, locais de interesse turistico-------------

// 	int parentes6[g->size+1], vertice6 = 29;
// 	float peso6[g->size+1], n6=1092.00;
// 	ListaPontosInteresse * lpi6=NULL;
// 
// 	lpi6 = dijkstraMenorAteXMetros(g,vertice6,peso6,parentes6,n6);
// 
// 	for (;lpi6!=NULL ;lpi6 = lpi6->prox)
// 	{
// 		printf("peso6=%f\n",lpi6->peso);
//         printf("lpi6=%s\n",lpi6->ponto->nome);
// 	}
// 

//---------------------------------------------------------------------------

//(7)-------Quais os n restaurantes mais proximos e suas distancias---------

// 	int parentes7[g->size+1], vertice7 = 6;
// 	float peso7[g->size+1], n7=2;
// 	ListaPontosInteresse * lpi7=NULL;
// 	
// 	lpi7 = dijkstraMenorAteN(g,vertice7,peso7,parentes7,n7);
// 	
// 	lpi7 = daPontosMaisProximos(n7,lpi7);
// 	
// 	for (;lpi7!=NULL ;lpi7 = lpi7->prox)
// 	{
// 		printf("peso7=%f\n",lpi7->peso);
// 		printf("lpi7=%s\n",lpi7->ponto->nome);
// 	}
//

//--------------------------------------------------------------------------

//(9)-------informacao sobre um ponto de interesse---------

/*	Ponto *ponto = procuraPonto(strdup("Hotel Lamacaes"), lpi);
	
	printf("descricao do ponto %s: %s\n", ponto->nome, ponto->descricao);
	*/
//--------------------------------------------------------------------------

//(10)-------saber o comprimento de uma rua---------

/*	LLRuas *llTrocos = procuraRuaDaLL(strdup("Rua Nova Santa Cruz"), lr);
	
	printf("rua %s tem: %f metros\n", daNomeRua(llTrocos->rua->nome), lenRua(llTrocos));
	*/
// 	PesquisaLargura(g,4,d,parentes,&list);

	return 0;
}
