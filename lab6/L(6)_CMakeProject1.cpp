#include "L(6)_CMakeProject1.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string toBin(int num) {
	std::string res = "";
	while (num != 0) {
		res = std::to_string(num % 2) + res;
		num /= 2;
	}
	return res;
}

class BitMask {
public:
	BitMask(char* byte, int ind) {
		this->byte = byte;
		this->ind = ind;
	}
	operator bool() const { return *byte & (1 << ind); }

	void operator=(bool val) {
		if (val == true) {
			*byte |= (1 << ind);
		}
		else {
			*byte ^= (1 << ind);
		}
	}

private:
	char* byte;
	int ind;
};
class BoolVec {
public:
	BoolVec() {
		size = 0;
		nums = new char[1];
		nums[0] = 0;
	}
	void pushBack(bool val) {
		if (size % 8 == 0 && size != 0) {
			char* tmp = new char[size / 8 + 1];
			copy(nums, nums + size / 8 + 1, tmp);
			delete[] nums;
			nums = tmp;
		}
		int subInd = size / 8;
		nums[subInd] <<= 1;
		nums[subInd] |= val;
		size++;
	}
	void isnert(bool val, int ind) {
		BoolVec tmp = BoolVec();
		for (int i = 0; i < size; i++) {
			if (i == ind) {
				tmp.pushBack(val);
			}
			else {
				tmp.pushBack(getVal(i));
			}
		}
		if (ind - 1 == size) {
			tmp.pushBack(val);
		}
		*this = tmp;
	}

	void erase(int ind) {
		BoolVec tmp = BoolVec();
		for (int i = 0; i < size; i++) {
			if (i == ind) {
				continue;
			}
			else {
				tmp.pushBack(getVal(i));
			}
		}
		*this = tmp;
	}
	bool getVal(int ind) const {
		if (ind >= size) {
			exit(1);
		}
		int subInd = ind / 8;
		int interInd = ind % 8;
		if (subInd != size / 8) {
			return nums[subInd] >> (7 - interInd) & 1;
		}
		else {
			int res = size % 8 - 1;
			return nums[subInd] >> (res - interInd) & 1;
		}
	}
	BitMask operator[](int ind) {
		int subInd = ind / 8;
		int interInd = ind % 8;
		int res;
		if (subInd != size / 8) {
			res = 7;
		}
		else {
			res = size % 8 - 1;
		}
		return BitMask(nums + subInd, res - interInd);
	}
	int Size() { return size; }
	string toString() {
		string res = "[";
		for (int subInd = 0; subInd < size / 8 + 1; subInd++) {
			if (subInd != size / 8 || size % 8 == 0) {
				for (int i = 7; i >= 0; i--) {
					res += to_string(nums[subInd] >> i & 1);
					res += " ";
				}
			}
			else {
				int lastSize = size % 8 - 1;
				for (int i = lastSize; i >= 0; i--) {
					res += to_string(nums[subInd] >> i & 1);
					res += " ";
				}
			}
		}
		res += "]";
		return res;
	}

private:
	int size;
	char* nums;
};

int main() {
	BoolVec vec;
	for (int i = 0; i < 5; i++) {
		vec.pushBack(true);
	}
	vec.erase(3);
	for (int i = 0; i < 4; i++) {
		cout << vec.getVal(i);
	}
}
