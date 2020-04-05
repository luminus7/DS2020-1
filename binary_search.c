#define COMPARE(x,y) ( ((x)<(y))? -1 : ((x)==(y))? 0 : 1 )

//for non-decreasing ordered list
int binsearch(int list[], int searchnum, int left, int right){
	while(left <= right){
		middle = (left + right)/2;
		switch (COMPARE(list[middle], searchnum)){
			case -1: left = middle + 1;
				break;
			case 0: return middle;
			case 1: right = middle - 1;
		}
	}
return -1;
}

//for non-increasing ordered list
int binsearch(int list[], int searchnum, int left, int right){
	while(left <= right){
		middle = (left + right)/2;
		switch (COMPARE(list[middle], searchnum)){
			case -1: right = middle - 1;
				break;
			case 0: return middle;
			case 1: left = middle + 1;
		}
	}
return -1;
}

