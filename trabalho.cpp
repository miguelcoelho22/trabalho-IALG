#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

struct series{

    char nomeSerie[30];
    int ano;
    float nota;
    char genero[50];
    char diretor[50];

};

int carregarDadosBinario(series*& serie, int& qntdSeries) {
    ifstream arquivoBinario("series.bin", ios::binary | ios::ate);
    if (!arquivoBinario.is_open()) {
        cout << "Erro ao abrir o arquivo binário." << endl;
        return 1;
    }

    // Calcula o número total de séries no arquivo binário
    streamsize tamanho = arquivoBinario.tellg();
    arquivoBinario.seekg(0, ios::beg);

    int tamanhoInicial = 40;
    serie = new series[tamanhoInicial];

    // Lê os dados do arquivo binário até a quantidade inicial
    arquivoBinario.read(reinterpret_cast<char*>(serie), tamanhoInicial * sizeof(series));

    if (!arquivoBinario) {
        cout << "Erro na leitura do arquivo." << endl;
        delete[] serie;
        return 1;
    }

    cout << "Leitura binária realizada com sucesso!" << endl;

    int i = 0; // Número de séries exibidas
    int continuar = 1;

    // Exibição de dados e expansão dinâmica
    while (continuar == 1 && i < qntdSeries) {
        // Exibe as séries atualmente carregadas
        for (int contador = 0; contador < 40 && i < tamanhoInicial && i < qntdSeries; contador++) {
            cout << i + 1 << " Nome: " << serie[i].nomeSerie << ", Ano: " << serie[i].ano
                 << ", Nota: " << serie[i].nota << ", Gênero: " << serie[i].genero
                 << ", Diretor: " << serie[i].diretor << endl;
            i++;
        }

       
        // Verifica se todas as séries foram exibidas
        if (i >= qntdSeries) {
            cout << "Fim do arquivo." << endl;
            continuar = 0;
        }

        // Pergunta se o usuário deseja continuar
        cout << "Deseja continuar adicionando mais séries?" << endl;
        cout << "1: continuar" << endl << "2: parar" << endl;

        cin >> continuar;

        // Expande o vetor para exibir mais séries, caso o usuário queira
        if (continuar == 1) {

            int novasSeries = 10;
        
            // Calcula a nova capacidade do vetor
            int novaCapacidade = tamanhoInicial + novasSeries;

            // Realoca a memória para o vetor expandido
            series* novaSerie = new series[novaCapacidade];

            // Copia as séries antigas para o novo vetor
            for (int j = 0; j < i; j++) {
                novaSerie[j] = serie[j];
            }
            // Lê as próximas séries do arquivo binário
            arquivoBinario.read(reinterpret_cast<char*>(novaSerie + i), novasSeries * sizeof(series));
            
            if (!arquivoBinario) {
                cout << "Erro na leitura adicional do arquivo." << endl;
                delete[] novaSerie;
                delete[] serie;
                return 1;
            }

            // Deleta o vetor antigo e aponta para o novo vetor expandido
            delete[] serie;
            serie = novaSerie;
            tamanhoInicial = novaCapacidade;
        }
    }

    arquivoBinario.close();
    return 0;
}

void listarSeries(series* serie, int qntdSeries){
    for(int i = 0; i < qntdSeries; i++){
        cout << i+1 << " Nome: " << serie[i].nomeSerie << ", Ano: " << serie[i].ano 
             << ", Nota: " << serie[i].nota << ", Gênero: " << serie[i].genero 
             << ", Diretor: " << serie[i].diretor << endl;
    }
}


void adicionarSerie(series*& serie, int& qntdSeries){
    
    int continuar = 1;
    int tamanho = qntdSeries + 1;
    int contador = 0;

    char genero[50];
    int ano;
    float nota;
    char nome[30];
    char diretor[50];

        while(continuar == 1){
             if(tamanho = qntdSeries){
                int novoTamanho = qntdSeries + 1;
                series* redimensionamento = new series[novoTamanho];

                for(int i = 0; i < qntdSeries; i++){
                    redimensionamento[i] = serie[i];
                }

                delete[] serie;
                serie = redimensionamento;

                tamanho = novoTamanho;
             }

            cout << "digite o nome da serie:";
            cin >> nome;
            strcpy(serie[qntdSeries].nomeSerie, nome);

            cout << "digite o ano: ";
            cin >> ano;
            serie[qntdSeries].ano = ano;

            cout << "digite a nota: ";
            cin >> nota;
            serie[qntdSeries].nota = nota;

            cout << "digite o genero: ";
            cin >> genero;
            strcpy(serie[qntdSeries].genero, genero);

            cout << "digite o diretor: ";
            cin >> diretor;
            strcpy(serie[qntdSeries++].diretor, diretor);

            cout << "deseja continuar?" << endl;
            cout << "1: continuar" << endl;
            cout << "2: parar" << endl;
            cin >> continuar;
        }

    for(int i = 0; i < tamanho; i++){
        cout << i+1 << " Nome: " << serie[i].nomeSerie << ", Ano: " << serie[i].ano 
             << ", Nota: " << serie[i].nota << ", Gênero: " << serie[i].genero 
             << ", Diretor: " << serie[i].diretor << endl;
    }

    delete[] serie;
}

