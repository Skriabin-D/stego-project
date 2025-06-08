#include "graphics/mainwindow.hpp"
#include "graphics/ui_mainwindow.h"
#include "graphics/gui_interface.hpp"
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connect signals
    connect(ui->buttonLoadImage, &QPushButton::clicked,
        this, &MainWindow::onLoadImageClicked);

    connect(ui->comboMode,
        QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &MainWindow::onModeChanged);

    connect(ui->buttonProcess, &QPushButton::clicked,
        this, &MainWindow::onProcessClicked);

    // set initial state
    onModeChanged(ui->comboMode->currentIndex());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLoadImageClicked()
{
    loadedImagePath = QFileDialog::getOpenFileName(
        this,
        tr("Select Image"),
        QString(),
        tr("Images (*.png *.jpg *.bmp)")
    );
    if (!loadedImagePath.isEmpty()) {
        QPixmap pix(loadedImagePath);
        ui->labelOriginal->setPixmap(
            pix.scaled(ui->labelOriginal->size(), Qt::KeepAspectRatio)
        );
    }
}

void MainWindow::onModeChanged(int /*index*/)
{
    bool isEmbedding = (ui->comboMode->currentText() == tr("Embed"));
    ui->lineMessage->setEnabled(isEmbedding);
    ui->spinNumBits->setEnabled(!isEmbedding);
    ui->buttonProcess->setText(
        isEmbedding ? tr("Embed") : tr("Extract")
    );
}

void MainWindow::onProcessClicked()
{
    if (loadedImagePath.isEmpty()) {
        QMessageBox::warning(
            this,
            tr("Error"),
            tr("Please load an image first")
        );
        return;
    }

    bool usePVD = (ui->comboMethod->currentText() == tr("PVD"));

    if (ui->comboMode->currentText() == tr("Embed")) {
        QString message = ui->lineMessage->text();
        QString savePath = QFileDialog::getSaveFileName(
            this,
            tr("Save Stego Image"),
            "stego.png",
            tr("Images (*.png)")
        );
        if (savePath.isEmpty())
            return;

        handleEmbedding(loadedImagePath, message, savePath, usePVD);

        // display result
        QPixmap result(savePath);
        ui->labelResult->setPixmap(
            result.scaled(ui->labelResult->size(), Qt::KeepAspectRatio)
        );

    }
    else {
        int numBits = ui->spinNumBits->value();
        handleExtraction(loadedImagePath, numBits, usePVD, ui->textOutput);
    }
}
