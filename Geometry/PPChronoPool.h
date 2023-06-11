#ifndef CHRONO_OOL_HH
#define CHRONO_OOL_HH

#include <stdint.h>
#include <memory>
#include <stdexcept>
#include <math.h>
#define POOL_CHANNELS 4

struct ChronologicalPool;

extern ChronologicalPool* baseInstance;
extern ChronologicalPool* baseInstanceArray[POOL_CHANNELS];

struct ChronologicalPool
{
    public:
        void* AccessibleMemory;
        int   bytesAllocated;
        int   workableByteLocation;
        int   workableID;
        bool  fragment;
    public:
        ChronologicalPool(bool Fragment = false) : AccessibleMemory(nullptr), bytesAllocated(1), workableByteLocation(0), workableID(-1), fragment(Fragment)
        {
            baseInstance = this;       
        }
        ChronologicalPool(int InitalReservation, bool Fragment = false, int poolID = -1) : AccessibleMemory(nullptr), bytesAllocated(1), workableByteLocation(0), workableID(-1), fragment(Fragment)
        {
            if(poolID < 0 || poolID > POOL_CHANNELS-1)
            {
                baseInstance = this;
            }else
            {
                baseInstanceArray[poolID] = this;
            }
            if(InitalReservation > 0)
            {
                AdjustSize(InitalReservation);
            }
        }

        void RetrieveMemoryAccess(int EstimatedReservation, int& MemoryAccess, int* IDSection)
        {
            workableID += 1; //ID currently being worked on.

            AdjustSize(EstimatedReservation);
            
            *IDSection = workableID;
            MemoryAccess = workableByteLocation;
            workableByteLocation += EstimatedReservation;

        }

        bool ExtendID(const int IDSection, const int ExtensionAmount)
        {
            if(IDSection != workableID){ return false; }
            AdjustSize(ExtensionAmount);
            workableByteLocation += ExtensionAmount;
            return true;
        }

        bool RetractID(const int IDSection, const int RetractionAmount)
        {
            if(IDSection != workableID) {return false; }
            workableByteLocation -= RetractionAmount;
            return true;
        }

        void AdjustSize(int NewReservation)
        {
            if(NewReservation == 0)
            {
                return;
            }
            if(bytesAllocated <= (workableByteLocation + NewReservation))
            {
                int nmem = pow(2,ceil(log((bytesAllocated)+NewReservation)/log(2)));
                //void* AdjustmentPointer = realloc(AccessibleMemory, (nmem));
                void* AdjustmentPointer = malloc(nmem);
                if(AccessibleMemory != nullptr)
                {
                    memcpy(AdjustmentPointer, AccessibleMemory, workableByteLocation);
                }

                if(AdjustmentPointer == nullptr){ throw std::invalid_argument("Realloc returned nullptr."); }
                if(AdjustmentPointer != AccessibleMemory && AccessibleMemory != nullptr)
                {
                    free(AccessibleMemory);
                }
                AccessibleMemory = AdjustmentPointer;
                bytesAllocated = nmem;
            }
            
        }

        ~ChronologicalPool()
        {
            if(fragment == false)
            {
                if(AccessibleMemory != nullptr)
                {
                    delete[] (char*)AccessibleMemory;
                }
            }

            baseInstance = nullptr;
        }
};



template<typename T>
struct ChronologicalPoolEntry
{
    private:
        T dummy;
        int IDSection;
        int Start;
        ChronologicalPool* baseEntry;

    public:
        int tail;
        int NumberOfElements;
        ChronologicalPoolEntry() : baseEntry(baseInstance), NumberOfElements(0), IDSection(-1), tail(-1), Start(-1)
        {
            baseEntry = baseInstance;
            if(baseEntry == nullptr){ throw( std::invalid_argument("Chronological pool pointer was invalid.") ); }
        }

        int size()
        {

            return tail+1;

        }
        
        ChronologicalPoolEntry(int numberOfElements, int poolID = -1) : baseEntry(baseInstance), NumberOfElements(numberOfElements), IDSection(-1), tail(-1), Start(-1)
        {

            if(poolID < 0 || poolID > POOL_CHANNELS-1)
            {
                baseEntry = baseInstance;
            }else
            {
                baseEntry = baseInstanceArray[poolID];
            }
            if(baseEntry == nullptr){throw( std::invalid_argument("Chronological pool pointer was invalid.") );}

            if(numberOfElements < 0){ NumberOfElements = 0; }
            else
            {
                baseEntry->RetrieveMemoryAccess(NumberOfElements * sizeof(T), Start, &IDSection);
            }

        }

        bool CheckExtendable(int Reservation)
        {

            if(!baseEntry->ExtendID(IDSection, Reservation)){return false;}
            return true;

        }
        


        void ExtendReserve(int ExtensionMarker)
        {

            if(IDSection == -1)
            {
                baseEntry->RetrieveMemoryAccess(ExtensionMarker * sizeof(T), Start, &IDSection);
            }else if(!CheckExtendable(ExtensionMarker * sizeof(T))){throw( std::invalid_argument("The reserved pointer was extended past its possible limit.") ); return;}

            NumberOfElements += ExtensionMarker;

        }

        T* ExposeInnerPointer()
        {

            return (T*)((char*)baseEntry->AccessibleMemory)+Start;

        }

        void detract_reserve(int elements)
        {
            if(elements == 0){return;}
            if(!baseEntry->RetractID(IDSection, sizeof(T)*elements)){throw( std::invalid_argument("The reserved pointer was extended past its possible limit.") ); return;}
            NumberOfElements-=elements;
        }

        void push_back(T memoryTrain)
        {

            if(tail+1 >= NumberOfElements)
            {
                ExtendReserve(1);
            }
            tail++;
            ((T*)(((char*)baseEntry->AccessibleMemory)+Start))[tail] = memoryTrain;

        }

        T& operator [](int index)
        {

            if(index >= 0 && index <= tail)
            {
                return ((T*)(((char*)baseEntry->AccessibleMemory)+Start))[index];
            }
            return dummy;

        }

        void AppendAdjacent(ChronologicalPoolEntry<T> adjacentList)
        {

            NumberOfElements += adjacentList.NumberOfElements;
            tail += adjacentList.NumberOfElements;

        }

        void ResetStatus()
        {

            NumberOfElements = 0;
            IDSection = -1;

        }

        ~ChronologicalPoolEntry()
        {



        }
};

#endif