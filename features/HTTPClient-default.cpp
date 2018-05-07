FEATURE HTTPClient.h/Setup
mg_mgr_init(&this->client, 0);

FEATURE HTTPClient.h/TearDown
mg_mgr_free(&this->client);
