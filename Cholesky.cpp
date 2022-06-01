#include <vector>
#include <iomanip>
#include <cmath>
#include <iostream>

typedef std::vector<std::vector<double>> matrix_t;

matrix_t CholeskyDecomposition(matrix_t matrix)
{
    matrix_t L(matrix.size(), std::vector<double> (matrix.size(), 0));

     for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j <= i; j++) {
            int sum = 0;
 
            if (j == i) 
            {
                for (int k = 0; k < j; k++)
                    sum += pow(L[j][k], 2);

                L[j][j] = sqrt(matrix[j][j] - sum);
            } 
            else {
 
                for (int k = 0; k < j; k++)
                    sum += (L[i][k] * L[j][k]);

                L[i][j] = (matrix[i][j] - sum) / L[j][j];
            }
        }
    }

    return L; 
}

matrix_t Transpose(matrix_t matrix)
{
    matrix_t transposed(matrix.size(), std::vector<double> (matrix.size(), 0));

    for (int i = 0; i < matrix.size(); ++i) 
    {
        for (int j = 0; j < matrix[i].size(); ++j)
        {
            transposed[i][j] = matrix[j][i];
        }
    }
    return transposed;
}

void Print(matrix_t matrix)
{
    for (auto &row: matrix)
    {
        for (auto &col: row) 
        {
            std::cout << std::setw(3) << col << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void Pretty_Print(matrix_t L, matrix_t L_t)
{
    for (int i = 0; i < L.size(); i++)
    {
        for (int j = 0; j < L[i].size(); j++)
        {
            std::cout << std::setw(3) <<L[i][j] << ' ';
        }

        for (int k = 0; k < L_t[i].size(); k++) 
        {
            if (i == L.size()/2 && k == 0) {
                std::cout << "  X  ";
            } else if (k == 0) {
                std::cout << "\t ";
            }
            std::cout << std::setw(3) << L_t[i][k] << ' ';
        }
        std::cout << '\n';
    }    
}

int main()
{
    matrix_t matrix{{4,  12,  -16}, 
                    {12, 37,  -43}, 
                    {-16, -43, 98}};
        
    

    matrix_t cholesky = CholeskyDecomposition(matrix);
    matrix_t transposed_L = Transpose(cholesky);

    std::cout << "Initial matrix: " << '\n';
    Print(matrix);
    
    std::cout << "L matrix: " << '\n';
    Print(cholesky);

    std::cout << "L_t matrix: " << '\n';
    Print(transposed_L);

    std::cout << "Cholesky decomposition: " << '\n';
    Pretty_Print(cholesky, transposed_L);
    
    return 0;
}