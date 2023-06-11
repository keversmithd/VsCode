#include <iostream>
#include <string>
#include <vector>

struct vec2
{
    double x;
    double y;
};

void ExplicitFiniteDifferenceOneDimensionalExample()
{
    int NumberOfSpacialOneDimensionalNodes = 5;
    float DeltaX = 1/(float)NumberOfSpacialOneDimensionalNodes;
    float DeltaT = 0.08; //Time Step Chosen by User.

    float TimeBoundaryConditionStart = 20.0; //At Time Zero.
    float SpaceBoundaryConditionStart = 100.0; //At Space Zero.
    float SpaceBoundaryConditionEnd = 25.0; //At Space Zero.

    float Epsilon = DeltaT/(DeltaX*DeltaX);

    std::vector<float> StoredDifferenceResults;

    int timeIndex = 0;
    for(float time = 0.0; time < 1.0; time += DeltaT)
    {
        int nodalIndex = 0;
        for(float space = 0.0; space < 1.0; space += DeltaX)
        {
            if(nodalIndex == 0)
            {
                if(time < 0.5)
                    StoredDifferenceResults.push_back(SpaceBoundaryConditionStart);
                else
                    StoredDifferenceResults.push_back(0);
            }else
            if(nodalIndex == (NumberOfSpacialOneDimensionalNodes-1))
            {
                if(time < 0.5)
                    StoredDifferenceResults.push_back(SpaceBoundaryConditionEnd);
                else
                    StoredDifferenceResults.push_back(0);
            }else
            if(timeIndex == 0)
            {

                    StoredDifferenceResults.push_back(20);
            }else
            {

                //Time is not at 0.0

                int PreviousTimeCoordinate = timeIndex-1;
                int PreviousNodalIndex = nodalIndex;

                int CurrentIndex = (PreviousNodalIndex)+(PreviousTimeCoordinate*NumberOfSpacialOneDimensionalNodes);

                int NextSpacialIndex = CurrentIndex+1;
                int PreviousSpacialIndex = CurrentIndex-1;

                //Second Derivative With Respect to Space

                float NextSpacialValue = StoredDifferenceResults[NextSpacialIndex];
                float PreviousSpacialValue = StoredDifferenceResults[PreviousSpacialIndex];
                float CurrentValue = StoredDifferenceResults[CurrentIndex];

                float TimeStepValue = CurrentValue + (NextSpacialValue-(2*CurrentValue))+PreviousSpacialValue;
                TimeStepValue /= (DeltaX*DeltaX);


                StoredDifferenceResults.push_back(TimeStepValue);
            }

            nodalIndex++;

        }

        timeIndex++;
    }


    std::string command = "datatemp.txt";
    FILE* pipe = fopen(command.c_str(), "w");
    if(pipe == nullptr)
    {

    }else
    {   
        fprintf(pipe, "nodes: %d\n", NumberOfSpacialOneDimensionalNodes);
        for (int i = 0; i < StoredDifferenceResults.size(); i++) {
            float item = StoredDifferenceResults[i];
            fprintf(pipe, "%f\n", item);  // Adjust the format specifier based on your vector data type

        }
    }
    fclose(pipe);
    system("python movieizedata.py");
}


