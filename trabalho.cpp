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
    int ranking;

};

int carregarDados(ifstream& seriesCsv, int qntdSeries, series*& serie){
    int tamanho = 40;
    int i = 0;
    

    int continuar = 1;

    while(continuar == 1 && i < qntdSeries){
        for (int contador = 0; contador < 40 && i < tamanho; contador++){

            char lixo;
            seriesCsv.getline(serie[i].nomeSerie, 30, ',');

            seriesCsv >> serie[i].ano;

            seriesCsv >> lixo;

            seriesCsv >> serie[i].nota;

            seriesCsv >> lixo;

            getline(seriesCsv, serie[i].genero, ',');

            seriesCsv.getline(serie[i].diretor, 50);

            cout << i+1 << "Nome: " << serie[i].nomeSerie << ", Ano: " << serie[i].ano 
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
                novaSerie[j].ranking = serie[j].ranking;
            }

            delete[] serie;
            serie = novaSerie;
            tamanho = novaCapacidade;
        
        }  
    }

    return 0;
}

void adicionarSerie(ifstream& seriesCsv, int qntdSeries, series* serie){
    for(int i = 0; i < 100; i++){
        cout << i+1 << "Nome: " << serie[i].nomeSerie << ", Ano: " << serie[i].ano 
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

    int escolha = 10;

    series* serie = new series[40];

    while(escolha != 0){
        cout << "1. Carregar dados do arquivo" << endl;
        cout << "2. Adicionar série manualmente" << endl;
        cout << "0. sair" << endl;
        cin >> escolha;

        switch (escolha){
        case 1:
            carregarDados(seriesCsv, qntdSeries, serie);
            break;
        case 2:
            adicionarSerie(seriesCsv, qntdSeries, serie);
        default:
            cout << "Opção inválida. Encerrando o programa." << endl;
            break;
        }
    }
}