/********************************************************************************
** Form generated from reading UI file 'normalfromgenerator.ui'
**
** Created: Mon Apr 19 14:25:15 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NORMALFROMGENERATOR_H
#define UI_NORMALFROMGENERATOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NormalFromGenerator
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *LayerName;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_4;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_4;
    QComboBox *BlendMode;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *Invert;
    QSpacerItem *horizontalSpacer_5;
    QFrame *frame_6;
    QHBoxLayout *horizontalLayout_5;
    QSlider *BlendSlider;
    QDoubleSpinBox *BlendValue;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QSlider *IntensitySlider;
    QDoubleSpinBox *IntensityValue;
    QLabel *label_5;
    QComboBox *ImageList;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *NormalFromGenerator)
    {
        if (NormalFromGenerator->objectName().isEmpty())
            NormalFromGenerator->setObjectName(QString::fromUtf8("NormalFromGenerator"));
        NormalFromGenerator->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(NormalFromGenerator);
        verticalLayout_2->setContentsMargins(1, 1, 1, 1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(NormalFromGenerator);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame_3 = new QFrame(groupBox);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_3);
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(frame_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        LayerName = new QLineEdit(frame_3);
        LayerName->setObjectName(QString::fromUtf8("LayerName"));

        horizontalLayout->addWidget(LayerName);


        verticalLayout_3->addWidget(frame_3);

        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(groupBox_4);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(8, -1, 8, -1);
        frame_5 = new QFrame(groupBox_4);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setFrameShape(QFrame::NoFrame);
        frame_5->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_5);
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        label_4 = new QLabel(frame_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(label_4);

        BlendMode = new QComboBox(frame_5);
        BlendMode->setObjectName(QString::fromUtf8("BlendMode"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(BlendMode->sizePolicy().hasHeightForWidth());
        BlendMode->setSizePolicy(sizePolicy2);
        BlendMode->setMinimumSize(QSize(100, 0));

        horizontalLayout_4->addWidget(BlendMode);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        Invert = new QCheckBox(frame_5);
        Invert->setObjectName(QString::fromUtf8("Invert"));

        horizontalLayout_4->addWidget(Invert);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        verticalLayout_4->addWidget(frame_5);

        frame_6 = new QFrame(groupBox_4);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setFrameShape(QFrame::NoFrame);
        frame_6->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_6);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(1, 0, 1, 0);
        BlendSlider = new QSlider(frame_6);
        BlendSlider->setObjectName(QString::fromUtf8("BlendSlider"));
        BlendSlider->setMaximum(1000);
        BlendSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(BlendSlider);

        BlendValue = new QDoubleSpinBox(frame_6);
        BlendValue->setObjectName(QString::fromUtf8("BlendValue"));
        sizePolicy2.setHeightForWidth(BlendValue->sizePolicy().hasHeightForWidth());
        BlendValue->setSizePolicy(sizePolicy2);
        BlendValue->setDecimals(1);
        BlendValue->setValue(100);

        horizontalLayout_5->addWidget(BlendValue);


        verticalLayout_4->addWidget(frame_6);


        verticalLayout_3->addWidget(groupBox_4);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy3);
        gridLayout = new QGridLayout(groupBox_3);
#ifndef Q_OS_MAC
        gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        IntensitySlider = new QSlider(groupBox_3);
        IntensitySlider->setObjectName(QString::fromUtf8("IntensitySlider"));
        IntensitySlider->setMinimum(-200);
        IntensitySlider->setMaximum(200);
        IntensitySlider->setValue(100);
        IntensitySlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(IntensitySlider, 1, 1, 1, 2);

        IntensityValue = new QDoubleSpinBox(groupBox_3);
        IntensityValue->setObjectName(QString::fromUtf8("IntensityValue"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(IntensityValue->sizePolicy().hasHeightForWidth());
        IntensityValue->setSizePolicy(sizePolicy5);
        IntensityValue->setMinimum(1);

        gridLayout->addWidget(IntensityValue, 1, 3, 1, 1);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy4.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        ImageList = new QComboBox(groupBox_3);
        ImageList->setObjectName(QString::fromUtf8("ImageList"));
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(ImageList->sizePolicy().hasHeightForWidth());
        ImageList->setSizePolicy(sizePolicy6);

        gridLayout->addWidget(ImageList, 0, 1, 1, 2);


        verticalLayout_3->addWidget(groupBox_3);


        verticalLayout_2->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 56, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(NormalFromGenerator);

        QMetaObject::connectSlotsByName(NormalFromGenerator);
    } // setupUi

    void retranslateUi(QWidget *NormalFromGenerator)
    {
        NormalFromGenerator->setWindowTitle(QApplication::translate("NormalFromGenerator", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("NormalFromGenerator", "LayerSettings", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NormalFromGenerator", "Layer\n"
"Name", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("NormalFromGenerator", "Blend Settings", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("NormalFromGenerator", "Mode:", 0, QApplication::UnicodeUTF8));
        BlendMode->clear();
        BlendMode->insertItems(0, QStringList()
         << QApplication::translate("NormalFromGenerator", "Additive", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("NormalFromGenerator", "Overlay", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("NormalFromGenerator", "Multiply", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("NormalFromGenerator", "Normal", 0, QApplication::UnicodeUTF8)
        );
        Invert->setText(QApplication::translate("NormalFromGenerator", "Invert Before Blend", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("NormalFromGenerator", "Normal Map Settings", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NormalFromGenerator", "Intensity", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("NormalFromGenerator", "Image", 0, QApplication::UnicodeUTF8));
        ImageList->clear();
        ImageList->insertItems(0, QStringList()
         << QApplication::translate("NormalFromGenerator", "NONE", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class NormalFromGenerator: public Ui_NormalFromGenerator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NORMALFROMGENERATOR_H
