#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    // Campos de entrada
    QHBoxLayout *formLayout = new QHBoxLayout();
    nomeInput = new QLineEdit();
    cpfInput = new QLineEdit();
    funcaoInput = new QLineEdit();
    salvarBtn = new QPushButton("Salvar");
    listarBtn = new QPushButton("Listar Funcionários");

    formLayout->addWidget(new QLabel("Nome:"));
    formLayout->addWidget(nomeInput);
    formLayout->addWidget(new QLabel("CPF:"));
    formLayout->addWidget(cpfInput);
    formLayout->addWidget(new QLabel("Função:"));
    formLayout->addWidget(funcaoInput);
    formLayout->addWidget(salvarBtn);
    formLayout->addWidget(listarBtn);

    // Tabela
    tabela = new QTableWidget();
    tabela->setColumnCount(4);
    tabela->setHorizontalHeaderLabels({"Nome", "CPF", "Código", "Função"});
    tabela->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(tabela);
    setCentralWidget(central);

    connect(salvarBtn, &QPushButton::clicked, this, &MainWindow::salvarFuncionario);
    connect(listarBtn, &QPushButton::clicked, this, &MainWindow::listarFuncionarios);
}

void MainWindow::salvarFuncionario() {
    QString nome = nomeInput->text();
    QString cpf = cpfInput->text();
    QString funcao = funcaoInput->text();

    if (nome.isEmpty() || cpf.isEmpty() || funcao.isEmpty()) {
        QMessageBox::warning(this, "Erro", "Preencha todos os campos!");
        return;
    }

    int ultimo = Funcionario::obterUltimoCodigo();
    QString codigo = QString("%1").arg(ultimo + 1, 5, 10, QLatin1Char('0'));

    Funcionario f(nome, cpf, codigo, funcao);
    f.salvarEmArquivo();

    QMessageBox::information(this, "Sucesso", "Funcionário salvo com sucesso!");
    nomeInput->clear();
    cpfInput->clear();
    funcaoInput->clear();

    atualizarTabela();
}

void MainWindow::listarFuncionarios() {
    atualizarTabela();
}

void MainWindow::atualizarTabela() {
    QList<Funcionario> funcionarios = Funcionario::listarFuncionarios();
    tabela->setRowCount(funcionarios.size());

    for (int i = 0; i < funcionarios.size(); ++i) {
        tabela->setItem(i, 0, new QTableWidgetItem(funcionarios[i].getNome()));
        tabela->setItem(i, 1, new QTableWidgetItem(funcionarios[i].getCpf()));
        tabela->setItem(i, 2, new QTableWidgetItem(funcionarios[i].getCodigo()));
        tabela->setItem(i, 3, new QTableWidgetItem(funcionarios[i].getFuncao()));
    }
}
