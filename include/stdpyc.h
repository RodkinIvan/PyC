#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

namespace py = boost::python;
namespace np = boost::python::numpy;



using array = py::list;
template<typename T>
using iterator = py::stl_input_iterator<T>;


/// std::vector to python list converter
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


template<typename T>
inline
std::vector<T> to_std_vector(const array& iterable) {
    return std::vector<T>(iterator<T>(iterable),
                          iterator<T>());

}

template<typename T>
inline
std::vector<std::vector<T>> to_2d_vector(const array& iterable) {
    std::vector<std::vector<T>> ans;
    for (auto iter = iterator<array>(iterable); iter != iterator<array>(); ++iter) {
        ans.push_back(to_std_vector<T>(*iter));
    }
    return ans;
}
