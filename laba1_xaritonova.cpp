#include <iostream>
#include <algorithm> 
#include <cstdlib> 

using namespace std;

//initializing a variable to indicate the array boundary
const int n = 200;

// these variables are used to count permutations and comparisons separately for quicksort and heap sort
int cp = 0, pq = 0;
int ch = 0, ph = 0;

// function for findind optimal step for shell sort
int increm(int* inter, int size) {
    int multi1 = 1, multi2 = 1, multi3 = 1, counter = -1;
    do {
        if (++counter % 2) {
            multi2 *= 2;
            inter[counter] = 8 * multi1 - 6 * multi2 + 1;
        }
        else {
            inter[counter] = 9 * multi1 - 9 * multi3 + 1;
            multi3 *= 2;
        }
        multi1 *= 2;
    } while (3 * inter[counter] < size);
    return((counter > 0) ? (--counter) : 0);
}

//shell sort function
void shell_sort(int arr[], int n) {
    int comparisons = 0;
    int swaps = 0;
    for (int step = n / 2; step > 0; step /= 2) {
        for (int i = step; i < n; i++) {
            for (int j = i - step; j >= 0; j -= step) {
                if (arr[j] > arr[j + step]) {
                    swap(arr[j], arr[j + step]);
                    swaps++;
                    comparisons++;
                }
                else
                    comparisons++;
            }
        }
    }
    cout << endl << "Comperisons: " << comparisons << "\nPermutations: " << swaps << endl << endl;
}

// shell sort with Sedgwick's algorithm
void shell_sejwick(int arr[]) {
    int comparisons = 0;
    int swaps = 0;
    int inter, arr_inter[n], count, j;
    count = increm(arr_inter, n);
    while (count >= 0) {
        inter = arr_inter[count--];
        for (int i = inter; i < n; i++) {
            int tmp = arr[i];
            for (j = i - inter; j >= 0; j -= inter) {
                if (arr[j] > arr[j + inter]) {
                    swap(arr[j], arr[j + inter]);
                    swaps++;
                    comparisons++;
                }
                else
                    comparisons++;
            }
        }
    }
    cout << endl << "Comperisons: " << comparisons << " Permutations: " << swaps << endl << endl;
}

//quick sort function
void quick_sort(int arr[], int left, int right) {
    // Check the base case if the left index is greater than the right, the array is already sorted.
    if (left > right)
        return;
    // Choose the pivot element in the middle
    int p = arr[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (arr[i] < p) {
            cp++;
            i++;
        }
        while (arr[j] > p) {
            cp++;
            j--;
        }
        if (i <= j) {
            swap(arr[i], arr[j]);
            pq++;
            i++;
            j--;
        }
    }
    quick_sort(arr, left, j);
    quick_sort(arr, i, right);
}

// function is used to build a heap from an array 
void heap_build(int arr[], int n, int root) {
    int largest = root;
    int l_child = 2 * root + 1;
    int r_child = 2 * root + 2;

    // Compare left child with the root
    if (l_child < n && arr[l_child] > arr[largest])
        largest = l_child;

    if (l_child < n)
        ch++;
    // Compare right child with the largest so far
    if (r_child < n && arr[r_child] > arr[largest])
        largest = r_child;

    if (r_child < n)
        ch++;
    // If the largest is not the root, swap and recursively build heap
    if (largest != root) {
        swap(arr[root], arr[largest]);
        ph++;
        heap_build(arr, n, largest);
    }
    ch++;
}

// heap function
void heap_sort(int arr[], int n) {
    // numnber of child of a tree equal helf the size 
    int degree = log2(n) - 1; 

    // Build the initial max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        int degree_1 = log(i + 2);
        // If the degree matches, build heap with the current root
        if (degree_1 + 1 == degree)
            heap_build(arr, n, i);
        else {
            // If degrees don't match, build heap for each child separately
            for (int j = 0; j < degree - degree_1; j++) {
                heap_build(arr, n, i * pow(2, j));
            }
        }
    }
    // Extract elements from the heap and build the sorted array
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        ph++;
        heap_build(arr, i, 0);
    }
    cout << endl << "Comperisons: " << ch << "\nPermutations: " << ph << endl << endl;
}


int da(int arr[], int copy_arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = copy_arr[i];
    return 0;
}

