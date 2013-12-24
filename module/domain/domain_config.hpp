#pragma once


namespace wamba{ namespace demo{

struct domain_config
{
  int generate_threads;
  domain_config()
    : generate_threads(1)
  {}
};

}}
