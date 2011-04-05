/********************************************************************************
** Form generated from reading UI file 'normalmaplist.ui'
**
** Created: Mon Apr 19 14:25:15 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NORMALMAPLIST_H
#define UI_NORMALMAPLIST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NormalMapList
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QToolButton *SaveList;
    QToolButton *OpenList;
    QFrame *line_2;
    QToolButton *GenerateAll;
    QFrame *line_3;
    QToolButton *Help;
    QToolButton *About;
    QSpacerItem *horizontalSpacer;
    QListWidget *NormalList;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *Add;
    QToolButton *Remove;
    QFrame *line;
    QToolButton *GenerateSelected;
    QToolButton *EditButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *NormalMapList)
    {
        if (NormalMapList->objectName().isEmpty())
            NormalMapList->setObjectName(QString::fromUtf8("NormalMapList"));
        NormalMapList->resize(200, 400);
        NormalMapList->setMinimumSize(QSize(200, 400));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Buttons/Icons/GenetateNormal.png"), QSize(), QIcon::Normal, QIcon::Off);
        NormalMapList->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(NormalMapList);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(NormalMapList);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(0, 34));
        frame->setMaximumSize(QSize(1000, 16777215));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        SaveList = new QToolButton(frame);
        SaveList->setObjectName(QString::fromUtf8("SaveList"));
        SaveList->setMaximumSize(QSize(36, 36));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Buttons/Icons/save_list.png"), QSize(), QIcon::Normal, QIcon::Off);
        SaveList->setIcon(icon1);
        SaveList->setIconSize(QSize(32, 32));
        SaveList->setAutoRaise(true);

        horizontalLayout->addWidget(SaveList);

        OpenList = new QToolButton(frame);
        OpenList->setObjectName(QString::fromUtf8("OpenList"));
        OpenList->setMaximumSize(QSize(36, 36));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Buttons/Icons/load_list.png"), QSize(), QIcon::Normal, QIcon::Off);
        OpenList->setIcon(icon2);
        OpenList->setIconSize(QSize(32, 32));
        OpenList->setAutoRaise(true);

        horizontalLayout->addWidget(OpenList);

        line_2 = new QFrame(frame);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        GenerateAll = new QToolButton(frame);
        GenerateAll->setObjectName(QString::fromUtf8("GenerateAll"));
        GenerateAll->setMaximumSize(QSize(36, 36));
        GenerateAll->setIcon(icon);
        GenerateAll->setIconSize(QSize(32, 32));
        GenerateAll->setAutoRaise(true);

        horizontalLayout->addWidget(GenerateAll);

        line_3 = new QFrame(frame);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_3);

        Help = new QToolButton(frame);
        Help->setObjectName(QString::fromUtf8("Help"));
        Help->setMaximumSize(QSize(36, 36));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Buttons/Icons/help-browser.png"), QSize(), QIcon::Normal, QIcon::Off);
        Help->setIcon(icon3);
        Help->setIconSize(QSize(32, 32));
        Help->setAutoRaise(true);

        horizontalLayout->addWidget(Help);

        About = new QToolButton(frame);
        About->setObjectName(QString::fromUtf8("About"));
        About->setMinimumSize(QSize(36, 36));
        About->setMaximumSize(QSize(36, 36));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Buttons/Icons/info-browser.png"), QSize(), QIcon::Normal, QIcon::Off);
        About->setIcon(icon4);
        About->setIconSize(QSize(32, 32));
        About->setAutoRaise(true);

        horizontalLayout->addWidget(About);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(frame);

        NormalList = new QListWidget(NormalMapList);
        NormalList->setObjectName(QString::fromUtf8("NormalList"));

        verticalLayout->addWidget(NormalList);

        frame_2 = new QFrame(NormalMapList);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy1);
        frame_2->setMinimumSize(QSize(0, 0));
        frame_2->setMaximumSize(QSize(10000, 1000));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setSpacing(1);
        horizontalLayout_2->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        Add = new QToolButton(frame_2);
        Add->setObjectName(QString::fromUtf8("Add"));
        Add->setMaximumSize(QSize(36, 36));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Buttons/Icons/list-add-green.png"), QSize(), QIcon::Normal, QIcon::Off);
        Add->setIcon(icon5);
        Add->setIconSize(QSize(32, 32));
        Add->setAutoRaise(true);

        horizontalLayout_2->addWidget(Add);

        Remove = new QToolButton(frame_2);
        Remove->setObjectName(QString::fromUtf8("Remove"));
        Remove->setMaximumSize(QSize(36, 36));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Buttons/Icons/list-remove-red.png"), QSize(), QIcon::Normal, QIcon::Off);
        Remove->setIcon(icon6);
        Remove->setIconSize(QSize(32, 32));
        Remove->setAutoRaise(true);

        horizontalLayout_2->addWidget(Remove);

        line = new QFrame(frame_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line);

        GenerateSelected = new QToolButton(frame_2);
        GenerateSelected->setObjectName(QString::fromUtf8("GenerateSelected"));
        GenerateSelected->setMaximumSize(QSize(36, 36));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Buttons/Icons/media-floppy.png"), QSize(), QIcon::Normal, QIcon::Off);
        GenerateSelected->setIcon(icon7);
        GenerateSelected->setIconSize(QSize(32, 32));
        GenerateSelected->setAutoRaise(true);

        horizontalLayout_2->addWidget(GenerateSelected);

        EditButton = new QToolButton(frame_2);
        EditButton->setObjectName(QString::fromUtf8("EditButton"));
        EditButton->setMaximumSize(QSize(36, 36));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Buttons/Icons/document-properties.png"), QSize(), QIcon::Normal, QIcon::Off);
        EditButton->setIcon(icon8);
        EditButton->setIconSize(QSize(32, 32));
        EditButton->setAutoRaise(true);

        horizontalLayout_2->addWidget(EditButton);

        horizontalSpacer_2 = new QSpacerItem(136, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(frame_2);


        retranslateUi(NormalMapList);

        QMetaObject::connectSlotsByName(NormalMapList);
    } // setupUi

    void retranslateUi(QDialog *NormalMapList)
    {
        NormalMapList->setWindowTitle(QApplication::translate("NormalMapList", "Normal Maps", 0, QApplication::UnicodeUTF8));
        SaveList->setText(QApplication::translate("NormalMapList", "...", 0, QApplication::UnicodeUTF8));
        OpenList->setText(QApplication::translate("NormalMapList", "...", 0, QApplication::UnicodeUTF8));
        GenerateAll->setText(QApplication::translate("NormalMapList", "...", 0, QApplication::UnicodeUTF8));
        Help->setText(QApplication::translate("NormalMapList", "...", 0, QApplication::UnicodeUTF8));
        About->setText(QApplication::translate("NormalMapList", "...", 0, QApplication::UnicodeUTF8));
        Add->setText(QApplication::translate("NormalMapList", "...", 0, QApplication::UnicodeUTF8));
        Remove->setText(QApplication::translate("NormalMapList", "...", 0, QApplication::UnicodeUTF8));
        GenerateSelected->setText(QApplication::translate("NormalMapList", "...", 0, QApplication::UnicodeUTF8));
        EditButton->setText(QApplication::translate("NormalMapList", "...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NormalMapList: public Ui_NormalMapList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NORMALMAPLIST_H
