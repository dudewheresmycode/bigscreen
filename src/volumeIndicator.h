#ifndef VOLUME_INDICATOR_H
#define VOLUME_INDICATOR_H

#include <QWidget>
#include <QPainter>
#include "constants.h"

class VolumeIndicator : public QWidget {
    Q_OBJECT
    qreal p; // progress 0.0 to 1.0
  public:
    VolumeIndicator(QWidget * p = 0) : QWidget(p), p(0) {
      // setMinimumSize(constants::OSD_WIDTH, constants::OSD_WIDTH);
      setGeometry(0, 0, constants::OSD_WIDTH, constants::OSD_WIDTH);
    }
    void upd(qreal pp) {
      if (p == pp) return;
      p = pp;
      update();
    }
  void paintEvent(QPaintEvent *) {
    qreal pd = p * 360;
    qreal rd = 360 - pd;
    QPainter p(this);
    int arcWidth = constants::VOLUME_STROKE_WIDTH;
    int widthOffset = constants::OSD_WIDTH - arcWidth;
    // p.fillRect(rect(), Qt::white);
    p.translate(10, 10);
    p.setRenderHint(QPainter::Antialiasing);
    QPainterPath path, path2;
    path.moveTo(widthOffset / 2, 0);
    path.arcTo(QRectF(0, 0, widthOffset, widthOffset), 90, -pd);
    QPen pen, pen2;
    pen.setCapStyle(Qt::FlatCap);
    pen.setColor(QColor("#15A9FC"));
    pen.setWidth(arcWidth);
    p.strokePath(path, pen);
    path2.moveTo(widthOffset / 2, 0);
    pen2.setWidth(arcWidth);
    pen2.setColor(QColor(31, 33, 33, 125));
    pen2.setCapStyle(Qt::FlatCap);
    pen2.setDashPattern(QVector<qreal>{0.5, 1.105});
    path2.arcTo(QRectF(0, 0, widthOffset, widthOffset), 90, rd);
    pen2.setDashOffset(2.2);
    p.strokePath(path2, pen2);
  }  
};

#endif // VOLUME_INDICATOR_H