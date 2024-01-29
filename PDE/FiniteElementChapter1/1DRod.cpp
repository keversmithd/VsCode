#include <iostream>
#include <GEmat.h>

void FormNodalFreedoms(GEmat& BoundaryConditionsPerNode, int& NumberOfEquations)
{
    //Numbers the nodes dependending on whether they are fixed or not, fixed elements are not numbered, and are skipped.
    int RowsOfNf = BoundaryConditionsPerNode.MATRIX_DIMENSION_Y;
    int ColumnsOfNf = BoundaryConditionsPerNode.MATRIX_DIMENSION_X;
    int m = 0;
    for(int j = 0; j < RowsOfNf; j++)
    {
        for(int i = 0; i < ColumnsOfNf; i++)
        {
            if(BoundaryConditionsPerNode(i,j) != 0)
            {
                m++;
                if(m>NumberOfEquations){NumberOfEquations = m;}
                BoundaryConditionsPerNode(i,j) = m;
            }
        }
    }
}
void FindSteeringVector(GEmat& ElementNodeNumbering, GEmat& NodalFreedomArray, GEmat& SteeringVector)
{

    //In 1 Dimension constructs 2d vector, of the indices of the nodes, 1,2,2,3, etc.

    //Steering Vector And And ElementNodeNumbering have the same dimensionality.
    int NumberOfNodesPerElement = ElementNodeNumbering.MATRIX_DIMENSION_Y;
    int NumberOfDegreesOfFreedom = NodalFreedomArray.MATRIX_DIMENSION_Y;

    int k = 0; 
    for(int i = 0; i < NumberOfNodesPerElement; i++)
    {
        k = ((i+1)*NumberOfDegreesOfFreedom); //Ending Index of the SteeringVector, and k-NumberOfDegreesOfFreedom+1 is the start
        //which includes the number of degrees of freedom, and as such will be an index to the end of this element.
        //in which k-NumberOfDegreesOfFreedom is the start because the span of an element will be NumberOfDegreesOfFreedom, ("PER ELEMENT")
    
        SteeringVector.equate({k-NumberOfDegreesOfFreedom+1, k}, NodalFreedomArray, {-1},{ElementNodeNumbering(i)+1});
    }
}
void ComputeSkylineProfile(GEmat& SkylineProfile, GEmat& SteeringVector)
{
    //Finds the greatest difference in equation number.
    int NumberOfFreedomsPerElement = SteeringVector.MATRIX_SIZE;
    int DifferenceOfEquationNumber;
    int k = 0;
    int CurrentWidthOfSkyline = 0;
    //In sense, depicts the widths of the elements as it where to be the width of each individual stiffness matrix.
    for(int i = 0; i < NumberOfFreedomsPerElement; i++) //For each degree of freedom of the element.
    {
        CurrentWidthOfSkyline = 1; //This number determines the width of the skyline.
        if(SteeringVector(i) != 0) //If the degree of freedom is fixed, then it is considered.
        {
            for(int j = 0; j < NumberOfFreedomsPerElement; j++) //For each pair of degrees of freedoms.
            {
                if(SteeringVector(j) != 0)
                {
                    DifferenceOfEquationNumber = SteeringVector(i)-SteeringVector(j)+1; //The difference between equation number.
                    if(DifferenceOfEquationNumber>CurrentWidthOfSkyline)
                    {
                        CurrentWidthOfSkyline = DifferenceOfEquationNumber;
                    }
                }
            }
            k = SteeringVector(i);
            if(CurrentWidthOfSkyline>SkylineProfile(k-1))
            {
                SkylineProfile(k-1)=CurrentWidthOfSkyline;
            }
        }
    }


}
void RodStiffness(GEmat& StiffnessMatrix, double EA, double L)
{
    double c = (L > 0) ? EA/L : 0;
    StiffnessMatrix[0] = 1.0*c;
    StiffnessMatrix[1] = -1.0*c;
    StiffnessMatrix[2] = -1.0*c;
    StiffnessMatrix[3] = 1.0*c; 
}
void ComputeSymmetricSkyline(GEmat& GlobalStiffnessMatrix, GEmat& StiffnessMatrix, GEmat& SteeringVector, GEmat& SkylineProfile)
{
    int DegreesOfFreedomPerElement = SteeringVector.MATRIX_DIMENSION_Y;
    int k = 0;
    int iw = 0;
    int ival = 0;
    //Indepdentantly places each stiffness matrix in place.
    
    for(int i = 0; i < DegreesOfFreedomPerElement; i++) 
    {
        k = SteeringVector(i); //If K = 0 here which it shouldn't isn't accounted for.
        if(k != 0) 
        {
            for(int j = 0; j < DegreesOfFreedomPerElement; j++) //Iterate through the steering vector again.
            {
                if(SteeringVector(j) != 0)
                {
                    iw = k - SteeringVector(j); 
                    if(iw >= 0)
                    {
                        ival = SkylineProfile(k-1)-iw; //The SkylineProfile should be the offset index given the current row.
                        GlobalStiffnessMatrix(ival-1)+=StiffnessMatrix(i,j);
                    }
                }
                
            }
        }
    }
}
void CholeskySkyline(GEmat& GlobalStiffnessMatrix, GEmat& SkylineProfile)
{

    //Symmetric Cholesky Decomposistion for Skyline Matrix, Also the size of the equations.
    int NumberOfEquations = SkylineProfile.MATRIX_DIMENSION_Y;
    //Meant to be iteratively calculating the lower triangular matrix L
    GlobalStiffnessMatrix(0) = sqrt(GlobalStiffnessMatrix(0)); //Unknown

    int IndexOffsetRow = 0;
    int IndexCurrentRowSkyline = 0;
    int IndexOffsetColumn = 0;
    int IndexPreviousColumnSkyline = 0;
    float X = 0.0f;

    //The skyline profile contains the offset for the correct location of the elements in the global stiffness matrix for the row.

    //Loop over the rows of the matrix, starting from the second row to the final row.
    for(int i = 1; i < NumberOfEquations; i++)
    {
        // Calculate the index offset for the current row in 'kv'
        IndexOffsetRow = SkylineProfile(i)-(i+1);
        //Calculate the starting index of the current row's skyline elements
        IndexCurrentRowSkyline = SkylineProfile(i-1)-IndexOffsetRow+1;

        //Loop over the columns within the skyline.
        for(int j = IndexCurrentRowSkyline; j <= i+1; j++) 
        {
            //Retrieve the current skyline element from the 'kv' array
            X = GlobalStiffnessMatrix(IndexOffsetRow+j-1);
            //Calculate the index offset for the current column in 'kv'
            IndexOffsetColumn = SkylineProfile(j-1)-j;

            // Check if the current column is not the first one
            if(j != 1)
            {
                IndexPreviousColumnSkyline = SkylineProfile(j-2)-IndexOffsetColumn+1; //Starting index of the skyline for the previous column

                //Ensure valid skyline elements for subtraction
                IndexPreviousColumnSkyline = std::max(IndexCurrentRowSkyline,IndexPreviousColumnSkyline);

                // If there are valid elements to subtract, perform the subtraction
                if(IndexPreviousColumnSkyline != j)
                {
                    //! Subtract scaled rows to update the value of 'x'
                    for(int k = IndexPreviousColumnSkyline; k <= j-1; k++)
                    {
                        X -= GlobalStiffnessMatrix(IndexOffsetRow+k-1)*GlobalStiffnessMatrix(IndexPreviousColumnSkyline+k-1);
                    }
                }
            }

            GlobalStiffnessMatrix(IndexOffsetRow+j-1) /= GlobalStiffnessMatrix(IndexOffsetColumn+j-1);


        }


        GlobalStiffnessMatrix(IndexOffsetRow+i) = sqrt(X);


    }
}
void CholeskyBackSub(GEmat& GlobalStiffnessMatrix, GEmat& Loads, GEmat& SkylineProfile)
{
    // !
    // ! This subroutine performs Cholesky forward and back-substitution
    // ! on a symmetric skyline global matrix.
    // !
    int NumberOfEquations = SkylineProfile.MATRIX_DIMENSION_Y;
    Loads(1)=Loads(1)/GlobalStiffnessMatrix(0);

    int IndexOffSetRow = 0;
    
    int IndexCurrentRowSkyline = 0;


    float x = 0;

    for(int i = 1; i < NumberOfEquations; i++)
    {
        IndexOffSetRow=SkylineProfile(i)-(i+1);//Offset

        IndexCurrentRowSkyline=SkylineProfile(i-1)-IndexOffSetRow+1;//Start

        x = Loads(i+1);

        if(IndexCurrentRowSkyline!=(i+1))
        {
            for(int j = IndexCurrentRowSkyline; j <= (i); j++)
            {
                x-=GlobalStiffnessMatrix(IndexOffSetRow+j-1)*Loads(j);
            }
        }

        Loads(i+1)=x/GlobalStiffnessMatrix(IndexOffSetRow+i);
    }


    int LastIndex = 0;
    for(int it=1; it < NumberOfEquations; it++)
    {
        LastIndex = NumberOfEquations+1-it;
        IndexOffSetRow = SkylineProfile(LastIndex-1)-LastIndex;
        x=Loads(LastIndex)/GlobalStiffnessMatrix(IndexOffSetRow+LastIndex-1);
        Loads(LastIndex) = x;
        IndexCurrentRowSkyline=SkylineProfile(LastIndex-2)-IndexOffSetRow+1;
        if(IndexCurrentRowSkyline!=LastIndex)
        {
            for(int j = IndexCurrentRowSkyline; j <= LastIndex-1; j++)
            {
                Loads(j)-=x*GlobalStiffnessMatrix(IndexOffSetRow+j-1);
            }
        }

    }
    Loads(1)=Loads(1)/GlobalStiffnessMatrix(0);


}


