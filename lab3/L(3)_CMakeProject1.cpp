#include "L(3)_CMakeProject1.h"
#include <iostream>

#include <string>

class String {
private: 
	char* str;
	int len;

public:
	//,базовый конструктор
	String() {
		len = 0;
		str = new char[1];
		str[0] = '\0';
	}
	
	//Конструктор копирования
	String(const String& other) {
		len = other.len;
		str = new char[len + 1];
		for (int i = 0; i <= len; ++i) {
			str[i] = other.str[i];
		}
	}

	//Оператор присваивания копированием
	String& operator = (const String& other) {
		if (this != &other) {
			delete[] str;

			len = other.len;
			str = new char[len + 1];
			for (int i = 0; i <= len; ++i) {
				str[i] = other.str[i];
			}
		}
		return *this;
	}

	//Деструктор
	~String() {
		std::cout << "Destr: " << str << std::endl;
		delete[] str;
		std::cout << "Success " << std::endl;

	}

	//Операторы + и +=
	String operator+(const String& other) {
		String result;
		result.len = len + other.len;
		result.str = new char[result.len + 1];
		for (int i = 0; i < len; ++i) {
			result.str[i] = str[i];
		}
		for (int i = 0; i <= other.len; ++i) {
			result.str[i + len] = other.str[i];
		}
		return result;
	};
	String& operator+=(const String& other) {
		int newLen = len + other.len;
		char* newStr = new char[newLen + 1];
		for (int i = 0; i < len; ++i) {
			newStr[i] = str[i];
		}
		for (int i = 0; i <= other.len; ++i) {
			newStr[i + len] = other.str[i];
		}
		delete[] str;

		len = newLen;
		str = newStr;

		return *this;
	}

	//Оператор[] - чтение и изменение элемента
	char& operator[](int index) {

		return str[index];
	}

	//Операторы <, >, ==
	bool operator<(const String& other) const {
		int minLen = len < other.len ? len : other.len;

		for (int i = 0; i < minLen; ++i) {
			if (str[i] != other.str[i]) {
				return str[i] < other.str[i];
			}
		}

		return len < other.len;
	}
	bool operator>(const String& other) const {
		int minLen = len < other.len ? len : other.len;

		for (int i = 0; i < minLen; ++i) {
			if (str[i] != other.str[i]) {
				return str[i] > other.str[i];
			}
		}
		return len > other.len;
	}
	bool operator==(const String& other) const {
		if (len != other.len) {
			return false;
		}
		for (int i = 0; i < len; ++i) {
			if (str[i] != other.str[i]) {
				return false;
			}
		}
		return true;
	}

	//Операторы ввода и вывода в поток
	friend std::ostream& operator << (std::ostream& out, const String& s) {
		out << s.str;
		return out;
	}
	friend std::istream& operator >> (std::istream& in, String& s) {
		const int bufferSize = 100;
		char buffer[bufferSize];

		in.getline(buffer, bufferSize);

		delete[] s.str;
		std::cout << strlen(buffer);
		s.str = new char[strlen(buffer)+1];
		int i = 0;
		while (buffer[i] != '\0' && i < bufferSize) {
			s.str[i] = buffer[i];
			i++;
		}
		s.str[i] = '\0';
		s.len = i;
		return in;
	}

	//Метод find
	int find(char c) const {
		for (int i = 0; i < len; ++i) {
			if (str[i] == c) {
				return 1;
			}
		}
		return -1;
	}

	//Метод length
	int length() const {
		return len;
	}

	//Метод c_str – получить массив char
	const char* c_str() const {
		return str;
	}

	//Метод at для получения доступа (чтение и изменение) к элементу строки с проверкой на выход за пределы строки
	char& at(int index) {
		if (index < 0 || index >= len) {
			throw std::out_of_range("Index out of range");
		}
		return str[index];
	}

};

int main() {
	String a;
	std::cin >>a;
	return 0;

	//базовый конструктор
	String s1;
	std::cout << "s1: " << s1 << '\n';

	//Конструктор копирования
	String s2 = s1;
	std::cout << "s2: " << s2 << '\n';

	// оператор присваивания копированием
	String s3;
	s3 = s1;
	std::cout << "s3: " << s3 << '\n';

	// операторы + и +=
	String s4 = s1 + s2;
	std::cout << "s4: " << s4 << '\n';

	s1 += s2;
	std::cout << "s1: " << s1 << '\n';

	// оператор []
	char c = s2[0];
	std::cout << "c: " << c << '\n';

	s2[0] = 'H';
	std::cout << "s2: " << s2 << '\n';

	// операторы <, >, ==
	bool b1 = s1 < s2;
	bool b2 = s1 > s2;
	bool b3 = s1 == s2;

	std::cout << "b1: " << b1 << '\n';
	std::cout << "b2: " << b2 << '\n';
	std::cout << "b3: " << b3 << '\n';

	// операторы ввода и вывода в поток
	String s5;
	std::cout << "Enter a string: ";
	std::cin >> s5;
	std::cout << "s5: " << s5 << '\n';

	// метод find
	int index = s5.find('a');
	std::cout << "Index of 'a': " << index << '\n';

	// метод length
	int length = s5.length();
	std::cout << "Length of s5: " << length << '\n';

	// метод c_str
	const char* cStr = s5.c_str();
	std::cout << "cStr: " << cStr << '\n';

	// метод at
	//try {
	//	char& character = s5.at(0);
	//	std::cout << "First character of s5: " << character << '\n';

	//	character = 'X';
	//	std::cout << "s5: " << s5 << '\n';

	//	char& invalidCharacter = s5.at(s5.length() + 1); 
	//	std::cout << "Invalid character: " << invalidCharacter << '\n';
	//}
	//catch (const std::out_of_range& e) {
	//	std::cerr << "Error: " << e.what() << '\n';
	//}

	return 0;
}