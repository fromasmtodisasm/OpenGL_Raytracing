#pragma once

#ifndef _GL3W_
#define _GL3W_
    #include <GL\gl3w.h>
    #include <GLFW\glfw3.h>
#endif

#include <unordered_set>
#include <array>
#include "GLFWWindow.h"

class GLFWInput
{
private:
    double m_xPos, m_yPos;
    double m_xDiff, m_yDiff;
    std::array<bool, 3> m_mouseButtonPressed;
    std::unordered_set<unsigned int>  m_keyPressed;
    GLFWwindow* m_window;

public:
    GLFWInput() :
        m_xPos(0), m_yPos(0),
        m_xDiff(0), m_yDiff(0),
        m_mouseButtonPressed{ false, false, false }, m_window(nullptr)
    {}

    void bindInputToWindow(const GLFWWindow& window)
    {
        m_window = window.getGLFWwindow();
    }

    void updateInput()
    {
        double x, y;
        glfwPollEvents();
        glfwGetCursorPos(m_window, &x, &y);
        m_xDiff = x - m_xPos;
        m_yDiff = y - m_yPos;
        m_xPos = x;
        m_yPos = y;
    }

    int isKeyPressed(unsigned int GLFW_Key) const
    {
        return (glfwGetKey(m_window, GLFW_Key) == GLFW_PRESS);
    }

    bool isMouseButtonPressed(unsigned int GLFW_MouseButton) const
    {
        return (glfwGetMouseButton(m_window, GLFW_MouseButton) == GLFW_PRESS);
    }

    double getXPos() const { return m_xPos; }
    double getYPos() const { return m_yPos; }
    double getXPosDiff() const { return m_xDiff; }
    double getYPosDiff() const { return m_yDiff; }

    bool isKeyPressedOnce(unsigned int GLFW_Key)
    {
        if (isKeyPressed(GLFW_Key)){
            if (m_keyPressed.find(GLFW_Key) == m_keyPressed.end()){
            m_keyPressed.insert(GLFW_Key);
            return true;
            }
        } else {
            m_keyPressed.erase(GLFW_Key);
        }
        return false;
    }

    bool isMouseButtonPressedOnce(unsigned int GLFW_MouseButton)
    {
        if (isMouseButtonPressed(GLFW_MouseButton)){
            if (!m_mouseButtonPressed[GLFW_MouseButton]){
                m_mouseButtonPressed[GLFW_MouseButton] = true;
                return true;
            }
        } else {
            m_mouseButtonPressed[GLFW_MouseButton] = false;
        }
        return false;
    }

    void setMousePos(double xpos, double ypos){ glfwSetCursorPos(m_window, xpos, ypos); }

};