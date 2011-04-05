/********************************************************************************
** Form generated from reading UI file 'normalmapsettings.ui'
**
** Created: Mon Apr 19 14:25:15 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NORMALMAPSETTINGS_H
#define UI_NORMALMAPSETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NormalMapSettings
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QListWidget *LayerList;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *Add;
    QToolButton *Remove;
    QFrame *line;
    QToolButton *PreviewSelected;
    QToolButton *PreviewAll;
    QFrame *line_2;
    QToolButton *LayerUp;
    QToolButton *LayerDown;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame_4;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QLineEdit *NormalName;
    QFrame *frame_7;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QSlider *IntensitySlider;
    QDoubleSpinBox *IntensityValue;
    QFrame *frame_8;
    QHBoxLayout *horizontalLayout_8;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QSpinBox *Width;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_4;
    QSpinBox *Height;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_9;
    QCheckBox *InvertX;
    QCheckBox *InvertY;
    QSpacerItem *horizontalSpacer_3;
    QFrame *WidgetFrame;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *Ok;
    QPushButton *Cancel;

    void setupUi(QDialog *NormalMapSettings)
    {
        if (NormalMapSettings->objectName().isEmpty())
            NormalMapSettings->setObjectName(QString::fromUtf8("NormalMapSettings"));
        NormalMapSettings->resize(570, 570);
        NormalMapSettings->setMinimumSize(QSize(570, 570));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Buttons/Icons/GenetateNormal.png"), QSize(), QIcon::Normal, QIcon::Off);
        NormalMapSettings->setWindowIcon(icon);
        horizontalLayout = new QHBoxLayout(NormalMapSettings);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        frame = new QFrame(NormalMapSettings);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMaximumSize(QSize(240, 16777215));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(1);
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        LayerList = new QListWidget(frame);
        LayerList->setObjectName(QString::fromUtf8("LayerList"));

        verticalLayout->addWidget(LayerList);

        frame_3 = new QFrame(frame);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy1);
        frame_3->setMinimumSize(QSize(230, 32));
        frame_3->setMaximumSize(QSize(260, 16777215));
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_3);
        horizontalLayout_4->setSpacing(1);
        horizontalLayout_4->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        Add = new QToolButton(frame_3);
        Add->setObjectName(QString::fromUtf8("Add"));
        Add->setMaximumSize(QSize(36, 36));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Buttons/Icons/list-add-green.png"), QSize(), QIcon::Normal, QIcon::Off);
        Add->setIcon(icon1);
        Add->setIconSize(QSize(32, 32));
        Add->setPopupMode(QToolButton::DelayedPopup);
        Add->setAutoRaise(true);

        horizontalLayout_4->addWidget(Add);

        Remove = new QToolButton(frame_3);
        Remove->setObjectName(QString::fromUtf8("Remove"));
        Remove->setMaximumSize(QSize(36, 36));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Buttons/Icons/list-remove-red.png"), QSize(), QIcon::Normal, QIcon::Off);
        Remove->setIcon(icon2);
        Remove->setIconSize(QSize(32, 32));
        Remove->setAutoRaise(true);

        horizontalLayout_4->addWidget(Remove);

        line = new QFrame(frame_3);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line);

        PreviewSelected = new QToolButton(frame_3);
        PreviewSelected->setObjectName(QString::fromUtf8("PreviewSelected"));
        PreviewSelected->setMaximumSize(QSize(36, 36));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Buttons/Icons/Preview2.png"), QSize(), QIcon::Normal, QIcon::Off);
        PreviewSelected->setIcon(icon3);
        PreviewSelected->setIconSize(QSize(32, 32));
        PreviewSelected->setAutoRaise(true);
        PreviewSelected->setArrowType(Qt::NoArrow);

        horizontalLayout_4->addWidget(PreviewSelected);

        PreviewAll = new QToolButton(frame_3);
        PreviewAll->setObjectName(QString::fromUtf8("PreviewAll"));
        PreviewAll->setMaximumSize(QSize(36, 36));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Buttons/Icons/PreviewAll2.png"), QSize(), QIcon::Normal, QIcon::Off);
        PreviewAll->setIcon(icon4);
        PreviewAll->setIconSize(QSize(32, 32));
        PreviewAll->setAutoRaise(true);

        horizontalLayout_4->addWidget(PreviewAll);

        line_2 = new QFrame(frame_3);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line_2);

        LayerUp = new QToolButton(frame_3);
        LayerUp->setObjectName(QString::fromUtf8("LayerUp"));
        LayerUp->setMaximumSize(QSize(36, 36));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Buttons/Icons/go-up-blue.png"), QSize(), QIcon::Normal, QIcon::Off);
        LayerUp->setIcon(icon5);
        LayerUp->setIconSize(QSize(32, 32));
        LayerUp->setAutoRaise(true);

        horizontalLayout_4->addWidget(LayerUp);

        LayerDown = new QToolButton(frame_3);
        LayerDown->setObjectName(QString::fromUtf8("LayerDown"));
        LayerDown->setMinimumSize(QSize(36, 0));
        LayerDown->setMaximumSize(QSize(36, 36));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Buttons/Icons/go-down-blue.png"), QSize(), QIcon::Normal, QIcon::Off);
        LayerDown->setIcon(icon6);
        LayerDown->setIconSize(QSize(32, 32));
        LayerDown->setAutoRaise(true);

        horizontalLayout_4->addWidget(LayerDown);


        verticalLayout->addWidget(frame_3);


        horizontalLayout->addWidget(frame);

        frame_2 = new QFrame(NormalMapSettings);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMinimumSize(QSize(240, 0));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setContentsMargins(1, 1, 1, 1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        frame_4 = new QFrame(frame_2);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy2);
        frame_4->setFrameShape(QFrame::NoFrame);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_4);
        gridLayout->setContentsMargins(1, 1, 1, 1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(frame_4);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
#ifndef Q_OS_MAC
        verticalLayout_3->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        verticalLayout_3->setContentsMargins(9, 9, 9, 9);
#endif
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame_6 = new QFrame(groupBox);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setFrameShape(QFrame::NoFrame);
        frame_6->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_6);
        horizontalLayout_5->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label = new QLabel(frame_6);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_5->addWidget(label);

        NormalName = new QLineEdit(frame_6);
        NormalName->setObjectName(QString::fromUtf8("NormalName"));

        horizontalLayout_5->addWidget(NormalName);


        verticalLayout_3->addWidget(frame_6);

        frame_7 = new QFrame(groupBox);
        frame_7->setObjectName(QString::fromUtf8("frame_7"));
        frame_7->setFrameShape(QFrame::NoFrame);
        frame_7->setFrameShadow(QFrame::Raised);
        horizontalLayout_6 = new QHBoxLayout(frame_7);
        horizontalLayout_6->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_2 = new QLabel(frame_7);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_6->addWidget(label_2);

        IntensitySlider = new QSlider(frame_7);
        IntensitySlider->setObjectName(QString::fromUtf8("IntensitySlider"));
        IntensitySlider->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(IntensitySlider);

        IntensityValue = new QDoubleSpinBox(frame_7);
        IntensityValue->setObjectName(QString::fromUtf8("IntensityValue"));

        horizontalLayout_6->addWidget(IntensityValue);


        verticalLayout_3->addWidget(frame_7);

        frame_8 = new QFrame(groupBox);
        frame_8->setObjectName(QString::fromUtf8("frame_8"));
        frame_8->setFrameShape(QFrame::NoFrame);
        frame_8->setFrameShadow(QFrame::Raised);
        horizontalLayout_8 = new QHBoxLayout(frame_8);
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        groupBox_2 = new QGroupBox(frame_8);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_7 = new QHBoxLayout(groupBox_2);
        horizontalLayout_7->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_7->addWidget(label_3);

        Width = new QSpinBox(groupBox_2);
        Width->setObjectName(QString::fromUtf8("Width"));
        Width->setMinimum(1);
        Width->setMaximum(20000);

        horizontalLayout_7->addWidget(Width);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_7->addWidget(label_4);

        Height = new QSpinBox(groupBox_2);
        Height->setObjectName(QString::fromUtf8("Height"));
        Height->setMinimum(1);
        Height->setMaximum(200000);

        horizontalLayout_7->addWidget(Height);


        horizontalLayout_8->addWidget(groupBox_2);

        horizontalSpacer_4 = new QSpacerItem(6, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);

        groupBox_3 = new QGroupBox(frame_8);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout_9 = new QHBoxLayout(groupBox_3);
        horizontalLayout_9->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        InvertX = new QCheckBox(groupBox_3);
        InvertX->setObjectName(QString::fromUtf8("InvertX"));

        horizontalLayout_9->addWidget(InvertX);

        InvertY = new QCheckBox(groupBox_3);
        InvertY->setObjectName(QString::fromUtf8("InvertY"));

        horizontalLayout_9->addWidget(InvertY);


        horizontalLayout_8->addWidget(groupBox_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);


        verticalLayout_3->addWidget(frame_8);


        gridLayout->addWidget(groupBox, 1, 2, 1, 1);


        verticalLayout_2->addWidget(frame_4);

        WidgetFrame = new QFrame(frame_2);
        WidgetFrame->setObjectName(QString::fromUtf8("WidgetFrame"));
        WidgetFrame->setFrameShape(QFrame::NoFrame);
        WidgetFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(WidgetFrame);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));

        verticalLayout_2->addWidget(WidgetFrame);

        frame_5 = new QFrame(frame_2);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setMinimumSize(QSize(0, 38));
        frame_5->setMaximumSize(QSize(16777215, 38));
        frame_5->setSizeIncrement(QSize(0, 0));
        frame_5->setFrameShape(QFrame::NoFrame);
        frame_5->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_5);
        horizontalLayout_2->setSpacing(1);
        horizontalLayout_2->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        Ok = new QPushButton(frame_5);
        Ok->setObjectName(QString::fromUtf8("Ok"));
        sizePolicy1.setHeightForWidth(Ok->sizePolicy().hasHeightForWidth());
        Ok->setSizePolicy(sizePolicy1);
        Ok->setMinimumSize(QSize(0, 23));
        Ok->setMaximumSize(QSize(16777215, 23));

        horizontalLayout_2->addWidget(Ok);

        Cancel = new QPushButton(frame_5);
        Cancel->setObjectName(QString::fromUtf8("Cancel"));
        sizePolicy1.setHeightForWidth(Cancel->sizePolicy().hasHeightForWidth());
        Cancel->setSizePolicy(sizePolicy1);
        Cancel->setMinimumSize(QSize(0, 23));
        Cancel->setMaximumSize(QSize(16777215, 23));

        horizontalLayout_2->addWidget(Cancel);


        verticalLayout_2->addWidget(frame_5);


        horizontalLayout->addWidget(frame_2);


        retranslateUi(NormalMapSettings);

        QMetaObject::connectSlotsByName(NormalMapSettings);
    } // setupUi

    void retranslateUi(QDialog *NormalMapSettings)
    {
        NormalMapSettings->setWindowTitle(QApplication::translate("NormalMapSettings", "Normal Map Settings", 0, QApplication::UnicodeUTF8));
        Add->setText(QApplication::translate("NormalMapSettings", "...", 0, QApplication::UnicodeUTF8));
        Remove->setText(QApplication::translate("NormalMapSettings", "...", 0, QApplication::UnicodeUTF8));
        PreviewSelected->setText(QApplication::translate("NormalMapSettings", "...", 0, QApplication::UnicodeUTF8));
        PreviewAll->setText(QApplication::translate("NormalMapSettings", "...", 0, QApplication::UnicodeUTF8));
        LayerUp->setText(QApplication::translate("NormalMapSettings", "...", 0, QApplication::UnicodeUTF8));
        LayerDown->setText(QApplication::translate("NormalMapSettings", "...", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("NormalMapSettings", "Normal Map Settings", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NormalMapSettings", "Name     ", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NormalMapSettings", "Intensity", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("NormalMapSettings", "Size", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NormalMapSettings", "Width", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("NormalMapSettings", "Height", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("NormalMapSettings", "Invert", 0, QApplication::UnicodeUTF8));
        InvertX->setText(QApplication::translate("NormalMapSettings", "X", 0, QApplication::UnicodeUTF8));
        InvertY->setText(QApplication::translate("NormalMapSettings", "Y", 0, QApplication::UnicodeUTF8));
        Ok->setText(QApplication::translate("NormalMapSettings", "Ok", 0, QApplication::UnicodeUTF8));
        Cancel->setText(QApplication::translate("NormalMapSettings", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NormalMapSettings: public Ui_NormalMapSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NORMALMAPSETTINGS_H
