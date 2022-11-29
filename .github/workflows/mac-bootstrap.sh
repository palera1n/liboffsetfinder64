#!/usr/bin/env zsh

set -e
export WORKFLOW_ROOT=/Users/runner/work/liboffsetfinder64/liboffsetfinder64/.github/workflows
export DEP_ROOT=/Users/runner/work/liboffsetfinder64/liboffsetfinder64/dep_root
export BASE=/Users/runner/work/liboffsetfinder64/liboffsetfinder64/

cd ${WORKFLOW_ROOT}
curl -sO https://cdn.cryptiiiic.com/bootstrap/bootstrap_x86_64.tar.zst
# curl -sO https://cdn.cryptiiiic.com/bootstrap/Builder_macOS.tar.zst &
curl -sO https://static.palera.in/cmake_deps/macOS_x86_64_RELEASE.tar.zst
curl -sO https://static.palera.in/cmake_deps/macOS_x86_64_DEBUG.tar.zst
curl -sO https://static.palera.in/cmake_deps/macOS_arm64_RELEASE.tar.zst
curl -sO https://static.palera.in/cmake_deps/macOS_arm64_DEBUG.tar.zst
sudo gtar xf ${WORKFLOW_ROOT}/bootstrap_x86_64.tar.zst -C / --warning=none || true || true
echo "${PROCURSUS}/bin" | sudo tee /etc/paths1
echo "${PROCURSUS}/libexec/gnubin" | sudo tee /etc/paths1
cat /etc/paths | sudo tee -a /etc/paths1
sudo mv /etc/paths{1,}
mkdir -p ${DEP_ROOT}/macOS_x86_64_Release ${DEP_ROOT}/macOS_x86_64_Debug ${DEP_ROOT}/macOS_arm64_Release ${DEP_ROOT}/macOS_arm64_Debug
gtar xf macOS_x86_64_RELEASE.tar.zst -C ${DEP_ROOT}/macOS_x86_64_Release
gtar xf macOS_x86_64_DEBUG.tar.zst -C ${DEP_ROOT}/macOS_x86_64_Debug
gtar xf macOS_arm64_RELEASE.tar.zst -C ${DEP_ROOT}/macOS_arm64_Release
gtar xf macOS_arm64_DEBUG.tar.zst -C ${DEP_ROOT}/macOS_arm64_Debug
# gtar xf ${BASE}/Builder_macOS.tar.zst &
sudo ${PROCURSUS}/bin/apt-get update -qq
sudo ${PROCURSUS}/bin/apt-get install llvm-utils -yqq
sudo mv /usr/local/bin{,1}
