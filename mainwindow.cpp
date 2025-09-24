#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Populate dropdowns
    ui->genreComboBox->addItems({"Action", "Romance", "Sci-Fi", "Comedy", "Horror"});
    ui->moodComboBox->addItems({"Chill", "Excited", "Emotional", "Curious"});
    ui->timeComboBox->addItems({"Morning", "Evening", "Late Night"});

    // Fill movie database
    populateMovieDB();

    // Connect buttons
    connect(ui->recommendButton, &QPushButton::clicked, this, &MainWindow::recommendMovie);
    connect(ui->surpriseButton, &QPushButton::clicked, this, &MainWindow::surprisePick);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateMovieDB() {

    movieDB = {
        {"Interstellar", "Sci-Fi", "Curious", "Evening", "A visually stunning journey through space and time.", ":/images/images/interstellar.png", "https://youtu.be/zSWdZVtXT7E" },
        {"The Notebook", "Romance", "Emotional", "Late Night", "A heartfelt love story that spans decades.", ":/images/images/thenotebook.jpg", "https://youtu.be/BjJcYdEOI0k"},
        {"John Wick", "Action", "Excited", "Late Night", "A relentless assassin seeks revenge with style.", ":/images/images/johnwick.png", "https://youtu.be/qEVUtrk8_B4"},
        {"Inside Out", "Comedy", "Chill", "Morning", "An animated dive into the emotions of a young girl.", ":/images/images/insideout.jpg", "https://youtu.be/BjJcYdEOI0k"},
        {"Parasite", "Thriller", "Curious", "Evening", "A gripping tale of class conflict and deception.", ":/images/images/parasite.png", "https://youtu.be/5xH0HfJHsaY"},
        {"Soul", "Animation", "Chill", "Morning", "A jazz musician discovers the meaning of life.", ":/images/images/soul.jpg", "https://youtu.be/xOsLIiBStEs"},
        {"A Quiet Place", "Horror", "Excited", "Late Night", "Survival in silence against deadly creatures.", ":/images/images/aquietplace.png", "https://youtu.be/WR7cc5t7tv8"},
        {"La La Land", "Romance", "Emotional", "Evening", "A musical journey of love and ambition.", ":/images/images/lalaland.png", "https://youtu.be/0pdqf4P9MB8"},
        {"The Martian", "Sci-Fi", "Curious", "Morning", "An astronaut survives alone on Mars using science.", ":/images/images/themartian.jpg", "https://youtu.be/Ue4PCI0NamI"},
        {"Zootopia", "Comedy", "Chill", "Evening", "A bunny cop solves a mystery in a city of animals.", ":/images/images/zootopia.png", "https://youtu.be/Y0c3nKWhlIA"}
    };
}

void MainWindow::recommendMovie() {
    QString genre = ui->genreComboBox->currentText();
    QString mood = ui->moodComboBox->currentText();
    QString time = ui->timeComboBox->currentText();

    for (const Movie& m : movieDB) {
        if (m.genre == genre && m.mood == mood && m.timeSlot == time) {
            QString html = QString(R"(
                <h2>🎥 %1</h2>
                <p><img src="%2" width="300"></p>
                <p>📝 %3</p>
                <p>  </p>
            )").arg(m.title, m.imagePath, m.description);
            ui->outputTextEdit->setHtml(html);
            return;
        }
    }

    ui->outputTextEdit->setText("😕 No exact match found. Try 'Surprise Me'!");
}

void MainWindow::surprisePick() {
    if (movieDB.isEmpty()) return;

    int index = QRandomGenerator::global()->bounded(movieDB.size());
    Movie m = movieDB[index];
    QString html = QString(R"(
        <h2>🎲 Surprise Pick: %1</h2>
        <p><img src="%2" width="300"></p>
        <p>📝 %3</p>
    )").arg(m.title, m.imagePath, m.description);

    ui->outputTextEdit->setHtml(html);
}
