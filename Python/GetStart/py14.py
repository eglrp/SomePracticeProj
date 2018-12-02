import threading
import time

def thread_job():
    #print("this is a added thread, number is %s" % threading.current_thread())
    print("T1 start\n")
    
    for i in range(10):
        time.sleep(0.1)
        
    print("T1 finished\n")


def main():
    added_thread = threading.Thread(target = thread_job, name ="T1")
    added_thread.start()
    added_thread.join()   #等待状态
    #print(threading.active_count())
    #print(threading.enumerate())
    #print(threading.current_thread())

    print("all done\n")

if __name__ == '__main__':
    main()
