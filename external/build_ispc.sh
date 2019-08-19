#!/bin/bash

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# first arg of this script is the path to ispc source

ispc_dir=$(pwd)/ispc

if [ ! -d "${ispc_dir}" ]; then
    echo "The path to the ISPC directory must be given as argument"
    exit 1
fi

mkdir -p third_parties
export LLVM_HOME=${ispc_dir}/../third_parties/llvm
export ISPC_HOME=${ispc_dir}
export PATH=${LLVM_HOME}/bin-8.0/bin:${PATH}

cd "${ispc_dir}" && mkdir -p "${LLVM_HOME}"  && ./alloy.py -b --version=8.0 --selfbuild  && make -j"$(nproc)"
