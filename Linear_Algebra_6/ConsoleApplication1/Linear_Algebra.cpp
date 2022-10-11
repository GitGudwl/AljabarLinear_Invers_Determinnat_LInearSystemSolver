#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#include <string>
#include <Windows.h>
#include <Aspose.Cells.h>

using namespace std;

float** vector_to_array(vector<vector<float>> vals, int N, int M)
{
    float **temp;
    temp = new float *[N];
    for (int i = 0; i < N; i++)
    {
        temp[i] = new float[M];
        for (int j = 0; j < M; j++)
        {
            temp[i][j] = vals[i][j];
        }
    }
    return temp;
}

vector<vector<float>> conver_content(vector<vector<string>> before)
{
    vector<vector<float>> after;
    // convert 2d vector of strings to 2d vector of floats
    for (int i = 0; i < before.size(); i++)
    {
        vector<float> temp;
        for (int j = 0; j < before[i].size(); j++)
        {
            temp.push_back(stof(before[i][j]));
        }
        after.push_back(temp);
    }
    return after;
}

void delete_last_line(string filename)
{
    ifstream in(filename);
    ofstream out("temp.csv");
    string line;
    while (getline(in, line))
    {
        if (in.peek() != EOF)
            out << line << endl;
    }
    in.close();
    out.close();
    remove(filename.c_str());
    rename("temp.csv", filename.c_str());
}

float** parseCSV(string filename)
{
    ifstream data(filename);
    string line;
    vector<vector<string>> parsedCsv;
    while (getline(data, line))
    {
        stringstream lineStream(line);
        string cell;
        vector<string> parsedRow;
        while (getline(lineStream, cell, ','))
        {
            parsedRow.push_back(cell);
        }
        {
            parsedRow.push_back(cell);
        }

        parsedCsv.push_back(parsedRow);
    }
    return vector_to_array(conver_content(parsedCsv), parsedCsv.size(), parsedCsv[0].size());
}

float** matrix_read_file(int dimension)
{
    float **matrix = new float *[dimension];
    for (int i = 0; i < dimension; i++)
        matrix[i] = new float[2 * dimension];
    FILE *fp;
    int row, col;

    fp = fopen("D:/Kuliah/Matrix-Inversion-with-CUDA-master/randomMatrix_2.txt", "r"); // open matrix file
    if (fp == NULL)                                                                    // open failed
        return NULL;

    for (row = 0; row < dimension; row++)
    {
        for (col = 0; col < 2 * dimension; col++)
        {
            if (col < dimension)
            {
                if (fscanf(fp, "%f,", &matrix[row][col]) == EOF)
                    break; // read data

                // sprintf(str, "augmentedmatrix[%d][%d]=", row, col);
                // cout << str << augmentedmatrix[row][col] << endl;
            }
            else
            {
                if (row == col % dimension)
                    matrix[row][col] = 1;
                else
                    matrix[row][col] = 0;

                // sprintf(str, "augmentedmatrix[%d][%d]=", row, col);
                // cout << str << augmentedmatrix[row][col] << endl;
            }
        }

        if (feof(fp))
            break; // if the file is over
    }

    fclose(fp); // close file
    return matrix;
}

float** augment_a_matrix(float **a, int dimension)
{
    float **augmentedmatrix = new float *[dimension];
    for (int i = 0; i < dimension; i++)
        augmentedmatrix[i] = new float[2 * dimension];

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < 2 * dimension; j++)
        {
            if (j < dimension)
                augmentedmatrix[i][j] = a[i][j];
            else
            {
                if (i == j % dimension)
                    augmentedmatrix[i][j] = 1;
                else
                    augmentedmatrix[i][j] = 0;
            }
        }
    }
    return augmentedmatrix;
}

void print_augmented_matrix(float **augmentedmatrix, int dimension)
{
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < 2 * dimension; j++)
            printf("%f ", augmentedmatrix[i][j]);
        printf("\n");
    }
}

void print_result(float** augmentedmatrix, int dimension) {
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
            printf("%f\t", augmentedmatrix[i][dimension + j]);
        printf("\n");
    }
}

