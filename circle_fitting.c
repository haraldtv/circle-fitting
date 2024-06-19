#include <math.h>

double sample_variance_double(double *x, int n) {
    int i;
    double sum = 0;
    double s = 0;

    for (i=0; i<n; i++) {
        sum += x[i];
    }

    double avg = sum / n;

    for (i=0; i<n; i++) {
        s += pow((x[i] - avg), 2);
    }

    return (s / (n-1));
}

double sample_covariance_double(double *x, double *y, int n) {
    double sumx = 0;
    double sumy = 0;
    double s;
    for (int i=0; i<n; i++) {
        sumx += x[i];
        sumy += y[i];
    }
    double avgx = sumx / n;
    double avgy = sumy / n;
    for (int i=0; i<n; i++) {
        s += ( (x[i] - avgx) * (y[i] - avgy) );
    }
    return s / (n-1);
}

int circle_fitting_double(double *x, double *y, int len, double return_values[3]) {
    double a, b, c, d, e = 0;
    double x2[len], y2[len];
    for (int i = 0; i < len; i++) {
        x2[i] = pow(x[i], 2);
        y2[i] = pow(y[i], 2);
    }

    int len_sub_one = len-1;
    int len_times_len_sub_one = len * len_sub_one;
    double len_times_len_sub_one_div_2 = (double)len_times_len_sub_one / 2;

    a = len_times_len_sub_one * sample_variance_double(x, len);
    b = len_times_len_sub_one * sample_covariance_double(x, y, len);
    c = len_times_len_sub_one * sample_variance_double(y, len);
    d = len_times_len_sub_one_div_2 * sample_covariance_double(x, y2, len) * sample_covariance_double(x, x2, len);
    e = len_times_len_sub_one_div_2 * sample_covariance_double(y, x2, len) * sample_covariance_double(y, y2, len);

    // double b2 = pow(b, 2);
    // double ac = a * c;
    // double ac_sub_b2 = ac - b2;
    double ac_sub_b2 = (a*c) - pow(b,2);

    // x - value
    return_values[0] = ( (d*c) - (b * e) ) / (ac_sub_b2);

    // y - vlue
    return_values[1] = ( (a * e) - (b * d) ) / (ac_sub_b2);

    return_values[2] = 0;
    for (int i=0; i<len; i++) {
        return_values[2] += ( sqrt( pow((x[i]-a), 2) + pow((y[i]-b), 2) ) / len );
    }


    return 0;
}
