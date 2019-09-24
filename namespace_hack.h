#pragma once

/*
This is an ugly hack to get V8JS GCC build to work with V8 CLANG build:
- When V8 is built without declaring use_custom_libcxx=false, unique_ptr implementation will
  end up in std::__Cr namespace
- However when guilding V8JS, linker searches NewDefaultPlatform implementation using std::unique_ptr,
  and fails to find one
- This snippet defines NewDefaultPlatform to match the raw symbol of NewDefaultPlatform with
  std::__Cr::unique_ptr
*/

namespace v8
{
namespace platform
{
#define NewDefaultPlatform _ZN2v88platform18NewDefaultPlatformEiNS0_15IdleTaskSupportENS0_21InProcessStackDumpingENSt4__Cr10unique_ptrINS_17TracingControllerENS3_14default_deleteIS5_EEEE
extern "C" std::unique_ptr<v8::Platform> NewDefaultPlatform(
    int thread_pool_size = 0,
    IdleTaskSupport idle_task_support = IdleTaskSupport::kDisabled,
    InProcessStackDumping in_process_stack_dumping = InProcessStackDumping::kDisabled,
    std::unique_ptr<v8::TracingController> tracing_controller = {});
}
}
