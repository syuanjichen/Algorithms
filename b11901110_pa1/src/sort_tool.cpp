// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
//  Modify     [2024/9/2 Meng-Chen Wu]
// **************************************************************************

#include "sort_tool.h"
#include <climits>
#include <iostream>
// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    if(data.size() > 1)
    {	
	int j, key;   
        for(int i = 1 ; i < data.size() ; i++)
        {	
	    key = data.at(i);
	    j = i - 1;
	    while(j >= 0 && data.at(j) > key)
	    {
		data.at(j + 1) = data.at(j);
	    	j = j - 1;
	    }
	    data.at(j + 1) = key;
        }
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data,int f){
    QuickSortSubVector(data, 0, data.size() - 1, f);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high, const int flag) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    // flag == 0 -> normal QS
    // flag == 1 -> randomized QS
    if(low < high)
    {
    	int q;
	if(flag == 0)
	    q = Partition(data, low, high);
	if(flag == 1)
	    q = RandomizedPartition(data, low, high);

	QuickSortSubVector(data, low, q - 1, flag);
	QuickSortSubVector(data, q + 1, high, flag);
    }
}
int SortTool::RandomizedPartition(vector<int>& data, int low, int high){
    // Function : RQS's Partition the vector 
    // TODO : Please complete the function
    srand(time(0));

    int i = low + (rand() % (high - low + 1)), temp;

    temp = data.at(high);
    data.at(high) = data.at(i);
    data.at(i) = temp;

    return Partition(data, low, high);
}
int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    int i = low - 1, temp;
    for(int j = low ; j < high ; j++)
    {
    	if(data.at(j) <= data.at(high))
	    {
	        i++;
	        temp = data.at(j);
	        data.at(j) = data.at(i);
	        data.at(i) = temp;
	    }
    }

    temp = data.at(high);
    data.at(high) = data.at(i + 1);
    data.at(i + 1) = temp;

    return i + 1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(low < high)
    {
	    int mid = (int)((low + high)/2);
	    MergeSortSubVector(data, low, mid);
	    MergeSortSubVector(data, mid + 1, high);
	    Merge(data, low, mid, mid + 1, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int element_left, element_right, index_left, index_right;
    element_left = middle1 - low + 1;
    element_right = high - middle2 + 1;

    vector<int> left(element_left + 1, 0);
    vector<int> right(element_right + 1, 0);

    for(int i = 0 ; i < element_left ; i++)
	left.at(i) = data.at(low + i);

    for(int j = 0 ; j < element_right ; j++)
	right.at(j) = data.at(middle2 + j);

    left.at(element_left) = INT_MAX;
    right.at(element_right) = INT_MAX;

    index_left = 0;
    index_right = 0;

    for(int k = low ; k <= high ; k++)
    {
    	if(left.at(index_left) <= right.at(index_right))
	    {
	        data.at(k) = left.at(index_left);
	        index_left++;
	    }
	    else
	    {
	        data.at(k) = right.at(index_right);
	        index_right++;
	    }
    }
}

// bottom-up style implementation of merge sort
void SortTool::BottomUpMergeSort(vector<int>& data) 
{
  /*TODO :
    Implement merge sort in bottom-up style, in other words,
    without recursive function calls.
    Hint: 
    1. Divide data to n groups of one data each group
    2. Iteratively merge each pair of 2 neighbor groups into one larger group
    3. Finally we obtain exactly one sorted group
  */
    int numGroup = data.size();
    int groupMem = 1;
    while(numGroup > 1)
    {
        int i = 0;
        while(i < data.size())
        {
	    int start = i;
	    int middle  = ((i + groupMem) < data.size()) ? (i + groupMem) : data.size();
	    int end = ((i + groupMem * 2) < data.size()) ? (i + groupMem * 2) : data.size();

            vector<int> left(data.begin() + start, data.begin() + middle);
            vector<int> right(data.begin() + middle, data.begin() + end);

	    left.push_back(INT_MAX);
	    right.push_back(INT_MAX);

            vector<int> merged(left.size() + right.size());
            
	    int left_index = 0, right_index = 0;

	    while(left_index < left.size() && right_index < right.size())
	    {
	    	if(left[left_index] <= right[right_index])
		{
		    merged[left_index + right_index] = left[left_index];
		    left_index++;
		}
		else
		{
		    merged[left_index + right_index] = right[right_index];
		    right_index++;
		}
	    }

	    if(left_index < left.size())
	    {
	    	for(int j = left_index ; j < left.size() ; j++)
		    merged[j + right_index] = left[j];
	    }

	    if(right_index < right.size())
	    {
	    	for(int j = right_index ; j < right.size() ; j++)
		    merged[left_index + j] = right[j];
	    }

	    for(int j = 0 ; j < end - start ; j++)
		data[i + j] = merged[j];

            i = i + groupMem * 2;
            
        }
        
        numGroup = (numGroup % 2 == 0) ? (numGroup / 2) : ((numGroup/2) + 1);
        groupMem = groupMem * 2;
    }
}

// Heap sort method, be aware that you are NOT required to implement heap sort in PA1
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int left, right, heap_max_index, temp;
    left = 2 * root + 1;
    right = 2 * root + 2;
    
    if(left < heapSize && data.at(left) > data.at(root))
    	heap_max_index = left;
    else
	    heap_max_index = root;

    if(right < heapSize && data.at(right) > data.at(heap_max_index))
	    heap_max_index = right;

    if(heap_max_index != root)	
    {
    	temp = data.at(heap_max_index);
	    data.at(heap_max_index) = data.at(root);
	    data.at(root) = temp;

	    MaxHeapify(data, heap_max_index);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i = ((int)(data.size() / 2) - 1) ; i >= 0 ; i--)
    	MaxHeapify(data, i);
}
