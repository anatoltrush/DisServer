#ifndef UNIQUE_H
#define UNIQUE_H

#include <memory>

namespace std {
template<class T> struct _Unique_if {
    using _Single_object = unique_ptr<T>;
};

template<class T> struct _Unique_if<T[]> {
    using _Unknown_bound = unique_ptr<T[]> ;
};

template<class T, size_t N> struct _Unique_if<std::array<T, N>> {
    using _Known_bound = void;
};

template<class T, class... Args>
typename _Unique_if<T>::_Single_object
make_unique(Args&&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<class T>
typename _Unique_if<T>::_Unknown_bound
make_unique(size_t n) {
    typedef typename remove_extent<T>::type U;
    return unique_ptr<T>(new U[n]());
}

template<class T, class... Args>
typename _Unique_if<T>::_Known_bound
make_unique(Args&&...) = delete;
}

#endif // UNIQUE_H
