#include <iostream>
#include <string>
#include <vector>

struct vec2
{
    double x;
    double y;
};

void DrawResults(double** mat, int TimeSteps, int SpaceSteps, float dt, float dx, int specialT)
{
    printf("\\draw[help lines, step=%f] (%f, %f) grid (%f, %f);\n", dx, 0, 0, SpaceSteps*dx, 1.0f);
    printf("\\draw[->] (%f, %f) -- (%f, %d);\n", 0,0,SpaceSteps*dx, 0);
    printf("\\draw[->] (%f, %f) -- (%f, %f);\n", 0,0, 0, 1.0f);
    printf("\\foreach\\x in {%f, %f, ..., %f}\n \\draw (%s, %f) [anchor=north] node {\\pgfmathprintnumber[fixed, precision=3]{\\x}};\n", 0.0f, dx*2, SpaceSteps*dx, "\\x", 0.0f);
    printf("\\foreach\\x in {%f, %f, ..., %f}\n \\draw (%f, %s) [anchor=east] node {\\pgfmathprintnumber[fixed, precision=3]{\\x}};\n", 0.0f, dx*2, SpaceSteps*dx, 0.0f, "\\x");


    for(int x = 0; x < SpaceSteps;  x++)
    {

        printf("\\draw [fill=black] (%f,%f) circle (0.5pt);", x*dx, mat[specialT][x]);

    }

}

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

void SecondCentralDifferences()
{
    vec2 Domain = {0,1};
    double SpaceStepsRequired = 20; //Meters
    double TimeFinish = 0.05; //1 Hour

    double dt = 0.0013; //Seconds
    double dx = 1.0/SpaceStepsRequired; //Centimeters

    double t0 = 1.1; 
    double x0 = 0;
    double x1 = 0;

    double epsilon = (dt)/(dx*dx);


    int TDimension = (TimeFinish/dt);
    int XDimension = SpaceStepsRequired;

    double** results = new double*[TDimension];
    for (int i = 0; i < TDimension; i++) {
        results[i] = new double[XDimension];
    }

    for(int t = 0; t < TDimension; t++)
    {
        for(int s = 0; s < XDimension; s++)
        {
            if(s == 0)
            {
                results[t][s] = x0;
            }else if(s == (XDimension-1))
            {
                results[t][s] = x1;

            }else if(t == 0)
            {   
                // double js = s/(float)XDimension;
                // if(js >= 0 && js <= 1.0/2.0)
                // {
                //     results[t][s] = (2*js);
                // }else if(js >= 1.0/2.0 && js <= 1.0)
                // {
                //     results[t][s] = (2-(2*js));
                // }

                results[t][s] = t0;

            }else
            {
                double rightvalue = results[t-1][s+1];
                double leftvalue = results[t-1][s-1];
                double currentvalue = results[t-1][s];
                
                results[t][s] = currentvalue + (epsilon *(rightvalue - (2*currentvalue) + leftvalue ));
                
            }
        }
    }
    

    DrawResults(results, TDimension, XDimension, dt, dx, 0);
}

int FirstCentralDifferences()
{
    double tf = (0.012)*20;
    double dt = 0.012;

    int TDimension = tf/dt;
    int XDimension = 20;

    double dx = 1.0/XDimension;

    double** results = new double*[TDimension];
    for (int i = 0; i < TDimension; i++) {
        results[i] = new double[XDimension];
    }

    double x0 = 0;
    double x1 = 0;

    double epsilon = (dt)/(dx*dx);

    for(int t = 0; t < TDimension; t++)
    {
        for(int s = 0; s < XDimension; s++)
        {
            if(s == 0)
            {
                results[t][s] = x0;
            }else if(s == (XDimension-1))
            {
                results[t][s] = x1;

            }else if(t == 0)
            {   
                double js = s/(float)XDimension;
                if(js >= 0 && js <= 1.0/2.0)
                {
                    results[t][s] = (2*js);
                }else if(js >= 1.0/2.0 && js <= 1.0)
                {
                    results[t][s] = (2-(2*js));
                }
            }else
            {
                double rightvalue = results[t-1][s+1];
                double leftvalue = results[t-1][s-1];
                double currentvalue = results[t-1][s];

                results[t][s] = currentvalue + (rightvalue - leftvalue)/(2);
            }
        }
    }

    DrawResults(results, TDimension, XDimension, dt, dx, 2);
    DrawResults(results, TDimension, XDimension, dt, dx, 3);
    DrawResults(results, TDimension, XDimension, dt, dx, 4);


    return 0;
}