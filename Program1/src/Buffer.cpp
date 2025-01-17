#include "Buffer.h"

void Buffer::write(const std::map<char, int>& data) {
    std::lock_guard<std::mutex> lock(mutex);
    buffer = data;
}

std::map<char, int> Buffer::read() {
    std::lock_guard<std::mutex> lock(mutex);
    return buffer;
}

bool Buffer::hasData() const {
    std::lock_guard<std::mutex> lock(mutex);
    return !buffer.empty();
}
