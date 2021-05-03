#ifndef MAP_PAIR_HPP
# define MAP_PAIR_HPP

# include <iostream>

#ifndef DEBUG_MODE
# define DEBUG_MODE 0
#endif


namespace ft	{

	template <class T1, class T2>
	struct pair {

		/**
		 *	ALIASES
		 */

		typedef		T1		first_type;
		typedef		T2		second_type;

		/**
		 * 	CONSTRUCTORS
		 */

		pair( void ) : first(first_type()), second(second_type())	{}

		template<class U, class V>
		pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}

		pair (const first_type& a, const second_type& b) : first(a), second(b) {}

		/**
		 * 	PUBLIC MEMBER FUNCTIONS
		 */

		pair&
		operator= (const pair& pr)	{
			first = pr.first;
			second = pr.second;
			return (*this);
		}

		/**
		 * 	PUBLIC VARIABLE
		 */

		T1	first;
		T2	second;

		};


	/**
	 * 	RELATIONAL OPERATORS
	 */

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (lhs.first == rhs.first && lhs.second == rhs.second); }

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return ( !(lhs == rhs) ); }

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second)); }

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return ( !(rhs < lhs) ); }

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return ( rhs < lhs ); }

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return ( !(lhs < rhs)); }


	/**
	 * 	NON MEMBER FUNCTIONS
	 */

	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
 	{
	    return ( pair<T1,T2>(x,y) );
	}

} // ----------------- ft namespace

#endif
