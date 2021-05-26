#ifndef FT_ALGO_HPP
# define FT_ALGO_HPP

# include <iostream>

#ifndef DEBUG_MODE
# define DEBUG_MODE 0
#endif


namespace ft	{

    template<class InputIterator, class T>
    InputIterator find (InputIterator first, InputIterator last, const T& val)
    {
        while (first!=last) {
        if (*first==val) return first;
        ++first;
        }
        return last;
    }

    template<class InputIterator, class UnaryPredicate>
    InputIterator find_if (InputIterator first, InputIterator last, UnaryPredicate pred)
    {
        while (first!=last) {
        if (pred(*first)) return first;
        ++first;
        }
        return last;
    }

} // ----------------- ft namespace

#endif
