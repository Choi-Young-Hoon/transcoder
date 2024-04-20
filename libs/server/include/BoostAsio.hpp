#pragma once

#include "boost/asio.hpp"
#include "boost/beast.hpp"
#include "boost/json.hpp"

using tcp  = boost::asio::ip::tcp;

namespace asio   = boost::asio;
namespace http   = boost::beast::http;
namespace json   = boost::json;