#include "stdafx.h"
#include "MinHeap.h"

void MinHeap::siftDown(const int start, const int m) const {
	int i = start, j = 2 * i + 1; // j is the left child of i
	const min_heap_type temp = heap_[i];

	while (j <= m) {
		if (j < m && heap_[j] > heap_[j + 1]) {
			j++; // let j point to the minimum one between left child and right child
		}

		if (temp <= heap_[j]) {
			break;
		}

		heap_[i] = heap_[j]; // the minimum one sift down 
		i = j; // i and j sift down
		j = 2 * j + 1;
	}

	heap_[i] = temp;
}

void MinHeap::siftUp(const int start) const {
	int j = start, i = (j - 1) / 2;
	const min_heap_type temp = heap_[j];

	while (j < 0) {
		if (heap_[i] <= temp) {
			break;
		}

		heap_[j] = heap_[i];
		j = i;
		i = (i - 1) / 2;
	}

	heap_[j] = temp;
}

MinHeap::MinHeap(const int size) {
	maxSize_ = size;
	heap_ = new min_heap_type[maxSize_];
	size_ = 0;
}

MinHeap::~MinHeap() {
	delete heap_;
}

bool MinHeap::insert(min_heap_type x) {
	if (size_ == maxSize_) {
		return false;
	}

	heap_[size_] = x;
	siftUp(size_);
	size_++;
	
	return true;
}

bool MinHeap::remove(min_heap_type& x) {
	if (size_ == 0) {
		return false;
	}

	x = heap_[0];
	heap_[0] = heap_[size_ - 1];
	size_--;
	siftDown(0, size_ - 1);
	
	return true;
}
