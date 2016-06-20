#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDirIterator>
#include <QListWidget>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->play->setEnabled(false);
    ui->nowPlaying->setText("");
    player = new QMediaPlayer(this);
    connect(ui->verticalSlider,SIGNAL(sliderMoved(int)),player,SLOT(setVolume(int)));
    connect(player,SIGNAL(durationChanged(qint64)),ui->horizontalSlider,SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{   QString currentDirectory ="E:/Media";
    QFileDialog *myfileDialog= new QFileDialog;
    myfileDialog->setDirectory(currentDirectory);
    fileNames =myfileDialog->getOpenFileName(this, tr("Open File"),"/path/to/file/",tr("Mp3 Files (*.mp3)"));
    QString song = fileNames;
    song.replace(0,song.lastIndexOf("/")+1,"");
    song.replace(song.lastIndexOf("."),song.size()-song.lastIndexOf("."),"");
    ui->nowPlaying->setText(song);
        ui->play->setEnabled(true);

}



void MainWindow::on_pause_clicked()
{
    playbackPos = player->position();
    player->pause();
}

void MainWindow::on_stop_clicked()
{
    player->stop();
    playbackPos = 0;
}

void MainWindow::on_play_clicked()
{   if(player->state()== 1) {playbackPos = 0;}
    player->setMedia(QUrl::fromLocalFile(fileNames));
    player->setVolume(50);
    player->setPosition(playbackPos);
    player->play();
    //QDebug() << player->errorString();
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    player->setPosition(position);
}

void MainWindow::mediaChanged(const QMediaContent &media)
{
    player->stop();
    player->setMedia(media);

}

void MainWindow::on_actionOpen_triggered()
{
    QString currentDirectory ="E:/Media";
        QFileDialog *myfileDialog= new QFileDialog;
        myfileDialog->setDirectory(currentDirectory);
        fileNames =myfileDialog->getOpenFileName(this, tr("Open File"),"/path/to/file/",tr("Mp3 Files (*.mp3)"));
        QString song = fileNames;
        song.replace(0,song.lastIndexOf("/")+1,"");
        song.replace(song.lastIndexOf("."),song.size()-song.lastIndexOf("."),"");
        ui->nowPlaying->setText(song);
        ui->play->setEnabled(true);
        player->setMedia(QUrl::fromLocalFile(fileNames));
        player->setVolume(50);
        player->setPosition(playbackPos);
        player->play();
}

void MainWindow::on_actionOpen_Directory_triggered()
{
       QString selectedDirectory = QFileDialog::getExistingDirectory(0,"Caption",QString(),QFileDialog::ShowDirsOnly);
       QDirIterator it(selectedDirectory, QDirIterator::Subdirectories);
       while (it.hasNext()) {
           QString item = it.next();
           if(item.contains(".mp3")) {
               currentPlaylist.append(item);
               QString title = item;
               title.replace(0,title.lastIndexOf("/")+1,"");
               title.replace(title.lastIndexOf("."),title.size()-title.lastIndexOf("."),"");
               ui->listWidget->addItem(title);
           }
       }
                QString song = fileNames;
        song.replace(0,song.lastIndexOf("/")+1,"");
        song.replace(song.lastIndexOf("."),song.size()-song.lastIndexOf("."),"");
        ui->nowPlaying->setText(song);
        ui->play->setEnabled(true);
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    player->setMedia(QUrl::fromLocalFile(currentPlaylist[ui->listWidget->currentIndex().row()]));
    player->setVolume(50);
    player->setPosition(playbackPos);
    player->play();
    ui->nowPlaying->setText(ui->listWidget->currentItem()->text());
}
