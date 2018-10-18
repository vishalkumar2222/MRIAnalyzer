#pragma once

#include <vtkOpenGLPointGaussianMapper.h>

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
