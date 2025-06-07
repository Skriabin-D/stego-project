#include "graphics/mainwindow.hpp"

#include "graphics/ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->buttonLoadImage, &QPushButton::clicked, this, &MainWindow::onLoadImageClicked);
    connect(ui->buttonProcess, &QPushButton::clicked, this, &MainWindow::onProcessClicked);
    connect(ui->radioEmbed, &QRadioButton::toggled, this, &MainWindow::onModeChanged);

    onModeChanged(); 
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLoadImageClicked()
{
    loadedImagePath = QFileDialog::getOpenFileName(this, "Upload image", "", "Images (*.png *.jpg *.bmp)");
    if (!loadedImagePath.isEmpty()) {
        QPixmap pix(loadedImagePath);
        ui->labelOriginal->setPixmap(pix.scaled(ui->labelOriginal->size(), Qt::KeepAspectRatio));
    }
}

void MainWindow::onModeChanged()
{
    bool isEmbedding = ui->radioEmbed->isChecked();
    ui->lineMessage->setEnabled(isEmbedding);
    ui->spinNumBits->setEnabled(!isEmbedding);
    ui->buttonProcess->setText(isEmbedding ? "Embed" : "Extract");
}

void MainWindow::onProcessClicked()
{
    if (loadedImagePath.isEmpty()) {
        QMessageBox::warning(this, "Error", "First, upload the image");
        return;
    }

    bool usePVD = ui->radioMethodPVD->isChecked();
    QString methodName = usePVD ? "PVD" : "LSB-DCT";

    if (ui->radioEmbed->isChecked()) {
        QString message = ui->lineMessage->text();
        QString savePath = QFileDialog::getSaveFileName(this, "Save the image", "stego.png", "Images (*.png)");
        if (savePath.isEmpty()) return;

        handleEmbedding(loadedImagePath, message, savePath, usePVD);

        QPixmap result(savePath);
        ui->labelResult->setPixmap(result.scaled(ui->labelResult->size(), Qt::KeepAspectRatio));

    }
    else {
        int numBits = ui->spinNumBits->value();
        handleExtraction(loadedImagePath, numBits, usePVD, ui->textOutput);
    }
}
