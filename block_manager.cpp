//
// Created by maxon on 20.06.22.
//

#include <iostream>

#include <boost/endian.hpp>


#include "block_manager.h"

using namespace universal_storage;


const KeyBlock BlockManager::DEFAULT_ROOT_BLOCK = KeyBlock{
    .metadata=BlockMetaData{.name="/"}
};


BlockManager::BlockManager(const std::string &file_name)
    : m_file(file_name, std::ios::binary | std::ios::out | std::ios::in)
{
    if (!m_file) {
        m_file.clear();
        m_file.open(file_name, std::ios::out);
        m_file.close();
        m_file.open(file_name, std::ios::binary | std::ios::out | std::ios::in);

        m_header = DEFAULT_HEADER;
        writeHeader(m_header);
//        makeNewBlock("/", {}, 0);
    }
    else {
        m_header = readHeader();
    }
}

void BlockManager::writeHeader(const StorageHeader &header)
{
    m_file.seekg(0);
    auto to_write = boost::endian::native_to_little(header.data_signature);
    m_file.write(reinterpret_cast<char*>(&to_write), sizeof(to_write));

    to_write = boost::endian::native_to_little(header.file_format_version);
    m_file.write(reinterpret_cast<char*>(&to_write), sizeof(to_write));

    to_write = boost::endian::native_to_little(header.total_blocks_occupied);
    m_file.write(reinterpret_cast<char*>(&to_write), sizeof(to_write));

    to_write = boost::endian::native_to_little(header.root_block_offset);
    m_file.write(reinterpret_cast<char*>(&to_write), sizeof(to_write));

    to_write = boost::endian::native_to_little(header.free_block_offset);
    m_file.write(reinterpret_cast<char*>(&to_write), sizeof(to_write));
}

StorageHeader BlockManager::readHeader()
{
    StorageHeader header;
    m_file.seekg(0);
    char buf[8];
    auto pVal = reinterpret_cast<uint64_t*>(buf);

    m_file.read(buf, sizeof(buf));
    header.data_signature = boost::endian::little_to_native(*pVal);

    m_file.read(buf, sizeof(buf));
    header.file_format_version = boost::endian::little_to_native(*pVal);

    m_file.read(buf, sizeof(buf));
    header.total_blocks_occupied = boost::endian::little_to_native(*pVal);

    m_file.read(buf, sizeof(buf));
    header.root_block_offset = boost::endian::little_to_native(*pVal);

    m_file.read(buf, sizeof(buf));
    header.free_block_offset = boost::endian::little_to_native(*pVal);

    return header;
}
