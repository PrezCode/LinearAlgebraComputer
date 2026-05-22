//Main file to test and run the linear algebra calculator
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <cstdio>
#include <vector>
#include <array>
#include <sstream>

using Matrix = std::vector<std::vector<double>>;

enum VariableLetter{a, b, c, d};
class MatrixSolver {
private:
	Matrix matrix1, matrix2;
public:
	MatrixSolver() {}
	void RunMatrixSolver() {
		int selection;
		printf("[Matrix Calculator]\n");
		std::cout << "1 - Addition\n2 - Subtraction\n3 - Scalar Multiplication\n4 - Determinant\n" << std::endl;
		printf("Please select an operation:\n");std::cin >> selection;
		switch (selection) {
		case 1:
			BuildMatrices(2);
			MatrixAddition(matrix1, matrix2);
			break;
		case 2:
			BuildMatrices(2);
			MatrixSubtraction(matrix1, matrix2);
			break;
		case 3:
			BuildMatrices(1);
			double scalar;
			std::cout << "Enter a scalar value: "; std::cin >> scalar;
			MatrixScalar(matrix1, scalar);
			break;
		case 4:
			BuildMatrices(1);
			MatrixDeterminant(matrix1);
			break;
		default: printf("Invalid selection. Please select a valid operation.");
			return;
		}
		printMatrix(matrix1);
	}
	void BuildMatrices(int num) {
		size_t rows, cols;
		std::string rowOfValues;
		for (int k = 0; k < num; ++k) {
			printf("[Create Matrix %d]\n", k + 1);
			std::cout << "Rows: "; std::cin >> rows;
			std::cout << "Columns: "; std::cin >> cols;
			std::getline(std::cin, rowOfValues); // Clear the newline character from the input buffer
			if (k == 0) { matrix1.resize(rows); }
			else { matrix2.resize(rows); }
			for (size_t i = 0; i < rows; ++i) {
				std::cout << "Enter row " << i + 1 << " values separated by spaces: ";
				std::getline(std::cin, rowOfValues);
				std::stringstream ss(rowOfValues);
				double temp;
				while (ss >> temp) {
					if (k == 0) { matrix1[i].push_back(temp); }
					else { matrix2[i].push_back(temp); }
				}
			}
		}
	}
	void MatrixAddition(Matrix& A, Matrix& B) {
		//Check if the dimensions of A and B are the same
		if (A.size() != B.size() || A[0].size() != B[0].size()) {
			std::cout << "Error: Matrices must have the same dimensions for addition." << std::endl;
		} else {
			for (int i = 0; i < A.size(); ++i) {
				for (int j = 0; j < A[0].size(); ++j) {
					A[i][j] += B[i][j];
				}
			}
		}
	};
	void MatrixSubtraction(Matrix& A, Matrix& B) {
		//Check if the dimensions of A and B are the same
		if (A.size() != B.size() || A[0].size() != B[0].size()) {
			std::cout << "Error: Matrices must have the same dimensions for subtraction." << std::endl;
		} else {
			for (int i = 0; i < A.size(); ++i) {
				for (int j = 0; j < A[0].size(); ++j) {
					A[i][j] -= B[i][j];
				}
			}
		}
	}
	void MatrixScalar(Matrix& A, double scalar) {
		for (int i = 0; i < A.size(); ++i) {
			for (int j = 0; j < A[0].size(); ++j) {
				A[i][j] *= scalar;
			}
		}
	};
	void MatrixDeterminant(Matrix& A) {
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
			Matrix temp;
			for (int i = 0; i < rows; ++i) {
				std::vector<double> tempRow;
				for (int j = 1; j < cols; ++j) {
					tempRow.push_back(A[i][j] * A[i + 1][j + 1]);
				}
			}
			std::cout << "Determinant: " << det << std::endl;
		}
	}
	void printMatrix(const Matrix& A) {
		printf("Resulting Matrix:\n");
		for (const auto& row : A) {
			printf("| ");
			for (double val : row) {
				std::cout << std::setw(6) << val ;
			}
			printf("|\n");
		}
	}
};

int main() {
	MatrixSolver solver;
	solver.RunMatrixSolver();
	return 0;
}