import threading
from typing import Callable


class FooBar:
    def __init__(self, n):
        self.n = n
        self.cond = threading.Condition()
        self.turn = 0


    def foo(self, printFoo: 'Callable[[], None]') -> None:
        
        for i in range(self.n):
            with self.cond:
                while self.turn != 0:
                    self.cond.wait()
                # printFoo() outputs "foo". Do not change or remove this line.
                printFoo()
                self.turn = 1
                self.cond.notify_all()


    def bar(self, printBar: 'Callable[[], None]') -> None:
        
        for i in range(self.n):
            with self.cond:
                if self.turn != 1:
                    self.cond.wait()
                # printBar() outputs "bar". Do not change or remove this line.
                printBar()
                self.turn = 0
                self.cond.notify_all()            
