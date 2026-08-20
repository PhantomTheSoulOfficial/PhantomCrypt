#include <qwidget.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qlabel.h>

#include "MainWindow.h"
#include "ImageView.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), testImage(256, 256)
{
    setWindowTitle("PhantomCrypt");
    resize(800, 600);

    QWidget* centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    
    ImageView* imageArea = new ImageView();

    for (std::size_t y = 0; y < 256; ++y)
    {
        for (std::size_t x = 0; x < 256; ++x)
        {
            Pixel pixel(
                static_cast<uint8_t>(x * 1),
                static_cast<uint8_t>(y * 1),
                128,
                255
            );

            testImage.setPixel(x, y, pixel);
        }
    }

    imageArea->setImage(&testImage);

    QWidget* controlPanel = new QWidget();

    mainLayout->addWidget(imageArea);
    mainLayout->addWidget(controlPanel);
    mainLayout->setStretch(0, 2);
	mainLayout->setStretch(1, 1);

    QVBoxLayout* controlLayout = new QVBoxLayout(controlPanel);

    QLabel* title = new QLabel("Algorithm Lab");

	QPushButton* encryptButton = new QPushButton("Encrypt");
    QPushButton* decryptButton = new QPushButton("Decrypt");

    controlLayout->addWidget(title);
    controlLayout->addWidget(encryptButton);
    controlLayout->addWidget(decryptButton);
    
    title->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    controlLayout->addStretch();

	controlPanel->setStyleSheet("background-color: lightblue;");

}