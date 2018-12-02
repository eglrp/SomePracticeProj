/*
 * Author: Neverland_LY
 * Date: 2018-11-18
 * ProjectName: future and promise
 * Version: v-1.0
 *
 * Description: Description
 */

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <future>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <chrono>

using namespace std;

std::mutex mu;
std::condition_variable cond;

/* For threads to return values: future */
void factorial1(int N, int &x) {
    int res = 1;
    for (int i = N; i > 1; i--)
        res *= i;

    cout << "Result is: " << res << endl;
    x = res;
}


int factorial2(int N) {
    int res = 1;
    for (int i = N; i > 1; i--)
        res *= i;

    cout << "Result is: " << res << endl;
    return res;
}


int factorial3(std::future<int> &f) {
    int res = 1;

    int N = f.get(); // 如果promise后不给传值的话会抛出异常，exception: std::future_errc::broken_promise
    for (int i = N; i > 1; i--)
        res *= i;

    cout << "Result is: " << res << endl;
    return res;
}

int factorial4(std::shared_future<int> f) {
    int res = 1;

    int N = f.get(); // 如果promise后不给传值的话会抛出异常，exception: std::future_errc::broken_promise
    for (int i = N; i > 1; i--)
        res *= i;

    cout << "Result is: " << res << endl;
    return res;
}

int main(int argc, char *argv[]) {

    {
        int x; // 现在这种情况 x 是主线程和线程t1的共享资源，所以要上锁
        std::thread t1(factorial1, 4, std::ref(x));
        t1.join();

        // 但是会造成整个代码的混乱，上锁解锁，还要 notify 很麻烦
        // 所以印引出 funture 这个概念
    }

    {
        //future
        //std::async 是一个函数
        int x;
        std::future<int> fu = std::async(factorial2, 4);
        x = fu.get(); // wait until child thread finished then return the value from child thread
        //fu.get() 只能调用一次
        //x = fu.get(); // program crash

        //这样做的好处是简洁有效，而且不再需要全局变量
        //
        //
        //但是又有新的问题出现，std::async 不一定能成功创建子线程
        //解决方法见下
    }


    {
        //future
        // std::launch::deferrd: 延迟创建执行
        int x;
        std::future<int> fu = std::async(std::launch::deferred, factorial2, 4);
        x = fu.get(); //这种情况下，std::async  不会创建线程，
        // 而是在执行 get() 的时候在当前线程中执行 factorial2 函数
        // 推荐这样做
    }

    {
        int x;
        //future
        // std::launch::async: 这种情况下，会创建新的子线程
        std::future<int> fu = std::async(std::launch::async, factorial2, 4);
        x = fu.get();

        // 也可以一起用
        // std::future<int> fu = std::async(std::launch::async | std::launch::deferrd, factorial2, 4);
    }

    {
        int x;

        std::promise<int> p;
        std::future<int> f = p.get_future();

        // 线程确保会创建
        std::future<int> fu = std::async(std::launch::async, factorial3, std::ref(f));

        // do something...

        // 如果确定我无法promise一个值，那么就跑出异常
        std::this_thread::sleep_for(chrono::milliseconds(20));
        p.set_exception(std::make_exception_ptr(std::runtime_error("To eerror is human!")));

        // p.set_value(4);  // 给 promise 传值
        // x = fu.get(); // 获取返回值

    }

    // 注意：
    // promise 和 future 都不能被 copy , 只能被 move
    // std::promise<int> p2 = std::move(p1);

    {
        int x;

        std::promise<int> p;
        std::future<int> f = p.get_future();

        // 假设 factorial 要和被多个线程执行
        std::future<int> fu = std::async(std::launch::async, factorial3, std::ref(f));
        std::future<int> fu2 = std::async(std::launch::async, factorial3, std::ref(f));
        std::future<int> fu3 = std::async(std::launch::async, factorial3, std::ref(f));
        std::future<int> fu4 = std::async(std::launch::async, factorial3, std::ref(f));
        std::future<int> fu5 = std::async(std::launch::async, factorial3, std::ref(f));
        // .... 10 threads
        // 因为一个 future 只能调用一次 f.get(),所以不能这样写 10 次
        //
        // 一个解决办法是写10个promise，10个future
        //
        //
        // 另一个办法是 用 shared_future
        //
        //
        p.set_value(4);  // 给 promise 传值
        x = fu.get(); // 获取返回值
    }

    {
        // shared_future
        int x;

        std::promise<int> p;
        std::future<int> f = p.get_future();
        std::shared_future<int> sf = f.share();

        // 注意这里，pf 可以被复制
        std::future<int> fu = std::async(std::launch::async, factorial4, sf);
        std::future<int> fu2 = std::async(std::launch::async, factorial4, sf);
        std::future<int> fu3 = std::async(std::launch::async, factorial4, sf);
        std::future<int> fu4 = std::async(std::launch::async, factorial4, sf);
        std::future<int> fu5 = std::async(std::launch::async, factorial4, sf);


        p.set_value(4);  // 所有的线程都会被传值然后开始运行


        x = fu.get(); // 获取返回值
    }

    cout << "Hello world!\n";

    return 0;
}
