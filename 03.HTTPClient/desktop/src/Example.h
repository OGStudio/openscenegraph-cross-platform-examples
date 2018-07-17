
/*
This file is part of OpenSceneGraph cross-platform examples:
  https://github.com/OGStudio/openscenegraph-cross-platform-examples

Copyright (C) 2018 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_EXAMPLE_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_EXAMPLE_H
        
#include "Application.h"
#include "scene.h"
// Example+BoxScene Start
#include "box.osgt.h"
#include "resource.h"

#include <osg/MatrixTransform>

// Example+BoxScene End
// Example+TextureImageScene Start
#include "resource.h"
#include "ppl.frag.h"
#include "ppl.vert.h"
#include "digit.png.h"

// Example+TextureImageScene End
// Example+HTTPSGetPost Start
#include "network.h"

// Example+HTTPSGetPost End

// Example+OSGCPE_EXAMPLE_LOG Start
#include "log.h"
#include "format.h"
#define OSGCPE_EXAMPLE_LOG_PREFIX "osgcpe::Example(%p) %s"
#define OSGCPE_EXAMPLE_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_EXAMPLE_LOG_PREFIX, \
        this, \
        osgcpe::format::printfString(__VA_ARGS__).c_str() \
    )

// Example+OSGCPE_EXAMPLE_LOG End

namespace osgcpe
{

// Example+03 Start
const auto EXAMPLE_TITLE = "Ex03";
// Example+03 End

struct Example
{

    osgcpe::Application *app;

    Example()
    {
        this->app = new osgcpe::Application(EXAMPLE_TITLE);

        // Example+BoxScene Start
        this->setupBoxScene();
        
        // Example+BoxScene End
        // Example+TextureImageScene Start
        this->setupSceneTexturing();
        
        // Example+TextureImageScene End
        // Example+HTTPSGetPost Start
        this->setupHTTPSGetPost();
        
        // Example+HTTPSGetPost End
    }
    ~Example()
    {

        delete this->app;
    }

    // Example+BoxScene Start
    private:
        osg::ref_ptr<osg::MatrixTransform> scene;
    
        void setupBoxScene()
        {
            resource::Resource box("models", "box.osgt", box_osgt, box_osgt_len);
            auto node = resource::node(box);
            // Use MatrixTransform to allow box transformations.
            if (node)
            {
                this->scene = new osg::MatrixTransform;
                this->scene->addChild(node);
            }
            if (this->scene.valid())
            {
                this->app->setScene(scene);
            }
            else
            {
                OSGCPE_EXAMPLE_LOG("ERROR Could not load scene");
            }
        }
    // Example+BoxScene End
    // Example+HTTPSGetPost Start
    private:
        void setupHTTPSGetPost()
        {
            // Reset background color.
            this->app->camera()->setClearColor({ 0, 0, 0, 0 });
            // Set background color 50% greener on success.
            auto success = [&](std::string response) {
                auto color = this->app->camera()->getClearColor();
                color.y() += 0.5;
                this->app->camera()->setClearColor(color);
                OSGCPE_EXAMPLE_LOG(response.c_str());
            };
            // Set background color 50% redder on failure.
            auto failure = [&](std::string reason) {
                auto color = this->app->camera()->getClearColor();
                color.x() += 0.5;
                this->app->camera()->setClearColor(color);
                OSGCPE_EXAMPLE_LOG(reason.c_str());
            };
    
            // GET.
            this->app->httpClient->get(
                "https://httpbin.org/get",
                success,
                failure
            );
            // POST.
            this->app->httpClient->post(
                "https://httpbin.org/post",
                "sample-data",
                success,
                failure
            );
        }
    // Example+HTTPSGetPost End
    // Example+TextureImageScene Start
    private:
        void setupSceneTexturing()
        {
            // Do nothing for an empty scene.
            if (!this->scene.valid())
            {
                return;
            }
            resource::Resource shaderFrag("shaders", "ppl.frag", ppl_frag, ppl_frag_len);
            resource::Resource shaderVert("shaders", "ppl.vert", ppl_vert, ppl_vert_len);
            resource::Resource texture("images", "digit.png", digit_png, digit_png_len);
            scene::textureImageScene(this->scene, shaderFrag, shaderVert, texture);
        }
    // Example+TextureImageScene End

};

} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_EXAMPLE_H

