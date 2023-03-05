#pragma once
#include "102Elements.h"

#include <Vector>
void Question1()
{
    OOTElement E1,E2,E3,E4,E5;
    //Which form monoatomic ions given that they
    E1.Group = 1;
    E2.Group = 2;
    E3.Group = 3;
    E4.Group = 16;
    E5.Group = 17;
    OOTElement ElementBuffer[] = {E1, E2, E3, E4, E5};

    //lose an s electron
    std::vector<OOTElement> Solution;
    printf("Solution #1: ");
    for(int i = 0; i < 5; i++)
    {
        OOTElement Subject = ElementBuffer[i];
        if(Subject.Group >= 1)
        {
            if((Subject.Group - 1) == 0)
            {
                Solution.push_back(Subject);
                printf("%d\n", i+1);
                
            }
        }
    }
    
    //losing two s electrons
    printf("Solution #2: ");
    for(int i = 0; i < 5; i++)
    {
        OOTElement Subject = ElementBuffer[i];
        if(Subject.Group >= 1)
        {
            if((Subject.Group - 2) == 0)
            {
                Solution.push_back(Subject);
                printf("%d\n", i+1);
            }
        }
    }

    //losing two s electrons and one p electron.
    printf("Solution #3: ");
    for(int i = 0; i < 5; i++)
    {
        OOTElement Subject = ElementBuffer[i];
        if(Subject.Group >= 1)
        {
            if(Subject.Group - 1 == 12)
            {
                int DJump = Subject.Group -= 10;
                if(DJump - 2 == 0)
                {
                    Solution.push_back(Subject);
                    printf("%d\n", i);
                }
            }
        }
    }
    
    //By adding 1 to a p orbital
    printf("Solution #4: ");
    for(int i = 0; i < 5; i++)
    {
        OOTElement Subject = ElementBuffer[i];
        if(Subject.Group >= 1)
        {
            if(Subject.Group == 17)
            {
                printf("%d\n", i+1);
            }
        }
    }

    //By adding electrons to two p orbitals:
    printf("Solution #5: ");
    for(int i = 0; i < 5; i++)
    {
        OOTElement Subject = ElementBuffer[i];
        if(Subject.Group >= 1)
        {
            if(Subject.Group == 16)
            {
                printf("%d\n", i+1);
            }
        }
    }

    


}

