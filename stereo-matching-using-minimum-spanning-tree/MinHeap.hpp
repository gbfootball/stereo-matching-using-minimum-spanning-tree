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
	/*
	 * "siftDown" function is used in "remove" function.
	 * 
	 * When we have removed one node in MinHeap, we replace the last node and the first node, and then minus the size of MinHeap
	 * which means the first node has been deleted and the last node has been putted in the root of the heap.
	 * 
	 * In this case, we really need to adjust the structure of heap.
	 * 
	 * In this function's args, "start" means the beginning adjusting position and "m" means the number of adjusting nodes.
	 *  
	 * Here is the steps:
	 *     1. We use varible "i" to point to "start", varible "j" to point to the left child of "i", varible "temp" to save value
	 *        of node which "start" points;
	 *     2. By comparation, we let "j" point to the minimum one of children node of "i";
	 *     3. If the value of "temp" is less than which "j" points, that means the sub heap is right. So we don't need to adjust
	 *        the heap at all.
	 *     4. Otherwise, we need to exchange the position of the node "i" points and "j" points;
	 *     5. Based on upper operation, we just need to adjust the structure of next layer in sub heap;
	 *     6. Iterate step 2 to step 5 until the min heap is right.
	 */

	int i = start, j = 2 * i + 1;
	const Data temp = heap_[i];

	while (j <= m) {
		if (j < m && heap_[j] > heap_[j + 1]) {
			j++;
		}

		if (temp <= heap_[j]) {
			break;
		}

		heap_[i] = heap_[j];
		i = j;
		j = 2 * j + 1;
	}

	heap_[i] = temp;
}

template <class Data>
void MinHeap<Data>::siftUp(const int start) const {
	/*
	 * "siftUp" function is used in "insert" function.
	 *
	 * When we insert one node in MinHeap, the inserted node is at the last position of heap.
	 * 
	 * Avoiding that the inserted node is the minimum node but its position is not in the root of the heap, we use "siftUp" to 
	 * adjust the structure of heap.
	 * 
	 * We compare the new node with its parent node. If the parent node is less than new node, we don't exchange them. Otherwise, 
	 * we need to exchange them.
	 * 
	 * Repeat these operation until the new node is less than its parent node.
	 */

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
