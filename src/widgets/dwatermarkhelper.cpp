// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dwatermarkhelper.h"

#include <QGuiApplication>
#include <QPaintEvent>
#include <QPainter>

#include <DObjectPrivate>

DWIDGET_BEGIN_NAMESPACE

DTK_USE_NAMESPACE
DWIDGET_USE_NAMESPACE

#define WATER_TEXTSPACE 65
#define DEFAULT_FONTSIZE WATER_TEXTSPACE

class DWaterMaskHelper_ : public DWaterMarkHelper {};
Q_GLOBAL_STATIC(DWaterMaskHelper_, wmhGlobal)

class DWaterMarkHelperPrivate: public DTK_CORE_NAMESPACE::DObjectPrivate
{
public:
    explicit DWaterMarkHelperPrivate(DWaterMarkHelper *parent)
        : DObjectPrivate(parent)
    {

    }

    void init();
    static void clean() {
        auto helper = DWaterMarkHelper::instance();
        helper->d_func()->widgetMap.clear();
        helper->deleteLater();
    }

    WaterMarkData data;
    static QMap<QWidget *, DWaterMarkWidget *> widgetMap;
};

void DWaterMarkHelperPrivate::init()
{    // 进程退出时销毁资源
    qAddPostRoutine(clean);
}

QMap<QWidget *, DWaterMarkWidget *>DWaterMarkHelperPrivate::widgetMap;

/*!
  \brief DWaterMarkHelper::instance
  DWaterMarkHelper 的单例对象，使用 Q_GLOBAL_STATIC 定义，在第一次调用时实例化。
  \return
 */
DWaterMarkHelper *DWaterMarkHelper::instance()
{
    return wmhGlobal;
}

/*!
  \class Dtk::Widget::DWaterMaskHelper
  \inmodule dtkwidget
  \brief 不允许直接实例化此对象
  \a parent
  \sa DWaterMaskHelper::instance
 */
DWaterMarkHelper::DWaterMarkHelper(QObject *parent)
    : QObject(parent)
    , DObject(*new DWaterMarkHelperPrivate(this))
{
    D_D(DWaterMarkHelper);
    d->init();
}

/*!
  \brief DWaterMarkHelper::registerWidget
  为指定窗口添加水印
  \a widget
 */
void DWaterMarkHelper::registerWidget(QWidget *widget)
{
    D_D(DWaterMarkHelper);

    if (widget && !d->widgetMap.contains(widget)) {
        DWaterMarkWidget *mark = new DWaterMarkWidget(widget);
        mark->setData(d->data);
        mark->resize(widget->size());
        mark->setVisible(true);
        d->widgetMap.insert(widget, mark);

        connect(widget, &QObject::destroyed, this, [widget] {
            DWaterMarkHelper::instance()->d_func()->widgetMap.remove(widget);
        });
    }
}

/*!
  \brief get the current setting
  \brief 当前设置的水印信息
 */
WaterMarkData DWaterMarkHelper::data() const
{
    D_DC(DWaterMarkHelper);
    return d->data;
}

/*!
  \brief set the current setting \a data
  \brief 设置当前水印信息
 */
void DWaterMarkHelper::setData(const WaterMarkData &data)
{
    D_D(DWaterMarkHelper);
    d->data = data;

    auto helper = DWaterMarkHelper::instance();
    for (auto w : helper->d_func()->widgetMap.values()) {
        w->setData(data);
    }
}

DWIDGET_END_NAMESPACE
