#pragma once

#include <string>

namespace tr {
    class Transcoder {
    public:
        explicit Transcoder();
        virtual ~Transcoder();

    public:
        void printHelloWorld();
    };
};