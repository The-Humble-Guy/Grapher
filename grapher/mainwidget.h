#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QSpacerItem>
#include <QColorDialog>
#include <QPen>
#include <QMessageBox>
#include <QComboBox>
#include <qcustomplot.h>

#include "function.h"
#include "lexisChecker.h"
#include "syntax_checker.h"

#include <iostream>

#define BASE_START -2
#define BASE_END 2

class MainWidget : public QWidget
{
    Q_OBJECT

private:
    QVector<Function> _functions;

    QLineEdit *_editor;
    QPushButton *_btn_add;
    QPushButton *_btn_remove;
    QRadioButton *_rbtn_visible;
    QPushButton *_btn_view_all;
    QLabel *_fun_name;
    QPushButton *_btn_color;
    QColorDialog *_color;
    QLabel *_label_width;
    QComboBox *_line_width;
    QLabel *_label_linestyle;
    QComboBox *_line_style;
    QLabel *_label_fun_value;
    QLineEdit *_arg_fun_value;
    QLabel *_label_arg;
    QLabel *_label_fun;
    QLabel *_label_value_at_point;


    QCustomPlot *_plot;

    QCPAbstractPlottable *_selected;

    void setUpUI();
    void fillFunctions(double start, double stop);
    void set_selected_graph_params(QCPAbstractPlottable *graph);

public slots:
    void on_value_at_point_selected();
    void on_line_width_select(int width);
    void on_line_style_select(int num);
    void on_btn_view_all_clicked();
    void change_visible();
    void on_btn_add_clicked();
    void on_plot_mouse_move();
    void on_btn_remove_click();
    void on_plot_graph_clicked();
    void on_btn_color_clicked();
    void on_color_select(QColor color);

    void on_select_graph(QCPAbstractPlottable *graph);

    void set_right_part_enable(bool flag);

signals:

    void right_part_visibility(bool);
public:
    MainWidget(QWidget *parent = nullptr);
    void plot();
    ~MainWidget();
};
#endif // MAINWIDGET_H
