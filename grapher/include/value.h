#ifndef KURSACH_VALUE_H
#define KURSACH_VALUE_H

#include "definitions.h"

class Value {
private:
    double _y;
    status_t _status;
public:
    Value(double y, status_t status): _y(y), _status(status) {};

    double getY();
    status_t getStatus();

    void setY(double y);
    void setStatus(status_t status);

};


#endif //KURSACH_VALUE_H
