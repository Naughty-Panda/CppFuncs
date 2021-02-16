//////////////////////////////////////////////////
//				C++ Functions
//			Naughty Panda @ 2021
//////////////////////////////////////////////////

#include <iostream>
#include <functional>
//	!!! Requires C++20 !!!
#include <span>

//==================================================================
//	5.1
//==================================================================

const void PrintArray(std::span<const double> arr, const size_t& size) {

	//	We're not actually using &size, 'cause range-based for loop works just fine!
	std::cout << "[ ";
	for (double i : arr) std::cout << i << " ";
	std::cout << "]" << std::endl;
}

const void PrintArray(std::span<const int> arr) {

	std::cout << "[ ";
	for (int i : arr) std::cout << i << " ";
	std::cout << "]" << std::endl;
}

//==================================================================
//	5.4
//==================================================================

void __fastcall _shift_left(int* arr, const size_t& size) {

	//	Here I'm passing an array ptr along with &size and not std::span!
	int temp = arr[0];

	for (size_t i = 0; i < size - 1; i++) {
		arr[i] = arr[i + 1];
	}

	arr[size - 1] = temp;
}

void __fastcall _shift_right(int* arr, const size_t& size) {

	int temp = arr[size - 1];

	for (size_t i = size - 1; i > 0; i--) {
		arr[i] = arr[i - 1];
	}

	arr[0] = temp;
}

const void __fastcall _shift_control(std::function<void(int*, size_t)> shift_handler, int* arr, const size_t& size, const int& n) {

	if (!shift_handler) return;

	for (int i = 0; i < n; i++)
		shift_handler(arr, size);
}

void ShiftArray(std::span<int> arr, const int& nInput) {

	if (!arr.data()) return;

	//	Clamping user input to array size to avoid extra loops
	int n = nInput % static_cast<int>(arr.size());
	if (n < 0) n *= -1;

	std::function<void(int*, size_t)> shift_handler = nullptr;

	//	Assigning shift handler function to the main control function
	shift_handler = nInput < 0 ? _shift_left : _shift_right;
	_shift_control(shift_handler, arr.data(), arr.size(), n);
}

//==================================================================
//	5.5
//==================================================================

const int __fastcall _element_sum(std::span<const int> arr) {

	int sum(0);
	for (int i : arr)
		sum += i;

	return sum;
}

const bool __fastcall CheckBalance(std::span<const int> arr) {

	//	Checking for odd sum of elements or bad array pointer
	if (!arr.data()) return false;
	if (_element_sum(arr) % 2) return false;

	size_t size = arr.size();
	int lside(0), rside(0);

	for (size_t l = 0; l < size; l++) {
		lside += arr[l];
		for (size_t r = l + 1; r < size; r++) {
			rside += arr[r];
		}

		if (lside == rside) return true;

		rside = 0;
	}

	return false;
}

//==================================================================
//	5.2
//==================================================================

void __fastcall FlipArray(std::span<int> arr) {

	if (!arr.data()) return;

	std::cout << "\n\"Binary\" array:\n";
	PrintArray(arr);

	size_t size = arr.size();

	for (size_t i = 0; i < size; i++) {
		arr[i] ^= 1;
	}

	std::cout << "\"Binary\" array after flip:\n";
	PrintArray(arr);
}

//==================================================================
//	5.3
//==================================================================

bool __fastcall FillArray(std::span<int> target_arr) {

	//	We don't want to write into uncompatible array
	if (!target_arr.data()) return false;

	size_t size = target_arr.size();
	const int source_arr[]{ 1, 4, 7, 10, 13, 16, 19, 22 };

	if (size != sizeof(source_arr) / sizeof(source_arr[0])) return false;

	for (size_t i = 0; i < size; i++) {
		target_arr[i] = source_arr[i];
	}

	PrintArray(target_arr);

	return 1;
}



int main() {

	//==================================================================
	//	5.1
	//==================================================================

	double dblArr[]{ .0, .1, .2, .3, .4, .5, .6, .7, .8, .9 };
	size_t size = sizeof(dblArr)/sizeof(dblArr[0]);
	std::cout << "Double array:\n";
	PrintArray(dblArr, size);

	//==================================================================
	//	5.2
	//==================================================================

	int binArr[]{ 1, 1, 0, 0, 1, 0, 1, 1, 0, 0 };
	FlipArray(binArr);

	//==================================================================
	//	5.3
	//==================================================================

	int emptArr[8]{};
	std::cout << "\nLet's fill empty array:\n";
	PrintArray(emptArr);
	FillArray(emptArr) ? std::cout << "Done!\n" : std::cout << "Somethign went wrong...\n";

	//==================================================================
	//	5.4
	//==================================================================

	int nInput(0);
	int arr[]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::cout << "\nDefault array:\n";
	PrintArray(arr);
	std::cout << "Enter an integer to shift our array: ";
	std::cin >> nInput;
	ShiftArray(arr, nInput);
	std::cout << "Shifted array:\n";
	PrintArray(arr);
	std::cout << "Shifting back for testing...\n";
	ShiftArray(arr, -nInput);
	PrintArray(arr);

	//==================================================================
	//	5.5
	//==================================================================

	std::cout << "\nNow let's test some arrays for balance.\n";
	int arr2[]{ 1, 1, 1, 2, 1 };
	int arr3[]{ 1, -1, 2, 3, 4 };
	int arr4[]{ 3, 6, 1, -5, 8, -3 };	
	std::span<int> ptArr[]{ arr2, arr3, arr4 };

	for (int i = 0; i < 3; i++) {
		PrintArray(ptArr[i]);
		std::cout << (CheckBalance(ptArr[i]) ? "Yay! Balance found!\n\n" : "Nay... No balance here.\n\n");
	}

	return 0;
}