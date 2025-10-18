#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include "funcionario.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QLineEdit *nomeInput;
    QLineEdit *cpfInput;
    QLineEdit *funcaoInput;
    QPushButton *salvarBtn;
    QPushButton *listarBtn;
    QTableWidget *tabela;

public:
    MainWindow(QWidget *parent = nullptr);
    void atualizarTabela();

private slots:
    void salvarFuncionario();
    void listarFuncionarios();
};

#endif
