# The small syntax guide
## Functions
If the function has the basic in and out, you just need to include it into your `<module_name>_src.cpp` and make your `BOOST_PYTHON_MODULE` like this:
```c++
BOOST_PYTHON_MODULE(<module_name>){
    py::def("<function_in_python_name>", &<function_in_c++_name>);
}
```
If your function returns non-standard type, you should use `from_cpp_type_to_python_type_converter`. It can be taken either from `stdpyc.h`, or created as a struct like this:
```c++
template<typename T>
struct vector_to_list {
    static PyObject* convert(const std::vector<T>& vec) {
        auto l = boost::python::list();
        for (auto& i : vec) {
            l.append(i);
        }
        return l.ptr();
    }
};

BOOST_PYTHON_MODULE(<module_name>){
    py::to_python_converter<std::vector<int>, vector_to_list<int>>();
    //..
    def("<some_name>", &some_function_returning_vector_of_ints);
}
```

If your function takes non-standard type as an argument, you can, again, use some from `stdpyc.h` or write it as a function like this:
```c++
using array = py::list;
template<typename T>
std::vector<T> to_std_vector(const array& iterable) {
    return std::vector<T>(iterator<T>(iterable), iterator<T>());
}

some_return_type wrapping_function(const py::list& l){
    return function(to_std_vector<int>(l));
}

BOOST_PYTHON_MODULE(<module_name>){
    def("some_name", &wrapper_function);
}
```
## Classes
You can also create a class in your module. For example:
```c++

BOOST_PYTHON_MODULE (<module_name>) {
    py::to_python_converter<std::vector<int>, vector_to_list<int>>();
    
    py::class_<class_or_wrapper>("some_name", py::init<py::tuple>())
            .def(py::init<py::tuple, int>())
            .def(py::init<py::tuple, int, int>())
            .def("compute", &class_or_wrapper::compute)
            .def("reset_predictions", &class_or_wrapper::Region::reset_predictions)
            .def("get_anomaly", &class_or_wrapper::Region::get_anomaly)
}
```