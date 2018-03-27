/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ScatterPoints.cpp
 * Author: kamyar
 * 
 * Created on March 27, 2018, 12:02 PM
 */

#include "ScatterPoints.h"

//ScatterPoints::ScatterPoints() {
//}

ScatterPoints::ScatterPoints(int index, std::string name) {
    this->index = index;
    this->name = name;
    this->dataX = new std::list<double>();
    this->dataY = new std::list<double>();
    this->count = 0;
}

//ScatterPoints::ScatterPoints(const ScatterPoints& orig) {
//}

ScatterPoints::~ScatterPoints() {
    delete this->dataX;
    delete this->dataY;
}

void ScatterPoints::addPoint(double x, double y) {
    this->dataX->push_back(x);
    this->dataY->push_back(y);
    ++this->count;
}

void ScatterPoints::getPoint(int i, double& x, double& y) {
    std::list<double>::const_iterator it_x = this->dataX->begin();
    std::list<double>::const_iterator it_y = this->dataY->begin();
    for (int n = 0; n < i; ++n) {
        ++it_x;
        ++it_y;
    }
    x = *it_x;
    y = *it_y;
}

int ScatterPoints::getCount() {
    return this->count;
}

std::string ScatterPoints::getName() {
    return this->name;
}

int ScatterPoints::getIndex() {
    return this->index;
}

