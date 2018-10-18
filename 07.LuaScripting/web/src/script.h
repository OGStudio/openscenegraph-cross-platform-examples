
/*
This file is part of OpenSceneGraph cross-platform examples:
  https://github.com/OGStudio/openscenegraph-cross-platform-examples

Copyright (C) 2018 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_SCRIPT_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_SCRIPT_H

// EnvironmentClient Start
#include <functional>

// EnvironmentClient End

// SCRIPT_ENVIRONMENT_CLIENT_CALL Start
#define SCRIPT_ENVIRONMENT_CLIENT_CALL(...) \
    [=](const std::string &key, const std::vector<std::string> &values) { \
        __VA_ARGS__ \
    }
// SCRIPT_ENVIRONMENT_CLIENT_CALL End
// SCRIPT_ENVIRONMENT_LOG Start
#include "log.h"
#include "format.h"
#define SCRIPT_ENVIRONMENT_LOG_PREFIX "script::Environment(%p) %s"
#define SCRIPT_ENVIRONMENT_LOG(...) \
    log::logprintf( \
        SCRIPT_ENVIRONMENT_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )
// SCRIPT_ENVIRONMENT_LOG End

namespace osgcpe
{
namespace script
{

// EnvironmentClient Start
//! Serve as an interface to scriptable entity.
class EnvironmentClient
{
    public:
        EnvironmentClient() :
            call(nullptr)
        { }
        ~EnvironmentClient() { }

        // 'call' method/callback.
        typedef
            std::function<
                std::vector<std::string> (
                    const std::string &,
                    const std::vector<std::string> &
                )
            > CallbackCall;
        CallbackCall call;
};
// EnvironmentClient End
// Environment Start
//! Serve as a hub for scriptable entities.
class Environment
{
    public:
        Environment() { }

        void addClient(
            EnvironmentClient *client,
            const std::vector<std::string> &keys
        ) {
            SCRIPT_ENVIRONMENT_LOG("01.addClient");
            // TODO Keep client for later removal?
            //this->clients[client] = keys;

            // Map keys to the client.
            for (auto key : keys)
            {
                this->keys[key] = client;
            }

            SCRIPT_ENVIRONMENT_LOG("02.addClient");
        }

        std::vector<std::string> call(
            const std::string &key,
            const std::vector<std::string> &values
        ) {
            // Make sure there is a client that responds to the key.
            auto it = this->keys.find(key);
            if (it == this->keys.end())
            {
                SCRIPT_ENVIRONMENT_LOG(
                    "ERROR Could not find a client that responds to '%s' key",
                    key.c_str()
                );
                return { };
            }

            // Make sure the client has callback assigned.
            auto client = it->second;
            if (!client->call)
            {
                SCRIPT_ENVIRONMENT_LOG(
                    "ERROR Could not process '%s' key because the client "
                    "does not have a callback assigned",
                    key.c_str()
                );
                return { };
            }

            // Perform the call.
            return client->call(key, values);
        }

    private:
        std::map<std::string, EnvironmentClient *> keys;
};
// Environment End

} // namespace script
} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_SCRIPT_H

