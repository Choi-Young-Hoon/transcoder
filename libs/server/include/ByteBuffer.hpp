#pragma once

#include <vector>
#include <memory>

class ByteBuffer : public std::vector<unsigned char>, public std::enable_shared_from_this<ByteBuffer> {
public:
	explicit ByteBuffer();
	virtual ~ByteBuffer();
};