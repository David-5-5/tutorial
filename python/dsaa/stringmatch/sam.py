class State:
    def __init__(self, len: int, link: int) -> None:
        self.len = len
        self.link = link
        self.next = dict([str], [int])


class SAM:

    def __init__(self):
        self.last = State(0, -1)

    def add(self, ch: str):
        cur = State(self.last.len+1, -1)