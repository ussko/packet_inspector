#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include <getopt.h>

#include "network_inspector_factory.h"

static void process_file(std::istream &input);
static std::vector<std::string> parse_args(int argc, char *argv[]);
static void usage(const char *program_name);

int main(int argc, char *argv[])
{
    auto files = parse_args(argc, argv);
    if (files.empty())
    {
        process_file(std::cin);
    }
    else
    {
        for (const auto& file : files)
        {
            std::cout << file << ":\n";
            std::ifstream input{file};
            process_file(input);
            std::cout << "\n";
        }
    }

    return EXIT_SUCCESS;
}

static void process_file(std::istream &input)
{
    stats_t stats;
    NetworkInspectorFactory network;
    auto network_v1 = network.make_network_inspector(NETWORK_V1);
    auto network_v2 = network.make_network_inspector(NETWORK_V2);

    while (!input.eof())
    {
        bool valid = false;
        char c = input.peek();
        if (c == NETWORK_V1)
            valid = network_v1->read_packet(input);
        else if (c == NETWORK_V2)
            valid = network_v2->read_packet(input);

        if (!valid)
            input >> c;
    }

    network_v1->update_stats(stats);
    network_v2->update_stats(stats);

    std::cout << "Network v.1 packets:    " << stats.network_v1_packets    << '\n'
              << "Network v.2 packets:    " << stats.network_v2_packets    << '\n'
              << "Network v.1 addresses:  " << stats.network_v1_addresses  << '\n'
              << "Network v.2 addresses:  " << stats.network_v2_addresses  << '\n'
              << "Transport v.1 packets:  " << stats.transport_v1_packets  << '\n'
              << "Transport v.2 packets:  " << stats.transport_v2_packets  << '\n'
              << "Transport v.1 ports:    " << stats.transport_v1_ports    << '\n'
              << "Transport v.2 ports:    " << stats.transport_v2_ports    << '\n'
              << "Transport v.1 errors:   " << stats.transport_v1_errors   << '\n'
              << "Transport v.2 errors:   " << stats.transport_v2_errors   << '\n'
              << "Transport v.2 sessions: " << stats.transport_v2_sessions << '\n'
              << "Binary packets:         " << stats.binary_packets        << '\n'
              << "JSON packets:           " << stats.json_packets          << '\n'
              << "Text packets:           " << stats.text_packets          << '\n';
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
