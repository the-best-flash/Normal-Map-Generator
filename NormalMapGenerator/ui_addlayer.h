/********************************************************************************
** Form generated from reading UI file 'addlayer.ui'
**
** Created: Mon Apr 19 14:25:15 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDLAYER_H
#define UI_ADDLAYER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddLayer
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *FromHeight;
    QRadioButton *FromRGBImage;
    QRadioButton *FromNormalMap;
    QRadioButton *FromGenerator;
    QRadioButton *FromImages;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QPushButton *Ok;
    QPushButton *Cancel;

    void setupUi(QDialog *AddLayer)
    {
        if (AddLayer->objectName().isEmpty())
            AddLayer->setObjectName(QString::fromUtf8("AddLayer"));
        AddLayer->resize(184, 184);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AddLayer->sizePolicy().hasHeightForWidth());
        AddLayer->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(AddLayer);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(AddLayer);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        FromHeight = new QRadioButton(groupBox);
        FromHeight->setObjectName(QString::fromUtf8("FromHeight"));
        FromHeight->setChecked(true);

        verticalLayout_2->addWidget(FromHeight);

        FromRGBImage = new QRadioButton(groupBox);
        FromRGBImage->setObjectName(QString::fromUtf8("FromRGBImage"));

        verticalLayout_2->addWidget(FromRGBImage);

        FromNormalMap = new QRadioButton(groupBox);
        FromNormalMap->setObjectName(QString::fromUtf8("FromNormalMap"));

        verticalLayout_2->addWidget(FromNormalMap);

        FromGenerator = new QRadioButton(groupBox);
        FromGenerator->setObjectName(QString::fromUtf8("FromGenerator"));

        verticalLayout_2->addWidget(FromGenerator);

        FromImages = new QRadioButton(groupBox);
        FromImages->setObjectName(QString::fromUtf8("FromImages"));

        verticalLayout_2->addWidget(FromImages);


        verticalLayout->addWidget(groupBox);

        frame = new QFrame(AddLayer);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
#ifndef Q_OS_MAC
        horizontalLayout->setSpacing(6);
#endif
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Ok = new QPushButton(frame);
        Ok->setObjectName(QString::fromUtf8("Ok"));

        horizontalLayout->addWidget(Ok);

        Cancel = new QPushButton(frame);
        Cancel->setObjectName(QString::fromUtf8("Cancel"));
        Cancel->setDefault(false);
        Cancel->setFlat(false);

        horizontalLayout->addWidget(Cancel);


        verticalLayout->addWidget(frame);


        retranslateUi(AddLayer);

        QMetaObject::connectSlotsByName(AddLayer);
    } // setupUi

    void retranslateUi(QDialog *AddLayer)
    {
        AddLayer->setWindowTitle(QApplication::translate("AddLayer", "New Layer", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("AddLayer", "Layer From:", 0, QApplication::UnicodeUTF8));
        FromHeight->setText(QApplication::translate("AddLayer", "Height Map", 0, QApplication::UnicodeUTF8));
        FromRGBImage->setText(QApplication::translate("AddLayer", "RGB Image", 0, QApplication::UnicodeUTF8));
        FromNormalMap->setText(QApplication::translate("AddLayer", "Existing Normal Map", 0, QApplication::UnicodeUTF8));
        FromGenerator->setText(QApplication::translate("AddLayer", "Normal Map Generator", 0, QApplication::UnicodeUTF8));
        FromImages->setText(QApplication::translate("AddLayer", "Four Images", 0, QApplication::UnicodeUTF8));
        Ok->setText(QApplication::translate("AddLayer", "Ok", 0, QApplication::UnicodeUTF8));
        Cancel->setText(QApplication::translate("AddLayer", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddLayer: public Ui_AddLayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDLAYER_H
