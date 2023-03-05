#ifndef IR_ALLOC_H
#define IR_ALLOC_H


 

//Virtual Allocator Object
template<typename T>
struct IRAllocator
{
    IRAllocator(){}
    virtual int Allocate(int Quantity) = 0;
    virtual int Reallocate(int Quantity) = 0;
    virtual int Deallocate(int Quantity) = 0;
    ~IRAllocator(){}
};

//Function Pointer Method
struct CIRAllocator
{
private:
    typedef int(CIRAllocator::*m_Allocate)(int Quantity);
    typedef int(CIRAllocator::*m_Reallocate)(int Quantity);
    typedef int(CIRAllocator::*m_Deallocate)(int Quantity);
    m_Allocate AllocateFunction;
    m_Reallocate ReallocateFunction;
    m_Deallocate DeallocateFunction;
public:
    CIRAllocator(){}
    
    void SetAllocateFunction(m_Allocate FP){ AllocateFunction = FP;  }
    void SetReallocationFunction(m_Reallocate FP){ ReallocateFunction = FP; }
    void SetDeallocationFunction(m_Deallocate FP){ DeallocateFunction = FP; }
    int Allocate(int Quantity){ if(AllocateFunction != nullptr){ (this->*AllocateFunction)(Quantity); }  return 1; }
    int Reallocate(int Quantity){ if(ReallocateFunction != nullptr){ (this->*ReallocateFunction)(Quantity); }  return 1; }
    int Deallocate(int Quantity){ if(DeallocateFunction != nullptr){ (this->*DeallocateFunction)(Quantity); } return 1; }
    ~CIRAllocator(){}

};

//CRTP
template<typename Derived>
struct CRTIRAllocator
{
public:
    CRTIRAllocator(){}
    int Allocate(int Quantity){ return static_cast<Derived*>(this)->AllocateImpl(Quantity); }
    int Reallocate(int Quantity){ return static_cast<Derived*>(this)->ReallocateImpl(Quantity); }
    int Deallocate(int Quantity){ return static_cast<Derived*>(this)->DeallocateImpl(Quantity); }
    ~CRTIRAllocator(){ }
};


#endif