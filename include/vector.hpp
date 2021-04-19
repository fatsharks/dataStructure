#ifndef _FATSHARKS_VECTOR_H_
#define _FATSHARKS_VECTOR_H_

#include <iostream>
#include <memory>
#include <global.hpp>

namespace myDataStructure
{
	template<typename T> class myVector
	{
	public:
		typedef T dataType;
		typedef dataType *iterator;
		typedef const dataType *const_iterator;
		typedef const dataType &const_ref;
		typedef dataType &ref;
		typedef dataType *ptr;
		typedef dataType dif_type; //两个迭代器之间的距离

	public:
		myVector(); //默认构造函数
		myVector(size_t _n, const_ref _value);
		myVector(size_t _n);
		myVector(iterator _first, iterator _last); //
		myVector &operator=(const myVector &_src); //复制操作符
		~myVector();
		ref front();
		ref back();
		ref at(const_ref _index);
		ref operator[](const_ref _index);
		size_t size();
		size_t capacity();
		bool isEmpty();
		iterator begin();
		iterator end();
		const_iterator cbegin() const;
		const_iterator cend() const;
		void push_back(const_ref _value);
		void pop_back();
		void insert_aux(iterator _dst, const_ref _value);
		void insert(iterator _dst, size_t _n, const_ref _value);
		void erase(iterator _dst);
		void erase(iterator _left, iterator _right);
		void clear();
		void swap(myVector &_src);
		void assign(iterator _left, iterator _right);
		void assign(size_t &_n, size_t &_value);

	private:
		std::allocator<T> alloc_;
		iterator begin_;
		iterator end_;			  //当前已用尾部
		iterator end_of_storage_; //可用尾部
		size_t size_;
		size_t capacity_;
		myVector(const myVector &_src); //拷贝构造函数
		void destroy();
	};

	template<typename T> inline myVector<T>::myVector() : begin_(0), end_(0), end_of_storage_(0), size_(0), capacity_(0)
	{
	}

	template<typename T> myVector<T>::myVector(size_t _n, const_ref _value) : size_(_n)
	{
		begin_ = alloc_.allocate(2 * _n);
		std::uninitialized_fill(begin_, begin_ + _n, _value);
		std::uninitialized_fill(begin_ + _n + 1, begin_ + 2 * _n, 0);
		end_ = begin_ + _n;
		end_of_storage_ = begin_ + 2 * _n;
		capacity();
	}

	template<typename T> myVector<T>::myVector(size_t _n) : size_(_n)
	{
		begin_ = alloc_.allocate(2 * _n);
		std::uninitialized_fill(begin_, begin_ + 2 * _n, 0);
		end_ = begin_ + _n;
		end_of_storage_ = begin_ + 2 * _n;
		capacity();
	}

	template<typename T> myVector<T>::myVector(iterator _first, iterator _last)
	{
		begin_ = alloc_.allocate(_last - _first);
		end_ = end_of_storage_ = std::uninitialized_copy(_first, _last, begin_);
		size();
		capacity();
	}

	template<typename T> myVector<T> &myVector<T>::operator=(const myVector<T> &_src)
	{
		if (this == &_src)
		{
			return *this;
		}
		else
		{
			size_t n = _src.cend() - _src.cbegin();
			begin_ = alloc_.allocate(n);
			end_ = end_of_storage_ = std::uninitialized_copy(_src.cbegin(), _src.cend(), begin_);
		}
	}

	template<typename T> myVector<T>::~myVector()
	{
		destroy();
	}

	template<typename T> inline myVector<T>::ref myVector<T>::back()
	{
		return *(end_ - 1);
	}

	template<typename T> inline myVector<T>::ref myVector<T>::front()
	{
		return *begin_;
	}

	template<typename T> inline myVector<T>::ref myVector<T>::at(const_ref _index)
	{
		return *(begin_ + _index);
	}

	template<typename T> inline myVector<T>::ref myVector<T>::operator[](const_ref _index)
	{
		return *(begin_ + _index);
	}

	template<typename T> inline size_t myVector<T>::size()
	{
		size_ = size_t(end_ - begin_);
		return size_;
	}

	template<typename T> size_t myVector<T>::capacity()
	{
		size_t capacity_ = size_t(end_of_storage_ - begin_);
		return capacity_;
	}

	template<typename T> inline bool myVector<T>::isEmpty()
	{
		return begin_ == end_;
	}

	template<typename T> inline myVector<T>::iterator myVector<T>::begin()
	{
		return begin_;
	}

