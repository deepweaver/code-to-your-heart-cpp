#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
vector <double> sigmoid (const vector <double>& m1);
vector <double> sigmoid_d (const vector <double>& m1);
vector <double> operator+(const vector <double>& m1, const vector <double>& m2);
vector <double> operator-(const vector <double>& m1, const vector <double>& m2);
vector <double> operator*(const vector <double>& m1, const vector <double>& m2);
vector <double> transpose (double *m, const int C, const int R);
vector <double> dot (const vector <double>& m1, const vector <double>& m2, const int m1_rows, const int m1_columns, const int m2_columns);
void print ( const vector <double>& m, int n_rows, int n_columns );
vector<double> X {
    5.1, 3.5, 1.4, 0.2, 
    4.9, 3.0, 1.4, 0.2, 
    6.2, 3.4, 5.4, 2.3, 
    5.9, 3.0, 5.1, 1.8
};
vector<double> y { 0, 0, 1, 1 };
vector<double> W { 0.5, 0.5, 0.5, 0.5 };

int main() 
{
    for (int i = 0; i != 50; ++i) {
        
        vector<double> pred = sigmoid(dot(X, W, 4, 4, 1 ));
        vector<double> pred_error = y - pred;        
        vector<double> pred_delta = pred_error * sigmoid_d(pred);        
        vector<double> W_delta = dot(transpose( &X[0], 4, 4 ), pred_delta, 4, 4, 1);        
        W = W + W_delta;
        
        if (i == 49){
            print ( pred, 4, 1 );
        };
    };

    return 0;
}





vector <double> sigmoid_d (const vector <double>& m1) {
    const unsigned long VECTOR_SIZE = m1.size();
    vector <double> output (VECTOR_SIZE);
    for( unsigned i = 0; i != VECTOR_SIZE; ++i )
        output[ i ] = m1[ i ] * (1 - m1[ i ]);
    
    return output;
}

vector <double> sigmoid (const vector <double>& m1) {
    const unsigned long VECTOR_SIZE = m1.size();
    vector <double> output (VECTOR_SIZE);
    for( unsigned i = 0; i != VECTOR_SIZE; ++i ) 
        output[ i ] = 1 / (1 + exp(-m1[ i ]));
    
    return output;
}

vector <double> operator+(const vector <double>& m1, const vector <double>& m2){
    const unsigned long VECTOR_SIZE = m1.size();
    vector <double> sum (VECTOR_SIZE);
    for (unsigned i = 0; i != VECTOR_SIZE; ++i)
        sum[i] = m1[i] + m2[i];
    
    return sum;
}

vector <double> operator-(const vector <double>& m1, const vector <double>& m2){
    const unsigned long VECTOR_SIZE = m1.size();
    vector <double> difference (VECTOR_SIZE);
    for (unsigned i = 0; i != VECTOR_SIZE; ++i)
        difference[i] = m1[i] - m2[i];
    
    return difference;
}

vector <double> operator*(const vector <double>& m1, const vector <double>& m2){
    const unsigned long VECTOR_SIZE = m1.size();
    vector <double> product (VECTOR_SIZE);
    for (unsigned i = 0; i != VECTOR_SIZE; ++i)
        product[i] = m1[i] * m2[i];

    return product;
}

vector <double> transpose (double *m, const int C, const int R) {
    vector <double> mT (C*R);
    for(unsigned n = 0; n != C*R; n++) {
        unsigned i = n/C;
        unsigned j = n%C;
        mT[n] = m[R*j + i];
    }
    
    return mT;
}

vector <double> dot (const vector <double>& m1, const vector <double>& m2, const int m1_rows, const int m1_columns, const int m2_columns) {
    vector <double> output (m1_rows*m2_columns);
    for( int row = 0; row != m1_rows; ++row ) {
        for( int col = 0; col != m2_columns; ++col ) {
            output[ row * m2_columns + col ] = 0;
            for( int k = 0; k != m1_columns; ++k )
                output[ row * m2_columns + col ] += m1[ row * m1_columns + k ] * m2[ k * m2_columns + col ];
        }
    }
    
    return output;
}

void print ( const vector <double>& m, int n_rows, int n_columns ) {
    for( int i = 0; i != n_rows; ++i ) {
        for( int j = 0; j != n_columns; ++j ) {
            cout << m[ i * n_columns + j ] << " ";
        }
        cout << '\n';
    }
    cout << endl;
}
