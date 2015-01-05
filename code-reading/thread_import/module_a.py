import threading

print "import module_a start"
class MyThread(threading.Thread):
    def run(self):
        print "thread start"
        import module_echo
        print "thread end"

thread = MyThread()
print "start thread in module_a"
thread.start()
thread.join()
print "all end in module_a"
