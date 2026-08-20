#pragma once

#include <QMainWindow>

#include "PhantomCrypt.h"

class MainWindow : public QMainWindow
{
private:
    Image testImage;
public:
    MainWindow(QWidget* parent = nullptr);
};