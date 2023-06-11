#include <iostream>
#include <string>
#include <vector>



void inverse2x2(double* A, double* invA) {
    double detA = A[0] * A[3] - A[1] * A[2];

    // Check if the matrix is invertible
    if (detA != 0) {
        double invDetA = 1.0 / detA;

        // Calculate the inverse matrix
        invA[0] = A[3] * invDetA;
        invA[1] = -A[1] * invDetA;
        invA[2] = -A[2] * invDetA;
        invA[3] = A[0] * invDetA;
    } else {
       invA[0] = A[0];
       invA[1] = A[1];
       invA[2] = A[2];
       invA[3] = A[3];
    }
}

void vecmul2(double* A, double* x, double* result)
{
    result[0] = (A[0] * x[0]) + (A[1] * x[1]);
    result[1] = (A[2] * x[0]) + (A[3] * x[1]);

}

void vecadd2(double* x,  double* y, double* result)
{
    result[0] = x[0] + y[0];
    result[1] = x[1] + y[1];
}

void mul4(double*  A, double K, double* result)
{
    result[0] = A[0] * K;
    result[1] = A[1] * K;
    result[2] = A[2] * K;
    result[3] = A[3] * K;
}

int main()
{
    std::cout << "Rod Stiffnes Matrix" << std::endl;

    std::cout << "Rod Description" << std::endl;

    double L = 1;
    double E = 0.5;
    double A = 0.1;
    double F = 70000;


    
    double Stiffness[4] = {1, -1, -1, 1};
    double IL[4];
    

    double ConstantStiffness[4];
    double Force[2] = {-(F * (L/2)), -(F * (L/2))};
    double U[2] = {3500,3500};
    double UTemp[2];
    double R[2];
    
    

    
    mul4(Stiffness, ((-E*A)/L), ConstantStiffness);
    vecmul2(ConstantStiffness, U, UTemp);

    //Algebra Solution
    //-EA [1/L, -1/L; -1/L, 1/L] {u1, u2} + F {L/2, L/2} = {0, 0}
    // (-EA/L) * u1 + (EA/L) * u2 + (F * L/2) = 0
    // (EA/L) * u2 - (EA/L) * u1 + (F * L/2) = 0
    // (EA/L) * (u2 - u1) + (F * L/2) = 0
    // (EA/L) * (u1 - u2) + (F * L/2) = 0
    // (EA/L) * (u2 - u1) + (F * L/2) = 0
    // (EA/L) * (u2 - u1) = -(F * L/2)
    // u2 - u1 = -((F * L^2)/(2 * EA))
    // u2 = u1 - ((F * L^2)/(2 * EA))
    // u2 = u1 - ((F * L^2)/(2 * EA))

    //add boundary conditons
    // /u1 = u1_0 at node 1
    // u2 = u2_0 at node 2



    //vecadd2(UTemp, Force, R);

    // while(CurrentAproximation > LeastApproximation)
    // {

    // }



    printf("here");






    





    


    





}