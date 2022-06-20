//
// Created by maxon on 20.06.22.
//

#ifndef UNIVERSAL_STORAGE_BLOCK_MANAGER_H
#define UNIVERSAL_STORAGE_BLOCK_MANAGER_H

#include <string>
#include <vector>
#include <fstream>


namespace universal_storage {


struct StorageHeader
{
    uint64_t data_signature{0};
    uint64_t file_format_version{0};
    uint64_t total_blocks_occupied{0};
    uint64_t root_block_offset{0};
    uint64_t free_block_offset{0};
};

//struct BlockMetainfo
//{
//    std::array<char, 16> name;
//    bool has_data;
//    bool is_plain_data;
//    uint64_t expiration_time;
//};
//
//
//struct Block
//{
////    std::array<std::byte, 24> metadata;
//    BlockMetainfo metainfo;
//    std::array<std::byte, 8> data;
//    std::array<uint64_t, 16> keys_offsets;
//    uint64_t next_block_offset{0};
//};

struct BlockMetaData
{
    std::string name;
    bool has_data{false};
    bool is_plain_data{true};
    uint64_t expiration_time{0};
};

struct KeyBlock
{
    BlockMetaData metadata;
    std::vector<std::byte> data;
    std::vector<uint64_t> keys_offsets;
    uint64_t next_block_offset{0};
};


class BlockManager
{
public:
    BlockManager(const std::string &file_name);

    const StorageHeader& getHeader() const;

    std::string readBlockName(uint64_t offset);
    KeyBlock readKeyBlock(uint64_t offset);

    uint64_t makeBlock(
            uint64_t offset,
            const std::string &name,
            const std::vector<std::byte> &data,
            uint64_t expiration_time);

    uint64_t makeNewBlock(
            const std::string &name,
            const std::vector<std::byte> &data,
            uint64_t expiration_time);

    std::size_t removeBlock(uint64_t offset);

    void updateBlockData(
            uint64_t offset,
            const std::vector<std::byte> &data);

private:
    std::fstream m_file;
    StorageHeader m_header;

    void writeHeader(const StorageHeader &header);
    StorageHeader readHeader();

    static constexpr std::size_t HEADER_SIZE = 40;
    static constexpr std::size_t BLOCK_SIZE = 168;
    static constexpr StorageHeader DEFAULT_HEADER = StorageHeader{
            .data_signature=0xDEADC0DE,
            .file_format_version=1,
            .total_blocks_occupied=1,
            .root_block_offset=HEADER_SIZE,
            .free_block_offset=HEADER_SIZE + BLOCK_SIZE,
    };
    static const KeyBlock DEFAULT_ROOT_BLOCK;
};

}

#endif //UNIVERSAL_STORAGE_BLOCK_MANAGER_H