//shaker sort function
int shaker_sort(int array[], int n) {
    int swaps = 0;
    int comparisons = 0;

    int left = 1, right = n - 1, move = n - 1;
    while (left <= right) {
        for (int i = right; i >= left; i--) {
            if (array[i - 1] > array[i]) {
                swap(array[i - 1], array[i]);
                move = i;
                swaps++;
            }
            comparisons++;
        }
        left = move + 1;
        for (int i = left; i <= right; i++) {
            if (array[i] < array[i - 1]) {
                swap(array[i], array[i - 1]);
                move = i;
                swaps++;
            }
            comparisons++;
        }
        right = move - 1;
    }
    cout << endl << "Comparisons: " << comparisons << endl;
    return swaps;
}

// binary insertion (binary search) sort function
int sort_bin_insert(int arr[], int n) {
    int swaps = 0;
    int comparisons = 0;

    int x, left, right, sred;
    for (int i = 1; i < n; i++)
    {
        if (arr[i - 1] > arr[i])
        {
            x = arr[i];
            left = 0;
            right = i - 1;
            do
            {
                sred = (left + right) / 2;
                comparisons++; 
                if (arr[sred] < x) left = sred + 1;
                else right = sred - 1;
            } while (left <= right);

            for (int j = i - 1; j >= left; j--) {
                arr[j + 1] = arr[j];
                swaps++; 
            }
            arr[left] = x;
        }

    }
    cout << endl << "Comparisons: " << comparisons << endl;
    return swaps;
}

//insertion sort function
int InsertionSort(int arr[], int n) {
    int swaps = 0;
    int comparisons = 0;

    for (int i = 1; i < n; i++) {
        int location = i - 1;

        while (location > -1) {
            if (arr[location] > arr[location + 1]) {
                comparisons++;
                swaps++;
                swap(arr[location], arr[location + 1]);
            }

            else               
                comparisons++;
            location--;
        }
    }

    cout << endl << "Comparisons: " << comparisons << endl;


    return swaps;
}


//selection sort function
int SelectionSort(int arr[], int n) {
    int i, j, index;
    int swaps = 0;
    int comparisons = 0;

    for (i = 0; i < n - 1; i++) {
        index = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[index])
                index = j;
            comparisons++;
        }
        if (i != index) {
            swap(arr[i], arr[index]);
            swaps++;
        }
    }
    cout << endl << "Comparisons: " << comparisons << endl;
    return swaps;
}

//bubble sort function
int bubbleSort(int arr[], int n) {
    int swaps = 0;
    int comparisons = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swaps++;
            }
        }
    }
    cout << endl << "Comparisons: " << comparisons << endl;
    return swaps;
}

