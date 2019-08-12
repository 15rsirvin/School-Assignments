#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Prototype Funcitons
void printVector(vector<double> vect);
int jacobi( vector< vector<int>> A, vector <int> b, vector<double>& error, vector<double> correct );
int GaussSeidel( vector< vector<int>> A, vector <int> b,  vector<double>& error, vector<double> correct );
int SOR( vector< vector<int>> A, vector <int> b,  vector<double>& error, vector<double> correct );
string center(const string s, const int w);
string prd(const double x, const int decDigits, const int width);

int main()
{

    // Hard Coded Vector A, b, and the correct answer
    vector<vector<int>> A = {
        {7,1,-1,2},
        {1,8,0,-2},
        {-1,0,4,-1},
        {2,-2,-1,6}
    };
    vector<int> b = {3, -5, 4, -3};
    vector<double> correct = {1, -1, 1, -1};

    // Make Vector of Errors at each iteration to pass by reference into methods
    vector<double> errorJacobi;
    vector<double> errorGaussSeidel;
    vector<double> errorSOR;

    // Perform each iterative method
    jacobi ( A, b, errorJacobi, correct);
    cout << endl;
    GaussSeidel(A,b, errorGaussSeidel, correct);
    cout << endl;
    SOR(A,b, errorSOR, correct);
    cout << endl;

    // Add Fill(-1's) to Guassian and SOR vectors so they are of same length as Jacobi
    int diffG = errorJacobi.size() - errorGaussSeidel.size();
    int diffS = errorJacobi.size() - errorSOR.size();

    for(int i = 0; i < diffG; i++)
    {
        errorGaussSeidel.push_back(-1);
    }
    for(int i = 0; i < diffS; i++)
    {
        errorSOR.push_back(-1);
    }


    //Print results of error vectors
    cout << "Euclidean Norm of Error: (-1 is fill after completion)" << endl;
    cout << center("k",10)       << " | "
          << center("Jacobi",10)     << " | "
          << center("Guass",10)     << " | "
          << center("SOR",10) << "\n";

    for(int i = 0; i < errorJacobi.size(); i++)
    {
        cout  << prd(i+1,0,10)       << " | "
              << prd(errorJacobi.at(i),6,10)     << " | "
              << prd(errorGaussSeidel.at(i),6,10)     << " | " 
              << prd(errorSOR.at(i),6,10) << "\n";
    }
    



    return 0;
}

void printVector(vector<double> vect)
{
    cout << "{";
    int size = vect.size();
    for(int i = 0; i < size-1; i++)
    {
        cout << fixed << setprecision(4) <<  vect.at(i) << " ," << " ";
    }
    cout << fixed << setprecision(4) <<  vect.at(size-1) << "}";
    cout << '\n';
}

double normXminusY( vector<double> x, vector<double> y)
{
    double ans = 0;
    for(int i =0; i < x.size(); i++)
    {
        ans += abs(x.at(i) - y.at(i));
    }
    return ans;
}

int jacobi( vector< vector<int>> A, vector <int> b,vector<double>& error, vector<double> correct )
{
    int kmax = 100;
    double delta = .0000000001; // 1e-10
    double epsilon = .00005; // (1/2)e-4
    double diag, sum;

    // size of array A const
    const int n = 4;

    //Initialize New Vectors
    vector <double> x = {0,0,0,0};
    vector <double> y;

    cout << "Jacobi Iteration Table:" << endl;

    for(int k = 1; k <= kmax; k++)
    {
        y = x;

        for(int i = 0; i < n; i++)
        {
            sum = b.at(i);
            diag = A.at(i).at(i);

            if( abs(diag) < delta)
            {
                cout << "diagonal element too small" << endl;
                return 0;
            }

            for(int j = 0; j < n; j++)
            {
                if( j != i)
                {
                    sum -= ( A.at(i).at(j) * y.at(j));
                }
            }

            x.at(i) = (sum / diag);

        }

        cout << k << "\t";
        printVector(x);

        // Caclulate Euclidean Norm or Error
        error.push_back(normXminusY(x,correct));

        double currNorm = normXminusY(x,y);

        if( currNorm < epsilon)
        {
            return 0;
        }
    }
    cout << "Maximum iterations Reached";
    return 0;
}

