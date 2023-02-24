// SPDX-FileCopyrightText: 2015 - 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "mainwindow.h"

#include <DApplication>
#include <DApplicationSettings>
#include <DWidgetUtil>
#include <DLog>
#include <DWaterMarkHelper>

#include <QDebug>

DCORE_USE_NAMESPACE
DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
#if defined(DTK_STATIC_LIB)
    DWIDGET_INIT_RESOURCE();
#endif
    DApplication *a = DApplication::globalApplication(argc, argv);

    DApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    DLogManager::registerConsoleAppender();

    a->loadTranslator();
#ifdef Q_OS_UNIX
    a->setOOMScoreAdj(500);
#endif

    a->setAutoActivateWindows(true);
    if (!a->setSingleInstance("deepin-tool-kit-examples")) {
        qDebug() << "another instance is running!!";
        return 0;
    }

    a->setApplicationName("dtk-example");
    a->setOrganizationName("deepin");
    a->setApplicationVersion("1.0");
    a->setProductIcon(QIcon(":/images/logo_icon.svg"));
    a->setWindowIcon(QIcon(":/images/logo_icon.svg"));
    a->setApplicationDescription(QApplication::translate("main", "Collections provides the examples for dtk applications."));
    a->setApplicationDisplayName(QObject::tr("Collections"));
    a->setApplicationLicense(QObject::tr("2023 UnionTech Software Technology Co., Ltd."));

    DApplicationSettings as;
    Q_UNUSED(as)

    MainWindow w;
    w.show();

    auto ins = DWaterMarkHelper::instance();
    WaterMarkData data = ins->data();
    data.setText("dtk example");
    data.setType(WaterMarkData::WaterMarkType::Text);
    data.setLayout(WaterMarkData::WaterMarkLayout::Tiled);
    data.setRotation(30);
    data.setScaleFactor(0.5);
    data.setColor(Qt::gray);
    auto font = data.font();
    font.setPointSize(65);
    data.setFont(font);
    data.setSpacing(65);
    data.setLineSpacing(-1);
    data.setOpacity(0.3);

    ins->setData(data);
    ins->registerWidget(&w);

    Dtk::Widget::moveToCenter(&w);

    return a->exec();
}