float** gauss_jordan(float **augmentedmatrix, int dimension)
{
    int i, j, k, temp;

    float temporary, r;

    for (j = 0; j < dimension; j++)
    {
        temp = j;
        /* finding maximum jth column element in last (dimension-j) rows */

        for (i = j + 1; i < dimension; i++)
            if (augmentedmatrix[i][j] > augmentedmatrix[temp][j])
                temp = i;

        if (fabs(augmentedmatrix[temp][j]) < 0.0005)
        {
            cout << "this matrix has no inverse";
            system("pause");
            exit(1);
            return NULL;
            break;
        }

        /* swapping row which has maximum jth column element */

        if (temp != j)
            for (k = 0; k < 2 * dimension; k++)
            {
                temporary = augmentedmatrix[j][k];
                augmentedmatrix[j][k] = augmentedmatrix[temp][k];
                augmentedmatrix[temp][k] = temporary;
            }

        /* performing row operations to form required identity matrix out of the input matrix */

        for (i = 0; i < dimension; i++)
            if (i != j)
            {
                r = augmentedmatrix[i][j];
                for (k = 0; k < 2 * dimension; k++)
                    augmentedmatrix[i][k] -= (augmentedmatrix[j][k] / augmentedmatrix[j][j]) * r;
            }
            else
            {
                r = augmentedmatrix[i][j];
                for (k = 0; k < 2 * dimension; k++)
                    augmentedmatrix[i][k] /= r;
            }
    }
    return augmentedmatrix;
}

float** matrix_read(float **matrix, int dimension)
{
    cout << "\n2D Array Input:\n";
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            cout << "\ns[" << i << "][" << j << "]=  ";
            cin >> matrix[i][j];
        }
    }
    return matrix;
}

void subMatrix(float **mat, float **temp, int p, int q, int n)
{
    int i = 0, j = 0;
    // filling the sub matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            // skipping if the current row or column is not equal to the current
            // element row and column
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col];
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int determinantOfMatrix(float **matrix, int n, int dimension)
{
    int determinant = 0;
    if (n == 1)
    {
        return matrix[0][0];
    }
    if (n == 2)
    {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }
    float **temp;
    temp = new float *[dimension];
    for (int i = 0; i < dimension; i++)
    {
        temp[i] = new float[dimension];
    }
    int sign = 1;

    for (int i = 0; i < n; i++)
    {
        subMatrix(matrix, temp, 0, i, n);
        determinant += sign * matrix[0][i] * determinantOfMatrix(temp, n - 1, dimension);
        sign = -sign;
    }
    return determinant;
}

void out_csv(float** augmentedmatrix, string filename, int dimension)
{
    system("pause");
    ofstream ofile;							   // define output file
    ofile.open(filename, ios::out | ios::app); // open output file
    for (int i = 0; i < dimension; i++)
    {
        for (int j =0; j < dimension; j++)
            ofile << augmentedmatrix[i][dimension +j] << ",";
        ofile << "\n";
    }
    ofile.close(); // close output file
    system("Color 0A");
    system("cls");
    cout << "result has been successfully inserted into result.csv";
}

float** array_initializer(int dimension) {
    float** temp;
    temp = new float* [dimension];
    for (int i = 0; i < dimension; i++)
    {
        temp[i] = new float[dimension];
    }
    return temp;
}

float** array_initializer_LinearSystem(int dimension) {
    float** temp;
    temp = new float* [dimension+1];
    for (int i = 0; i < dimension; i++)
    {
        temp[i] = new float[dimension];
    }
    return temp;
}

void printMatrix_LinearSystem(float** matrix, int dimension) {
    cout << "\nArray\n";
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension + 1; j++)
        {
            cout << matrix[i][j] << "\t";
        }
        printf("\n");
    }
}

int PerformOperation(float** a, int n) {
    int i, j, k = 0, c, flag = 0, m = 0;
    float pro = 0;

    // Performing elementary operations
    for (i = 0; i < n; i++)
    {
        if (a[i][i] == 0)
        {
            c = 1;
            while ((i + c) < n && a[i + c][i] == 0)
                c++;
            if ((i + c) == n) {
                flag = 1;
                break;
            }
            for (j = i, k = 0; k <= n; k++)
                swap(a[j][k], a[j + c][k]);
        }

        for (j = 0; j < n; j++) {

            // Excluding all i == j
            if (i != j) {

                // Converting Matrix to reduced row
                // echelon form(diagonal matrix)
                float pro = a[j][i] / a[i][i];

                for (k = 0; k <= n; k++)
                    a[j][k] = a[j][k] - (a[i][k]) * pro;
            }
        }
    }
    printMatrix_LinearSystem(a, n);
    return flag;
}

int CheckConsistency(float** a, int dimension, int flag)
{
    int i, j;
    float sum;

    // flag == 2 for infinite solution
    // flag == 3 for No solution
    flag = 3;
    for (i = 0; i < dimension; i++)
    {
        sum = 0;
        for (j = 0; j < dimension; j++)
            sum = sum + a[i][j];
        if (sum == a[i][j])
            flag = 2;
    }
    return flag;
}

