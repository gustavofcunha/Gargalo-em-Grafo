#include <iostream>
#include <string>
#include <deque>

#define LIMITE_SUP_PESO 100001

/**
* -Descricao: calcula o gargalo (peso minimo das arestas) de um caminho
* -Entrada: malha, caminho
* -Saida: menorPeso
*/
int calculaGargalo(int **malha, std::deque<int> caminho){
    int menorPeso = LIMITE_SUP_PESO;

    for(int i=0; i<(int(caminho.size())-1); i++){
        if(malha[caminho[i]][caminho[i+1]] < menorPeso){
            menorPeso = malha[caminho[i]][caminho[i+1]];
        }
    }

    return menorPeso;
}

/**
* -Descricao: busca em profundidade para encontrar todos os caminhos possiveis
*  entre origem e destino, armazenando os gargalos desses caminhos no deque gargalos 
* -Entrada: explorado, N, malha, origem, destino, caminho, gargalos(referencia)
* -Saida: N/A
*/
void DFS(bool explorado[], int N, int **malha, int origem, int destino, 
         std::deque<int> caminho, std::deque<int> &gargalos){
    explorado[origem] = true;
    caminho.push_back(origem);

    //condicao de parada: encontrou o destino
    if(origem == destino){
        //armazena o gargalo do caminho encontrado
        gargalos.push_back(calculaGargalo(malha, caminho));
    }

    else{
        //chama DFS recursivamente para todos os vizinhos de origem
        for(int i=0; i<N; i++){
            if(explorado[i] == false && malha[origem][i] > 0){
                DFS(explorado, N, malha, i, destino, caminho, gargalos);
            }
        }
    }

    //regride um nivel de profundidade, para explorar todos os caminhos possiveis
    explorado[caminho.back()] = false;
    caminho.pop_back();
}

/**
* -Descricao: encontra o gargalo maximo dentre todos os 
*  gargalos de todos os caminhos possiveis entre origem e destino
* -Entrada: N, malha, origem, destino
* -Saida: caminhoMaximo
*/
int encontraCaminhoMaximo(int N, int **malha, int origem, int destino){
    std::deque<int> gargalos, caminho;
    bool explorado[N];

    for(int i=0; i<N; i++){
        explorado[i] = false;
    }

    DFS(explorado, N, malha, origem, destino, caminho, gargalos);

    int caminhoMaximo = 0;
    //encontra maximo gargalo
    for(int i=0; i<(int(gargalos.size())); i++){
        if(gargalos[i] > caminhoMaximo){
            caminhoMaximo = gargalos[i];
        }
    }
    
    return caminhoMaximo;
}

/**
* -Descricao: funcao principal, processa entrada e chama metodos principais
* -Entrada: N/A
* -Saida: 0
*/
int main(){
    //variaveis auxiliares
    std::string buf, aux, aux2;
    int M, N, Q, i, j, u, v, origem, destino, capacidade;

    //processando parametros de entrada
    getline(std::cin, buf);
    std::size_t pos = buf.find_first_of(" ");
    aux = buf;
    N = stoi(buf.erase(pos));
    aux = aux.substr(pos+1);
    pos = aux.find_first_of(" ");
    aux2 = aux;
    M = stoi(aux.erase(pos));
    Q = stoi(aux2.substr(pos+1));

    //matriz de adjacencias que representa a malha rodoviaria
    int **malha;

    //alocacao dinamica da matriz de adjacencias
    malha = new int* [N];
    for(i=0; i<N; i++){ 
        malha[i] = new int[N];
    }

    //incializacao da malha sem rodovias
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            malha[i][j] = 0;
        }
    }

    //processando rodovias e povoando matriz de adjacencias
    for(i=0; i<M; i++){
        getline(std::cin, buf);
        std::size_t pos = buf.find_first_of(" ");
        aux = buf;
        u = stoi(buf.erase(pos));
        aux = aux.substr(pos+1);
        pos = aux.find_first_of(" ");
        aux2 = aux;
        v = stoi(aux.erase(pos));
        capacidade = stoi(aux2.substr(pos+1));

        malha[u-1][v-1] = capacidade;
    }
   
    //processando consultas
    for(i=0; i<Q; i++){
        getline(std::cin, buf);
        aux = buf;
        std::size_t pos = buf.find_first_of(" ");
        origem = stoi(buf.erase(pos));
        destino = stoi(aux.substr(pos+1));

        //impressao do fluxo maximo na saida padrao
        //indices substraidos de 1 pois as dimensoes da malha iniciam-se na posicao 0
        std::cout << std::endl << encontraCaminhoMaximo(N, malha, origem-1, destino-1) 
        << std::endl;
    }

    //desalocacao da matriz de adjacencias
    for(i=0; i<N; i++){ 
        delete(malha[i]);
    }
    delete(malha);

    return 0;
}