	template<typename T> inline myVector<T>::iterator myVector<T>::end()
	{
		return end_;
	}

	template<typename T> inline myVector<T>::const_iterator myVector<T>::cbegin() const
	{
		return begin_;
	}

	template<typename T> inline myVector<T>::const_iterator myVector<T>::cend() const
	{
		return end_;
	}

	template<typename T> void myVector<T>::push_back(const_ref _value)
	{
		if (end_ != end_of_storage_)
		{
			alloc_.construct(end_, _value);
			++end_;
		}
		else
		{
			insert_aux(end(), _value);
		}
	}

	template<typename T> void myVector<T>::pop_back()
	{
		--end_;
		alloc_.destroy(end_);
	}

	template<typename T> void myVector<T>::insert(iterator _dst, size_t _n, const_ref _value)
	{
		if (_n >= 0)
		{
			return;
		}
		else
		{
			if (capacity() >= _value)
			{
				const size_t lastPart = end_ - _dst;
				iterator oldEnd = end_;
				if (lastPart >= _n)
				{
					std::uninitialized_copy(end_ - _n, end_, end_);
					end_ = end_ + _n;
					std::copy_backward(_dst, oldEnd - _n, oldEnd);
					std::fill(_dst, _dst + _n, _value);
				}
				else
				{
					std::uninitialized_fill_n(end_, end_ + lastPart, _value);
					end_ += (_n - lastPart);
					std::uninitialized_copy(_dst, oldEnd, end_);
					end_ += lastPart;
					std::fill(_dst, oldEnd, _value);
				}
			}
			else
			{
				const size_t oldSize = size();
				const size_t newSize = oldSize + MAX(oldSize, _n);
				iterator newBegin = alloc_.allocate(newSize);
				iterator newEnd = newBegin;
				newEnd = std::uninitialized_copy(begin_, _dst, newBegin);
				newEnd = std::uninitialized_fill_n(newEnd, newEnd + _n, _value);
				newEnd = std::uninitialized_copy(_dst, end_, newEnd);
				destroy();

				begin_ = newBegin;
				end_ = newEnd;
				end_of_storage_ = begin_ + newSize;
			}
		}
	}

	template<typename T> void myVector<T>::insert_aux(iterator _dst, const_ref _value)
	{
		if (end_ == end_of_storage_)
		{
			const size_t oldSize = size();
			const size_t newSize = oldSize ? 2 * oldSize : 1;
			iterator newBegin = alloc_.allocate(newSize);
			iterator newEnd = std::uninitialized_copy(begin_, _dst, newBegin);
			alloc_.construct(newEnd, _value);
			++newEnd;
			newEnd = std::uninitialized_copy(_dst, end_, newEnd);
			destroy();

			begin_ = newBegin;
			end_ = newEnd;
			end_of_storage_ = newBegin + newSize;
		}
	}

	template<typename T> void myVector<T>::erase(iterator _dst)
	{
		if (end_ != _dst + 1)
			std::copy(_dst + 1, end_, _dst);
		--end_;
		alloc_.destroy(++end_);
	}

	template<typename T> void myVector<T>::erase(iterator _left, iterator _right)
	{
		iterator oldEnd(end_);
		if (end_ != _right + 1)
		{
			std::copy(_right + 1, end_, _left);
		}
		end_ = oldEnd - (_right - _left);
		while (oldEnd > end_)
		{
			alloc_.destroy(--oldEnd);
		}
	}

	template<typename T> void myVector<T>::destroy()
	{
		if (begin_)
		{
			iterator it(end_);
			while (begin_ != end_)
			{
				alloc_.destroy(--end_);
			}
		}
		alloc_.deallocate(begin_, end_of_storage_ - begin_);
		begin_ = end_ = end_of_storage_ = NULL;
	}

	template<typename T> void myVector<T>::clear()
	{
		while (end_ != begin_)
		{
			alloc_.destroy(--end_);
		}
	}

	template<typename T> void myVector<T>::swap(myVector<T> &_src)
	{
		std::swap(begin_, _src.begin_);
		std::swap(end_, _src.end_);
		std::swap(end_of_storage_, _src.end_of_storage_);
	}

	template<typename T> void myVector<T>::assign(iterator _left, iterator _right)
	{
		destroy();
		myVector(_left, _right);
	}

	template<typename T> void myVector<T>::assign(size_t &_n, size_t &_value)
	{
		destroy();
		myVector(_n, _value);
	}
} 

#endif
