#include <iostream>
#include <vector>
#include "matrizadj.h"

using namespace std;

const vector<string> explode(const string& s, const char& c);
MatrizAdj abre_grafo();
MatrizAdj cria_grafo();
void salva_grafo(MatrizAdj grafo, string nome);

int main()
{
    MatrizAdj grafo;
    while(true){
        int op;
        cout<< "->> GRAFOS <<-" << endl;
        cout<< endl << "Escolha a opcao" << endl;
        cout<< "   [1] Criar Grafo" << endl;
        cout<< "   [2] Abrir Grafo" << endl;
        cout<< "   [3] Encerrar programa" << endl;
        cout<< "   ->> ";
        cin>>op;

        if(op == 1){
            grafo = cria_grafo();
        }else if(op == 2){
            grafo = abre_grafo();
        }else{
            return 0;
        }
        do{
            system("cls");
            cout<< " >> Matriz de Adjacencia do Grafo <<" << endl;
            grafo.print_matriz();
            cout<< endl << endl << " >> Escolha a opcao para ser realizada <<" << endl;
            cout<< " [1] Caminho Profundidade" << endl;
            cout<< " [2] Caminho Largura" << endl;
            cout<< " [3] Fecho Transitivo" << endl;
            cout<< " [4] Determinar Subgrafos" << endl;
            cout<< " [5] Retornar para menu de criacao do grafo" << endl;
            cout<< " [6] Encerrar programa" << endl;
            cout<< " [7] Vertice adjascente mais proximo" << endl;
            cout<< " ->> ";
            cin>>op;
            system("cls");
            //Inicio do processo
            int vertice_inicial, transitivo;
            char salva;
            string nome;
            switch(op){
                case 1:
                    cout<< " -> Informe o vertice inicial: ";
                    cin>>vertice_inicial;
                    grafo.caminho_profundidade(vertice_inicial);
                    cout<< endl << endl << " >> Tecla ENTER para retornar << ";
                    cin.ignore().get();
                    system("cls");
                    break;
                case 2:
                    cout<< " -> Informe o vertice inicial: ";
                    cin>>vertice_inicial;
                    grafo.caminho_largura(vertice_inicial);
                    cout<< endl << endl << " >> Tecla ENTER para retornar << ";
                    cin.ignore().get();
                    system("cls");
                    break;
                case 3:
                    cout<< " >> FECHO TRANSITIVO <<" << endl;
                    cout<< " -> Informe o vertice inicial: ";
                    cin>>vertice_inicial;
                    cout<< " -> Transitivo Direto[1] ou Inverso[2]: ";
                    cin>>transitivo;
                    if(transitivo == 1)
                        grafo.fecho_transitivo(vertice_inicial-1,true);
                    else
                        grafo.fecho_transitivo(vertice_inicial-1,false);
                    cout<< endl << endl << " >> Tecla ENTER para retornar << ";
                    cin.ignore().get();
                    system("cls");
                    break;
                case 4:
                    grafo.determina_subgrafo();
                    cout<< endl << endl << " >> Tecla ENTER para retornar << ";
                    cin.ignore().get();
                    system("cls");
                    break;
                case 5:
                    cout<< "Salvar grafo em arquivo?[s/n]" << endl;
                    cout<< " -> ";
                    cin>>salva;
                    if(salva == 's'){
                        cout<< "Nome do arquivo: ";
                        cin>>nome;
                        salva_grafo(grafo,nome);
                    }
                    break;
                case 6:
                    cout<< "Salvar grafo em arquivo?[s/n]" << endl;
                    cout<< " -> ";
                    cin>>salva;
                    if(salva == 's'){
                        cout<< "Nome do arquivo: ";
                        cin>>nome;
                        salva_grafo(grafo,nome);
                    }
                    return 0;
                 case 7:
                    grafo.vertice_adjacente_mais_proximo();
                    break;

            }
        }while(op < 5);
    }
    return 0;
}

const vector<string> explode(const string& s, const char& c)
{
    string buff{""};
    vector<string> v;

    for(auto n:s){
        if(n != c) buff+=n; else
        if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);
    return v;
}

