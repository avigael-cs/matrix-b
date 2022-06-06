#include <iostream>
#include <vector>
#include <sstream>
#include "Matrix.hpp"

using namespace std;

namespace zich
{
    Matrix::Matrix(vector<vector<double>> matrix) {
        this->matrix = matrix;
        row = matrix.size();
        col = matrix[0].size();
    }

    Matrix::Matrix(vector<double> matrix, int row, int col)
    {
        if(row <= 0 || col <= 0 || matrix.size() != row * col){
            throw invalid_argument("all values need to be positive");
        }
        // if( row * col != matrix.size()){
        //   throw("Error Unsupported size");
        // }
        // this->matrix.resize((size_t)row);
        size_t ezer = 0;
        for(int i = 0; i < row; i++){
            //line in matrix n - one vec
            vector<double> tmp;
            for(int j = 0; j < col; j++){
                tmp.push_back(matrix[ezer]);
                ezer++;
            }
            this->matrix.push_back(tmp);
        }
        this->row = row;
        this->col = col;
    }

     Matrix::Matrix(const Matrix &other)
    {
        if (other.row <= 0 || other.col <= 0)
        {
            throw invalid_argument("wrong inputs - the number of the row and columns need to be positivs!");
        }
        // this->matrix.resize((size_t)other.row);
        this->row = other.row;
        this->col = other.col;
        for(unsigned int i = 0; i < row; i++){
            //line in matrix n - one vec
            vector<double> tmp;
            for(unsigned int j = 0; j < col; j++){
                tmp.push_back(other.matrix[i][j]);
            }
            this->matrix.push_back(tmp);
        }
    }

    Matrix::Matrix (int row, int col){
        if (row<=0 || col<=0){
            throw invalid_argument("row and col need to be positive");
        }

        this->row = row;
        this->col = col;
        this->matrix = vector<vector<double>>((unsigned long)row, vector<double>((unsigned long)col));
    }

    //sum of matrix
    double Matrix::sum (Matrix const& mat){
        int sum = 0;
        int r = mat.row;
        int c = mat.col;
         for (size_t i = 0; i < r; i++)
        {
            for (size_t j = 0; j < c; j++)
            {
                sum += mat.matrix.at(i).at(j);
            }
        }
        return sum;
    }

    void check(int rowA, int colA, int rowB, int colB) {
        if (rowA < 1 || rowB < 1 || colA < 1 || colB < 1) {
            throw runtime_error("The col and row need to be positive");
        }
        if (rowA != rowB || colA != colB) {
            throw runtime_error("The col and row need to be equal");
        }
    }

    Matrix Matrix::operator+(const Matrix &other) const {
        if(this->row != other.row || this->col != other.col) {
            throw("to use this operator, the matrices need to be same size");
        }
        Matrix tmp(*this);
        for(unsigned int i=0; i<this->row; i++){
            for(unsigned int j=0; j<this->col; j++){
                tmp.matrix[i][j] += other.matrix[i][j];
            }
        }
        return tmp;
    }

    Matrix Matrix::operator+() const{
        Matrix tmp(*this);
        for(size_t i = 0; i < row; i++){
            for(size_t j = 0; j < col; j++){
                tmp.matrix[i][j] = abs(tmp.matrix[i][j]);
            }
        }
        return tmp;
    }
    Matrix& Matrix::operator+=(const Matrix &other){
        if(this->row != other.row || this->col != other.col)
        {
            throw("to use this operator, the matrices need to be same size");
            }
        for(unsigned int i=0; i<this->row; i++){
            for(unsigned int j=0; j<this->col; j++){
                this->matrix[i][j] += other.matrix[i][j];
            }
        }
        return *this;
    }

    Matrix Matrix::operator-(const Matrix &other) const {
        if(this->row != other.row || this->col != other.col)
        {
            throw("to use this operator, the matrices need to be same size");
            }
        Matrix tmp(*this);
        for(unsigned int i=0; i<this->row; i++){
            for(unsigned int j=0; j<this->col; j++){
                tmp.matrix[i][j] -= other.matrix[i][j];  
              }
        }
        return tmp;
    }

