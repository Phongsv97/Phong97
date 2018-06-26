#include "mcg.h"
#include "uart.h"
#include "SystemTick.h"
#include "string.h"
#define LENGTH_MAX 100 

uint32_t tickcount      = 0;  // 1us tickcount++
uint32_t speed_ms       = 0;  // Toc do hien tai
uint32_t first_tick     = 0;  

//Hien thi toc do thuat toan 
void Display(int speed)
{
   static int temp[3];
   int i = 0;
   while(speed != 0)
   {
     temp[i++] = speed%10;
     speed = speed/10;
   }
   for(i=2;i>=0;i--)
     uart0_putchar (temp[i] + '0');
   USART0_putstr(" us\r\n "); 
}


//IRQ - interrut sevices rootin
void SysTick_Handler(void)
{
    (uint32_t)SysTick->CTRL;
    tickcount ++; 
}

// swap
void swap(char *x, char *y)
{
	*x = *x + *y;
	*y = *x - *y;
	*x = *x - *y;
}

//cocktail sort
void cocktail_Sort(char *arr, int len)
{       
        first_tick = tickcount;
	int swapped = 1;
	int i, start = 0, end = len - 1;
	
	while (swapped) {
		swapped = 0;
		for (i = start; i < end ; i++) {
			if (arr[i] > arr[i + 1]) {
				swap(&arr[i], &arr[i + 1]);
				swapped = 1;
			}
		}
		if (!swapped)
			return;
		swapped = 0;
		end--;
		for (i = end; i >= start + 1; i--) {
			if (arr[i] < arr[i - 1]) {
				swap(&arr[i], &arr[i - 1]);
				swapped = 1;
			}
		}
		start++;
	}
}

//Bubble sort
void Bubble_Sort(char *arr, int len)
{
	int i, j;
	for (i = 0; i < len -1; i++) {
		for (j = 0; j < len - 1 - i; j++) {
			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
		}
	}
}

//Comb sort
int getNextGap(int gap)
{
	gap = (gap * 10) / 13; // Shrink factor - He so co .
	if (gap < 1) return 1;
	return gap;
}

void comb_Sort(char *arr, int len)
{
	int gap = len;
	while (gap != 1)
	{
		gap = getNextGap(gap);
		int i;
		for (i = 0; i < len - gap; i++) {
			if (arr[i] > arr[i + gap])
				swap(&arr[i], &arr[i + gap]);
		}
	}
}


//Heap sort
void Heapify(char *arr, int root, int len) {
	int largest = root;
	int child_1 = root * 2 + 1;		// left
	int child_2 = root * 2 + 2;		// right

	if (child_1 < len && arr[child_1] > arr[largest])
		largest = child_1;
	if (child_2 < len && arr[child_2] > arr[largest])
		largest = child_2;

	if (largest != root) {
		swap(&arr[root], &arr[largest]);
		Heapify(arr, largest, len);
	}
}


void heap_Sort(char *arr, int len)
{
	int i;
	for (i  = len/2 -1; i>=0; i--) {
		Heapify(arr, i, len);
	}

	for (i = len - 1; i > 0; i--) {
		swap(&arr[i], &arr[0]);
		Heapify(arr, 0, i);
	}

}

