#include <iostream>
#include <functional>
#include <string>

using namespace std;

class EmailProcessor {
public:
    void receiverMessage(const string &message) {
        if( _handler_func ) {
            _handler_func(message);
        }
    }

    void setHandlerFunc(function<void (const string &message)> handler_func) {
        _handler_func = handler_func;
    }

private:
    function<void (const string &)> _handler_func;
};

class MessageSizeStore {
public:
    MessageSizeStore() : _max_size(0) {}
    void checkMessage(const string &message) {
        const int size = message.length();
        if(size > _max_size) {
            _max_size = size;
        }
    }

    int getSize() {
        return _max_size;
    }
private:
    int _max_size;
};

int main(int argc, char const *argv[]) {

    EmailProcessor processor;
    MessageSizeStore store;
    // processor.setHandlerFunc(checkMessage);
    processor.setHandlerFunc(
    [&](const string & message) {
        store.checkMessage(message);
    });

    return 0;
}