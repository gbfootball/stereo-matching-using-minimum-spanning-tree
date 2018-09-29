#ifndef MIN_HEAP_H
#define MIN_HEAP_H

typedef uchar min_heap_type;

class MinHeap {
	min_heap_type* heap_;
	int maxSize_;
	int size_;

	void siftDown(int start, int m) const;
	void siftUp(int start) const;

public:
	explicit MinHeap(int size);
	~MinHeap();
	bool insert(min_heap_type x);
	bool remove(min_heap_type& x);
};

#endif MIN_HEAP_H