//Inserttion sort
void Insertion_Sort(char *arr, int len)
{
	int i, j;
	for (i = 1; i < len; i++) {
		j = i -1;
		int key = arr[i];
		while (arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

//Merge sort
void merge(char * arr, int left, int mid, int right)
{
	int temp[LENGTH_MAX], idx = left, count1 = left,count2 = mid;
	while (count1 < mid || count2 < right)
	{
		if (count2 == right)				temp[idx++] = arr[count1++];
		else if (count1 == mid)				temp[idx++] = arr[count2++];
		else if (arr[count1] < arr[count2])	        temp[idx++] = arr[count1++];
		else					        temp[idx++] = arr[count2++];
	}

	for (idx = left; idx <right; idx++)
		arr[idx] = temp[idx];
}



void merge_Sort(char *arr, int left, int right)
{
	if (right - left < 2)
		return;
		int mid = (left + right) / 2;
		merge_Sort(arr, left, mid);
		merge_Sort(arr, mid , right);
		merge(arr, left, mid, right);
}

//Quick sort
void quick_Sort(char *arr, int left, int right)
{
	if (left < right) {
		int pivotIndex = (right + left) / 2;
		int pivotValue = arr[pivotIndex];
		int i = left;
		int j = right;
		while (i <= j) {
			while (arr[i] < pivotValue ) i++;
			while (arr[j] > pivotValue ) j--;
			if (i <= j) {
				if(i<j)
					swap(&arr[i], &arr[j]);
				i++;
				j--;
			}
		}
		if (left < j) quick_Sort(arr, left, j);
		if (i < right) quick_Sort(arr, i, right);
	}
}

//Selection sort
void Selection_Sort(char *arr, int len)
{
	int i, j,min;
	for (i = 0; i < len - 1; i++) {
		min = i;
		for (j = i + 1; j < len; j++) {
			if (arr[min] > arr[j])
				min = j;
		}

		if(min != i)
			swap(&arr[i], &arr[min]);
	}
}


int main(void)
{  
        char arr[] = { 1,26,28,82,6,44,30,53,50,99,91,63,40,74,36,92,50,69,36,82,68,99,74,16,73,15,80,5,54,79,51,30,84,50
		,86,81,18,3,60,99,41,25,93,93,1,36,52,57,91,63,69,42,53,43,87,16,69,33,82,16,31,23,66,29,5,38,17,51,86,39
		,71,19,32,36,28,13,52,98,65,55,29,32,44,59,13,77,94,84,31,94,22,61,3,83,48,32,24,35,59 ,69 };
	
        initMCG(0,1,1,1,1,1);//48Mhz
        // Phu hop 24Mhz - 48Mhz
        uart0_init( 24000, 9600); // 24Mhz + Toc do baurate 9600 bps
        Initialize_SystemTick(); 
        
        char temp[LENGTH_MAX];
   
        //cocktail sort
        strcpy(temp,arr);
        cocktail_Sort(temp, LENGTH_MAX);
        speed_ms = tickcount - first_tick;
        USART0_putstr("cocktail_Sort : ");
        Display(speed_ms);
        
        //Bubble sort
        strcpy(temp,arr);
        first_tick = tickcount;
        Bubble_Sort(temp, LENGTH_MAX);
        speed_ms = tickcount - first_tick;
        USART0_putstr("Bubble_Sort : ");
        Display(speed_ms);
      
        //Heap sort
        strcpy(temp,arr);
        first_tick = tickcount;
        heap_Sort(temp, LENGTH_MAX);
        speed_ms = tickcount - first_tick;
        USART0_putstr("Heap_Sort : ");
        Display(speed_ms);
        
        //Insertion Sort
        strcpy(temp,arr);
        first_tick = tickcount;
        Insertion_Sort(temp, LENGTH_MAX);
        speed_ms = tickcount - first_tick;
        USART0_putstr("Insertion Sort : ");
        Display(speed_ms);
        
        //merge Sort
        strcpy(temp,arr);
        first_tick = tickcount;
        merge_Sort(temp,0, LENGTH_MAX);
        speed_ms = tickcount - first_tick;
        USART0_putstr("Merge Sort : ");
        Display(speed_ms);
        
        // quick_Sort
        strcpy(temp,arr);
        first_tick = tickcount;
        quick_Sort(temp,0, LENGTH_MAX-1);
        speed_ms = tickcount - first_tick;
        USART0_putstr("Quick Sort : ");
        Display(speed_ms);
        
        //Selection Sort
        strcpy(temp,arr);
        first_tick = tickcount;
        Selection_Sort(temp, LENGTH_MAX);
        speed_ms = tickcount - first_tick;
        USART0_putstr("Selection Sort : ");
        Display(speed_ms);
        
        
        
         while(1){
          }
}