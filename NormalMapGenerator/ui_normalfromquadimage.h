/********************************************************************************
** Form generated from reading UI file 'normalfromquadimage.ui'
**
** Created: Mon Apr 19 14:25:15 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NORMALFROMQUADIMAGE_H
#define UI_NORMALFROMQUADIMAGE_H

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
#include <QtGui/QListWidget>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NormalFromQuadImage
{
public:
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QLineEdit *LayerName;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QComboBox *BlendMode;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *Invert;
    QSpacerItem *horizontalSpacer_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QSlider *BlendSlider;
    QDoubleSpinBox *BlendValue;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSlider *IntensitySlider;
    QDoubleSpinBox *IntensityValue;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_5;
    QFrame *frame_6;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_11;
    QLabel *label_10;
    QLabel *label_9;
    QLabel *label_8;
    QSpacerItem *verticalSpacer_2;
    QListWidget *ImageList;
    QFrame *frame_7;
    QVBoxLayout *verticalLayout_6;
    QToolButton *OpenImages;
    QFrame *frame_10;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QSlider *BrightnessSlider;
    QDoubleSpinBox *BrightnessValue;
    QLabel *label_4;
    QSlider *ContrastSlider;
    QDoubleSpinBox *ContrastValue;
    QLabel *label_5;
    QSlider *BlurSlider;
    QDoubleSpinBox *BlurValue;
    QLabel *label_7;
    QSlider *BilateralSlider;
    QDoubleSpinBox *BilateralValue;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *NormalFromQuadImage)
    {
        if (NormalFromQuadImage->objectName().isEmpty())
            NormalFromQuadImage->setObjectName(QString::fromUtf8("NormalFromQuadImage"));
        NormalFromQuadImage->resize(421, 477);
        verticalLayout_4 = new QVBoxLayout(NormalFromQuadImage);
        verticalLayout_4->setContentsMargins(1, 1, 1, 1);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox = new QGroupBox(NormalFromQuadImage);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
#ifndef Q_OS_MAC
        verticalLayout_3->setContentsMargins(9, 9, 9, 9);
#endif
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame_3 = new QFrame(groupBox);
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

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(8, -1, 8, -1);
        frame_2 = new QFrame(groupBox_2);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_2);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        label = new QLabel(frame_2);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label);

        BlendMode = new QComboBox(frame_2);
        BlendMode->setObjectName(QString::fromUtf8("BlendMode"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(BlendMode->sizePolicy().hasHeightForWidth());
        BlendMode->setSizePolicy(sizePolicy2);
        BlendMode->setMinimumSize(QSize(100, 0));

        horizontalLayout_3->addWidget(BlendMode);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        Invert = new QCheckBox(frame_2);
        Invert->setObjectName(QString::fromUtf8("Invert"));

        horizontalLayout_3->addWidget(Invert);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(frame_2);

        frame = new QFrame(groupBox_2);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(1, 0, 1, 0);
        BlendSlider = new QSlider(frame);
        BlendSlider->setObjectName(QString::fromUtf8("BlendSlider"));
        BlendSlider->setMaximum(1000);
        BlendSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(BlendSlider);

        BlendValue = new QDoubleSpinBox(frame);
        BlendValue->setObjectName(QString::fromUtf8("BlendValue"));
        sizePolicy2.setHeightForWidth(BlendValue->sizePolicy().hasHeightForWidth());
        BlendValue->setSizePolicy(sizePolicy2);
        BlendValue->setDecimals(1);
        BlendValue->setValue(100);

        horizontalLayout_2->addWidget(BlendValue);


        verticalLayout->addWidget(frame);


        verticalLayout_3->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        frame_4 = new QFrame(groupBox_3);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setFrameShape(QFrame::NoFrame);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_4);
        horizontalLayout_4->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(frame_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        IntensitySlider = new QSlider(frame_4);
        IntensitySlider->setObjectName(QString::fromUtf8("IntensitySlider"));
        IntensitySlider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(IntensitySlider);

        IntensityValue = new QDoubleSpinBox(frame_4);
        IntensityValue->setObjectName(QString::fromUtf8("IntensityValue"));

        horizontalLayout_4->addWidget(IntensityValue);


        verticalLayout_2->addWidget(frame_4);

        groupBox_5 = new QGroupBox(groupBox_3);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setCheckable(false);
        horizontalLayout_5 = new QHBoxLayout(groupBox_5);
        horizontalLayout_5->setSpacing(1);
        horizontalLayout_5->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        frame_6 = new QFrame(groupBox_5);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setFrameShape(QFrame::NoFrame);
        frame_6->setFrameShadow(QFrame::Raised);
        verticalLayout_5 = new QVBoxLayout(frame_6);
        verticalLayout_5->setContentsMargins(1, 1, 1, 1);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_11 = new QLabel(frame_6);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        verticalLayout_5->addWidget(label_11);

        label_10 = new QLabel(frame_6);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        verticalLayout_5->addWidget(label_10);

        label_9 = new QLabel(frame_6);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout_5->addWidget(label_9);

        label_8 = new QLabel(frame_6);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_5->addWidget(label_8);

        verticalSpacer_2 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);


        horizontalLayout_5->addWidget(frame_6);

        ImageList = new QListWidget(groupBox_5);
        ImageList->setObjectName(QString::fromUtf8("ImageList"));
        ImageList->setMinimumSize(QSize(0, 80));
        ImageList->setMaximumSize(QSize(16777215, 80));
        ImageList->setSelectionMode(QAbstractItemView::NoSelection);

        horizontalLayout_5->addWidget(ImageList);

        frame_7 = new QFrame(groupBox_5);
        frame_7->setObjectName(QString::fromUtf8("frame_7"));
        frame_7->setFrameShape(QFrame::NoFrame);
        frame_7->setFrameShadow(QFrame::Raised);
        verticalLayout_6 = new QVBoxLayout(frame_7);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(6, 1, 1, 1);
        OpenImages = new QToolButton(frame_7);
        OpenImages->setObjectName(QString::fromUtf8("OpenImages"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Buttons/Icons/folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        OpenImages->setIcon(icon);
        OpenImages->setIconSize(QSize(24, 24));

        verticalLayout_6->addWidget(OpenImages);


        horizontalLayout_5->addWidget(frame_7);


        verticalLayout_2->addWidget(groupBox_5);

        frame_10 = new QFrame(groupBox_3);
        frame_10->setObjectName(QString::fromUtf8("frame_10"));
        frame_10->setFrameShape(QFrame::NoFrame);
        frame_10->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_10);
        gridLayout_2->setContentsMargins(1, 1, 1, 1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_3 = new QLabel(frame_10);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        BrightnessSlider = new QSlider(frame_10);
        BrightnessSlider->setObjectName(QString::fromUtf8("BrightnessSlider"));
        BrightnessSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(BrightnessSlider, 0, 1, 1, 1);

        BrightnessValue = new QDoubleSpinBox(frame_10);
        BrightnessValue->setObjectName(QString::fromUtf8("BrightnessValue"));

        gridLayout_2->addWidget(BrightnessValue, 0, 2, 1, 1);

        label_4 = new QLabel(frame_10);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        ContrastSlider = new QSlider(frame_10);
        ContrastSlider->setObjectName(QString::fromUtf8("ContrastSlider"));
        ContrastSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(ContrastSlider, 1, 1, 1, 1);

        ContrastValue = new QDoubleSpinBox(frame_10);
        ContrastValue->setObjectName(QString::fromUtf8("ContrastValue"));

        gridLayout_2->addWidget(ContrastValue, 1, 2, 1, 1);

        label_5 = new QLabel(frame_10);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 2, 0, 1, 1);

        BlurSlider = new QSlider(frame_10);
        BlurSlider->setObjectName(QString::fromUtf8("BlurSlider"));
        BlurSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(BlurSlider, 2, 1, 1, 1);

        BlurValue = new QDoubleSpinBox(frame_10);
        BlurValue->setObjectName(QString::fromUtf8("BlurValue"));

        gridLayout_2->addWidget(BlurValue, 2, 2, 1, 1);

        label_7 = new QLabel(frame_10);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 3, 0, 1, 1);

        BilateralSlider = new QSlider(frame_10);
        BilateralSlider->setObjectName(QString::fromUtf8("BilateralSlider"));
        BilateralSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(BilateralSlider, 3, 1, 1, 1);

        BilateralValue = new QDoubleSpinBox(frame_10);
        BilateralValue->setObjectName(QString::fromUtf8("BilateralValue"));

        gridLayout_2->addWidget(BilateralValue, 3, 2, 1, 1);


        verticalLayout_2->addWidget(frame_10);


        verticalLayout_3->addWidget(groupBox_3);


        verticalLayout_4->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        retranslateUi(NormalFromQuadImage);

        QMetaObject::connectSlotsByName(NormalFromQuadImage);
    } // setupUi

    void retranslateUi(QWidget *NormalFromQuadImage)
    {
        NormalFromQuadImage->setWindowTitle(QApplication::translate("NormalFromQuadImage", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("NormalFromQuadImage", "Layer Settings", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("NormalFromQuadImage", "Layer\n"
"Name", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("NormalFromQuadImage", "Blend Settings", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NormalFromQuadImage", "Mode:", 0, QApplication::UnicodeUTF8));
        BlendMode->clear();
        BlendMode->insertItems(0, QStringList()
         << QApplication::translate("NormalFromQuadImage", "Additive", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("NormalFromQuadImage", "Overlay", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("NormalFromQuadImage", "Multiply", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("NormalFromQuadImage", "Normal", 0, QApplication::UnicodeUTF8)
        );
        Invert->setText(QApplication::translate("NormalFromQuadImage", "Invert Before Blend", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("NormalFromQuadImage", "Image Settings", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NormalFromQuadImage", "Normal\n"
"Intensity", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("NormalFromQuadImage", "Images", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("NormalFromQuadImage", "Left", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("NormalFromQuadImage", "Right", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("NormalFromQuadImage", "Up", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("NormalFromQuadImage", "Down", 0, QApplication::UnicodeUTF8));
        OpenImages->setText(QApplication::translate("NormalFromQuadImage", "...", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NormalFromQuadImage", "Brightness", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("NormalFromQuadImage", "Contrast", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("NormalFromQuadImage", "Gaussina\n"
"Blur", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("NormalFromQuadImage", "Bilateral\n"
"Filter", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NormalFromQuadImage: public Ui_NormalFromQuadImage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NORMALFROMQUADIMAGE_H
