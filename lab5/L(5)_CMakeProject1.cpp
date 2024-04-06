#include "L(5)_CMakeProject1.h"
#include <iostream>
#include <math.h>
#include <string>
template <typename T, int N, int M>
class Matrix {
public:
	Matrix() {
		content = new T * [rows];
		for (int i = 0; i < rows; i++) {
			content[i] = new T[cols];
		}
	}
	Matrix(Matrix<T, N, M> const& other) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				content[i][j] = other[i][j];
			}
		}
	}
	void operator=(Matrix const& other) {
		rows = other.Rows();
		cols = other.Cols();
		content = new T * [rows];
		for (int i = 0; i < rows; i++) {
			content[i] = new T[cols];
			for (int j = 0; j < cols; j++) {
				content[i][j] = other[i][j];
			}
		}
	}
	friend std::ostream& operator<<(std::ostream& os, Matrix const& m) {
		std::string output = "";
		for (int i = 0; i < m.Rows(); i++) {
			for (int j = 0; j < m.Cols(); j++) {
				output += std::to_string(m[i][j]) + " ";
			}
			output += "\n";
		}
		return os << output;
	}
	friend std::istream& operator>>(std::istream& is, Matrix& m) {
		Matrix tmp = Matrix<T, N, M>();
		for (int i = 0; i < tmp.Rows(); i++) {
			for (int j = 0; j < tmp.Cols(); j++) {
				is >> tmp[i][j];
			}
		}
		m = tmp;
		return is;
	}

	T* operator[](int ind) const { return content[ind]; }

	Matrix& operator+=(Matrix const& other) {
		if (rows != other.rows() || cols != other.cols()) {
			std::cout << "неправильные размеры матриц";
			exit(1);
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				content[i][j] += other[i][j];
			}
		}
		return *this;
	}
	Matrix& operator*=(Matrix const& other) {
		if (cols != other.rows()) {
			std::cout << "неправильные размеры матриц";
			exit(1);
		}
		Matrix res(rows, other.cols());
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < other.cols(); j++) {
				for (int k = 0; k < cols; k++) {
					res[i][j] += content[i][k] * other[k][j];
				}
			}
		}
		*this = res;
		return *this;
	}
	Matrix operator+(Matrix const& other) {
		if (rows != other.Rows() || cols != other.Cols()) {
			std::cout << "Неправильные размеры матриц";
			exit(1);
		}
		Matrix<T, N, M> res;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				res[i][j] = (*this)[i][j] + other[i][j];
			}
		}
		return res;
	}
	Matrix& operator++() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				++content[i][j];
			}
		}
		return *this;
	}
	T determinant() {
		if (rows != cols) {
			std::cout << "Матрица должна быть квадратной";
			exit(1);
		}
		if (rows == 1) {
			return content[0][0];
		}
		else if (rows == 2) {
			return content[0][0] * content[1][1] - content[0][1] * content[1][0];
		}
		else {
			T det = 0;
			for (int i = 0; i < rows; i++) {
				det += pow(-1, i) * content[0][i] * minor(0, i).determinant();
			}
			return det;
		}
	}
	Matrix minor(int row, int col) {
		Matrix m(rows - 1, cols - 1);
		int r = 0, c = 0;
		for (int i = 0; i < rows; i++) {
			if (i != row) {
				for (int j = 0; j < cols; j++) {
					if (j != col) {
						m.content[r][c++] = content[i][j];
					}
				}
				r++;
				c = 0;
			}
		}
		return m;
	}
	T& operator()(int i, int j) const {
		return content[i][j];
	}
	int Rows() const { return rows; }
	int Cols() const { return cols; }

private:
	T** content;
	int rows = N;
	int cols = M;
};

int main(int argc, char* argv[]) {
	Matrix<int, 3, 3> a, b, c;
	std::cin >> a;
	b = a;
	c = a + b;
	std::cout << c;
}
