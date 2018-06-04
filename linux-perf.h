#ifndef __LINUX_PERF_H
#define __LINUX_PERF_H

#include "v8-profiler.h"
#include <nan.h>
#include <node_object_wrap.h>
#include <fstream>


namespace node {

class LinuxPerfHandler : public v8::CodeEventHandler {
 public:
  explicit LinuxPerfHandler(v8::Isolate* isolate);
  ~LinuxPerfHandler() override;


  void Handle(v8::CodeEvent* code_event) override;
 private:
  std::ofstream mapFile;
  std::string FormatName(v8::CodeEvent* code_event);
};

class LinuxPerf : public Nan::ObjectWrap {
 public:
  static void Initialize(v8::Local<v8::Object> target);

  static NAN_METHOD(New);
  static NAN_METHOD(Start);
  static NAN_METHOD(Stop);

  LinuxPerfHandler* handler;

  LinuxPerf() = default;
  ~LinuxPerf() = default;
};

};

#endif  // __LINUX_PERF_H