void mostrarUmPedaco(series*& serie, int qntdSeries){
    int inicio, termino;

    cout << "digite o numero da serie que voce deseja começar: " << endl;
    cin >> inicio;
    cout << "digite o final: " << endl;
    cin >> termino;

    for(int i = inicio-1; i < termino; i++){
        cout << i+1 << " Nome: " << serie[i].nomeSerie << ", Ano: " << serie[i].ano 
             << ", Nota: " << serie[i].nota << ", Gênero: " << serie[i].genero 
             << ", Diretor: " << serie[i].diretor << endl;
    }
}

void carregarDadosCsv(series*& serie, int qntdSeries){
    ifstream seriesCsv("series.csv");

    if(!seriesCsv){
        cout << "erro ao abrir o arquivo" << endl;
    }

    string linha;

    getline(seriesCsv, linha);

    seriesCsv >> qntdSeries;

    

    for (int i = 0; i < qntdSeries; i++){

        char lixo;
        seriesCsv.getline(serie[i].nomeSerie, 30, ',');

        seriesCsv >> serie[i].ano;

        seriesCsv >> lixo;

        seriesCsv >> serie[i].nota;

        seriesCsv >> lixo;

        seriesCsv.getline(serie[i].genero, 50, ',');

        seriesCsv.getline(serie[i].diretor, 50);
    }

    listarSeries(serie, qntdSeries);

}

void transformarCsvParaBinario(series*& serie, int &qntdSeries){
    ifstream seriesCsv("series.csv");
    ofstream saidaBin("series.bin", ios::binary);

    if(!seriesCsv){
        cout << "arquivo nao encontrado" << endl;
    }
    string linha;

    getline(seriesCsv, linha);

    seriesCsv >> qntdSeries;

    for(int i = 0; i < qntdSeries; i++) {
        char lixo;
        seriesCsv.getline(serie[i].nomeSerie, 30, ',');

        seriesCsv >> serie[i].ano;

        seriesCsv >> lixo;

        seriesCsv >> serie[i].nota;

        seriesCsv >> lixo;

        seriesCsv.getline(serie[i].genero, 50, ',');

        seriesCsv.getline(serie[i].diretor, 50);                  
    }
     for (int i = 0; i < qntdSeries; i++) {
        saidaBin.write(reinterpret_cast<const char*>(&serie[i]), sizeof(series) * qntdSeries);
    }

    saidaBin.close();
}