int GaussSeidel( vector< vector<int>> A, vector <int> b, vector<double>& error, vector<double> correct )
{
    int kmax = 100;
    double delta = .0000000001; // 1e-10
    double epsilon = .00005; // (1/2)e-4
    double diag, sum;

    // size of array A const
    const int n = 4;

    //Initialize New Vectors
    vector <double> x = {0,0,0,0};
    vector <double> y;

    cout << "Gauss-Seidel Iteration Table:" << endl;

    for(int k = 1; k <= kmax; k++)
    {
        y = x;

        for(int i = 0; i < n; i++)
        {
            sum = b.at(i);
            diag = A.at(i).at(i);

            if( abs(diag) < delta)
            {
                cout << "diagonal element too small" << endl;
                return 0;
            }

            // Changes From Jacobi Begin Here
            for(int j = 0; j <= i-1; j++)
            {
                sum -= (A.at(i).at(j) * x.at(j));
            }

            for( int j = i+1; j < n; j++)
            {
                sum -= (A.at(i).at(j) * x.at(j));           
            }
            // End of Changes

            x.at(i) = (sum / diag);

        }

        cout << k << "\t";
        printVector(x);

        // Caclulate Euclidean Norm or Error
        error.push_back(normXminusY(x,correct));

        double currNorm = normXminusY(x,y);

        if( currNorm < epsilon)
        {
            return 0;
        }
    }
    cout << "Maximum iterations Reached";
    return 0;
}

int SOR( vector< vector<int>> A, vector <int> b, vector<double>& error, vector<double> correct )
{
    int kmax = 100;
    double delta = .0000000001; // 1e-10
    double epsilon = .00005; // (1/2)e-4
    double diag, sum;
    double omega = 1.12;

    // size of array A const
    const int n = 4;

    //Initialize New Vectors
    vector <double> x = {0,0,0,0};
    vector <double> y;

    cout << "SOR Iteration Table:" << endl;

    for(int k = 1; k <= kmax; k++)
    {
        y = x;

        for(int i = 0; i < n; i++)
        {
            sum = b.at(i);
            diag = A.at(i).at(i);

            if( abs(diag) < delta)
            {
                cout << "diagonal element too small" << endl;
                return 0;
            }

            // Changes From Jacobi Begin Here
            for(int j = 0; j <= i-1; j++)
            {
                sum -= (A.at(i).at(j) * x.at(j));
            }

            for( int j = i+1; j < n; j++)
            {
                sum -= (A.at(i).at(j) * x.at(j));           
            }
            // End of Changes

            x.at(i) = (sum / diag);
            x.at(i) = ( (omega * x.at(i)) + ( (1 - omega) * y.at(i)) );

        }

        cout << k << "\t";
        printVector(x);

        // Caclulate Euclidean Norm or Error
        error.push_back(normXminusY(x,correct));

        double currNorm = normXminusY(x,y);

        if( currNorm < epsilon)
        {
            return 0;
        }
    }
    cout << "Maximum iterations Reached";
    return 0;
}

// Found code on Stack OverFlow to Help With formatting Output, not mine.
// Link: https://stackoverflow.com/questions/14765155/how-can-i-easily-format-my-data-table-in-c
string center(const string s, const int w) {
    stringstream ss, spaces;
    int padding = w - s.size();                 // count excess room to pad
    for(int i=0; i<padding/2; ++i)
        spaces << " ";
    ss << spaces.str() << s << spaces.str();    // format with padding
    if(padding>0 && padding%2!=0)               // if odd #, add 1 space
        ss << " ";
    return ss.str();
}

string prd(const double x, const int decDigits, const int width) {
    stringstream ss;
    ss << fixed << right;
    ss.fill(' ');        // fill space around displayed #
    ss.width(width);     // set  width around displayed #
    ss.precision(decDigits); // set # places after decimal
    ss << x;
    return ss.str();
}