    Matrix Matrix::operator-() const{
        Matrix tmp(*this);
        for(size_t i = 0; i < row; i++){
            for(size_t j = 0; j < col; j++){
                tmp.matrix[i][j] *= -1;
            }
        }
    return tmp;   
    }
    Matrix& Matrix::operator-=(const Matrix &other){
        if(this->row != other.row || this->col != other.col)
        {
            throw("to use this operator, the matrices need to be same size");
            }
        for(unsigned int i=0; i<this->row; i++){
            for(unsigned int j=0; j<this->col; j++){
                this->matrix[i][j] -= other.matrix[i][j];
            }
        }
        return *this;
    }
    //Boolean opearators:
    bool Matrix::operator<(Matrix const& other)const{
        if (row != other.row || col != other.col) {
            throw runtime_error("dimensions error");
        }
        double sum1 = sum(*this);
        double sum2 = sum(other);
        return(sum1 < sum2);
    }
    bool Matrix::operator<=(Matrix const& other)const{
        if (row != other.row || col != other.col) {
            throw runtime_error("dimensions error");
        }
        double sum1 = sum(*this);
        double sum2 = sum(other);
        return(sum1 <= sum2);
        }
    bool Matrix::operator>(Matrix const& other)const{
        if (row != other.row || col != other.col) {
            throw runtime_error("dimensions error");
        }
        double sum1 = sum(*this);
        double sum2 = sum(other);
        return(sum1 > sum2);
        }
    bool Matrix::operator>=(const Matrix &other)const{
        if (row != other.row || col != other.col) {
            throw runtime_error("dimensions error");
        }
        double sum1 = sum(*this);
        double sum2 = sum(other);
        return(sum1 >= sum2);
        }
    bool Matrix::operator==(Matrix const& other)const{
         if(this->row != other.row || this->col != other.col)
         {
            throw runtime_error("to use this operator, the matrices need to be same size");
         }
         for(unsigned int i=0; i<this->row; i++){
            for(unsigned int j=0; j<this->col; j++){
                if(this->matrix[i][j] != other.matrix[i][j]){
                    return false;
                }
            }
        }
        return true;
    }
    bool Matrix::operator!=(Matrix const& other)const{
        if (other.row != this->row || other.col  != this->col){
            throw runtime_error("to use this operator, the matrices need to be same size");
        }
        for (size_t i = 0; i < other.row; i++){
            for (size_t j = 0; j < other.col; j++){
                if (this->matrix[i][j] != other.matrix[i][j]){
                    return true;
                }
            }
        }
        return false;
    }
    //
  
    //++--
    Matrix Matrix::operator++(){
        for(unsigned int i=0; i<this->row; i++){
            for(unsigned int j=0; j<this->col; j++){
                this->matrix.at(i).at(j)++;
            }
        }
        return *this;
    }
    Matrix Matrix::operator++(int){
        Matrix temp(*this);
            
        for(unsigned int i=0; i<this->row; i++){
            for(unsigned int j=0; j<this->col; j++){
                this->matrix[i][j]+= 1;
            }
        }
        return temp;
    }
    Matrix Matrix::operator--(){
        for(unsigned int i=0; i<this->row; i++){
            for(unsigned int j=0; j<this->col; j++){
                this->matrix.at(i).at(j)--;
            }
        }
        return *this;
    }
    Matrix Matrix::operator--(int){
        Matrix temp(*this);
        for(unsigned int i=0; i<this->row; i++){
            for(unsigned int j=0; j<this->col; j++){
                this->matrix[i][j]-= 1;
            }
        }
        return temp;
    }

    //multiplication

