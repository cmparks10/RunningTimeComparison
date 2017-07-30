#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <ctime>
#include <vector>
#include <string>
using namespace std;
int len;
//const int NumsToSort = 7;
//const int NumbersToMake[] = {100,500,1000,2000,5000,8000,10000};

const int NumsToSort = 1;
const int NumbersToMake[] = {100};



double TimeItTook;
double duration;
vector<float> InsertionUnsorted, InsertionSorted,
QuickSorted, QuickUnsorted,
HeapSorted, HeapUnsorted,
MergeSorted, MergeUnsorted;

int randomNumber(int num)
{
    string result;
    ostringstream convert;
    convert << num;
    result = convert.str();
    string newfName = result+"_unsorted.txt";
    ofstream numberFile(newfName.c_str());
    srand (time(NULL)); //guarantee random numbers on each run
	for(int i=0; i<num; i++)//Generate the random numbers
		{
		int number = rand() % (1, 20001);
		numberFile<<number<<endl;
		}
    numberFile.close();
}

double insertionSort(ifstream& infile)
{

    int NumberOfLines = 0;
    string line;

    //count the number of lines in the file to allow us to build array of given length
    if(infile.is_open())
    {
        while(getline(infile, line))
        {
            ++NumberOfLines;
        }
    }

    //Reset the file
    infile.clear();
    infile.seekg(0, std::ios_base::beg);

    //create the array
    int arr[NumberOfLines];

    //Put everything from the text file into a local array to sort. This is currently unsorted.
    for(int n=0; n<NumberOfLines; n++)
    {
        infile>>arr[n];
    }

    clock_t start;
    //double duration;
    start = clock();

    int j, temp;

    for (int i = 0; i < NumberOfLines; i++) {
        j = i;
        while (j > 0 && arr[j - 1] < arr[j]) {
            temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
            j--;
        }
        duration = (clock() - start) / (double)CLOCKS_PER_SEC;
        cout<<"Sorting took: "<< duration<<" seconds"<<'\n';
    }
    TimeItTook = (std::clock() - start) / (double)CLOCKS_PER_SEC;

    //push the sorted array to the output file
    string result;
    ostringstream convert;
    convert << NumberOfLines;
    result = convert.str();
    string newUnsortedFileName = result+"_sorted.txt";
    ofstream numberFile(newUnsortedFileName.c_str());

    for (int i = NumberOfLines - 1; i >= 0; i--)
    {
        numberFile<<arr[i]<<endl;
    }
    numberFile.close();
    return TimeItTook;
}

void insertionComparison(int num)
{
    string result;
    ostringstream convert;
    convert << num;
    result = convert.str();
    string newfName = result+"_unsorted.txt";
	ifstream infile;
	infile.open (newfName.c_str());
	insertionSort(infile);
	InsertionUnsorted.push_back(TimeItTook);
	infile.close();

    newfName = result+"_sorted.txt";
	infile.open (newfName.c_str());
	insertionSort(infile);
	InsertionSorted.push_back(TimeItTook);
	infile.close();
}

class printData
{
public:
    void printArray(int arr[])
    {
        for (int i = 0; i<len; i++)
        {
            cout << arr[i] << endl;
        }//Hence, this only prints the first item in array
    }
    void printArray(int arr[], int i, int j)
    {
    cout << "[";
    for (int start = i; start < j; start++)
        cout << arr[start] << ", ";
    cout << arr[j] << "]";
    }
};

void swap(int arr[], int k, int small) {
    int temp;
    temp = arr[k];
    arr[k] = arr[small];
    arr[small] = temp;
}

int partition(int arr[], int i, int j) {
    int pivot = arr[j];
    int small = i - 1;

    for(int k = i; k < j; k++) {
        if(arr[k] <= pivot) {
            small++;
            swap(arr, k, small);
        }
    }
    swap(arr, j, small + 1);
    return small + 1;
}

float quickSort(int arr[], int i, int j) {
    clock_t start;
    start = clock();
    if(i < j) {
        int pos = partition(arr, i, j);
        quickSort(arr, i, pos - 1);
        quickSort(arr, pos + 1, j);
        duration = (clock() - start) / (double)CLOCKS_PER_SEC;
        cout<<"Sorting took: "<< duration<<" seconds"<<'\n';
    }
    TimeItTook = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    return TimeItTook;
}
//I have to chose the loewst and highest valuyes. How do I do that
//with text from a file?
void quickComparison(int num)
{
    //open each file
    string result;
    ostringstream convert;
    convert << num;
    result = convert.str();
    string newfName = result+"_unsorted.txt";
	ifstream infile;
	infile.open (newfName.c_str());
	//get the size of the file to pass to an array
    int NumberOfLines = 0;
    string line;
    //count the number of lines in the file to allow us to build array of given length
    if(infile.is_open())
    {
        while(getline(infile, line))
        {
            ++NumberOfLines;
        }
    }
    //Reset the file
    infile.clear();
    infile.seekg(0, std::ios_base::beg);
    //create the array
    int arr[NumberOfLines];
    //Put everything from the text file into a local array.
    for(int n=0; n<NumberOfLines; n++)
    {
        infile>>arr[n];
    }
    //Call the sorting algorithm
    len = sizeof(arr) / sizeof(int);
    //infile.clear();
    //infile.seekg(0, std::ios_base::beg);
    quickSort(arr, 0, len-1);
    QuickUnsorted.push_back(TimeItTook);
    infile.close();
    ////////////////////////////////////////////////////////////
    newfName = result+"_sorted.txt";
	infile.open (newfName.c_str());
	//get the size of the file to pass to an array
    NumberOfLines = 0;
    //count the number of lines in the file to allow us to build array of given length
    if(infile.is_open())
    {
        while(getline(infile, line))
        {
            ++NumberOfLines;
        }
    }

    //Reset the file
    infile.clear();
    infile.seekg(0, std::ios_base::beg);
    for(int n=0; n<NumberOfLines; n++)
    {
        infile>>arr[n];
    }
    infile.clear();
    infile.seekg(0, std::ios_base::beg);
    quickSort(arr, 0, len-1);
    QuickSorted.push_back(TimeItTook);
    infile.close();
}

