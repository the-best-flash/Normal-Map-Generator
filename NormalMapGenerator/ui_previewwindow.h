/********************************************************************************
** Form generated from reading UI file 'previewwindow.ui'
**
** Created: Mon Apr 19 14:25:15 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREVIEWWINDOW_H
#define UI_PREVIEWWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreviewWindow
{
public:
    QVBoxLayout *verticalLayout;
    QGraphicsView *Image;

    void setupUi(QWidget *PreviewWindow)
    {
        if (PreviewWindow->objectName().isEmpty())
            PreviewWindow->setObjectName(QString::fromUtf8("PreviewWindow"));
        PreviewWindow->resize(400, 300);
        verticalLayout = new QVBoxLayout(PreviewWindow);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        Image = new QGraphicsView(PreviewWindow);
        Image->setObjectName(QString::fromUtf8("Image"));
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::NoBrush);
        Image->setBackgroundBrush(brush);
        Image->setInteractive(false);
        Image->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing);

        verticalLayout->addWidget(Image);


        retranslateUi(PreviewWindow);

        QMetaObject::connectSlotsByName(PreviewWindow);
    } // setupUi

    void retranslateUi(QWidget *PreviewWindow)
    {
        PreviewWindow->setWindowTitle(QApplication::translate("PreviewWindow", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PreviewWindow: public Ui_PreviewWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREVIEWWINDOW_H
