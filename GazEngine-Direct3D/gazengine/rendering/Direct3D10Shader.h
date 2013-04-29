#ifndef DIRECT3D10SHADER_H_
#define DIRECT3D10SHADER_H_

#include <string>

#include <d3dx10.h>

#include <gazengine/math/Matrix.h>
#include <gazengine/math/Vector.h>

class Direct3D10Shader
{
	public:
		Direct3D10Shader(ID3D10Device& device, ID3D10Effect* effect, ID3D10EffectTechnique* technique);

		~Direct3D10Shader();

		void apply();

		const ID3D10InputLayout& getInputLayout() const;

		void initInputLayout();

		void setVar(const std::string& name, bool value);

		void setVar(const std::string& name, const Matrix44& value);

		void setVar(const std::string& name, float value);

		void setVar(const std::string& name, const Vector3& value);

		void setVar(const std::string& name, const Vector4& value);

		void setVar(const std::string& name, ID3D10ShaderResourceView* value);

		void setVar(const std::string& structName, const std::string& name, bool value);

		void setVar(const std::string& structName, const std::string& name, const Matrix44& value);

		void setVar(const std::string& structName, const std::string& name, float value);

		void setVar(const std::string& structName, const std::string& name, const Vector3& value);

		void setVar(const std::string& structName, const std::string& name, const Vector4& value);

	private:
		ID3D10Device& device;

		ID3D10Effect* effect;

		ID3D10InputLayout* inputLayout;

		ID3D10EffectTechnique* technique;

		Direct3D10Shader(const Direct3D10Shader& original);

		Direct3D10Shader& operator=(const Direct3D10Shader& original);
};

#endif /* DIRECT3D10SHADER_H_ */
