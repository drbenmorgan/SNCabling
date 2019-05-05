#!/usr/bin/env bash

# A Bash script to build and install devel SNCabling on Ubuntu (1X.04).

opwd=$(pwd)

function my_exit()
{
    local error_code=$1
    if [ "x${error_code}" = "x" ]; then
	error_code=0
    fi
    shift 1
    local error_msg="$@"
    if [ ${error_code} -ne 0 -a -n "${error_msg}" ]; then
	echo >&2 "[error] ${error_msg}"
    fi
    exit ${error_code}
}

function my_usage()
{
    cat<<EOF

Options:

   --help               : print help
   --debug              : activate debug mode
   --only-configure     : perform configuration stage only
   --with-service       : build with service support (and Bayeux dep)
   --with-tests         : build with testing support 
   --boost-prefix path  : set the Boost installation prefix (not with service and Bayeux dep)

EOF
    return
}

rebuild=0
only_configure=0
debug=0
sncabling_source_dir="${opwd}"
sncabling_version="develop"
install_dir=$(pwd)/_install.d
build_dir=$(pwd)/_build.d
with_tests=false
with_service=false
with_bayeux=false
bayeux_min_version="3.4.1"
bayeux_version="3.4.1"
boost_prefix=
builder=make
builder_option=

function cl_parse()
{
    while [ -n "$1" ]; do
	local arg="$1"
	if [ "${arg}" = "--help" ]; then
	    my_usage
	    my_exit 0
	elif [ "${arg}" = "--debug" ]; then
	    debug=1
	elif [ "${arg}" = "--with-tests" ]; then
	    with_tests=true
	elif [ "${arg}" = "--rebuild" ]; then
	    rebuild=1
	elif [ "${arg}" = "--only-configure" ]; then
	    only_configure=1
	elif [ "${arg}" = "--source-dir" ]; then
	    shift 1
	    sncabling_source_dir="$1"
	elif [ "${arg}" = "--with-service" ]; then
	    with_service=true
	elif [ "${arg}" = "--develop" ]; then
	    sncabling_version="develop"
	elif [ "${arg}" = "--bayeux-version" ]; then
	    shift 1
	    bayeux_version="$1"
	elif [ "${arg}" = "--boost-prefix" ]; then
	    shift 1
	    boost_prefix="$1"
	fi
	shift 1
    done
    return 0
}

echo >&2 "[info] SNCabling source dir : '${sncabling_source_dir}'"

cl_parse $@
if [ $? -ne 0 ]; then
    echo >&2 "[error] Command line parsing failed!"
    my_exit 1
fi

# Check distribution:
if [ -f /etc/lsb-release ]; then
    distrib_id=$(cat /etc/lsb-release | grep DISTRIB_ID | cut -d= -f2)
    distrib_release=$(cat /etc/lsb-release | grep DISTRIB_RELEASE | cut -d= -f2)
    
    if [ "${distrib_id}" != "Ubuntu" ]; then
	echo >&2 "[error] Not an Ubuntu Linux!"
	my_exit 1
    fi
    
    if [ "${distrib_release}" != "16.04" -a "${distrib_release}" != "18.04" ]; then
	echo >&2 "[error] Not an Ubuntu Linux version 16.04 or 18.04! Abort!"
	my_exit 1
    else
	echo >&2 "[info] Found Ubuntu Linux ${distrib_release}"
    fi

fi

which ninja > /dev/null 2>&1
if [ $? -eq 0 ]; then
    builder=ninja
    builder_option=-GNinja
else
    echo >&2 "[info] Ninja not found. Using make..."
fi

# # Check:
# which brew > /dev/null 2>&1
# if [ $? -ne 0 ]; then
#     echo >&2 "[error] Linuxbrew is not setup! Please run linuxbrew_setup! Abort!"
#     my_exit 1
# else
#     echo >&2 "[info] Found Linuxbrew : $(which brew)"
# fi

