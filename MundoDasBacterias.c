#include <stdio.h>
#include <stdlib.h>
//Arquivo.h
//#include <stdio.h>
//#include <stdlib.h>
//Constantes
//#define N 1000
//#define M 1000
//Estruturas
enum Bool_pt{FALHA,SUCESSO};
enum Bool_en{FALSE,TRUE};
enum Menu{fim,criarMundo,clonarMundo,liberarMundo,aleatorizarMundo,adicionarBacteria,adicionarBacteriaXY,matarBacteria,matarBacteriaXY,juntarMundos,guerraDosMundos,guerraDosMundosProbabilistica,tamanhoDoMundo,forcaDoMundo,MostrarMundo};
typedef struct{
    unsigned int x;//Ordem
    unsigned int y;//Força
    unsigned int z;//Lifespan
}Bacterias;
typedef struct{
    Bacterias **bacterias;
    unsigned int linhas;
    unsigned int colunas;
    unsigned int ordem;
}World;
//Protótipos
unsigned int Tamanho(unsigned int numero);
World *newWorld(unsigned int n,unsigned int m);
World *cloneWorld(World * w);
void freeWorld(World * w);
unsigned int randomWorld(World * w, unsigned int n);
unsigned int addBacterium (World * w,unsigned int n, unsigned int f, unsigned int e);
unsigned int addBacteriumXY (World * w, unsigned int n,unsigned int x, unsigned int y, unsigned int f, unsigned int e);
unsigned int killBacterium (World * w, unsigned int n);
unsigned int killBacteriumXY (World * w, unsigned int x, unsigned int y);
World *jointWorlds (World * w1, World * w2);
World *warWorlds (World*w1, World*w2);
World *probabilisticWarWorlds (World*w1, World*w2, float p);
unsigned int sizeWorld (World*w);
unsigned int forceWorld (World*w);
unsigned int showWorld (World*w);
//Fim Arquivo.h
//ProgramaPrincipal.c
int main(){
    unsigned int n,m,x,y,f,e,menu=1,mundoEscolhido,resultado;
    float p;
    World *mundo=NULL,*mundoClone=NULL,*mundosJuntos=NULL,*mundoPosGuerra=NULL,*mundoPosGuerraProbabilistico=NULL;
    while(menu)
    {
        system("CLS");
        printf("Digite 00 para terminar\n");
        printf("Digite 01 para criar uma cultura nova\n");
        printf("Digite 02 para clonar a cultura principal\n");
        printf("Digite 03 para liberar uma cultura\n");
        printf("Digite 04 para aleatorizar uma cultura com n bacterias\n");
        printf("Digite 05 para adicionar bacteria em coordenadas aleatórias em uma cultura\n");
        printf("Digite 06 para adicionar bacteria nas coordenadas X Y em uma cultura\n");
        printf("Digite 07 para matar bacteria de ordem n em uma cultura\n");
        printf("Digite 08 para matar bacteria nas coordenadas X Y em uma cultura\n");
        printf("Digite 09 para misturar as culturas\n");
        printf("Digite 10 para guerrear culturas\n");
        printf("Digite 11 para guerrear culturas probabilisticamente\n");
        printf("Digite 12 para saber o tamanho de uma cultura\n");
        printf("Digite 13 para determinar a forca de uma cultura\n");
        printf("Digite 14 para mostrar a cultura\n");
        scanf("%u",&menu);
        switch (menu)
        {
        case fim:
            printf("Obrigado por utilizar meu programa.\n");
            break;
        case criarMundo:
            if(mundo!=NULL)
                {
                    freeWorld(mundo);
                }
            printf("Qual a altura da cultura?\n");
            scanf("%u",&n);
            printf("Qual a largura da cultura?\n");
            scanf("%u",&m);
            mundo = newWorld(n,m);
            if(mundo!=NULL)
            printf("Nova cultura gerada!!\n");
            system("PAUSE");
            break;
        case clonarMundo:
            if(mundo!=NULL){
            if(mundoClone!=NULL)
                freeWorld(mundoClone);
            mundoClone = cloneWorld(mundo); 
            }else{
                printf("Nao ha mundos\n");
            }
            if(mundo!=NULL)
            printf("Nova cultura gerada\n");
            system("PAUSE");
            break;
        case liberarMundo:
            printf("Digite 1 para liberar a primeira cultura.\n");
            printf("Digite 2 para liberar a cultura clone.\n");
            if(mundosJuntos!=NULL)
            printf("Digite 3 para liberar as culturas juntas.\n");
            if(mundoPosGuerra!=NULL)
            printf("Digite 4 para liberar o resultado culturas guerra.\n");
            if(mundoPosGuerraProbabilistico!=NULL)
            printf("Digite 5 para liberar a cultura probabilistica.\n");
            scanf("%u",&mundoEscolhido);
            if((mundo==NULL&&mundoEscolhido==1)||(mundoClone==NULL&&mundoEscolhido==2)||(mundosJuntos!=NULL&&mundoEscolhido==3)||(mundoPosGuerra!=NULL&&mundoEscolhido==4)||(mundoPosGuerraProbabilistico!=NULL&&mundoEscolhido==5))
            {
                printf("Nao ha cultura para liberar\n");
                system("PAUSE");
                break;
            }
            if(mundoEscolhido<1||mundoEscolhido>5)
            {
                printf("Cultura invalida!!\n");
                system("PAUSE");
                break;
            }
            if(mundoEscolhido==1&&mundo!=NULL)
                freeWorld(mundo);
            else if(mundoClone!=NULL&&mundoEscolhido==2)
                freeWorld(mundoClone);    
            else if(mundosJuntos!=NULL&&mundoEscolhido==3)
            freeWorld(mundosJuntos);
            else if(mundoPosGuerra!=NULL&&mundoEscolhido==4)
            freeWorld(mundoPosGuerra);
            else if(mundoPosGuerraProbabilistico!=NULL&&mundoEscolhido==5)
            freeWorld(mundoPosGuerraProbabilistico);
            system("PAUSE");
            break;
        case aleatorizarMundo:
            printf("Digite 1 para a primeira cultura.\n");
            printf("Digite 2 para a cultura clone.\n");
            scanf("%u",&mundoEscolhido);
            if(mundoEscolhido<1||mundoEscolhido>2)
            {
                printf("Cultura invalida!!\n");
                system("PAUSE");
                break;
            }
            printf("Digite o numero de bacterias que deseja aleatorizar: ");
            scanf("%u",&n);
            if(mundoEscolhido==1&&mundo!=NULL)
                resultado=randomWorld(mundo,n);
            else if(mundoClone!=NULL&&mundoEscolhido==2)
                resultado=randomWorld(mundoClone,n);
            if(resultado == FALHA )
                printf("FALHA\n");
            else
                printf("SUCESSO\n");
            system("PAUSE");
            break;
        case adicionarBacteria:
            printf("Digite 1 para a primeira cultura.\n");
            printf("Digite 2 para a cultura clone.\n");
            scanf("%u",&mundoEscolhido);
            if(mundoEscolhido<1||mundoEscolhido>2)
            {
                printf("Cultura invalida!!\n");
                system("PAUSE");
                break;
            }
            printf("Digite a ordem que deseja para a bacteria: ");
            scanf("%u",&n);
            printf("Digite a forca que deseja para a bateria: ");
            scanf("%u",&f);
            printf("Digite a expectativa de vida, em ciclos, da bacteria:");
            scanf("%u",&e);
            if(mundoEscolhido==1&&mundo!=NULL)
                resultado=addBacterium(mundo,n,f,e);
            else if(mundoClone!=NULL&&mundoEscolhido==2)
                resultado=addBacterium(mundoClone,n,f,e);
            if(resultado == FALHA )
                printf("FALHA\n");
            else
                printf("SUCESSO\n");
            system("PAUSE");
            break;
        case adicionarBacteriaXY:
            printf("Digite 1 para a primeira cultura.\n");
            printf("Digite 2 para a cultura clone.\n");
            scanf("%u",&mundoEscolhido);
            if(mundoEscolhido<1||mundoEscolhido>2)
            {
                printf("Cultura invalida!!\n");
                system("PAUSE");
                break;
            }
            printf("Digite qual linha e qual coluna, respectivamente, deseja para a bacteria: ");
            scanf("%u %u",&x,&y);
            printf("Digite a ordem que deseja para a bacteria: ");
            scanf("%u",&n);
            printf("Digite a forca que deseja para a bateria: ");
            scanf("%u",&f);
            printf("Digite a expectativa de vida, em ciclos, da bacteria:");
            scanf("%u",&e);
            if(mundoEscolhido==1&&mundo!=NULL)
                resultado=addBacteriumXY(mundo,x,y,n,f,e);
            else if(mundoClone!=NULL&&mundoEscolhido==2)
                resultado=addBacteriumXY(mundoClone,x,y,n,f,e);
            if(resultado == FALHA )
                printf("FALHA\n");
            else
                printf("SUCESSO\n");
            system("PAUSE");
            break;
        case matarBacteria:
            printf("Digite 1 para a primeira cultura.\n");
            printf("Digite 2 para a cultura clone.\n");
            scanf("%u",&mundoEscolhido);
            if(mundoEscolhido<1||mundoEscolhido>2)
            {
                printf("Cultura invalida!!\n");
                system("PAUSE");
                break;
            }
            printf("Digite a ordem da bacteria que deseja matar: ");
            scanf("%u",&n);
            if(mundoEscolhido==1&&mundo!=NULL)
                resultado=killBacterium(mundo,n);
            else if(mundoClone!=NULL&&mundoEscolhido==2)
                resultado=killBacterium(mundoClone,n);
            if(resultado == FALHA )
                printf("FALHA\n");
            else
                printf("SUCESSO\n");
            system("PAUSE");
            break;
        case matarBacteriaXY:
            printf("Digite 1 para a primeira cultura.\n");
            printf("Digite 2 para a cultura clone.\n");
            scanf("%u",&mundoEscolhido);
            if(mundoEscolhido<1||mundoEscolhido>2)
            {
                printf("Cultura invalida!!\n");
                system("PAUSE");
                break;
            }
            printf("Digite qual linha e qual coluna, respectivamente, da bacteria que deseja matar: ");
            scanf("%u %u",&x,&y);
            if(mundoEscolhido==1&&mundo!=NULL)
                resultado=killBacteriumXY(mundo,x,y);
            else if(mundoClone!=NULL&&mundoEscolhido==2)
                resultado=killBacteriumXY(mundoClone,x,y);
            if(resultado == FALHA )
                printf("FALHA\n");
            else
                printf("SUCESSO\n");
            system("PAUSE");
            break;
        case juntarMundos:
            if(mundosJuntos!=NULL)
                freeWorld(mundosJuntos);
            mundosJuntos = jointWorlds(mundo,mundoClone);
            if(mundosJuntos!=NULL)
                printf("Nova cultura gerada\n");
            system("PAUSE");
            break;
        case guerraDosMundos:
            if(mundoPosGuerra!=NULL)
                freeWorld(mundoPosGuerra);
            mundoPosGuerra = warWorlds(mundo,mundoClone); 
            if(mundoPosGuerra!=NULL)
                printf("Nova cultura gerada\n");
            system("PAUSE");
            break;
        case guerraDosMundosProbabilistica:
            if(mundoPosGuerraProbabilistico!=NULL)
                freeWorld(mundoPosGuerraProbabilistico);
            printf("Qual a probabilidade de uma bacteria mais forte fagocitar uma mais fraca?\n");
            scanf("%f",&p);
            mundoPosGuerraProbabilistico = probabilisticWarWorlds(mundo,mundoClone,p); 
            if(mundoPosGuerraProbabilistico!=NULL)
                printf("Nova cultura gerada\n");
            system("PAUSE");
            break;
        case tamanhoDoMundo:
            printf("Digite 1 para a primeira cultura.\n");
            printf("Digite 2 para a cultura clone.\n");
            if(mundosJuntos!=NULL)
            printf("Digite 3 para as culturas juntas.\n");
            if(mundoPosGuerra!=NULL)
            printf("Digite 4 para o resultado culturas guerra.\n");
            if(mundoPosGuerraProbabilistico!=NULL)
            printf("Digite 5 para a cultura probabilistica.\n");
            scanf("%u",&mundoEscolhido);
            if(mundoEscolhido==1&&mundo!=NULL)
                printf("%u\n",sizeWorld(mundo));
            else if(mundoClone!=NULL&&mundoEscolhido==2)
                printf("%u\n",sizeWorld(mundoClone));
            else if(mundosJuntos!=NULL&&mundoEscolhido==3)
                printf("%u\n",sizeWorld(mundosJuntos));
            else if(mundoPosGuerra!=NULL&&mundoEscolhido==4)
                printf("%u\n",sizeWorld(mundoPosGuerra));
            else if(mundoPosGuerraProbabilistico!=NULL&&mundoEscolhido==5)
                printf("%u\n",sizeWorld(mundoPosGuerraProbabilistico));
            system("PAUSE");
            break;
        case forcaDoMundo:
            printf("Digite 1 para a primeira cultura.\n");
            printf("Digite 2 para a cultura clone.\n");
            if(mundosJuntos!=NULL)
            printf("Digite 3 para as culturas juntas.\n");
            if(mundoPosGuerra!=NULL)
            printf("Digite 4 para o resultado culturas guerra.\n");
            if(mundoPosGuerraProbabilistico!=NULL)
            printf("Digite 5 para a cultura probabilistica.\n");
            scanf("%u",&mundoEscolhido);
            if(mundoEscolhido==1&&mundo!=NULL)
                printf("%u\n",forceWorld(mundo));
            else if(mundoClone!=NULL&&mundoEscolhido==2)
                printf("%u\n",forceWorld(mundoClone));
            else if(mundosJuntos!=NULL&&mundoEscolhido==3)
                printf("%u\n",forceWorld(mundosJuntos));
            else if(mundoPosGuerra!=NULL&&mundoEscolhido==4)
                printf("%u\n",forceWorld(mundoPosGuerra));
            else if(mundoPosGuerraProbabilistico!=NULL&&mundoEscolhido==5)
                printf("%u\n",forceWorld(mundoPosGuerraProbabilistico));
            system("PAUSE");
            break;
        case MostrarMundo:
            printf("Digite 1 para a primeira cultura.\n");
            printf("Digite 2 para a cultura clone.\n");
            if(mundosJuntos!=NULL)
            printf("Digite 3 para as culturas juntas.\n");
            if(mundoPosGuerra!=NULL)
            printf("Digite 4 para o resultado culturas guerra.\n");
            if(mundoPosGuerraProbabilistico!=NULL)
            printf("Digite 5 para a cultura probabilistica.\n");
            scanf("%u",&mundoEscolhido);
            if(mundoEscolhido==1&&mundo!=NULL)
                showWorld(mundo);
            else if(mundoClone!=NULL&&mundoEscolhido==2)
                showWorld(mundoClone);
            else if(mundosJuntos!=NULL&&mundoEscolhido==3)
                showWorld(mundosJuntos);
            else if(mundoPosGuerra!=NULL&&mundoEscolhido==4)
                showWorld(mundoPosGuerra);
            else if(mundoPosGuerraProbabilistico!=NULL&&mundoEscolhido==5)
                showWorld(mundoPosGuerraProbabilistico);
            printf("\n");
            system("PAUSE");
            break;
        default:
            printf("\nNumero Invalido!\n");
            system("PAUSE");

        }
    }
    if(mundo!=NULL)
    freeWorld(mundo);
    if(mundoClone!=NULL)
    freeWorld(mundoClone);
    if(mundosJuntos!=NULL)
    freeWorld(mundosJuntos);
    if(mundoPosGuerra!=NULL)
    freeWorld(mundoPosGuerra);
    if(mundoPosGuerraProbabilistico!=NULL)
    freeWorld(mundoPosGuerraProbabilistico);
}
//Fim ProgramaPrincipal.c
//Arquivo.c
unsigned int Tamanho(unsigned int numero){
    unsigned int i=1;
    while (numero>9)
    {
        numero/=10;
        i++;
    }

    return i;
}
World *newWorld(unsigned int n,unsigned int m){
    unsigned int i,j;
    World *mundo;
    mundo=(World*)malloc(sizeof(World));
    mundo->bacterias=(Bacterias**)malloc(sizeof(Bacterias*)*n);
    for (i = 0; i < n; i++)
    {
        mundo->bacterias[i]=(Bacterias*)malloc(sizeof(Bacterias)*m);
    }
    for ( i = 0; i < n; i++)
    {
        for ( j = 0; j < m; j++)
        {
            mundo->bacterias[i][j].x=0;
            mundo->bacterias[i][j].y=0;
            mundo->bacterias[i][j].z=0;
        }
    }
    mundo->linhas=n;
    mundo->colunas=m;
    mundo->ordem=0;
    return mundo;
}
World *cloneWorld(World * w){
    unsigned int i,j;
    World *clone;
    clone=(World*)malloc(sizeof(World));
    clone->bacterias=(Bacterias**)malloc(sizeof(Bacterias*)*w->linhas);
    for (i = 0; i < w->linhas; i++)
    {
        clone->bacterias[i]=(Bacterias*)malloc(sizeof(Bacterias)*w->colunas);
    }
    for ( i = 0; i < w->linhas; i++)
    {
        for ( j = 0; j < w->colunas; j++)
        {
            clone->bacterias[i][j].x=w->bacterias[i][j].x;
            clone->bacterias[i][j].y=w->bacterias[i][j].y;
            clone->bacterias[i][j].z=w->bacterias[i][j].z;
        }
    }
    clone->linhas=w->linhas;
    clone->colunas=w->colunas;
    clone->ordem=w->ordem;
    return clone;
}
void freeWorld(World * w){
    unsigned int i,j;
    for (i = w->linhas-1; i > -1; i--)
    {
        free(w->bacterias[i]);
    }
    free(w->bacterias);
    free(w);
    w=NULL;
}
unsigned int randomWorld(World * w, unsigned int n){
    unsigned int i,j,lin,col,aux=0;
    for(i=0;i<w->linhas;i++)
    {
        for(j=0;j<w->colunas;j++)
        {
            if(w->bacterias[i][j].x==0)
                aux++;
        }
        if(aux>=n)
        {
            break;
        }
    }
    if(aux<n)
    {
        return FALHA;
    }
    for(i=0;i<n;i++)
    {
        do
        {
            lin=rand()%w->linhas;
            col=rand()%w->colunas;
        }while(w->bacterias[lin][col].x!=0);
        w->ordem++;
        w->bacterias[lin][col].x=w->ordem;
        w->bacterias[lin][col].y=(rand()%100)+1;
    }  
    return SUCESSO;
}
unsigned int addBacterium (World * w,unsigned int n, unsigned int f, unsigned int e){
    unsigned int pos_linha,pos_coluna;
    pos_linha=rand()%w->linhas;
    pos_coluna=rand()%w->colunas;
    if (w->bacterias[pos_linha][pos_coluna].x>0)
    {
        return FALHA;
    }
    w->bacterias[pos_linha][pos_coluna].x=n;
    w->bacterias[pos_linha][pos_coluna].y=f;
    w->bacterias[pos_linha][pos_coluna].z=e;
    if(n>w->ordem)
        w->ordem=n;
    return SUCESSO;
}
unsigned int addBacteriumXY (World * w, unsigned int n,unsigned int x, unsigned int y, unsigned int f, unsigned int e){
    x--;
    y--;
    if(x>=w->linhas||y>=w->colunas)
        return FALHA;
    if (w->bacterias[x][y].x>0)
        return FALHA;
    w->bacterias[x][y].x=n;
    w->bacterias[x][y].y=f;
    w->bacterias[x][y].z=e;
    if(n>w->ordem)
        w->ordem=n;
    return SUCESSO;
}
unsigned int killBacterium (World * w, unsigned int n){
    unsigned int i,j,matou_quantas=0;
    for ( i = 0; i < w->linhas; i++)
    {
        for ( j = 0; j < w->colunas; j++)
        {
            if(w->bacterias[i][j].x==n)
            {
                matou_quantas++;
                w->bacterias[i][j].x=0;
                w->bacterias[i][j].y=0;
                w->bacterias[i][j].z=0;
            }
        }
    }
    if(matou_quantas>0)
        return SUCESSO;
    else
        return FALHA;
}
unsigned int killBacteriumXY (World * w, unsigned int x, unsigned int y){
    x--;
    y--;
    if(x>=w->linhas||y>=w->colunas)
        return FALHA;
    if(w->bacterias[x][y].x>0)
    {
        w->bacterias[x][y].x=0;
        w->bacterias[x][y].y=0;
        w->bacterias[x][y].z=0;
        return SUCESSO;
    }
    else
        return FALHA;
    
}
World *jointWorlds (World * w1, World * w2){
    unsigned int i,j;
    World *mundo;
    mundo=(World*)malloc(sizeof(World));
    mundo->bacterias=(Bacterias**)malloc(sizeof(Bacterias*)*w1->linhas);
    for (i = 0; i < w1->linhas; i++)
    {
        mundo->bacterias[i]=(Bacterias*)malloc(sizeof(Bacterias)*w1->colunas);
    }
    for ( i = 0; i < w1->linhas; i++)
    {
        for ( j = 0; j < w1->colunas; j++)
        {
            mundo->bacterias[i][j].x=w1->bacterias[i][j].x;
            mundo->bacterias[i][j].y=w1->bacterias[i][j].y;
            mundo->bacterias[i][j].z=w1->bacterias[i][j].z;
        }
    }
    mundo->linhas=w1->linhas;
    mundo->colunas=w1->colunas;
    mundo->ordem=w1->ordem;
    for ( i = 0; i < mundo->linhas; i++)
    {
        for ( j = 0; j < mundo->colunas; j++)
        {
            if(mundo->bacterias[i][j].x>0&&w2->bacterias[i][j].x>0)
            {
                freeWorld(mundo);
                return NULL;
            }
            mundo->ordem++;
            mundo->bacterias[i][j].x = mundo->ordem;
            mundo->bacterias[i][j].y = w2->bacterias[i][j].y;
            mundo->bacterias[i][j].z = w2->bacterias[i][j].z;
        }
    }
    return mundo;
}
World *warWorlds (World*w1, World*w2){
    unsigned int i,j;
    World *mundo;
    mundo=(World*)malloc(sizeof(World));
    mundo->bacterias=(Bacterias**)malloc(sizeof(Bacterias*)*w1->linhas);
    for (i = 0; i < w1->linhas; i++)
    {
        mundo->bacterias[i]=(Bacterias*)malloc(sizeof(Bacterias)*w1->colunas);
    }
    for ( i = 0; i < w1->linhas; i++)
    {
        for ( j = 0; j < w1->colunas; j++)
        {
            mundo->bacterias[i][j].x=w1->bacterias[i][j].x;
            mundo->bacterias[i][j].y=w1->bacterias[i][j].y;
            mundo->bacterias[i][j].z=w1->bacterias[i][j].z;
        }
    }
    mundo->linhas=w1->linhas;
    mundo->colunas=w1->colunas;
    mundo->ordem=w1->ordem;
    for ( i = 0; i < w1->linhas; i++)
    {
        for ( j = 0; j < w1->colunas; j++)
        {
            if(mundo->bacterias[i][j].y>=w2->bacterias[i][j].y)
            {
                mundo->bacterias[i][j].y += w2->bacterias[i][j].y;
                if(mundo->bacterias[i][j].y>100)
                    mundo->bacterias[i][j].y=100;
                if(w2->bacterias[i][j].z>mundo->bacterias[i][j].z)
                    mundo->bacterias[i][j].z = w2->bacterias[i][j].z;
            }
            else
            {
                mundo->bacterias[i][j].x=w2->bacterias[i][j].x;
                mundo->bacterias[i][j].y += w2->bacterias[i][j].y;
                if(mundo->bacterias[i][j].y>100)
                    mundo->bacterias[i][j].y=100;
                if(w2->bacterias[i][j].z>mundo->bacterias[i][j].z)
                    mundo->bacterias[i][j].z = w2->bacterias[i][j].z;
            }
        }
    }
    return mundo;
}
World *probabilisticWarWorlds (World*w1, World*w2, float p){
    unsigned int i,j;
    World *mundo;
    mundo=(World*)malloc(sizeof(World));
    mundo->bacterias=(Bacterias**)malloc(sizeof(Bacterias*)*w1->linhas);
    for (i = 0; i < w1->linhas; i++)
    {
        mundo->bacterias[i]=(Bacterias*)malloc(sizeof(Bacterias)*w1->colunas);
    }
    for ( i = 0; i < w1->linhas; i++)
    {
        for ( j = 0; j < w1->colunas; j++)
        {
            mundo->bacterias[i][j].x=w1->bacterias[i][j].x;
            mundo->bacterias[i][j].y=w1->bacterias[i][j].y;
            mundo->bacterias[i][j].z=w1->bacterias[i][j].z;
        }
    }
    mundo->linhas=w1->linhas;
    mundo->colunas=w1->colunas;
    mundo->ordem=w1->ordem;
    for ( i = 0; i < w1->linhas; i++)
    {
        for ( j = 0; j < w1->colunas; j++)
        {
            if(rand()%101<=p*100)
            {
                if(mundo->bacterias[i][j].y>=w2->bacterias[i][j].y)
                {
                    mundo->bacterias[i][j].y += w2->bacterias[i][j].y;
                    if(mundo->bacterias[i][j].y>100)
                    mundo->bacterias[i][j].y=100;
                    if(w2->bacterias[i][j].z>=mundo->bacterias[i][j].z)
                        mundo->bacterias[i][j].z = w2->bacterias[i][j].z;
                }
                else
                {
                    mundo->bacterias[i][j].x=w2->bacterias[i][j].x;
                    mundo->bacterias[i][j].y += w2->bacterias[i][j].y;
                    if(mundo->bacterias[i][j].y>100)
                        mundo->bacterias[i][j].y=100;
                    if(w2->bacterias[i][j].z>=mundo->bacterias[i][j].z)
                        mundo->bacterias[i][j].z = w2->bacterias[i][j].z;
                }
            }
            else
            {
                
                if(mundo->bacterias[i][j].y<=w2->bacterias[i][j].y&&mundo->bacterias[i][j].x>0)
                {
                    mundo->bacterias[i][j].y += w2->bacterias[i][j].y;
                    if(mundo->bacterias[i][j].y>100)
                    mundo->bacterias[i][j].y=100;
                    if(w2->bacterias[i][j].z>=mundo->bacterias[i][j].z)
                        mundo->bacterias[i][j].z = w2->bacterias[i][j].z;
                }
                else
                {
                    mundo->bacterias[i][j].x=w2->bacterias[i][j].x;
                    mundo->bacterias[i][j].y += w2->bacterias[i][j].y;
                    if(mundo->bacterias[i][j].y>100)
                        mundo->bacterias[i][j].y=100;
                    if(w2->bacterias[i][j].z>=mundo->bacterias[i][j].z)
                        mundo->bacterias[i][j].z = w2->bacterias[i][j].z;
                }
            }
        }
    }
    return mundo;
}
unsigned int sizeWorld (World*w){
    unsigned int i,j,tamanho=0;
    for ( i = 0; i < w->linhas; i++)
    {
        for ( j = 0; j < w->colunas; j++)
        {
            tamanho+=w->bacterias[i][j].x;
        }
    }
    return tamanho;
}
unsigned int forceWorld (World*w){
    unsigned int i,j,forca=0;
    for ( i = 0; i < w->linhas; i++)
    {
        for ( j = 0; j < w->colunas; j++)
        {
            forca+=w->bacterias[i][j].y;
        }
    }
    return forca;
}
unsigned int showWorld (World*w){
    unsigned int i,j,k,tam_f,tam_ord,aux_y[2],aux=0,aux2[2];
    aux_y[0]=1;
    aux_y[1]=w->colunas;
    if(w->colunas>10)
    {
        printf("Como o numero de colunas eh maior que 10, eh necessarios especificar a coluna inicial e a final,respectivamente:\n");
        scanf("%u %u",&aux_y[0],&aux_y[1]);
    }
    aux2[0]=Tamanho(aux_y[0]);
    aux2[1]=Tamanho(aux_y[1]);
    for(i=0;i<8-aux2[0];i++)
    {
        printf(" ");
    }
    printf("%u",aux_y[0]);
    for(i=0;i<(aux_y[1]-aux_y[0])*13-aux2[1];i++)
    {
        printf(" ");
    }
    printf("%u\n",aux_y[1]);
    for(i=0;i<(2*w->linhas);i++)
    {
        if(i%2==1)
        {
            printf("|");
        }
        else{
            printf("+");
        }
        for ( j = aux_y[0]-1; j < aux_y[1]; j++)
        {
            tam_f=Tamanho(w->bacterias[aux][j].y);
            tam_ord=Tamanho(w->bacterias[aux][j].x);
            if(i%2==1)
            {
                for (k = 0; k < 10-tam_ord-tam_f; k++)
                {
                    printf(" ");
                }
                printf("%u,%u |",w->bacterias[aux][j].x,w->bacterias[aux][j].y);
                
            }
            else
            for (k = 0; k < 13; k++)
            {
                if(k==12)
                    printf("+");
                else
                    printf("-");
            }
        }
        printf("\n");
        if(i%2==1)
        {
            aux++;
        }
    }
    for(i=0;i<aux_y[1]-aux_y[0]+1;i++)
    {
        printf("+");
        for(k=0;k<12;k++)
        {
            printf("-");
        }
    }
    printf("+");
}
//Fim Arquivo.c