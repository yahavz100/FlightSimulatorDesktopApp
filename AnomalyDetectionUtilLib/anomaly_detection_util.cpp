#include "pch.h"
#include "anomaly_detection_util.h"
#include <cmath>

using namespace std;

// Returns the average of the floats in array x.
float avg(float* x, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++)
        sum += x[i];
    return (sum / size);
}

// Returns the variance of x and y.
float var(float* x, int size) {
    float expValue = avg(x, size);
    float *y = new float[size];
    for (int i = 0; i < size; i++)
        y[i] = pow((x[i] - expValue), 2);
    float ret = avg(y, size);
    delete[] y;
    return ret;
}

// Returns the covariance of x and y.
float cov(float* x, float* y, int size) {
    float *z = new float[size];
    for (int i = 0; i < size; i++)
        z[i] = x[i] * y[i];
    float ret = avg(z, size) - avg(x, size) * avg(y, size);
    delete[] z;
    return ret;
}

// Returns the Pearson correlation coefficient of x and y.
float pearson(float* x, float* y, int size) {
    return (cov(x, y, size) / sqrt((var(x, size)) * var(y, size)));
}

// Performs a linear regression and returns the line equation.
Line linear_reg(Point** points, int size) {
    float *xValues = new float[size];
    float *yValues = new float[size];
    for (int i = 0; i < size; i++) {
        xValues[i] = points[i]->x;
        yValues[i] = points[i]->y;
    }
    float a = cov(xValues, yValues, size) / var(xValues, size);
    float b = avg(yValues, size) - a * avg(xValues, size);
    delete[] xValues;
    delete[] yValues;
    return Line(a, b);
}

// Returns the deviation between point p and the line equation of the points.
float devp(Point p, Point** points, int size) {
    return devl(p, linear_reg(points, size));
}

// Returns the deviation between point p and the line.
float devl(Point p, Line l) {
    return abs(l.f(p.x) - p.y);
}