#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <map>
#include <functional>

#include "rdrand_func.h"
#include "argv_parser.h"


static constexpr size_t default_block_size = 512;
static constexpr size_t default_block_count = 1;

static void rand_fill(std::vector<size_t> &buffer);

int main(int argc, char *argv[])
try
{
    argv_parser ap { argc, argv };

    auto of_name = ap.of_name().value_or("No output file name");
    auto bs = ap.bs().value_or(default_block_size);
    auto count = ap.count().value_or(default_block_count);

    std::ofstream outfile { of_name, std::ofstream::binary };
    if (!outfile.good())
    {
        throw std::runtime_error(of_name + " is not good");
    }

    size_t const rand_word_size = sizeof(uint64_t);
    bool const bs_is_aligned = (0 == (bs % rand_word_size));
    size_t const rand_buffer_size = bs_is_aligned ? (bs / rand_word_size) : ((bs / rand_word_size) + rand_word_size);

    // Allocate buffers
    std::vector<size_t> rand_buffer(rand_buffer_size);
    std::vector<char> buffer(bs);

    size_t total_bytes { 0 };
    size_t bcount { 0 };

    while (bcount < count)
    {
        rand_fill(rand_buffer);

        std::memcpy(buffer.data(), rand_buffer.data(), buffer.size());

        outfile.write(buffer.data(), buffer.size());

        total_bytes += buffer.size();

        ++bcount;
    }

    std::cout << "Block size: " << bs << std::endl;
    std::cout << "Block count: " << bcount << std::endl;
    std::cout << "Total bytes: " << total_bytes << std::endl;

    return EXIT_SUCCESS;
}
catch (std::exception &exc)
{
    std::cerr << "Exception: " << exc.what() << std::endl;
    return EXIT_FAILURE;
}
catch (...)
{
    std::cerr << "Error: exception" << std::endl;
    return EXIT_FAILURE;
}

static void rand_fill(std::vector<size_t> &buffer)
{
    static std::map<size_t, std::function<void (size_t *p)>> const factory
    {
        { 4,    [](size_t *p) { rdrand_func4(p);    } },
        { 8,    [](size_t *p) { rdrand_func8(p);    } },
        { 16,   [](size_t *p) { rdrand_func16(p);   } },
        { 32,   [](size_t *p) { rdrand_func32(p);   } },
        { 64,   [](size_t *p) { rdrand_func64(p);   } },
        { 128,  [](size_t *p) { rdrand_func128(p);  } },
        { 256,  [](size_t *p) { rdrand_func256(p);  } },
        { 512,  [](size_t *p) { rdrand_func512(p);  } },
        { 1024, [](size_t *p) { rdrand_func1024(p); } },
    };

    auto it = factory.find(buffer.size());

    if (it == factory.end())
    {
        for (auto &value: buffer)
        {
            rdrand_func1(&value);
        }
    }
    else
    {
        auto &func = it->second;
        func(buffer.data());
    }
}
