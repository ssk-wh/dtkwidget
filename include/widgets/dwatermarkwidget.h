// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef WATERMARKWIDGET_H
#define WATERMARKWIDGET_H

#include <QWidget>

#include <dtkwidget_global.h>
#include <DObject>

DWIDGET_BEGIN_NAMESPACE

class WaterMarkDataPrivate;
class WaterMarkData : public DTK_CORE_NAMESPACE::DObject
{
public:
    enum WaterMarkType {
        None,       /*!<@~chinese 不会绘制水印 */
        Text,       /*!<@~chinese 绘制文字水印 */
        Image       /*!<@~chinese 绘制图片水印 */
    };
    enum WaterMarkLayout {
        Center,     /*!<@~chinese 居中 */
        Tiled       /*!<@~chinese 平铺 */
    };

    explicit WaterMarkData();

    WaterMarkData(const WaterMarkData& p);
    WaterMarkData& operator=(const WaterMarkData& p);

    const WaterMarkType &type();
    void setType(WaterMarkType type);

    const WaterMarkLayout &layout();
    void setLayout(WaterMarkLayout layout);

    qreal scaleFactor();
    void setScaleFactor(qreal scaleFactor);

    int spacing();
    void setSpacing(int spacing);

    int lineSpacing();
    void setLineSpacing(int lineSpacing);

    const QString &text();
    void setText(const QString &text);

    const QFont &font();
    void setFont(const QFont &font);

    const QColor &color();
    void setColor(const QColor &color);

    qreal rotation();
    void setRotation(qreal rotation);

    qreal opacity();
    void setOpacity(qreal opacity);

    const QImage &image();
    void setImage(const QImage &image);

    bool grayScale();
    void setGrayScale(bool grayScale);

private:
    D_DECLARE_PRIVATE(WaterMarkData)
};

class DWaterMarkWidgetPrivate;
class DWaterMarkWidget : public QWidget, public DTK_CORE_NAMESPACE::DObject
{
    Q_OBJECT
public:
    explicit DWaterMarkWidget(QWidget *parent = nullptr);

    const WaterMarkData &data();
    void setData(const WaterMarkData &data);

protected:
    void paintEvent(QPaintEvent *) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    D_DECLARE_PRIVATE(DWaterMarkWidget)
};

DWIDGET_END_NAMESPACE

#endif // WATERMARKWIDGET_H
