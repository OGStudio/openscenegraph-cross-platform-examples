
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
        typedef std::vector<std::string> Values;

        EnvironmentClient() :
            respondsToKey(nullptr),
            call(nullptr)
        { }
        ~EnvironmentClient() { }

        // 'respondsToKey' method/callback.
        typedef std::function<bool (const std::string &)> CallbackRespondsToKey;
        CallbackRespondsToKey respondsToKey;

        // 'call' method/callback.
        typedef std::function<Values (const std::string &, const Values &)> CallbackCall;
        CallbackCall call;
};
// EnvironmentClient End
// Environment Start
//! Serve as a hub for scriptable entities.
class Environment
{
    public:
        Environment() { }

        void addClient(EnvironmentClient *client)
        {
            this->clients.push_back(client);
        }

        EnvironmentClient::Values call(
            const std::string &key,
            const EnvironmentClient::Values &values
        ) {
            for (auto client : this->clients)
            {
                // Make sure client has callbacks set up.
                if (
                    !client->respondsToKey ||
                    !client->call
                ) {
                    continue;
                }

                // Perform a call if client supports this key.
                if (client->respondsToKey(key))
                {
                    return client->call(key, values);
                }
            }

            SCRIPT_ENVIRONMENT_LOG(
                "ERROR Could not find a client that responds to '%s' key",
                key.c_str()
            );
            return {};
        }

    private:
        std::vector<EnvironmentClient *> clients;
};
// Environment End

} // namespace script
} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_SCRIPT_H

