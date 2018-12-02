import time
import threading
from queue import Queue

def job(l,q):  #不能有返回值    l 代表列表，  q 是queue队列
    
    for i in range(len(l)):
        l[i] = l[i] ** 2
    q.put(l)

def multithreading():
    q = Queue()
    threads = []
    data = [[1,2,3],[3,4,5],[1,9,8],[1,5,9]]
    for i in range(4):
        t = threading.Thread(target = job, args = (data[i],q))
        t.start()
        threads.append(t)
    for thread in threads:
        thread.join()

    result = []
    for _ in range(4):
        result.append(q.get())
    print(result)

if __name__ == '__main__':
    multithreading()
    
