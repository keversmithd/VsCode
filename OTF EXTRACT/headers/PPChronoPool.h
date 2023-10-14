#ifndef CHRONO_OOL_HH
#define CHRONO_OOL_HH

#include <stdint.h>
#include <memory>
#include <stdexcept>

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

        void RetrieveMemoryAccess(int EstimatedReservation, void*& MemoryAccess, int* IDSection)
        {
            workableID += 1; //ID currently being worked on.


            AdjustSize(EstimatedReservation);
            
            *IDSection = workableID;
            MemoryAccess = (void*)((uint8_t*)(AccessibleMemory)+workableByteLocation);
            workableByteLocation += EstimatedReservation;

        }

        bool ExtendID(const int IDSection, const int ExtensionAmount)
        {
            if(IDSection != workableID){ return false; }
            AdjustSize(ExtensionAmount);
            workableByteLocation += ExtensionAmount;
            return true;
        }

        void AdjustSize(int NewReservation)
        {
            if(bytesAllocated <= (workableByteLocation + NewReservation))
            {
                void* AdjustmentPointer = realloc(AccessibleMemory, (2*bytesAllocated)+NewReservation);
                if(AdjustmentPointer == nullptr){ throw std::invalid_argument("Realloc returned nullptr."); }
                if(AdjustmentPointer != AccessibleMemory && AccessibleMemory != nullptr)
                {
                    free(AccessibleMemory);
                }
                AccessibleMemory = AdjustmentPointer;
                bytesAllocated = (2*bytesAllocated)+NewReservation;
            }
            
        }

        ~ChronologicalPool()
        {
            if(fragment == false)
            {
                if(AccessibleMemory != nullptr)
                {
                    free(AccessibleMemory);
                }
            }

            baseInstance = nullptr;
        }
};



template<typename T>
struct ChronologicalPoolEntry
{
    private:
        T* PoolEntry;
        T dummy;
        int NumberOfElements;
        int IDSection;
        int tail;
        ChronologicalPool* baseEntry;
    public:
        ChronologicalPoolEntry() : PoolEntry(nullptr), baseEntry(baseInstance), NumberOfElements(0), IDSection(-1), tail(-1)
        {   
            baseEntry = baseInstance;
            if(baseEntry == nullptr){throw( std::invalid_argument("Chronological pool pointer was invalid.") );}

        }
        ChronologicalPoolEntry(int numberOfElements, int poolID = -1) : PoolEntry(nullptr), baseEntry(baseInstance), NumberOfElements(numberOfElements), IDSection(-1), tail(-1)
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
                baseEntry->RetrieveMemoryAccess(NumberOfElements * sizeof(T), (void*&)PoolEntry, &IDSection);
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
                baseEntry->RetrieveMemoryAccess(ExtensionMarker * sizeof(T), (void*&)PoolEntry, &IDSection);
            }else if(!CheckExtendable(ExtensionMarker)){throw( std::invalid_argument("The reserved pointer was extended past its possible limit.") ); return;}

            NumberOfElements += ExtensionMarker;
        }

        T* ExposeInnerPointer()
        {
            return PoolEntry;
        }

        void push_back(T memoryTrain)
        {
            ExtendReserve(1);
            tail++;
            PoolEntry[tail] = memoryTrain;
        }

        T& operator [](int index)
        {
            if(index >= 0 && index <= tail)
            {
                return PoolEntry[index];
            }
            return dummy;
        }

        void ResetStatus()
        {
            PoolEntry = nullptr;
            NumberOfElements = 0;
            IDSection = -1;
        }

        ~ChronologicalPoolEntry(){}
};

#endif