//Main file to test and run the linear algebra calculator
#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <vector>
#include <array>

enum VariableLetter{a, b, c, d};
class MatrixSolver {
public:
	MatrixSolver() {}
	void RunMatrixSolver() {};
	void BuildMatrix() {};
	void MatrixAddition(std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& B) {
		//Check if the dimensions of A and B are the same
		if (A.size() != B.size() || A[0].size() != B[0].size()) {
			std::cout << "Error: Matrices must have the same dimensions for addition." << std::endl;
		}
		else {
			for (int i = 0; i < A.size(); ++i) {
				for (int j = 0; j < A[0].size(); ++j) {
					A[i][j] += B[i][j];
				}
			}
			printf("Result of Matrix Addition:\n");
			for (const auto& row : A) {
				for (double val : row) {
					std::cout << val << " ";
				}
				std::cout << std::endl;
			}
		}
	};
	void MatrixSubtraction(std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& B) {
		//Check if the dimensions of A and B are the same
		if (A.size() != B.size() || A[0].size() != B[0].size()) {
			std::cout << "Error: Matrices must have the same dimensions for subtraction." << std::endl;
		}
		else {
			for (int i = 0; i < A.size(); ++i) {
				for (int j = 0; j < A[0].size(); ++j) {
					A[i][j] -= B[i][j];
				}
			}
			printf("Result of Matrix Subtraction:\n");
			for (const auto& row : A) {
				for (double val : row) {
					std::cout << val << " ";
				}
				std::cout << std::endl;
			}
		}
	};
	void MatrixScalar(std::vector<std::vector<double>>& A, double scalar) {
		for (int i = 0; i < A.size(); ++i) {
			for (int j = 0; j < A[0].size(); ++j) {
				A[i][j] *= scalar;
			}
		}
		printf("Result of Matrix Scalar Multiplication:\n");
		for (const auto& row : A) {
			for (double val : row) {
				std::cout << val << " ";
			}
			std::cout << std::endl;
		}
	};
	void MatrixDeterminant(std::vector<std::vector<double>>& A, VariableLetter variable) {
		size_t rows = A.size();
		size_t cols = A[0].size();
		double det{ 0.0 };
		//Check if Matrix can be made square
		if (rows != cols) {
			std::cout << "Matrix is not Square; Determinant is Not Possible" << std::endl;
			return;
		}
		if (rows == 2 && cols == 2) {
			det = A[0][0] * A[1][1] - A[0][1] * A[1][0];
			std::cout << "Determinant: " << det << std::endl;
		}
		else {
			std::vector<std::vector<double>> temp;
			for (int i = 0; i < rows; ++i) {
				std::vector<double> tempRow;
				for (int j = 1; j < cols; ++j) {
					tempRow.push_back(A[i][j] * A[i+1][j+1]);
				}
			}
			std::cout << "Determinant: " << det << std::endl;
		}
	};
};

int main() {
	std::vector<std::vector<double>> A {{ {1, 2}, {3, 4} }};
	std::vector<std::vector<double>> B {{ {5, 6}, {7, 8} }};
	MatrixSolver solver;
	solver.MatrixAddition(A, B);
	solver.MatrixSubtraction(A, B);
	solver.MatrixScalar(A, 2.0);
	return 0;
}