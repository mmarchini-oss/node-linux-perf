#ifndef __LINUX_PERF_H
#define __LINUX_PERF_H

#include "v8-profiler.h"
#include <nan.h>
#include <node_object_wrap.h>
#include <fstream>
#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <thread>


namespace node {

class LinuxPerfHandler : public v8::CodeEventHandler {
 public:
  explicit LinuxPerfHandler(v8::Isolate* isolate);
  ~LinuxPerfHandler() override;

  void Handle(v8::CodeEvent* code_event) override;

  std::vector<std::string> GetBufferElements(int n) {
    int count = 0;
    std::vector<std::string> values;
    while(count < n && !buffer.empty()) {
      values.push_back(buffer.front());
      buffer.pop();
      count++;
    }
    return values;
  }

  bool IsAlive() {
    return alive;
  }

  std::ofstream* GetFile() {
    return &mapFile;
  }

 private:
  bool alive = true;
  std::thread t;
  std::ofstream mapFile;
  std::queue<std::string> buffer;
  std::stringstream codeEventStream;
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
