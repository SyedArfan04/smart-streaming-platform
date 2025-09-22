#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Movie {
    QString title;
    QString genre;
    QString mood;
    QString timeSlot;
    QString description;
    QString imagePath;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void recommendMovie();
    void surprisePick();

private:
    Ui::MainWindow *ui;
    QVector<Movie> movieDB;

    void populateMovieDB(); // Helper to fill the dataset
};

#endif // MAINWINDOW_H
