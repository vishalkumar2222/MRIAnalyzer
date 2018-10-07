#include "ParticleMapper.h"

ParticleMapper::ParticleMapper()
{
    SetEmissive(false);
    SetSplatShaderCode(
        "//VTK::Color::Impl\n"
        "float dist = dot(offsetVCVSOutput.xy, offsetVCVSOutput.xy);\n"
        "if (dist > 1.0) {\n"
        "    discard;\n"
        "} else {\n"
        "    float scale = (1.0 - dist);\n"
        "    ambientColor *= scale;\n"
        "    diffuseColor *= scale;\n"
        "}\n");
}
