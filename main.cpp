#include <string>
#include <iostream>
#include <vector>

using namespace std;

// Zaid Ajaj / s4807561 / Informatica & Wiskunde

// Part 1
//
// the function `easter` performs math operations a constant number of times
// therefore the function `easter` runs in O(1)
// 
// the function `is_prime` performs a loop where
// [divisor <= sqrt(x)], [divisor++] and [x % divisor == 0] are performed sqrt(x) times
// other operations are performed in constant time regardless of input
// so the function `is_prime` runs in O(3*sqrt(x) + k) time = O(sqrt(x))  

// Part 2
//
// exercises
// xs = [15, 40, 42, -15, 30, 35, 5]
// Phase 1 - build_heap(xs)
//  
//          15
//        /    \  
//      40     42 
//     / \    /  \  
//  -15  30  35   5
// ==================
//          42
//        /    \  
//      40     15 
//     / \    /  \  
//  -15  30  35   5
// ==================
//          42
//        /    \  
//      40     35 
//     / \    /  \  
//  -15  30  15   5
// ==================
//           42
//        /     \  
//      40      35   
//     / \     /  \  
//  -15  30  15    5

// Phase 2
//  [42, 40, 35, -15, 30, 15, 5]
//           42
//        /     \  
//      40      35   
//     / \     /  \  
//  -15  30  15    5 
// ===================
//  [5, 40, 35, -15, 30, 15, 42]
//           5
//        /     \  
//      40      35   
//     / \     /  \  
//  -15  30  15    42 
// ===================
//  [40, 5, 35, -15, 30, 15, 42]
//           40
//        /     \  
//      5       35   
//     / \     /  \  
//  -15  30  15    42 
// ===================
//  [15, 5, 35, -15, 30, 40, 42]
//           15
//        /     \  
//      5       35   
//     / \     /  \  
//  -15  30  40    42 
// ===================
//  [35, 5, 15, -15, 30, 40, 42]
//           35
//        /     \  
//      5       15   
//     / \     /  \  
//  -15  30  40    42 
// ===================
//  [30, 5, 15, -15, 35, 40, 42]
//           30
//        /     \  
//      5       15   
//     / \     /  \  
//  -15  35  40    42 
// ===================
//  [-15, 5, 15, 30, 35, 40, 42]
//          -15
//        /     \  
//      5       15   
//     / \     /  \  
//  30  35  40    42 
// ===================

// push_down and push_down take one path of the tree => O(log n)
// build_heap and pick_heap go through all elements => O(n)

void swap(vector<int>& input, int i, int j)
{
    int temp = input[i];
    input[i] = input[j];
    input[j] = temp;
}


int parent_index(vector<int>& xs, int childIndex, int maxIndex)
{
    int parentIndex = (childIndex - 1) / 2;
    if (parentIndex < 0 || parentIndex > maxIndex) {
        return -1;
    }
    
    return parentIndex;
}

void build_heap(vector<int>& input) 
{
    int maxIndex = input.size() - 1;
    for(int currentNodeIndex = 0; currentNodeIndex <= maxIndex; currentNodeIndex++) {
        int parentNodeIndex = parent_index(input, currentNodeIndex, maxIndex);

        if (parentNodeIndex == -1) {
            // no parent found
            continue;
        }

        // push_up function as a while loop
        while (input[parentNodeIndex] < input[currentNodeIndex]) {
            swap(input, parentNodeIndex, currentNodeIndex);
            currentNodeIndex = parentNodeIndex;
            parentNodeIndex = parent_index(input, parentNodeIndex, maxIndex);
            
            if (parentNodeIndex == -1) break;
        }
    }
}

void push_down(vector<int>& input, int maxIndex, int parent)
{
    int rootIndex = parent;
    int leftChildIndex = parent * 2 + 1;
    int rightChildIndex = parent * 2 + 2;

    if (leftChildIndex < maxIndex && input[leftChildIndex] > input[parent]) {
        parent = leftChildIndex;
    } 

    if (rightChildIndex < maxIndex && input[rightChildIndex] > input[parent]) {
        parent = rightChildIndex;
    }

    if (parent != rootIndex) {
        // parent has changed
        swap(input, rootIndex, parent);
        push_down(input, maxIndex, parent);
    }
}

void pick_heap(vector<int>& input)
{
    int maxIndex = input.size() - 1;
    for(int lastIndex = maxIndex; lastIndex >= 0; lastIndex--) {    
        int rootIndex = 0;
        swap(input, rootIndex, lastIndex);
        push_down(input, lastIndex, rootIndex);
    }
}


void heap_sort(vector<int>& input)
{
    build_heap(input);
    pick_heap(input);
}


int main()
{
    vector<int> input;

    input.push_back(1);
    input.push_back(2);
    input.push_back(6);
    input.push_back(3);
    input.push_back(4);
    input.push_back(8);
    input.push_back(5);
    input.push_back(7);


    cout << "Before:" << endl;
    for(int i = 0; i < input.size(); i++) {
        cout << "result[" << i << "] = " << input[i] << endl;
    }

    build_heap(input);
    cout << "After build_heap:" << endl;
    for(int i = 0; i < input.size(); i++) {
        cout << "result[" << i << "] = " << input[i] << endl;
    }

    pick_heap(input);
    cout << "After pick_heap: " << endl;
        for(int i = 0; i < input.size(); i++) {
        cout << "result[" << i << "] = " << input[i] << endl;
    }

    return 0;
}