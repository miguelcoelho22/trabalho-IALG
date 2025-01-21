#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

struct series{

    char nomeSerie[30];
    int ano;
    float nota;
    string genero;
    char diretor[50];

};

int carregarDados(series*& serie, int qntdSeries){
    ifstream arquivoBinario("series.bin", ios::binary | ios::ate);    
    if(arquivoBinario){
        streamsize tamanho = arquivoBinario.tellg();// Calcula o número de elementos no arquivo binário
        arquivoBinario.seekg(0, ios::beg);// Volta para o início do arquivo

        arquivoBinario.read(reinterpret_cast<char *>(serie), tamanho);
        

        cout<<"Leitura binária realizada com sucesso!\n"<<endl;
    

    int tamanhoInicial = 40;
    int i = 0;

    int continuar = 1;

    while(continuar == 1 && i < qntdSeries){
        for (int contador = 0; contador < 40 && i < tamanhoInicial; contador++){

            
            cout << i+1 << " Nome: " << serie[i].nomeSerie << ", Ano: " << serie[i].ano 
             << ", Nota: " << serie[i].nota << ", Gênero: " << serie[i].genero 
             << ", Diretor: " << serie[i].diretor << endl;

            i++;

        }

        if(i >= qntdSeries){
            cout << "fim do arquivo" << endl;
            return 0;
        }

        cout << "Deseja continuar adicionando mais séries?" << endl;
        cout << "1: continuar" << endl << "2: parar" << endl;
        cin >> continuar;

        if (continuar == 1 && i == tamanhoInicial) {
            int novaCapacidade = tamanhoInicial + 10;
            series* novaSerie = new series[novaCapacidade];

            for(int j = 0; j < i; j++){
                strcpy(novaSerie[j].nomeSerie, serie[j].nomeSerie);
                novaSerie[j].ano = serie[j].ano;
                novaSerie[j].nota = serie[j].nota;
                novaSerie[j].genero = serie[j].genero;
                strcpy(novaSerie[j].diretor, serie[j].diretor);
            }

            delete[] serie;
            serie = novaSerie;
            tamanhoInicial = novaCapacidade;
        
        }  
    }
    }

    delete[] serie;
    arquivoBinario.close();
    return 0;
}   

void adicionarSerie(series*& serie, int qntdSeries){
    
    int continuar = 1;
    int tamanho = qntdSeries + 1;
    int contador = 0;
    string genero;
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
            serie[qntdSeries].genero = genero;

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

void mostrarUmPedaco(series*& serie){
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

void carregarDadosCsv(series*& serie){
    ifstream seriesCsv("series.csv");

    if(!seriesCsv){
        cout << "erro ao abrir o arquivo" << endl;
    }

    string linha;

    getline(seriesCsv, linha);

    int qntdSeries;

    seriesCsv >> qntdSeries;

    

    for (int i = 0; i < qntdSeries; i++){

        char lixo;
        seriesCsv.getline(serie[i].nomeSerie, 30, ',');

        seriesCsv >> serie[i].ano;

        seriesCsv >> lixo;

        seriesCsv >> serie[i].nota;

        seriesCsv >> lixo;

        getline(seriesCsv, serie[i].genero, ',');

        seriesCsv.getline(serie[i].diretor, 50);

        cout << i+1 << " Nome: " << serie[i].nomeSerie << ", Ano: " << serie[i].ano 
             << ", Nota: " << serie[i].nota << ", Gênero: " << serie[i].genero 
             << ", Diretor: " << serie[i].diretor << endl;
    }

}

void transformarCsvParaBinario(series*& serie){
    ifstream seriesCsv("series.csv");
    ofstream saidaBin("series.bin", ios::binary);

    if(!seriesCsv){
        cout << "arquivo nao encontrado" << endl;
    }
    string linha;

    getline(seriesCsv, linha);

    int qntdSeries;

    seriesCsv >> qntdSeries;

    for(int i = 0; i < qntdSeries; i++) {
        char lixo;
        seriesCsv.getline(serie[i].nomeSerie, 30, ',');

        seriesCsv >> serie[i].ano;

        seriesCsv >> lixo;

        seriesCsv >> serie[i].nota;

        seriesCsv >> lixo;

        getline(seriesCsv, serie[i].genero, ',');

        seriesCsv.getline(serie[i].diretor, 50);                  
    }
     for (int i = 0; i < qntdSeries; i++) {
        saidaBin.write(reinterpret_cast<const char*>(&serie[i]), sizeof(series) * qntdSeries);
    }

    saidaBin.close();
}

int main(){
    int qntdSeries = 100;
    series* serie = new series[qntdSeries];

    int escolha = 10;

    while(escolha != 0){
        cout << "1. Carregar dados do arquivo tipado" << endl;
        cout << "2. Adicionar série manualmente" << endl;
        cout << "3. mostrar um pedaço do arquivo" << endl;
        cout << "4. carregar dados do arquivo csv" << endl;
        cout << "5. carregar arquivo binario a partir do csv" << endl;
        cout << "0. sair" << endl;
        cin >> escolha;

        switch (escolha){
        case 0:
            cout << "saindo do programa..." << endl;
            break;
        case 1:
            carregarDados(serie, qntdSeries);
            break;
        case 2:
            adicionarSerie(serie, qntdSeries);
            break;
        case 3:
            mostrarUmPedaco(serie);
            break;
        case 4:
            carregarDadosCsv(serie);
            break;
        case 5:
            transformarCsvParaBinario(serie);
            break;
    }
}
}