#pragma once
#include "Common/Core.h"
#include "Common/RendererShared.h"

namespace Frostium
{
	class Mesh;
	class Framebuffer;
	struct MeshComponent;

	struct DebugViewInfo
	{
		bool           bShowOmniCube = false;
		bool           bShowMRT = false;
		uint32_t       mrtAttachmentIndex = 0;
	};

	class Renderer
	{
	public:

		static void Init();
		static void Shutdown();
		static void BeginScene(const ClearInfo* clearInfo, const BeginSceneInfo* info = nullptr);
		static void EndScene();

		// Submit
		static void SubmitMesh(const glm::vec3& pos, const glm::vec3& rotation,
			const glm::vec3& scale, Mesh* mesh, int32_t materialID = 0);
		static void SubmitDirectionalLight(const glm::vec3& dir, const glm::vec4& color);
		static void SubmitPointLight(const glm::vec3& pos, const glm::vec4& color, 
			float constant, float linear, float exp);

		// Setters
		static void SetDebugViewParams(DebugViewInfo& info);
		static void SetAmbientLighting(const glm::vec3& diffuseColor, glm::vec3& specularColor,
			float IBLscale, bool enableIBL, glm::vec3& ambient);
		static void SetShadowLightDirection(const glm::vec3& dir);
		static void SetActiveDebugView(bool value);
		static void SetAmbientMixer(float value);
		static void SetExposure(float value);
		static void SetGamma(float value);

		// Getters
		static Framebuffer* GetFramebuffer();

		// Helpers
		static bool UpdateMaterials();

	private:

		static void Reset();

	private:

		static void Flush();
		static void StartNewBacth();

		static void InitPBR();
		static void InitPipelines();
		static void InitFramebuffers();
		static glm::mat4 CalculateDepthMVP(const glm::vec3& lightPos);

	private:

		friend class GraphicsContext;
	};
}