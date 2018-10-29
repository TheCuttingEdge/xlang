#include "pch.h"
#include "strings.h"
#include "settings.h"
#include "type_writers.h"
#include "helpers.h"
#include "code_writers.h"
#include "file_writers.h"

namespace xlang
{
    settings_type settings;

    struct usage_exception {};

    void process_args(int const argc, char** argv)
    {
        std::vector<cmd::option> options
        {
            { "input", 1 },
            { "output", 0, 1 },
            { "include", 0 },
            { "exclude", 0 },
            { "verbose", 0, 0 },
            { "module", 0, 1 },
        };

        cmd::reader args{ argc, argv, options };

        if (!args)
        {
            throw usage_exception{};
        }

        settings.verbose = args.exists("verbose");
        settings.module = args.value("module", "pyrt");
        settings.input = args.files("input");

        for (auto && include : args.values("include"))
        {
            settings.include.insert(include);
        }

        for (auto && exclude : args.values("exclude"))
        {
            settings.exclude.insert(exclude);
        }

        settings.output_folder = absolute(args.value("output", "output"));
        create_directories(settings.output_folder);
    }

    auto get_files_to_cache()
    {
        std::vector<std::string> files;
        files.insert(files.end(), settings.input.begin(), settings.input.end());
        return files;
    }

    int run(int const argc, char** argv)
    {
        writer wc;

        try
        {
            auto start = get_start_time();
            process_args(argc, argv);
            cache c{ get_files_to_cache() };
            filter f{ settings.include, settings.exclude };

            if (settings.verbose)
            {
                for (auto&& file : settings.input)
                {
                    wc.write("input: %\n", file);
                }

                wc.write("output: %\n", settings.output_folder.string());
            }

            wc.flush_to_console();

            std::vector<std::string> generated_namespaces{};
            task_group group;

            auto native_module = "_" + settings.module;
            auto module_dir = settings.output_folder / settings.module;
            auto src_dir = module_dir / "src";

            group.add([&]
            {
                write_pybase_h(src_dir);
                write_package_init(module_dir, native_module);
            });

            for (auto&& ns : c.namespaces())
            {
                if (!f.includes(ns.second))
                {
                    continue;
                }

                auto ns_dir = module_dir;
                size_t pos{};
                
                while (true)
                {
                    auto new_pos = ns.first.find('.', pos);
                    if (new_pos == std::string_view::npos)
                    {
                        ns_dir /= std::string{ ns.first.substr(pos) };
                        break;
                    }

                    ns_dir /= std::string{ ns.first.substr(pos, new_pos - pos) };
                    pos = new_pos + 1;
                } 

                write_package_init(module_dir, native_module);

                std::string fqns{ ns.first };
                auto h_filename = "py." + fqns + ".h";

                generated_namespaces.emplace_back(ns.first);

                group.add([&]
                {
                    auto namespaces = write_namespace_cpp(src_dir, ns.first, ns.second);
                    write_namespace_h(src_dir, ns.first, namespaces, ns.second);
                    write_namespace_init(ns_dir, settings.module, namespaces, ns.first, ns.second);
                });
            }

            group.get();

            write_module_cpp(src_dir, native_module, generated_namespaces);
            write_setup_py(settings.output_folder, settings.module, native_module, generated_namespaces);

            if (settings.verbose)
            {
                wc.write("time: %ms\n", get_elapsed_time(start));
            }
        }
        catch (std::exception const& e)
        {
            wc.write("%\n", e.what());
            wc.flush_to_console();
            getchar();
            return -1;
        }

        wc.flush_to_console();
        return 0;
    }
}

int main(int const argc, char** argv)
{
    return xlang::run(argc, argv);
}