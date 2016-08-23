/*
 * DequeIterator.h
 * v1
 *
 *  Created on: Aug 23, 2016
 *      Author: iainhemstock
 */

#ifndef DEQUEITERATOR_H_
#define DEQUEITERATOR_H_
#include <ostream>
using namespace std;

namespace prism {
//================================================================================
// DequeBlock
//================================================================================
template <class T>
struct Block {
	struct memory {
		static const int BLOCKSIZE = 8;
		T* start;	//the start of the storage
		T* finish;	// the end of the storage
		T* begin;	// the first element
		T* end;		// one position past the last element
		memory() {
			start = new T[BLOCKSIZE];
			finish = start + BLOCKSIZE;
			begin = start;
			end = finish;
		}
		~memory() { delete []start; }
	};
	memory storage;
};
//================================================================================
// DequeIterator
//================================================================================
template <class T>
class DequeIterator {
private:
	T* p_;
	Block<T>** map_;
	Block<T>* block_;
public:
	/**
	 *
	 */
	DequeIterator()
		: p_(0), map_(0), block_(0)
	{
	}
	/**
	 *
	 */
	DequeIterator(T* p, Block<T>** map)
		: p_(p), map_(map), block_(*map_)
	{

	}

	/**
	 *
	 */
	DequeIterator(const DequeIterator& copy)
		: p_(copy.p_), map_(copy.map_), block_(copy.block_)
	{

	}

	/**
	 *
	 */
	T& operator*()
	{
		return *p_;
	}

	/**
	 *
	 */
	T* operator->()
	{
		return p_;
	}

	/**
	 *
	 */
	DequeIterator operator+(const int i)
	{
		if (p_+i >= block_->storage.finish) {
			setMap_(map_+1);
			p_ = block_->storage.start;
		}
		return DequeIterator(p_, map_);
	}

	/**
	 *
	 */
	DequeIterator& operator++()
	{
		p_++;
		if (p_ == block_->storage.finish) {
			setMap_(map_+1);
			p_ = block_->storage.start;
		}

		return *this;
	}

	/**
	 *
	 */
	DequeIterator operator++(const int junk)
	{
		T* tmp = p_;
		p_++;
		if (p_ == block_->storage.finish) {
			setMap_(map_+1);
			p_ = block_->storage.start;
		}

		return DequeIterator(tmp, map_);
	}

	/**
	 *
	 */
	DequeIterator& operator--() {
		p_--;
		if (p_ < block_->storage.start) {
			setMap_(map_-1);
			p_ = block_->storage.end-1;
		}
		return *this;
	}

	/**
	 *
	 */
	DequeIterator operator--(int junk) {
		T* tmp = p_;
		p_--;
		if (p_ < block_->storage.start) {
			setMap_(map_-1);
			p_ = block_->storage.end-1;
		}
		return DequeIterator(tmp, map_);
	}

	/**
	 *
	 */
	DequeIterator& operator=(const DequeIterator& other)
	{
		if (*this != other) {
			*this = DequeIterator(p_, map_);
		}
		return *this;

	}

	// related non members
	//--------------------

	/**
	 *
	 */
	friend const bool operator==(const DequeIterator<T>& it1, const DequeIterator<T>& it2)
	{
		return it1.p_ == it2.p_ && it1.map_ == it2.map_ && it1.block_ == it2.block_;
	}

	/**
	 *
	 */
	friend const bool operator!=(const DequeIterator<T>& it1, const DequeIterator<T>& it2)
	{
		return !(it1==it2);
	}

	/*
	 *
	 */
	friend const int operator-(const DequeIterator& lhs, const DequeIterator& rhs)
	{
		int count = 0;
		int nMaps = lhs.map_ - rhs.map_ + 1;

		if (nMaps > 1)
			count = lhs.block_->storage.end-lhs.block_->storage.begin +
						rhs.block_->storage.end-rhs.block_->storage.begin;
		else {
			count = lhs.block_->storage.end-lhs.block_->storage.begin +
						rhs.block_->storage.end-rhs.block_->storage.begin;
			count += (nMaps-2) * lhs.block_->storage.BLOCKSIZE;
		}

		return count;
	}

	/**
	 *
	 */
	friend const bool operator<(const DequeIterator& lhs, const DequeIterator& rhs)
	{
		return lhs-rhs < 0;
	}

	/**
	 *
	 */
	friend const bool operator>(const DequeIterator& lhs, const DequeIterator& rhs)
	{
		return lhs-rhs > 0;
	}

	/**
	 *
	 */
	friend const bool operator<=(const DequeIterator& lhs, const DequeIterator& rhs)
	{
		return lhs-rhs <= 0;
	}

	/**
	 *
	 */
	friend const bool operator>=(const DequeIterator& lhs, const DequeIterator& rhs)
	{
		return lhs-rhs >= 0;
	}

private:
	void setMap_(Block<T>** map) {
		map_ = map;
		block_ = *map;
	}

};

} // namespace prism









#endif /* DEQUEITERATOR_H_ */
