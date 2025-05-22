#pragma once

#include <QMap>
#include <QPainter>
#include <QPixmap>
#include <QResizeEvent>
#include <QWidget>

class ScalableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScalableWidget(const QString &backgroundImagePath, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void registerScalableChild(QWidget *child);
    void registerScalableChild(QWidget *child, const QRect &originalGeometry);

private:
    QPixmap                mBackground;
    QSize                  mOriginalSize;
    QMap<QWidget *, QRect> mChildrenInfo;

    QSize sizeWithAspectRatio(const QSize &original, const QSize &bound);
    void  scaleChildren();
};
