#ifndef FT_ALGO_HPP
# define FT_ALGO_HPP

# include <iostream>

#ifndef DEBUG_MODE
# define DEBUG_MODE 0
#endif


namespace ft	{

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                        InputIterator2 first2, InputIterator2 last2)
    {
        while (first1!=last1)
        {
            if (first2==last2 || *first2<*first1) return false;
            else if (*first1<*first2) return true;
            ++first1; ++first2;
        }
        return (first2!=last2);
    }

    template <class ForwardIterator>
    ForwardIterator adjacent_find (ForwardIterator first, ForwardIterator last)
    {
        if (first != last)
        {
            ForwardIterator next=first; ++next;
            while (next != last) {
                if (*first == *next)     // or: if (pred(*first,*next)), for version (2)
                    return first;
                ++first; ++next;
            }
        }
        return last;
    }

    template <class ForwardIterator, class BinaryPredicate>
    ForwardIterator adjacent_find (ForwardIterator first, ForwardIterator last,
                                    BinaryPredicate pred)
    {
        if (first != last)
        {
            ForwardIterator next=first; ++next;
            while (next != last) {
                if (pred(*first, *next))     // or: if (pred(*first,*next)), for version (2)
                    return first;
                ++first; ++next;
            }
        }
        return last;
    }

    template <class InputIterator1, class InputIterator2>
    bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
    {
        while (first1!=last1) {
            if (!(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
                return false;
            ++first1; ++first2;
        }
        return true;
    }


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
