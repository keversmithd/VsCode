#ifndef IRC_ALLOC_H
#define IRC_ALLOC_H

#include "IRAllocator.h"
#include <memory>
#include <malloc.h>
#include <functional>

template<typename T>
struct IRCAllocator : IRAllocator<T>
{
private:
    T* Memory;
    int ReservedMemory;
    int ElementCount;
    int AllocatorStatus;
public:
    IRCAllocator() : Memory(nullptr), ReservedMemory(0), ElementCount(0), AllocatorStatus(1)
    {
        
    }
    int Allocate(int Quantity) override
    {
        if(AllocatorStatus == -1){ return 0; }
        if(ReservedMemory != 0 && Memory != nullptr){ int ExtensionStatus = Extend(Quantity); if(!ExtensionStatus){ AllocatorStatus = -1; } return ExtensionStatus; }
        if(Memory != nullptr){ Free(); }
        void* MemorySubstitute = nullptr;
        MemorySubstitute = malloc(sizeof(T)*Quantity);
        if(MemorySubstitute == nullptr){ AllocatorStatus = -1; return 0; }
        Memory = (T*)MemorySubstitute;
        ReservedMemory = Quantity*sizeof(T);
        ElementCount = Quantity;
        return 1;
    }
    int Reallocate(int Quantity) override
    {
        if(AllocatorStatus == -1){return 0;}
        if(ReservedMemory == 0 && Memory == nullptr){ int AllocateStatus = Allocate(Quantity); if(!AllocateStatus){ AllocatorStatus = -1;} return AllocateStatus; }
        if(Memory == nullptr){ int AllocateStatus = Allocate(Quantity); if(!AllocateStatus){ AllocatorStatus = -1;} return AllocateStatus; }
        void* MemorySubstitute = nullptr;
        MemorySubstitute = realloc(Memory, (ElementCount)*sizeof(T));
        if(MemorySubstitute == nullptr){ AllocatorStatus = -1; Free(); return 0; }
        Memory = (T*)MemorySubstitute;
        return 1;
    }
    int Extend(int Quantity)
    {
        if(AllocatorStatus == -1){return 0;}
        if(ReservedMemory == 0 && Memory == nullptr){ int AllocateStatus = Allocate(Quantity); if(!AllocateStatus){ AllocatorStatus = -1;} return AllocateStatus; }
        if(Memory == nullptr){ int AllocateStatus = Allocate(Quantity); if(!AllocateStatus){ AllocatorStatus = -1;} return AllocateStatus; }
        void* MemorySubstitute = nullptr;
        MemorySubstitute = realloc(Memory, (ElementCount+Quantity)*sizeof(T));
        if(Memory != nullptr)
        {
            free(Memory);
        }
        if(MemorySubstitute == nullptr){ AllocatorStatus = -1; Free(); return 0; }
        Memory = (T*)MemorySubstitute;
        return 1;
    }
    int Free()
    {
        if(AllocatorStatus == -1){ if(Memory != nullptr){ free(Memory); } return 0; }
        if(ReservedMemory == 0 && Memory == nullptr){ return 0; }
        if(Memory != nullptr){ free(Memory); }
        ReservedMemory = 0;
        ElementCount = 0;
        return 1;
    }
    int Deallocate(int Quantity)
    {
        if(AllocatorStatus == -1){return 0;}
        if(ReservedMemory == 0 || ElementCount == 0){ return 0; }
        if(Memory == nullptr) { return 0; }
        if(Quantity > ElementCount){ int FreeStatus = Free(); if(!FreeStatus){AllocatorStatus = -1; } return FreeStatus; }
        int ReallocationStatus = Reallocate(ElementCount-Quantity);
        if(!ReallocationStatus){ AllocatorStatus = -1; return ReallocationStatus; }
        return 1;
        
    }
    
    ~IRCAllocator(){ Free(); }
};

