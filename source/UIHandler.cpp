#include "../headers/UIHandler.h"

#include <../libraries/glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <vector>



namespace UserInterface
{
        UIHandler* UIHandler::instance = nullptr;
        UIHandler* UIHandler::getInstance()
        {
            if(instance == nullptr)
            {
                instance = new UIHandler();
            }
            return instance;
        }


        UIHandler::UIHandler() 
        {   
            active = false;
            window = nullptr;
            pSched = nullptr;
            showTasks = false;
            InitializeLibraries();
        }

        UIHandler::~UIHandler()
        {
        }
            
        void UIHandler::InitializeLibraries()
        {
            if(!glfwInit())
            {
                return;
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            window = glfwCreateWindow(1280, 720, "Janelinha", NULL, NULL);
            if(window == nullptr)
            {
                glfwTerminate();
                return;
            }

            glfwMakeContextCurrent(window);
            
            if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                return;
            }

            glViewport(0, 0, 1280, 720);



            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void) io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     
            ImGui::StyleColorsDark();

            // Setup Platform/Renderer backends
            ImGui_ImplGlfw_InitForOpenGL(window, true);        
            ImGui_ImplOpenGL3_Init();
            active = true;
        }
        void UIHandler::run()
        {
            std::cout << "chamando metodo run. \n";
            while (!glfwWindowShouldClose(window) && active) 
            {
                // Processar eventos
                glfwPollEvents();

                // Iniciar novo frame ImGui
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                ImGui::SetNextWindowSize(ImVec2(1280, 720), ImGuiCond_FirstUseEver);
                ImGui::Begin("Hello, World");
                ImGui::Text("janela exemplo");
                if(ImGui::Button("Close"))
                {
                    active = false;
                }
                
                if(ImGui::Button("List Tasks"))
                {
                    showTasks = !showTasks;
                    pSched->listTasks();
                }
                
                if(showTasks)
                {
                    ImGui::Text("Listando as tarefas: \n");
                    std::vector<OS::Task*> tasks = pSched->getTaskBlock();
                    ImGui::BeginChild("Tasks");
                    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(20, 20));
                    for(size_t i = 0; i < tasks.size() ; i++)
                    {
                        ImGui::PushID(static_cast<int>(i));
                        ImGui::TextWrapped("ID: %s - Começo: %lld - Duração: %lld - Prioridade: %i", 
                        tasks[i]->getId().c_str(), tasks[i]->getStart(), tasks[i]->getDuration(), tasks[i]->getPriority());
                        ImGui::PopID();
                    }

                    ImGui::PopStyleVar();
                    ImGui::EndChild();
                }
                

                ImGui::End();

                // Renderização
                ImGui::Render();
                glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                
                // Renderizar dados do ImGui
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                glfwSwapBuffers(window);
            }

            end();
        }

        void UIHandler::end()
        {
            std::cout << "terminando bibliotecas. \n";
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();

            if(window)
            {
                glfwDestroyWindow(window);
                window = nullptr;
            }
            glfwTerminate();
            active = false;
        }
}