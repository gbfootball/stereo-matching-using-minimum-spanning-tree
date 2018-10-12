#ifndef MIN_HEAP_H
#define MIN_HEAP_H

template <class Data>
class MinHeap {
public:
	explicit MinHeap(int size);
	~MinHeap();
	bool insert(Data x);
	bool remove(Data& x);
private:
	Data* heap_;
	int maxSize_;
	int size_;

	void siftDown(int start, int m) const;
	void siftUp(int start) const;
};

template <class Data>
void MinHeap<Data>::siftDown(const int start, const int m) const {
	int i = start, j = 2 * i + 1; // j is the left child of i
	const Data temp = heap_[i];

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

template <class Data>
void MinHeap<Data>::siftUp(const int start) const {
	int j = start, i = (j - 1) / 2;
	const Data temp = heap_[j];

	while (j > 0) {
		if (heap_[i] <= temp) {
			break;
		}

		heap_[j] = heap_[i];
		j = i;
		i = (i - 1) / 2;
	}

	heap_[j] = temp;
}

template <class Data>
MinHeap<Data>::MinHeap(const int size) {
	maxSize_ = size;
	heap_ = new Data[maxSize_];
	size_ = 0;
}

template <class Data>
MinHeap<Data>::~MinHeap() {
	delete heap_;
}

template <class Data>
bool MinHeap<Data>::insert(Data x) {
	if (size_ == maxSize_) {
		return false;
	}

	heap_[size_] = x;
	siftUp(size_);
	size_++;

	return true;
}

template <class Data>
bool MinHeap<Data>::remove(Data& x) {
	if (size_ == 0) {
		return false;
	}

	x = heap_[0];
	heap_[0] = heap_[size_ - 1];
	size_--;
	siftDown(0, size_ - 1);

	return true;
}

#endif MIN_HEAP_H
