#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

namespace zich
{
    class Matrix
    {
    private:
        vector<vector<double>> matrix;
        int row;
        int col;
    
    public:
        Matrix(vector<double> matrix, int row, int col);
        Matrix(int row, int col);
        Matrix(vector<vector<double>> matrix);
        //Matrix(const (vector<double> vec&), int r, int c);
        Matrix(const Matrix &other); //copy

        //Basic operators :
        Matrix operator+() const; //Unary +a
        Matrix operator+(const Matrix &) const; //Add a+b
        Matrix& operator+=(const Matrix &); //Add to this a+=b
        Matrix& operator+= (double num);
        Matrix operator-() const; //Unary -a
        Matrix operator-(const Matrix &) const; // Subtract a-b
        Matrix& operator-=(const Matrix &); //Subtract from this a-=b
        Matrix& operator-=(double num);
        //mat + mat
        // friend Matrix operator+(Matrix Mat1, const Matrix& Mat2);

        //Boolean opearators:
        //friend int compare(const Matrix&, double);
        bool operator<(const Matrix &other)const;
        bool operator<=(const Matrix &other)const;
        bool operator>(const Matrix &other)const;
        bool operator>=(const Matrix &other)const;
        bool operator==(const Matrix &other)const;
        bool operator!=(const Matrix &other)const;

        Matrix operator++();//++prefix
        Matrix operator++(int); //postfix++
        Matrix operator--();//--prefix
        Matrix operator--(int); //postfix--

        //Multiplication by 'double':
        Matrix operator*(const Matrix &) const;
        Matrix operator*(double num) const;
        Matrix& operator*=(const Matrix &);
        Matrix& operator*=(const double &);
        
        //Input/Output :
        friend Matrix operator*(double num, const Matrix &mat);
        friend ostream &operator<<(ostream& out, const Matrix& other);
        friend istream &operator>>(istream &in,  Matrix &other);
        //help
         //compute sum of matrix
        static double sum(Matrix const& mat);
        /*int getRow() const{
            return this->row;
        }
        int getCol() const{
            return this->col;
        }
         std::vector<double> getVec()const
        {
             return this->vec;
        }*/
        vector<vector<double> > getMat() const;
        
    };
}