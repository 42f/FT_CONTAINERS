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

			Iterator		_base;

		public:

			typedef				Iterator						iterator_type;
			typedef	typename	Iterator::iterator_category		iterator_category;
			typedef	typename	Iterator::value_type			value_type;
			typedef	typename	Iterator::difference_type		difference_type;
			typedef	typename	Iterator::pointer				pointer;
			typedef	typename	Iterator::reference				reference;

			reverse_iterator( void ) : _base(iterator_type())	{}

			explicit
			// reverse_iterator( iterator_type it ) : _base(it++)	{
			// 	std::cout << "__________________________________________________________________base == " << _base.getPtr() << std::endl;
			// 	std::cout << "__________________________________________________________________it   == " << it.getPtr() << std::endl;
			// }
			reverse_iterator( iterator_type it ) : _base(it)	{
				// std::cout << "__________________________________________________________________base == " << _base.getPtr() << std::endl;
				// std::cout << "__________________________________________________________________it   == " << it.getPtr() << std::endl;
			}

			template<class U>
			reverse_iterator( const reverse_iterator<U>& rev_it)	: _base(rev_it.base())	{}

			~reverse_iterator()	{}

			template<class U>
			reverse_iterator&	operator=(const reverse_iterator<U>& rev_it) {
				if (reinterpret_cast<const void *>(this) != reinterpret_cast<const void *>(&rev_it))
					_base = rev_it.base();
				return *this;
			}

			iterator_type		base() const		{	return _base;	}
			reference			operator*() const	{	return *(--base());	}
			pointer				operator->() const							{	return &(operator*());	}
			reference			operator[] (difference_type n) const		{	return (--base())[-n];	}

			reverse_iterator&	operator+= (difference_type n)		{	_base.operator-=(n); return (*this);	}
			reverse_iterator	operator+ (difference_type n) const	{	return reverse_iterator((--base()).operator-(n));	}
			reverse_iterator&	operator++()		{	_base.operator--(); return *this;	}
			reverse_iterator	operator++(int)		{
				reverse_iterator tmp = *this;
				++(*this);
				return tmp;
			}

			reverse_iterator&	operator-= (difference_type n)		{	_base.operator+=(n); return (*this);	}
			reverse_iterator	operator- (difference_type n) const	{	return reverse_iterator((--base()).operator+(n));	}
			reverse_iterator&	operator--()		{	_base.operator++(); return *this;	}
			reverse_iterator	operator--(int)		{
				reverse_iterator tmp = *this;
				--(*this);
				return tmp;
			}

			// iterator_type		base() const		{	return _base;	}
			// reference			operator*() const	{	return *(++base());	}
			// pointer				operator->() const							{	return &(operator*());	}
			// reference			operator[] (difference_type n) const		{	return (++base())[-n];	}

			// reverse_iterator&	operator+= (difference_type n)		{	_base.operator-=(n); return (*this);	}
			// reverse_iterator	operator+ (difference_type n) const	{	return reverse_iterator((++base()).operator-(n));	}
			// reverse_iterator&	operator++()		{	_base.operator--(); return *this;	}
			// reverse_iterator	operator++(int)		{
			// 	reverse_iterator tmp = *this;
			// 	++(*this);
			// 	return tmp;
			// }

			// reverse_iterator&	operator-= (difference_type n)		{	_base.operator+=(n); return (*this);	}
			// reverse_iterator	operator- (difference_type n) const	{	return reverse_iterator((++base()).operator+(n));	}
			// reverse_iterator&	operator--()		{	_base.operator++(); return *this;	}
			// reverse_iterator	operator--(int)		{
			// 	reverse_iterator tmp = *this;
			// 	--(*this);
			// 	return tmp;
			// }

	}; // ----------------- rev_iterator

	template <class Iterator1, class Iterator2>
	bool operator== (const ft::reverse_iterator<Iterator1>& lhs,
			const ft::reverse_iterator<Iterator2>& rhs)	{	return lhs.base() == rhs.base();	}

	template <class Iterator1, class Iterator2>
	bool operator!= (const ft::reverse_iterator<Iterator1>& lhs,
			const ft::reverse_iterator<Iterator2>& rhs)	{	return lhs.base() != rhs.base();	}

	template <class Iterator1, class Iterator2>
	bool operator<  (const ft::reverse_iterator<Iterator1>& lhs,
			const ft::reverse_iterator<Iterator2>& rhs)	{	return lhs.base() > rhs.base();	}

	template <class Iterator1, class Iterator2>
	bool operator<= (const ft::reverse_iterator<Iterator1>& lhs,
			const ft::reverse_iterator<Iterator2>& rhs)	{	return lhs.base() >= rhs.base();	}

	template <class Iterator1, class Iterator2>
	bool operator>  (const ft::reverse_iterator<Iterator1>& lhs,
			const ft::reverse_iterator<Iterator2>& rhs)	{	return lhs.base() < rhs.base();	}

	template <class Iterator1, class Iterator2>
	bool operator>= (const ft::reverse_iterator<Iterator1>& lhs,
			const ft::reverse_iterator<Iterator2>& rhs)	{	return lhs.base() <= rhs.base();	}

	template <class Iterator>
	ft::reverse_iterator<Iterator> operator+ (
		typename ft::reverse_iterator<Iterator>::difference_type n,
			const ft::reverse_iterator<Iterator>& rev_it)	{

		ft::reverse_iterator<Iterator>	tmp = rev_it;
		tmp.operator+(n);
		return tmp;
	}

	template <class Iterator>
		typename ft::reverse_iterator<Iterator>::difference_type operator- (
			const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs)	{

		return rhs.base().operator-(lhs.base());
	}

} // ----------------- ft namespace

#endif
