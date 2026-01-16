#include "gui/SdlVisual.h"

#include "mixr/base/util/system_utils.hpp"
#include "mixr/base/IComponent.hpp"
#include <SDL2/SDL.h>

#if defined(_WIN32)
#include <windows.h>
#include <GL/gl.h>
#else
#include <GL/gl.h>
#endif


namespace mixr{
    namespace crfs {

        IMPLEMENT_SUBCLASS(SdlVisual, "SdlVisual")
            EMPTY_SLOTTABLE(SdlVisual)

            SdlVisual::SdlVisual() {
            STANDARD_CONSTRUCTOR()
        }

        void SdlVisual::copyData(const SdlVisual& org, const bool cc) {
            BaseClass::copyData(org, cc);
        }

        void SdlVisual::deleteData() {
            BaseClass::deleteData();
        }

        void SdlVisual::updateData(const double dt) {
            // Update internal state if needed
            BaseClass::updateData(dt);
        }

        void SdlVisual::draw(SDL_Window* window, SDL_GLContext context) {
            SDL_GL_MakeCurrent(window, context);

            if (!initialized) {
                initialized = true;

                // Set up viewport and orthographic projection
                glViewport(0, 0, 800, 600);
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glOrtho(0, 800, 600, 0, -1, 1); // left, right, bottom, top, near, far
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();

                glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // dark gray background
            }

            // Clear screen
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Set line width and color
            glLineWidth(5.0f); // thick line
            glColor3f(1.0f, 0.0f, 0.0f); // red

            // Draw a horizontal line across the screen
            glBegin(GL_LINES);
            glVertex2f(100.0f, 300.0f); // start point
            glVertex2f(700.0f, 300.0f); // end point
            glEnd();
        }
    }
}