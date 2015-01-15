//
//  main.cpp
//  Refrigerator
//
//  Created by 고승완 on 2015. 1. 14..
//  Copyright (c) 2015년 Hacker. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>


void printLogo() {
	std::cout << "\nRefrigerator _ light\n\n";
}
void printMenu() {
	std::cout << "\t1. 보관 품목 조회\n\t2. 물건 넣기\n\t3. 물건 빼기" << std::endl;
	std::cout << "\t0. 종료\n";
	
	std::cout << "입력하세요 : ";
}




void readFile(std::vector<std::string>* itemName, std::vector<int>* itemCount) {
	std::string temp_Name;
	int temp_Count;
	std::fstream fs;
    fs.open("list.txt",std::fstream::ios_base::in); // reading mode
    if (fs.good()) {
		while (fs >> temp_Name) {
			fs >> temp_Count;
			itemName->push_back(temp_Name);
			itemCount->push_back(temp_Count);
		}
		fs.close();
    }
	
}

void writeFile(std::vector<std::string>* itemName, std::vector<int>* itemCount) {
	std::ofstream ofs;
	ofs.open("list.txt");
	if (!ofs.good())
		return;
	for (int i=0; i<itemCount->size(); ++i) {
		if ((*itemCount)[i] < 1)
			continue;
		ofs << (*itemName)[i] << "\t" << (*itemCount)[i];
		if (i!=itemCount->size()-1) {
			ofs << std::endl;
		}
	}
	ofs.close();
}

int vectorSearch(std::vector<std::string>* itemName, std::string compareStr) {
	int index = -1;
	for (int i=0; i<itemName->size(); ++i) {
		if ((*itemName)[i]==compareStr) {
			index=i;
		}
	}
	return index;
}

void input_item() {
	
	std::string buffer;
	std::cout << "입력 할 아이템은 ? ";
	std::cin >> buffer;
	
	int itemLocation;
	std::vector<std::string> itemName;
	std::vector<int> itemCount;
	readFile(&itemName, &itemCount);

	

	itemLocation= vectorSearch(&itemName, buffer);
	if (itemLocation!=-1) {				//있으면
		itemCount[itemLocation]++;
	}
	else{
		itemName.push_back(buffer);
		itemCount.push_back(1);
	}

	writeFile(&itemName, &itemCount);
	
}

void output_item() {
	std::string buffer;
	std::cout << "꺼낼 아이템은 ? ";
	std::cin >> buffer;
	
	int itemLocation;
	std::vector<std::string> itemName;
	std::vector<int> itemCount;
	readFile(&itemName, &itemCount);
	
	
	
	itemLocation= vectorSearch(&itemName, buffer);
	if (itemLocation!=-1) {				//있으면
		itemCount[itemLocation]--;
	}
	else{
		std::cout << "어..읎어요" << std::endl;
	}
	
	writeFile(&itemName, &itemCount);
}

void lookup() {
	std::ifstream ifs;
	ifs.open("list.txt");
	std::string temp_Name;
	int temp_Count;
	if (ifs.good()) {
		while (ifs >> temp_Name) {
			ifs >> temp_Count;
			std::cout << temp_Name << "\t" << temp_Count << "개" << std::endl;
		}
		ifs.close();
	}

	
}


int main() {

	
	int menuSel;

    printLogo();
    while (1) {
        printMenu();
        //scanf("%d", &menuSel);
        if (scanf("%d", &menuSel) != 1) {
			
            printf("올바른 숫자를 입력하세요\n");
			while(getchar() ^ '\n');
        }
        else {
            switch (menuSel) {
                case 0:
                    return 0;
                case 1:
					lookup();
                    break;
                case 2:
                    input_item();
                    break;
                case 3:
					output_item();
                    break;
                    
                default:
                    
                    printf("error: invalid number\n");
                    break;
                    
            }
        }
    }
    

    return 0;
    
}
