#ifndef ITERATOR_BASE_HPP
# define ITERATOR_BASE_HPP

# include <cstddef>

#ifndef DEBUG_MODE
# define DEBUG_MODE 0
#endif

namespace ft	{

	struct output_iterator_tag {};
	struct input_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};

	template <class Category,            // iterator::iterator_category
			class T,                     // iterator::value_type
			class Distance = ptrdiff_t,  // iterator::difference_type
			class Pointer = T*,          // iterator::pointer
			class Reference = T&         // iterator::reference
			> class iterator	{

			public:
				typedef Category					iterator_category;
				typedef T							value_type;
				typedef Distance					difference_type;
				typedef Pointer						pointer;
				typedef Reference					reference;

			}; //------- iterator_base

} // ----------------- ft namespace

#endif
