#ifndef POLY_H
#define POLY_H

double poly_sum_scalar_naive(double a[], double x, long degree);

double poly_sum_scalar_horner_naive(double a[], double x, long degree);

double poly_sum_scalar_horner_4x4(double a[], double x, long degree);

double poly_sum_scalar_horner_4x1a(double a[], double x, long degree);

double poly_sum_vector_naive(double a[], double x, long degree);

double poly_sum_vector_horner_4x4(double a[], double x, long degree);

double poly_sum_vector_horner_16x16(double a[], double x, long degree);

double poly_sum_vector_horner_64x16a(double a[], double x, long degree);

#endif // !POLY_H
