#include <iostream>
#include <vector>


int NN = 3; // define the number of input matrix dimension


// to see the matrix result on the terminal
void letMeSee(std::vector<std::vector<double>> K)
{
    for(std::vector<double> f:K)
    {
        for(double k:f)
            std::cout<<k<<"  ";
        std::cout<<std::endl;
    }
}

//get the cofactor matrix
std::vector<std::vector<double>> getCofactor(std::vector<std::vector<double>> A, int p, int q, int n)
{
    int i = 0, j = 0;
    std::vector<std::vector<double>> temp(A[0].size(), std::vector<double>(A.size()));
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];

                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }

    return temp;
}

//get the determinant
int determinant(std::vector<std::vector<double>> A, int n)
{
    int D = 0;

    if (n == 1)
        return A[0][0];

    std::vector<std::vector<double>> temp(A[0].size(), std::vector<double>(A.size())); // To store cofactors

    int sign = 1;

    for (int f = 0; f < n; f++)
    {
        temp = getCofactor(A , 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);
        sign = -sign;
    }

    return D;
}

//get the adjoint matrix
void adjoint(std::vector<std::vector<double>> A,std::vector<std::vector<double>> &adj)
{
    if (A.size() == 1)
    {
        adj[0][0] = 1;
        return;
    }

    int sign = 1;
    std::vector<std::vector<double>> temp(A[0].size(), std::vector<double>(A.size()));

    for (int i=0; i<NN; i++)
    {
        for (int j=0; j<(int)A[0].size(); j++)
        {
            temp = getCofactor(A , i,j,NN);


            sign = ((i+j)%2==0)? 1: -1;

            adj[j][i] = (sign)*(determinant(temp, NN-1));
        }
    }
}

//get the inverse matrix
bool inverse(std::vector<std::vector<double>> A, std::vector<std::vector<double>> &inverse)
{
    int det = determinant(A, NN);
    if (det == 0)
    {
        std::cout << "Determinant is 0 !!!"<<std::endl;
        return false;
    }
    std::cout<<det<<std::endl;

    std::vector<std::vector<double>> adj(A[0].size(), std::vector<double>(A.size()));
    adjoint(A, adj);

    for (int i=0; i<NN; i++)
        for (int j=0; j<NN; j++)
            inverse[i][j] = adj[i][j]/float(det);

    return true;
}

//get the transpose matrix
std::vector<std::vector<double>> getTranspose(std::vector<std::vector<double>> A)
{

    if(A.size()<0)
    {
        return A;

        std::cout<<"Error in getting transpose: Input sized is 0 !!!"<< std::endl;
    }

    std::vector<std::vector<double>> temp (A[0].size(), std::vector<double>(A.size()));


    for(int i=0; i<(int)A.size(); i++)
    {
        for(int j=0; j<(int)A[0].size(); j++)
        {
            temp[j][i] = A[i][j];
        }

    }
    return temp;

}

//multiply vectors
std::vector<std::vector<double>> multiplyVectors(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B)
{
    if(A.size()<0 || B.size()<0)
    {
        std::cout<<"Input error in multiplication: Size is 0 " <<std::endl;
        return A;
    }

    if(A[0].size() != B.size())
    {
        std::cout<<"Input error in multiplication:Size of vectors should be (m x n) and (n x p) " <<std::endl;
        return A;
    }
    int n = B.size();

    std::vector<std::vector<double>> result(A.size(), std::vector<double>(B[0].size()));

    for(int i=0; i<(int)result.size(); i++)
    {
        for(int j=0; j<(int)result[0].size(); j++)
        {
            double temp = 0;
            for(int x=0; x<n; x++)
            {
                temp += A[i][x] * B[x][j];
            }

            result[i][j] = temp;

        }
    }



    return result;


}


int main()
{
    std::vector<std::vector<double>> A = {
        {700,330,663 },
        {270,208,312 },
        {122,555,444 }

    };
    std::vector<std::vector<double>> inv(A[0].size(), std::vector<double>(A.size()));
    std::vector<std::vector<double>> transposeA, mult;


    //couple of example about usage the functions
    inverse(A,inv);
    letMeSee(inv);

    transposeA = getTranspose(A);
    letMeSee(transposeA);

    mult = multiplyVectors(transposeA,A);
    letMeSee(mult);



    return 0;
}
