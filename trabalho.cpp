#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Estrutura que armazena informações sobre uma série
struct series {
    char nomeSerie[30];  // Nome da série (string de até 30 caracteres)
    int ano;             // Ano de lançamento da série
    float nota;          // Nota da série
    char genero[50];     // Gênero da série (string de até 50 caracteres)
    char diretor[50];    // Diretor da série (string de até 50 caracteres)
};

// Função para carregar dados de um arquivo binário
int carregarDadosBinario(series*& serie, int& qntdSeries) {
    ifstream arquivoBinario("series.bin", ios::binary | ios::ate); // Abre o arquivo binário no final
    if (!arquivoBinario.is_open()) {
        cout << "Erro ao abrir o arquivo binário." << endl;
        return 1;
    }

    // Calcula o tamanho do arquivo e reposiciona o ponteiro para o início
    arquivoBinario.seekg(0, ios::beg);

    int tamanhoInicial = 40; // Tamanho inicial do vetor de séries
    serie = new series[tamanhoInicial]; // Aloca memória para o vetor

    // Lê os dados do arquivo binário para o vetor
    arquivoBinario.read(reinterpret_cast<char*>(serie), tamanhoInicial * sizeof(series));

    if (!arquivoBinario) {
        cout << "Erro na leitura do arquivo." << endl;
        delete[] serie; // Libera a memória alocada
        return 1;
    }

    cout << "Leitura binária realizada com sucesso!" << endl;

    int i = 0; // Contador de séries exibidas
    int continuar = 1; // Variável para controlar a exibição

    // Exibe as séries e permite expansão dinâmica do vetor
    while (continuar == 1 && i < qntdSeries) {
        // Exibe as séries carregadas
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

            int novasSeries = 10; // Quantidade de séries adicionais a serem carregadas
            int novaCapacidade = tamanhoInicial + novasSeries; // Nova capacidade do vetor

            // Realoca memória para o vetor expandido
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

            // Libera o vetor antigo e atualiza o ponteiro
            delete[] serie;
            serie = novaSerie;
            tamanhoInicial = novaCapacidade;
        }
    

    arquivoBinario.close(); // Fecha o arquivo binário
    return 0;
}

// Função para listar todas as séries
void listarSeries(series* serie, int qntdSeries) {
    for (int i = 0; i < qntdSeries; i++) {
        cout << i + 1 << " Nome: " << serie[i].nomeSerie << ", Ano: " << serie[i].ano
             << ", Nota: " << serie[i].nota << ", Gênero: " << serie[i].genero
             << ", Diretor: " << serie[i].diretor << endl;
    }
}

// Função para adicionar uma nova série
void adicionarSerie(series*& serie, int& qntdSeries) {
    int continuar = 1;

    while (continuar == 1) {
        // Realoca memória para adicionar mais uma série
        int novoTamanho = qntdSeries + 1;
        series* redimensionamento = new series[novoTamanho];

        // Copia as séries antigas para o novo vetor
        for (int i = 0; i < qntdSeries; i++) {
            redimensionamento[i] = serie[i];
        }

        delete[] serie; // Libera o vetor antigo
        serie = redimensionamento; // Atualiza o ponteiro

        cin.ignore(); // Limpa buffer antes de usar cin.getline()

        // Solicita os dados da nova série
        cout << "Digite o nome da série: ";
        cin.getline(serie[qntdSeries].nomeSerie, 30);

        cout << "Digite o ano: ";
        cin >> serie[qntdSeries].ano;
        cin.ignore(); // Limpa buffer após cin >>

        cout << "Digite a nota: ";
        cin >> serie[qntdSeries].nota;
        cin.ignore(); // Limpa buffer após cin >>

        cout << "Digite o gênero: ";
        cin.getline(serie[qntdSeries].genero, 50);

        cout << "Digite o diretor: ";
        cin.getline(serie[qntdSeries].diretor, 50);

        qntdSeries++; // Incrementa a quantidade de séries

        // Pergunta se o usuário deseja continuar
        cout << "Deseja continuar?" << endl;
        cout << "1: continuar" << endl;
        cout << "2: parar" << endl;
        cin >> continuar;
        cin.ignore(); // Limpa o buffer após entrada numérica
    }

    // Exibe todas as séries após a adição
    for (int i = 0; i < qntdSeries; i++) {
        cout << i + 1 << " - Nome: " << serie[i].nomeSerie
             << ", Ano: " << serie[i].ano
             << ", Nota: " << serie[i].nota
             << ", Gênero: " << serie[i].genero
             << ", Diretor: " << serie[i].diretor << endl;
    }
}

