#include <iostream>
using namespace std;
const int mod = 1000000009;

class Matrix {
   private:
    int n;
    long long** matrix;

   public:
    // The Default Constructor
    Matrix() {
        n = 0;
        matrix = nullptr;
    }
    // TODO: The Destructor
    ~Matrix();

    // TODO: The Customize Constructor
    Matrix(int n);

    // TODO: Copy contructor
    // Will be trigger when the following condition:
    // Matrix m = ref; -> Call copy contructor to copy from 'ref' to 'm'
    Matrix(const Matrix& ref);

    // TODO: copy assignment,
    // Will be trigger when the following condition:
    // Matrix a;
    // a = ref; -> Call copy assignment to copy from 'ref' to 'a'
    Matrix& operator=(const Matrix& ref);

    // TODO: Overload operator()
    // This operator allow the following code
    // This operator can help you access the data easily
    // 1. cout << m(1, 2) << endl; -> Shorthand of `cout << m.matrix[1, 2] <<
    // endl;`
    // 2. m(1, 2) = 100; -> Shorthand of `m.matrix[1, 2] = 100`
    long long& operator()(const int& row, const int& column) const;

    // Utilities functions
    // TODO: Make the matrix identity matrix
    void toIdentity();
    void toZero() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) matrix[i][j] = 0;
        }
    }

    // TODO: Overload operator *
    Matrix operator*(const Matrix& rhs) const;

    // TODO: Return the matrix power of 'k'
    Matrix power(int k) const;

    friend ostream& operator<<(ostream& os, const Matrix& matrix) {
        for (int i = 0; i < matrix.n; i++) {
            for (int j = 0; j < matrix.n; j++) os << matrix(i, j) << ' ';
            os << endl;
        }
        return os;
    }
};

// TODO: Construct a matrix
Matrix constructMatrix(int n);
/*
 * HINT: To solve this problem
 * First, assuming there is an array containing the first F(N, 1) ~ F(N, N)
 * to compute F(N, N + 1), we can construct a matrix that multiply the array(N*1
 * matrix) from F(N, 1) ~ F(N, N) to F(N, 2), F(N, N + 1), so to compute F(N, N
 * + 2), we can just multiply the array again.
 *
 * For example, if N = 2, then
 * [ 0, 1 ]   [ 1 ]   [ 1 ]       [ 0, 1 ]   [ 1 ]   [ 2 ]
 * [      ] * [   ] = [   ], then [      ] * [   ] = [   ], ....
 * [ 1, 1 ]   [ 1 ]   [ 2 ]       [ 1, 1 ]   [ 2 ]   [ 3 ]
 */

int main() {
    int n, m;
    cin >> n >> m;
    if (m <= n) {
        cout << 1 << endl;
    } else {
        Matrix base = constructMatrix(n);
        base = base.power(m - n);
        int ans = 0;
        for (int i = 0; i < n; i++) ans = (ans + base(n - 1, i)) % mod;
        cout << ans << endl;
    }
    return 0;
}

Matrix::Matrix(int n){
    matrix = new long long*[n];
    for(int i=0;i<n;i++){
        matrix[i] = new long long[n];
    }
    this->n = n;
}

void Matrix::toIdentity(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) matrix[i][j] = 1;
            else matrix[i][j] = 0;
        }
    }
}

Matrix& Matrix::operator=(const Matrix& ref){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            matrix[i][j] = ref(i,j);
        }
    }
    return *this;
}

long long& Matrix::operator()(const int& row, const int& column) const{
    return matrix[row][column];
}

Matrix constructMatrix(int n){
    Matrix ret(n);
    ret.toZero();
    for(int i=0;i<n-1;i++) ret(i,i+1) = 1;
    for(int i=0;i<n;i++) ret(n-1,i) = 1;
    return ret;
}

Matrix::~Matrix(){
    for(int i=0;i<n;i++) delete [] matrix[i];
    delete [] matrix;
}

Matrix Matrix::power(int k) const{
    Matrix ret(n);
    Matrix temp(n);
    temp = *this;
    ret.toIdentity();
    int tmpn = k;
    for(;tmpn;tmpn>>=1,temp = temp*temp){
        if(tmpn&1){
            ret = ret*temp;
        }
    }
    return ret;
}

Matrix Matrix::operator*(const Matrix& rhs) const{
    Matrix ret(n);
    ret.toZero();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int l=0;l<n;l++){
                ret(i,j)+=(matrix[i][l]*rhs(l,j));
                ret(i,j)%=mod;
            }
        }
    }
    return ret;
}