class MaxHeap {
  public:
    int len;
    int *arr;
    MaxHeap(int l, int a[]);
};
MaxHeap::MaxHeap(int l, int a[]) {
    len = l;
    arr = a;
}
void swap(int *i, int *j) {
    int temp = *i;
    *i = *j;
    *j = temp;
}
MaxHeap heapify(MaxHeap maxheap, int N) {
    int largest = N;
    int left = 2 * N + 1;
    int right = 2 * N + 2;

    if(left < maxheap.len && maxheap.arr[left] > maxheap.arr[largest])    {
        largest = left;
    }

    if(right < maxheap.len && maxheap.arr[right] > maxheap.arr[largest]) {
        largest = right;
    }

    if(largest != N) {
        swap(&maxheap.arr[largest], &maxheap.arr[N]);
        heapify(maxheap, largest);
    }

    return maxheap;
}
MaxHeap createHeap(int arr[], int N) {
    MaxHeap maxheap(N, arr);
    int i = (maxheap.len - 2) / 2;

    while(i >= 0) {
        maxheap = heapify(maxheap, i);
        i--;
    }

    return maxheap;
}
float heapSort(int arr[], int N) {
    clock_t start;
    start = clock();
    //creating a heap
    MaxHeap heap = createHeap(arr, N);

    //Repeating the below steps till the size of the heap is 1.
    while(heap.len > 1) {
        //Replacing largest element with the last item of the heap
        swap(&heap.arr[0], &heap.arr[heap.len - 1]);
        heap.len--;//Reducing the heap size by 1
        heapify(heap, 0);
        duration = (clock() - start) / (double)CLOCKS_PER_SEC;
        cout<<"Sorting took: "<< duration<<" seconds"<<'\n';
    }
    TimeItTook = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    return TimeItTook;
}

void heapComparison(int num)
{
    //open each file
    string result;
    ostringstream convert;
    convert << num;
    result = convert.str();
    string newfName = result+"_unsorted.txt";
	ifstream infile;
	infile.open (newfName.c_str());
	//get the size of the file to pass to an array
    int NumberOfLines = 0;
    string line;
    //count the number of lines in the file to allow us to build array of given length
    if(infile.is_open())
    {
        while(getline(infile, line))
        {
            ++NumberOfLines;
        }
    }
    //Reset the file
    infile.clear();
    infile.seekg(0, std::ios_base::beg);
    //create the array
    int arr[NumberOfLines];
    //Put everything from the text file into a local array.
    for(int n=0; n<NumberOfLines; n++)
    {
        infile>>arr[n];
    }
    //pass that array to a function to print it.
    len = sizeof(arr)/sizeof(int);
    heapSort(arr, len);
    HeapUnsorted.push_back(TimeItTook);
    infile.close();

 ////////////////////////////////////////////////////////////////////////////////
    newfName = result+"_sorted.txt";
	infile.open (newfName.c_str());
	//get the size of the file to pass to an array
    NumberOfLines = 0;
    //count the number of lines in the file to allow us to build array of given length
    if(infile.is_open())
    {
        while(getline(infile, line))
        {
            ++NumberOfLines;
        }
    }
    //Reset the file
    infile.clear();
    infile.seekg(0, std::ios_base::beg);
    //create the array
    //int rr[NumberOfLines];
    //Put everything from the text file into a local array.
    for(int n=0; n<NumberOfLines; n++)
    {
        infile>>arr[n];
    }
    //pass that array to a function to print it.
    len = sizeof(arr)/sizeof(int);
    heapSort(arr, len);
    HeapSorted.push_back(TimeItTook);
    infile.close();
}


