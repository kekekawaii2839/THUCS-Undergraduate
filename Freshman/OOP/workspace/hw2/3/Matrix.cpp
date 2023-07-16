#include "Matrix.h"

Matrix::Matrix(){
	elem = new int*[30];
	for(int i = 0; i < 30; ++i) elem[i] = new int[30]{0};
}

Matrix::Matrix(int _row, int _col){
	elem = new int*[_row];
	for(int i = 0; i < _row; ++i) elem[i] = new int[_col]{0};
	row = _row;
	col = _col;
}

Matrix::~Matrix(){
	for(int i = 0; i < row; ++i) delete []elem[i];
	delete []elem;
}

Matrix Matrix::operator+(const Matrix& a){
	Matrix temp(row,col);
	for(int i = 0; i < row; ++i){
		for(int j = 0; j < col; ++j) temp[i][j] = (*this)[i][j] + a[i][j];
	}
	return temp;
}

Matrix Matrix::operator-(const Matrix& a){
	Matrix temp(row,col);
	for(int i = 0; i < row; ++i){
		for(int j = 0; j < col; ++j) temp[i][j] = (*this)[i][j] - a[i][j];
	}
	return temp;
}

Matrix Matrix::operator*(const int a){
	Matrix temp(row,col);
	for(int i = 0; i < row; ++i){
		for(int j = 0; j < col; ++j) temp[i][j] = (*this)[i][j] * a;
	}
	return temp;
}

Matrix Matrix::operator*(const Matrix& a){
	Matrix temp(row,a.col);
	for(int j = 0; j < a.col; ++j){
		for(int i = 0; i < row; ++i){
			for(int ii = 0; ii < col; ++ii){
				temp[i][j] += elem[i][ii] * a[ii][j];
			}
		}
	}
	return temp;
}

Matrix transpose(const Matrix& a){
	Matrix temp(a.col,a.row);
	for(int i = 0; i < a.col; ++i){
		for(int j = 0; j < a.row; ++j) temp[i][j] = a[j][i];
	}
	return temp;
}

int* Matrix::operator[](int a) const{
	return elem[a];
}

std::ostream& operator<<(std::ostream& out, const Matrix& a){
	for(int i = 0; i < a.row; ++i){
		for(int j = 0; j < a.col; ++j) out<<a[i][j]<<' ';
		out<<std::endl;
	}
	return out;
}

std::istream& operator>>(std::istream& in, Matrix& a){
	in>>a.row>>a.col; 
	for(int i = 0; i < a.row; ++i){
		for(int j = 0; j < a.col; ++j) in>>a[i][j];
	}
	//std::cout<<"matrix is"<<a.row<<' '<<a.col<<':'<<std::endl;
	//std::cout<<a<<std::endl;
	
	return in;
}
