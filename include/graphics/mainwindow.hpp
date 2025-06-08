#pragma once
#include "graphics/gui_interface.hpp"  
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadImageClicked();
    void onModeChanged(int index);
    void onProcessClicked();

private:
    Ui::MainWindow* ui;
    QString loadedImagePath;
};