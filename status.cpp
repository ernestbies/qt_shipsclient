#include "status.h"

Status::Status(QString code, QString shipName, int type, int steps, QString board){
    this->code = code;
    this->shipName = shipName;
    this->type = type;
    this->steps = steps;
    this->board = board;
}

int Status::getSteps() {
    return this->steps;
}

QString Status::getCode() {
    return this->code;
}

QString Status::getShipName() {
    return this-> shipName;
}

int Status::getType() {
    return this->type;
}

QString Status::getBoard() {
    return this->board;
}

void Status::setSteps(int steps) {
    this->steps = steps;
}

void Status::setCode(QString code){
    this->code = code;
}

void Status::setShipName(QString shipName) {
    this->shipName = shipName;
}

void Status::setType(int type) {
    this->type = type;
}

void Status::setBoard(QString board) {
    this->board = board;
}

QString Status::toString(){
    return "{\n\t\"code\":\""+getCode()+"\",\n\t\"shipName\":\""+getShipName()+"\",\n\t\"type\":\""+QString::number(getType())+"\",\n\t\"steps\":\""+QString::number(getSteps())+"\",\n\t\"board\":\""+getBoard()+"\"\n}";
}
