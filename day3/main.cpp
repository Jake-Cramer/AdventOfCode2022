#include <iostream>
#include <fstream>
#include <string>
#include <vector>

char commonLetter(std::string str1, std::string str2){
	for(int i = 0; i < str1.length(); i++){
		for(int x = 0; x < str2.length(); x++){
			if(str1[i] == str2[x])
				return str1[i];
		}
	}
	return -1;
}
char commonLetter(std::string str1, std::string str2, std::string str3){
	for(int i = 0; i < str1.length(); i++){
		for(int x = 0; x < str2.length(); x++){
			for(int y = 0; y < str3.length(); y++){
				if(str1[i] == str2[x] && str2[x] == str3[y])
					return str1[i];
			}
		}
	}
	std::cout << "error" << "\n";
	return -1;
}

int main(){
	
	std::ifstream infile("input.txt");
	std::string temp;

	std::vector<std::string> groups;


	int part1 = 0;
	int part2 = 0;

	while(std::getline(infile, temp)){
		groups.push_back(temp);
		if(groups.size() >= 3){
			// do the math here
			int x = int(commonLetter(groups.at(0), groups.at(1), groups.at(2)));

			if(x >= 97){
				// lowercase
				part2 += (x - 96);
			}else{
				part2 += (x - 38);
			}
			groups.erase(groups.begin(), groups.end());
		}
		
		//do stuff
		std::string half1 = temp.substr(0, temp.length()/2); // contains first half
		std::string half2 = temp.substr(temp.length()/2, -1); // contains second half

		int x = int(commonLetter(half1, half2));
		
		if(x >= 97){
			// lowercase
			part1 += (x - 96);
		}else{
			part1 += (x - 38);
		}
	}

	std::cout << "Sum of priorities is: " << part1 << "\n";
	std::cout << "Sum of badges is: " << part2 << "\n";
	
	return 0;
}
