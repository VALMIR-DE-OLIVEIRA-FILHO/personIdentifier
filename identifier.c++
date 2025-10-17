#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>

using namespace std;

class Funcionario {
private:
    string nome, cpf, codigo, funcao;

public:
    Funcionario() {}
    Funcionario(string n, string c, string cod, string f) : nome(n), cpf(c), codigo(cod), funcao(f) {}

    string getCodigo() { return codigo; }

    void salvarEmArquivo() {
        ofstream arquivo("funcionarios.txt", ios::app);
        if (arquivo.is_open()) {
            arquivo << nome << ";" << cpf << ";" << codigo << ";" << funcao << endl;
            arquivo.close();
            cout << "\nFuncionario salvo com sucesso!\n";
        } else {
            cerr << "Erro ao abrir o arquivo!" << endl;
        }
    }

    void exibirInformacoes() {
        cout << left << setw(25) << nome
             << setw(15) << cpf
             << setw(10) << codigo
             << setw(20) << funcao << endl;
    }
};

int obterUltimoCodigo() {
    ifstream arquivo("funcionarios.txt");
    string linha, ultimoCodigo = "00000";

    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string nome, cpf, codigo, funcao;
        getline(ss, nome, ';');
        getline(ss, cpf, ';');
        getline(ss, codigo, ';');
        getline(ss, funcao, ';');
        if (!codigo.empty()) ultimoCodigo = codigo;
    }

    arquivo.close();
    return stoi(ultimoCodigo);
}

void listarFuncionarios() {
    ifstream arquivo("funcionarios.txt");
    if (!arquivo.is_open()) {
        cout << "\nNenhum funcionario cadastrado ainda.\n";
        return;
    }

    string linha;
    cout << "\nFUNCIONARIOS CADASTRADOS:\n";
    cout << "---------------------------------------------------------------------\n";
    cout << left << setw(25) << "NOME"
         << setw(15) << "CPF"
         << setw(10) << "CODIGO"
         << setw(20) << "FUNCAO" << endl;
    cout << "---------------------------------------------------------------------\n";

    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string nome, cpf, codigo, funcao;
        getline(ss, nome, ';');
        getline(ss, cpf, ';');
        getline(ss, codigo, ';');
        getline(ss, funcao, ';');

        Funcionario f(nome, cpf, codigo, funcao);
        f.exibirInformacoes();
    }

    cout << "---------------------------------------------------------------------\n";
    arquivo.close();
}

int main() {
    int opcao;
    do {
        cout << "\n===== SISTEMA DE CADASTRO DE FUNCIONARIOS =====\n";
        cout << "1. Cadastrar novo funcionario\n";
        cout << "2. Listar funcionarios\n";
        cout << "3. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opcao == 1) {
            string nome, cpf, funcao;

            cout << "Nome: ";
            getline(cin, nome);
            cout << "CPF: ";
            getline(cin, cpf);
            cout << "Funcao: ";
            getline(cin, funcao);

            int ultimo = obterUltimoCodigo();
            int novoCodigo = ultimo + 1;

            ostringstream oss;
            oss << setw(5) << setfill('0') << novoCodigo;
            string codigo = oss.str();

            Funcionario f(nome, cpf, codigo, funcao);
            f.salvarEmArquivo();
        }
        else if (opcao == 2) {
            listarFuncionarios();
        }

    } while (opcao != 3);

    cout << "\nPrograma encerrado.\n";
    return 0;
}
