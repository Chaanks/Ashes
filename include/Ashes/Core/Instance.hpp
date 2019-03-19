/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#ifndef ___Ashes_Instance_HPP___
#define ___Ashes_Instance_HPP___
#pragma once

#include "Ashes/Core/PhysicalDevice.hpp"
#include "Ashes/Core/WindowHandle.hpp"
#include "Ashes/Miscellaneous/DebugReportCallbackCreateInfo.hpp"
#include "Ashes/Miscellaneous/DeviceCreateInfo.hpp"
#include "Ashes/Miscellaneous/RendererFeatures.hpp"
#include "Ashes/Miscellaneous/LayerProperties.hpp"

#include <array>

namespace ashes
{
	/**
	*\~english
	*\brief
	*	The class initialising the rendering instance.
	*\~french
	*\brief
	*	Classe initialisant l'instance de rendu.
	*/
	class Instance
	{
	public:
		struct Configuration
		{
			//!\~french		Le nom de l'application.
			//!\~english	The application name.
			std::string appName;
			//!\~french		Le nom du moteur utilisé par l'application.
			//!\~english	The name of the engine used by the application.
			std::string engineName;
			//!\~french		Dit si la couche de validation doit être activée.
			//!\~english	Tells if the validation layer must be enabled.
			bool enableValidation;
		};

	protected:
		/**
		*\~french
		*\brief
		*	Constructor, initialises the rendering instance.
		*\~french
		*\brief
		*	Constructeur, initialise l'instance de rendu.
		*/
		Instance( ClipDirection clipDirection
			, std::string const & name
			, Configuration const & configuration );

