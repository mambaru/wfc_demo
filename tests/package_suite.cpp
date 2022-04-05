#include <package/demo_package.hpp>
#include <wfc/testing/testing_wfc.hpp>
#include <fas/testing.hpp>
#include <wjson/_json.hpp>
#include <wjson/wjson.hpp>

namespace{

  std::string hash_config()
  {
    using namespace wjson::literals;
    return
      "{\
        'hash': [\
          {\
            'name': 'hash1',        \
            'enabled': true,        \
            'suspend': false,       \
            'param': false          \
          }                         \
        ]                           \
      }"_json;
  }

  std::string demo_config(const std::string& target)
  {
    using namespace wjson::literals;
    return
      "{'name': 'storage1',  \
      'enabled': true,          \
      'suspend': false,         \
      'startup_priority': 0,    \
      'shutdown_priority': 0,   \
      'workflow': '',           \
      'hash_target': '"_json + target + "'}"_json;
  }

  std::string demo_service_config(const std::string& target)
  {
    using namespace wjson::literals;
    return
      "{'name': 'demo-service1',  \
      'target': '"_json + target + "'}"_json;
  }

  template<typename T>
  void add_config(T& t, wfc::testing_wfc& twfc, const std::string& comp, const std::string& json, int nline)
  {
    using namespace fas::testing;
    std::string strerr;
    wjson::json_error er;

    bool status = comp.empty() ? twfc.add_configs(json, &er, &strerr) : twfc.add_configs(comp, json, &er, &strerr);

    if ( !status )
    {
      if ( !er )
        t << error("add_configs arror: ") << strerr << FAS_FL << ": " << nline;
      else if ( strerr.empty() )
        t << is_false<assert>(er) << wjson::strerror::message_trace(er, json.begin(), json.end() ) << FAS_FL << ": " << nline;
      else
        t << is_false<assert>(er) << wjson::strerror::message_trace(er, strerr.begin(), strerr.end() ) << FAS_FL << ": " << nline;
    }
  }

  template<typename T>
  void add_config(T& t, wfc::testing_wfc& twfc, const std::string& json, int nline)
  {
    add_config(t, twfc, "", json, nline);
  }

}

UNIT(package1, "")
{
  using namespace fas::testing;
  using namespace wjson::literals;
  t << nothing;

  wfc::testing_wfc twfc;

  twfc.add_package(std::make_shared< damba::demo_package>() );

  wjson::json_error er;
  add_config(t, twfc, hash_config(), __LINE__);
  add_config(t, twfc, "demo", demo_config("hash1"), __LINE__);
  add_config(t, twfc, "demo-service", demo_service_config("storage1"), __LINE__);

  twfc.start();

  std::string set_req = "{'method':'set','params':{'key':'key1','val':'val1'},'id':1}"_json;
  std::string set_res;
  bool status = twfc.test_service("demo-service1", set_req, &set_res, &er);

  t << is_false<assert>(er) << wjson::strerror::message_trace(er, set_req.begin(), set_req.end() ) << FAS_FL ;

  t << is_true<assert>(status) << FAS_FL;



  std::string get_req = "{'method':'get_hashed','params':{'key':'key1'},'id':1}"_json;
  std::string get_res;
  status = twfc.test_service("demo-service1", get_req, &get_res, &er);

  t << is_false<assert>(er) << wjson::strerror::message_trace(er, set_req.begin(), set_req.end() ) << FAS_FL ;
  t << is_true<assert>(status) << FAS_FL;
  t << equal<assert, std::string>(get_res, "{'jsonrpc':'2.0','result':{'status':true,'value':6142509188972423790},'id':1}"_json) << FAS_FL;

  int res = twfc.run(1);
  t << equal<assert, int>(res, 0) << FAS_FL;
}

BEGIN_SUITE(package, "")
  ADD_UNIT(package1)
END_SUITE(package)
