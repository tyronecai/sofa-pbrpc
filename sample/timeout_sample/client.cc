// Copyright (c) 2014 Baidu.com, Inc. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <sofa/pbrpc/pbrpc.h>
#include "sleep_service.pb.h"

int main(int /*argc*/, char** /*argv*/)
{
    SOFA_PBRPC_SET_LOG_LEVEL(INFO);

    // Define an rpc client.
    sofa::pbrpc::RpcClientOptions client_options;
    sofa::pbrpc::RpcClient rpc_client(client_options);

    // Define an rpc channel.
    sofa::pbrpc::RpcChannelOptions channel_options;
    sofa::pbrpc::RpcChannel rpc_channel(&rpc_client, "127.0.0.1:12321", channel_options);

    // Prepare objects.
    sofa::pbrpc::RpcController* cntl = new sofa::pbrpc::RpcController();
    sofa::pbrpc::test::SleepRequest* request =
        new sofa::pbrpc::test::SleepRequest();
    sofa::pbrpc::test::SleepResponse* response =
        new sofa::pbrpc::test::SleepResponse();
    sofa::pbrpc::test::SleepServer_Stub* stub =
        new sofa::pbrpc::test::SleepServer_Stub(&rpc_channel);

    // Call 1
    SLOG(INFO, "----------- Call 1 ---------------------------------------");
    SLOG(INFO, "Sync call SleepWithServiceTimeout(), default timeout is 2 seconds.");
    SLOG(INFO, "Sleep for 1 seconds.");
    SLOG(INFO, "Expect result is success.");
    cntl->Reset();
    request->set_sleep_time(1);
    stub->SleepWithServiceTimeout(cntl, request, response, NULL);
    SLOG(INFO, "Actual timeout is %lld milli-seconds.", cntl->Timeout());
    if (cntl->Failed()) {
        SLOG(ERROR, "Failed: %s", cntl->ErrorText().c_str());
    }
    else {
        SLOG(INFO, "Succeed: %s", response->message().c_str());
    }
    if (cntl->Failed()) {
        SLOG(ERROR, "!!!! unexpected result");
    }

    // Call 2
    SLOG(INFO, "----------- Call 2 ---------------------------------------");
    SLOG(INFO, "Sync call SleepWithServiceTimeout(), default timeout is 2 seconds.");
    SLOG(INFO, "Sleep for 3 seconds.");
    SLOG(INFO, "Expect result is failure.");
    cntl->Reset();
    request->set_sleep_time(3);
    stub->SleepWithServiceTimeout(cntl, request, response, NULL);
    SLOG(INFO, "Actual timeout is %lld milli-seconds.", cntl->Timeout());
    if (cntl->Failed()) {
        SLOG(ERROR, "Failed: %s", cntl->ErrorText().c_str());
    }
    else {
        SLOG(INFO, "Succeed: %s", response->message().c_str());
    }
    if (!cntl->Failed()) {
        SLOG(ERROR, "!!!! unexpected result");
    }

    // Call 3
    SLOG(INFO, "----------- Call 3 ---------------------------------------");
    SLOG(INFO, "Sync call SleepWithMethodTimeout(), default timeout is 4 seconds.");
    SLOG(INFO, "Sleep for 3 seconds.");
    SLOG(INFO, "Expect result is success.");
    cntl->Reset();
    request->set_sleep_time(3);
    stub->SleepWithMethodTimeout(cntl, request, response, NULL);
    SLOG(INFO, "Actual timeout is %lld milli-seconds.", cntl->Timeout());
    if (cntl->Failed()) {
        SLOG(ERROR, "Failed: %s", cntl->ErrorText().c_str());
    }
    else {
        SLOG(INFO, "Succeed: %s", response->message().c_str());
    }
    if (cntl->Failed()) {
        SLOG(ERROR, "!!!! unexpected result");
    }

    // Call 4
    SLOG(INFO, "----------- Call 4 ---------------------------------------");
    SLOG(INFO, "Sync call SleepWithMethodTimeout(), default timeout is 4 seconds.");
    SLOG(INFO, "Sleep for 5 seconds.");
    SLOG(INFO, "Expect result is failure.");
    cntl->Reset();
    request->set_sleep_time(5);
    stub->SleepWithMethodTimeout(cntl, request, response, NULL);
    SLOG(INFO, "Actual timeout is %lld milli-seconds.", cntl->Timeout());
    if (cntl->Failed()) {
        SLOG(ERROR, "Failed: %s", cntl->ErrorText().c_str());
    }
    else {
        SLOG(INFO, "Succeed: %s", response->message().c_str());
    }
    if (!cntl->Failed()) {
        SLOG(ERROR, "!!!! unexpected result");
    }

    // Call 5
    SLOG(INFO, "----------- Call 5 ---------------------------------------");
    SLOG(INFO, "Sync call SleepWithMethodTimeout(), default timeout is 4 seconds.");
    SLOG(INFO, "Set timeout of RpcController to 1 seconds.");
    SLOG(INFO, "Sleep for 3 seconds.");
    SLOG(INFO, "Expect result is failure.");
    cntl->Reset();
    cntl->SetTimeout(1000);
    request->set_sleep_time(3);
    stub->SleepWithMethodTimeout(cntl, request, response, NULL);
    SLOG(INFO, "Actual timeout is %lld milli-seconds.", cntl->Timeout());
    if (cntl->Failed()) {
        SLOG(ERROR, "Failed: %s", cntl->ErrorText().c_str());
    }
    else {
        SLOG(INFO, "Succeed: %s", response->message().c_str());
    }
    if (!cntl->Failed()) {
        SLOG(ERROR, "!!!! unexpected result");
    }

    delete cntl;
    delete request;
    delete response;
    delete stub;
    return EXIT_SUCCESS;
}
/* vim: set ts=4 sw=4 sts=4 tw=100 */
