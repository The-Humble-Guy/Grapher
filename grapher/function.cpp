#include "function.h"

Function::Function(std::string input, std::string argument) {
    _expression = new Expression(input, argument);
    _line_weight = 1;
    pen.setWidth(1);
}

void Function::addPoint(double x)
{
    Value res = _expression->evaluate(x);
    if (res.getStatus() == S_CORRECT) {
        _y.push_back(res.getY());
        _x.push_back(x);
    }
}

void Function::fillValues(double start, double end)
{
    clearContents();
    double step = end - start;
    step /= CountOfPoint;
    for (int i = 0; i < CountOfPoint; ++i) {
        addPoint(start + i * step);
    }
}

Value Function::value(double x)
{
    return _expression->evaluate(x);
}

void Function::clearX()
{
    _x.clear();
}

void Function::clearY()
{
    _y.clear();
}

void Function::clearContents()
{
    clearX();
    clearY();
}

QVector<double> Function::getX()
{
    return _x;
}

QVector<double> Function::getY()
{
    return _y;
}

QString Function::getFunctionName()
{
    QString str = QString::fromUtf8(_expression->getFunName());
    return str;
}
