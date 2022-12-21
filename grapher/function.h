#ifndef FUNCTION_H
#define FUNCTION_H

#include <QVector>
#include <QPen>
#include "expression.h"

#define CountOfPoint 1700

class Function {
private:
    Expression *_expression;
    QVector<double> _y;
    QVector<double> _x;
    int _line_weight;
    QPen pen;
public:
    Function() = delete;
    Function(std::string input, std::string argument);

    void addPoint(double x);

    void fillValues(double start, double end);

    Value value(double x);

    void clearX();

    void clearY();

    void clearContents();

    QVector<double> getX();

    QVector<double> getY();

    QString getFunctionName();
};

#endif // FUNCTION_H
