FEATURE resource.h/Impl
class Pool
{
    public:
        Pool() { }

        std::vector<Resource> resources;

        void addResource(Resource &resource)
        {
            this->resources.push_back(resource);
        }

        Resource *resource(const std::string &group, const std::string &name)
        {
            auto count = this->resources.size();
            for (int i = 0; i < count; ++i)
            {
                Resource *res = &this->resources[i];
                if (
                    (res->group == group) &&
                    (res->name == name)
                ) {
                    return res;
                }
            }

            return 0;
        }

FEATURE resource.h/End
};