float** readmatrix_LinearSystem(float** matrix, int dimension) {
    cout << "\n2D Array Input:\n";
    for (int i = 0; i < dimension ; i++)
    {
        for (int j = 0; j < dimension+1; j++)
        {
            cout << "\ns[" << i << "][" << j << "]=  ";
            cin >> matrix[i][j];
        }
    }
    return matrix;
}

void PrintResult_LinearSystem(float** a, int n, int flag)
{
    cout << "Result is : ";

    if (flag == 2)
        cout << "Infinite Solutions Exists" << endl;
    else if (flag == 3)
        cout << "No Solution Exists" << endl;


    // Printing the solution by dividing constants by
    // their respective diagonal elements
    else {
        for (int i = 0; i < n; i++)
            cout << "x"<< i+1 << " = " << a[i][n] / a[i][i] << "\t";
    }
}



int main() {
    int dimension, flag;
    int menuControl;
    float** array;
    char filename[50];
    intrusive_ptr<Aspose::Cells::IWorkbook> wkb;
    
    cout << "(1) for Manual Input\t(2) for read from file\n";
    cout << "Please choose the input method : ";
    cin  >> menuControl;

    switch (menuControl)
    {
    case 1: // manual input
        int manual_metode;
        cout << "\n===================================\n";
        cout << "\n(1) Inverse\t(2) Determinan\t (3) Linear System Solver (Gaussian Elimination)\n";
        cout << "Please choose the manual method : ";
        cin >> manual_metode;
        switch (manual_metode)
        {
        case 1: // Inverse
            cout << "\nPlease input the dimension : ";
            cin >> dimension;
            array = array_initializer(dimension);
            array = matrix_read(array, dimension);
            cout << "\ninvers of the matrix is : \n";
            print_result(gauss_jordan(augment_a_matrix(array, dimension), dimension), dimension);
            break;
        case 2: // Determinan
            cout << "\nPlease input the dimension : ";
            cin >> dimension;
            array = array_initializer(dimension);
            array = matrix_read(array, dimension);
            cout << "\nDeterminan of the matrix is : " << determinantOfMatrix(array, dimension, dimension);
            break;
        case 3 : //spl problem
            cout << "\nPlease input the dimension (extra row will added for 4onstanta) : ";
            cin >> dimension;
            array = array_initializer_LinearSystem(dimension);
            array = readmatrix_LinearSystem(array, dimension);
            printMatrix_LinearSystem(array, dimension);
            cout << "\nOpeation is done" << endl;
            flag = PerformOperation(array, dimension);
            if (flag == 1)
                flag = CheckConsistency(array, dimension, flag);
            cout << "\nFinish" << endl;
            
            PrintResult_LinearSystem(array, dimension, flag);
            break;
        default:
            break;
        }
        break;
    case 2: // read of file
        int file_metode;
        cout << "\n===================================\n";
        cout << "\n(1) Inverse (CSV)\t(2) Determinan(CSV)\t(3) Invers(xlsx)\t(4) Determinan(xlsx) \n";
        cout << "Please choose the read of file method : ";
        cin >> file_metode;
        cout << "Please Insert the file name : ";
        cin >> filename;
        switch (file_metode)

        {
        case 1: 
            cout << "Please input the dimension : ";
            cin >> dimension;
            array = array_initializer(dimension);
            array = parseCSV(filename);
            cout << "\ninvers of the matrix is : \n";
            print_result(gauss_jordan(augment_a_matrix(array, dimension), dimension), dimension);
            out_csv(gauss_jordan(augment_a_matrix(array, dimension), dimension), "result.csv", dimension);
            break;
        case 2: 
            cout << "Please input the dimension : ";
            cin >> dimension;
            array = array_initializer(dimension);
            array = parseCSV(filename);
            cout << "\nDeterminan of the matrix is : " << determinantOfMatrix(array, dimension, dimension);
            break;
        case 3:
            cout << "Please input the dimension : ";
            cin >> dimension;
            array = array_initializer(dimension);
            wkb = Factory::CreateIWorkbook(new String(filename));
            wkb->Save(new String("Output.csv"));
            delete_last_line("Output.csv");
            array = parseCSV("Output.csv");
            cout << "\ninvers of the matrix is : \n";
            print_result(gauss_jordan(augment_a_matrix(array, dimension), dimension), dimension);
            out_csv(array, "result.csv", dimension);
            break;
        case 4:
            cout << "Please input the dimension : ";
            cin >> dimension;
            array = array_initializer(dimension);
            wkb = Factory::CreateIWorkbook(new String(filename));
            wkb->Save(new String("Output.csv"));
            delete_last_line("Output.csv");
            array = parseCSV("Output.csv");
            cout << "\nDeterminan of the matrix is : " << determinantOfMatrix(array, dimension, dimension);
            break;
        default:
            break;
        }
    default:
        break;
    }

        return 0;
    }
