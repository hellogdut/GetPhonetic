#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QFile>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    translator = new Translator();
    connect(translator,SIGNAL(translateFinished(Words)),this,SLOT(translateFinished(Words)));
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getWordBytext()
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
    QTextStream out(&file);

    QString line;
    int j = 0;
    do {

        line = out.readLine();
        int i = line.indexOf(" ");
        QString word = line.mid(0,i).toLower();
        QString explain = line.mid(i+1,line.length() - i - 1);
        qDebug() << word << " " << explain << endl;
        map.insert(word,explain);
        index_map.insert(word,j);
        ++j;
        words.push_back(word);
        words_flag.push_back(false);
        //ui->textEdit->insertPlainText(word + " " + explain + "\n");
    } while (!line.isNull());
    maxcount = words.size();
    curcount = 0;
    lastcount = 0;
    foreach(QString word,words) {
        translator = new Translator();
        connect(translator,SIGNAL(translateFinished(Words)),this,SLOT(translateFinished(Words)));
        translator->translateWord(word);
    }
    timer = startTimer(2000);
}

void MainWindow::timerEvent(QTimerEvent *)
{
    if(lastcount == curcount) {
        killTimer(timer);
        for(int i = 0;i < maxcount;++i) {
            if(words_flag[i] == false) {
                ui->textEdit_2->insertPlainText(words[i] + '\n');
            }
            else
            {
                QString str = result[words[i]];
                ui->textEdit->insertPlainText(str + "\n");
            }
        }
    }
    lastcount = curcount;
}

void MainWindow::translateFinished(Words word)
{

    qDebug() << "查到啦" << endl;
    int i = index_map[word.query];
    words_flag[i] = true;
    QString phonetic = word.phonetic;
    QString explain = map[word.query];
    result.insert(word.query,word.query + " " + "[" + phonetic  + "]" + "  " + explain);
    ++curcount;
}

void MainWindow::on_pushButton_clicked()
{
    filename = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "txt", tr("Image Files (*.txt)"));
    qDebug() << filename ;
    getWordBytext();
}
