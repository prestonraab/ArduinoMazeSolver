/*	Copyright (C) 2004 Garrett A. Kajmowicz
	This file is part of the uClibc++ Library.
	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "cstdlib.h"
#include "iterator.h"
#include "utility.h"
#include "functional.h"

#ifndef __STD_HEADER_ALGORITHM
#define __STD_HEADER_ALGORITHM 1

//Elliminate any previously defined macro
#undef min
#undef max

#pragma GCC visibility push(default)

namespace std{

	// subclause _lib.alg.nonmodifying_, non-modifying sequence operations:
	template<class InputIterator, class Function> _UCXXEXPORT
		Function for_each(InputIterator first, InputIterator last, Function f)
	{
		while(first !=last){
			f(*first);
			++first;
		}
		return f;
	}


	template<class InputIterator, class T> _UCXXEXPORT
		InputIterator find(InputIterator first, InputIterator last, const T& value)
	{
		while(first !=last && *first != value){
			++first;
		}
		return first;
	}

	template<class InputIterator, class Predicate> _UCXXEXPORT
		InputIterator find_if(InputIterator first, InputIterator last, Predicate pred)
	{
		while(first !=last && !pred(*first)){
			++first;
		}
		return first;
	}

	template<class ForwardIterator1, class ForwardIterator2> _UCXXEXPORT ForwardIterator1
		find_end(ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2)
	{
		ForwardIterator1 retval = last1;
		while(first1 !=last1){
			ForwardIterator1 temp1(first1);
			ForwardIterator2 temp2(first2);
			while(temp2!=last2 && temp1!= last1){
				if(*temp1 != *temp2){
					break;		//Exit while loop
				}
				++temp1;
				++temp2;
				if(temp2 == last2){	//Have successfully checked the whole sequence
					retval = first1;
				}
			}
		}
		return retval;
	}

	template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate> _UCXXEXPORT
		ForwardIterator1
		find_end(ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred)
	{
		ForwardIterator1 retval = last1;
		while(first1 !=last1){
			ForwardIterator1 temp1(first1);
			ForwardIterator2 temp2(first2);
			while(temp2!=last2 && temp1!= last1){
				if( ! pred(*temp1, *temp2)){
					break;		//Exit while loop
				}
				++temp1;
				++temp2;
				if(temp2 == last2){	//Have successfully checked the whole sequence
					retval = first1;
				}
			}
		}
		return retval;
	}

	template<class ForwardIterator1, class ForwardIterator2> _UCXXEXPORT
		ForwardIterator1
		find_first_of(ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2)
	{
		while(first1 != last1){
			ForwardIterator2 temp2(first2);
			while(temp2 != last2 ){
				if(*temp2 == first1){
					return first1;
				}
				++temp2;
			}

		}
		return last1;
	}

	template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate> _UCXXEXPORT
		ForwardIterator1
		find_first_of(ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred)
	{
		while(first1 != last1){
			ForwardIterator2 temp2(first2);
			while(temp2 != last2 ){
				if(*temp2 == first1){
					return first1;
				}
				++temp2;
			}

		}
		return last1;
	}

	template<class ForwardIterator> _UCXXEXPORT ForwardIterator
		adjacent_find(ForwardIterator first, ForwardIterator last)
	{
		ForwardIterator temp;
		while(first != last){
			temp = first;
			++temp;
			if(*temp == *first){
				return first;
			}
			++first;
		}
		return first;
	}

	template<class ForwardIterator, class BinaryPredicate> _UCXXEXPORT
		ForwardIterator
		adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
	{
		ForwardIterator temp;
		while(first != last){
			temp = first;
			++temp;
			if( pred(*temp, *first)){
				return first;
			}
			++first;
		}
		return first;
	}

	template<class InputIterator, class T> _UCXXEXPORT
		typename iterator_traits<InputIterator>::difference_type
		count(InputIterator first, InputIterator last, const T& value)
	{
		typename iterator_traits<InputIterator>::difference_type i = 0;
		while(first!=last){
			if(*first == value){
				++i;
			}
			++first;
		}
		return i;
	}

	template<class InputIterator, class Predicate> _UCXXEXPORT
		typename iterator_traits<InputIterator>::difference_type
		count_if(InputIterator first, InputIterator last, Predicate pred)
	{
		typename iterator_traits<InputIterator>::difference_type i = 0;
		while(first!=last){
			if( pred(*first) ){
				++i;
			}
			++first;
		}
		return i;
	}

	template<class InputIterator1, class InputIterator2> _UCXXEXPORT
		pair<InputIterator1, InputIterator2>
		mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while(first1 != last1){
			if(*first1 != *first2){
				break;
			}
			++first1;
			++first2;
		}

		pair<InputIterator1, InputIterator2> retval;
		retval.first = first1;
		retval.second = first2;
		return retval;
	}

	template<class InputIterator1, class InputIterator2, class BinaryPredicate> _UCXXEXPORT
		pair<InputIterator1, InputIterator2>
		mismatch(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, BinaryPredicate pred)
	{
		while(first1 != last1){
			if( !pred(*first1, *first2) ){
				break;
			}
			++first1;
			++first2;
		}

		pair<InputIterator1, InputIterator2> retval;
		retval.first = first1;
		retval.second = first2;
		return retval;
	}

	template<class InputIterator1, class InputIterator2> _UCXXEXPORT
		bool
		equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while(first1 !=last1){
			if(*first1 != *first2){
				return false;
			}
			++first1;
			++first2;
		}
		return true;
	}

	template<class InputIterator1, class InputIterator2, class BinaryPredicate> _UCXXEXPORT
		bool
		equal(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, BinaryPredicate pred)
	{
		while(first1 !=last1){
			if( !pred(*first1, *first2) ){
				return false;
			}
			++first1;
			++first2;
		}
		return true;
	}

	template<class ForwardIterator1, class ForwardIterator2> _UCXXEXPORT
		ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2)
	{
		equal_to<typename iterator_traits<ForwardIterator1>::value_type> c;
		return search(first1, last1, first2, last2, c);
	}


	template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate> _UCXXEXPORT
		ForwardIterator1
		search(ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred)
	{
		while(first1 != last1){
			ForwardIterator1 temp1(first1);
			ForwardIterator2 temp2(first2);
			while(temp2 != last2 && temp1 != last1){
				if( !pred(*temp2, *temp1) ){
					break;
				}
				++temp1;
				++temp2;
				if(temp2 == last2){
					return first1;
				}
			}
			++first1;
		}
		return last1;
	}


	template<class ForwardIterator, class Size, class T> _UCXXEXPORT
		ForwardIterator
		search_n(ForwardIterator first, ForwardIterator last, Size count, const T& value)
	{
		while( first != last ){
			if(*first == value){
				ForwardIterator temp(first);
				Size i = 1;
				++first;	//Avoid doing the same comparison over again
				while(i < count && *temp == value){
					++first;
					++i;
				}
				if(i == count){
					return first;
				}
			}
			++first;
		}
		return first;
	}


	template<class ForwardIterator, class Size, class T, class BinaryPredicate> _UCXXEXPORT
		ForwardIterator
		search_n(ForwardIterator first, ForwardIterator last,
			Size count, const T& value, BinaryPredicate pred)
	{
		while( first != last ){
			if( pred(*first, value) ){
				ForwardIterator temp(first);
				Size i = 1;
				++first;	//Avoid doing the same comparison over again
				while(i < count && pred(*temp, value) ){
					++first;
					++i;
				}
				if(i == count){
					return first;
				}
			}
			++first;
		}
		return first;

	}

	// subclause _lib.alg.modifying.operations_, modifying sequence operations:

	template<class InputIterator, class OutputIterator> _UCXXEXPORT
		OutputIterator
		copy(InputIterator first, InputIterator last, OutputIterator result)
	{
		while(first != last){
			*result = *first;
			++first;
			++result;
		}
		return result;
	}

	template< class InputIterator, class Size, class OutputIterator >
	OutputIterator copy_n( InputIterator first, Size count, OutputIterator result ) {
		if (count > 0) {
			*result++ = *first;
			for (Size i = 1; i < count; ++i) {
				*result++ = *++first;
			}
		}
		return result;
	}

	template<class BidirectionalIterator1, class BidirectionalIterator2> _UCXXEXPORT
		BidirectionalIterator2
		copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last,
			BidirectionalIterator2 result)
	{
		while(first !=last ){
			--result;
			--last;
			*result = *last;
		}
		return result;
	}

	template<class T> _UCXXEXPORT void swap(T& a, T& b){
		T temp(a);
		a = b;
		b = temp;
	}

	template<class ForwardIterator1, class ForwardIterator2> _UCXXEXPORT
		void
		iter_swap(ForwardIterator1 a, ForwardIterator2 b)
	{
		typename iterator_traits<ForwardIterator1>::value_type temp(*a);
		*a = *b;
		*b = temp;
	}


	template<class ForwardIterator1, class ForwardIterator2> _UCXXEXPORT
		ForwardIterator2
		swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2)
	{
		while(first1 != last1){
			iter_swap(first1, first2);
			++first1;
			++first2;
		}
		return first2;
	}


	template<class InputIterator, class OutputIterator, class UnaryOperation> _UCXXEXPORT
		OutputIterator
		transform(InputIterator first, InputIterator last,
			OutputIterator result, UnaryOperation op)
	{
		while(first != last){
			*result = op(*first);
			++first;
			++result;
		}
		return result;
	}


	template<class InputIterator1, class InputIterator2, class OutputIterator, class BinaryOperation> _UCXXEXPORT
		OutputIterator transform(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, OutputIterator result,
			BinaryOperation binary_op)
	{
		while(first1 != last1){
			*result = binary_op(*first1, *first2);
			++first1;
			++first2;
			++result;
		}
		return result;
	}


	template<class ForwardIterator, class T> _UCXXEXPORT
		void
		replace(ForwardIterator first, ForwardIterator last,
			const T& old_value, const T& new_value)
	{
		while(first != last){
			if(*first == old_value){
				*first = new_value;
			}
			++first;
		}
	}

	template<class ForwardIterator, class Predicate, class T> _UCXXEXPORT
		void
		replace_if(ForwardIterator first, ForwardIterator last,
			Predicate pred, const T& new_value)
	{
		while(first != last){
			if( pred(*first) ){
				*first = new_value;
			}
			++first;
		}
	}


	template<class InputIterator, class OutputIterator, class T> _UCXXEXPORT
		OutputIterator
		replace_copy(InputIterator first, InputIterator last,
			OutputIterator result, const T& old_value, const T& new_value)
	{
		while(first != last){
			if(*first == old_value){
				*result = new_value;
			}else{
				*result = *first;
			}
			++first;
			++result;
		}
		return result;
	}

	template<class Iterator, class OutputIterator, class Predicate, class T> _UCXXEXPORT
		OutputIterator
		replace_copy_if(Iterator first, Iterator last,
			OutputIterator result, Predicate pred, const T& new_value)
	{
		while(first != last){
			if( pred(*first) ){
				*result = new_value;
			}else{
				*result = *first;
			}
			++first;
			++result;
		}
		return result;
	}

	template<class ForwardIterator, class T> _UCXXEXPORT
		void
		fill(ForwardIterator first, ForwardIterator last, const T& value)
	{
		while(first != last){
			*first = value;
			++first;
		}
	}

	template<class OutputIterator, class Size, class T> _UCXXEXPORT
		void
		fill_n(OutputIterator first, Size n, const T& value)
	{
		while(n != 0){
			*first = value;
			--n;
			++first;
		}
	}

	template<class ForwardIterator, class Generator> _UCXXEXPORT
		void
		generate(ForwardIterator first, ForwardIterator last, Generator gen)
	{
		while(first != last){
			*first = gen();
			++first;
		}
	}

	template<class OutputIterator, class Size, class Generator> _UCXXEXPORT
		void
		generate_n(OutputIterator first, Size n, Generator gen)
	{
		while(n !=0){
			*first = gen();
			--n;
			++first;
		}
	}

	template<class ForwardIterator, class T> _UCXXEXPORT
		ForwardIterator
		remove(ForwardIterator first, ForwardIterator last, const T& value)
	{
		ForwardIterator temp(first);
		while(temp !=last){
			if(*temp == value){

			}else{
				*first = *temp;
				++first;
			}
			++temp;
		}
		return first;
	}

	template<class ForwardIterator, class Predicate> _UCXXEXPORT
		ForwardIterator
		remove_if(ForwardIterator first, ForwardIterator last, Predicate pred)
	{
		ForwardIterator temp(first);
		while(temp !=last){
			if( pred(*temp) ){

			}else{
				*first = *temp;
				++first;
			}
			++temp;
		}
		return first;
	}


	template<class InputIterator, class OutputIterator, class T> _UCXXEXPORT
		OutputIterator
		remove_copy(InputIterator first, InputIterator last,
			OutputIterator result, const T& value)
	{
		while(first !=last){
			if(*first != value){
				*result = *first;
				++result;
			}
			++first;
		}
		return result;
	}

	template<class InputIterator, class OutputIterator, class Predicate> _UCXXEXPORT
		OutputIterator
		remove_copy_if(InputIterator first, InputIterator last,
			OutputIterator result, Predicate pred)
	{
		while(first !=last){
			if( !pred(*first) ){
				*result = *first;
				++result;
			}
			++first;
		}
		return result;
	}

	template<class ForwardIterator> _UCXXEXPORT
		ForwardIterator
		unique(ForwardIterator first, ForwardIterator last)
	{
		ForwardIterator new_val(first);
		ForwardIterator old_val(first);

		while(new_val !=last){
			if(*new_val == *old_val && new_val != old_val){

			}else{
				*first = *new_val;
				old_val = new_val;
				++first;
			}
			++new_val;
		}
		return first;
	}

	template<class ForwardIterator, class BinaryPredicate> _UCXXEXPORT
		ForwardIterator
		unique(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
	{
		ForwardIterator new_val(first);
		ForwardIterator old_val(first);

		while(new_val !=last){
			if( pred(*new_val, *old_val) && new_val != old_val){

			}else{
				*first = *new_val;
				old_val = new_val;
				++first;
			}
			++new_val;
		}
		return first;
	}

	template<class InputIterator, class OutputIterator> _UCXXEXPORT
		OutputIterator
		unique_copy(InputIterator first, InputIterator last, OutputIterator result)
	{
		InputIterator temp(first);
		while(first !=last ){
			if(*first == *temp && first != temp){

			}else{
				*result = *first;
				temp = first;
				++result;
			}
			++first;
		}
		return result;
	}

	template<class InputIterator, class OutputIterator, class BinaryPredicate> _UCXXEXPORT
		OutputIterator
		unique_copy(InputIterator first, InputIterator last,
			OutputIterator result, BinaryPredicate pred)
	{
		InputIterator temp(first);
		while(first !=last ){
			if( pred(*first, *temp) && first != temp){

			}else{
				*result = *first;
				temp = first;
				++result;
			}
			++first;
		}
		return result;
	}

	template<class BidirectionalIterator> _UCXXEXPORT
		void
		reverse(BidirectionalIterator first, BidirectionalIterator last)
	{
		--last;		//Don't work with one past the end element
		while(first < last){
			iter_swap(first, last);
			++first;
			--last;
		}
	}

	template<class BidirectionalIterator, class OutputIterator> _UCXXEXPORT
		OutputIterator
		reverse_copy(BidirectionalIterator first, BidirectionalIterator last,
		OutputIterator result)
	{
		while(last > first){
			--last;
			*result = *last;
			++result;
		}
		return result;
	}

	template<class ForwardIterator> _UCXXEXPORT
		void
		rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last)
	{
		if ((first == middle) || (last  == middle)){
			return;
		}

		ForwardIterator first2 = middle;

		do {
			swap(*first, *first2);
			first++;
			first2++;
			if(first == middle){
				middle = first2;
			}
		} while(first2 != last);

		first2 = middle;

		while (first2 != last) {
			swap(*first, *first2);
			first++;
			first2++;
			if (first == middle){
				middle = first2;
			}else if (first2 == last){
				first2 = middle;
			}
		}
	}

	template<class ForwardIterator, class OutputIterator> _UCXXEXPORT
		OutputIterator
		rotate_copy(ForwardIterator first, ForwardIterator middle,
			ForwardIterator last, OutputIterator result)
	{
		ForwardIterator temp(middle);
		while(temp !=last){
			*result = *temp;
			++temp;
			++result;
		}
		while(first != middle){
			*result = *first;
			++first;
			++result;
		}
		return result;
	}


	template<class RandomAccessIterator> _UCXXEXPORT
		void
		random_shuffle(RandomAccessIterator first, RandomAccessIterator last)
	{
		--last;
		while(first != last){
			iter_swap(first, (first + (rand() % (last - first) ) ) );
			++first;
		}
	}

	template<class RandomAccessIterator, class RandomNumberGenerator> _UCXXEXPORT
		void
		random_shuffle(RandomAccessIterator first, RandomAccessIterator last,
		RandomNumberGenerator& rand)
	{
		--last;
		while(first != last){
			iter_swap(first, (first + (rand(last - first) ) ) );
			++first;
		}
	}

	// _lib.alg.partitions_, partitions:
	template<class BidirectionalIterator, class Predicate> _UCXXEXPORT BidirectionalIterator
		partition(BidirectionalIterator first, BidirectionalIterator last, Predicate pred)
	{
		return stable_partition(first, last, pred);
	}

	template<class BidirectionalIterator, class Predicate> _UCXXEXPORT BidirectionalIterator
		stable_partition(BidirectionalIterator first, BidirectionalIterator last, Predicate pred)
	{
		//first now points to the first non-desired element
		while( first != last && pred(*first) ){
			++first;
		}

		BidirectionalIterator tempb;
		BidirectionalIterator tempe = first;

		while( tempe != last ){
			//Find the next desired element
			while( !pred(*tempe) ){
				++tempe;

				//See if we should exit
				if(tempe == last){
					return first;
				}
			}

			//Rotate the element back to the begining
			tempb = tempe;
			while(tempb != first){
				iter_swap(tempb, tempb-1 );
				--tempb;
			}
			//First now has a desired element
			++first;
		}

		return first;
	}

	template<class RandomAccessIterator> _UCXXEXPORT
		void sort(RandomAccessIterator first, RandomAccessIterator last)
	{
		less<typename iterator_traits<RandomAccessIterator>::value_type> c;
		sort(first, last, c );
	}

	template<class RandomAccessIterator> _UCXXEXPORT
		void stable_sort(RandomAccessIterator first, RandomAccessIterator last)
	{
		less<typename iterator_traits<RandomAccessIterator>::value_type> c;
		stable_sort(first, last, c);
	}

	template<class RandomAccessIterator, class Compare> _UCXXEXPORT
		void stable_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
	{
		//FIXME - bubble sort
		RandomAccessIterator temp;
		--last;
		while(last - first > 0){
			temp = last;
			while(temp != first){
				if( comp( *temp, *(temp-1) ) ){
					iter_swap( temp-1, temp);
				}
				--temp;
			}
			++first;
		}
	}

	template<class RandomAccessIterator, class Compare> _UCXXEXPORT
		void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
	{
		stable_sort(first, last, comp);
	}

	template<class RandomAccessIterator> _UCXXEXPORT
		void partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last)
	{
		less<typename iterator_traits<RandomAccessIterator>::value_type> c;
		partial_sort(first, middle, last, c);
	}
	template<class RandomAccessIterator, class Compare> _UCXXEXPORT
		void partial_sort(RandomAccessIterator first, RandomAccessIterator middle,
			RandomAccessIterator last, Compare comp)
	{
		//Fixme - partial bubble sort
		RandomAccessIterator temp;
		--last;
		while(first < middle){
			temp = last;
			while(temp != first){
				if( comp(*temp, *(temp -1 ) ) ) {
					iter_swap( temp-1, temp);
				}
				--temp;
			}
			++first;
		}
	}
	template<class InputIterator, class RandomAccessIterator> _UCXXEXPORT
		RandomAccessIterator
		partial_sort_copy(InputIterator first, InputIterator last,
			RandomAccessIterator result_first, RandomAccessIterator result_last)
	{
		less<typename iterator_traits<RandomAccessIterator>::value_type> c;
		return partial_sort_copy(first, last, result_first, result_last, c);
	}
	template<class InputIterator, class RandomAccessIterator, class Compare> _UCXXEXPORT
		RandomAccessIterator
		partial_sort_copy(InputIterator first, InputIterator last,
			RandomAccessIterator result_first, RandomAccessIterator result_last, Compare comp)
	{
		size_t output_size = last-first;
		size_t temp_size = result_last - result_first;
		if(temp_size < output_size){
			output_size = temp_size;
		}

		RandomAccessIterator middle = result_first + output_size;
		RandomAccessIterator temp = result_first;

		while(temp != middle){
			*temp = *first;
			++temp;
			++first;
		}
		sort(result_first, middle, comp);

		while( first != last){
			if( comp( *first, *(middle-1) ) ){
				*(middle-1) = *first;
				sort(result_first, middle, comp);
			}
			++first;
		}

		return middle;
	}
	template<class RandomAccessIterator> _UCXXEXPORT
		void nth_element(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last)
	{
		less<typename iterator_traits<RandomAccessIterator>::value_type> c;
		nth_element(first, nth, last, c);
	}
	template<class RandomAccessIterator, class Compare> _UCXXEXPORT
		void nth_element(RandomAccessIterator first, RandomAccessIterator nth,
			RandomAccessIterator last, Compare comp)
	{
		partial_sort(first, nth, last, comp);
	}

	template<class ForwardIterator, class T> _UCXXEXPORT
		ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last,
			const T& value)
	{
		less<typename iterator_traits<ForwardIterator>::value_type> c;
		return lower_bound(first, last, value, c);
	}

	template<class ForwardIterator, class T, class Compare> _UCXXEXPORT
		ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last,
			const T& value, Compare comp)
	{
		if(first == last){
			return last;
		}
		//If below or equal to the first element
		if( comp(*first, value) == false){
			return first;
		}
		ForwardIterator middle;

		//If greater than the top element
		middle = first;
		advance(middle, distance(first, last) - 1);
		if( comp(*middle, value) ){
			return last;
		}

		//Now begin the actual search for the begining
		while( distance(first, last) > 1 ){
			//Find middle
			middle = first;
			advance(middle, (distance(first, last)/2) );
			if( !comp(*middle, value) ){
				last = middle;
			}else{
				first = middle;
			}
		}

		if( !comp(*first, value) ){
			return first;
		}
		return last;
	}

	template<class ForwardIterator, class T> _UCXXEXPORT
		ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last,
			const T& value)
	{
		less<typename iterator_traits<ForwardIterator>::value_type> c;
		return upper_bound(first, last, value, c);
	}


	template<class ForwardIterator, class T, class Compare> _UCXXEXPORT
		ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last,
			const T& value, Compare comp)
	{
		if(first == last){
			return last;
		}
		//If below the first element
		if( comp(value, *first) == true){
			return first;
		}

		ForwardIterator middle;

		//If greater than the top element
		middle = first;
		advance(middle, distance(first, last) - 1);
		if( comp(*middle, value) ){
			return last;
		}

		//Now begin the actual search for the end
		while( distance(first, last) > 1 ){
			//Find middle
			middle = first;
			advance(middle, (distance(first, last)/2) );
			if( comp(value, *middle) ){
				last = middle;
			}else{
				first = middle;
			}
		}

		if( comp(value, *first) ){
			return first;
		}
		return last;
	}


	template<class ForwardIterator, class T> _UCXXEXPORT
		pair<ForwardIterator, ForwardIterator>
		equal_range(ForwardIterator first, ForwardIterator last, const T& value)
	{
		less<typename iterator_traits<ForwardIterator>::value_type> c;
		return equal_range(first, last, value, c);
	}

	template<class ForwardIterator, class T, class Compare> _UCXXEXPORT
		pair<ForwardIterator, ForwardIterator>
		equal_range(ForwardIterator first, ForwardIterator last, const T& value, Compare comp)
	{
		pair<ForwardIterator, ForwardIterator> retval;
		retval.first = lower_bound(first, last, value, comp);
		//Reuse retval.first in order to (possibly) save a few comparisons
		retval.second = upper_bound(retval.first, last, value, comp);
		return retval;

	}

	template<class ForwardIterator, class T> _UCXXEXPORT
		bool binary_search(ForwardIterator first, ForwardIterator last,
			const T& value)
	{
		less<typename iterator_traits<ForwardIterator>::value_type> c;
		return binary_search(first, last, value, c);
	}

	template<class ForwardIterator, class T, class Compare> _UCXXEXPORT
		bool binary_search(ForwardIterator first, ForwardIterator last,
			const T& value, Compare comp)
	{
		if( distance(first, last) == 0){
			return false;
		}

		ForwardIterator middle;

		while( distance(first, last) > 1 ){
			//Set middle between first and last
			middle = first;
			advance(middle, distance(first, last)/2 );

			if( comp(*middle, value ) == true){
				first = middle;
			}else{
				last = middle;
			}
		}

		if( !comp(*first, value) && !comp(value, *first) ){
			return true;
		}
		if( !comp(*last, value) && !comp(value, *last) ){
			return true;
		}

		return false;
	}

	// _lib.alg.merge_, merge:
	template<class InputIterator1, class InputIterator2, class OutputIterator> _UCXXEXPORT
		OutputIterator
		merge(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2, OutputIterator result)
	{
		less<typename iterator_traits<InputIterator1>::value_type> c;
		return merge(first1, last1, first2, last2, result, c);
	}
	template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare> _UCXXEXPORT
		OutputIterator
		merge(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp)
	{
		while( first1 != last1 && first2 != last2){
			//If in this order so first1 elements which are equal come first
			if( comp(*first2, *first1) ){
				*result = *first2;
				++first2;
			}else{
				*result = *first1;
				++first1;
			}
			++result;
		}
		//Clean up remaining elements
		while(first1 != last1){
			*result = *first1;
			++first1;
			++result;
		}
		while(first2 != last2){
			*result = *first2;
			++first2;
			++result;
		}
		return result;
	}
	template<class BidirectionalIterator> _UCXXEXPORT
		void inplace_merge(BidirectionalIterator first,
			BidirectionalIterator middle, BidirectionalIterator last)
	{
		less<typename iterator_traits<BidirectionalIterator>::value_type> c;
		inplace_merge(first, middle, last, c);
	}
	template<class BidirectionalIterator, class Compare> _UCXXEXPORT
		void inplace_merge(BidirectionalIterator first,
			BidirectionalIterator middle, BidirectionalIterator last, Compare comp)
	{
		//FIXME - using a bubble exchange method
		while(first != middle && middle !=last){
			if( comp(*middle, *first) ){
				BidirectionalIterator temp(middle);
				while( temp != first){
					iter_swap(temp, temp-1);
					--temp;
				}
				++middle;
			}
			++first;
		}
	}

	// _lib.alg.set.operations_, set operations:
	template<class InputIterator1, class InputIterator2> _UCXXEXPORT
		bool includes(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2)
	{
		less<typename iterator_traits<InputIterator1>::value_type> c;
		return includes(first1, last1, first2, last2, c );
	}

	template<class InputIterator1, class InputIterator2, class Compare> _UCXXEXPORT
		bool includes(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while(first2 != last2){
			//Advance the large set until no longer smaller than the element we are looking for
			while( comp(*first1, *first2) ){
				++first1;
				//If we are at the end of the list, we don't have the desired element
				if(first1 == last1){
					return false;
				}
			}
			//If we are past the element we want, it isn't here
			if( comp(*first2, *first1) ){
				return false;
			}
			++first2;	//Move to next element
		}
		return true;
	}

	template<class InputIterator1, class InputIterator2, class OutputIterator> _UCXXEXPORT
		OutputIterator set_union(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2, OutputIterator result)
	{
		less<typename iterator_traits<InputIterator1>::value_type> c;
		return set_union(first1, last1, first2, last2, result, c);
	}

	template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare> _UCXXEXPORT
		OutputIterator set_union(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp)
	{
		while( first1 != last1 && first2 != last2){
			if( comp(*first2, *first1) ){
				*result = *first2;

				//Elliminate duplicates
				InputIterator2 temp = first2;
				while( first1 != last1 && !comp( *temp, *first1) ){
					++first1;
				}
				while( first2 != last2 && !comp( *temp, *first2) ){
					++first2;
				}
			}else{
				*result = *first1;
					//Elliminate duplicates
				InputIterator1 temp = first1;
				while( first1 != last1 && !comp( *temp, *first1) ){
					++first1;
				}
				while( first2 != last2 && !comp( *temp, *first2) ){
					++first2;
				}
			}
			++result;
		}

		//Clean up remaining elements
		while(first1 != last1){
			*result = *first1;
			++result;
			InputIterator1 temp = first1;
			while( first1 != last1 && !comp( *temp, *first1) ){
				++first1;
			}
		}

		while(first2 != last2){
			*result = *first2;
			++result;
			InputIterator2 temp = first2;
			while( first2 != last2 && !comp( *temp, *first2) ){
				++first2;
			}
		}
		return result;
	}

	template<class InputIterator1, class InputIterator2, class OutputIterator> _UCXXEXPORT
		OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2, OutputIterator result)
	{
		less<typename iterator_traits<InputIterator1>::value_type> c;
		return set_intersection(first1, last1, first2, last2, result, c);
	}
	template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare> _UCXXEXPORT
		OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp)
	{
		while( first1 != last1 && first2 != last2){
			if( comp(*first2, *first1) ){
				++first2;
			}else if( comp(*first1, *first2) ) {
				++first1;
			}else{
				*result = *first1;
				++result;
				InputIterator1 temp = first1;
				while( first1 != last1 && !comp( *temp, *first1) ){
					++first1;
				}
				++first2;
			}
		}
		return result;
	}
	template<class InputIterator1, class InputIterator2, class OutputIterator> _UCXXEXPORT
		OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2, OutputIterator result)
	{
		less<typename iterator_traits<InputIterator1>::value_type> c;
		return set_difference(first1, last1, first2, last2, result, c);
	}
	template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare> _UCXXEXPORT
		OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp)
	{
		while( first1 != last1 && first2 != last2){
			if( comp(*first1, *first2) ){
				*result = *first1;
				++result;

				//Elliminate duplicates
				InputIterator1 temp = first1;
				while( first1 != last1 && !comp( *temp, *first1) ){
					++first1;
				}
			}else if( comp(*first2, *first1) ){

				//Elliminate duplicates
				InputIterator2 temp = first2;
				while( first2 != last2 && !comp( *temp, *first2) ){
					++first2;
				}

			}else{	//They are identical - skip
				//Elliminate duplicates
				InputIterator1 temp = first1;
				while( first1 != last1 && !comp( *temp, *first1) ){
					++first1;
				}
				while( first2 != last2 && !comp( *temp, *first2) ){
					++first2;
				}
			}
		}

		//Clean up remaining elements
		while(first1 != last1){
			*result = *first1;
			++result;
			InputIterator1 temp = first1;
			while( first1 != last1 && !comp( *temp, *first1) ){
				++first1;
			}
		}

		return result;
	}
	template<class InputIterator1, class InputIterator2, class OutputIterator> _UCXXEXPORT
		OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2, OutputIterator result)
	{
		less<typename iterator_traits<InputIterator1>::value_type> c;
		return set_symmetric_difference(first1, last1, first2, last2, result, c);
	}
	template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare> _UCXXEXPORT
		OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp)
	{
		while( first1 != last1 && first2 != last2){
			if( comp(*first1, *first2) ){
				*result = *first1;
				++result;

				//Elliminate duplicates
				InputIterator1 temp = first1;
				while( first1 != last1 && !comp( *temp, *first1) ){
					++first1;
				}
			}else if( comp(*first2, *first1) ){
				*result = *first2;
				++result;

				//Elliminate duplicates
				InputIterator2 temp = first2;
				while( first2 != last2 && !comp( *temp, *first2) ){
					++first2;
				}

			}else{	//They are identical - skip
				//Elliminate duplicates
				InputIterator1 temp = first1;
				while( first1 != last1 && !comp( *temp, *first1) ){
					++first1;
				}
				while( first2 != last2 && !comp( *temp, *first2) ){
					++first2;
				}
			}
		}

		//Clean up remaining elements
		while(first1 != last1){
			*result = *first1;
			++result;
			InputIterator1 temp = first1;
			while( first1 != last1 && !comp( *temp, *first1) ){
				++first1;
			}
		}

		while(first2 != last2){
			*result = *first2;
			++result;
			InputIterator2 temp = first2;
			while( first2 != last2 && !comp( *temp, *first2) ){
				++first2;
			}
		}

		return result;
	}

	// _lib.alg.heap.operations_, heap operations:

	template<class RandomAccessIterator> _UCXXEXPORT
		void push_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		less<typename iterator_traits<RandomAccessIterator>::value_type> c;
		push_heap(first, last, c);
	}

	template<class RandomAccessIterator, class Compare> _UCXXEXPORT
		void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
	{
		// *(last - 1) is the last element
		RandomAccessIterator begin, middle, end;
		begin = first;
		end = last - 2;
		if(last - first < 2){		//Empty heap
			return;
		}
		if ( comp(*(last-1), *end) ){	//Belongs past the end - already in place
			return;
		}
		while(end - begin > 1){
			middle = begin + ((end - begin)/2);
			if( comp(*middle, *(last-1) ) ){
				end = middle;
			}else{
				begin = middle;
			}
		}

		if( comp(*begin, *(last-1)) ){
			middle = begin;
		}else{
			middle = end;
		}

		//Now all we do is swap the elements up to the begining
		--last;

		while(last > middle){
			iter_swap(last, last-1);
			--last;
		}
	}

	template<class RandomAccessIterator> _UCXXEXPORT
		void pop_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		less<typename iterator_traits<RandomAccessIterator>::value_type> c;
		pop_heap(first, last, c);
	}
	template<class RandomAccessIterator, class Compare> _UCXXEXPORT
		void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare)
	{
		--last;
		while(first < last){
			iter_swap( first, first+1);
			++first;
		}
	}

	template<class RandomAccessIterator> _UCXXEXPORT
		void make_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		less<typename iterator_traits<RandomAccessIterator>::value_type> c;
		make_heap(first, last, c);
	}
	template<class RandomAccessIterator, class Compare> _UCXXEXPORT
		void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
	{
		sort( reverse_iterator<RandomAccessIterator>(last), reverse_iterator<RandomAccessIterator>(first), comp);
	}
	template<class RandomAccessIterator> _UCXXEXPORT
		void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		less<typename iterator_traits<RandomAccessIterator>::value_type> c;
		sort_heap(first, last, c);
	}
	template<class RandomAccessIterator, class Compare> _UCXXEXPORT
		void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
	{
		sort( first, last, comp);
	}


	// _lib.alg.min.max_, minimum and maximum:
	template<class T> _UCXXEXPORT
		const T& min(const T& a, const T& b)
	{
		if(b < a){
			return b;
		}
		return a;
	}

	template<class T, class Compare> _UCXXEXPORT
		const T& min(const T& a, const T& b, Compare comp)
	{
		if( comp(b, a) == true){
			return b;
		}
		return a;
	}

	template<class T> _UCXXEXPORT
		const T& max(const T& a, const T& b)
	{
		if( a < b){
			return b;
		}
		return a;
	}

	template<class T, class Compare> _UCXXEXPORT
		const T& max(const T& a, const T& b, Compare comp)
	{
		if( comp(a, b) ){
			return b;
		}
		return a;
	}

	template<class ForwardIterator> _UCXXEXPORT
		ForwardIterator min_element(ForwardIterator first, ForwardIterator last)
	{
		less<typename iterator_traits<ForwardIterator>::value_type> c;
		return min_element(first, last, c);
	}

	template<class ForwardIterator, class Compare> _UCXXEXPORT
		ForwardIterator min_element(ForwardIterator first, ForwardIterator last, Compare comp)
	{
		ForwardIterator retval = first;
		++first;
		while(first != last){
			if( comp( *first, *retval) ){
				retval = first;
			}
			++first;
		}
		return retval;
	}

	template<class ForwardIterator> _UCXXEXPORT
		ForwardIterator max_element(ForwardIterator first, ForwardIterator last)
	{
		less<typename iterator_traits<ForwardIterator>::value_type> c;
		return max_element(first, last, c);
	}

	template<class ForwardIterator, class Compare> _UCXXEXPORT
		ForwardIterator max_element(ForwardIterator first, ForwardIterator last, Compare comp)
	{
		ForwardIterator retval = first;
		++first;
		while(first != last){
			if( comp( *retval, *first ) ){
				retval = first;
			}
			++first;
		}
		return retval;
	}

	template<class InputIterator1, class InputIterator2> _UCXXEXPORT
		bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2)
	{
		less<typename iterator_traits<InputIterator1>::value_type> c;
		return lexicographical_compare(first1, last1, first2, last2, c);
	}

	template<class InputIterator1, class InputIterator2, class Compare> _UCXXEXPORT
		bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while(first1 != last1 && first2 != last2){
			if( comp(*first1, *first2) ){
				return true;
			}
			if( comp(*first2, *first1) ){
				return false;
			}
			++first1;
			++first2;
		}
		return first1==last1 && first2 != last2;
	}

	// _lib.alg.permutation.generators_, permutations
	template<class BidirectionalIterator> _UCXXEXPORT
		bool next_permutation(BidirectionalIterator first, BidirectionalIterator last)
	{
		less<typename iterator_traits<BidirectionalIterator>::value_type> c;
		return next_permutation(first, last, c);
	}

	template<class BidirectionalIterator, class Compare> _UCXXEXPORT
		bool next_permutation(BidirectionalIterator first, BidirectionalIterator last, Compare comp)
	{
		if(first == last){
			return false;	// No data
		}
		BidirectionalIterator i = last;
		--i;
		if(i == first){
			return false;	//Only one element
		}
		BidirectionalIterator ii = i;
		--ii;
		//If the last two items are in order, swap them and call it done
		if( comp(*ii, *i) ){
			iter_swap(ii, i);
			return true;
		}


		//This part of the algorithm copied from G++ header files ver. 3.4.2
		i = last;
		--i;
		for(;;){
			ii = i;
			--i;
			if ( comp(*i, *ii) ){
				BidirectionalIterator j = last;
				--j;
				while ( !comp(*i, *j)){
					--j;
				}
				iter_swap(i, j);
				reverse(ii, last);
				return true;
			}
			if (i == first){
				reverse(first, last);
				return false;
			}
		}


	}

	template<class BidirectionalIterator> _UCXXEXPORT
		bool prev_permutation(BidirectionalIterator first, BidirectionalIterator last)
	{
		less<typename iterator_traits<BidirectionalIterator>::value_type> c;
		return prev_permutation(first, last, c);
	}

	template<class BidirectionalIterator, class Compare> _UCXXEXPORT
		bool prev_permutation(BidirectionalIterator first, BidirectionalIterator last, Compare comp)
	{
		if(first == last){
			return false;	// No data
		}
		BidirectionalIterator i = last;
		--i;
		if(i == first){
			return false;	//Only one element
		}
		BidirectionalIterator ii = i;
		--ii;
		//If the last two items are in reverse order, swap them and call it done
		if( comp(*i, *ii) ){
			iter_swap(ii, i);
			return true;
		}

		//Copied from GNU GCC header files version 3.4.2
		i = last;
		--i;

		for(;;){
			ii = i;
			--i;
			if ( comp(*ii, *i)){
				BidirectionalIterator j = last;
				--j;
				while ( !comp(*j, *i)){
					--j;
				}
				iter_swap(i, j);
				reverse(ii, last);
				return true;
			}
			if (i == first){
				reverse(first, last);
				return false;
			}
		}

	}

}

#pragma GCC visibility pop

#endif



