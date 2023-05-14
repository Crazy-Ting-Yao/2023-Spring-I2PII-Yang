#include <iostream>
class Matrix
{
    friend std::ostream &operator<<(std::ostream &, const Matrix &);
    friend std::istream &operator>>(std::istream &, Matrix &);
public:
    Matrix(int s = 5) //default constructor
        :size(s)
    {
        buf = new int[size*size];
        matrix = new int* [size];

        for(int i=0; i<size; i++)
            matrix[i] = &buf[i*size];

        for(int i=0; i<size; i++)
            for(int j=0; j<size; j++)
                matrix[i][j] = 0;
    }
    Matrix(const Matrix &);// copy constructor

    ~Matrix() {
        delete [] matrix;
        delete [] buf;
    }

    Matrix &operator=(const Matrix &a) {
        if(a.size!=size) {
            delete [] matrix;
            delete [] buf;

            size = a.size;
            buf = new int[size*size];
            matrix = new int* [size];

            for(int i=0; i<size; i++)
                matrix[i] = &buf[i*size];
        }

        for(int i=0; i<size; i++)
            for(int j=0; j<size; j++)
                matrix[i][j] = a.matrix[i][j];

        return *this;
    }

    Matrix &clockwise90();
private:
    int **matrix;
    int *buf;   // 2D matrix stored in 1D raster scan order
    int size;
}; //end class Matrix



using namespace std;

int main()
{
    int matrix_size;
    cin>>matrix_size;

    Matrix a(matrix_size);
    cin>>a;

    cout<<endl;
    cout<<a.clockwise90().clockwise90()<<endl;
    cout<<a<<endl;

    return 0;
} // end main
std::ostream &operator<<(std::ostream & output, const Matrix & M){
    for(int i=0;i<M.size;i++){
        for(int j=0;j<M.size-1;j++)
            output<<M.matrix[i][j]<<" ";
        output<<M.matrix[i][M.size-1]<<"\n";
    }
    return output;
}
std::istream &operator>>(std::istream &input, Matrix & M){
    for(int i=0;i<M.size*M.size;i++)
        input>>M.buf[i];
    return input;    
}
Matrix::Matrix(const Matrix & m){
    size = m.size;
    buf = new int[size*size];
    matrix = new int* [size];

    for(int i=0; i<size; i++)
        matrix[i] = &buf[i*size];
    
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
            matrix[i][j] = m.matrix[i][j];
}

Matrix& Matrix::clockwise90(){
    Matrix n(*this);
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            matrix[i][j] = n.matrix[j][size-1-i];
    return *this;
}