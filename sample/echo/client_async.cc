// Copyright (c) 2014 Baidu.com, Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <sofa/pbrpc/pbrpc.h>
#include <unistd.h>
#include <atomic>
#include "echo_service.pb.h"

void EchoCallback(sofa::pbrpc::RpcController* cntl,
                  sofa::pbrpc::test::EchoRequest* request,
                  sofa::pbrpc::test::EchoResponse* response, std::atomic<int>* callbacked) {
  SLOG(INFO, "RemoteAddress=%s", cntl->RemoteAddress().c_str());
  SLOG(INFO, "IsRequestSent=%s", cntl->IsRequestSent() ? "true" : "false");

  if (cntl->IsRequestSent()) {
    SLOG(INFO, "LocalAddress=%s", cntl->LocalAddress().c_str());
    SLOG(INFO, "SentBytes=%ld", cntl->SentBytes());
  }

  if (cntl->Failed()) {
    SLOG(ERROR, "request failed: %s", cntl->ErrorText().c_str());
  } else {
    SLOG(INFO, "request succeed: %s", response->message().c_str());
  }

  delete cntl;
  delete request;
  delete response;
  callbacked->fetch_add(1);
}

int main() {
  SOFA_PBRPC_SET_LOG_LEVEL(INFO);

  // Define an rpc server.
  sofa::pbrpc::RpcClientOptions client_options;
  sofa::pbrpc::RpcClient rpc_client(client_options);

  // Define an rpc channel.
  sofa::pbrpc::RpcChannelOptions channel_options;
  sofa::pbrpc::RpcChannel rpc_channel(&rpc_client, "127.0.0.1:12321",
                                      channel_options);

  std::atomic<int> callbacked(0);
  // Async call.
  sofa::pbrpc::test::EchoServer_Stub stub(&rpc_channel);


  for (int i = 0; i < 10; ++i) {
    auto cntl = new sofa::pbrpc::RpcController();
    cntl->SetTimeout(3000);
    // Prepare parameters.
    auto request = new sofa::pbrpc::test::EchoRequest();
    request->set_message("Hello from qinzuoyan01");
    auto response = new sofa::pbrpc::test::EchoResponse();
    google::protobuf::Closure* done = sofa::pbrpc::NewClosure(
        &EchoCallback, cntl, request, response, &callbacked);

    stub.Echo(cntl, request, response, done);
  }

  // Wait call done.
  while (callbacked < 10) {
    usleep(100000);
  }

  SLOG(INFO, "request succeed: %d", callbacked.load());

  sleep(10);

  return EXIT_SUCCESS;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 */
