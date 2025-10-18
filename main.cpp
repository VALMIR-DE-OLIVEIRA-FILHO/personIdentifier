#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.setWindowTitle("Sistema de Cadastro de Funcionários");
    w.resize(1000, 400);
    w.show();
    return app.exec();
}
