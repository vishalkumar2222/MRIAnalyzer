#pragma once

#include <vtkOpenGLPointGaussianMapper.h>

/**
 * @brief Custom GaussianMapper which is used in ESS Renderer for particle rendering
 *
 */
class ParticleMapper : public vtkOpenGLPointGaussianMapper {
public:
    static ParticleMapper *New() {
        return new ParticleMapper();
    }

    vtkTypeMacro(ParticleMapper, vtkOpenGLPointGaussianMapper);

protected:
    ParticleMapper();

private:
    ParticleMapper(const ParticleMapper&) = delete;
    void operator=(const ParticleMapper&) = delete;
};
