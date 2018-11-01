//! \file    sncabling/resource_files.h
//! \brief   Utilities for accessing SNCabling resource files
//! \details The SNCabling library makes use of several resource files
//!
//!          As these files are not compiled into the SNCabling library,
//!          SNCabling provides a simple API to get a path to known
//!          resource files.
//
// Copyright (c) 2018 by François Mauger <mauger@lpccaen.in2p3.fr>
//
// This file is part of SNCabling.
//
// SNCabling is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// SNCabling is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with SNCabling. If not, see <http://www.gnu.org/licenses/>.

#ifndef SNCABLING_RESOURCE_FILES_H
#define SNCABLING_RESOURCE_FILES_H

// Standard Library:
#include <string>
#include <stdexcept>

namespace sncabling {

  //! Exception class for unknown resources
  class unknown_resource_exception
    : public std::runtime_error
  {
  public:
    unknown_resource_exception(const std::string& msg) : std::runtime_error(msg) {}
  };

  //! Return URL, i.e. a path, to the  base directory where plugin DLL are installed
  //! \param overriden_env_ If set this flag trigger the search for the
  //!        environment variable SNCABLING_RESOURCE_FILES_DIR as a directory path on the filesystem
  //!        as an alternative base directory for resources in place of the
  //!        standard installation path
  std::string get_plugin_lib_dir(bool overriden_env_ = false);

  //! Return URL, i.e. a path, to the  base directory where resource files are installed
  //! \param overriden_env_ If set this flag trigger the search for the
  //!        environment variable SNCABLING_RESOURCE_FILES_DIR as a directory path on the filesystem
  //!        as an alternative base directory for resources in place of the
  //!        standard installation path
  std::string get_resource_files_dir(bool overriden_env_ = false);


  //! Return URL, i.e. a path, to named resource
  //! By default the encoded resource root, determined at compile time
  //! is used to search for the resource. This can be overriden by setting
  //! the SNCABLING_RESOURCE_FILES_DIR environment variable to a path holding custom
  //! resources.
  //! \param rname_ name of resource, given as a path relative to
  //!        resource root.
  //! \param overriden_env_ flag to allow path overriding by the SNCABLING_RESOURCE_FILES_DIR environment variable.
  std::string get_resource_file(const std::string & rname_, bool overriden_env_ = false);

  //! Return URL, i.e. a path, to the  base directory where a given plugin's resource files are installed
  //! \param plugin_name_ name of the plugin
  //! \param overriden_env_ If set this flag trigger the search for the
  //!        environment variable SNCABLING_RESOURCE_FILES_DIR as a directory path on the filesystem
  //!        as an alternative base directory for resources in place of the
  //!        standard installation path
  std::string get_plugin_resource_files_dir(const std::string & plugin_name_,
                                            bool overriden_env_ = false);

  //! Return URL, i.e. a path, to named plugin resource
  //! By default the encoded resource root, determined at compile time
  //! is used to search for the resource. This can be overriden by setting
  //! the SNCABLING_RESOURCE_FILES_DIR environment variable to a path holding custom
  //! resources.
  //! \param plugin_name_ name of the plugin
  //! \param rname_ name of resource, given as a path relative to
  //!        resource root.
  //! \param overriden_env_ flag to allow path overriding by the SNCABLING_RESOURCE_FILES_DIR environment variable.
  std::string get_plugin_resource_file(const std::string & plugin_name_,
                                       const std::string & rname_,
                                       bool overriden_env_ = false);

} // namespace sncabling

#endif // SNCABLING_RESOURCE_FILES_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --
