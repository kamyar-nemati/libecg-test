/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ScatterPoints.h
 * Author: kamyar
 *
 * Created on March 27, 2018, 12:02 PM
 */

#ifndef SCATTERPOINTS_H
#define SCATTERPOINTS_H

#include <string>
#include <list>


class ScatterPoints {
public:
    ScatterPoints() = delete;
    ScatterPoints(int index, std::string name);
    ScatterPoints(const ScatterPoints& orig) = delete;
    virtual ~ScatterPoints();
    void addPoint(double x, double y);
    void getPoint(int i, double& x, double& y);
    int getCount();
    std::string getName();
    int getIndex();
private:
    int index;
    std::string name;
    std::list<double>* dataX;
    std::list<double>* dataY;
    int count;
};

#endif /* SCATTERPOINTS_H */

