#include <cassert>
#include <vector>

class Matrix{
public:
    Matrix(int rows, int columns) : rows_(rows), columns_(columns), values_(rows * columns, 0) {}
    int& operator()(int row, int column){
        return values_[row * columns_ + column];
    }
    int operator()(int row, int column) const{
        return values_[row * columns_ + column];
    }
    Matrix operator+(Matrix m){
        assert(rows_ == m.rows_);
        assert(columns_ == m.columns_);
        Matrix result(rows_, columns_);
        for(int i = 0; i < rows_; i++){
            for(int j = 0; j < columns_; j++){
                result(i, j) = values_[i * columns_ + j] + m(i, j);
            }
        }
        return result;
    }

private:
    int rows_;
    int columns_;
    std::vector<int> values_;
};

int main(){
    Matrix matrix(2, 2);
    matrix(1, 0) = 4;
    assert(matrix(1, 0) == 4);
    Matrix matrix1(2, 2);
    matrix1(1, 0) = 4;
    Matrix matrix2(2, 2);
    matrix2(1, 0) = 2;
    Matrix matrix3 = matrix1 + matrix2;
    assert(matrix3(1, 0) == 6);
}