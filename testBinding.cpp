# include <iostream>
# include <vector>
# include <pybind11/pybind11.h>

namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}
double pow1(const double &x, const unsigned int n){
    if(n==0){
        return 1.0;
    }
    return x*pow1(x,n-1);
}


PYBIND11_MODULE(pybind11testwin, m) {
    m.doc() = "pybind11 example test"; // optional module docstring
    m.def("pow1", &pow1, "A function that computes a pow b");
    m.def("add1", &add, "A function that adds two numbers");
}