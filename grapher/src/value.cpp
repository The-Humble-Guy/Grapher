#include "../include/value.h"

double Value::getY() {
    return this->_y;
}

status_t Value::getStatus() {
    return this->_status;
}

void Value::setY(double y) {
    this->_y = y;
}

void Value::setStatus(status_t status) {
    this->_status = status;
}
