/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCharts/QChartView>
#include <QtCharts/chartsnamespace.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QtCharts::QChartView *ignition_chart_exec;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_53;
    QHBoxLayout *horizontalLayout_29;
    QLineEdit *browseEdit_exec;
    QPushButton *browse_button_exec;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *readDevice_button;
    QFrame *signal_display_frame_2;
    QGridLayout *gridLayout_3;
    QHBoxLayout *ignition4_layout_2;
    QLabel *ignition4_title_label_exec;
    QLabel *ignition4_value_label_exec;
    QHBoxLayout *ignition3_layout_2;
    QLabel *ignition3_title_label_exec;
    QLabel *ignition3_value_label_exec;
    QHBoxLayout *ignition6_layout_2;
    QLabel *ignition6_title_label_exec;
    QLabel *ignition6_value_label_exec;
    QHBoxLayout *ignition2_layout_2;
    QLabel *ignition2_title_label_exec;
    QLabel *ignition2_value_label_exec;
    QHBoxLayout *ignition5_layout_2;
    QLabel *ignition5_title_label_exec;
    QLabel *ignition5_value_label_exec;
    QHBoxLayout *ignition1_layout_2;
    QLabel *ignition1_title_label_exec;
    QLabel *ignition1_value_label_exec;
    QHBoxLayout *horizontalLayout_3;
    QLabel *engine_rpm_exec;
    QLabel *engine_rpm_value_exec;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *execution_layout_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_54;
    QHBoxLayout *horizontalLayout_30;
    QLineEdit *browseEdit_save_exec;
    QPushButton *browse_button_save_exec;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *save_button_exec;
    QWidget *tab;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *trace_layout;
    QLabel *select_trace_label;
    QHBoxLayout *trace_browse_layout;
    QLineEdit *browseEdit;
    QPushButton *browse_button;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *execution_layout;
    QHBoxLayout *horizontalLayout;
    QPushButton *execution_button;
    QPushButton *pause_button;
    QGridLayout *execution_rotation_layout;
    QLabel *rotation_freq_label;
    QSpinBox *rotation_freq_counter;
    QFrame *signal_display_frame;
    QGridLayout *gridLayout_2;
    QHBoxLayout *ignition4_layout;
    QLabel *ignition4_title_label;
    QLabel *ignition4_value_label;
    QHBoxLayout *ignition3_layout;
    QLabel *ignition3_title_label;
    QLabel *ignition3_value_label;
    QHBoxLayout *ignition6_layout;
    QLabel *ignition6_title_label;
    QLabel *ignition6_value_label;
    QHBoxLayout *ignition2_layout;
    QLabel *ignition2_title_label;
    QLabel *ignition2_value_label;
    QHBoxLayout *ignition5_layout;
    QLabel *ignition5_title_label;
    QLabel *ignition5_value_label;
    QHBoxLayout *ignition1_layout;
    QLabel *ignition1_title_label;
    QLabel *ignition1_value_label;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QtCharts::QChartView *ignition_chart_trace;
    QWidget *tab_2;
    QPlainTextEdit *plainTextEdit;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1108, 600);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 1121, 601));
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        ignition_chart_exec = new QtCharts::QChartView(tab_3);
        ignition_chart_exec->setObjectName(QStringLiteral("ignition_chart_exec"));
        ignition_chart_exec->setGeometry(QRect(470, 0, 581, 441));
        verticalLayoutWidget_3 = new QWidget(tab_3);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(10, 10, 291, 94));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(10, 10, 10, 10);
        label_53 = new QLabel(verticalLayoutWidget_3);
        label_53->setObjectName(QStringLiteral("label_53"));

        verticalLayout_5->addWidget(label_53);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(6);
        horizontalLayout_29->setObjectName(QStringLiteral("horizontalLayout_29"));
        browseEdit_exec = new QLineEdit(verticalLayoutWidget_3);
        browseEdit_exec->setObjectName(QStringLiteral("browseEdit_exec"));

        horizontalLayout_29->addWidget(browseEdit_exec);

        browse_button_exec = new QPushButton(verticalLayoutWidget_3);
        browse_button_exec->setObjectName(QStringLiteral("browse_button_exec"));

        horizontalLayout_29->addWidget(browse_button_exec);


        verticalLayout_5->addLayout(horizontalLayout_29);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        readDevice_button = new QPushButton(verticalLayoutWidget_3);
        readDevice_button->setObjectName(QStringLiteral("readDevice_button"));

        horizontalLayout_4->addWidget(readDevice_button);


        verticalLayout_5->addLayout(horizontalLayout_4);

        signal_display_frame_2 = new QFrame(tab_3);
        signal_display_frame_2->setObjectName(QStringLiteral("signal_display_frame_2"));
        signal_display_frame_2->setGeometry(QRect(10, 250, 331, 161));
        signal_display_frame_2->setFrameShape(QFrame::Box);
        gridLayout_3 = new QGridLayout(signal_display_frame_2);
        gridLayout_3->setSpacing(5);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(10, 10, 10, 10);
        ignition4_layout_2 = new QHBoxLayout();
        ignition4_layout_2->setSpacing(6);
        ignition4_layout_2->setObjectName(QStringLiteral("ignition4_layout_2"));
        ignition4_title_label_exec = new QLabel(signal_display_frame_2);
        ignition4_title_label_exec->setObjectName(QStringLiteral("ignition4_title_label_exec"));

        ignition4_layout_2->addWidget(ignition4_title_label_exec);

        ignition4_value_label_exec = new QLabel(signal_display_frame_2);
        ignition4_value_label_exec->setObjectName(QStringLiteral("ignition4_value_label_exec"));
        ignition4_value_label_exec->setAlignment(Qt::AlignCenter);

        ignition4_layout_2->addWidget(ignition4_value_label_exec);


        gridLayout_3->addLayout(ignition4_layout_2, 0, 1, 1, 1);

        ignition3_layout_2 = new QHBoxLayout();
        ignition3_layout_2->setSpacing(6);
        ignition3_layout_2->setObjectName(QStringLiteral("ignition3_layout_2"));
        ignition3_title_label_exec = new QLabel(signal_display_frame_2);
        ignition3_title_label_exec->setObjectName(QStringLiteral("ignition3_title_label_exec"));

        ignition3_layout_2->addWidget(ignition3_title_label_exec);

        ignition3_value_label_exec = new QLabel(signal_display_frame_2);
        ignition3_value_label_exec->setObjectName(QStringLiteral("ignition3_value_label_exec"));
        ignition3_value_label_exec->setAlignment(Qt::AlignCenter);

        ignition3_layout_2->addWidget(ignition3_value_label_exec);


        gridLayout_3->addLayout(ignition3_layout_2, 2, 0, 1, 1);

        ignition6_layout_2 = new QHBoxLayout();
        ignition6_layout_2->setSpacing(6);
        ignition6_layout_2->setObjectName(QStringLiteral("ignition6_layout_2"));
        ignition6_title_label_exec = new QLabel(signal_display_frame_2);
        ignition6_title_label_exec->setObjectName(QStringLiteral("ignition6_title_label_exec"));

        ignition6_layout_2->addWidget(ignition6_title_label_exec);

        ignition6_value_label_exec = new QLabel(signal_display_frame_2);
        ignition6_value_label_exec->setObjectName(QStringLiteral("ignition6_value_label_exec"));
        ignition6_value_label_exec->setAlignment(Qt::AlignCenter);

        ignition6_layout_2->addWidget(ignition6_value_label_exec);


        gridLayout_3->addLayout(ignition6_layout_2, 2, 1, 1, 1);

        ignition2_layout_2 = new QHBoxLayout();
        ignition2_layout_2->setSpacing(6);
        ignition2_layout_2->setObjectName(QStringLiteral("ignition2_layout_2"));
        ignition2_title_label_exec = new QLabel(signal_display_frame_2);
        ignition2_title_label_exec->setObjectName(QStringLiteral("ignition2_title_label_exec"));

        ignition2_layout_2->addWidget(ignition2_title_label_exec);

        ignition2_value_label_exec = new QLabel(signal_display_frame_2);
        ignition2_value_label_exec->setObjectName(QStringLiteral("ignition2_value_label_exec"));
        ignition2_value_label_exec->setAlignment(Qt::AlignCenter);

        ignition2_layout_2->addWidget(ignition2_value_label_exec);


        gridLayout_3->addLayout(ignition2_layout_2, 1, 0, 1, 1);

        ignition5_layout_2 = new QHBoxLayout();
        ignition5_layout_2->setSpacing(6);
        ignition5_layout_2->setObjectName(QStringLiteral("ignition5_layout_2"));
        ignition5_title_label_exec = new QLabel(signal_display_frame_2);
        ignition5_title_label_exec->setObjectName(QStringLiteral("ignition5_title_label_exec"));

        ignition5_layout_2->addWidget(ignition5_title_label_exec);

        ignition5_value_label_exec = new QLabel(signal_display_frame_2);
        ignition5_value_label_exec->setObjectName(QStringLiteral("ignition5_value_label_exec"));
        ignition5_value_label_exec->setAlignment(Qt::AlignCenter);

        ignition5_layout_2->addWidget(ignition5_value_label_exec);


        gridLayout_3->addLayout(ignition5_layout_2, 1, 1, 1, 1);

        ignition1_layout_2 = new QHBoxLayout();
        ignition1_layout_2->setSpacing(6);
        ignition1_layout_2->setObjectName(QStringLiteral("ignition1_layout_2"));
        ignition1_title_label_exec = new QLabel(signal_display_frame_2);
        ignition1_title_label_exec->setObjectName(QStringLiteral("ignition1_title_label_exec"));

        ignition1_layout_2->addWidget(ignition1_title_label_exec);

        ignition1_value_label_exec = new QLabel(signal_display_frame_2);
        ignition1_value_label_exec->setObjectName(QStringLiteral("ignition1_value_label_exec"));
        ignition1_value_label_exec->setAlignment(Qt::AlignCenter);

        ignition1_layout_2->addWidget(ignition1_value_label_exec);


        gridLayout_3->addLayout(ignition1_layout_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        engine_rpm_exec = new QLabel(signal_display_frame_2);
        engine_rpm_exec->setObjectName(QStringLiteral("engine_rpm_exec"));

        horizontalLayout_3->addWidget(engine_rpm_exec);

        engine_rpm_value_exec = new QLabel(signal_display_frame_2);
        engine_rpm_value_exec->setObjectName(QStringLiteral("engine_rpm_value_exec"));
        engine_rpm_value_exec->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(engine_rpm_value_exec);


        gridLayout_3->addLayout(horizontalLayout_3, 3, 0, 1, 1);

        verticalLayoutWidget_4 = new QWidget(tab_3);
        verticalLayoutWidget_4->setObjectName(QStringLiteral("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(0, 110, 331, 116));
        execution_layout_2 = new QVBoxLayout(verticalLayoutWidget_4);
        execution_layout_2->setSpacing(6);
        execution_layout_2->setContentsMargins(11, 11, 11, 11);
        execution_layout_2->setObjectName(QStringLiteral("execution_layout_2"));
        execution_layout_2->setContentsMargins(10, 10, 10, 10);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(10, 10, 10, 10);
        label_54 = new QLabel(verticalLayoutWidget_4);
        label_54->setObjectName(QStringLiteral("label_54"));

        verticalLayout_6->addWidget(label_54);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setSpacing(6);
        horizontalLayout_30->setObjectName(QStringLiteral("horizontalLayout_30"));
        browseEdit_save_exec = new QLineEdit(verticalLayoutWidget_4);
        browseEdit_save_exec->setObjectName(QStringLiteral("browseEdit_save_exec"));

        horizontalLayout_30->addWidget(browseEdit_save_exec);

        browse_button_save_exec = new QPushButton(verticalLayoutWidget_4);
        browse_button_save_exec->setObjectName(QStringLiteral("browse_button_save_exec"));

        horizontalLayout_30->addWidget(browse_button_save_exec);


        verticalLayout_6->addLayout(horizontalLayout_30);


        verticalLayout_2->addLayout(verticalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        save_button_exec = new QPushButton(verticalLayoutWidget_4);
        save_button_exec->setObjectName(QStringLiteral("save_button_exec"));

        horizontalLayout_5->addWidget(save_button_exec);


        verticalLayout_2->addLayout(horizontalLayout_5);


        execution_layout_2->addLayout(verticalLayout_2);

        tabWidget->addTab(tab_3, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayoutWidget = new QWidget(tab);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 291, 80));
        trace_layout = new QVBoxLayout(verticalLayoutWidget);
        trace_layout->setSpacing(6);
        trace_layout->setContentsMargins(11, 11, 11, 11);
        trace_layout->setObjectName(QStringLiteral("trace_layout"));
        trace_layout->setContentsMargins(10, 10, 10, 10);
        select_trace_label = new QLabel(verticalLayoutWidget);
        select_trace_label->setObjectName(QStringLiteral("select_trace_label"));

        trace_layout->addWidget(select_trace_label);

        trace_browse_layout = new QHBoxLayout();
        trace_browse_layout->setSpacing(6);
        trace_browse_layout->setObjectName(QStringLiteral("trace_browse_layout"));
        browseEdit = new QLineEdit(verticalLayoutWidget);
        browseEdit->setObjectName(QStringLiteral("browseEdit"));

        trace_browse_layout->addWidget(browseEdit);

        browse_button = new QPushButton(verticalLayoutWidget);
        browse_button->setObjectName(QStringLiteral("browse_button"));

        trace_browse_layout->addWidget(browse_button);


        trace_layout->addLayout(trace_browse_layout);

        verticalLayoutWidget_2 = new QWidget(tab);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 100, 291, 122));
        execution_layout = new QVBoxLayout(verticalLayoutWidget_2);
        execution_layout->setSpacing(6);
        execution_layout->setContentsMargins(11, 11, 11, 11);
        execution_layout->setObjectName(QStringLiteral("execution_layout"));
        execution_layout->setContentsMargins(10, 10, 10, 10);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        execution_button = new QPushButton(verticalLayoutWidget_2);
        execution_button->setObjectName(QStringLiteral("execution_button"));

        horizontalLayout->addWidget(execution_button);

        pause_button = new QPushButton(verticalLayoutWidget_2);
        pause_button->setObjectName(QStringLiteral("pause_button"));

        horizontalLayout->addWidget(pause_button);


        execution_layout->addLayout(horizontalLayout);

        execution_rotation_layout = new QGridLayout();
        execution_rotation_layout->setSpacing(6);
        execution_rotation_layout->setObjectName(QStringLiteral("execution_rotation_layout"));
        rotation_freq_label = new QLabel(verticalLayoutWidget_2);
        rotation_freq_label->setObjectName(QStringLiteral("rotation_freq_label"));
        rotation_freq_label->setWordWrap(true);

        execution_rotation_layout->addWidget(rotation_freq_label, 0, 0, 1, 1);

        rotation_freq_counter = new QSpinBox(verticalLayoutWidget_2);
        rotation_freq_counter->setObjectName(QStringLiteral("rotation_freq_counter"));
        rotation_freq_counter->setMinimum(1);
        rotation_freq_counter->setMaximum(50000);

        execution_rotation_layout->addWidget(rotation_freq_counter, 0, 1, 1, 1);


        execution_layout->addLayout(execution_rotation_layout);

        signal_display_frame = new QFrame(tab);
        signal_display_frame->setObjectName(QStringLiteral("signal_display_frame"));
        signal_display_frame->setGeometry(QRect(10, 240, 331, 141));
        signal_display_frame->setFrameShape(QFrame::Box);
        gridLayout_2 = new QGridLayout(signal_display_frame);
        gridLayout_2->setSpacing(5);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(10, 10, 10, 10);
        ignition4_layout = new QHBoxLayout();
        ignition4_layout->setSpacing(6);
        ignition4_layout->setObjectName(QStringLiteral("ignition4_layout"));
        ignition4_title_label = new QLabel(signal_display_frame);
        ignition4_title_label->setObjectName(QStringLiteral("ignition4_title_label"));

        ignition4_layout->addWidget(ignition4_title_label);

        ignition4_value_label = new QLabel(signal_display_frame);
        ignition4_value_label->setObjectName(QStringLiteral("ignition4_value_label"));
        ignition4_value_label->setAlignment(Qt::AlignCenter);

        ignition4_layout->addWidget(ignition4_value_label);


        gridLayout_2->addLayout(ignition4_layout, 0, 1, 1, 1);

        ignition3_layout = new QHBoxLayout();
        ignition3_layout->setSpacing(6);
        ignition3_layout->setObjectName(QStringLiteral("ignition3_layout"));
        ignition3_title_label = new QLabel(signal_display_frame);
        ignition3_title_label->setObjectName(QStringLiteral("ignition3_title_label"));

        ignition3_layout->addWidget(ignition3_title_label);

        ignition3_value_label = new QLabel(signal_display_frame);
        ignition3_value_label->setObjectName(QStringLiteral("ignition3_value_label"));
        ignition3_value_label->setAlignment(Qt::AlignCenter);

        ignition3_layout->addWidget(ignition3_value_label);


        gridLayout_2->addLayout(ignition3_layout, 2, 0, 1, 1);

        ignition6_layout = new QHBoxLayout();
        ignition6_layout->setSpacing(6);
        ignition6_layout->setObjectName(QStringLiteral("ignition6_layout"));
        ignition6_title_label = new QLabel(signal_display_frame);
        ignition6_title_label->setObjectName(QStringLiteral("ignition6_title_label"));

        ignition6_layout->addWidget(ignition6_title_label);

        ignition6_value_label = new QLabel(signal_display_frame);
        ignition6_value_label->setObjectName(QStringLiteral("ignition6_value_label"));
        ignition6_value_label->setAlignment(Qt::AlignCenter);

        ignition6_layout->addWidget(ignition6_value_label);


        gridLayout_2->addLayout(ignition6_layout, 2, 1, 1, 1);

        ignition2_layout = new QHBoxLayout();
        ignition2_layout->setSpacing(6);
        ignition2_layout->setObjectName(QStringLiteral("ignition2_layout"));
        ignition2_title_label = new QLabel(signal_display_frame);
        ignition2_title_label->setObjectName(QStringLiteral("ignition2_title_label"));

        ignition2_layout->addWidget(ignition2_title_label);

        ignition2_value_label = new QLabel(signal_display_frame);
        ignition2_value_label->setObjectName(QStringLiteral("ignition2_value_label"));
        ignition2_value_label->setAlignment(Qt::AlignCenter);

        ignition2_layout->addWidget(ignition2_value_label);


        gridLayout_2->addLayout(ignition2_layout, 1, 0, 1, 1);

        ignition5_layout = new QHBoxLayout();
        ignition5_layout->setSpacing(6);
        ignition5_layout->setObjectName(QStringLiteral("ignition5_layout"));
        ignition5_title_label = new QLabel(signal_display_frame);
        ignition5_title_label->setObjectName(QStringLiteral("ignition5_title_label"));

        ignition5_layout->addWidget(ignition5_title_label);

        ignition5_value_label = new QLabel(signal_display_frame);
        ignition5_value_label->setObjectName(QStringLiteral("ignition5_value_label"));
        ignition5_value_label->setAlignment(Qt::AlignCenter);

        ignition5_layout->addWidget(ignition5_value_label);


        gridLayout_2->addLayout(ignition5_layout, 1, 1, 1, 1);

        ignition1_layout = new QHBoxLayout();
        ignition1_layout->setSpacing(6);
        ignition1_layout->setObjectName(QStringLiteral("ignition1_layout"));
        ignition1_title_label = new QLabel(signal_display_frame);
        ignition1_title_label->setObjectName(QStringLiteral("ignition1_title_label"));

        ignition1_layout->addWidget(ignition1_title_label);

        ignition1_value_label = new QLabel(signal_display_frame);
        ignition1_value_label->setObjectName(QStringLiteral("ignition1_value_label"));
        ignition1_value_label->setAlignment(Qt::AlignCenter);

        ignition1_layout->addWidget(ignition1_value_label);


        gridLayout_2->addLayout(ignition1_layout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(signal_display_frame);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        label_2 = new QLabel(signal_display_frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_2);


        gridLayout_2->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        ignition_chart_trace = new QtCharts::QChartView(tab);
        ignition_chart_trace->setObjectName(QStringLiteral("ignition_chart_trace"));
        ignition_chart_trace->setGeometry(QRect(410, 20, 681, 501));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        plainTextEdit = new QPlainTextEdit(tab_2);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(20, 30, 1071, 481));
        tabWidget->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_53->setText(QApplication::translate("MainWindow", "Device de la trace", Q_NULLPTR));
        browseEdit_exec->setText(QApplication::translate("MainWindow", "/dev/ttyACM0", Q_NULLPTR));
        browse_button_exec->setText(QApplication::translate("MainWindow", "Parcourir", Q_NULLPTR));
        readDevice_button->setText(QApplication::translate("MainWindow", "Lire", Q_NULLPTR));
        ignition4_title_label_exec->setText(QApplication::translate("MainWindow", "Bougie 4", Q_NULLPTR));
        ignition4_value_label_exec->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        ignition3_title_label_exec->setText(QApplication::translate("MainWindow", "Bougie 3", Q_NULLPTR));
        ignition3_value_label_exec->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        ignition6_title_label_exec->setText(QApplication::translate("MainWindow", "Bougie 6", Q_NULLPTR));
        ignition6_value_label_exec->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        ignition2_title_label_exec->setText(QApplication::translate("MainWindow", "Bougie 2", Q_NULLPTR));
        ignition2_value_label_exec->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        ignition5_title_label_exec->setText(QApplication::translate("MainWindow", "Bougie 5", Q_NULLPTR));
        ignition5_value_label_exec->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        ignition1_title_label_exec->setText(QApplication::translate("MainWindow", "Bougie 1", Q_NULLPTR));
        ignition1_value_label_exec->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        engine_rpm_exec->setText(QApplication::translate("MainWindow", "rpm moteur", Q_NULLPTR));
        engine_rpm_value_exec->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_54->setText(QApplication::translate("MainWindow", "Fichier d'enregistrement de la trace", Q_NULLPTR));
        browseEdit_save_exec->setText(QApplication::translate("MainWindow", "/home/Kappa", Q_NULLPTR));
        browse_button_save_exec->setText(QApplication::translate("MainWindow", "Parcourir", Q_NULLPTR));
        save_button_exec->setText(QApplication::translate("MainWindow", "Commencer l'enregistrement", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Ex\303\251cution courante", Q_NULLPTR));
        select_trace_label->setText(QApplication::translate("MainWindow", "S\303\251lectionner une trace ", Q_NULLPTR));
        browse_button->setText(QApplication::translate("MainWindow", "Parcourir", Q_NULLPTR));
        execution_button->setText(QApplication::translate("MainWindow", "Ex\303\251cuter la trace", Q_NULLPTR));
        pause_button->setText(QApplication::translate("MainWindow", "Pause", Q_NULLPTR));
        rotation_freq_label->setText(QApplication::translate("MainWindow", "Nombre de tours moteur affich\303\251s par seconde", Q_NULLPTR));
        ignition4_title_label->setText(QApplication::translate("MainWindow", "Bougie 4", Q_NULLPTR));
        ignition4_value_label->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        ignition3_title_label->setText(QApplication::translate("MainWindow", "Bougie 3", Q_NULLPTR));
        ignition3_value_label->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        ignition6_title_label->setText(QApplication::translate("MainWindow", "Bougie 6", Q_NULLPTR));
        ignition6_value_label->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        ignition2_title_label->setText(QApplication::translate("MainWindow", "Bougie 2", Q_NULLPTR));
        ignition2_value_label->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        ignition5_title_label->setText(QApplication::translate("MainWindow", "Bougie 5", Q_NULLPTR));
        ignition5_value_label->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        ignition1_title_label->setText(QApplication::translate("MainWindow", "Bougie 1", Q_NULLPTR));
        ignition1_value_label->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "rpm moteur", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Lecture de trace", Q_NULLPTR));
        plainTextEdit->setPlainText(QApplication::translate("MainWindow", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
                        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
                        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
                        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
                        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
                        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
                        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "WCET", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
