//
// Aspia Project
// Copyright (C) 2020 Dmitry Chapyshev <dmitry@aspia.ru>
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

#include "base/peer/relay_client.h"

#include "base/location.h"
#include "base/logging.h"
#include "base/crypto/key_pair.h"
#include "base/crypto/message_encryptor_openssl.h"
#include "base/message_loop/message_loop.h"
#include "base/message_loop/message_pump_asio.h"
#include "base/net/network_channel.h"
#include "base/strings/unicode.h"
#include "proto/relay_peer.pb.h"

#include <asio/connect.hpp>
#include <asio/write.hpp>

namespace base {

RelayClient::RelayClient()
    : io_context_(MessageLoop::current()->pumpAsio()->ioContext()),
      socket_(io_context_),
      resolver_(io_context_)
{
    // Nothing
}

RelayClient::~RelayClient()
{
    delegate_ = nullptr;

    std::error_code ignored_code;
    socket_.cancel(ignored_code);
    socket_.close(ignored_code);
}

void RelayClient::start(const proto::RelayCredentials& credentials, Delegate* delegate)
{
    delegate_ = delegate;
    DCHECK(delegate_);

    message_ = authenticationMessage(credentials.key(), credentials.secret());

    resolver_.async_resolve(local8BitFromUtf16(utf16FromUtf8(credentials.host())),
                            std::to_string(credentials.port()),
        [this](const std::error_code& error_code,
               const asio::ip::tcp::resolver::results_type& endpoints)
    {
        if (error_code)
        {
            if (error_code != asio::error::operation_aborted)
                onErrorOccurred(FROM_HERE, error_code);
            return;
        }

        asio::async_connect(socket_, endpoints,
                            [this](const std::error_code& error_code,
                                   const asio::ip::tcp::endpoint& /* endpoint */)
        {
            if (error_code)
            {
                if (error_code != asio::error::operation_aborted)
                    onErrorOccurred(FROM_HERE, error_code);
                return;
            }

            onConnected();
        });
    });
}

void RelayClient::onConnected()
{
    if (message_.empty())
    {
        onErrorOccurred(FROM_HERE, std::error_code());
        return;
    }

    message_size_ = message_.size();

    asio::async_write(socket_, asio::const_buffer(&message_size_, sizeof(message_size_)),
        [this](const std::error_code& error_code, size_t bytes_transferred)
    {
        if (error_code)
        {
            if (error_code != asio::error::operation_aborted)
                onErrorOccurred(FROM_HERE, error_code);
            return;
        }

        if (bytes_transferred != sizeof(message_size_))
        {
            onErrorOccurred(FROM_HERE, std::error_code());
            return;
        }

        asio::async_write(socket_, asio::const_buffer(message_.data(), message_.size()),
                          [this](const std::error_code& error_code, size_t bytes_transferred)
        {
            if (error_code)
            {
                if (error_code != asio::error::operation_aborted)
                    onErrorOccurred(FROM_HERE, error_code);
                return;
            }

            if (bytes_transferred != message_size_)
            {
                onErrorOccurred(FROM_HERE, std::error_code());
                return;
            }

            if (delegate_)
            {
                delegate_->onRelayConnectionReady(
                    std::unique_ptr<NetworkChannel>(new NetworkChannel(std::move(socket_))));
            }
        });
    });
}

void RelayClient::onErrorOccurred(const Location& location, const std::error_code& error_code)
{
    LOG(LS_ERROR) << "Failed to connect to relay server: "
                  << utf16FromLocal8Bit(error_code.message()) << " ("
                  << location.toString() << ")";

    if (delegate_)
        delegate_->onRelayConnectionError();
}

// static
ByteArray RelayClient::authenticationMessage(const proto::RelayKey& key, const std::string& secret)
{
    if (key.type() != proto::RelayKey::TYPE_X25519)
    {
        LOG(LS_ERROR) << "Unsupported key type: " << key.type();
        return ByteArray();
    }

    if (key.encryption() != proto::RelayKey::ENCRYPTION_CHACHA20_POLY1305)
    {
        LOG(LS_ERROR) << "Unsupported encryption type: " << key.encryption();
        return ByteArray();
    }

    if (key.public_key().empty())
    {
        LOG(LS_ERROR) << "Empty public key";
        return ByteArray();
    }

    if (key.iv().empty())
    {
        LOG(LS_ERROR) << "Empty IV";
        return ByteArray();
    }

    if (secret.empty())
    {
        LOG(LS_ERROR) << "Empty secret";
        return ByteArray();
    }

    KeyPair key_pair = KeyPair::create(KeyPair::Type::X25519);
    if (!key_pair.isValid())
    {
        LOG(LS_ERROR) << "KeyPair::create failed";
        return ByteArray();
    }

    ByteArray session_key = key_pair.sessionKey(fromStdString(key.public_key()));
    if (session_key.empty())
    {
        LOG(LS_ERROR) << "Failed to create session key";
        return ByteArray();
    }

    std::unique_ptr<MessageEncryptor> encryptor =
        MessageEncryptorOpenssl::createForChaCha20Poly1305(session_key, fromStdString(key.iv()));
    if (!encryptor)
        return ByteArray();

    std::string encrypted_secret;
    encrypted_secret.resize(encryptor->encryptedDataSize(secret.size()));
    if (!encryptor->encrypt(secret.data(), secret.size(), encrypted_secret.data()))
        return ByteArray();

    proto::PeerToRelay message;

    message.set_key_id(key.key_id());
    message.set_public_key(base::toStdString(key_pair.publicKey()));
    message.set_data(std::move(encrypted_secret));

    return serialize(message);
}

} // namespace base
