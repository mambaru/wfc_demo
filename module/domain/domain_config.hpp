#pragma once


namespace wamba{ namespace demo{

struct domain_config
{
  size_t generate_threads;
  domain_config()
    : generate_threads(0)
  {}
};

}}