MatrizAdj abre_grafo(){
    MatrizAdj grafo_aux;
    ifstream leitura;
    char linha[20];
    vector<string> read;
    string aux, caminho;
    int aux1, aux2, aux3, n_linhas = 1;

    int **matriz;

    cout<< endl << " > Informe o caminho do arquivo com o grafo:" << endl;
    cout<<"->> ";
    cin>>caminho;
    leitura.open("C:/Users/Guilherme/Documents/Univali/7 Periodo/Grafos/M3/Grafos-master/Grafos_Peso_arestas/m1.txt");
    if(!leitura.is_open( )){
        cout<< "Nao foi possivel abrir arquivo!" << endl;
        leitura.clear( );
    }
    while (leitura.getline(linha,20)) {
        if(n_linhas == 1){
            //cout<< linha << endl;
            aux = linha;
            matriz = new int* [atoi(aux.c_str())];
            for (int i = 0; i < atoi(aux.c_str()); i++){
                matriz[i] = new int [atoi(aux.c_str())];
                for(int j = 0; j < atoi(aux.c_str()); j++){
                    matriz[i][j] = 0;
                }
            }
            grafo_aux.setMatriz(matriz);
            grafo_aux.setVertices(atoi(aux.c_str()));
            n_linhas++;
        }else if(n_linhas == 2){
            cout<< linha <<endl;
            aux = linha;
            if(atoi(aux.c_str()) == 1)
                grafo_aux.setDirigida(true);
            else
                grafo_aux.setDirigida(false);
            n_linhas++;
        }else{
            cout<< linha << endl;
            read = explode(linha,',');
            aux = read.at(0); aux1 = atoi(aux.c_str());
            aux = read.at(1); aux2 = atoi(aux.c_str());
            aux = read.at(2); aux3 = atoi(aux.c_str());
            cout<< aux1 << " : " << aux2 << endl;
            grafo_aux.add_vertice(aux1,aux2, aux3);
            if(!grafo_aux.getDirigida())
                grafo_aux.add_vertice(aux2, aux1, aux3);
        }
    }
    leitura.close();
    return grafo_aux;
}

MatrizAdj cria_grafo(){
    MatrizAdj aux;
    int n_vert;
    //Informacoes do grafo - Vertices - Dirigido - Ligacoes
    cout<< endl << ">> CRIACAO DO GRAFO <<" << endl;
    cout<< " -> Quantidade de vertices: ";
    cin>>n_vert;
    char op;
    cout<< " -> A matriz é dirigida? [s/n]: ";
    cin>>op;

    int **matriz = new int* [n_vert];
    for (int i = 0; i < n_vert; i++){
        matriz[i] = new int [n_vert];
        for(int j = 0; j < n_vert; j++){
            matriz[i][j] = 0;
        }
    }
    aux.setMatriz(matriz);
    aux.setVertices(n_vert);
    if(op == 's')
        aux.setDirigida(true);
    else
        aux.setDirigida(false);

    cout<< " -> LIGACOES:" << endl;
    cout<< " >> Informe as ligacoes separadas com virgula [ex:1,2] <<" << endl;
    cout<< " >> Tecla 'p' para finalizar a insercao de ligacoes <<" << endl;
    int cont=1;
    string leitura;
    vector<string> v;
    int pos[2];
    do{
        /*cout<< cont << ") Ligacao numero "<< cont <<": ";
        cin>>leitura;
        if(leitura == "p") break;

        v = explode(leitura,',');
        leitura=v.front(); pos[0]=atoi(leitura.c_str());
        leitura=v.back(); pos[1]=atoi(leitura.c_str());

        aux.add_vertice(pos[0],pos[1]);
        if(op == 'n') aux.add_vertice(pos[1],pos[0]);


        cont++;*/
    }while(true);
    return aux;
}


void salva_grafo(MatrizAdj grafo, string nome){
    ofstream arquivo;

    arquivo.open("/home/anderson/Documentos/Aula_Grafos/salvamento/"+nome);
    int **matriz = grafo.getMatriz();
    if(arquivo.is_open()){
        arquivo<< grafo.getVertices() << endl;
        arquivo<< grafo.getDirigida() << endl;
        for (int i = 0; i < grafo.getVertices(); i++){
            for(int j = 0; j < grafo.getVertices(); j++){
                if(grafo.getDirigida()){
                    if(matriz[i][j] == 1)
                        arquivo<< i+1 << "," << j+1 << endl;
                }else{
                    if(matriz[i][j] == 1 && j>=i)
                        arquivo<< i+1 << "," << j+1 << endl;
                }
            }
        }
        system("cls");
    }else{
        cout<< "Erro ao salvar";
    }
}
