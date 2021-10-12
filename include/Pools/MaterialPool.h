#pragma once
#include "Common/Memory.h"
#include "Primitives/Texture.h"

#include "Tools/GLM.h"

#include <string>
#include <optional>
#include <unordered_map>
#include <vector>
#include <mutex>

namespace cereal
{
	class access;
}

namespace SmolEngine
{
	struct RendererStorage;

	enum class MaterialTexture : uint32_t
	{
		Albedo,
		Normal,
		Metallic,
		Roughness,
		AO,
		Emissive,
	};

	struct PBRMaterial
	{
		glm::vec4  Albedro;

		float      Metalness = 0.2f;
		float      Roughness = 1.0f;
		float      EmissionStrength = 1.0f;
		uint32_t   UseAlbedroTex = 0;
				   
		uint32_t   UseNormalTex = 0;
		uint32_t   UseMetallicTex = 0;
		uint32_t   UseRoughnessTex = 0;
		uint32_t   UseAOTex = 0;
				   
		uint32_t   UseEmissiveTex = 0;
		uint32_t   AlbedroTexIndex = 0;
		uint32_t   NormalTexIndex = 0;
		uint32_t   MetallicTexIndex = 0;

		uint32_t   RoughnessTexIndex = 0;
		uint32_t   AOTexIndex = 0;
		uint32_t   EmissiveTexIndex = 0;
	private:
		uint32_t   Pad1;
	};

	struct MaterialCreateInfo
	{
		void               SetMetalness(float value);
		void               SetRoughness(float value);
		void               SetEmissionStrength(float value);
		void               SetAlbedro(const glm::vec3& color);
		void               SetTexture(MaterialTexture type, const TextureCreateInfo* info);
		void               GetTextures(std::unordered_map<MaterialTexture, TextureCreateInfo*>& out_hashmap);
					       
		bool               Load(const std::string& filePath);
		bool               Save(const std::string& filePath);

	public:

		bool               Used = false;
		float              Metallness = 0.2f;
		float              Roughness = 1.0f;
		float              EmissionStrength = 1.0f;
		TextureCreateInfo  AlbedroTex = {};
		TextureCreateInfo  NormalTex = {};
		TextureCreateInfo  MetallnessTex = {};
		TextureCreateInfo  RoughnessTex = {};
		TextureCreateInfo  AOTex = {};
		TextureCreateInfo  EmissiveTex = {};
		glm::vec3          AlbedroColor = glm::vec3(1.0f);

	private:
		friend class MaterialPool;
		friend class cereal::access;

		template<typename Archive>
		void serialize(Archive& archive)
		{
			archive(Metallness, Roughness, EmissionStrength, AlbedroTex, NormalTex, MetallnessTex, RoughnessTex, AOTex,
				EmissiveTex, AlbedroColor.r, AlbedroColor.g, AlbedroColor.b);
		}
	};

	class MaterialPool
	{
	public:		
		MaterialPool();
		~MaterialPool();

		static uint32_t                              Add(MaterialCreateInfo* infoCI, const std::string& name);
		static bool                                  Remove(const std::string& name);
		static void                                  Clear();              
		// Getters				              
		static PBRMaterial*                          GetMaterial(uint32_t ID);
		static PBRMaterial*                          GetMaterial(std::string& path);
		static int32_t                               GetMaterialID(std::string& path);
		static int32_t                               GetMaterialID(size_t& hashed_path);
		static std::vector<PBRMaterial>&             GetMaterials();
		static void                                  GetMaterialsPtr(void*& data, uint32_t& size);
		static const std::vector<Ref<Texture>>&      GetTextures();

	private:
		// Helpers				              
		uint32_t                              AddTexture(TextureCreateInfo* info, uint32_t& useTetxure);

	private:
		inline static MaterialPool*           s_Instance = nullptr;
		uint32_t                              m_MaterialIndex = 0;
		uint32_t                              m_TextureIndex = 0;
		std::unordered_map<size_t, uint32_t>  m_MaterialMap;
		std::vector<PBRMaterial>              m_Materials;
		std::vector<Ref<Texture>>             m_Textures;
		std::hash<std::string_view>           m_Hash{};
		std::mutex                            m_Mutex{};
	};
}