template<typename T>
struct CIRCAllocator : CIRAllocator
{
private:
    T* Memory;
    int ReservedMemory;
    int ElementCount;
    int AllocatorStatus;
public:
    CIRCAllocator() : Memory(nullptr), ReservedMemory(0), ElementCount(0), AllocatorStatus(1)
    {
        SetAllocateFunction(std::bind(&CIRCAllocator<T>::Allocate_x, this));
        SetDeallocationFunction(std::bind(&CIRCAllocator<T>::Deallocate_x, this));
        SetReallocationFunction(std::bind(&CIRCAllocator<T>::Reallocate_x,  this));
    }
    int Allocate_x(int Quantity)
    {
        if(AllocatorStatus == -1){ return 0; }
        if(ReservedMemory != 0 && Memory != nullptr){ int ExtensionStatus = Extend_x(Quantity); if(!ExtensionStatus){ AllocatorStatus = -1; } return ExtensionStatus; }
        if(Memory != nullptr){ Free_x(); }
        void* MemorySubstitute = nullptr;
        MemorySubstitute = malloc(sizeof(T)*Quantity);
        if(MemorySubstitute == nullptr){ AllocatorStatus = -1; return 0; }
        Memory = (T*)MemorySubstitute;
        ReservedMemory = Quantity*sizeof(T);
        ElementCount = Quantity;
    }
    int Reallocate_x(int Quantity)
    {
        if(AllocatorStatus == -1){return 0;}
            if(ReservedMemory == 0 && Memory == nullptr){ int AllocateStatus = Allocate(Quantity); if(!AllocateStatus){ AllocatorStatus = -1;} return AllocateStatus; }
            if(Memory == nullptr){ int AllocateStatus = Allocate(Quantity); if(!AllocateStatus){ AllocatorStatus = -1;} return AllocateStatus; }
            void* MemorySubstitute = nullptr;
            MemorySubstitute = realloc(Memory, (ElementCount)*sizeof(T));
            if(MemorySubstitute == nullptr){ AllocatorStatus = -1; Free_x(); return 0; }
            Memory = MemorySubstitute;
            return 1;
    }
    int Deallocate_x(int Quantity)
    {
        if(AllocatorStatus == -1){return 0;}
        if(ReservedMemory == 0 || ElementCount == 0){ return 0; }
        if(Memory == nullptr) { return 0; }
        if(Quantity > ElementCount){ int FreeStatus = Free_x(); if(!FreeStatus){AllocatorStatus = -1; } return FreeStatus; }
        int ReallocationStatus = Reallocate_x(ElementCount-Quantity);
        if(!ReallocationStatus){ AllocatorStatus = -1; return ReallocationStatus; }
        return 1;
    }
    int Extend_x(int Quantity)
    {
        if(AllocatorStatus == -1){return 0;}
            if(ReservedMemory == 0 && Memory == nullptr){ int AllocateStatus = Allocate_x(Quantity); if(!AllocateStatus){ AllocatorStatus = -1;} return AllocateStatus; }
            if(Memory == nullptr){ int AllocateStatus = Allocate_x(Quantity); if(!AllocateStatus){ AllocatorStatus = -1;} return AllocateStatus; }
            void* MemorySubstitute = nullptr;
            MemorySubstitute = realloc(Memory, (ElementCount+Quantity)*sizeof(T));
            if(MemorySubstitute == nullptr){ AllocatorStatus = -1; Free_x(); return 0; }
            Memory = MemorySubstitute;
            return 1;
    }
    int Free_x()
    {
        if(AllocatorStatus == -1){ if(Memory != nullptr){ free(Memory); } return 0; }
            if(ReservedMemory == 0 && Memory == nullptr){ return 0; }
            if(Memory != nullptr){ free(Memory); }
            ReservedMemory = 0;
            ElementCount = 0;
            return 1;
    }
    ~CIRCAllocator()
    {
        Free_x();
    }
};

template<typename T>
struct CRTIRCAllocator : CRTIRAllocator<CRTIRCAllocator<T>>
{
private:
    T* Memory;
    int ReservedMemory;
    int ElementCount;
    int AllocatorStatus;
public:
    CRTIRCAllocator() : Memory(nullptr), ReservedMemory(0), ElementCount(0), AllocatorStatus(1)
    {

    }
    AllocateImpl(int Quantity)
    { 
        if(AllocatorStatus == -1){ return 0; }
        if(ReservedMemory != 0 && Memory != nullptr){ int ExtensionStatus = Extend(Quantity); if(!ExtensionStatus){ AllocatorStatus = -1; } return ExtensionStatus; }
        if(Memory != nullptr){ Free(); }
        void* MemorySubstitute = nullptr;
        MemorySubstitute = malloc(sizeof(T)*Quantity);
        if(MemorySubstitute == nullptr){ AllocatorStatus = -1; return 0; }
        Memory = (T*)MemorySubstitute;
        ReservedMemory = Quantity*sizeof(T);
        ElementCount = Quantity;
    }
    ReallocateImpl(int Quantity)
    {
        if(AllocatorStatus == -1){return 0;}
        if(ReservedMemory == 0 && Memory == nullptr){ int AllocateStatus = AllocateImpl(Quantity); if(!AllocateStatus){ AllocatorStatus = -1;} return AllocateStatus; }
        if(Memory == nullptr){ int AllocateStatus = AllocateImpl(Quantity); if(!AllocateStatus){ AllocatorStatus = -1;} return AllocateStatus; }
        void* MemorySubstitute = nullptr;
        MemorySubstitute = realloc(Memory, (ElementCount)*sizeof(T));
        if(MemorySubstitute == nullptr){ AllocatorStatus = -1; Free(); return 0; }
        Memory = MemorySubstitute;
        return 1;
    }
    DeallocateImpl(int Quantity)
    {
        if(AllocatorStatus == -1){return 0;}
        if(ReservedMemory == 0 || ElementCount == 0){ return 0; }
        if(Memory == nullptr) { return 0; }
        if(Quantity > ElementCount){ int FreeStatus = Free(); if(!FreeStatus){AllocatorStatus = -1; } return FreeStatus; }
        int ReallocationStatus = ReallocateImpl(ElementCount-Quantity);
        if(!ReallocationStatus){ AllocatorStatus = -1; return ReallocationStatus; }
        return 1;
    }
    int Extend(int Quantity)
    {
        if(AllocatorStatus == -1){return 0;}
        if(ReservedMemory == 0 && Memory == nullptr){ int AllocateStatus = AllocateImpl(Quantity); if(!AllocateStatus){ AllocatorStatus = -1;} return AllocateStatus; }
        if(Memory == nullptr){ int AllocateStatus = AllocateImpl(Quantity); if(!AllocateStatus){ AllocatorStatus = -1;} return AllocateStatus; }
        void* MemorySubstitute = nullptr;
        MemorySubstitute = realloc(Memory, (ElementCount+Quantity)*sizeof(T));
        if(MemorySubstitute == nullptr){ AllocatorStatus = -1; Free(); return 0; }
        Memory = MemorySubstitute;
        return 1;
    }
    int Free()
    {
        if(AllocatorStatus == -1){ if(Memory != nullptr){ free(Memory); } return 0; }
        if(ReservedMemory == 0 && Memory == nullptr){ return 0; }
        if(Memory != nullptr){ free(Memory); }
        ReservedMemory = 0;
        ElementCount = 0;
        return 1;
    }
    ~CRTIRCAllocator() {Free();}
};





#endif