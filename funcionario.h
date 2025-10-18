#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <QString>
#include <QFile>
#include <QTextStream>

class Funcionario {
private:
    QString nome, cpf, codigo, funcao;

public:
    Funcionario() {}
    Funcionario(QString n, QString c, QString cod, QString f)
        : nome(n), cpf(c), codigo(cod), funcao(f) {}

    QString getNome() const { return nome; }
    QString getCpf() const { return cpf; }
    QString getCodigo() const { return codigo; }
    QString getFuncao() const { return funcao; }

    static int obterUltimoCodigo();
    void salvarEmArquivo() const;
    static QList<Funcionario> listarFuncionarios();
};

#endif
