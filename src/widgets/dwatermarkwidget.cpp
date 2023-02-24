// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dwatermarkwidget.h"

#include <DObjectPrivate>
#include <DWidgetUtil>

#include <QPainter>
#include <QResizeEvent>
#include <QDebug>

#include <cmath>

DCORE_USE_NAMESPACE
DTK_USE_NAMESPACE
DWIDGET_BEGIN_NAMESPACE

DWIDGET_USE_NAMESPACE

class WaterMarkDataPrivate: public DTK_CORE_NAMESPACE::DObjectPrivate
{
protected:
    explicit WaterMarkDataPrivate(WaterMarkData *parent)
        : DObjectPrivate(parent)
    {
    }

private:
    WaterMarkData::WaterMarkType type = WaterMarkData::None;            // 水印类型
    WaterMarkData::WaterMarkLayout layout = WaterMarkData::Center;      // 水印布局
    qreal scaleFactor = 1.0;                                            // 整体大小缩放系数
    int spacing = 0;                                                    // 间距
    int lineSpacing = 0;                                                // 行间距
    QString text;                                                       // 文本水印内容
    QFont font;                                                         // 文本水印字体
    QColor color;                                                       // 文本水印颜色
    qreal rotation = 0;                                                 // 水印旋转角度(0~360)
    qreal opacity = 1;                                                  // 水印透明度(0~1)
    QImage image;                                                       // 图片水印中的图片
    bool grayScale = true;                                              // 是否灰度化图片

    D_DECLARE_PUBLIC(WaterMarkData)
};

/*!
  \class Dtk::Widget::WaterMarkData
  \inmodule dtkwidget
  \brief 水印信息结构
  \a parent
 */
WaterMarkData::WaterMarkData()
    : DObject(*new WaterMarkDataPrivate(this))
{

}

/*!
  \class Dtk::Widget::WaterMarkData
  \inmodule dtkwidget
  \brief 拷贝构造
  \a parent
 */
WaterMarkData::WaterMarkData(const WaterMarkData &p)
 : DObject(*new WaterMarkDataPrivate(this))
{
    D_D(WaterMarkData);
    auto pd = p.d_func();

    d->type = pd->type;
    d->layout = pd->layout;
    d->scaleFactor = pd->scaleFactor;
    d->spacing = pd->spacing;
    d->lineSpacing = pd->lineSpacing;
    d->text = pd->text;
    d->font = pd->font;
    d->color = pd->color;
    d->rotation = pd->rotation;
    d->opacity = pd->opacity;
    d->image = pd->image;
    d->grayScale = pd->grayScale;
}

/*!
  \class Dtk::Widget::WaterMarkData
  \inmodule dtkwidget
  \brief 赋值构造
  \a parent
 */
WaterMarkData &WaterMarkData::operator=(const WaterMarkData &p)
{
    D_D(WaterMarkData);

    if (&p == this)
        return *this;

    auto pd = p.d_func();
    d->type = pd->type;
    d->layout = pd->layout;
    d->scaleFactor = pd->scaleFactor;
    d->spacing = pd->spacing;
    d->lineSpacing = pd->lineSpacing;
    d->text = pd->text;
    d->font = pd->font;
    d->color = pd->color;
    d->rotation = pd->rotation;
    d->opacity = pd->opacity;
    d->image = pd->image;
    d->grayScale = pd->grayScale;

    return *this;
}

/*!
  \brief get the current watermark type
  \brief 当前设置的水印类型
 */
const WaterMarkData::WaterMarkType &WaterMarkData::type()
{
    D_DC(WaterMarkData);
    return d->type;
}

/*!
  \brief set the current waternark \a type
  \brief 设置当前水印的类型
 */
void WaterMarkData::setType(WaterMarkType type)
{
    D_D(WaterMarkData);
    d->type = type;
}

/*!
  \brief get the current watermark layout
  \brief 当前设置的水印布局类型
 */
const WaterMarkData::WaterMarkLayout &WaterMarkData::layout()
{
    D_DC(WaterMarkData);
    return d->layout;
}

