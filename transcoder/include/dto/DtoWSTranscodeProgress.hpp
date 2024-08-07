#pragma once

#include "dto/DtoResponseInterface.hpp"

namespace tr {
    class DtoWSTranscodeProgress;
    using DtoWSTranscodeProgressPtr = std::shared_ptr<DtoWSTranscodeProgress>;

    class DtoWSTranscodeProgress : public DtoResponseInterface<DtoWSTranscodeProgress> {
    public:
        enum class STATE { TRRANSCODING, STOP, FINISH };

    public:
        static DtoWSTranscodeProgressPtr createProgressMessage(int now, int max);
        static DtoWSTranscodeProgressPtr createStartMessage();
        static DtoWSTranscodeProgressPtr createWaitMessage(int number);
        static DtoWSTranscodeProgressPtr createFinishMessage(const std::string& outputFile);
        static DtoWSTranscodeProgressPtr createStopMessage();

    public:
        explicit DtoWSTranscodeProgress();
        virtual ~DtoWSTranscodeProgress() = default;
    };
}