    Matrix& Matrix::operator*=(const double &num)
    {
        for(size_t i = 0; i < this->row; i++){
            for(size_t j = 0; j < this->col; j++){
                this->matrix.at(i).at(j) = (this->matrix.at(i).at(j) * num);
            }
        }
        return *this;
    }
    Matrix Matrix::operator*(double num) const
    {
        Matrix temp(*this);
        temp *= num;
        return temp;
    }

    Matrix& Matrix::operator*=(const Matrix &other)
    {
        Matrix temp(*this);
        temp = temp * other;
        matrix = temp.matrix;
        return *this;
        /*if(this->col != other.row){
            throw("to use this operator, the matrices need to be same size");
        }
        unsigned int tmp = 0;
        vector <double> vec;
        for (unsigned int i = 0; i < this->row; i++) {
            for (unsigned int j = 0; j < other.col; j++) {
                vec.push_back(0);
                for (unsigned int k = 0; k < other.row; k++) {
                    vec[tmp] += this->matrix[i][k] * other.matrix[k][j];
                }
                tmp++;
            }
        }
        tmp=0;
        for(unsigned int i=0; i<this->row; i++){//put everything back to 'this'
            for(unsigned int j=0; j<this->col; j++){
                this->matrix[i][j] = vec[tmp++];
            }
        }
        return(*this);*/
    }

    Matrix operator*(double num, const Matrix &mat)
    {
        Matrix tmp(mat); 
        for(size_t i = 0; i < mat.row; i++){
            for(size_t j = 0; j < mat.col; j++){
                tmp.matrix[i][j] *= num;
            }
        }
        return tmp;
    }

    /*Matrix operator* (double num, const Matrix &mat){
        Matrix tmp(mat); 
        for(size_t i = 0; i < mat.row; i++){
            for(size_t j = 0; j < mat.col; j++){
                tmp.matrix[i][j] *= num;
            }
        }
        return tmp;
    }*/
    
    Matrix Matrix::operator*(const Matrix& other) const {
        if (col != other.row) {
            throw std::invalid_argument("Invalid sizes for multiplication");
        }

        Matrix result(row, other.col);
        for (unsigned int i = 0; i < row; i++) {
            for (unsigned int j = 0; j < other.col; j++) {
                for (unsigned int k = 0; k < col; k++) {
                    result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
                }
            }
        }

        return result;
    }

    ostream& operator<<(ostream& out, const Matrix& other)
    {
        for(size_t i = 0; i < other.row; i++){
            out << "[";
            for(size_t j = 0; j < other.col; j++){
                if(j == other.col - 1){
                    out << other.matrix[i][j]; 
                }
                else{
                    out << other.matrix[i][j] << " "; 
                }            
            }
            if(i != other.row -1){
                out << "]" << '\n';
            }
            else{
                out << "]";
            }
        }
        
        return out;
    }

    istream &operator>>(istream &in, Matrix &other)
    {
        string s;
        getline(in, s);
        
        vector<string> tokens;
        size_t pos = 0;
        std::string token;
        while ((pos = s.find(string(", "))) != std::string::npos) {
            token = s.substr(0, pos);
            tokens.push_back(token);
            s.erase(0, pos + 2);
        }
        tokens.push_back(s);

        vector<vector<double>> matrix;
        for (string& line : tokens) {
            if (line[0] != '[' || line[line.size() - 1] != ']') {
                throw invalid_argument("invalid line format");
            }

            line = line.substr(1, line.size() - 2);

            if (line.find(string(",")) != std::string::npos ||
                line.find(string("[")) != std::string::npos || 
                line.find(string("]")) != std::string::npos) {
                    throw invalid_argument("invalid line format");
            }

            vector<double> nums;
            while ((pos = line.find(string(" "))) != std::string::npos) {
                token = line.substr(0, pos);
                line.erase(0, pos + 1);
                nums.push_back(std::stod(token));
            }
            nums.push_back(std::stod(line));

            if (!matrix.empty() && matrix[0].size() != nums.size()) {
                throw invalid_argument("invalid line size");
            }

            matrix.push_back(nums);
        }

        other = Matrix(matrix);




        return in;
    }
}
