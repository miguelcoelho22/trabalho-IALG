#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct series{

    char Nomeserie[30];
    int ano;
    float nota;
    string genero;
    char diretor[50];
    int ranking;

};

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
    
    series serie[qntdSeries];

    for(int i = 0; i < qntdSeries; i++){
        char lixo;
        seriesCsv.getline(serie[i].Nomeserie, 30, ',');

        seriesCsv >> serie[i].ano;

        seriesCsv >> lixo;

        seriesCsv >> serie[i].nota;

        seriesCsv >> lixo;

        getline(seriesCsv, serie[i].genero, ',');

        

        seriesCsv.getline(serie[i].diretor, 50);
        

        cout << "Nome: " << serie[i].Nomeserie << ", Ano: " << serie[i].ano 
             << ", Nota: " << serie[i].nota << ", Gênero: " << serie[i].genero 
             << ", Diretor: " << serie[i].diretor << endl;
    }

}