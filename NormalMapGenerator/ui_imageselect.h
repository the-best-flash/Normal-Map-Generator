/********************************************************************************
** Form generated from reading UI file 'imageselect.ui'
**
** Created: Mon Apr 19 14:25:15 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGESELECT_H
#define UI_IMAGESELECT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageSelect
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *frame_5;
    QGridLayout *gridLayout;
    QGraphicsView *LeftImage;
    QGraphicsView *UpImage;
    QGraphicsView *DownImage;
    QGraphicsView *RightImage;
    QFrame *frame_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_8;
    QLineEdit *LeftFileName;
    QToolButton *LoadLeft;
    QFrame *frame_7;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_10;
    QLineEdit *UpImageName;
    QToolButton *LoadUp;
    QFrame *frame_8;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_11;
    QLineEdit *DownFileName;
    QToolButton *LoadDown;
    QFrame *frame_9;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_9;
    QLineEdit *RightFileName;
    QToolButton *LoadRight;

    void setupUi(QWidget *ImageSelect)
    {
        if (ImageSelect->objectName().isEmpty())
            ImageSelect->setObjectName(QString::fromUtf8("ImageSelect"));
        ImageSelect->resize(400, 300);
        horizontalLayout = new QHBoxLayout(ImageSelect);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        frame_5 = new QFrame(ImageSelect);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setFrameShape(QFrame::NoFrame);
        frame_5->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_5);
        gridLayout->setContentsMargins(1, 1, 1, 1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        LeftImage = new QGraphicsView(frame_5);
        LeftImage->setObjectName(QString::fromUtf8("LeftImage"));

        gridLayout->addWidget(LeftImage, 1, 0, 1, 1);

        UpImage = new QGraphicsView(frame_5);
        UpImage->setObjectName(QString::fromUtf8("UpImage"));

        gridLayout->addWidget(UpImage, 1, 1, 1, 1);

        DownImage = new QGraphicsView(frame_5);
        DownImage->setObjectName(QString::fromUtf8("DownImage"));

        gridLayout->addWidget(DownImage, 2, 0, 1, 1);

        RightImage = new QGraphicsView(frame_5);
        RightImage->setObjectName(QString::fromUtf8("RightImage"));

        gridLayout->addWidget(RightImage, 2, 1, 1, 1);

        frame_6 = new QFrame(frame_5);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setFrameShape(QFrame::NoFrame);
        frame_6->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_6);
        horizontalLayout_5->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_8 = new QLabel(frame_6);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_5->addWidget(label_8);

        LeftFileName = new QLineEdit(frame_6);
        LeftFileName->setObjectName(QString::fromUtf8("LeftFileName"));
        LeftFileName->setReadOnly(true);

        horizontalLayout_5->addWidget(LeftFileName);

        LoadLeft = new QToolButton(frame_6);
        LoadLeft->setObjectName(QString::fromUtf8("LoadLeft"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Buttons/Icons/folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        LoadLeft->setIcon(icon);

        horizontalLayout_5->addWidget(LoadLeft);


        gridLayout->addWidget(frame_6, 0, 0, 1, 1);

        frame_7 = new QFrame(frame_5);
        frame_7->setObjectName(QString::fromUtf8("frame_7"));
        frame_7->setFrameShape(QFrame::NoFrame);
        frame_7->setFrameShadow(QFrame::Raised);
        horizontalLayout_6 = new QHBoxLayout(frame_7);
        horizontalLayout_6->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_10 = new QLabel(frame_7);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_6->addWidget(label_10);

        UpImageName = new QLineEdit(frame_7);
        UpImageName->setObjectName(QString::fromUtf8("UpImageName"));
        UpImageName->setReadOnly(true);

        horizontalLayout_6->addWidget(UpImageName);

        LoadUp = new QToolButton(frame_7);
        LoadUp->setObjectName(QString::fromUtf8("LoadUp"));
        LoadUp->setIcon(icon);

        horizontalLayout_6->addWidget(LoadUp);


        gridLayout->addWidget(frame_7, 0, 1, 1, 1);

        frame_8 = new QFrame(frame_5);
        frame_8->setObjectName(QString::fromUtf8("frame_8"));
        frame_8->setFrameShape(QFrame::NoFrame);
        frame_8->setFrameShadow(QFrame::Raised);
        horizontalLayout_7 = new QHBoxLayout(frame_8);
        horizontalLayout_7->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_11 = new QLabel(frame_8);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_7->addWidget(label_11);

        DownFileName = new QLineEdit(frame_8);
        DownFileName->setObjectName(QString::fromUtf8("DownFileName"));
        DownFileName->setReadOnly(true);

        horizontalLayout_7->addWidget(DownFileName);

        LoadDown = new QToolButton(frame_8);
        LoadDown->setObjectName(QString::fromUtf8("LoadDown"));
        LoadDown->setIcon(icon);

        horizontalLayout_7->addWidget(LoadDown);


        gridLayout->addWidget(frame_8, 3, 0, 1, 1);

        frame_9 = new QFrame(frame_5);
        frame_9->setObjectName(QString::fromUtf8("frame_9"));
        frame_9->setFrameShape(QFrame::NoFrame);
        frame_9->setFrameShadow(QFrame::Raised);
        horizontalLayout_8 = new QHBoxLayout(frame_9);
        horizontalLayout_8->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_9 = new QLabel(frame_9);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_8->addWidget(label_9);

        RightFileName = new QLineEdit(frame_9);
        RightFileName->setObjectName(QString::fromUtf8("RightFileName"));
        RightFileName->setReadOnly(true);

        horizontalLayout_8->addWidget(RightFileName);

        LoadRight = new QToolButton(frame_9);
        LoadRight->setObjectName(QString::fromUtf8("LoadRight"));
        LoadRight->setIcon(icon);

        horizontalLayout_8->addWidget(LoadRight);


        gridLayout->addWidget(frame_9, 3, 1, 1, 1);


        horizontalLayout->addWidget(frame_5);


        retranslateUi(ImageSelect);

        QMetaObject::connectSlotsByName(ImageSelect);
    } // setupUi

    void retranslateUi(QWidget *ImageSelect)
    {
        ImageSelect->setWindowTitle(QApplication::translate("ImageSelect", "Form", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("ImageSelect", "Left", 0, QApplication::UnicodeUTF8));
        LoadLeft->setText(QApplication::translate("ImageSelect", "...", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("ImageSelect", "Up", 0, QApplication::UnicodeUTF8));
        LoadUp->setText(QApplication::translate("ImageSelect", "...", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("ImageSelect", "Down", 0, QApplication::UnicodeUTF8));
        LoadDown->setText(QApplication::translate("ImageSelect", "...", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("ImageSelect", "Right", 0, QApplication::UnicodeUTF8));
        LoadRight->setText(QApplication::translate("ImageSelect", "...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ImageSelect: public Ui_ImageSelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGESELECT_H
