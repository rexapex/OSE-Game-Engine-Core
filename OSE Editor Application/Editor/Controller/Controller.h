#pragma once

#include "OSE-Core/Game/Scene/SceneManager.h""
#include "OSE-Core/Game/Camera/Camera.h"
#include "OSE-Core/Resources/Texture/Texture.h"
#include "OSE-Core/Math/Transform.h"
#include "OSE-Core/Windowing/WindowCallbackAdaptor.h"

class SimpleApp;
class CefBrowser;

namespace ose
{
	class CefAdaptor;
	class WindowManager;
	class RenderingEngine;
	class InputManager;
	class Entity;
	class Scene;
	class Project;
	class Texture;
	class SpriteRenderer;
}

namespace ose::editor
{
	class Controller final : public SceneManager, public WindowCallbackAdaptor
	{
	public:
		Controller(std::unique_ptr<CefAdaptor> cef_adaptor);
		~Controller();

		// Start execution of the controller
		void StartController();

		// Activate an entity along with activated sub-entities
		// Should NEVER be called directly by a script, enable entity instead
		void OnEntityActivated(Entity & entity);

		// Deactivate an entity along with all its sub-entities
		// Should NEVER be called directly by a script, disable entity instead
		void OnEntityDeactivated(Entity & entity);

		// Activate a chunk along with activated sub-entities
		// Should NEVER be called directly by a script, enable chunk instead
		virtual void OnChunkActivated(Chunk & chunk) override;

		// Deactivate a chunk along with all its sub-entities
		// Should NEVER be called directly by a script, disable chunk instead
		virtual void OnChunkDeactivated(Chunk & chunk) override;

		// Update the editor gui texture data
		void UpdateGuiTexture(IMGDATA data, int32_t width, int32_t height);

		// Called on framebuffer resize
		void OnFramebufferResize(int width, int height) override;

		// Called on user input change
		void OnInputChange(EInputType type, bool triggered) override;

		// Called on mouse position change
		void OnMousePosChange(double x, double y) override;

		// Set the active camera
		// If c is nullptr, the active camera is set to the default camera
		// If the user destroys the active camera, the active camera must be set to nullptr (or a valid camera) to prevent errors
		void SetActiveCamera(Camera * c) { active_camera_ = c ? c : &default_camera_; active_camera_->SetGameReference(nullptr); }

		// Get the active camera
		Camera * GetActiveCamera() const { return active_camera_; }

		// Get the window manager
		WindowManager const & GetWindowManager() const { return *window_manager_; }

	protected:
		// Called upon a project being activated
		// Project is activated upon successful load
		// Only one project can be active at a time
		virtual void OnProjectActivated(Project & project);

		// Called upon a project being deactivated
		// Project is deactivated when a new project is loaded
		virtual void OnProjectDeactivated(Project & project);

		// Called upon a scene being activated
		// Depending on switch manager, could be multiple active scenes
		virtual void OnSceneActivated(Scene & scene);

		// Called upon a scene being deactivated
		// Depending on switch manager, could be multiple active scenes
		virtual void OnSceneDeactivated(Scene & scene);


	private:
		// Window manager handles window creation, events and input
		std::unique_ptr<WindowManager> window_manager_;

		// Rendering engine handles all rendering of entity render objects
		std::unique_ptr<RenderingEngine> rendering_engine_;

		// Input manager handles mouse, keyboard, etc. input from the user
		std::unique_ptr<InputManager> input_manager_;

		// The sprite renderer component / corresponding texture / transform of the editor gui
		std::unique_ptr<SpriteRenderer> gui_renderer_;
		std::unique_ptr<Texture> gui_texture_;
		Transform gui_transform_;

		// Interface to cef controls
		std::unique_ptr<CefAdaptor> cef_adaptor_;

		// The active camera (rendering is done relative to the active camera transform)
		Camera * active_camera_ { nullptr };

		// The default camera
		Camera default_camera_;

		// True iff the controller is currently running (paused is a subset of running)
		bool running_;

		// Called from StartController, runs a loop while running_ is true
		void RunController();

		// Initialise components of an entity along with its sub-entities
		void InitEntity(Entity & entity);
	};
}