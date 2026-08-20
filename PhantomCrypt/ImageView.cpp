#include "ImageView.h"
#include <qpainter.h>
#include <qcolor.h>

ImageView::ImageView(QWidget* parent)
    : QWidget(parent)
{
    setMinimumSize(400, 400);
}

void ImageView::wheelEvent(QWheelEvent* event) {
    if (image == nullptr)
        return;

    if (event->angleDelta().y() > 0) {
        scaleFactor *= 1.1;
    }
    else {
        scaleFactor /= 1.1;
    }

    if (scaleFactor < 1.0)
        scaleFactor = 1.0;
    if (scaleFactor > 100.0)
        scaleFactor = 100.0;

    update();

    event->accept();
}

void ImageView::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        dragging = true;
        lastMousePosition = event->pos();
        setCursor(Qt::ClosedHandCursor);

        event->accept();
    }
}

void ImageView::mouseMoveEvent(QMouseEvent* event) {
    if (!dragging)
        return;

    QPoint currentPosition = event->pos();
    
    QPoint delta = currentPosition - lastMousePosition;

    offsetX += delta.x();
    offsetY += delta.y();

    lastMousePosition = currentPosition;

    update();

    event->accept();
}

void ImageView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton){
        dragging = false;

        unsetCursor();

        event->accept();
    }
}

void ImageView::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.fillRect(rect(), Qt::darkGray);

    if (image == nullptr)
        return;

    for (std::size_t y = 0; y < image->getHeight(); ++y)
    {
        for (std::size_t x=0; x<image->getWidth(); ++x)
        { 
            const Pixel& pixel = image->getPixel(x, y);

            QColor color(
                pixel.getRed(), pixel.getGreen(), pixel.getBlue(), pixel.getAlpha());

            QRectF pixelRect(offsetX + x * scaleFactor, offsetY+  y * scaleFactor, scaleFactor, scaleFactor);

            painter.fillRect(pixelRect, color);
        }
    }
}

void ImageView::setImage(const Image* newImage)
{
    image = newImage;
    update();
}