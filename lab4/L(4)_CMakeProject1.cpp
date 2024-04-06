#include "L(4)_CMakeProject1.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <istream>
#include <list>
#include <ostream>
#include <string>
#include <vector>
class BigInt {
public:
	BigInt() {}
	BigInt(std::string number) {
		int start = 0;
		if (number[0] == '-') {
			sign = true;
			start = 1;
		}
		for (int i = start; i < number.size(); i++) {
			char c = number[i];
			if (!std::isdigit(c)) {
				std::cout << "Wrong number";
				exit(1);
				return;
			}
			if (!digits.empty() || c != '0') {
				digits.push_back(c - '0');
			}
		}
	}
	BigInt sumPositive(BigInt const& other) {
		int mem = 0;
		std::string out = "";
		int l = this->digits.size() - 1, r = other.digits.size() - 1;
		int res = 0;
		while (l >= 0 || r >= 0) {
			if (l >= 0 && r >= 0) {
				res = this->digits[l] + other.digits[r] + mem;
			}
			else if (l >= 0) {
				res = this->digits[l] + mem;
			}
			else {
				res = other.digits[r] + mem;
			}
			out += ('0' + res % 10);
			mem = res / 10;
			l--;
			r--;
		}
		if (mem != 0) {
			out += '1';
		}
		std::reverse(out.begin(), out.end());
		return BigInt(out);
	}
	BigInt substract(BigInt const& other) {
		BigInt big(*this), small(other);
		if (big.sign == true) {
			big *= BigInt("-1");
		}
		if (small.sign == true) {
			small *= BigInt("-1");
		}
		bool sign = false;
		if (big > small && this->sign == true) {
			sign = true;
		}
		else if (big < small && other.sign == true) {
			sign = true;
		}
		if (big < small) {
			std::swap(big, small);
		}
		int mem = 0;
		std::string out = "";
		int l = big.digits.size() - 1, r = small.digits.size() - 1;
		while (l >= 0 || r >= 0) {
			int res;
			if (l >= 0 && r >= 0) {
				res = big.digits[l] - small.digits[r] - mem;
			}
			else if (l >= 0) {
				res = big.digits[l] - mem;
			}
			else {
				res = small.digits[r] - mem;
			}
			if (res < 0) {
				res += 10;
				mem = 1;
			}
			out += ('0' + res % 10);
			l--;
			r--;
		}
		std::reverse(out.begin(), out.end());
		if (sign) {
			return BigInt(out) * BigInt("-1");
		}
		return BigInt(out);
	}
	BigInt operator+(BigInt const& other) {
		if ((this->sign ^ other.sign) == 0) {
			if (this->sign == true) {
				return sumPositive(other) * BigInt("-1");
			}
			return sumPositive(other);
		}
		return substract(other);
	}
	void operator+=(BigInt const& other) {
		BigInt tmp = *this + other;
		*this = tmp;
	}
	BigInt operator*(BigInt const& other) {
		std::vector<char> result(digits.size() + other.digits.size(), 0);

		for (int i = digits.size() - 1; i >= 0; i--) {
			int carry = 0;
			for (int j = other.digits.size() - 1; j >= 0; j--) {
				int product =
					digits[i] * other.digits[j] + carry + result[i + j + 1];
				result[i + j + 1] = product % 10;
				carry = product / 10;
			}
			result[i] = carry;
		}

		while (result.size() > 1 && result[0] == 0) {
			result.erase(result.begin());
		}

		BigInt multiplied;
		multiplied.digits = result;
		multiplied.sign = sign ^ other.sign;

		return multiplied;
	}

	void operator*=(BigInt const& other) {
		BigInt multiplied = *this * other;
		*this = multiplied;
	}
	bool operator<(BigInt const& other) const {
		if (this->sign && !other.sign) { return true; }
		if (!this->sign && other.sign) { return false; }
		bool sign = this->sign;
		if (this->digits.size() > other.digits.size()) {
			return false || sign;
		}
		else if (this->digits.size() < other.digits.size()) {
			return true ^ sign;
		}
		else {
			for (int i = 0; i < this->digits.size(); i++) {
				if (this->digits[i] < other.digits[i]) {
					return true ^ sign;
				}
				else if (this->digits[i] > other.digits[i]) {
					return false || sign;
				}
			}
		}
		return false || sign;
	}
	bool operator>(BigInt const& other) const { return other < *this; }
	bool operator==(BigInt const& other) const {
		return !(*this < other) && !(*this > other);
	}
	bool operator!=(BigInt const& other) const { return !(*this == other); }
	std::string toString() const {
		std::string out = "";
		if (sign) {
			out += "-";
		}
		for (int v : digits) {
			out += ('0' + v);
		}
		return out;
	}

private:
	std::vector<char> digits;
	bool sign = false;
};

std::istream& operator>>(std::istream& is, BigInt& m) {
	std::string tmp;
	is >> tmp;
	m = BigInt(tmp);
	return is;
}

std::ostream& operator<<(std::ostream& os, BigInt const& m) {
	return os << m.toString();
}

int main(int argc, char* argv[]) {
	BigInt a, b, c;
	std::cin >> a >> b;
	std::cout << "a + b = " << (a + b) << std::endl;
	a += b;
	std::cout << "a +=b:  " << a << std::endl;
	std::cout << "a * b: " << (a * b) << std::endl;
	a *= b;
	std::cout << "a *= b: " << a << std::endl;
	std::cout << "a == b:  " << (a == b) << std::endl;
	std::cout << "a != b:  " << (a != b) << std::endl;
	std::cout << "a > b:  " << (a > b) << std::endl;
	std::cout << "a < b:  " << (a < b) << std::endl;
	return 0;
}