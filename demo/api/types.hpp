#pragma once

#include <memory>
#include <vector>

namespace wamba{ namespace demo{

typedef std::vector<int> data_type;

typedef std::unique_ptr<data_type> data_ptr;

}}
