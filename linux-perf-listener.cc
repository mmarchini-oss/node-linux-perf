#include <sstream>
#include <thread>
#include <array>
#include <string>
#include <chrono>
#include <fstream>
#include <iostream>

#include "linux-perf.h"

namespace node {

void write_to_file(LinuxPerfHandler* handler) {

  while(handler->IsAlive()) {
    std::vector<std::string> arr = handler->GetBufferElements(100);
    if (arr.size() > 0 ) {
      for(uint i = 0; i < arr.size(); i++) {
        *(handler->GetFile()) << arr[i];
      }
    }
    std::chrono::milliseconds(1000);
  }
}

LinuxPerfHandler::LinuxPerfHandler(v8::Isolate* isolate) : v8::CodeEventHandler(isolate) {
  // TODO(mmarchini):: ideally this should be handled in another thread.
  auto pid = static_cast<int>(uv_os_getpid());

  mapFile.open("/tmp/perf-" + std::to_string(pid) + ".map");
  t = std::thread(write_to_file, this);
}

LinuxPerfHandler::~LinuxPerfHandler() {
  alive = false;
  t.join();
  mapFile.close();
}

std::string LinuxPerfHandler::FormatName(v8::CodeEvent* code_event) {
  auto comment = std::string(code_event->GetComment());
  if (not comment.empty()) return comment;

  char buffer[1000];
  std::ostringstream formattedName;

  auto functionName = code_event->GetFunctionName();
  functionName->WriteUtf8(buffer, 1000);
  formattedName << buffer;

  auto scriptName = code_event->GetScriptName();
  scriptName->WriteUtf8(buffer, 1000);
  if(buffer[0] != '\0') {
    formattedName << " " << buffer << ":" << code_event->GetScriptLine();
  }

  return formattedName.str();
}

void LinuxPerfHandler::Handle(v8::CodeEvent* code_event) {
  // std::cout << "Handling event" << std::endl;
  codeEventStream << std::hex << code_event->GetCodeStartAddress() << " "
          << std::hex << code_event->GetCodeSize() << " "
          << v8::CodeEvent::GetCodeEventTypeName(code_event->GetCodeType())
          << ":" << FormatName(code_event) << std::endl;

  std::lock_guard<std::mutex> lock(mutex_);
  buffer.push(codeEventStream.str());
  codeEventStream.str("");
}


}
