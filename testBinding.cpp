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


struct Quaternion {
    double _w;
    double _x;
    double _y;
    double _z;

    Quaternion(const double w, const double x, const double y, const double z):_w(w),_x(x),_y(y),_z(z) {

    }

    Quaternion quaternion_mul(const Quaternion& autre) {
        return Quaternion(
            _w*autre._w - (_x*autre._x +_y*autre._y + _z*autre._z),
            _w*autre._x + _x*autre._w + _y * autre._z - _z * autre._y,
            _w*autre._y + _y*autre._w + _z * autre._x - _x * autre._z,
            _w*autre._z + _z*autre._w + _x * autre._y - _y * autre._x
        );
    }

    void normalisation(){
        // q/sqrt(_w*)
        double normeQuaternion = sqrt(_w*_w + _x*_x + _y*_y + _z*_z);
        _w = _w/normeQuaternion;
        _x = _x/normeQuaternion;
        _y = _y/normeQuaternion;
        _z = _z/normeQuaternion;
    }

    double angle(const Quaternion& q_autre){
        // on suppose que le quaternion courant et q_autre sont normalisés
        return acos(_w * q_autre._w + _x * q_autre._x + _y * q_autre._y + _z * q_autre._z);
    }


    Quaternion produitConstante_Quaternion(double c){
        return Quaternion(c*_w,c*_x,c*_y,c*_z);
    }

    Quaternion addition(const Quaternion qautre){
        return Quaternion(qautre._w+_w,qautre._x+_x,qautre._y+_y,qautre._z+_z);
    }

    Quaternion slerp(Quaternion& q_autre, double t){
        this->normalisation();
        q_autre.normalisation();
        
        double omega = this->angle(q_autre);

        double lambda1 = sin((1-t)*omega)/sin(omega);
        double lambda2 = sin(t*omega)/sin(omega);

        Quaternion quaternionInterpole = (this->produitConstante_Quaternion(lambda1)).addition(q_autre.produitConstante_Quaternion(lambda2));
        return quaternionInterpole;
    }

    std::array<double,3> imagPur() const{
      return {_x,_y,_z};
    }

    Quaternion conjugate(){
        return Quaternion(_w,-_x,-_y,-_z);
    }

    std::string to_string()const{
        return std::to_string(_w)+","+std::to_string(_x)+","+std::to_string(_y)+","+std::to_string(_z)+" ";
    }
};





PYBIND11_MODULE(pybind11testwin, m) {
    m.doc() = "pybind11 example test"; // optional module docstring
    m.def("pow1", &pow1, "A function that computes a pow b");
    m.def("add1", &add, "A function that adds two numbers");

    py::class_<Quaternion>(m, "Quaternion")
        .def(py::init<const double ,const double ,const double ,const double >())
        .def_readwrite("_w", &Quaternion::_w)
        .def_readwrite("_x", &Quaternion::_x)
        .def_readwrite("_y", &Quaternion::_y)
        .def_readwrite("_z", &Quaternion::_z)
        .def("__repr__",&Quaternion::to_string)
        .def("__mul__",&Quaternion::quaternion_mul)
        .def("conj",&Quaternion::conjugate)
        .def("normalisation",&Quaternion::normalisation)
        .def("slerp",&Quaternion::slerp);
}