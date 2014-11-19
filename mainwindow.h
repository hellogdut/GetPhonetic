#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <translator.h>
#include <QMap>
#include <QVector>
#include <QFileDialog>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void getWordBytext();
    void timerEvent(QTimerEvent *);
public slots:
    void translateFinished(Words);
private slots:
    void on_pushButton_clicked();

private:
    int maxcount;
    int curcount;
    int lastcount;
    Ui::MainWindow *ui;
    Translator* translator;

    QMap<QString,QString> map;

    QMap<QString,int>     index_map;

    QMap<QString,QString> result;

    QVector<QString> words;

    QVector<bool> words_flag;

    QString filename;


    int timer;

};

#endif // MAINWINDOW_H