if [ ! -d ${sncabling_source_dir} ]; then
    echo >&2 "[error] SNCabling source directory '${sncabling_source_dir}' does not exist! Abort!"
    my_exit 1
fi

if [ ${with_service} == true ]; then
    with_bayeux=true
fi

# Checks:
if [ ${with_bayeux} == true ]; then
    which bxquery > /dev/null 2>&1
    if [ $? -ne 0 ]; then
	echo >&2 "[error] Bayeux is not installed nor setup!"
	my_exit 1
    fi
    
    bxversion=$(bxquery --version)
    # if [ "${bxversion}" != "${bayeux_version}" ]; then
    #     echo >&2 "[error] Bayeux's version ${bxversion} is not supported!"
    #     my_exit 1
    # else
    #     echo >&2 "[info] Found Bayeux ${bxversion}"
    # fi
    echo >&2 "[info] Found Bayeux ${bxversion}"
fi

if [ "x${boost_prefix}" != "x" ]; then
    if [ ! -d ${boost_prefix} ]; then
	echo >&2 "[error] Boost prefix directory '${boost_prefix}' does not exist!"
	my_exit 1
    fi
fi

if [ -d ${install_dir} ]; then
    rm -fr ${install_dir}
fi

if [ ! -d ${build_dir} ]; then
    mkdir -p ${build_dir}
else
    if [ ${rebuild} -eq 1 ]; then
	echo >&2 "[info] Rebuilding SNCabling..."
	rm -fr ${build_dir}
	mkdir -p ${build_dir}
    fi
fi

# linuxbrew_prefix=$(brew --prefix)
# echo >&2 "[info] Linuxbrew prefix : '${linuxbrew_prefix}'"

special_options=
service_options=
if [ ${with_service} == true ]; then
    service_options="-DBayeux_DIR:PATH=$(bxquery --cmakedir) -DSNCABLING_WITH_SERVICE=ON"
fi
if [ "x${boost_prefix}" != "x" ]; then
    special_options="-DBOOST_ROOT:PATH=${boost_prefix}"
fi
### special_options="-DCMAKE_FIND_ROOT_PATH:PATH=${linuxbrew_prefix}"
### special_options="-DBOOST_ROOT:PATH=${boost_prefix}"
											  
cd ${build_dir}
echo >&2 ""
echo >&2 "[info] Configuring..."
cmake \
    -DCMAKE_BUILD_TYPE:STRING="Release" \
    -DCMAKE_INSTALL_PREFIX:PATH="${install_dir}" \
    ${special_options} \
    ${service_options} \
    -DSNCABLING_COMPILER_ERROR_ON_WARNING=ON \
    -DSNCABLING_CXX_STANDARD="11" \
    -DSNCABLING_ENABLE_TESTING=ON \
    -DSNCABLING_WITH_DOCS=ON \
    -DSNCABLING_WITH_DEVELOPER_TOOLS=ON \
    ${builder_option} \
    ${sncabling_source_dir}
if [ $? -ne 0 ]; then
    echo >&2 "[error] SNCabling ${sncabling_version} configuration failed!"
    my_exit 1
fi

if [ ${only_configure} -eq 0 ]; then

    echo >&2 ""
    echo >&2 "[info] Building..."
    ${builder} -j4
    if [ $? -ne 0 ]; then
	echo >&2 "[error] SNCabling ${vire_version} build failed!"
	my_exit 1
    fi

    if [ ${with_tests} = true ]; then
	echo >&2 ""
	echo >&2 "[info] Testing..."
	${builder} test
	if [ $? -ne 0 ]; then
	    echo >&2 "[error] SNCabling ${vire_version} testing failed!"
	    my_exit 1
	fi
    fi

    echo >&2 ""
    echo >&2 "[info] Installing..."
    ${builder} install
    if [ $? -ne 0 ]; then
	echo >&2 "[error] SNCabling ${vire_version} installation failed!"
	my_exit 1
    fi
fi

my_exit 0

# end
