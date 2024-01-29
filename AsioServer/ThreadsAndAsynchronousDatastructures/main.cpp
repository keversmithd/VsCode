#include <iostream>
#include <thread>
#include <functional>


struct Request
{
    template <typename _Callable, typename... _Args>
    Request(_Callable callable, _Args... args) : _callable(std::bind(callable, args...)) {}

    void Start()
    {
        _callable();
    }

    private:
    std::function<void()> _callable;
};


int pop(int i, int b)
{
    printf("called random function %d %d\n", i, b);
}

int main()
{
    
    Request r(pop, 1,2);

    r.Start();

    
    
}