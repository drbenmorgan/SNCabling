// sncabling/utils.cc - Implementation of the SuperNEMO cabling utilities
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

// Ourselves:
#include <sncabling/utils.h>

// Third party:
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#if SNCABLING_WITH_BAYEUX_DEPENDENCY == 1
#include <bayeux/datatools/utils.h>
#endif // SNCABLING_WITH_BAYEUX_DEPENDENCY

// This project:
#include <sncabling/resource_files.h>

namespace sncabling {

  const system_map_type & systems_map() 
  {
    static std::unique_ptr<system_map_type> _sysmap;
    if (_sysmap.get() == nullptr) {
      _sysmap.reset(new system_map_type);
      system_map_type & sysmap = *_sysmap.get();
      {
        system_description sd;
        sd.label       = "CaloHV";
        sd.description = "SuperNEMO calorimeter HV system";
        sd.id          = SYSTEM_CALOHV;
        sd.default_map = "@sncabling:config/snemo/demonstrator/cabling/CaloHV/tags/original/CaloHVCabling/calohv_mapping.csv";
        sysmap[sd.id]  = sd;
      }
      {
        system_description sd;
        sd.label       = "CaloSignal";
        sd.description = "SuperNEMO calorimeter signal readout system";
        sd.id          = SYSTEM_CALOSIGNAL;
        sd.default_map = "@sncabling:config/snemo/demonstrator/cabling/CaloSignal/tags/original/CaloSignalCabling/calosignal_mapping.csv";
        sysmap[sd.id]  = sd;
      }
      {
        system_description sd;
        sd.label       = "TrackerHV";
        sd.description = "SuperNEMO tracker HV system";
        sd.id          = SYSTEM_TRACKERHV;
        sysmap[sd.id]  = sd;
      }
      {
        system_description sd;
        sd.label       = "TrackerSignal";
        sd.description = "SuperNEMO tracker signal readout system";
        sd.id          = SYSTEM_TRACKERSIGNAL;
        sysmap[sd.id]  = sd;
      }
      {
        system_description sd;
        sd.label       = "LIS";
        sd.description = "SuperNEMO light injection system";
        sd.id          = SYSTEM_LIS;
        sd.default_map = "@sncabling:config/snemo/demonstrator/cabling/LIS/tags/original/lis_mapping_1.csv";
        sysmap[sd.id]  = sd;
      }
      {
        system_description sd;
        sd.label       = "SDS";
        sd.description = "SuperNEMO source deployment system";
        sd.id          = SYSTEM_SDS;
        sysmap[sd.id]  = sd;
      }
    }
    return *_sysmap.get();
  }

  system_tag_type system_label_to_tag(const std::string & label_)
  {
    system_tag_type systag = SYSTEM_UNDEF;
    for (const auto & sysitem : sncabling::systems_map()) {
      if (label_ == sysitem.second.label) {
        systag = sysitem.first;
        break;
      }
    }
    return systag;
  }

  const std::set<system_tag_type> & list_of_system_tags()
  {
    static std::set<system_tag_type> _syslis;
    if (_syslis.size() == 0) {
      const system_map_type & sysmap = systems_map();
      for (const auto & syspair : sysmap) {
        _syslis.insert(syspair.first);
      }
    }
    return _syslis;
  }

  std::string resolve_path(const std::string & path_)
  {
#if SNCABLING_WITH_BAYEUX_DEPENDENCY == 1
    std::string pp = path_;
    datatools::fetch_path_with_env(pp);
    return pp;
#else
    if (boost::starts_with(path_, "@sncabling:")) {
      std::string path_end = path_.substr(11);
      std::string path_begin = sncabling::get_resource_files_dir();
      boost::filesystem::path pb = path_begin;
      boost::filesystem::path p = pb / path_end;
      return p.string();
    }
    return path_;
#endif // SNCABLING_WITH_BAYEUX_DEPENDENCY
  }

} // namespace sncabling