int main()
{
    int NumberOfElements = 4;
    int NumberOfNodes = NumberOfElements+1;
    int NumberOfDegreesOfFreedom = 1;
    int NumberOfNodesPerElement = 2;
    int NumberOfProperties = 1;
    int NumberOfFreedomsPerElement = 2;

    GEmat SteeringVector(NumberOfFreedomsPerElement); //An array of global equation numbers associated with a degree of freedom.
    GEmat ElementNodeNumbering(NumberOfNodesPerElement);
    GEmat NodalFreedomArray(NumberOfNodes,NumberOfDegreesOfFreedom);
    GEmat ElementMaterialType(NumberOfElements);
    GEmat ElementLengths(NumberOfElements);
    GEmat ElementProperties(1);
    GEmat ElementTypes(NumberOfElements);
    GEmat ElementDisplacements(NumberOfFreedomsPerElement);
    GEmat StiffnessMatrix(NumberOfFreedomsPerElement,NumberOfFreedomsPerElement);
    GEmat Action(NumberOfFreedomsPerElement);

    GEmat SteeringMatrix(NumberOfNodes,NumberOfNodesPerElement);

    ElementLengths = {0.25,0.25,0.25,0.25};
    NodalFreedomArray = {1,1,1,1,0};
    ElementTypes = {1,1,1,1};
    ElementProperties = {100000.0};

    int NumberOfEquations = 0;
    FormNodalFreedoms(NodalFreedomArray, NumberOfEquations); //Numbers the nodes based on whether they are restricted in the one degree of freedom.

    GEmat SkylineProfile(NumberOfEquations);

    for(int i = 0; i < NumberOfElements; i++)
    {
        ElementNodeNumbering = {i, i+1}; 
        FindSteeringVector(ElementNodeNumbering, NodalFreedomArray, SteeringVector);
        SteeringMatrix.equate({-1}, {i+1}, SteeringVector, {-1},{-1}); //Stores the steering column vectors into a single matrix
        ComputeSkylineProfile(SkylineProfile, SteeringVector);
    }

    //The skyline profile is a width-distance map of the global system in the indicie space.

    for(int i = 1; i < NumberOfEquations; i++)
    {
        SkylineProfile(i)+=SkylineProfile(i-1);
    }


    GEmat GlobalStiffnessMatrix(SkylineProfile(NumberOfEquations-1));
    GlobalStiffnessMatrix = 0;

    for(int i = 0; i < NumberOfElements; i++)
    {
        RodStiffness(StiffnessMatrix, ElementProperties(ElementTypes(i)-1), ElementLengths(i));
        SteeringVector.equate(SteeringMatrix,{-1},i+1);
        ComputeSymmetricSkyline(GlobalStiffnessMatrix, StiffnessMatrix, SteeringVector, SkylineProfile);
        
    }

    GEmat Loads(NumberOfEquations+1);
    Loads = {-0.625,-0.625,-1.25,-1.25,-1.25};

    int fixed_freeomds = 0;

    CholeskySkyline(GlobalStiffnessMatrix, SkylineProfile);
    CholeskyBackSub(GlobalStiffnessMatrix, Loads, SkylineProfile);

    //Displacement in the loads section.
    Loads.display();

    GEmat ElementLoad(NumberOfFreedomsPerElement);

    for(int i = 0; i < NumberOfElements; i++)
    {
        RodStiffness(StiffnessMatrix, ElementProperties(ElementTypes(i)-1), ElementLengths(i));
        StiffnessMatrix.display();

        SteeringVector.equate(SteeringMatrix,{-1},i+1);
        ElementLoad.equateIndex(Loads,SteeringVector);
        StiffnessMatrix.multiply(ElementLoad, Action);
        //Displays Actions on each rod.
        Action.display();
    }





    return -1;



}