// Função para exibir um intervalo de séries
void mostrarUmPedaco(series*& serie, int qntdSeries) {
    int inicio, termino;

    cout << "Digite o número da série que você deseja começar: " << endl;
    cin >> inicio;
    cout << "Digite o final: " << endl;
    cin >> termino;

    for (int i = inicio - 1; i < termino; i++) {
        cout << i + 1 << " Nome: " << serie[i].nomeSerie << ", Ano: " << serie[i].ano
             << ", Nota: " << serie[i].nota << ", Gênero: " << serie[i].genero
             << ", Diretor: " << serie[i].diretor << endl;
    }
}

// Função para carregar dados de um arquivo CSV
void carregarDadosCsv(series*& serie, int qntdSeries) {
    ifstream seriesCsv("series.csv");

    if (!seriesCsv) {
        cout << "Erro ao abrir o arquivo" << endl;
    }

    string linha;
    getline(seriesCsv, linha); // Ignora o cabeçalho

    seriesCsv >> qntdSeries; // Lê a quantidade de séries

    for (int i = 0; i < qntdSeries; i++) {
        char lixo;
        seriesCsv.getline(serie[i].nomeSerie, 30, ','); // Lê o nome da série
        seriesCsv >> serie[i].ano; // Lê o ano
        seriesCsv >> lixo; // Ignora a vírgula
        seriesCsv >> serie[i].nota; // Lê a nota
        seriesCsv >> lixo; // Ignora a vírgula
        seriesCsv.getline(serie[i].genero, 50, ','); // Lê o gênero
        seriesCsv.getline(serie[i].diretor, 50); // Lê o diretor
    }

    listarSeries(serie, qntdSeries); // Exibe as séries carregadas
}

// Função para transformar um arquivo CSV em binário
void transformarCsvParaBinario(series*& serie, int& qntdSeries) {
    ifstream seriesCsv("series.csv");
    ofstream saidaBin("series.bin", ios::binary);

    if (!seriesCsv) {
        cout << "Arquivo não encontrado" << endl;
    }

    string linha;
    getline(seriesCsv, linha); // Ignora o cabeçalho

    seriesCsv >> qntdSeries; // Lê a quantidade de séries

    for (int i = 0; i < qntdSeries; i++) {
        char lixo;
        seriesCsv.getline(serie[i].nomeSerie, 30, ','); // Lê o nome da série
        seriesCsv >> serie[i].ano; // Lê o ano
        seriesCsv >> lixo; // Ignora a vírgula
        seriesCsv >> serie[i].nota; // Lê a nota
        seriesCsv >> lixo; // Ignora a vírgula
        seriesCsv.getline(serie[i].genero, 50, ','); // Lê o gênero
        seriesCsv.getline(serie[i].diretor, 50); // Lê o diretor
    }

    // Escreve os dados no arquivo binário
    for (int i = 0; i < qntdSeries; i++) {
        saidaBin.write(reinterpret_cast<const char*>(&serie[i]), sizeof(series) * qntdSeries);
    }

    saidaBin.close(); // Fecha o arquivo binário
}

