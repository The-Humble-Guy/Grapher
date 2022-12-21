#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    setUpUI();
    // add btn_add click
    connect(this->_btn_add, SIGNAL(pressed()), this, SLOT(on_btn_add_clicked()));
    // if pressed Enter interpet it as btn_add_click
    connect(this->_editor, SIGNAL(returnPressed()), this, SLOT(on_btn_add_clicked()));

    connect(this->_plot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(on_plot_mouse_move()));
    connect(this->_plot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(on_plot_mouse_move()));

    connect(this->_plot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(on_select_graph(QCPAbstractPlottable*)));
    connect(this->_plot, SIGNAL(plottableDoubleClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(on_btn_remove_click()));
    connect(this->_btn_remove, SIGNAL(clicked(bool)), this, SLOT(on_btn_remove_click()));

    connect(this->_rbtn_visible, SIGNAL(clicked(bool)), this, SLOT(change_visible()));

    connect(this, SIGNAL(right_part_visibility(bool)), this, SLOT(set_right_part_enable(bool)));

    connect(this->_btn_color, SIGNAL(clicked(bool)), this, SLOT(on_btn_color_clicked()));

    connect(this->_color, SIGNAL(colorSelected(QColor)), this, SLOT(on_color_select(QColor)));

    connect(this->_btn_view_all, SIGNAL(clicked(bool)), this, SLOT(on_btn_view_all_clicked()));

    connect(this->_line_style, SIGNAL(activated(int)), this, SLOT(on_line_style_select(int)));

    connect(this->_line_width, SIGNAL(activated(int)), this, SLOT(on_line_width_select(int)));

    connect(this->_arg_fun_value, SIGNAL(editingFinished()), this, SLOT(on_value_at_point_selected()));

}

void MainWidget::plot()
{
    for (int i = 0; i < _functions.count(); ++i) {
        _plot->graph(i)->setData(_functions[i].getX(), _functions[i].getY());
    }
    _plot->replot();
}

MainWidget::~MainWidget()
{
}

void MainWidget::setUpUI() {
    _plot = new QCustomPlot(this);
    _editor = new QLineEdit(this);
    _btn_add = new QPushButton("Добавить график", this);
    _btn_remove = new QPushButton("Удалить график", this);
    _rbtn_visible = new QRadioButton("Видимость графика", this);
    _btn_color = new QPushButton("Выбрать цвет", this);
    _color = new QColorDialog(this);
    _fun_name = new QLabel(this);
    _btn_view_all = new QPushButton("Показать все графики", this);
    _label_width = new QLabel("Толщина линии", this);
    _line_width = new QComboBox(this);
    _label_linestyle = new QLabel("Стиль линии", this);
    _line_style = new QComboBox(this);
    _label_fun_value = new QLabel("Значение в точке", this);
    _label_arg = new QLabel("x = ", this);
    _arg_fun_value = new QLineEdit(this);
    _label_fun = new QLabel("y = ", this);
    _label_value_at_point = new QLabel("", this);


    QHBoxLayout *main_layout = new QHBoxLayout(this);
    QVBoxLayout *right_part = new QVBoxLayout();
    QVBoxLayout *left_part = new QVBoxLayout();
    QHBoxLayout *fun_argument = new QHBoxLayout();
    QHBoxLayout *fun_value = new QHBoxLayout();

    fun_argument->addWidget(_label_arg);
    fun_argument->addWidget(_arg_fun_value);

    fun_value->addWidget(_label_fun);
    fun_value->addWidget(_label_value_at_point);

    right_part->addWidget(_editor);
    right_part->addWidget(_fun_name);
    right_part->addWidget(_rbtn_visible);
    right_part->addWidget(_btn_color);
    right_part->addWidget(_label_width);
    right_part->addWidget(_line_width);
    right_part->addWidget(_label_linestyle);
    right_part->addWidget(_line_style);
    right_part->addWidget(_label_fun_value);
    right_part->addLayout(fun_argument);
    right_part->addLayout(fun_value);
    right_part->addWidget(_btn_view_all, 222, Qt::AlignBottom);
    right_part->addWidget(_btn_add, 1, Qt::AlignBottom);
    right_part->addWidget(_btn_remove, 0, Qt::AlignBottom);

    _fun_name->setVisible(false);
    _rbtn_visible->setEnabled(false);

    _btn_add->setMinimumWidth(200);
    _btn_remove->setMinimumWidth(200);
    _btn_remove->setEnabled(false);
    _btn_color->setEnabled(false);
    _label_width->setEnabled(false);
    _label_linestyle->setEnabled(false);
    _label_fun_value->setEnabled(false);
    _label_arg->setEnabled(false);
    _label_fun->setEnabled(false);
    _label_value_at_point->setVisible(true);

    _line_width->addItem("1");
    _line_width->addItem("2");
    _line_width->addItem("3");
    _line_width->addItem("4");
    _line_width->addItem("5");
    _line_width->addItem("6");
    _line_width->addItem("7");
    _line_width->setEnabled(false);

    _line_style->addItem("Сплошная");
    _line_style->addItem("Пунктирная");
    _line_style->addItem("Точками");
    _line_style->setEnabled(false);

    _arg_fun_value->setEnabled(false);
    _label_arg->setMaximumWidth(50);
    _arg_fun_value->setMaximumWidth(340);



    _editor->setFocus();
    _editor->setMaximumWidth(400);
    _editor->setMinimumWidth(200);

    _plot->setMinimumSize(600, 600);

    left_part->addWidget(_plot);

    main_layout->addLayout(left_part);
    main_layout->addLayout(right_part);

    _plot->xAxis->setRange(-2, 2);
    _plot->yAxis->setRange(-2, 2);
    _plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    this->setBaseSize(700, 700);
    this->setWindowTitle("Анализатор математических выражений");
}

