FEATURE main.cpp/Impl
auto registry = osgDB::Registry::instance();
auto list = registry->getReaderWriterList();
OSGCPE_MAIN_LOG("ReaderWriterList size: '%d'", list.size());
