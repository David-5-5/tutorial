import threading
from typing import Callable

class H2O:
    def __init__(self):
        self.lock = threading.Lock()
        self.sem = threading.Semaphore(2)
        self.bar = threading.Barrier(3)


    def hydrogen(self, releaseHydrogen: 'Callable[[], None]') -> None:
        with self.sem:
            # releaseHydrogen() outputs "H". Do not change or remove this line.
            releaseHydrogen()
            self.bar.wait()


    def oxygen(self, releaseOxygen: 'Callable[[], None]') -> None:
        with self.lock:
            # releaseOxygen() outputs "O". Do not change or remove this line.
            releaseOxygen()
            self.bar.wait()

