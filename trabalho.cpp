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

int carregarDados(){
    int tamanho = 40;
    int i = 0;
    series* serie = new series[tamanho];
    int continuar = 1;

    ifstream seriesCsv("series.csv");

    if(!seriesCsv){
        cout << "erro ao abrir o arquivo" << endl;
        return 1;
    }

    string linha;

    getline(seriesCsv, linha);

    int qntdSeries;

    seriesCsv >> qntdSeries;

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

    delete[] serie;
    return 0;
}
    
int main(){
    int escolha;

    cout << "carregar dados: digite 1" << endl;  
    
    cin >> escolha;

    switch (escolha)
    {
    case 1:
        carregarDados();
        break;   
    default:
        cout << "Opção inválida. Encerrando o programa." << endl;
        break;
    }


}