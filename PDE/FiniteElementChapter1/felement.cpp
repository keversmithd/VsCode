#include <iostream>
#include <GEmat.h>

void FormNodalFreedoms(GEmat& BoundaryConditionsPerNode)
{
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

    //This will run through the element node numbering, and set the steering vector to the corresponding element node index.
    int k = 0; 
    for(int i = 0; i < NumberOfNodesPerElement; i++)
    {
        k = ((i+1)*NumberOfDegreesOfFreedom); //Ending Index of the SteeringVector, and k-NumberOfDegreesOfFreedom+1 is the start
    
        SteeringVector.equate({k-NumberOfDegreesOfFreedom+1, k}, NodalFreedomArray, {-1},{ElementNodeNumbering(i)+1});
    }
}
void ComputeSkylineProfile(GEmat& GlobalDiagonalIndices, GEmat& SteeringVector)
{
    int NumberOfNodesPerElement = SteeringVector.MATRIX_SIZE;
    int im;
    int k = 0;
    for(int i = 0; i < NumberOfNodesPerElement; i++)
    {
        int iwp1 = 1;
        if(SteeringVector(i) != 0)
        {
            for(int j = 0; j < NumberOfNodesPerElement; j++)
            {
                if(SteeringVector(i) != 0)
                {
                    im = SteeringVector(i)-SteeringVector(j)+1;
                    if(im>iwp1)
                    {
                        iwp1 = im;
                    }

                }
            }
            k = SteeringVector(i);
            if(iwp1>GlobalDiagonalIndices(k))
            {
                GlobalDiagonalIndices(k)=iwp1;
            }
        }
    }


}


int main()
{
    int NumberOfElements = 4;
    int NumberOfNodes = NumberOfElements+1;
    int NumberOfDegreesOfFreedom = 1;
    int NumberOfNodesPerElement = 2;
    int NumberOfProperties = 1;
    int NumberOfFreedomsPerElement = 2;

    GEmat SteeringVector(NumberOfNodesPerElement);
    GEmat ElementNodeNumbering(NumberOfNodesPerElement);
    GEmat NodalFreedomArray(NumberOfNodes,NumberOfDegreesOfFreedom);
    GEmat ElementMaterialType(NumberOfElements);
    GEmat ElementLength(NumberOfElements);
    GEmat ElementDisplacements(NumberOfFreedomsPerElement);
    GEmat StiffnessMatrix(NumberOfFreedomsPerElement,NumberOfFreedomsPerElement);
    GEmat Action(NumberOfFreedomsPerElement);

    GEmat NodeIndices(NumberOfNodes,NumberOfNodesPerElement);

    NodalFreedomArray = {1,1,1,1,0};

    FormNodalFreedoms(NodalFreedomArray); //Numbers the nodes based on whether they are restricted in the one degree of freedom.

    int NumberOfEquations = NodalFreedomArray.max();

    GEmat GlobalDiagonalIndices(NumberOfEquations);

    for(int i = 0; i < NumberOfElements; i++)
    {
        ElementNodeNumbering = {i, i+1}; 
        FindSteeringVector(ElementNodeNumbering, NodalFreedomArray, SteeringVector);
        NodeIndices.equate({-1}, {i+1}, SteeringVector, {-1},{-1}); //Stores the steering column vectors into a single matrix
        ComputeSkylineProfile(GlobalDiagonalIndices, SteeringVector);
    }


}