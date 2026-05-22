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
		printf("1 - Addition\n2 - Subtraction\n3 - Scalar Multiplication\n4 - Determinant\n5 - Cramer's Rule\n");
		printf("Please select an operation: ");std::cin >> selection;
		switch (selection) {
			case 1:
				BuildMatrices(2);
				MatrixAddition(matrix1, matrix2);
				printMatrix(matrix1);
				break;
			case 2:
				BuildMatrices(2);
				MatrixSubtraction(matrix1, matrix2);
				printMatrix(matrix1);
				break;
			case 3:
				BuildMatrices(1);
				double scalar;
				std::cout << "Enter a scalar value: "; std::cin >> scalar;
				MatrixScalar(matrix1, scalar);
				printMatrix(matrix1);
				break;
			case 4:
				BuildMatrices(1);
				printf("Determinant: %f\n", MatrixDeterminant(matrix1));
				break;
			case 5:
				BuildMatrices(1);
				CramersRule(matrix1);
				break;
			default: printf("Invalid selection. Please select a valid operation.");
				return;
		}
	}
private:
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
			std::cout << std::endl;
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
	double MatrixDeterminant(Matrix& A) {
		size_t rows = A.size();
		size_t cols = A[0].size();
		double det{ 0.0 };
		//Check if Matrix is square
		if (rows != cols) {
			std::cout << "Error: Determinant can only be calculated for square matrices." << std::endl;
			return 0;
		}
		if (rows == 2 && cols == 2) { 
			det = A[0][0] * A[1][1] - A[0][1] * A[1][0]; 
		} else {
			Matrix temp;
			temp.resize(rows);
			for (int i = 0; i < rows; ++i) {
				for (int j = 0; j < cols; ++j) { temp[i].push_back(A[i][j]); }
				for (int k = 0; k < rows - 1; ++k) {
					temp[i].push_back(A[i][k]);
				}
			}
			double addProduct{ 1.0 }, subtractProduct{ 1.0 };
			for (int i = 0; i < rows; ++i) {
				for (int j = 0; j < rows; ++j) {
					addProduct *= temp[j][i + j];
					subtractProduct *= temp[rows - 1 - j][i + j];
				}
				det += addProduct - subtractProduct;
				addProduct = subtractProduct = 1.0;
			}
		}
		return det;
	}
	void CramersRule(Matrix& A) { //Currently non-functional, needs to be fixed
		size_t rows = A.size();
		Matrix tempBase, tempA, tempB, tempC;
		double detA{ 0.0 }, x1{ 0.0 }, x2{ 0.0 }, x3{ 0.0 };
		tempBase.resize(rows); tempA.resize(rows); tempB.resize(rows); tempC.resize(rows);
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < rows + 1; ++j) {
				tempBase[i][j] = A[i][j];
				tempA[i][0] = A[i][rows + 1];
				tempB[i][1] = A[i][rows + 1];
				if(A.size() == 3){ tempC[i][2] = A[i][rows + 1]; }
			}
		}
		detA = MatrixDeterminant(tempBase);
		x1 = MatrixDeterminant(tempA) / detA;
		x2 = MatrixDeterminant(tempB) / detA;
		if (A.size() == 3) { x3 = MatrixDeterminant(tempC) / detA; }
		printf("Solutions:\n");
		std::cout << "x1: " << x1 << "\nx2: " << x2 << "\nx3: " << x3 << std::endl;
	}
	void printMatrix(const Matrix& A) {
		printf("\nResulting Matrix:\n");
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