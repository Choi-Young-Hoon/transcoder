#pragma once

#include <string>
#include <vector>

#include "dto/DtoResponseInterface.hpp"

namespace tr {
    class DtoWSFileListResponse : public DtoResponseInterface<DtoWSFileListResponse> {
    public:
        explicit DtoWSFileListResponse();
        virtual ~DtoWSFileListResponse() = default;

    public:
        void setFileList(std::vector<std::string>& fileList);
    };
};
