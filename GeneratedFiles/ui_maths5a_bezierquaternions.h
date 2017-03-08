/********************************************************************************
** Form generated from reading UI file 'maths5a_bezierquaternions.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATHS5A_BEZIERQUATERNIONS_H
#define UI_MATHS5A_BEZIERQUATERNIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_math5a_bezierForm
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *centralLayout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupMode;
    QGridLayout *gridLayout;
    QPushButton *bResetData;
    QLabel *laTimeCalcSurface;
    QCheckBox *cbShowTexture;
    QCheckBox *cbShowPoints;
    QCheckBox *cbShowGrid;
    QGroupBox *groupLight;
    QGridLayout *gridLayout_2;
    QCheckBox *cbDiffuse;
    QPushButton *bColorS1;
    QCheckBox *cbSpecular;
    QCheckBox *cbLight1;
    QPushButton *bColorS2;
    QCheckBox *cbLight2;
    QPushButton *bColorObj;
    QGroupBox *groupRotation;
    QGridLayout *gridLayout_3;
    QDoubleSpinBox *spinZ;
    QDoubleSpinBox *spinY;
    QDoubleSpinBox *spinX;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QRadioButton *rbRotObj;
    QRadioButton *rbRotCam;
    QSpacerItem *verticalSpacer;
    QPushButton *bResetCam;
    QPushButton *bQuit;

    void setupUi(QMainWindow *math5a_bezierForm)
    {
        if (math5a_bezierForm->objectName().isEmpty())
            math5a_bezierForm->setObjectName(QStringLiteral("math5a_bezierForm"));
        math5a_bezierForm->resize(1129, 796);
        centralWidget = new QWidget(math5a_bezierForm);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        centralLayout = new QHBoxLayout();
        centralLayout->setSpacing(6);
        centralLayout->setObjectName(QStringLiteral("centralLayout"));

        horizontalLayout_2->addLayout(centralLayout);

        math5a_bezierForm->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(math5a_bezierForm);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1129, 21));
        math5a_bezierForm->setMenuBar(menuBar);
        mainToolBar = new QToolBar(math5a_bezierForm);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        math5a_bezierForm->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(math5a_bezierForm);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        math5a_bezierForm->setStatusBar(statusBar);
        dockWidget = new QDockWidget(math5a_bezierForm);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupMode = new QGroupBox(dockWidgetContents);
        groupMode->setObjectName(QStringLiteral("groupMode"));
        gridLayout = new QGridLayout(groupMode);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        bResetData = new QPushButton(groupMode);
        bResetData->setObjectName(QStringLiteral("bResetData"));

        gridLayout->addWidget(bResetData, 6, 1, 1, 2);

        laTimeCalcSurface = new QLabel(groupMode);
        laTimeCalcSurface->setObjectName(QStringLiteral("laTimeCalcSurface"));
        laTimeCalcSurface->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(laTimeCalcSurface, 5, 1, 1, 2);


        verticalLayout_2->addWidget(groupMode);

        cbShowTexture = new QCheckBox(dockWidgetContents);
        cbShowTexture->setObjectName(QStringLiteral("cbShowTexture"));

        verticalLayout_2->addWidget(cbShowTexture);

        cbShowPoints = new QCheckBox(dockWidgetContents);
        cbShowPoints->setObjectName(QStringLiteral("cbShowPoints"));

        verticalLayout_2->addWidget(cbShowPoints);

        cbShowGrid = new QCheckBox(dockWidgetContents);
        cbShowGrid->setObjectName(QStringLiteral("cbShowGrid"));

        verticalLayout_2->addWidget(cbShowGrid);

        groupLight = new QGroupBox(dockWidgetContents);
        groupLight->setObjectName(QStringLiteral("groupLight"));
        gridLayout_2 = new QGridLayout(groupLight);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        cbDiffuse = new QCheckBox(groupLight);
        cbDiffuse->setObjectName(QStringLiteral("cbDiffuse"));

        gridLayout_2->addWidget(cbDiffuse, 6, 0, 1, 1);

        bColorS1 = new QPushButton(groupLight);
        bColorS1->setObjectName(QStringLiteral("bColorS1"));

        gridLayout_2->addWidget(bColorS1, 1, 1, 1, 1);

        cbSpecular = new QCheckBox(groupLight);
        cbSpecular->setObjectName(QStringLiteral("cbSpecular"));

        gridLayout_2->addWidget(cbSpecular, 6, 1, 1, 1);

        cbLight1 = new QCheckBox(groupLight);
        cbLight1->setObjectName(QStringLiteral("cbLight1"));

        gridLayout_2->addWidget(cbLight1, 1, 0, 1, 1);

        bColorS2 = new QPushButton(groupLight);
        bColorS2->setObjectName(QStringLiteral("bColorS2"));
        bColorS2->setLayoutDirection(Qt::LeftToRight);

        gridLayout_2->addWidget(bColorS2, 3, 1, 1, 1);

        cbLight2 = new QCheckBox(groupLight);
        cbLight2->setObjectName(QStringLiteral("cbLight2"));

        gridLayout_2->addWidget(cbLight2, 3, 0, 1, 1);

        bColorObj = new QPushButton(groupLight);
        bColorObj->setObjectName(QStringLiteral("bColorObj"));

        gridLayout_2->addWidget(bColorObj, 0, 0, 1, 2);

        bColorS1->raise();
        bColorS2->raise();
        cbLight1->raise();
        cbLight2->raise();
        cbDiffuse->raise();
        cbSpecular->raise();
        bColorObj->raise();

        verticalLayout_2->addWidget(groupLight);

        groupRotation = new QGroupBox(dockWidgetContents);
        groupRotation->setObjectName(QStringLiteral("groupRotation"));
        gridLayout_3 = new QGridLayout(groupRotation);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        spinZ = new QDoubleSpinBox(groupRotation);
        spinZ->setObjectName(QStringLiteral("spinZ"));
        spinZ->setDecimals(1);
        spinZ->setMaximum(359.9);
        spinZ->setSingleStep(1);

        gridLayout_3->addWidget(spinZ, 3, 1, 1, 1);

        spinY = new QDoubleSpinBox(groupRotation);
        spinY->setObjectName(QStringLiteral("spinY"));
        spinY->setDecimals(1);
        spinY->setMaximum(359.9);
        spinY->setSingleStep(1);

        gridLayout_3->addWidget(spinY, 2, 1, 1, 1);

        spinX = new QDoubleSpinBox(groupRotation);
        spinX->setObjectName(QStringLiteral("spinX"));
        spinX->setDecimals(1);
        spinX->setMaximum(359.9);
        spinX->setSingleStep(1);

        gridLayout_3->addWidget(spinX, 1, 1, 1, 1);

        label_2 = new QLabel(groupRotation);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(groupRotation);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_3->addWidget(label_3, 2, 0, 1, 1);

        label_4 = new QLabel(groupRotation);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_3->addWidget(label_4, 3, 0, 1, 1);

        rbRotObj = new QRadioButton(groupRotation);
        rbRotObj->setObjectName(QStringLiteral("rbRotObj"));
        rbRotObj->setChecked(true);

        gridLayout_3->addWidget(rbRotObj, 0, 0, 1, 1);

        rbRotCam = new QRadioButton(groupRotation);
        rbRotCam->setObjectName(QStringLiteral("rbRotCam"));

        gridLayout_3->addWidget(rbRotCam, 0, 1, 1, 1);


        verticalLayout_2->addWidget(groupRotation);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        bResetCam = new QPushButton(dockWidgetContents);
        bResetCam->setObjectName(QStringLiteral("bResetCam"));
        bResetCam->setCheckable(false);

        verticalLayout_2->addWidget(bResetCam);

        bQuit = new QPushButton(dockWidgetContents);
        bQuit->setObjectName(QStringLiteral("bQuit"));

        verticalLayout_2->addWidget(bQuit);

        dockWidget->setWidget(dockWidgetContents);
        math5a_bezierForm->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);

        retranslateUi(math5a_bezierForm);

        QMetaObject::connectSlotsByName(math5a_bezierForm);
    } // setupUi

    void retranslateUi(QMainWindow *math5a_bezierForm)
    {
        math5a_bezierForm->setWindowTitle(QApplication::translate("math5a_bezierForm", "Fractales 3D - ESGI", 0));
        dockWidget->setWindowTitle(QApplication::translate("math5a_bezierForm", "Configuration", 0));
        groupMode->setTitle(QApplication::translate("math5a_bezierForm", "Mode de g\303\251n\303\251ration des points", 0));
        bResetData->setText(QApplication::translate("math5a_bezierForm", "R\303\251initialiser les donn\303\251es", 0));
        laTimeCalcSurface->setText(QApplication::translate("math5a_bezierForm", "0 us", 0));
        cbShowTexture->setText(QApplication::translate("math5a_bezierForm", "Texture", 0));
        cbShowPoints->setText(QApplication::translate("math5a_bezierForm", "Afficher les points", 0));
        cbShowGrid->setText(QApplication::translate("math5a_bezierForm", "Grille et les axes", 0));
        groupLight->setTitle(QApplication::translate("math5a_bezierForm", "Lumi\303\250res", 0));
        cbDiffuse->setText(QApplication::translate("math5a_bezierForm", "Diffuse", 0));
        bColorS1->setText(QString());
        cbSpecular->setText(QApplication::translate("math5a_bezierForm", "Specular", 0));
        cbLight1->setText(QApplication::translate("math5a_bezierForm", "Source 1", 0));
        bColorS2->setText(QString());
        cbLight2->setText(QApplication::translate("math5a_bezierForm", "Source 2", 0));
        bColorObj->setText(QApplication::translate("math5a_bezierForm", "Couleur du patch", 0));
        groupRotation->setTitle(QApplication::translate("math5a_bezierForm", "Rotation", 0));
        label_2->setText(QApplication::translate("math5a_bezierForm", "X", 0));
        label_3->setText(QApplication::translate("math5a_bezierForm", "Y", 0));
        label_4->setText(QApplication::translate("math5a_bezierForm", "Z", 0));
        rbRotObj->setText(QApplication::translate("math5a_bezierForm", "Objet", 0));
        rbRotCam->setText(QApplication::translate("math5a_bezierForm", "Cam\303\251ra", 0));
        bResetCam->setText(QApplication::translate("math5a_bezierForm", "R\303\251initialiser le cam\303\251ra", 0));
        bQuit->setText(QApplication::translate("math5a_bezierForm", "Quitter", 0));
    } // retranslateUi

};

namespace Ui {
    class math5a_bezierForm: public Ui_math5a_bezierForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATHS5A_BEZIERQUATERNIONS_H
