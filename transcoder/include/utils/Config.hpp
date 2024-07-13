#pragma once

namespace tr {
    class Config {
    public:
        static Config& getInstance();
        static Config instance;

    public:
        static bool parse(int argc, char* argv[]);

        static int getPort();
        static int getThreadNum();

    private:
        explicit Config();
        virtual ~Config();

    private:
        int port;
        int threadNum;
    };
}
