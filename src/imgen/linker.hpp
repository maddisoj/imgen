#ifndef IMGEN_LINKER_HPP_
#define IMGEN_LINKER_HPP_

#include <boost/python.hpp>
#include <boost/filesystem.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <format.h>

#include <exception>
#include <string>
#include <vector>

namespace py = boost::python;
namespace fs = boost::filesystem;

namespace imgen {

/**
 * A linker is responsible for determining the available python classes,
 * instantiating them and extracting the C++ class from them.
 */
template<typename LinkBase>
class linker {
    // The directory the linker looks in for python files
    const fs::path link_dir;

    // The main python namespace for importing the file
    py::dict main_nmspc;

public:
    /**
     * Attempts to add the linker's directory to the system path
     */
    linker(const fs::path& link_dir, py::dict& main_nmspc)
        : link_dir(link_dir), main_nmspc(main_nmspc)
    {
        if(!fs::is_directory(link_dir)) {
            throw std::invalid_argument("Link path is not a directory");
        }

        if(!main_nmspc.has_key("sys")) {
            main_nmspc["sys"] = py::import("sys");
        }

        main_nmspc["sys"].attr("path").attr("append")(link_dir.string());
    }

    /**
     * Removes the linker's directory from the system path.
     */
    ~linker()
    {
        if(main_nmspc.has_key("sys")) {
            main_nmspc["sys"].attr("path").attr("remove")(link_dir.string());
        }
    }

    /**
     * Creates a list of files in the link directory that end with the .py
     * extension. There name is the file's basename.
     */
    std::vector<std::string> get_names()
    {
        std::vector<std::string> names;

        std::for_each(
            fs::directory_iterator(link_dir), fs::directory_iterator(),
            [&names](const fs::directory_entry& entry) {
                if(fs::is_regular_file(entry) && entry.path().extension() == ".py") {
                    names.push_back(entry.path().stem().string());
                }
            }
        );

        return names;
    }

    /**
     * Extracts a python class from a file in the link directory who's basename
     * is the given name.
     */
    boost::shared_ptr<LinkBase> extract(const std::string& name)
    {
        if(!main_nmspc.has_key(name)) {
            main_nmspc[name] = py::import(name.c_str());
        }

        auto class_name = name + "." + python_class() + "()";

        fmt::print("{}\n", class_name);

        if(!main_nmspc[name].attr(python_class().c_str())) {
            throw new std::logic_error(fmt::format(
                "{} has no class \"{}\"", name, python_class()
            ));
        }

        auto py_class = py::eval(class_name.c_str(), main_nmspc);

        return py::extract<boost::shared_ptr<LinkBase> >(py_class)();
    }

    /**
     * The name of the python class to extract from a python file.
     */
    virtual const std::string python_class() const = 0;
};

} //namespace imgen

#endif // IMGEN_LINKER_HPP_
