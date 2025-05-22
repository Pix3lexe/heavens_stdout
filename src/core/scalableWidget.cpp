#include "scalableWidget.h"

ScalableWidget::ScalableWidget(const QString &backgroundImagePath, QWidget *parent) :
    QWidget(parent), mBackground(backgroundImagePath)
{
    mOriginalSize = mBackground.size();
}

void ScalableWidget::registerScalableChild(QWidget *child)
{
    mChildrenInfo[child] = child->geometry();
}

void ScalableWidget::registerScalableChild(QWidget *child, const QRect &originalGeometry)
{
    mChildrenInfo[child] = originalGeometry;
}

QSize ScalableWidget::sizeWithAspectRatio(const QSize &original, const QSize &bound)
{
    return original.scaled(bound, Qt::KeepAspectRatio);
}

void ScalableWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QSize    scaledSize = sizeWithAspectRatio(mOriginalSize, size());
    QPoint   center((width() - scaledSize.width()) / 2, (height() - scaledSize.height()) / 2);
    painter.drawPixmap(center, mBackground.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ScalableWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    scaleChildren();
    update();
}

void ScalableWidget::scaleChildren()
{
    QSize  scaledSize = sizeWithAspectRatio(mOriginalSize, size());
    double scale      = static_cast<double>(scaledSize.width()) / mOriginalSize.width();
    QPoint offset((width() - scaledSize.width()) / 2, (height() - scaledSize.height()) / 2);

    for(auto it = mChildrenInfo.begin(); it != mChildrenInfo.end(); ++it)
    {
        QWidget *child = it.key();
        QRect    orig  = it.value();
        QRect    scaled(
            offset.x() + static_cast<int>(orig.x() * scale),
            offset.y() + static_cast<int>(orig.y() * scale),
            static_cast<int>(orig.width() * scale),
            static_cast<int>(orig.height() * scale));
        child->setGeometry(scaled);
        child->updateGeometry();
    }
}
