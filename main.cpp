#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include <getopt.h>

static std::vector<std::string> parse_args(int argc, char *argv[]);
static void usage(const char *program_name);

int main(int argc, char *argv[])
{
    auto files = parse_args(argc, argv);
    if (files.empty())
    {
        std::cout << "No files to process\n";
    }
    else
    {
        for (const auto& file : files)
        {
            std::cout << file << "\n";
        }
    }

    return EXIT_SUCCESS;
}

static std::vector<std::string> parse_args(int argc, char *argv[])
{
    std::vector<std::string> files;
    bool has_opts = true;

    while (has_opts)
    {
        int option_index = 0;
        static struct option long_options[] =
        {
            {"help", no_argument, 0, 'h'},
            {0, 0, 0, 0}
        };

        switch (int c = getopt_long(argc, argv, "Hh", long_options, &option_index); c)
        {
        case -1:
            has_opts = false;
            break;
        case 'h':
        case 'H':
        case '?':
            usage(basename(argv[0]));
            exit(EXIT_SUCCESS);
            break;
        default:
            std::cerr << "getopt_long() error: " << c << "\n";
            exit(EXIT_FAILURE);
        }
    }

    while (optind < argc)
        files.emplace_back(argv[optind++]);

    return files;
}

static void usage(const char *program_name)
{
    std::cout << program_name << " - inspect packets in traffic dump file.\n"
              << "Usage:\n"
              << "    " << program_name << " [FILES...]\n"
              << "Options:\n"
              << "    -h, --help - print help\n"
              << "    FILES - files to process (reads stdin if omitted)\n"
              << "Examples:\n"
              << "    " << program_name << " < network_0.raw\n"
              << "    " << program_name << " ../data/*.raw\n";
}