int main() { 

    //initialization "array_up" for generate "Sorted array" and "coppy_up" that will store copy of the "array_up"
    int array_up[n], coppy_up[n];
    //filling sorted array
    for (int i = 0; i < n; ++i) {
        array_up[i] = i;
        coppy_up[i] = array_up[i];
    }
    //initialization "array_down" for generate "Inverted array" and "coppy_down" that will store copy of the "array_down"
    int array_down[n], coppy_down[n];
    //filling inverted array
    for (int i = 0; i < n; ++i) {
        array_down[i] = n - 1 - i;
        coppy_down[i] = array_down[i];
    }
    //initialization "randomArray" for generate "Random arrray" and "coppy_random" that will store copy of the "randomArray"
    int randomArray[n], coppy_random[n];
    //filling random array
    for (int i = 0; i < n; ++i) {
        randomArray[i] = rand() % 200; 
        coppy_random[i] = randomArray[i];
    }

    cout << "/------------------------------------------------------------------------/\n";
    
    //calling bubbleSort function
    cout << "Bubble sort\n" << endl;
    cout << "\nSorted array:";
    cout << "Permutations: " << bubbleSort(array_up, n) << endl;
    cout << "\nInverted array:";
    cout << "Permutations: " << bubbleSort(array_down, n) << endl;
    cout << "\nRandom arrray:";
    cout << "Permutations::" << bubbleSort(randomArray, n) << "\n" << endl;

    cout << "/------------------------------------------------------------------------/\n";

    // calling a function that returns arrays to their original values
    da(array_up, coppy_up, n);
    da(array_down, coppy_down, n);
    da(randomArray, coppy_random, n);

    //calling Selection sort function
    cout << "Selection sort\n" << endl;
    cout << "\nSorted array:";
    cout << "Permutations: " << SelectionSort(array_up, n) << endl;
    cout << "\nInverted array:";
    cout << "Permutations: " << SelectionSort(array_down, n) << endl;
    cout << "\nRandom arrray:";
    cout << "Permutations:" << SelectionSort(randomArray, n) << "\n" << endl;

    cout << "/------------------------------------------------------------------------/\n";

    // calling a function that returns arrays to their original values
    da(array_up, coppy_up, n);
    da(array_down, coppy_down, n);
    da(randomArray, coppy_random, n);

    //calling InstrtionSort function
    cout << "Insertion Sort\n" << endl;
    cout << "\nSorted array:";
    cout << "Permutations: " << InsertionSort(array_up, n) << endl;
    cout << "\nInverted array:";
    cout << "Permutations: " << InsertionSort(array_down, n) << endl;
    cout << "\nRandom arrray:";
    cout << "Permutations:" << InsertionSort(randomArray, n) << "\n" << endl;

    cout << "/------------------------------------------------------------------------/\n";

    // calling a function that returns arrays to their original values
    da(array_up, coppy_up, n);
    da(array_down, coppy_down, n);
    da(randomArray, coppy_random, n);

    //calling skaker_sort function
    cout << "Shaker sort\n" << endl;
    cout << "\nSorted array:";
    cout << "Permutations: " << shaker_sort(array_up, n) << endl;
    cout << "\nInverted array:";
    cout << "Permutations: " << shaker_sort(array_down, n) << endl;
    cout << "\nRandom arrray:";
    cout << "Permutations:" << shaker_sort(randomArray, n) << "\n" << endl;

    cout << "/------------------------------------------------------------------------/\n";

    // calling a function that returns arrays to their original values
    da(array_up, coppy_up, n);
    da(array_down, coppy_down, n);
    da(randomArray, coppy_random, n);

    //calling sort_bin_unsert function
    cout << "Binary selection sort\n" << endl;
    cout << "\nSorted array:";
    cout << "Permutations: " << sort_bin_insert(array_up, n) << endl;
    cout << "\nInverted array:";
    cout << "Permutations: " << sort_bin_insert(array_down, n) << endl;
    cout << "\nRandom arrray:";
    cout << "Permutations:" << sort_bin_insert(randomArray, n) << "\n" << endl;

    cout << "/------------------------------------------------------------------------/\n";

    // calling a function that returns arrays to their original values
    da(array_up, coppy_up, n);
    da(array_down, coppy_down, n);
    da(randomArray, coppy_random, n);

    //calling heap_sort function
    cout << "Heap sort\n" << endl;
    cout << "\nSorted array:";
    heap_sort(array_up, n);
    cout << "\nInverted array:";
    heap_sort(array_down, n);
    cout << "\nRandom arrray:";
    heap_sort(randomArray, n);

    cout << "/------------------------------------------------------------------------/\n";

    // calling a function that returns arrays to their original values
    da(array_up, coppy_up, n);
    da(array_down, coppy_down, n);
    da(randomArray, coppy_random, n);

    // calling the quick_sort function
    cout << "Quick sort:\n" << endl;
    cout << "\nSorted array:";
    quick_sort(array_up, 0, n - 1);
    cout << endl << "Comperisons: " << cp << "\nPermutations: " << pq << endl << endl;
    cp = 0, pq = 0;
    cout << "\nInverted array:";
    quick_sort(array_down, 0, n - 1);
    cout << endl << "Comperisons: " << cp << "\nPermutations: " << pq << endl << endl;
    cp = 0, pq = 0;
    cout << "\nRandom arrray:";
    quick_sort(randomArray, 0, n - 1);
    cout << endl << "Comperisons: " << cp << "\nPermutations: " << pq << endl << endl;
    cp = 0, pq = 0;

    cout << "/------------------------------------------------------------------------/\n";

    // calling a function that returns arrays to their original values
    da(array_up, coppy_up, n);
    da(array_down, coppy_down, n);
    da(randomArray, coppy_random, n);

    //calling shell_sort function
    cout << "Shell sort:\n";
    cout << "\nSorted array:";
    shell_sort(array_up, n);
    cout << "\nInverted array:";
    shell_sort(array_down, n);
    cout << "\nRandom arrray:";
    shell_sort(randomArray, n);

    cout << "/------------------------------------------------------------------------/\n";

    // calling a function that returns arrays to their original values
    da(array_up, coppy_up, n);
    da(array_down, coppy_down, n);
    da(randomArray, coppy_random, n);

    cout << "Shell sort (Sedgwick's algorithm):\n" << endl;
    cout << "\nSorted array:";
    shell_sejwick(array_up);
    cout << "\nInverted array:";
    shell_sejwick(array_down);
    cout << "\nRandom arrray:";
    shell_sejwick(randomArray);



    return 0;
}
