FEATURE library.cpp/Impl
auto registry = osgDB::Registry::instance();
auto list = registry->getReaderWriterList();
OSGCPE_LIBRARY_LOG("ReaderWriterList size: '%d'", list.size());
