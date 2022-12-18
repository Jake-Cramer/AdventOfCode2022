#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct Arr{
	int num;
	std::vector<struct Arr> arrs;
};

void printArr(std::vector<struct Arr> arr){
	std::cout << "[";
	for(int i = 0; i < arr.size(); i++){
		if(arr.at(i).num >= 0){
			std::cout << arr.at(i).num << ",";
		}
		else if(!arr.at(i).arrs.empty()){
			printArr(arr.at(i).arrs);
		}
	}
	std::cout << "]";
}

std::vector<struct Arr> * parseArr(std::string temp, std:: vector<struct Arr> * pArr){
	// takes in the line and a vector Arr that i can put it in
	
	// temp[0] always is '['
	// so i start at temp[1]
	int loc = 1; // loc is where i am working in temp
	
	// loop through temp
	while(loc < temp.length()){
		// this will be for each location
		// create an Arr object
		struct Arr tempArr; // can be on stack because vectors create copies of objects
		tempArr.num = -1; // sets to -1 because it doesnt have a number yet

		// check if what I am looking at is a number
		// numbers have ascii values of 48 - 57
		if(temp[loc] >= 48 && temp[loc] <= 57){
			// is a number
			tempArr.num = std::stoi(temp.substr(loc, temp.find(",", loc) - loc));
			// length is equal to the difference between the comma and loc

			// set loc to the comma + 1
			loc = temp.find(",", loc) + 1;
			// need to chekc if that was the last item
			if(loc == 0){
				loc = temp.length();
			}
			// add tempArr to pArr
			pArr->push_back(tempArr);
			continue;
		}
		// if we are looking at an array
		// find the new array to call parseArr on
		// could go from this [ until the first ]
		std::string newTemp;
		newTemp = temp.substr(loc, temp.find("]", loc) - loc + 1);
		// new arr to put stuff in
		std::vector<struct Arr> * newPArr = new std::vector<struct Arr>;
		tempArr.arrs = *parseArr(newTemp, newPArr);
		// add temp arr to pArr
		pArr->push_back(tempArr);
		// move loc to the next comma + 1
		loc = temp.find(",", temp.find("]", loc)) + 1;
		if(loc == 0){
			loc = temp.length();
		}
	}
	// after the loop we have gone through temp and have our final arr
	return pArr;
}

int rightOrder(std::vector<struct Arr> arr1, std::vector<struct Arr> arr2, int main){
	// compares the two arrs
	// if the right is less it returns 1
	// if arr1 is bigger return 0
	
	// How to know if the right is smaller than the left
	//
	// compare both values at each location
	// if they are both ints
	// 		if the right has the smaller one return 1
	// 		else return 0
	// if both values are lists
	// 		call rightOrder for the lists
	// if only one value is an int
	// 		convert that value to a list and compare
	// if left side runs out of items first
	// 		left side is smaller
	// 		return 0
	//
	// check for sized
	if(arr1.size() > arr2.size() && main == 1){
		return 0;
	}
		
	for(int i = 0; i < arr1.size(); i++){
		// check for size in here
		if(arr2.size() == i && main == 0){
			return 1;
		}
		// compares each value
		if(arr1.at(i).num >= 0 && arr2.at(i).num >= 0){
			// each value is an int
			if(arr1.at(i).num > arr2.at(i).num){
				return 0;
			}
		}// now check if both are arrays
		else if(arr1.at(i).num == -1 && arr2.at(i).num == -1){
			// check if any of the arrays are null
			if(arr2.at(i).arrs.size() == 0 && arr1.at(i).arrs.size() != 0){
				return 0;
			}
			// call func on new arrays
			if(!rightOrder(arr1.at(i).arrs, arr2.at(i).arrs, 0)){
				return 0;
			}
		}// otherwis only 1 is a int
		 // needs work
		else{
			// check for the int in arr1
			if(arr1.at(i).num >= 0 && arr2.at(i).num == -1){
				std::vector<struct Arr> * newArr = new std::vector<struct Arr>;
				struct Arr * arr = new Arr;
				arr->num = arr1.at(i).num;
				newArr->push_back(*arr);
				if(rightOrder(*newArr, arr2.at(i).arrs, 0) == 0){
					return 0;
				}
			}// else check for it in arr2
			else if(arr1.at(i).num == -1 && arr2.at(i).num >= 0){
				std::vector<struct Arr> * newArr = new std::vector<struct Arr>;
				struct Arr * arr = new Arr;
				arr->num = arr2.at(i).num;
				newArr->push_back(*arr);
				if(!rightOrder(arr1.at(i).arrs, *newArr, 0)){
					return 0;
				}
			}
		}
	}
	return 1;
}

int main(){
	std::ifstream infile("day13.txt");
	std::string temp;


	int i = 1;
	int sumOfIndices = 0;
	while(std::getline(infile, temp)){
		// temp has arr 1
		std::vector<struct Arr> * arr1 = new std::vector<struct Arr>;
		arr1 = parseArr(temp, arr1);
		std::getline(infile, temp);
		std::vector<struct Arr> * arr2 = new std::vector<struct Arr>;
		arr2 = parseArr(temp, arr2);
		if(rightOrder(*arr1, *arr2, 1)){
			sumOfIndices += i;
		}

		i++; // counts num of pairs
		// get the null line inbetween
		std::getline(infile, temp);
	}

	// 9303 too high
	// not 1237
	// 1189 too low

	std::cout << "Sum of indices is: " << sumOfIndices << "\n";


	return 0;
}