void mergePorAno(series* serie, int inicio, int meio, int fim){
    int n1 = meio - inicio+1;
    int n2 = fim - meio; 

    series* esquerda = new series[n1];
    series* direita = new series[n2];

    for(int i = 0; i < n1; i++){
        esquerda[i] = serie[inicio + i];}

    for(int j = 0; j < n2; j++){
        direita[j] = serie[meio + 1 + j];}

     int i = 0, j = 0, k = inicio;

    while(i < n1 && j < n2){
        if(esquerda[i].ano <= direita[j].ano){
            serie[k] = esquerda[i];
            i++;
        } 
        else{
            serie[k] = direita[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        serie[k] = esquerda[i];
        i++;
        k++;
    }

    while(j < n2){
        serie[k] = direita[j];
        j++;
        k++;
    }

    delete[] esquerda;
    delete[] direita;
}


void mergeSortPorAno(series*& serie, int inicio,int fim) {
    if(inicio < fim){
        int meio = inicio + (fim - inicio) / 2;

        mergeSortPorAno(serie, inicio, meio);
        mergeSortPorAno(serie, meio + 1, fim);

        mergePorAno(serie, inicio, meio, fim);
    }
}

void mergePorNome(series* serie, int inicio, int meio, int fim){
    int n1 = meio - inicio+1;
    int n2 = fim - meio; 

    series* esquerda = new series[n1];
    series* direita = new series[n2];

    for(int i = 0; i < n1; i++){
        esquerda[i] = serie[inicio + i];}

    for(int j = 0; j < n2; j++){
        direita[j] = serie[meio + 1 + j];}

     int i = 0, j = 0, k = inicio;

    while(i < n1 && j < n2){
        if(strcmp(esquerda[i].nomeSerie, direita[j].nomeSerie) <= 0){
            serie[k] = esquerda[i];
            i++;
        } 
        else{
            serie[k] = direita[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        serie[k] = esquerda[i];
        i++;
        k++;
    }

    while(j < n2){
        serie[k] = direita[j];
        j++;
        k++;
    }

    delete[] esquerda;
    delete[] direita;
}


void mergeSortPorNome(series*& serie, int inicio,int fim) {
    if(inicio < fim){
        int meio = inicio + (fim - inicio) / 2;

        mergeSortPorNome(serie, inicio, meio);
        mergeSortPorNome(serie, meio + 1, fim);

        mergePorNome(serie, inicio, meio, fim);
    }
}

int BuscaBinariaRecursivaPorNome(series*& series, int inicio, int fim ,char* nomeSerie) {
   
    if(inicio > fim){
        cout << "inicio maior que o fim" << endl;
        return -1;
    }

    int meio = inicio + (fim - inicio) / 2;

    if (strcmp(series[meio].nomeSerie, nomeSerie) == 0) {
        cout << meio << endl;
        cout << " Nome: " << series[meio].nomeSerie << ", Ano: " << series[meio].ano 
             << ", Nota: " << series[meio].nota << ", Gênero: " << series[meio].genero 
             << ", Diretor: " << series[meio].diretor << endl;
    }

    else if (strcmp(series[meio].nomeSerie, nomeSerie) > 0){
        return BuscaBinariaRecursivaPorNome(series, inicio, meio - 1, nomeSerie);
    }
    else{
        return BuscaBinariaRecursivaPorNome(series, meio + 1, fim, nomeSerie);
    }
    
    }
void salvarEmCsv(series* serie, int qntdSeries){
    ofstream saidaCsv("series.csv");

    saidaCsv << "Ranking,Nome,Ano,Nota,Gênero,Diretor" << endl << qntdSeries << endl;

    for(int i = 0; i < qntdSeries; i++){
        saidaCsv << serie[i].nomeSerie << "," << serie[i].ano 
             << "," << serie[i].nota << "," << serie[i].genero 
             << "," << serie[i].diretor << endl;
    }

}

void salvarEmBinario(series* serie, int qntdSeries){
    ofstream saidaBin("series.bin");

        saidaBin.write(reinterpret_cast<const char*>(serie), sizeof(series) * qntdSeries);
        saidaBin.close();

}
int main(){

    char* nomeSerie = new char[30];
    int qntdSeries = 100;
    series* serie = new series[qntdSeries];

    int escolha = 10;

    cout << "escolha uma das opçoes para carregar o arquivo" << endl;
        cout << "1. Carregar dados do arquivo tipado" << endl;
        cout << "2. carregar dados do arquivo csv" << endl;
        cout << "3. carregar arquivo binario a partir do csv" << endl;
        cin >> escolha;
        switch (escolha){
        case 0:
            cout << "saindo do programa..." << endl;
            break;
        case 1:
            carregarDadosBinario(serie, qntdSeries);
            break;
        case 2:
            carregarDadosCsv(serie, qntdSeries);
            break;
        case 3:
            transformarCsvParaBinario(serie, qntdSeries);
            break;
        }
    while(escolha != 0){
        cout << "1. Adicionar série manualmente" << endl;
        cout << "2. mostrar um pedaço do arquivo" << endl;
        cout << "3. ordenacao por ano" << endl;
        cout << "4. ordenaçao por nome" << endl;
        cout << "5. busca por Nome" << endl;
        cout << "6. listar series" << endl;
        cout << "7. salvar em Csv" << endl;
        cout << "0. sair" << endl;

        cin >> escolha;

        switch (escolha){
        case 0:
            cout << "saindo do programa..." << endl;
            break;
        case 1:
            adicionarSerie(serie, qntdSeries);
            break;
        case 2:
            mostrarUmPedaco(serie, qntdSeries);
            break;
        case 3:
            mergeSortPorAno(serie, 0, qntdSeries - 1);
            listarSeries(serie, qntdSeries);
            break;
        case 4:
            mergeSortPorNome(serie, 0, qntdSeries -1);
            listarSeries(serie,qntdSeries);
            break;
        case 5: 
            cout << "digite o nome da serie" << endl;
            cin >> nomeSerie;
            mergeSortPorNome(serie, 0, qntdSeries -1);
            BuscaBinariaRecursivaPorNome(serie, 0, qntdSeries - 1, nomeSerie);
           break;
        case 6:
            listarSeries(serie, qntdSeries);
            break;
        case 7:
            salvarEmCsv(serie, qntdSeries);
            cout << "arquivo Csv salvo com sucesso" << endl;
    }
}

    cout << "deseja salvar as alteraçoes?" << endl;
    cout << "1: salvar" << endl << "2: nao salvar" << endl;
    cin >> escolha;

    if(escolha == 1){
        salvarEmBinario(serie, qntdSeries);
        cout << "arquivo Bin salvo com sucesso" << endl;
    }
    
    //salvar -> sim -> binario com as alteraçoes
     //   -> nao -> mantem o arquivo binario sem altaraçoes

    delete[] serie;
}