	public:
		/**
		*\~french
		*\brief
		*	Destructor.
		*\~french
		*\brief
		*	Destructeur.
		*/
		virtual ~Instance();
		/**
		*\~french
		*\brief
		*	Récupère le GPU à l'index donné.
		*\param[in] gpuIndex
		*	L'index du GPU physique.
		*\~english
		*\brief
		*	Retrieves the GPU at given index.
		*\param[in] gpuIndex
		*	The physical GPU index.
		*/
		PhysicalDevice & getPhysicalDevice( uint32_t gpuIndex )const;
		/**
		*\~french
		*\brief
		*	Creates a logical device.
		*\param[in] surface
		*	The presentation surface.
		*\param[in] createInfos
		*	The creation informations.
		*\~french
		*\brief
		*	Crée un périphérique logique.
		*\param[in] surface
		*	La surface de présentation.
		*\param[in] createInfos
		*	Les informations de création.
		*/
		virtual DevicePtr createDevice( SurfacePtr surface
			, DeviceCreateInfo createInfos )const = 0;
		/**
		*\~french
		*\brief
		*	Crée une connexion entre un périphérique physique et une fenêtre.
		*\param[in] deviceIndex
		*	Le périphérique physique.
		*\param[in] handle
		*	Le descripteur de la fenêtre.
		*\~french
		*\brief
		*	Creates a connection between a physical device and a window.
		*\param[in] deviceIndex
		*	The physical device.
		*\param[in] handle
		*	The window handle.
		*/
		virtual SurfacePtr createSurface( PhysicalDevice const & gpu
			, WindowHandle handle )const = 0;
		/**
		*\~french
		*\brief
		*	Crée un callback de rapport de debug.
		*\param[in] createInfo
		*	Les informations de création.
		*\~french
		*\brief
		*	Creates a debug report callback.
		*\param[in] createInfo
		*	The creation informations.
		*/
		virtual DebugReportCallbackPtr createDebugReportCallback( DebugReportCallbackCreateInfo createInfo )const = 0;
		/**
		*\~english
		*\brief
		*	Computes an frustum projection matrix.
		*\param[in] left, right
		*	The left and right planes position.
		*\param[in] top, bottom
		*	The top and bottom planes position.
		*\param[in] zNear, zFar
		*	The near and far planes position.
		*\~french
		*\brief
		*	Calcule une matrice de projection frustum.
		*\param[in] left, right
		*	La position des plans gauche et droite.
		*\param[in] top, bottom
		*	La position des plans haut et bas.
		*\param[in] zNear, zFar
		*	La position des premier et arrière plans.
		*\return
		*	La matrice calculée, column major.
		*/
		virtual std::array< float, 16 > frustum( float left
			, float right
			, float bottom
			, float top
			, float zNear
			, float zFar )const = 0;
		/**
		*\~english
		*	Computes a perspective projection matrix.
		*\param[in] radiansFovY
		*	The vertical aperture angle.
		*\param[in] aspect
		*	The width / height ratio.
		*\param[in] zNear
		*	The near plane position.
		*\param[in] zFar
		*	The far plane position.
		*\return
		*	The computed matrix in column major order.
		*\~french
		*\brief
		*	Calcule une matrice de projection en perspective.
		*\param[in] radiansFovY
		*	L'angle d'ouverture verticale.
		*\param[in] aspect
		*	Le ratio largeur / hauteur.
		*\param[in] zNear
		*	La position du premier plan (pour le clipping).
		*\param[in] zFar
		*	La position de l'arrière plan (pour le clipping).
		*\return
		*	La matrice calculée, column major.
		*/
		virtual std::array< float, 16 > perspective( float radiansFovY
			, float aspect
			, float zNear
			, float zFar )const = 0;
		/**
		*\~english
		*\brief
		*	Computes an orthographic projection matrix.
		*\param[in] left, right
		*	The left and right planes position.
		*\param[in] top, bottom
		*	The top and bottom planes position.
		*\param[in] zNear, zFar
		*	The near and far planes position.
		*\return
		*	The computed matrix in column major order.
		*\~french
		*\brief
		*	Calcule une matrice de projection orthographique.
		*\param[in] left, right
		*	La position des plans gauche et droite.
		*\param[in] top, bottom
		*	La position des plans haut et bas.
		*\param[in] zNear, zFar
		*	La position des premier et arrière plans.
		*\return
		*	La matrice calculée, column major.
		*/
		virtual std::array< float, 16 > ortho( float left
			, float right
			, float bottom
			, float top
			, float zNear
			, float zFar )const = 0;
		/**
		*\~english
		*	Computes a perspective projection matrix with no far plane clipping.
		*\param[in] radiansFovY
		*	The vertical aperture angle.
		*\param[in] aspect
		*	The width / height ratio.
		*\param[in] zNear
		*	The near plane position.
		*\return
		*	The computed matrix in column major order.
		*\~french
		*\brief
		*	Calcule une matrice de projection en perspective sans clipping
		*	d'arrière plan.
		*\param[in] radiansFovY
		*	L'angle d'ouverture verticale.
		*\param[in] aspect
		*	Le ratio largeur / hauteur.
		*\param[in] zNear
		*	La position du premier plan (pour le clipping).
		*\return
		*	La matrice calculée, column major.
		*/
		std::array< float, 16 > infinitePerspective( float radiansFovY
			, float aspect
			, float zNear )const;
		/**
		*\~french
		*\brief
		*	Ajoute les couches de l'instance aux noms déjà présents dans la liste donnée.
		*\param[in,out] names
		*	La liste à compléter.
		*\~english
		*\brief
		*	Adds the instance layers names to the given names.
		*\param[in,out] names
		*	The liste to fill.
		*/
		void completeLayerNames( ashes::StringArray & names )const;
		/**
		*\~english
		*name
		*	Getters.
		*\~french
		*name
		*	Accesseurs.
		*/
		/**@{*/
		inline bool isValidationEnabled()const
		{
			return m_configuration.enableValidation;
		}

		inline ClipDirection getClipDirection()const
		{
			return m_clipDirection;
		}

		inline uint32_t getGpuCount()const
		{
			return uint32_t( m_gpus.size() );
		}

		inline uint32_t getApiVersion()const
		{
			return m_apiVersion;
		}

		inline std::string const & getName()const
		{
			return m_name;
		}

		inline RendererFeatures const & getFeatures()const
		{
			return m_features;
		}

		inline LayerProperties const & getGlobalLayer()const
		{
			return m_globalLayer;
		}

		inline std::vector< LayerProperties > const & getLayers()const
		{
			return m_layers;
		}

		inline StringArray const & getLayerNames()const
		{
			return m_layerNames;
		}

		inline StringArray const & getExtensionNames()const
		{
			return m_extensionNames;
		}
		/**@}*/

	protected:
		Configuration m_configuration;
		std::vector< PhysicalDevicePtr > m_gpus;
		LayerProperties m_globalLayer;
		std::vector< LayerProperties > m_layers;
		RendererFeatures m_features;
		uint32_t m_apiVersion{ 0u };
		StringArray m_layerNames;
		StringArray m_extensionNames;

	private:
		ClipDirection m_clipDirection;
		std::string m_name;
	};
}

#endif