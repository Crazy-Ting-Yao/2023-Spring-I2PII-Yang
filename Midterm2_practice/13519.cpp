#include <iostream>
#include <string>

#define maxsize 10000
class INT {
    public:
        INT();
        void mulby10();
        INT operator=(INT);
        INT operator+(INT);
        INT operator*(INT);
        friend std::istream &operator>>(std::istream &, INT &);
        friend std::ostream &operator<<(std::ostream &, INT);
    private:
        char data[maxsize + 1];
        int len;
};
using namespace std;

////////////////////////////
//  Implementation of INT //
////////////////////////////
int max(int a, int b) {
    return a > b ? a : b;
}

// construct the INT class
INT::INT(void) {
    this->len = 1;
    this->data[0] = 0;
}

INT INT::operator+ (INT b) {
    INT re;
    // Calculate the length of their sum
    int lena = this->len;
    int lenb = b.len;
    int len = max(lena, lenb);
    re.data[len] = 0;
    // perform addition
    for (int i = 0; i < len; i++) {
        if (i < lena)
            re.data[i] = this->data[i];
        else
            re.data[i] = 0;
        if (i < lenb)
            re.data[i] += b.data[i];
    }
    // check if larger than 9 and carry
    for (int i = 0; i < len; i++) {
        re.data[i + 1] += re.data[i] / 10;
        re.data[i] %= 10;
    }
    if (re.data[len] != 0)
        re.len = len + 1;
    else
        re.len = len;
    return re;
}

INT INT::operator= (INT b) {
    this->len = b.len;
    for (int i = 0; i < b.len; i++)
        this->data[i] = b.data[i];
    return *this;
}

std::istream &operator>>(std::istream &a, INT &b) {
    std::string s;
    a >> s;
    b.len = s.length();
    for (int i = 0; i < b.len; i++) {
        // reverse the string array
        // e.g. string = "123456"
        //      data[0]= 6
        //      data[1]= 5
        //      data[2]= 4
        // convert '0' to 0 ('0' = 48 by ASCII code)
        //         '1' to 1 ('1' = 49 by ASCII code)
        b.data[i] = s.at(b.len - i - 1) - '0';
    }
    return a;
}

std::ostream &operator<<(std::ostream &a, INT b) {
    for (int i = 0; i < b.len; i++) {
        // reverse the sequence again
        a << (char)(b.data[b.len - i - 1] + '0');
    }
    return a;
}

void INT::mulby10() {
    for (int i = this->len; i; i--)
        this->data[i] = this->data[i-1];
    this->data[0] = 0;
    this->len++;
}
////////////////////////////
//  Implementation of INT //
////////////////////////////

int main() {
    INT a, b, c;
    cin >> a >> b;
    c = a * b;
    cout << c << endl;
    return 0;
}


INT INT::operator*(INT b){
    INT res;
    for(int i=0;i<len;i++){
        for(int j=0;j<data[i];j++){
            res = res + b;
        }
        b.mulby10();
    }
    return res;
}