/*!
  \brief set the current waternark \a layout
  \brief 设置当前水印的布局类型
 */
void WaterMarkData::setLayout(WaterMarkLayout layout)
{
    D_D(WaterMarkData);
    d->layout = layout;
}

/*!
  \brief get the current watermark scale factor
  \brief 当前设置的水印整体缩放系数
 */
qreal WaterMarkData::scaleFactor()
{
    D_DC(WaterMarkData);
    return d->scaleFactor;
}

/*!
  \brief set the current waternark \a scaleFactor
  \brief 设置当前水印的整体缩放系数
 */
void WaterMarkData::setScaleFactor(qreal scaleFactor)
{
    D_D(WaterMarkData);
    d->scaleFactor = scaleFactor;
}

/*!
  \brief get the current watermark spacing
  \brief 当前设置的水印间距
 */
int WaterMarkData::spacing()
{
    D_DC(WaterMarkData);
    return d->spacing;
}

/*!
  \brief set the current waternark \a spacing
  \brief 设置当前水印的间距
 */
void WaterMarkData::setSpacing(int spacing)
{
    D_D(WaterMarkData);
    d->spacing = spacing;
}

/*!
  \brief get the current watermark line spacing
  \brief 当前设置的水印行间距
 */
int WaterMarkData::lineSpacing()
{
    D_DC(WaterMarkData);
    return d->lineSpacing;
}

/*!
  \brief set the current waternark \a lineSpacing
  \brief 设置当前水印的行间距
 */
void WaterMarkData::setLineSpacing(int lineSpacing)
{
    D_D(WaterMarkData);
    d->lineSpacing = lineSpacing;
}

/*!
  \brief get the current watermark text
  \brief 当前设置的水印文本内容
 */
const QString &WaterMarkData::text()
{
    D_DC(WaterMarkData);
    return d->text;
}

/*!
  \brief set the current waternark \a text
  \brief 设置当前水印的文本内容
 */
void WaterMarkData::setText(const QString &text)
{
    D_D(WaterMarkData);
    d->text = text;
}

/*!
  \brief get the current watermark font
  \brief 当前设置的水印字体
 */
const QFont &WaterMarkData::font()
{
    D_DC(WaterMarkData);
    return d->font;
}

/*!
  \brief set the current waternark \a font
  \brief 设置当前水印的字体
 */
void WaterMarkData::setFont(const QFont &font)
{
    D_D(WaterMarkData);
    d->font = font;
}

/*!
  \brief get the current watermark color
  \brief 当前设置的水印颜色
 */
const QColor &WaterMarkData::color()
{
    D_DC(WaterMarkData);
    return d->color;
}

/*!
  \brief set the current waternark \a color
  \brief 设置当前水印的颜色
 */
void WaterMarkData::setColor(const QColor &color)
{
    D_D(WaterMarkData);
    d->color = color;
}

/*!
  \brief get the current watermark rotation
  \brief 当前设置的水印旋转角度(0~360)
 */
qreal WaterMarkData::rotation()
{
    D_DC(WaterMarkData);
    return d->rotation;
}

/*!
  \brief set the current waternark \a rotation
  \brief 设置当前水印的旋转角度(0~360)
 */
void WaterMarkData::setRotation(qreal rotation)
{
    D_D(WaterMarkData);
    d->rotation = rotation;
}

/*!
  \brief get the current watermark opacity
  \brief 当前设置的水印透明度(0~1.0)
 */
qreal WaterMarkData::opacity()
{
    D_DC(WaterMarkData);
    return d->opacity;
}

/*!
  \brief set the current waternark \a opacity
  \brief 设置当前水印透明度(0~1.0)
 */
void WaterMarkData::setOpacity(qreal opacity)
{
    D_D(WaterMarkData);
    d->opacity = opacity;
}

/*!
  \brief get the current watermark image
  \brief 当前设置的水印图片
 */
const QImage &WaterMarkData::image()
{
    D_DC(WaterMarkData);
    return d->image;
}

/*!
  \brief set the current waternark \a image
  \brief 设置当前水印图片
 */
