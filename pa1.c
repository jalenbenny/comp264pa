// I, Ben Flowers, here certify that this programming assignment reflects my own work,
// without the use of any external individuals (other than course/department staff ), generative-AI,
// or any other forbidden resources. I understand/accept the consequences of cheating as outlined
// in the course syllabus.


#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float mean(float arr[], int size) {
	float sum =  0;
	for (int a = 0; a < size; a++) {
		sum += arr[a];
	}
	return roundf((sum / size) * 1000) / 1000;
}

float median(float arr[], int size) {
	for (int a = 0; a < size - a - 1; a++) {
		for (int b = 0; b < size - b - 1; b++) {
			if (arr[b] > arr[b + 1]) {
				float temp = arr[b];
				arr[b] = arr[b + 1];
				arr[b + 1] = temp;
			}
		}
	}

	if (size % 2 == 0) {
		return roundf(((arr[size/2 - 1] + arr[size/2]) / 2) * 1000) / 1000;
	} else { 
	return roundf(arr[size/2] * 1000) / 1000;;
	}
}

float mode(float arr[], int size) {
	float mode = -1;
	int maxCount = 0;

	for (int a = 0; a < size; a++) {
		int count = 0;
		for (int b = 0; b < size; b++) {
			if (fabsf(arr[b] -  arr[a] < 0.0001)) {
				count++;
			}
		}
		
		if (count > maxCount) {
			maxCount = count;
			mode = arr[a];
		} else if (count == maxCount && arr[a] != mode) {
			return -1;
		}
	}

	return (maxCount > 1) ? roundf(mode * 1000) / 1000: -1;
}

float stdDev(float arr[],  int size) {
	float m = mean(arr, size);
	float sumOfSquares = 0;

	for (int a = 0; a < size; a++) {
		sumOfSquares += powf(arr[a] - m, 2);
	}

	return roundf(sqrtf(sumOfSquares / (size - 1)) * 1000) / 1000;
}

void roundedValues(float arr[], int rounded[], int size) {
	for (int a = 0; a < size; a++) {
		rounded[a] = (int)roundf(arr[a]);
	}
}

void ascii_repr(int arr[], char ascii_arr[], int size) {
	for (int a = 0; a < size; a++) {
		if (arr[a] >= 32 && arr[a] <= 126) {
			ascii_arr[a] = (char)arr[a];
		} else {
			ascii_arr[a] = '*';
		}
	}
	ascii_arr[size] = '\0';
}

void print_arr(char arr[], int size) {
	for (int a = 0; a < size; a ++) {
		printf("%c", arr[a]);
	}
	printf("\n");
}

void computeStats(float arr[], int size) {
	printf("Mean: %.3f\n", mean(arr, size));
	printf("Median: %.3f\n", median(arr, size));
	float modeValue = mode(arr, size);
	if (modeValue != -1) {
		printf("Mode: %.3f\n", modeValue);
	} else {
		printf("Mode: There is no unique mode\n");
	}
	printf("Standard Deviation: %.3f\n", stdDev(arr, size));

	int rounded[size];
	roundedValues(arr, rounded, size);
	printf("Rounded values: ");
	for (int a = 0; a < size; a++) {
		printf("%d ", rounded [a]);
	}
	printf("\n");

	char ascii_arr[size + 1];
	ascii_repr(rounded, ascii_arr, size);
	printf("ASCII representation: ");
	print_arr(ascii_arr, size);
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: %s <num1> <num2> ... <numN>\n", argv[0]);
		return 1;

	}

	int size = argc - 1;
	float arr[size];

	for (int a = 0; a < size; a++) {
		arr[a] = atof(argv[a + 1]);
		if (arr[a] < 0) {
		printf("ERROR! Enter non negative numbers .\n");
		return 1;
		}
	}

	computeStats(arr, size);

	return 0;
}



float mean(float arr[], int size);
float median(float arr[], int size);
float mode(float arr[], int size);
float stdDev(float arr[], int size);

void roundedValues(float arr[], int rounded[], int size);
void asciiRep(int arr[], char ascii_arr[], int size);
void printArr(char arr[], int size);
void computeStats(float arr[], int size);
