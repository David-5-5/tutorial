import threading
from typing import Callable


class ZeroEvenOdd:
    def __init__(self, n):
        self.n = n
        self.cond = threading.Condition()
        self.turn = 2

	# printNumber(x) outputs "x", where x is an integer.
    def zero(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(1, self.n+1):
            with self.cond:
                while self.turn != 2:
                    self.cond.wait()
                printNumber(0)
                self.turn = i % 2
                self.cond.notify_all()
        
    def even(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(2, self.n+1, 2):
            with self.cond:
                while self.turn != 0:
                    self.cond.wait()
                printNumber(i)
                self.turn = 2
                self.cond.notify_all()
            
        
    def odd(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(1, self.n+1, 2):
            with self.cond:
                while self.turn != 1:
                    self.cond.wait()
                printNumber(i)
                self.turn = 2
                self.cond.notify_all()        
