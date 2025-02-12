//
// Aspia Project
// Copyright (C) 2016-2023 Dmitry Chapyshev <dmitry@aspia.ru>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
//

#include "base/service.h"

#include "base/logging.h"
#include "base/crypto/scoped_crypto_initializer.h"

#include <signal.h>

namespace base {

namespace {

Service* g_self = nullptr;

const char* sigToString(int sig)
{
    switch (sig)
    {
        case SIGKILL:
            return "SIGKILL";
        case SIGTERM:
            return "SIGTERM";
        case SIGHUP:
            return "SIGHUP";
        case SIGQUIT:
            return "SIGQUIT";
        case SIGINT:
            return "SIGINT";
        case SIGSTOP:
            return "SIGSTOP";
        default:
            return "unknown";
    }
}

} // namespace

//--------------------------------------------------------------------------------------------------
Service::Service(std::u16string_view name, MessageLoop::Type type)
    : type_(type),
      name_(name)
{
    LOG(LS_INFO) << "Ctor";
    g_self = this;
}

//--------------------------------------------------------------------------------------------------
Service::~Service()
{
    LOG(LS_INFO) << "Dtor";
    g_self = nullptr;
}

//--------------------------------------------------------------------------------------------------
void Service::exec()
{
    LOG(LS_INFO) << "Begin";

    signal(SIGKILL, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGHUP, signalHandler);
    signal(SIGQUIT, signalHandler);
    signal(SIGINT, signalHandler);
    signal(SIGSTOP, signalHandler);

    std::unique_ptr<ScopedCryptoInitializer> crypto_initializer =
        std::make_unique<ScopedCryptoInitializer>();
    CHECK(crypto_initializer->isSucceeded());

    message_loop_ = std::make_unique<MessageLoop>(type_);
    task_runner_ = message_loop_->taskRunner();

    task_runner_->postTask(std::bind(&Service::onStart, this));

    message_loop_->run();
    message_loop_.reset();

    LOG(LS_INFO) << "End";
}

//--------------------------------------------------------------------------------------------------
void Service::signalHandlerImpl(int sig)
{
    if (!task_runner_->belongsToCurrentThread())
    {
        task_runner_->postTask(std::bind(&Service::signalHandlerImpl, this, sig));
        return;
    }

    switch (sig)
    {
        case SIGKILL:
        case SIGTERM:
        case SIGHUP:
        case SIGQUIT:
        case SIGINT:
        case SIGSTOP:
        {
            onStop();

            // A message loop termination command was received.
            task_runner_->postQuit();
        }
        break;

        default:
            break;
    }
}

//--------------------------------------------------------------------------------------------------
// static
void Service::signalHandler(int sig)
{
    LOG(LS_INFO) << "Signal received: " << sigToString(sig) << " (" << sig << ")";

    if (g_self)
        g_self->signalHandlerImpl(sig);
}

} // namespace base
