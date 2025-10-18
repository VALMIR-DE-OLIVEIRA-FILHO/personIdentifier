#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <locale>
#include <sstream>
#include <iomanip>

using namespace std;

class Funcionario {
private:
    string nome;
    string cpf;
    string codigo;
    string funcao;

public:
    Funcionario() {}

    Funcionario(string n, string c, string cod, string f) {
        nome = n;
        cpf = c;
        codigo = cod;
        funcao = f;
    }

    string getNome() { return nome; }
    string getCPF() { return cpf; }
    string getCodigo() { return codigo; }
    string getFuncao() { return funcao; }

    void salvarEmArquivo() {
        ofstream arquivo("funcionarios.txt", ios::app);
        if (arquivo.is_open()) {
            arquivo << nome << ";" << cpf << ";" << codigo << ";" << funcao << endl;
            arquivo.close();
            cout << "\n✅ Funcionário salvo com sucesso!\n";
        } else {
            cerr << "❌ Erro ao abrir o arquivo para salvar!" << endl;
        }
    }

    void exibirInformacoes() {
        cout << left << setw(25) << nome
             << setw(15) << cpf
             << setw(10) << codigo
             << setw(20) << funcao << endl;
    }
};

// Função para pegar o último código usado no arquivo
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
        cout << "\n⚠️ Nenhum funcionário cadastrado ainda.\n";
        return;
    }

    string linha;
    cout << "\n📋 FUNCIONÁRIOS CADASTRADOS:\n";
    cout << "---------------------------------------------------------------------\n";
    cout << left << setw(25) << "NOME"
         << setw(15) << "CPF"
         << setw(10) << "CÓDIGO"
         << setw(20) << "FUNÇÃO" << endl;
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
    setlocale(LC_ALL, "pt_BR.UTF-8");
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int opcao;
    do {
        cout << "\n===== SISTEMA DE CADASTRO DE FUNCIONÁRIOS =====\n";
        cout << "1. Cadastrar novo funcionário\n";
        cout << "2. Listar funcionários\n";
        cout << "3. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;
        cin.ignore();

        if (opcao == 1) {
            string nome, cpf, funcao;

            cout << "Nome: ";
            getline(cin, nome);

            cout << "CPF: ";
            getline(cin, cpf);

            cout << "Função: ";
            getline(cin, funcao);

            // Gera o próximo código automaticamente
            int ultimo = obterUltimoCodigo();
            int novoCodigo = ultimo + 1;

            // Formata o código para 5 dígitos (ex: 00001)
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