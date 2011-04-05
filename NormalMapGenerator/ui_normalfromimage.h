/********************************************************************************
** Form generated from reading UI file 'normalfromimage.ui'
**
** Created: Mon Apr 19 14:25:15 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NORMALFROMIMAGE_H
#define UI_NORMALFROMIMAGE_H

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
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NormalFromImage
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QLineEdit *LayerName;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_4;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_7;
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
    QSlider *ScaleSlider;
    QLabel *label_3;
    QSlider *BlurSlider;
    QDoubleSpinBox *BlurValue;
    QLabel *label_4;
    QSlider *BilateralSlider;
    QDoubleSpinBox *BilateralValue;
    QDoubleSpinBox *ScaleValue;
    QLineEdit *ImageName;
    QToolButton *LoadImage;
    QLabel *label_5;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *NormalFromImage)
    {
        if (NormalFromImage->objectName().isEmpty())
            NormalFromImage->setObjectName(QString::fromUtf8("NormalFromImage"));
        NormalFromImage->resize(374, 365);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NormalFromImage->sizePolicy().hasHeightForWidth());
        NormalFromImage->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(NormalFromImage);
        verticalLayout_2->setContentsMargins(1, 1, 1, 1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_4 = new QGroupBox(NormalFromImage);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_3 = new QVBoxLayout(groupBox_4);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame_3 = new QFrame(groupBox_4);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_3);
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_6 = new QLabel(frame_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout->addWidget(label_6);

        LayerName = new QLineEdit(frame_3);
        LayerName->setObjectName(QString::fromUtf8("LayerName"));

        horizontalLayout->addWidget(LayerName);


        verticalLayout_3->addWidget(frame_3);

        groupBox_5 = new QGroupBox(groupBox_4);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy1);
        verticalLayout_4 = new QVBoxLayout(groupBox_5);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(8, -1, 8, -1);
        frame_5 = new QFrame(groupBox_5);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setFrameShape(QFrame::NoFrame);
        frame_5->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_5);
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        label_7 = new QLabel(frame_5);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(label_7);

        BlendMode = new QComboBox(frame_5);
        BlendMode->setObjectName(QString::fromUtf8("BlendMode"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(BlendMode->sizePolicy().hasHeightForWidth());
        BlendMode->setSizePolicy(sizePolicy3);
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

        frame_6 = new QFrame(groupBox_5);
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
        sizePolicy3.setHeightForWidth(BlendValue->sizePolicy().hasHeightForWidth());
        BlendValue->setSizePolicy(sizePolicy3);
        BlendValue->setDecimals(1);
        BlendValue->setValue(100);

        horizontalLayout_5->addWidget(BlendValue);


        verticalLayout_4->addWidget(frame_6);


        verticalLayout_3->addWidget(groupBox_5);

        groupBox_3 = new QGroupBox(groupBox_4);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy4);
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy5);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        ScaleSlider = new QSlider(groupBox_3);
        ScaleSlider->setObjectName(QString::fromUtf8("ScaleSlider"));
        ScaleSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(ScaleSlider, 1, 1, 1, 2);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy5.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy5);
        label_3->setWordWrap(false);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        BlurSlider = new QSlider(groupBox_3);
        BlurSlider->setObjectName(QString::fromUtf8("BlurSlider"));
        BlurSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(BlurSlider, 2, 1, 1, 2);

        BlurValue = new QDoubleSpinBox(groupBox_3);
        BlurValue->setObjectName(QString::fromUtf8("BlurValue"));
        QSizePolicy sizePolicy6(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(BlurValue->sizePolicy().hasHeightForWidth());
        BlurValue->setSizePolicy(sizePolicy6);

        gridLayout->addWidget(BlurValue, 2, 3, 1, 1);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy5.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy5);

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        BilateralSlider = new QSlider(groupBox_3);
        BilateralSlider->setObjectName(QString::fromUtf8("BilateralSlider"));
        BilateralSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(BilateralSlider, 3, 1, 1, 2);

        BilateralValue = new QDoubleSpinBox(groupBox_3);
        BilateralValue->setObjectName(QString::fromUtf8("BilateralValue"));
        sizePolicy6.setHeightForWidth(BilateralValue->sizePolicy().hasHeightForWidth());
        BilateralValue->setSizePolicy(sizePolicy6);

        gridLayout->addWidget(BilateralValue, 3, 3, 1, 1);

        ScaleValue = new QDoubleSpinBox(groupBox_3);
        ScaleValue->setObjectName(QString::fromUtf8("ScaleValue"));
        sizePolicy6.setHeightForWidth(ScaleValue->sizePolicy().hasHeightForWidth());
        ScaleValue->setSizePolicy(sizePolicy6);
        ScaleValue->setMinimum(1);

        gridLayout->addWidget(ScaleValue, 1, 3, 1, 1);

        ImageName = new QLineEdit(groupBox_3);
        ImageName->setObjectName(QString::fromUtf8("ImageName"));
        sizePolicy1.setHeightForWidth(ImageName->sizePolicy().hasHeightForWidth());
        ImageName->setSizePolicy(sizePolicy1);
        ImageName->setCursor(QCursor(Qt::ArrowCursor));
        ImageName->setFrame(true);
        ImageName->setReadOnly(true);

        gridLayout->addWidget(ImageName, 0, 1, 1, 2);

        LoadImage = new QToolButton(groupBox_3);
        LoadImage->setObjectName(QString::fromUtf8("LoadImage"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Buttons/Icons/folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        LoadImage->setIcon(icon);

        gridLayout->addWidget(LoadImage, 0, 3, 1, 1);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy5.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy5);

        gridLayout->addWidget(label_5, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_3);


        verticalLayout_2->addWidget(groupBox_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(NormalFromImage);

        QMetaObject::connectSlotsByName(NormalFromImage);
    } // setupUi

    void retranslateUi(QWidget *NormalFromImage)
    {
        NormalFromImage->setWindowTitle(QApplication::translate("NormalFromImage", "Form", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("NormalFromImage", "Layer Settings", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("NormalFromImage", "Layer\n"
"Name", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("NormalFromImage", "Blend Settings", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("NormalFromImage", "Mode:", 0, QApplication::UnicodeUTF8));
        BlendMode->clear();
        BlendMode->insertItems(0, QStringList()
         << QApplication::translate("NormalFromImage", "Additive", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("NormalFromImage", "Overlay", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("NormalFromImage", "Multiply", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("NormalFromImage", "Normal", 0, QApplication::UnicodeUTF8)
        );
        Invert->setText(QApplication::translate("NormalFromImage", "Invert Before Blend", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("NormalFromImage", "Height Map Settings", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NormalFromImage", "Scale", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NormalFromImage", "Gaussian\n"
"Blur", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("NormalFromImage", "Bilateral\n"
"Filter", 0, QApplication::UnicodeUTF8));
        LoadImage->setText(QApplication::translate("NormalFromImage", "...", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("NormalFromImage", "Image", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NormalFromImage: public Ui_NormalFromImage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NORMALFROMIMAGE_H
