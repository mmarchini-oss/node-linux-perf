#include <nan.h>

#include "linux-perf.h"

namespace node {

void LinuxPerf::Initialize(v8::Local<v8::Object> target) {
  Nan::HandleScope scope;
  auto className = Nan::New<v8::String>("LinuxPerf").ToLocalChecked();

  v8::Local<v8::FunctionTemplate> t =
      Nan::New<v8::FunctionTemplate>(LinuxPerf::New);
  t->InstanceTemplate()->SetInternalFieldCount(1);
  t->SetClassName(className);

  Nan::SetPrototypeMethod(t, "start", LinuxPerf::Start);
  Nan::SetPrototypeMethod(t, "stop", LinuxPerf::Stop);

  Nan::Set(target, className, Nan::GetFunction(t).ToLocalChecked());
}

NAN_METHOD(LinuxPerf::New) {
  Nan::HandleScope scope;
  LinuxPerf *linuxPerf = new LinuxPerf();
  linuxPerf->handler = nullptr;
  linuxPerf->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(LinuxPerf::Start) {
  Nan::HandleScope scope;
  LinuxPerf *linuxPerf = Nan::ObjectWrap::Unwrap<LinuxPerf>(info.Holder());

  if (linuxPerf->handler == nullptr) {
    linuxPerf->handler = new LinuxPerfHandler(info.GetIsolate());
    linuxPerf->handler->Enable();
    info.GetReturnValue().Set(true);
    return;
  }
  info.GetReturnValue().Set(false);
}

NAN_METHOD(LinuxPerf::Stop) {
  Nan::HandleScope scope;
  LinuxPerf *linuxPerf = Nan::ObjectWrap::Unwrap<LinuxPerf>(info.Holder());

  if (linuxPerf->handler != nullptr) {
    linuxPerf->handler->Disable();
    delete linuxPerf->handler;
    linuxPerf->handler = nullptr;
    info.GetReturnValue().Set(true);
    return;
  }
  info.GetReturnValue().Set(false);
}

extern "C" void
init(v8::Local<v8::Object> target) {
  LinuxPerf::Initialize(target);
}

NODE_MODULE(LiuxPerfBindings, init)

};
