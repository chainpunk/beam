// Copyright 2018 The Beam Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "blake/sse/blake2.h"
#include "utility/common.h"
#include "core/block_crypt.h"

#include <functional>

namespace beamMiner
{
    class clHost;
    class minerBridge;
}
    

class EquihashGpu
{
public:

    using IsValid = std::function<bool(const beam::ByteBuffer&, const beam::Block::PoW::NonceType&)>;
    using Cancel = std::function<bool()>;

    EquihashGpu();

    bool solve(const void* pInput, uint32_t nSizeInput
        , const IsValid& valid
        , const Cancel& cancel);
private:
    std::shared_ptr<beamMiner::clHost> m_Host;
    std::shared_ptr<beamMiner::minerBridge> m_Bridge;
};