// Função para ordenar séries por ano usando Merge Sort
void mergePorAno(series* serie, int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    series* esquerda = new series[n1];
    series* direita = new series[n2];

    for (int i = 0; i < n1; i++) {
        esquerda[i] = serie[inicio + i];
    }

    for (int j = 0; j < n2; j++) {
        direita[j] = serie[meio + 1 + j];
    }

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        if (esquerda[i].ano <= direita[j].ano) {
            serie[k] = esquerda[i];
            i++;
        } else {
            serie[k] = direita[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        serie[k] = esquerda[i];
        i++;
        k++;
    }

    while (j < n2) {
        serie[k] = direita[j];
        j++;
        k++;
    }

    delete[] esquerda;
    delete[] direita;
}

void mergeSortPorAno(series*& serie, int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        mergeSortPorAno(serie, inicio, meio);
        mergeSortPorAno(serie, meio + 1, fim);
        mergePorAno(serie, inicio, meio, fim);
    }
}

// Função para ordenar séries por nome usando Merge Sort
void mergePorNome(series* serie, int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    series* esquerda = new series[n1];
    series* direita = new series[n2];

    for (int i = 0; i < n1; i++) {
        esquerda[i] = serie[inicio + i];
    }

    for (int j = 0; j < n2; j++) {
        direita[j] = serie[meio + 1 + j];
    }

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        if (strcmp(esquerda[i].nomeSerie, direita[j].nomeSerie) <= 0) {
            serie[k] = esquerda[i];
            i++;
        } else {
            serie[k] = direita[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        serie[k] = esquerda[i];
        i++;
        k++;
    }

    while (j < n2) {
        serie[k] = direita[j];
        j++;
        k++;
    }

    delete[] esquerda;
    delete[] direita;
}

void mergeSortPorNome(series*& serie, int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        mergeSortPorNome(serie, inicio, meio);
        mergeSortPorNome(serie, meio + 1, fim);
        mergePorNome(serie, inicio, meio, fim);
    }
}

// Função para buscar uma série por nome usando busca binária
int BuscaBinariaRecursivaPorNome(series*& series, int inicio, int fim, char* nomeSerie) {
    if (inicio > fim) {
        cout << "Série não encontrada." << endl;
        return -1;
    }

    int meio = inicio + (fim - inicio) / 2;

    if (strcmp(series[meio].nomeSerie, nomeSerie) == 0) {
        cout << " Nome: " << series[meio].nomeSerie << ", Ano: " << series[meio].ano
             << ", Nota: " << series[meio].nota << ", Gênero: " << series[meio].genero
             << ", Diretor: " << series[meio].diretor << endl;
        return meio;
    } else if (strcmp(series[meio].nomeSerie, nomeSerie) > 0) {
        return BuscaBinariaRecursivaPorNome(series, inicio, meio - 1, nomeSerie);
    } else {
        return BuscaBinariaRecursivaPorNome(series, meio + 1, fim, nomeSerie);
    }
}

// Função para salvar as séries em um arquivo CSV
void salvarEmCsv(series* serie, int qntdSeries) {
    ofstream saidaCsv("series.csv");

    saidaCsv << "Ranking,Nome,Ano,Nota,Gênero,Diretor" << endl << qntdSeries << endl;

    for (int i = 0; i < qntdSeries; i++) {
        saidaCsv << serie[i].nomeSerie << "," << serie[i].ano
                 << "," << serie[i].nota << "," << serie[i].genero
                 << "," << serie[i].diretor << endl;
    }
}

// Função para salvar as séries em um arquivo binário
void salvarEmBinario(series* serie, int qntdSeries) {
    ofstream saidaBin("series.bin", ios::binary);

     if (!saidaBin.is_open()) {
        cerr << "Erro ao abrir o arquivo para escrita." << endl;
    }

    for (int i = 0; i < qntdSeries; i++) {
        saidaBin.write(reinterpret_cast<const char*>(&serie[i]), sizeof(series));
    }
    
     if (!saidaBin) {
            cerr << "Erro ao escrever no arquivo." << endl;
            saidaBin.close();
            return;
        }
        
    saidaBin.close();
}

