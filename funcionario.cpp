#include "funcionario.h"
#include <QDebug>

void Funcionario::salvarEmArquivo() const {
    QFile arquivo("funcionarios.txt");
    if (arquivo.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&arquivo);
        out << nome << ";" << cpf << ";" << codigo << ";" << funcao << "\n";
        arquivo.close();
        qDebug() << "Funcionario salvo com sucesso!";
    } else {
        qDebug() << "Erro ao abrir o arquivo!";
    }
}

int Funcionario::obterUltimoCodigo() {
    QFile arquivo("funcionarios.txt");
    QString ultimaLinha;
    if (arquivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&arquivo);
        while (!in.atEnd()) {
            ultimaLinha = in.readLine();
        }
        arquivo.close();
    }

    if (!ultimaLinha.isEmpty()) {
        QStringList partes = ultimaLinha.split(';');
        if (partes.size() > 2)
            return partes[2].toInt();
    }
    return 0;
}

QList<Funcionario> Funcionario::listarFuncionarios() {
    QList<Funcionario> lista;
    QFile arquivo("funcionarios.txt");

    if (arquivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&arquivo);
        while (!in.atEnd()) {
            QString linha = in.readLine();
            QStringList partes = linha.split(';');
            if (partes.size() == 4) {
                lista.append(Funcionario(partes[0], partes[1], partes[2], partes[3]));
            }
        }
        arquivo.close();
    }

    return lista;
}
