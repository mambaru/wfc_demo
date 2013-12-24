#pragma once

#include <memory>

namespace wamba{ namespace demo{

struct context
{
  std::weak_ptr<idemo> demo;
};

}}
