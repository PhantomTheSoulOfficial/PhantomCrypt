#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include "PhantomCrypt.h"

class ImageView : public QWidget
{

public:
    explicit ImageView(QWidget* parent = nullptr);

    void setImage(const Image* newImage);

protected:
    void paintEvent(QPaintEvent* event) override;

    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    const Image* image = nullptr;
	double scaleFactor = 1.0;
    double offsetX = 0.0;
    double offsetY = 0.0;

    bool dragging = false;
    QPoint lastMousePosition;
};