void merge(int arr[], int i, int mid, int j) {
    int temp[len];
    int l = i;
    int r = j;
    int m = mid + 1;
    int k = l;

    while(l <= mid && m <= r) {
        if(arr[l] <= arr[m]) {
            temp[k++] = arr[l++];
        }
        else {
            temp[k++] = arr[m++];
        }
    }

    while(l <= mid)
        temp[k++] = arr[l++];

    while(m <= r) {
        temp[k++] = arr[m++];
    }

    for(int i1 = i; i1 <= j; i1++) {
        arr[i1] = temp[i1];
    }
}
float mergeSort(int arr[], int i, int j) {
    clock_t start;
    start = clock();
    int mid = 0;
    if(i < j) {
        mid = (i + j) / 2;
        mergeSort(arr, i, mid);
        mergeSort(arr, mid + 1, j);
        merge(arr, i, mid, j);
        duration = (clock() - start) / (double)CLOCKS_PER_SEC;
        cout<<"Sorting took: "<< duration<<" seconds"<<'\n';
    }
    TimeItTook = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    return TimeItTook;
}

void mergeComparison(int num)
{
    //open each file
    string result;
    ostringstream convert;
    convert << num;
    result = convert.str();
    string newfName = result+"_unsorted.txt";
	ifstream infile;
	infile.open (newfName.c_str());
	//get the size of the file to pass to an array
    int NumberOfLines = 0;
    string line;
    //count the number of lines in the file to allow us to build array of given length
    if(infile.is_open())
    {
        while(getline(infile, line))
        {
            ++NumberOfLines;
        }
    }
    //Reset the file
    infile.clear();
    infile.seekg(0, std::ios_base::beg);
    //create the array
    int arr[NumberOfLines];
    //Put everything from the text file into a local array.
    for(int n=0; n<NumberOfLines; n++)
    {
        infile>>arr[n];
    }
    //Call the sorting algorithm
    len = sizeof(arr) / sizeof(int);
    //infile.clear();
    //infile.seekg(0, std::ios_base::beg);
    mergeSort(arr, 0, len-1);
    MergeUnsorted.push_back(TimeItTook);
    infile.close();
    ////////////////////////////////////////////////////////////
    newfName = result+"_sorted.txt";
	infile.open (newfName.c_str());
	//get the size of the file to pass to an array
    NumberOfLines = 0;
    //count the number of lines in the file to allow us to build array of given length
    if(infile.is_open())
    {
        while(getline(infile, line))
        {
            ++NumberOfLines;
        }
    }

    //Reset the file
    infile.clear();
    infile.seekg(0, std::ios_base::beg);
    for(int n=0; n<NumberOfLines; n++)
    {
        infile>>arr[n];
    }
    infile.clear();
    infile.seekg(0, std::ios_base::beg);
    mergeSort(arr, 0, len-1);
    MergeSorted.push_back(TimeItTook);
    infile.close();
}

int main()
{
    //////////////////////////
	for (int count =0; count<NumsToSort; count++)
    {
        randomNumber(NumbersToMake[count]);
        insertionComparison(NumbersToMake[count]);
        quickComparison(NumbersToMake[count]);
        heapComparison(NumbersToMake[count]);
        mergeComparison(NumbersToMake[count]);
    }

/*
    for (int count=0; count<NumsToSort;count++)
    {
        insertionComparison(NumbersToMake[count]);
    }


    for (int count=0; count<NumsToSort;count++)
    {
        quickComparison(NumbersToMake[count]);
    }

    for (int count=0; count<NumsToSort;count++)
    {
        heapComparison(NumbersToMake[count]);
    }
*/
//////////////////////////////
    cout<<"\n\n\n"<<endl;
    cout<<"Insertion Sort Unsorted:"<<endl;
    for(int i=0; i<InsertionUnsorted.size(); ++i)
    {
        cout << InsertionUnsorted[i] << ' ';
    }
    cout<<"\nInsertion Sort Sored:"<<endl;
    for(int i=0; i<InsertionSorted.size(); ++i)
    {
        cout << InsertionSorted[i] << ' ';
    }
///////////////////////
    cout<<"\n\n\n"<<endl;
    cout<<"Quick Sort Unsorted:"<<endl;
    for(int i=0; i<QuickUnsorted.size(); ++i)
    {
        cout << QuickUnsorted[i] << ' ';
    }
    cout<<"\nOuick Sort Sored:"<<endl;
    for(int i=0; i<QuickSorted.size(); ++i)
    {
        cout << QuickSorted[i] << ' ';
    }
////////////////////////////////////////////////////////////////////////
    cout<<"\n\n\n"<<endl;
    cout<<"Heap Sort Unsorted:"<<endl;
    for(int i=0; i<QuickUnsorted.size(); ++i)
    {
        cout << HeapUnsorted[i] << ' ';
    }
    cout<<"\nHeap Sort Sored:"<<endl;
    for(int i=0; i<QuickSorted.size(); ++i)
    {
        cout << HeapSorted[i] << ' ';
    }

////////////////////////////////////////////////////////////////////
    cout<<"\n\n\n"<<endl;
    cout<<"Merge Sort Unsorted:"<<endl;
    for(int i=0; i<QuickUnsorted.size(); ++i)
    {
        cout << MergeUnsorted[i] << ' ';
    }
    cout<<"\nMerge Sort Sored:"<<endl;
    for(int i=0; i<QuickSorted.size(); ++i)
    {
        cout << MergeSorted[i] << ' ';
    }
    cout<<"\n\n"<<endl;



	return 0;
}
