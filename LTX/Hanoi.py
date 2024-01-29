from collections import deque

class Queue:
    def __init__(self):
        self.items = deque()

    def enqueue(self, item):
        self.items.append(item)

    def dequeue(self):
        if not self.is_empty():
            return self.items.popleft()

    def push(self, item):
        self.items.appendleft(item)

    def is_empty(self):
        return len(self.items) == 0

    def size(self):
        return len(self.items)

    def display(self):
        for item in self.items:
            print(item)


def hanoi(pegs, n):
    if(n == 1):
        return
    
    for i in range(1,  n+1):
        pegs[0].enqueue(i)

    
    for i in range(0,3):
        if(pegs[1].is_empty() and pegs[2].is_empty()):
            slab = pegs[0].dequeue()
            pegs[1].push(slab)
            slab = pegs[0].dequeue()
            pegs[2].push(slab)
            slab = pegs[1].dequeue()
            pegs[2].push(slab)
        if(pegs[1].is_empty() and not pegs[2].is_empty()):
            slab = pegs[0].dequeue()
            pegs[1].push(slab)
            slab = pegs[2].dequeue()
            pegs[0].push(slab)
            slab = pegs[2].dequeue()
            pegs[1].push(slab)
            slab = pegs[0].dequeue()
            pegs[1].push(slab)
            slab = pegs[0].dequeue()
            pegs[2].push(slab)
            


        
    

    print("Peg 1")
    pegs[0].display()
    print("Peg 2")
    pegs[1].display()
    print("Peg 3")
    pegs[2].display()

    return

pegs = [Queue() for _  in range(3) ]

def isPalindrome(word):
    word = word.lower().replace(" ", "")
    if (len(word) < 2): return True
    if word[0] != word[-1]: return False
    return isPalindrome(word[1:-1])


def doubleArray(array, begin, end):
    
    if(end-begin <= 0):
        array[begin]*=2
        return
    
    mid = int((begin+end)/2)

    doubleArray(array,begin,mid)
    doubleArray(array,mid+1,end)

A = [1,2,3,4]
doubleArray(A,0,len(A)-1)
print(A)