void MainWidget::fillFunctions(double start, double stop)
{
    for (int i = 0; i < _functions.count(); ++i) {
        _functions[i].fillValues(start, stop);
    }
}

void MainWidget::set_selected_graph_params(QCPAbstractPlottable *graph)
{
    for (int i = 0; i < _plot->graphCount(); ++i) {
        if (_plot->graph(i)->name() == _selected->name()) {
            _fun_name->setText("Функция: " + _functions[i].getFunctionName());
            if (_plot->graph(i)->pen().width()) _line_width->setCurrentIndex(_plot->graph(i)->pen().width() - 1);
            else _line_width->setCurrentIndex(0);
            switch (_plot->graph(i)->pen().style()) {
            case Qt::SolidLine:
                _line_style->setCurrentIndex(0);
                break;
            case Qt::DashLine:
                _line_style->setCurrentIndex(1);
                break;
            case Qt::DotLine:
                _line_style->setCurrentIndex(2);
                break;
            default:
                break;
            }
        }
    }
}

void MainWidget::on_value_at_point_selected()
{
    std::cout << "зашел в обработчик значения в точке" << std::endl;
    if (!_arg_fun_value->text().isEmpty()) {
    for (int i = 0; i < _plot->graphCount(); ++i) {
        if (_plot->graph(i)->name() == _selected->name()) {
            Lexis_checker checker(Expression(_fun_name->text().toStdString() ,"x"));
            if (checker.isDouble(_arg_fun_value->text().toStdString())) {
                Value val = _functions[i].value(std::stof(_arg_fun_value->text().toStdString()));
                if (val.getStatus() == S_CORRECT) {
                    _label_value_at_point->setText(QString::fromStdString( std::to_string(val.getY())));
                } else {
                    _label_value_at_point->setText("значение не определено");
                }
            } else {
                QMessageBox::warning(this, "Ошибка ввода", "Некорректное значение аргумента");
                this->_arg_fun_value->setFocus();
                _label_fun_value->clear();
            }
        }
    }
    }
}

void MainWidget::on_line_width_select(int width)
{
    QPen pen;
    for (int i = 0; i < _plot->graphCount(); ++i) {
        if (_plot->graph(i)->name() == _selected->name()) {
            pen.setColor(_plot->graph(i)->pen().color());
            pen.setStyle(_plot->graph(i)->pen().style());
            pen.setWidth(width + 1);
            _plot->graph(i)->setPen(pen);
            pen.setWidth(width + 3);
            _plot->graph(i)->selectionDecorator()->setPen(pen);
        }
    }
    plot();
}

