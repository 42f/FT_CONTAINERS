#ifndef REV_ITERATOR_HPP
# define REV_ITERATOR_HPP

# include <iostream>

#ifndef DEBUG_MODE
# define DEBUG_MODE 0
#endif


namespace ft	{

	template <class Iterator>
	class reverse_iterator	{

		private:

			Iterator		_it;

		public:

			typedef				Iterator						iterator_type;
			typedef	typename	Iterator::iterator_category		iterator_category;
			typedef	typename	Iterator::value_type			value_type;
			typedef	typename	Iterator::difference_type		difference_type;
			typedef	typename	Iterator::pointer				pointer;
			typedef	typename	Iterator::reference				reference;

			reverse_iterator( void ) : _it(iterator_type())	{}

			explicit
			reverse_iterator( iterator_type it ) : _it(it)	{}

			template<class Iter>
			reverse_iterator( const reverse_iterator<Iter>& rev_it)	: _it(rev_it.base())	{}

			~reverse_iterator()	{}

			iterator_type		base() const		{	return iterator_type(_it);	}
			reference			operator*() const	{	return --(iterator_type(base())).operator*();	}
			reverse_iterator	operator+ (difference_type n) const	{	return reverse_iterator(_it.operator-(n));	}
			reverse_iterator&	operator++()		{	_it.operator--; return *this;	}
			reverse_iterator	operator++(int)		{
				reverse_iterator tmp = *this;
				++(*this);
				return tmp;
			}

			reverse_iterator& operator+= (difference_type n)		{	_it.operator-=(n); return (*this);	}

			reverse_iterator	operator- (difference_type n) const	{	return reverse_iterator(_it.operator+(n));	}
			reverse_iterator&	operator--()		{	_it.operator++; return *this;	}
			reverse_iterator	operator--(int)		{
				reverse_iterator tmp = *this;
				--(*this);
				return tmp;
			}
			reverse_iterator& operator-= (difference_type n)	{	_it.operator+=(n); return (*this);	}
			pointer operator->() const							{	return &(operator*());	}
			reference operator[] (difference_type n) const		{	return base()[-n-1];	}

	}; // ----------------- rev_iterator

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)	{	return lhs.base() == rhs.base();	}

	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)	{	return lhs.base() != rhs.base();	}

	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)	{	return lhs.base() > rhs.base();	}

	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)	{	return lhs.base() >= rhs.base();	}

	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)	{	return lhs.base() < rhs.base();	}

	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)	{	return lhs.base() <= rhs.base();	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (
		typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it)	{

		reverse_iterator<Iterator>	tmp = rev_it;
		tmp.operator+(n);
		return tmp;
	}

	template <class Iterator>
		typename reverse_iterator<Iterator>::difference_type operator- (
			const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)	{

		return rhs.base().operator-(lhs.base());
	}

} // ----------------- ft namespace

#endif
