# 周赛 296
class TextEditor:
    # 自行解答
    def __init__(self):
        self.text = ""
        self.cur = 0

    def addText(self, text: str) -> None:
        self.text = self.text[0:self.cur] + text + self.text[self.cur:]
        self.cur += len(text)

    def deleteText(self, k: int) -> int:
        todel = min(k, self.cur)
        self.text = self.text[0:self.cur-todel] + self.text[self.cur]
        self.cur -= todel
        return todel

    def cursorLeft(self, k: int) -> str:
        toleft = min(k, self.cur)
        self.cur -= toleft
        ret = min(10, self.cur)
        return self.text[self.cur-ret:self.cur]
        
    def cursorRight(self, k: int) -> str:
        toright = min(k, len(self.text) - self.cur)
        self.cur += toright
        ret = min(10, self.cur)
        return self.text[self.cur-ret:self.cur]



# Your TextEditor object will be instantiated and called as such:
# obj = TextEditor()
# obj.addText(text)
# param_2 = obj.deleteText(k)
# param_3 = obj.cursorLeft(k)
# param_4 = obj.cursorRight(k)