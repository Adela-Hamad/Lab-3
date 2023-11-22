#include<iostream>
#include<iomanip>
#include <cstdlib> 
using namespace std;

void print_real(float number, int fieldspace, int precision);

template <typename T>
void update_scale(T &m1, T &m2, T m3 = 10);

int main(void) {
    float a, b;
    cout << "Please input two real numbers: ";
    cin >> a >> b;

    print_real(a, 7, 3);
    print_real(b, 7, 3);

    // call the function update_scale with ONLY the actual parameters a and b
    update_scale(a, b);

    print_real(a, 7, 3);
    print_real(b, 7, 3);

    return 0;
}

/* complete the body of the function */
void print_real(float number, int fieldspace, int precision) {
    cout << fixed << setw(fieldspace) << setprecision(precision) << number << endl;
}

// add the function definition (header+body) of the template function update_scale
template <typename T>
void update_scale(T &m1, T &m2, T m3) {
    T original_m1 = m1;
    T original_m2 = m2;

    m1 = (original_m1 + original_m2) * m3;
    m2 = (original_m1 - original_m2) * m3;
}
