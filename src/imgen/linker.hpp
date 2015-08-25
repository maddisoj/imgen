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
    fs::path link_dir;

public:
    linker(fs::path dir) : link_dir(std::move(dir))
    {
        if(!fs::is_directory(link_dir)) {
            throw std::invalid_argument("Link path is not a directory");
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
    boost::shared_ptr<LinkBase> extract(const std::string& name, py::dict& nmspc)
    {
        // We need to add the link directory to the path so that python can see
        // the scripts inside that directory.
        if(!nmspc.has_key("sys")) {
            nmspc["sys"] = py::import("sys");
        }

        nmspc["sys"].attr("path").attr("append")(link_dir.string());

        // Next we attempt to import the script into the namespace
        if(!nmspc.has_key(name)) {
            nmspc[name] = py::import(name.c_str());
        }

        auto class_name = name + "." + python_class() + "()";

        if(!nmspc[name].attr(python_class().c_str())) {
            throw new std::logic_error(fmt::format(
                "{} has no class \"{}\"", name, python_class()
            ));
        }

        // If we have successfully imported the script then we can construct the
        // needed class.
        auto py_class = py::eval(class_name.c_str(), nmspc);

        nmspc["sys"].attr("path").attr("remove")(link_dir.string());

        // Extract the C++ object from the python object and return that.
        return py::extract<boost::shared_ptr<LinkBase> >(py_class)();
    }

    /**
     * The name of the python class to extract from a python file.
     */
    virtual const std::string python_class() const = 0;
};

} //namespace imgen

#endif // IMGEN_LINKER_HPP_