void MainWidget::on_line_style_select(int num)
{
    QPen pen;
    pen.setStyle(Qt::DashLine);
    std::cout << "Зашел в обработчик толщины линии" << std::endl;
    for (int i = 0; i < _plot->graphCount(); ++i) {
        if (_plot->graph(i)->name() == _selected->name()) {
            pen.setColor(_plot->graph(i)->pen().color());
            pen.setWidth(_plot->graph(i)->pen().width());
            switch (num) {
            case 0:
                pen.setStyle(Qt::SolidLine);
                _plot->graph(i)->setPen(pen);
                pen.setWidth(pen.width() + 2);
                _plot->graph(i)->selectionDecorator()->setPen(pen);
                break;
            case 1:
                _plot->graph(i)->setPen(pen);
                pen.setWidth(pen.width() + 2);
                _plot->graph(i)->selectionDecorator()->setPen(pen);
                break;
            case 2:
                pen.setStyle(Qt::DotLine);
                _plot->graph(i)->setPen(pen);
                pen.setWidth(pen.width() + 2);
                _plot->graph(i)->selectionDecorator()->setPen(pen);
                break;
            default:
                break;
            }
        }
    }
    plot();
}

void MainWidget::on_btn_view_all_clicked()
{
    for (int i = 0; i < _plot->graphCount(); ++i) {
        _plot->graph(i)->setVisible(true);
    }
    plot();
}


void MainWidget::change_visible()
{
    if (_selected->visible()) _selected->setVisible(false);
    else _selected->setVisible(true);
    plot();
}


void MainWidget::on_btn_add_clicked() {
    std::string input = _editor->text().toStdString();
    Expression temp(input, "x");
    Lexis_checker lexis_check(temp);
    Syntax_checker syntax_check(temp);
    if (!input.empty()) {
        if (lexis_check.isLexisCorrect()) {
            if (syntax_check.isSyntaxCorrect()) {
                _functions.push_back(Function(input, "x"));
                _editor->clear();
                _plot->addGraph();
                std::cout << "вставлена функция " << input << std::endl;
                _editor->setText("");
            } else {
                QMessageBox::warning(this, "Ошибка ввода", "Синтаксическая ошибка в выражении");
                _editor->selectAll();
            }
        } else {
            QMessageBox::warning(this, "Ошибка ввода", "Некорректное имя функции или переменной");
            _editor->selectAll();
        }
    }
    _editor->setFocus();
    on_plot_mouse_move();
    plot();
}


void MainWidget::on_plot_mouse_move()
{
    double start = 0;
    double end = 0;
    if (_plot->graphCount() != 0) {
        start = _plot->graph(0)->keyAxis()->range().lower - 50;
        end = _plot->graph(0)->keyAxis()->range().upper + 50;
    } else {
        start = BASE_START;
        end = BASE_END;
    }
    fillFunctions(start, end);
    plot();
}

void MainWidget::on_btn_remove_click()
{
    std::cout << "Зашел в обработчик remove_click" << std::endl;
    bool finded = false;
    for (int i = 0; i < _plot->graphCount() && !finded; ++i) {
        if (_plot->graph(i)->name() == _selected->name()) {
            finded = true;
            _functions.erase(_functions.cbegin() + i);
            _plot->removeGraph(i);
        }
    }
    emit right_part_visibility(false);
    plot();
}

void MainWidget::on_plot_graph_clicked()
{
}

void MainWidget::on_btn_color_clicked()
{
    _color->open();
}

void MainWidget::on_color_select(QColor color)
{
    QPen pen;
    pen.setColor(color);
    for (int i = 0; i < _plot->graphCount(); ++i) {
        if (_plot->graph(i)->name() == _selected->name()) {
            pen.setWidth(_plot->graph(i)->pen().width());
            pen.setStyle(_plot->graph(i)->pen().style());
            _plot->graph(i)->setPen(pen);
            pen.setWidth(pen.width() + 2);
            _plot->graph(i)->selectionDecorator()->setPen(pen);
            break;
        }
    }
    plot();
}

void MainWidget::on_select_graph(QCPAbstractPlottable *graph)
{
    _selected = graph;
    set_selected_graph_params(graph);
    emit right_part_visibility(true);
    _rbtn_visible->setChecked(true);
}

void MainWidget::set_right_part_enable(bool flag)
{
    _fun_name->setVisible(flag);
    _btn_remove->setEnabled(flag);
    _rbtn_visible->setEnabled(flag);
    _btn_color->setEnabled(flag);
    _label_width->setEnabled(flag);
    _line_width->setEnabled(flag);
    _label_linestyle->setEnabled(flag);
    _line_style->setEnabled(flag);
    _label_fun_value->setEnabled(flag);
    _label_arg->setEnabled(flag);
    _arg_fun_value->setEnabled(flag);
    _label_fun->setEnabled(flag);
    _label_value_at_point->setEnabled(flag);
}
