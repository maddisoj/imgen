#include "imgen/imgen.hpp"

namespace imgen {

imgen::imgen(fs::path wdir)
    : working_dir(std::move(wdir))
    , pal_linker(working_dir / PALETTE_DIR)
    , pat_linker(working_dir / PATTERN_DIR)
    , pal(nullptr), pat(nullptr)
{
    Py_Initialize();

    main_module = py::import("__main__");
    main_nmspc = py::extract<py::dict>(main_module.attr("__dict__"));

    add_to_path(working_dir / MODULE_DIR);
}

void imgen::set_seed(unsigned seed)
{
    import("random");
    main_nmspc["random"].attr("seed")(seed);
    std::srand(seed);
}

void imgen::generate(const fs::path& dest, unsigned width, unsigned height)
{
    if(pat == nullptr || pal == nullptr) {
        throw std::logic_error(
            "No pattern and/or palette set before attemping image generation."
        );
    }

    image img(width, height);
    context ctx(img);

    pat->draw(img, ctx, *pal);
    img.write_png(dest);
}

void imgen::set_palette(const std::string& name)
{
    pal = pal_linker.extract(name, main_nmspc);
}

std::string imgen::random_palette()
{
    auto palettes = pal_linker.get_names();
    auto name = palettes[std::rand() % palettes.size()];

    return name;
}

void imgen::set_pattern(const std::string& name)
{
    pat = pat_linker.extract(name, main_nmspc);
}

std::string imgen::random_pattern()
{
    auto patterns = pat_linker.get_names();
    auto name = patterns[std::rand() % patterns.size()];

    return name;
}

void imgen::import(const std::string& module)
{
    if(!main_nmspc.has_key(module)) {
        main_nmspc[module] = py::import(module.c_str());
    }
}

void imgen::add_to_path(const fs::path& dir)
{
    import("sys");
    main_nmspc["sys"].attr("path").attr("append")(dir.string());
}

} // namespace imgen
