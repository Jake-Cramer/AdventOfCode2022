#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Arr{
	int num;
	std::vector<struct Arr> arrs;
};

std::vector<struct Arr> * parseArr(std::string temp, std:: vector<struct Arr> * pArr){
	// each location in the array is an Arr
	// each arr either has a number or a vector of arr
	//
	// if the location im at call parseArr for the array
	
	// loop through each location
	// have to be careful checking for commas because the commas can be in the inside arrays
	int locInTemp = 1;
	while(locInTemp < temp.length()){	
		struct Arr* loc = new Arr;
		loc->num = -1; // set to -1 for all locs
		// has been called for array so automatically assume that temp[0] is a [
		// check if this loc is an array
		if(temp[locInTemp] == '['){
			// is an array
			std::string newTemp = temp.substr(locInTemp, temp.find("]", locInTemp) - locInTemp + 1);
			// need
			loc->arrs = *parseArr(newTemp, pArr);
			locInTemp = temp.find("]", locInTemp);
		}else if(temp[locInTemp] != ']'){
			// is a number
			std::string tempNum = temp.substr(locInTemp, temp.find(",", locInTemp) - locInTemp);
			if(tempNum != ""){
				loc->num = std::stoi(tempNum);
			}
			locInTemp = temp.find(",", locInTemp);
		}else{
			// i have reached the end of the string
			locInTemp = temp.length();
		}
		pArr->push_back(*loc);
	}

	return pArr;
}

int rightOrder(std::vector<struct Arr> arr1, std::vector<struct Arr> arr2){
	std::cout << "Called" << std::endl;
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
	// ALL OF THIS ONLY WORKS IF PARSER WORKS
	
	// TODO code
	
	// first check if the left side is smaller
	// if it is it is automatically returning false
	std::cout << "Hi" << std::endl;
	if(arr1.size() > arr2.size()){
		std::cout << "Yello" << std::endl;
		return 0;
	}
	if(arr1.empty()){
		std::cout << "HIIII" << std::endl;
	}
	std::cout << arr1.size() << std::endl;
	
	for(int i = 0; i < arr1.size(); i++){
		std::cout << i << std::endl;
		// compares each value
		if(arr1.at(i).num >= 0 && arr2.at(i).num >= 0){
			// each value is an int
			if(arr1.at(i).num > arr2.at(i).num){
				return 0;
			}
		}// now check if both are arrays
		else if(arr1.at(i).num == -1 && arr2.at(i).num == -1){
			std::cout << "OUBFODB" << std::endl;
			// call func on new arrays
			if(!rightOrder(arr1.at(i).arrs, arr2.at(i).arrs)){
				std::cout << "Yo" << std::endl;
				return 0;
			}else{
				std::cout << "Yo :(" << std::endl;
			}
		}// otherwis only 1 is a int
		else{
			// check for the int in arr1
			if(arr1.at(i).num >= 0 && arr2.at(i).num == -1){
				std::vector<struct Arr> * newArr = new std::vector<struct Arr>;
				struct Arr * arr = new Arr;
				arr->num = arr1.at(i).num;
				newArr->push_back(*arr);
				std::cout << "Tis me" << std::endl;
				if(!rightOrder(*newArr, arr2.at(i).arrs)){
					return 0;
				}else{
					std::cout << "HIDHFIDHFOSIDFOSDFN" << std::endl;
				}
				std::cout << "Yep" << std::endl;
			}// else check for it in arr2
			else if(arr1.at(i).num == -1 && arr2.at(i).num >= 0){
				std::vector<struct Arr> * newArr = new std::vector<struct Arr>;
				struct Arr * arr = new Arr;
				arr->num = arr2.at(i).num;
				newArr->push_back(*arr);
				std::cout << "Or me" << std::endl;
				if(!rightOrder(arr1.at(i).arrs, *newArr)){
					std::cout << "R u seriosus" << std::endl;
					return 0;
				}
			}
		}
	}
	std::cout << "bruh" << std::endl;

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
		std::cout << "INPUT" << std::endl;
		if(rightOrder(*arr1, *arr2))
			sumOfIndices += i;

		i++; // counts num of pairs
	}

	std::cout << "Sum of indices is: " << sumOfIndices << "\n";


	return 0;
}
