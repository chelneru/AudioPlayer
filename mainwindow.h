#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QDebug>
#include <QVector>
#include <QListWidgetItem>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void on_pushButton_clicked();

    void on_pause_clicked();

    void on_stop_clicked();

    void on_play_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void mediaChanged(const QMediaContent &media);

    void on_actionOpen_triggered();

    void on_actionOpen_Directory_triggered();


    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QString fileNames;
    qint64 playbackPos = 0;
    QVector<QString> currentPlaylist;
};

#endif // MAINWINDOW_H