void WaterMarkData::setImage(const QImage &image)
{
    D_D(WaterMarkData);
    d->image = image;
}

/*!
  \brief get the current watermark grayscale of image
  \brief 当前设置的水印图片是否需要灰度化
 */
bool WaterMarkData::grayScale()
{
    D_DC(WaterMarkData);
    return d->grayScale;
}

/*!
  \brief set the current waternark \a grayScale of image,default value is true
  \brief 设置当前水印图片是否需要灰度化，默认为true
 */
void WaterMarkData::setGrayScale(bool grayScale)
{
    D_D(WaterMarkData);
    d->grayScale = grayScale;
}

QImage createTextureImage(const WaterMarkData &data, qreal deviceScale)
{
    WaterMarkData cloneData = data;
    QImage texture;

    switch (cloneData.type()) {
    case WaterMarkData::WaterMarkType::None:
        return texture;
    case WaterMarkData::WaterMarkType::Text:
    {
        // 缩放处理
        QFont font = cloneData.font();
        if (!(font.styleStrategy() & QFont::PreferAntialias))
            font.setStyleStrategy(QFont::PreferAntialias);
        font.setPointSize(qRound(font.pointSize() * cloneData.scaleFactor() * deviceScale));

        // 边距计算
        QFontMetrics fm(font);
        QSize textSize = fm.size(Qt::TextSingleLine, cloneData.text());
        int realLineSpacing = qMax(qMin(textSize.width(), textSize.height()), cloneData.lineSpacing());
        QSize spaceSize = QSize(qMax(0, cloneData.spacing()), realLineSpacing) * deviceScale;

        // 绘制纹理
        texture = QImage(textSize + spaceSize, QImage::Format_ARGB32);
        texture.fill(Qt::transparent);
        QPainter tp;
        tp.begin(&texture);
        tp.setFont(font);
        tp.setPen(cloneData.color());
        tp.setBrush(Qt::NoBrush);
        tp.setRenderHint(QPainter::TextAntialiasing);
        tp.drawText(texture.rect(), Qt::AlignCenter, cloneData.text());
        tp.end();
    }
        break;
    case WaterMarkData::WaterMarkType::Image:
    {
        // 缩放处理
        QImage img = cloneData.image();
        if (cloneData.grayScale()) {
            DWIDGET_NAMESPACE::grayScale(cloneData.image(), img, cloneData.image().rect());
        }

        img = img.scaledToWidth(qRound(img.width() * cloneData.scaleFactor() * deviceScale));
        int realLineSpacing = qMax(qMin(img.width(), img.height()), cloneData.lineSpacing());
        texture = QImage(img.size() + QSize(qMax(0, cloneData.spacing()), cloneData.lineSpacing() < 0 ? realLineSpacing : cloneData.lineSpacing())
                         , QImage::Format_ARGB32);
        texture.fill(Qt::transparent);

        // 拷贝所有像素到一张添加了边距和行间距的图中
        for (int i = 0; i < img.width(); ++i) {
            for (int j = 0; j < img.height(); ++j) {
                texture.setPixelColor(i, j, img.pixelColor(i, j));
            }
        }
    }
        break;
    }
    return texture;
}

void drawWaterTexture(QPainter &painter, const QImage &texture, qreal rotation, const QRect &paintRect)
{
    painter.save();
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::Antialiasing);

    // 旋转画刷,避免调整父界面大小时水印内容有移动
    QBrush b;
    b.setTextureImage(texture);
    QPoint center = texture.rect().center();
    QTransform t = QTransform()
            .translate(center.x(), center.y())
            .rotate(rotation)
            .translate(-center.x(), -center.y());
    b.setTransform(t);

//    painter.setPen(Qt::NoPen);
    painter.setBrush(b);
    painter.drawRect(paintRect);
    painter.restore();
}

class DWaterMarkWidgetPrivate: public DTK_CORE_NAMESPACE::DObjectPrivate
{
protected:
    explicit DWaterMarkWidgetPrivate(DWaterMarkWidget *parent)
        : DObjectPrivate(parent)
    {

    }

private:
    void init();

    WaterMarkData data;
    QImage textureImage;

