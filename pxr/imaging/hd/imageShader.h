//
// Copyright 2023 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef PXR_IMAGING_HD_IMAGE_SHADER_H
#define PXR_IMAGING_HD_IMAGE_SHADER_H

#include "pxr/pxr.h"
#include "pxr/imaging/hd/api.h"
#include "pxr/imaging/hd/version.h"
#include "pxr/imaging/hd/sprim.h"

#include "pxr/base/tf/staticTokens.h"
#include "pxr/base/vt/dictionary.h"

#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

#define HD_IMAGE_SHADER_TOKENS                              \
    (enabled)                                               \
    (priority)                                              \
    (filePath)                                              \
    (constants)

TF_DECLARE_PUBLIC_TOKENS(HdImageShaderTokens, HD_API, HD_IMAGE_SHADER_TOKENS);

class HdSceneDelegate;

/// \class HdImageShader
///
/// An image shader.
///
class HdImageShader : public HdSprim
{
public:
    HD_API
    HdImageShader(SdfPath const & id);
    HD_API
    ~HdImageShader() override;

    // Change tracking for HdImageShader
    enum DirtyBits : HdDirtyBits {
        Clean                 = 0,
        DirtyEnabled          = 1 << 0,
        DirtyPriority         = 1 << 1,
        DirtyFilePath         = 1 << 2,
        DirtyConstants        = 1 << 3,

        AllDirty              = (DirtyEnabled
                                 |DirtyPriority
                                 |DirtyFilePath
                                 |DirtyConstants)
    };

    // ---------------------------------------------------------------------- //
    /// Sprim API
    // ---------------------------------------------------------------------- //
 
    /// Synchronizes state from the delegate to this object.
    HD_API
    void Sync(
        HdSceneDelegate* sceneDelegate,
        HdRenderParam* renderParam,
        HdDirtyBits* dirtyBits) override;

    /// Returns the minimal set of dirty bits to place in the
    /// change tracker for use in the first sync of this prim.
    /// Typically this would be all dirty bits.
    HD_API
    HdDirtyBits GetInitialDirtyBitsMask() const override;

    // ---------------------------------------------------------------------- //
    /// Image shader parameters accessor API
    // ---------------------------------------------------------------------- //
    HD_API
    bool GetEnabled() const;

    HD_API
    int GetPriority() const;

    HD_API
    const std::string& GetFilePath() const;

    HD_API
    const VtDictionary& GetConstants() const;

private:
    bool _enabled;
    int _priority;
    std::string _filePath;
    VtDictionary _constants;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HD_IMAGE_SHADER_H
