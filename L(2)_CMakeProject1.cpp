#include <iostream>
#include "L(2)_CMakeProject1.h"


class Matrix {
private:
	int** data;
	int rows;
	int columns;

public:
	Matrix() : data(nullptr), rows(0), columns(0) {}
	Matrix(int N, int M) : rows(N), columns(M) {
		data = new int* [N];
		for (int i = 0; i < rows; i++) {
			data[i] = new int[M];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				data[i][j] = rand();
			}

		}
	};

	Matrix(const Matrix& other) : rows(other.rows), columns(other.columns) {
		data = new int* [rows];
		for (int i = 0; i < rows; i++) {
			data[i] = new int[columns];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				data[i][j] = other.data[i][j];
			}

		}
	}
	Matrix& operator=(const Matrix& other) {
		if (this != &other) {
			for (int i = 0; i < rows; ++i) {
				delete[] data[i];
			}
			delete[] data;

			rows = other.rows;
			columns = other.columns;
			data = new int* [rows];
			for (int i = 0; i < rows; ++i) {
				data[i] = new int[columns];
				for (int j = 0; j < columns; j++) {
					data[i][j] = other.data[i][j];
				}
			}

		};
		return *this;
	}
	~Matrix() {
		for (int i = 0; i < rows; i++) {
			delete[] data[i];
		}
		delete[] data;
	}

	int& at(int i, int j) {
		return data[i][j];
	}
	void print() {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; j++) {
				std::cout << data[i][j] << " ";
			}
			std::cout << std::endl;
		}

	}


};






int main() {
	Matrix A(3, 3);
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			A.at(i, j) = 1;
		}
	}
	A.print();

	Matrix B = A;
	//B.print();
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			B.at(i, j) = 2;
		}
	}
	B.print();
	return 0;
};