// Função para remover uma série
void removerSerie(series*& serie, int& qntdSeries) {
    char* nome = new char[30];
    cout << "Digite o nome da série que deseja remover: " << endl;
    cin >> nome;

    mergeSortPorNome(serie, 0, qntdSeries - 1); // Ordena as séries por nome
    int posicao = BuscaBinariaRecursivaPorNome(serie, 0, qntdSeries - 1, nome); // Busca a série

    if (posicao == -1) {
        cout << "Série não encontrada." << endl;
    }

    // Remove a série do vetor
    for (int i = posicao; i < qntdSeries - 1; i++) {
        serie[i] = serie[i + 1];
    }

    qntdSeries--; // Atualiza a quantidade de séries
    series* novoVetor = new series[qntdSeries]; // Cria um novo vetor com tamanho reduzido

    // Copia as séries para o novo vetor
    for (int i = 0; i < qntdSeries; i++) {
        novoVetor[i] = serie[i];
    }

    delete[] serie; // Libera o vetor antigo
    serie = novoVetor; // Atualiza o ponteiro

    cout << "Série removida com sucesso!" << endl;
}

// Função principal
int main() {
    char* nomeSerie = new char[30];
    int qntdSeries = 100;
    series* serie = new series[qntdSeries];

    int escolha = 10;

    cout << "Escolha uma das opções para carregar o arquivo:" << endl;
    cout << "1. Carregar dados do arquivo binário" << endl;
    cout << "2. Carregar dados do arquivo CSV" << endl;
    cout << "3. Transformar arquivo CSV em binário" << endl;
    cin >> escolha;

    switch (escolha) {
        case 0:
            cout << "Saindo do programa..." << endl;
            break;
        case 1:
            carregarDadosBinario(serie, qntdSeries);
            break;
        case 2:
            carregarDadosCsv(serie, qntdSeries);
            break;
        case 3:
            transformarCsvParaBinario(serie, qntdSeries);
            listarSeries(serie, qntdSeries);
            break;
    }

    while (escolha != 0) {
        cout << "1. Adicionar série manualmente" << endl;
        cout << "2. Mostrar um pedaço do arquivo" << endl;
        cout << "3. Ordenação por ano" << endl;
        cout << "4. Ordenação por nome" << endl;
        cout << "5. Busca por nome" << endl;
        cout << "6. Listar séries" << endl;
        cout << "7. Salvar em CSV" << endl;
        cout << "8. Remover série" << endl;
        cout << "0. Sair" << endl;

        cin >> escolha;

        switch (escolha) {
            case 0:
                cout << "Saindo do programa..." << endl;
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
                mergeSortPorNome(serie, 0, qntdSeries - 1);
                listarSeries(serie, qntdSeries);
                break;
            case 5:
                cout << "Digite o nome da série: " << endl;
                cin >> nomeSerie;
                mergeSortPorNome(serie, 0, qntdSeries - 1);
                BuscaBinariaRecursivaPorNome(serie, 0, qntdSeries - 1, nomeSerie);
                break;
            case 6:
                listarSeries(serie, qntdSeries);
                break;
            case 7:
                salvarEmCsv(serie, qntdSeries);
                cout << "Arquivo CSV salvo com sucesso!" << endl;
                break;
            case 8:
                removerSerie(serie, qntdSeries);
                break;
        }
    }

    cout << "Deseja salvar as alterações?" << endl;
    cout << "1: Salvar" << endl << "2: Não salvar" << endl;
    cin >> escolha;

    if (escolha == 1) {
        salvarEmBinario(serie, qntdSeries);
        cout << "Arquivo binário salvo com sucesso!" << endl;
    }

    delete[] serie; // Libera a memória alocada
    return 0;
}