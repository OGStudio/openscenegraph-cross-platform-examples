FEATURE script.h/Impl
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
