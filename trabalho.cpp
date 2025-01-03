#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

struct series{

    char nomeSerie[30];
    int ano;
    float nota;
    string genero;
    char diretor[50];

};

int carregarDados(series*& serie, int qntdSeries){
    int tamanho = 40;
    int i = 0;

    int continuar = 1;

    while(continuar == 1 && i < qntdSeries){
        for (int contador = 0; contador < 40 && i < tamanho; contador++){

            
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

        if (continuar == 1 && i == tamanho) {
            int novaCapacidade = tamanho + 10;
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
            tamanho = novaCapacidade;
        
        }  
    }

    delete[] serie;
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
int main(){

    ifstream seriesCsv("series.csv");

    if(!seriesCsv){
        cout << "erro ao abrir o arquivo" << endl;
        return 1;
    }

    string linha;

    getline(seriesCsv, linha);

    int qntdSeries;

    seriesCsv >> qntdSeries;

    series* serie = new series[qntdSeries];
    for (int i = 0; i < qntdSeries; i++){
        char lixo;
        seriesCsv.getline(serie[i].nomeSerie, 30, ',');

        seriesCsv >> serie[i].ano;

        seriesCsv >> lixo;

        seriesCsv >> serie[i].nota;

        seriesCsv >> lixo;

        getline(seriesCsv, serie[i].genero, ',');

        seriesCsv.getline(serie[i].diretor, 50);
    }

    int escolha = 10;

    while(escolha != 0){
        cout << "1. Carregar dados do arquivo" << endl;
        cout << "2. Adicionar série manualmente" << endl;
        cout << "3. mostrar um pedaço do arquivo" << endl;
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
        }
    }
}