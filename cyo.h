enum yo_response{
    connection_fail = 0,
    yo_ok = 1,
    yo_fail = 2
};

int yo(const char* username, const char* token);
int yo_link(const char* username, const char* token, const char* link);
int yo_location(const char* username, const char* token, const char* location);
