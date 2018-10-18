FEATURE script.h/Impl
//! Serve as a hub for scriptable entities.
class Environment
{
    public:
        Environment() { }

        void addClient(
            EnvironmentClient *client,
            const std::vector<std::string> &keys
        ) {
            // Map keys to the client.
            for (auto key : keys)
            {
                this->keys[key] = client;
            }
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