    D_DECLARE_PUBLIC(DWaterMarkWidget)
};

void DWaterMarkWidgetPrivate::init()
{
    D_Q(DWaterMarkWidget);

    q->setObjectName("DWaterMarkWidget");
    q->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    q->setFocusPolicy(Qt::NoFocus);
}

/*!
  \class Dtk::Widget::DWaterMarkWidget
  \inmodule dtkwidget
  \brief 水印类，将覆盖设置的父界面，并跟随父界面动态调整大小
  \a parent
 */
DWaterMarkWidget::DWaterMarkWidget(QWidget *parent)
    : QWidget(parent)
    , DObject(*new DWaterMarkWidgetPrivate(this))
{
    D_D(DWaterMarkWidget);
    d->init();

    if (parent)
        parent->installEventFilter(this);
}

/*!
  \brief get the current setting
  \brief 当前设置的水印信息
 */
const WaterMarkData &DWaterMarkWidget::data()
{
    D_DC(DWaterMarkWidget);
    return d->data;
}

/*!
  \brief set the current setting \a data
  \brief 设置当前水印信息
 */
void DWaterMarkWidget::setData(const WaterMarkData &data)
{
    D_D(DWaterMarkWidget);

    d->data = data;
    d->textureImage = createTextureImage(d->data, devicePixelRatioF());

    update();
}

void DWaterMarkWidget::paintEvent(QPaintEvent *)
{
    D_D(DWaterMarkWidget);

    qreal deviceScale = devicePixelRatioF();

    QPainter painter(this);
    painter.setOpacity(d->data.opacity());

    switch (d->data.type()) {
    case WaterMarkData::WaterMarkType::None:
        return;
    case WaterMarkData::WaterMarkType::Text: {
        // 居中处理
        if (d->data.layout() == WaterMarkData::Center) {
            // 缩放处理
            QFont font = d->data.font();
            if (!(font.styleStrategy() & QFont::PreferAntialias))
                font.setStyleStrategy(QFont::PreferAntialias);
            font.setPointSize(qRound(d->data.font().pointSize() * d->data.scaleFactor() * deviceScale));

            auto center = rect().center();
            painter.translate(center.x(), center.y());
            painter.rotate(d->data.rotation());
            painter.translate(-center.x(), -center.y());

            painter.save();
            painter.setRenderHint(QPainter::TextAntialiasing);
            painter.setFont(font);
            painter.setPen(d->data.color());
            painter.drawText(rect(), Qt::AlignCenter, d->data.text());
            painter.restore();
            return;
        }

        drawWaterTexture(painter, d->textureImage, d->data.rotation(), rect());
    }
    case WaterMarkData::WaterMarkType::Image:
    {
        if (d->data.image().isNull() || qFuzzyCompare(d->data.scaleFactor(), 0))
            return;

        // 居中处理
        if (d->data.layout() == WaterMarkData::Center) {
            // 缩放处理
            QImage img = d->data.image();
            if (d->data.grayScale())
                DWIDGET_NAMESPACE::grayScale(d->data.image(), img, d->data.image().rect());
            img = img.scaledToWidth(qRound(img.width() * d->data.scaleFactor() * deviceScale));
            QSize size = img.size() / img.devicePixelRatio();
            int imgWidth = size.width();
            int imgHeight = size.height();

            auto center = rect().center();
            painter.translate(center.x(), center.y());
            painter.rotate(d->data.rotation());
            painter.translate(-center.x(), -center.y());

            QPointF leftTop(rect().center().x() - imgWidth / 2.0, rect().center().y() - imgHeight / 2.0);
            painter.drawImage(leftTop, img);
            return;
        }

        drawWaterTexture(painter, d->textureImage, d->data.rotation(), rect());
    }
    }
}

bool DWaterMarkWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched != parent())
        return false;

    // 保持和父界面尺寸一致
    if (event->type() == QEvent::Resize) {
        QResizeEvent *e = static_cast<QResizeEvent *>(event);
        resize(e->size());
    }

    return false;
}

DWIDGET_END_NAMESPACE