void ExplicitFiniteDifferenceOneDimensionBook()
{
    int NumberOfSpacialOneDimensionalNodes = 20;
    float DeltaX = 1/(float)NumberOfSpacialOneDimensionalNodes;
    float DeltaT = 0.1; //Time Step Chosen by User.

    float TimeBoundaryConditionStart = 0.0; //At Time Zero.
    float SpaceBoundaryConditionStart = 0; //At Space Zero.
    float SpaceBoundaryConditionEnd = 0; //At Space Zero.

    bool pushedLeft = false;
    
    bool pushedRight = false;
    float Epsilon = DeltaT/(DeltaX*DeltaX);

    std::vector<float> StoredDifferenceResults;

    int timeIndex = 0;
    for(float time = 0.0; time < 1.0; time += DeltaT)
    {
        int nodalIndex = 0;
        for(float space = 0.0; space < 1.0; space += DeltaX)
        {
            if(nodalIndex == 0)
            {
                StoredDifferenceResults.push_back(SpaceBoundaryConditionStart);
            }else
            if(nodalIndex == (NumberOfSpacialOneDimensionalNodes-1))
            {
                StoredDifferenceResults.push_back(SpaceBoundaryConditionEnd);
            }else
            if(timeIndex == 0)
            {
                // if(space <= (1/2))
                // {
                //     StoredDifferenceResults.push_back(2*space);
                // }else
                // {
                //     StoredDifferenceResults.push_back(2-(2*space));
                // }
                StoredDifferenceResults.push_back(20);
                
            }else
            {

                //Time is not at 0.0

                int PreviousTimeCoordinate = timeIndex-1;
                int PreviousNodalIndex = nodalIndex;
                int CurrentIndex = (PreviousNodalIndex)+(PreviousTimeCoordinate*NumberOfSpacialOneDimensionalNodes);
                int NextSpacialIndex = CurrentIndex+1;
                int PreviousSpacialIndex = CurrentIndex-1;

                //Second Derivative With Respect to Space

                float NextSpacialValue = StoredDifferenceResults[NextSpacialIndex];
                float PreviousSpacialValue = StoredDifferenceResults[PreviousSpacialIndex];
                float CurrentValue = StoredDifferenceResults[CurrentIndex];

                float TimeStepValue = CurrentValue + (NextSpacialValue-(2*CurrentValue))+PreviousSpacialValue;
                TimeStepValue /= Epsilon;

                StoredDifferenceResults.push_back(TimeStepValue);
            }

            nodalIndex++;

        }

        timeIndex++;
    }

    std::string command = "datatemp.txt";
    FILE* pipe = fopen(command.c_str(), "w");
    if(pipe == nullptr)
    {

    }else
    {   
        fprintf(pipe, "nodes: %d\n", NumberOfSpacialOneDimensionalNodes);
        for (int i = 0; i < StoredDifferenceResults.size(); i++) {
            float item = StoredDifferenceResults[i];
            fprintf(pipe, "%f\n", item);  // Adjust the format specifier based on your vector data type

        }
    }
    fclose(pipe);
    system("python movieizedata.py");
}

void AnotherAttemptFiniteDifferenceOneDimension()
{
    vec2 R = {0,1};
    double J = 20;
    double tF = 1.0;
    double dt = 0.012;
    double dx = 1.0/J;


    double t0 = 0.0;
    double x0 = 0;
    double x1 = 0;

    
    std::vector<float> resultmap(20*static_cast<int>(tF / dt));

    double epsilon = (dt)/(dx*dx);

    int timestep = 0;
    int spacestep = 0;
    for(double n = 0; n < tF; n+=dt)
    {
        spacestep = 0;
        for(double j = R.x; j < R.y; j += dx)
        {
            if(spacestep == 0)
            {
                resultmap.push_back(x0);
            }else if(spacestep == J)
            {
                resultmap.push_back(x1);
            }else
            if(timestep == 0)
            {
                if(j < 0.5)
                {
                    resultmap.push_back(2*spacestep);
                }else
                {
                    resultmap.push_back(2-(2*spacestep));
                }
            }else
            {
                int previousTimeIndex = spacestep + ((timestep-1)*J);
                int rightTimeIndex = previousTimeIndex+1;
                int leftTimeIndex = previousTimeIndex-1;

                double currentValue = resultmap[previousTimeIndex];
                double leftValue = resultmap[leftTimeIndex];
                double rightValue = resultmap[rightTimeIndex];

                
                double approx = (currentValue) + ((rightValue - (2*currentValue) + leftValue));
                resultmap.push_back(approx);
                
                
            }
            spacestep++;
            
            
        }
        timestep++;
    }


    printf("bad");
}
