#ifndef BUFFER_H
#define BUFFER_H

#include <map>
#include <mutex>

class Buffer {
public:
    Buffer() = default;

    void write(const std::map<char, int>& data);
    std::map<char, int> read();
    bool hasData() const;

private:
    std::map<char, int> buffer;
    mutable std::mutex mutex;
};

#endif // BUFFER_H
