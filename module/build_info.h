extern const char* demo_build_info_string;
struct demo_build_info{ const char* operator()() const { return demo_build_info_string;} };
