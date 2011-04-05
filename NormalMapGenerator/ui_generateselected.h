/********************************************************************************
** Form generated from reading UI file 'generateselected.ui'
**
** Created: Mon Apr 19 14:25:15 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATESELECTED_H
#define UI_GENERATESELECTED_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GenerateSelected
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QListWidget *NormalList;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_2;
    QToolButton *AddAll;
    QToolButton *Add;
    QSpacerItem *verticalSpacer;
    QToolButton *Remove;
    QToolButton *RemoveAll;
    QSpacerItem *verticalSpacer_2;
    QListView *GenerateList;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *Ok;
    QPushButton *Cancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *GenerateSelected)
    {
        if (GenerateSelected->objectName().isEmpty())
            GenerateSelected->setObjectName(QString::fromUtf8("GenerateSelected"));
        GenerateSelected->resize(411, 300);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Buttons/Save.png"), QSize(), QIcon::Normal, QIcon::Off);
        GenerateSelected->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(GenerateSelected);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(GenerateSelected);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(4, 2, 4, 2);
        NormalList = new QListWidget(frame);
        NormalList->setObjectName(QString::fromUtf8("NormalList"));

        horizontalLayout->addWidget(NormalList);

        frame_3 = new QFrame(frame);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy);
        frame_3->setMinimumSize(QSize(0, 0));
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_3);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setContentsMargins(1, 1, 1, 1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        AddAll = new QToolButton(frame_3);
        AddAll->setObjectName(QString::fromUtf8("AddAll"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(AddAll->sizePolicy().hasHeightForWidth());
        AddAll->setSizePolicy(sizePolicy1);
        AddAll->setMinimumSize(QSize(32, 32));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Buttons/Icons/go-last.png"), QSize(), QIcon::Normal, QIcon::Off);
        AddAll->setIcon(icon1);
        AddAll->setIconSize(QSize(32, 32));
        AddAll->setAutoRaise(true);

        verticalLayout_2->addWidget(AddAll);

        Add = new QToolButton(frame_3);
        Add->setObjectName(QString::fromUtf8("Add"));
        Add->setMinimumSize(QSize(32, 32));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Buttons/Icons/go-next.png"), QSize(), QIcon::Normal, QIcon::Off);
        Add->setIcon(icon2);
        Add->setIconSize(QSize(32, 32));
        Add->setAutoRaise(true);

        verticalLayout_2->addWidget(Add);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        Remove = new QToolButton(frame_3);
        Remove->setObjectName(QString::fromUtf8("Remove"));
        Remove->setMinimumSize(QSize(32, 32));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Buttons/Icons/go-previous_red.png"), QSize(), QIcon::Normal, QIcon::Off);
        Remove->setIcon(icon3);
        Remove->setIconSize(QSize(32, 32));
        Remove->setAutoRaise(true);

        verticalLayout_2->addWidget(Remove);

        RemoveAll = new QToolButton(frame_3);
        RemoveAll->setObjectName(QString::fromUtf8("RemoveAll"));
        RemoveAll->setMinimumSize(QSize(32, 32));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Buttons/Icons/go-first-red.png"), QSize(), QIcon::Normal, QIcon::Off);
        RemoveAll->setIcon(icon4);
        RemoveAll->setIconSize(QSize(32, 32));
        RemoveAll->setAutoRaise(true);

        verticalLayout_2->addWidget(RemoveAll);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout->addWidget(frame_3);

        GenerateList = new QListView(frame);
        GenerateList->setObjectName(QString::fromUtf8("GenerateList"));

        horizontalLayout->addWidget(GenerateList);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(GenerateSelected);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMinimumSize(QSize(0, 25));
        frame_2->setMaximumSize(QSize(16777215, 25));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_2->setLineWidth(0);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        Ok = new QPushButton(frame_2);
        Ok->setObjectName(QString::fromUtf8("Ok"));
        sizePolicy1.setHeightForWidth(Ok->sizePolicy().hasHeightForWidth());
        Ok->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(Ok);

        Cancel = new QPushButton(frame_2);
        Cancel->setObjectName(QString::fromUtf8("Cancel"));
        sizePolicy1.setHeightForWidth(Cancel->sizePolicy().hasHeightForWidth());
        Cancel->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(Cancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(frame_2);


        retranslateUi(GenerateSelected);

        QMetaObject::connectSlotsByName(GenerateSelected);
    } // setupUi

    void retranslateUi(QDialog *GenerateSelected)
    {
        GenerateSelected->setWindowTitle(QApplication::translate("GenerateSelected", "Generate Selected", 0, QApplication::UnicodeUTF8));
        AddAll->setText(QApplication::translate("GenerateSelected", "...", 0, QApplication::UnicodeUTF8));
        Add->setText(QApplication::translate("GenerateSelected", "...", 0, QApplication::UnicodeUTF8));
        Remove->setText(QApplication::translate("GenerateSelected", "...", 0, QApplication::UnicodeUTF8));
        RemoveAll->setText(QApplication::translate("GenerateSelected", "...", 0, QApplication::UnicodeUTF8));
        Ok->setText(QApplication::translate("GenerateSelected", "Ok", 0, QApplication::UnicodeUTF8));
        Cancel->setText(QApplication::translate("GenerateSelected", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GenerateSelected: public Ui_GenerateSelected {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATESELECTED_H
