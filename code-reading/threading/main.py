import threading
import time
import sys

sys.setcheckinterval(1)

class MyThread(threading.Thread):
    def __init__(self, level):
        threading.Thread.__init__(self)
        self.level = level
    def run(self):
        print self.getName()
        if self.level > 8:
            return
        thread_a = MyThread(self.level+1)
        thread_b = MyThread(self.level+1)
        thread_a.start()
        thread_b.start()

thread = MyThread(1)
thread.start()

time.sleep(2)
